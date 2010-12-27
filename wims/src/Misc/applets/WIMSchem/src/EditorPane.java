/*
    WIMSchem Elements: Chemistry molecular diagram drawing tool.
    
    (c) 2005 Dr. Alex M. Clark
    
    Released as GNUware, under the Gnu Public License (GPL)
    
    See www.gnu.org for details.
*/

package WIMSchem;

import java.util.*;
import java.text.*;
import java.awt.*;
import java.awt.geom.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

/*
    Custom widget for viewing and editing a molecular structure. The widget is a rather heavy one, and features a lot of the work-horse
    functions for various tools, including the specific details of user interaction, and drawing of the structure itself, with various
    annotations for editing and selection. Can optionally be used as a lightweight widget with just view and selection.
*/

public class EditorPane extends JComponent 
    implements MouseListener, MouseMotionListener, FocusListener, KeyListener, MouseWheelListener, ComponentListener
{
    Molecule mol;
    boolean editable=true,hasBorder=false,autoScale=false;
    static final double IDEALBOND=1.5; // stylised bond distance (Angstroms)
    // note: px=(atomX+offsetX)*scale; ax=px/scale-offsetX; offsetX=px/scale-ax (and same for Y)
    double offsetX=0,offsetY=0; // in Angstrom units
    double scale=DrawMolecule.DEFSCALE; // pixels per Angstrom
    boolean[] selected=null,dragged=null;
    double[] px=null,py=null,rw=null,rh=null;
    double[][] bfx=null,bfy=null,btx=null,bty=null;
    int highlightAtom=0,highlightBond=0;
    int showMode=DrawMolecule.SHOW_ALL_ELEMENTS;
    // jm.evers 27/12/2008
    boolean showHydr=MainPanel.viewH;
    boolean viewC=MainPanel.viewC;
    public static boolean[] bondselection;
    public static boolean[] atomselection;
    //
    boolean showSter=false;

    static final int TOOL_CURSOR=1;
    static final int TOOL_ROTATOR=2;
    static final int TOOL_ERASOR=3;
    static final int TOOL_ATOM=4;
    static final int TOOL_BOND=5;
    static final int TOOL_CHARGE=6;
    static final int TOOL_TEMPLATE=7;
    // jm.evers 4/3/2010
    static final int TOOL_SELECT=8;
    
    static final int DRAG_SELECT=1;
    static final int DRAG_MOVE=2;
    static final int DRAG_COPY=3;
    static final int DRAG_SCALE=4;
    static final int DRAG_ROTATE=5;
    
    int trackX=-1,trackY=-1; // last seen position of mouse
    
    boolean isSelectionPane=false; // false=is for editing; true=is for viewing and selecting only
    int selBoxW=0,selBoxH=0; // size to this, for selection panes
    
    MolSelectListener selectListen=null;
        
    int tool=0;
    int toolDragReason=0;
    double toolDragX1,toolDragY1,toolDragX2,toolDragY2;
    String toolAtomType=null;
    boolean toolAtomDrag,toolAtomSnap;
    int toolAtomEditSel=0,toolAtomEditX,toolAtomEditY;
    JTextField toolAtomEditBox=null;

    int toolBondOrder=0,toolBondType=0,toolBondFrom=0,toolBondHit=0;
    double toolBondFromX=0,toolBondFromY=0,toolBondToX=0,toolBondToY=0;
    boolean toolSnap,toolBondDrag=false;
    
    int toolCharge=0;
    
    static final int UNDO_LEVELS=10;
    class EditState{
    	Molecule Molecule;
	boolean Selected[];
    };
    EditState[] undo=null,redo=null;
    
    Molecule template=null,templDraw=null;
    int templateIdx=0;
    
    Molecule lastCleanMol=null;
    boolean lastDirty=false;

    // ------------------ public functions --------------------

    // Constructor for fully-fledged interactive editing panes.
    public EditorPane() {Init();}

    // Constructor for "selection only" editor panes.
    public EditorPane(int width,int height) 
    {
    	isSelectionPane=true; 
	selBoxW=width;
	selBoxH=height;
	Init();
    }
    
    void Init()
    {
    	mol=new Molecule();
    	DetermineSize();
	addMouseListener(this);
	addMouseMotionListener(this);
	addMouseWheelListener(this);
	addComponentListener(this);
	if(MainApplet.user_selection){// jm.evers
	    atomselection=new boolean[mol.NumAtoms()+32];
	    bondselection=new boolean[mol.NumBonds()+32];
	}
    }
    
    // obtain underlying molecule; not a copy, careful about modifying
    public Molecule MolData() {return mol;}
    
    public boolean IsEmpty() {return mol.NumAtoms()==0;}
    
    // unit operation equivalent to deleting all atoms
    public void Clear()
    {
    	CacheUndo();
	if(MainApplet.user_selection){
	    atomselection = new boolean[256];
	    bondselection = new boolean[256];
	}
    	mol=new Molecule();
	ClearTemporary();
	DetermineSize();
	repaint();
	CheckDirtiness();
    }

    // override the underlying molecule
    public void Replace(Molecule Mol) {Replace(Mol,false,true);}
    public void Replace(Molecule Mol,boolean ClearSelection) {Replace(Mol,ClearSelection,true);}
    public void Replace(Molecule Mol,boolean ClearSelection,boolean Repaint) 
    {
    	if (mol.NumAtoms()!=Mol.NumAtoms()) ClearSelection=true;
    	mol=Mol;
	ClearTemporary(ClearSelection);
	if (Repaint) repaint();
    }
    
    // set which object, if any, gets a response when an atom is "selected" with a mouse click
    public void SetMolSelectListener(MolSelectListener listen) {selectListen=listen;}
    
    // by default the editor pane captures lots of events and allows much editor; this function can be used to turn it off
    public void SetEditable(boolean Editable) {editable=Editable;}
    
    // if true, will draw a border around the edge
    public void SetBorder(boolean HasBorder) {hasBorder=HasBorder;}

    // if true, every time the size changes, the molecule will scale-to-fit    
    public void SetAutoScale(boolean AutoScale) {autoScale=AutoScale;}

    // informs the editor that the current state has been synchronised with what is in a disk file, or something equivalent
    public void NotifySaved(){
    	lastCleanMol=mol.Clone();
	lastDirty=false;
	if (selectListen!=null) selectListen.DirtyChanged(false);
    }
    
    // dirty==true when there have been some changes since the last modification
    public boolean IsDirty() {return lastDirty;}
    
    // checks to see whether the current molecule is the same as the last saved state; notifies if different; note that this is done by
    // an actual molecule comparison, which makes tracking changes a lot simpler, and also a {do something/restore it somehow} sequence
    // is functionally equivalent to undo, which is nice
    void CheckDirtiness(){
    	boolean nowDirty=mol.CompareTo(lastCleanMol)!=0;
	
    	if (nowDirty!=lastDirty)
	{
	    if (selectListen!=null) selectListen.DirtyChanged(nowDirty);
	    lastDirty=nowDirty;
	}
    }
        
    // affect the way the molecule is rendered
    public void SetShowMode(int ShowMode){
    	if (showMode==ShowMode) return;
	showMode=ShowMode;
	repaint();
    }
    public void SetShowHydrogens(boolean ShowHydr)
    {
    	if (showHydr==ShowHydr) return;
	showHydr=ShowHydr;
	repaint();
    }
    public void SetShowStereolabels(boolean ShowSter)
    {
    	if (showSter==ShowSter) return;
	showSter=ShowSter;
	repaint();
    }
    
    // notify selection of various tools
    public void SetToolCursor() 
    {
    	tool=TOOL_CURSOR; 
	repaint();
    }
    public void SetToolRotator()
    {
    	tool=TOOL_ROTATOR;
	repaint();
    }
    public void SetToolErasor() 
    {
    	tool=TOOL_ERASOR; 
	repaint();
    }
    public void SetToolAtom(String Atom) 
    {
    	tool=TOOL_ATOM;
	toolAtomType=Atom;
    	toolAtomDrag=false;
	toolAtomSnap=false;
    	toolBondFrom=0;
    	toolBondToX=0;
	toolBondToY=0;
	repaint();
    }
    public void SetToolBond(int Order)
    {
    	tool=TOOL_BOND;
	toolBondFrom=0;
	if (Order>=0) {toolBondOrder=Order; toolBondType=Molecule.BONDTYPE_NORMAL;}
	else 
	{
	    toolBondOrder=1;
	    if (Order==-1) toolBondType=Molecule.BONDTYPE_INCLINED;
	    else if (Order==-2) toolBondType=Molecule.BONDTYPE_DECLINED;
	    else if (Order==-3) toolBondType=Molecule.BONDTYPE_UNKNOWN;
	}
	repaint();
    }
    public void SetToolCharge(int DChg)
    {
    	tool=TOOL_CHARGE;
	toolCharge=DChg;
    }
    public void SetToolTemplate(Molecule Templ,int Idx)
    {
    	tool=TOOL_TEMPLATE;
    	template=Templ;
    	templateIdx=Idx;
	repaint();
    }
    
    // whether or not there is anything in the undo/redo stacks
    public boolean CanUndo() {return undo!=null && undo[0]!=null;}
    public boolean CanRedo() {return redo!=null && redo[0]!=null;}
    
    // cause the actual undo/redo to happen
    public void Undo()
    {
    	if (!CanUndo()) return;
	
	if (redo==null) redo=new EditState[UNDO_LEVELS];
	for (int n=UNDO_LEVELS-1;n>0;n--) redo[n]=redo[n-1];
    	redo[0]=new EditState();
	redo[0].Molecule=mol;
	redo[0].Selected=selected;
	
	mol=undo[0].Molecule;
	selected=undo[0].Selected;
	for (int n=0;n<UNDO_LEVELS-1;n++) undo[n]=undo[n+1];
	ClearTemporary(false);
	DetermineSize();
	repaint();
	
	CheckDirtiness();
    }
    public void Redo()
    {
    	if (!CanRedo()) return;
	
	if (undo==null) undo=new EditState[UNDO_LEVELS];
	for (int n=UNDO_LEVELS-1;n>0;n--) undo[n]=undo[n-1];
	undo[0]=new EditState();
	undo[0].Molecule=mol;
	undo[0].Selected=selected;
	
	mol=redo[0].Molecule;
	selected=redo[0].Selected;
	for (int n=0;n<UNDO_LEVELS-1;n++) redo[n]=redo[n+1];
	
	ClearTemporary(false);
	DetermineSize();
	repaint();
	
	CheckDirtiness();
    }
    
    // fits the molecule on the screen and centres everything; very pleasant thing to have at certain junctures, but not too often
    public void ScaleToFit() {ScaleToFit(20);}
    public void ScaleToFit(double MaxScale)
    {
	ClearTemporary();

    	double mw=2+mol.RangeX(),mh=2+mol.RangeY();
	Rectangle vis=getVisibleRect();
	if (vis.getWidth()==0 || vis.getHeight()==0) vis=new Rectangle(0,0,getWidth(),getHeight());
	double sw=selBoxW>vis.getWidth() ? selBoxW : vis.getWidth();
	double sh=selBoxH>vis.getHeight() ? selBoxH : vis.getHeight();
    	scale=Math.min(Math.min(sw/mw,sh/mh),MaxScale);
	offsetX=0.5*(sw/scale-mol.RangeX())-mol.MinX();
	offsetY=0.5*(sh/scale-mol.RangeY())+mol.MaxY();
    }

    // change the magnification, and adjust scrollbars etc accordingly
    public void ZoomFull() 
    {
    	ScaleToFit();
    	DetermineSize();
    	repaint();
    }
    public void ZoomIn(double Mag)
    {
    	scale*=Mag;
    	DetermineSize();
    	repaint();
    }
    public void ZoomOut(double Mag)
    {
    	scale/=Mag;
    	DetermineSize();
    	repaint();
    }
    
    // select all atoms
    public void SelectAll()
    {
    	selected=new boolean[mol.NumAtoms()];
	for (int n=0;n<mol.NumAtoms();n++) selected[n]=true;
    	repaint();
    }

    //jm.evers
    public void DeSelectAll(){
    	atomselection=new boolean[mol.NumAtoms()+32];
    	bondselection=new boolean[mol.NumBonds()+32];
    	repaint();
    }
    //jm.evers 4/3/2010
    public void Select(){
	tool = TOOL_SELECT;
    }
    
    // finds a nice place to put the new fragment which does not overlap existing content, then appends the atoms & bonds; note that
    // ownership of Frag is assumed
    public void AddArbitraryFragment(Molecule Frag)
    {
    	if (Frag.NumAtoms()==0) return;
    
    	CacheUndo();
    	if (mol.NumAtoms()==0) 
	{
	    mol=Frag;
	    ClearTemporary();
	    ScaleToFit();
	    DetermineSize();
	    repaint();
	    CheckDirtiness();
	    return;
	}
    
    	final double dirX[]={1,0,-1,1,-1,1,0,-1},dirY[]={1,1,1,0,0,-1,-1,-1};
    	double dx[]=new double[8],dy[]=new double[8],score[]=new double[8];
	
	for (int n=0;n<8;n++)
	{
	    double vx=dirX[n],vy=dirY[n];

	    if (n==0 || n==3 || n==5) {dx[n]=mol.MinX()-Frag.MaxX();}
	    else if (n==2 || n==4 || n==7) {dx[n]=mol.MaxX()-Frag.MinX();}
	    else dx[n]=0.5*(mol.MinX()+mol.MaxX()-Frag.MinX()-Frag.MaxX());
	    
	    if (n==5 || n==6 || n==7) {dy[n]=mol.MinY()-Frag.MaxY();}
	    else if (n==0 || n==1 || n==2) {dy[n]=mol.MaxY()-Frag.MinY();}
	    else dy[n]=0.5*(mol.MinY()+mol.MaxY()-Frag.MinY()-Frag.MaxY());
	    
	    dx[n]-=vx;
	    dy[n]-=vy;
	    score[n]=FragPosScore(Frag,dx[n],dy[n]);
	    
	    vx*=0.25;
	    vy*=0.25;
	    for (int iter=100;iter>0;iter--)
	    {
	    	double iscore=FragPosScore(Frag,dx[n]+vx,dy[n]+vy);
		if (iscore<=score[n]) break;
		score[n]=iscore;
		dx[n]+=vx;
		dy[n]+=vy;
	    }
	    for (int iter=100;iter>0;iter--) for (int d=0;d<8;d++)
	    {
	    	vx=dirX[d]*0.1;
		vy=dirY[d]*0.1;
	    	double iscore=FragPosScore(Frag,dx[n]+vx,dy[n]+vy);
		if (iscore<=score[n]) break;
		score[n]=iscore;
		dx[n]+=vx;
		dy[n]+=vy;
	    }
	}
	
	int best=0;
	for (int n=1;n<8;n++) if (score[n]>score[best]) best=n;
	
	for (int n=1;n<=Frag.NumAtoms();n++) Frag.SetAtomPos(n,Frag.AtomX(n)+dx[best],Frag.AtomY(n)+dy[best]);
	int base=mol.NumAtoms();
	mol.Append(Frag);
	
    	ClearTemporary();
	ScaleToFit();
	DetermineSize();
	
	selected=new boolean[mol.NumAtoms()];
	for (int n=0;n<mol.NumAtoms();n++) selected[n]=n>=base;
	
	repaint();
	CheckDirtiness();
    }
    
    // scoring function for above: more congested is better, but any two atoms < 1A = zero; post-biased to favour square aspect ratio
    double FragPosScore(Molecule Frag,double DX,double DY)
    {
    	double score=0;
    	for (int i=1;i<=mol.NumAtoms();i++)
	for (int j=1;j<=Frag.NumAtoms();j++)
	{
	    double dx=Frag.AtomX(j)+DX-mol.AtomX(i),dy=Frag.AtomY(j)+DY-mol.AtomY(i);
	    double dist2=dx*dx+dy*dy;
	    if (dist2<1) return 0;
	    score+=1/dist2;
	}
	double minX=Math.min(Frag.MinX()+DX,mol.MinX()),maxX=Math.max(Frag.MaxX()+DX,mol.MaxX());
	double minY=Math.min(Frag.MinY()+DY,mol.MinY()),maxY=Math.max(Frag.MaxY()+DY,mol.MaxY());
	double rangeX=Math.max(1,maxX-minX),rangeY=Math.max(1,maxY-minY);
	double ratio=Math.max(rangeX/rangeY,rangeY/rangeX);
	return score/ratio;
    }
    
    // returns the # of atoms in selection set
    public int CountSelected()
    {
    	if (selected==null) return 0;
	int num=0;
	for (int n=0;n<mol.NumAtoms();n++) if (selected[n]) num++;
	return num;
    }
    
    // returns array of atoms which are presently selected, or everything if none
    public ArrayList<Integer> SelectedIndices()
    {
    	ArrayList<Integer> selidx=new ArrayList<Integer>();
    	if (selected!=null) for (int n=0;n<mol.NumAtoms();n++) if (selected[n]) selidx.add(n+1);
	if (selidx.size()==0) for (int n=1;n<=mol.NumAtoms();n++) selidx.add(n);
	return selidx;
    }
    
    // returns a subgraph of the molecule corresponding to selected atoms - or if none, the whole thing
    public Molecule SelectedSubgraph()
    {
    	if (selected==null) return mol.Clone();
	int sum=0;
	for (int n=0;n<mol.NumAtoms();n++) if (selected[n]) sum++;
	if (sum==0) return mol.Clone();

	return mol.Subgraph(selected);
    }
    
    // deletes selected atoms, or all atoms if none selected
    public void DeleteSelected()
    {
    	CacheUndo();

    	boolean anySelected=false;
	if (selected!=null) for (int n=0;n<mol.NumAtoms();n++) if (selected[n]) {anySelected=true; break;}
	if (!anySelected) return;

	for (int n=mol.NumAtoms()-1;n>=0;n--) if (selected[n]) mol.DeleteAtomAndBonds(n+1);

    	ClearTemporary();
	// jm.evers 
	if(MainApplet.user_selection){
	    bondselection = new boolean[mol.NumBonds()+256];
	    atomselection = new boolean[mol.NumAtoms()+256];
	}
	//ScaleToFit();
	DetermineSize();
	repaint();
	CheckDirtiness();
    }
    
    // switch between explicit/implicit modes; going to explicit marks current calculated value as absolute
    public void HydrogenSetExplicit(boolean IsExpl) {HydrogenSetExplicit(IsExpl,Molecule.HEXPLICIT_UNKNOWN);}
    public void HydrogenSetExplicit(boolean IsExpl,int NumExpl)
    {
	CacheUndo();

    	ArrayList<Integer> sel=SelectedIndices();
	for (int n=0;n<sel.size();n++) 
	{
	    int i=sel.get(n).intValue();
	    if (IsExpl) mol.SetAtomHExplicit(i,mol.AtomHydrogens(i)); else mol.SetAtomHExplicit(i,NumExpl);
	}
	repaint();

	CheckDirtiness();
    }
    
    // any hydrogens which are implicit or explicit are actually created as nodes in the molecular graph; the explicit value of each
    // parent is set to unknown
    public void HydrogenCreateActual()
    {
	CacheUndo();

    	ArrayList<Integer> sel=SelectedIndices();
	int score[]=new int[360];
	for (int n=0;n<sel.size();n++)
	{
	    int i=sel.get(n).intValue();
	    int hy=mol.AtomHydrogens(i);
	    if (hy==0) continue;
	    
	    for (int j=0;j<360;j++) score[j]=0;
	    int adj[]=mol.AtomAdjList(i);
	    for (int j=0;j<adj.length;j++) 
	    {
	    	int iang=(int)(Math.atan2(mol.AtomY(adj[j])-mol.AtomY(i),mol.AtomX(adj[j])-mol.AtomX(i))*180/Math.PI);
		if (iang<0) iang+=360;
		score[iang]=-1; score[(iang+1)%360]=-1; score[(iang+359)%360]=-1;
		int i0=(iang+180)%360,i1=(iang+120)%360,i2=(iang+240)%360;
		if (score[i0]>=0) score[i0]+=2;
		if (score[i1]>=0) score[i1]+=4;
		if (score[i2]>=0) score[i2]+=4;
	    }
	    
	    while (hy>0)
	    {
	    	int iang=0;
		for (int j=1;j<360;j++) if (score[j]>score[iang]) iang=j;
		int num=mol.AddAtom("H",mol.AtomX(i)+Math.cos(iang*Math.PI/180.0),mol.AtomY(i)+Math.sin(iang*Math.PI/180.0));
		mol.AddBond(i,num,1);
		score[iang]=-1; score[(iang+1)%360]=-1; score[(iang+359)%360]=-1;
		int i0=(iang+180)%360,i1=(iang+120)%360,i2=(iang+240)%360;
		if (score[i0]>=0) score[i0]++;
		if (score[i1]>=0) score[i1]+=2;
		if (score[i2]>=0) score[i2]+=2;
	    	hy--;
	    }
	    
	    mol.SetAtomHExplicit(i,Molecule.HEXPLICIT_UNKNOWN);
	}
    
    	ClearTemporary();
	DetermineSize();
	repaint();

	CheckDirtiness();
    }
    
    // of all the selected atoms and their neighbours, removes any which are element H
    public void HydrogenDeleteActual()
    {
    	ArrayList<Integer> sel=SelectedIndices(),chop=new ArrayList<Integer>();
	for (int n=0;n<sel.size();n++)
	{
	    int i=sel.get(n).intValue();
	    if (mol.AtomElement(i).compareTo("H")==0) chop.add(new Integer(i));
	    int adj[]=mol.AtomAdjList(i);
	    for (int j=0;j<adj.length;j++) if (mol.AtomElement(adj[j]).compareTo("H")==0) chop.add(adj[j]);
	}
	
	if (chop.size()==0) return;
	CacheUndo();
	Collections.sort(chop);
	
	for (int n=0;n<chop.size();n++)
	{
	    int adj[]=mol.AtomAdjList(chop.get(n).intValue());
	    for (int i=0;i<adj.length;i++) mol.SetAtomHExplicit(adj[i],Molecule.HEXPLICIT_UNKNOWN);
	}

	int decr=0,lastVal=-1;
	for (int n=0;n<chop.size();n++)
	{
	    int i=chop.get(n).intValue();
	    if (i==lastVal) continue;
	    mol.DeleteAtomAndBonds(i-decr);
	    decr++;
	    lastVal=i;
	}
    
    	ClearTemporary();
	DetermineSize();
	repaint();

	CheckDirtiness();
    }
    
    // scale bond lengths to reasonable values (note: affects all atoms, selected or not)
    public void NormaliseBondLengths()
    {
    	double numer=0,denom=0;
	for (int n=1;n<=mol.NumBonds();n++)
	{
	    double dx=mol.AtomX(mol.BondFrom(n))-mol.AtomX(mol.BondTo(n)),dy=mol.AtomY(mol.BondFrom(n))-mol.AtomY(mol.BondTo(n));
	    double weight=mol.BondInRing(n) ? 1 : 2;
	    numer+=Math.sqrt(dx*dx+dy*dy)*weight;
	    denom+=weight;
	}
	if (denom==0) return;
	
	CacheUndo();
    	
	double stretch=IDEALBOND*denom/numer;
    	for (int n=1;n<=mol.NumAtoms();n++)
	{
	    mol.SetAtomPos(n,mol.AtomX(n)*stretch,mol.AtomY(n)*stretch);
	}

	
	ClearTemporary();
	DetermineSize();
	repaint();
    }
    
    // select next/prev atoms or connected components
    public void CycleSelection(boolean Forward,boolean Group)
    {
    	if (mol.NumAtoms()<=1) return;
	
    	int high=0;
	if (selected!=null) for (int n=1;n<=mol.NumAtoms();n++) if (selected[n-1])
	{
	    if (Group) {if (mol.AtomConnComp(n)>high) high=mol.AtomConnComp(n);}
	    else {high=n;}
	}
	int max=Group ? 0 : mol.NumAtoms();
	if (Group) for (int n=1;n<=mol.NumAtoms();n++) if (mol.AtomConnComp(n)>max) max=mol.AtomConnComp(n);
	
	int pos=Forward ? high+1 : high-1;
	if (pos<1) pos=max;
	if (pos>max) pos=1;
	
	selected=new boolean[mol.NumAtoms()];
	for (int n=1;n<=mol.NumAtoms();n++)
	{
	    if (Group) {selected[n-1]=mol.AtomConnComp(n)==pos;}
	    else {selected[n-1]=n==pos;}
	}
	
	ClearTemporary(false);
	repaint();
    }
    
    // move selected atoms by a small translation
    public void NudgeSelectedAtoms(double DX,double DY)
    {
    	if (selected==null) return;
    	CacheUndo();	
	for (int n=1;n<=mol.NumAtoms();n++) if (selected[n-1]) mol.SetAtomPos(n,mol.AtomX(n)+DX,mol.AtomY(n)+DY);

	ClearTemporary(false);
	DetermineSize();
	repaint();
    }
    
    // selected atoms are inverted about a mirror plane coincident with their centre of gravity
    public void FlipSelectedAtoms(boolean Vertical)
    {
    	if (selected==null) return;
	
	int count=0;
	double cx=0,cy=0;
	for (int n=1;n<=mol.NumAtoms();n++) if (selected[n-1]) {cx+=mol.AtomX(n); cy+=mol.AtomY(n); count++;}
	if (count==0) return;
	
    	CacheUndo();	

	cx/=count;
	cy/=count;
	for (int n=1;n<=mol.NumAtoms();n++) if (selected[n-1]) 
	{
	    if (Vertical) mol.SetAtomPos(n,mol.AtomX(n),2*cy-mol.AtomY(n));
	    else mol.SetAtomPos(n,2*cx-mol.AtomX(n),mol.AtomY(n));
	}
	
	ClearTemporary(false);
	DetermineSize();
	repaint();
    }
    
    // selected atoms are rotated about their centre of gravity
    public void RotateSelectedAtoms(double Degrees)
    {
    	if (selected==null) return;
	
	int count=0;
	double cx=0,cy=0;
	for (int n=1;n<=mol.NumAtoms();n++) if (selected[n-1]) {cx+=mol.AtomX(n); cy+=mol.AtomY(n); count++;}
	if (count==0) return;
	
    	CacheUndo();	

	cx/=count;
	cy/=count;
    	double radians=Degrees*Math.PI/180;
	for (int n=1;n<=mol.NumAtoms();n++) if (selected[n-1]) 
	{
	    double dx=mol.AtomX(n)-cx,dy=mol.AtomY(n)-cy;
	    double dist=Math.sqrt(dx*dx+dy*dy),theta=Math.atan2(dy,dx);
	    mol.SetAtomPos(n,cx+dist*Math.cos(theta+radians),cy+dist*Math.sin(theta+radians));
	}

	ClearTemporary(false);
	DetermineSize();
	repaint();
    }
    
    // changes stereochemistry; STEREO_UNKNOWN=invert, POS/NEG=set to this
    public void SetStereo(int Operation)
    {
    	ArrayList<Integer> selidx=SelectedIndices();

    	int[][] graph=new int[mol.NumAtoms()][];
	for (int n=0;n<mol.NumAtoms();n++) graph[n]=mol.AtomAdjList(n+1);

	CacheUndo();

    	// chiral centres
	for (int n=0;n<selidx.size();n++) 
	{
	    int a=selidx.get(n);
	    int ster=mol.AtomChirality(a);
	    if (Operation==Molecule.STEREO_UNKNOWN)
	    	{if (ster!=Molecule.STEREO_POS && ster!=Molecule.STEREO_NEG) continue;}
	    else 
	    	{if (ster==Operation) continue;}

    	    // first the easy option: the atom already has chirality, can just flip all the wedges...
	    if (ster==Molecule.STEREO_POS || ster==Molecule.STEREO_NEG)
	    {
	    	for (int i=1;i<=mol.NumBonds();i++) 
		    if (mol.BondFrom(i)==a)
		{
		    if (mol.BondType(i)==Molecule.BONDTYPE_INCLINED) mol.SetBondType(i,Molecule.BONDTYPE_DECLINED);
		    else if (mol.BondType(i)==Molecule.BONDTYPE_DECLINED) mol.SetBondType(i,Molecule.BONDTYPE_INCLINED);
    	    	}
	    	continue;
	    }
	    
	    // not quite so easy: centre has no current chirality, and a specific enantiomer has been requested
	    ArrayList<int[]> perm=WedgeFormations(a,Operation);
	    if (perm!=null && perm.size()>0) // if anything available, use best...
	    {
	    	int[] adj=mol.AtomAdjList(a);
    	    	for (int i=0;i<adj.length;i++)
		{
		    int j=mol.FindBond(a,adj[i]); if (j==0) continue;
		    mol.SetBondType(j,perm.get(0)[i]<0 ? Molecule.BONDTYPE_DECLINED 
		                    : perm.get(0)[i]>0 ? Molecule.BONDTYPE_INCLINED : Molecule.BONDTYPE_NORMAL);
    	    	    if (mol.BondFrom(j)!=a) mol.SetBondFromTo(j,mol.BondTo(j),mol.BondFrom(j));
		}
	    }
	}
		
	// cis/trans 
	for (int n=1;n<=mol.NumBonds();n++) 
	{
	    int bf=mol.BondFrom(n),bt=mol.BondTo(n);
	    if (mol.BondOrder(n)==2 && selidx.indexOf(bf)<0 && selidx.indexOf(bt)<0) continue;
	    int ster=mol.BondStereo(n);
	    if ((ster!=Molecule.STEREO_POS && ster!=Molecule.STEREO_NEG) || ster==Operation) continue;
	    if (mol.AtomRingBlock(bf)!=0 && mol.AtomRingBlock(bf)!=mol.AtomRingBlock(bt)) continue; // refuse to work with ring alkene
	    
	    // classify the sides of the X=Y bond by partitioning the component
	    int sc1=1,sc2=1,side[]=new int[mol.NumAtoms()];
	    for (int i=0;i<mol.NumAtoms();i++) side[i]=0;
	    side[bf-1]=1; side[bt-1]=2;
	    while (true)
	    {
	    	boolean changed=false;
		for (int i=0;i<mol.NumAtoms();i++) if (side[i]==0)
		    for (int j=0;j<graph[i].length;j++) if (side[graph[i][j]-1]!=0) 
		{
		    side[i]=side[graph[i][j]-1];
		    if (side[i]==1) sc1++; else sc2++;
		    changed=true;
		}
		if (!changed) break;
	    }
	    int which=sc1<=sc2 ? 1 : 2;
	    double cx=mol.AtomX(which==1 ? bf : bt),cy=mol.AtomY(which==1 ? bf : bt);
	    double axis=Math.atan2(cy-mol.AtomY(which==1 ? bt : bf),cx-mol.AtomX(which==1 ? bt : bf));
	    for (int i=0;i<mol.NumAtoms();i++) if (side[i]==which)
	    {
	    	double dx=mol.AtomX(i+1)-cx,dy=mol.AtomY(i+1)-cy;
	    	double r=Math.sqrt(dx*dx+dy*dy),th=Math.atan2(dy,dx);
		th=2*axis-th;
		mol.SetAtomPos(i+1,cx+r*Math.cos(th),cy+r*Math.sin(th));
	    }
	    for (int i=1;i<=mol.NumBonds();i++) 
	    	if (mol.BondType(i)==Molecule.BONDTYPE_INCLINED || mol.BondType(i)==Molecule.BONDTYPE_DECLINED)
	    	    if (side[mol.BondFrom(i)-1]==which && side[mol.BondTo(i)-1]==which)
	    	    	mol.SetBondType(i,mol.BondType(i)==Molecule.BONDTYPE_INCLINED ? Molecule.BONDTYPE_DECLINED 
			    	    	    	    	    	    	    	      : Molecule.BONDTYPE_INCLINED);
	}

    	ClearTemporary(false);
    	DetermineSize();
    	repaint();
    }
    
    // selected chiral centres lose their wedge bonds
    public void RemoveChiralWedges()
    {
    	CacheUndo();
    
    	ArrayList<Integer> selidx=SelectedIndices();
	for (int n=0;n<selidx.size();n++) if (mol.AtomChirality(selidx.get(n))!=Molecule.STEREO_NONE)
	{
	    for (int i=1;i<=mol.NumBonds();i++) 
		if ((mol.BondFrom(i)==selidx.get(n) || mol.BondTo(i)==selidx.get(n)) && 
		    (mol.BondType(i)==Molecule.BONDTYPE_INCLINED || mol.BondType(i)==Molecule.BONDTYPE_DECLINED))
		mol.SetBondType(i,Molecule.BONDTYPE_NORMAL);
	}
	repaint();
    }

    // for any chiral centres, pick the next set of valid wedge bonds
    public void CycleChiralWedges()
    {
    	CacheUndo();
    
    	ArrayList<Integer> selidx=SelectedIndices();
	for (int n=0;n<selidx.size();n++)
	{
	    int a=selidx.get(n),chi=mol.AtomChirality(a);
	    if (chi!=Molecule.STEREO_POS && chi!=Molecule.STEREO_NEG) continue;
	    ArrayList<int[]> perm=WedgeFormations(a,chi);
    	    if (perm.size()<=1) continue; // invalid or no point
	    
	    int[] adj=mol.AtomAdjList(a),curperm=new int[adj.length];
	    for (int i=0;i<adj.length;i++)
	    {
	    	int j=mol.FindBond(a,adj[i]);
		curperm[i]=mol.BondType(j)==Molecule.BONDTYPE_INCLINED ? 1 : mol.BondType(j)==Molecule.BONDTYPE_DECLINED ? -1 : 0;
	    }
	    int match=-1;
	    for (int i=0;i<perm.size();i++)
	    {
	    	int[] thisperm=perm.get(i);
		boolean same=true;
		for (int j=0;j<curperm.length;j++) if (thisperm[j]!=curperm[j]) {same=false; break;}
		if (same) {match=i; break;}
	    }
	    match=(match+1)%perm.size();
	    curperm=perm.get(match);

	    for (int i=0;i<adj.length;i++)
	    {
	    	int j=mol.FindBond(a,adj[i]);
		if (mol.BondFrom(j)!=a) mol.SetBondFromTo(j,a,adj[i]);
		mol.SetBondType(j,curperm[i]<0 ? Molecule.BONDTYPE_DECLINED 
		    	        : curperm[i]>0 ? Molecule.BONDTYPE_INCLINED : Molecule.BONDTYPE_NORMAL);
	    }
	}
	repaint();
    }
    
    // ------------------ private functions --------------------

    // translation of screen & molecule coordinates    
    double AngToX(double AX) {return (offsetX+AX)*scale;}
    double AngToY(double AY) {return (offsetY-AY)*scale;}
    double XToAng(double PX) {return (PX/scale)-offsetX;}
    double YToAng(double PY) {return (-PY/scale)+offsetY;}

    // resizes the widget, which is assumed scrollable, to fit the current magnification of the whole molecule
    void DetermineSize()
    {
    	int w,h;
    	if (!isSelectionPane)
	{
	    w=Math.max((int)AngToX(mol.MaxX()+1),500);
	    h=Math.max((int)AngToY(mol.MinY()-1),500);
	}
	else
	{
    	    w=selBoxW;
	    h=selBoxH;
	}
    	setPreferredSize(new Dimension(w,h));
	setSize(w,h);
    }
    
    // erases some of the datastructures used for caching the drawing elements
    void ClearTemporary() {ClearTemporary(true);}
    void ClearTemporary(boolean AndSelected)
    {
    	px=py=rw=rh=null;
	highlightAtom=highlightBond=0;
	if (AndSelected) selected=null; 
	else if (selected!=null && selected.length!=mol.NumAtoms())
	{
	    boolean newSelected[]=new boolean[mol.NumAtoms()];
	    for (int n=0;n<selected.length;n++) newSelected[n]=selected[n];
	    selected=newSelected;
	}
    }
    
    void ResetSelected(boolean Clear)
    {
    	if (selected==null) selected=new boolean[mol.NumAtoms()];
	if (Clear) for (int n=0;n<mol.NumAtoms();n++) selected[n]=false;
    }
    
    // return the atom underneath the given position, in screen coordinates; assumes that the appropriate arrays of size and position
    // have been filled out
    int PickAtom(int X,int Y)
    {
    	if (px==null || py==null) return 0; //DefinePositions()...?;
	
    	for (int n=1;n<=mol.NumAtoms();n++) 
	{
	    double dx=X-px[n-1],dy=Y-py[n-1];
	    if (Math.abs(dx)<=rw[n-1] && Math.abs(dy)<=rh[n-1])
	    	if (dx*dx/(rw[n-1]*rw[n-1])+dy*dy/(rh[n-1]*rh[n-1])<=1) {return n;}
	}
	return 0;
    }
    
    // returns the bond underneath the screen position
    int PickBond(int X,int Y)
    {
    	if (px==null || py==null) return 0;
    
    	for (int n=1;n<=mol.NumBonds();n++)
	{
	    double x1=px[mol.BondFrom(n)-1],y1=py[mol.BondFrom(n)-1],x2=px[mol.BondTo(n)-1],y2=py[mol.BondTo(n)-1];

	    double nx1=x1,ny1=y1,nx2=x2,ny2=y2;
	    int delta=Math.max(2,(int)(scale/20));
	    if (nx1>nx2) {nx1=x2; nx2=x1;}
	    if (ny1>ny2) {ny1=y2; ny2=y1;}
	    if (X<nx1-2*delta || X>nx2+2*delta || Y<ny1-2*delta || Y>ny2+2*delta) continue;

	    double dx=x2-x1,dy=y2-y1,d;
	    if (Math.abs(dx)>Math.abs(dy)) d=Y-y1-(X-x1)*dy/dx; else d=X-x1-(Y-y1)*dx/dy;
	    if (Math.abs(d)>(2+mol.BondOrder(n))*delta) continue;
	    return n;
	}
	return 0;
    }
    
    // snaps the draw-to-position to multiples of 30 degrees
    void SnapToolBond()
    {
    	double cx=toolBondFrom>0 ? mol.AtomX(toolBondFrom) : toolBondFromX;
	double cy=toolBondFrom>0 ? mol.AtomY(toolBondFrom) : toolBondFromY;
	double dx=toolBondToX-cx,dy=toolBondToY-cy;
    	double th=Math.atan2(dy,dx)*180/Math.PI,ext=Math.sqrt(dx*dx+dy*dy);
	th=(Math.round(th/30)*30)*Math.PI/180;
	ext=Math.round(ext/IDEALBOND)*IDEALBOND;
	toolBondToX=cx+ext*Math.cos(th);
	toolBondToY=cy+ext*Math.sin(th);
    }
        
    // should be called before any unit operation is conducted; the current molecule state is stored in the undo buffer
    void CacheUndo()
    {
    	// !! check to see if the last molecule in the cache is literally identical, and if so, do nothing
    	if (undo==null) undo=new EditState[UNDO_LEVELS];
	redo=null;
	for (int n=UNDO_LEVELS-1;n>0;n--) undo[n]=undo[n-1];
	undo[0]=new EditState();
	undo[0].Molecule=mol==null ? null : mol.Clone();
	undo[0].Selected=selected==null ? null : selected.clone();
    }
    
    // called when the element editing widget has ended its lifecycle, and the change is to be applied
    void CompleteAtomEdit()
    {
    	if (toolAtomEditBox==null) return;
	String el=toolAtomEditBox.getText();
	if (el.length()>0)
	{
	    CacheUndo();

	    if (el.charAt(0)>='a' && el.charAt(0)<='z') el=el.substring(0,1).toUpperCase()+el.substring(1);

	    if (toolAtomEditSel==0)
	    {
		mol.AddAtom(el,XToAng(toolAtomEditX),YToAng(toolAtomEditY));
		ClearTemporary();
		DetermineSize();
	    }
	    else mol.SetAtomElement(toolAtomEditSel,el);
	}
	
	toolAtomEditBox.setVisible(false);
    	remove(toolAtomEditBox);
	toolAtomEditBox=null;
	
	repaint();
	CheckDirtiness();
    }
    
    // the currently active template is rotated according to a mapping between atoms
    void AdjustTemplateByAtom(int Atom)
    {
    	templDraw=template.Clone();
	
	ArrayList<Integer> bonded=new ArrayList<Integer>();
	for (int n=1;n<=mol.NumBonds();n++)
	{
	    if (mol.BondFrom(n)==Atom) bonded.add(new Integer(mol.BondTo(n)));
	    if (mol.BondTo(n)==Atom) bonded.add(new Integer(mol.BondFrom(n)));
	}
	
	final int INCR=1;
	double[] rotScores=new double[360/INCR];
	for (int n=1;n<=templDraw.NumAtoms();n++) if (n!=templateIdx)
	{
	    double x=template.AtomX(n)-template.AtomX(templateIdx),y=template.AtomY(n)-template.AtomY(templateIdx);
	    double th=Math.atan2(y,x),ext=Math.sqrt(x*x+y*y);
	    for (int i=0;i<(360/INCR);i++)
	    {
	    	double rx=mol.AtomX(Atom)+ext*Math.cos(th+i*INCR*Math.PI/180),ry=mol.AtomY(Atom)+ext*Math.sin(th+i*INCR*Math.PI/180);
		for (int j=0;j<bonded.size();j++)
		{
		    int k=bonded.get(j).intValue();
		    double dx=mol.AtomX(k)-rx,dy=mol.AtomY(k)-ry;
		    double ext2=dx*dx+dy*dy;
		    if (ext2<0.01) ext2=0.01;
		    rotScores[i]+=1/ext2;
		}
	    }
	}
	
	int bestRot=0;
	for (int n=1;n<(360/INCR);n++) if (rotScores[n]<rotScores[bestRot]) bestRot=n;
	
	for (int n=1;n<=templDraw.NumAtoms();n++)
	{
	    double x=template.AtomX(n)-template.AtomX(templateIdx),y=template.AtomY(n)-template.AtomY(templateIdx);
	    double th=Math.atan2(y,x),ext=Math.sqrt(x*x+y*y);
	    templDraw.SetAtomPos(n,mol.AtomX(Atom)+ext*Math.cos(th+bestRot*INCR*Math.PI/180),
	    	    	    	   mol.AtomY(Atom)+ext*Math.sin(th+bestRot*INCR*Math.PI/180));
	}
    }
    
    // the currently active template is rotated according to a mapping between bonds
    boolean AdjustTemplateByBond(int Bond)
    {
    	Molecule[] rotMol=new Molecule[2];
	double[] rotScores=new double[2];
	
	for (int r=0;r<2;r++)
	{
	    rotMol[r]=template.Clone();
	    int imol1=r==0 ? mol.BondFrom(Bond) : mol.BondTo(Bond),imol2=r==0 ? mol.BondTo(Bond) : mol.BondFrom(Bond);
	    int irot1=template.BondFrom(-templateIdx),irot2=template.BondTo(-templateIdx);
	    double dtheta=Math.atan2(mol.AtomY(imol2)-mol.AtomY(imol1),mol.AtomX(imol2)-mol.AtomX(imol1))
	    	    	 -Math.atan2(template.AtomY(irot2)-template.AtomY(irot1),template.AtomX(irot2)-template.AtomX(irot1));
	    
	    for (int n=1;n<=template.NumAtoms();n++)
	    {
	    	double rx=template.AtomX(n)-template.AtomX(irot1),ry=template.AtomY(n)-template.AtomY(irot1);
		double th=Math.atan2(ry,rx),ext=Math.sqrt(rx*rx+ry*ry);
		rx=mol.AtomX(imol1)+ext*Math.cos(th+dtheta);
		ry=mol.AtomY(imol1)+ext*Math.sin(th+dtheta);
		rotMol[r].SetAtomPos(n,rx,ry);
		
		for (int i=1;i<=mol.NumAtoms();i++)
		{
		    double dx=mol.AtomX(i)-rx,dy=mol.AtomY(i)-ry;
		    double ext2=dx*dx+dy*dy;
		    if (ext2<0.01) ext2=0.01;
		    rotScores[r]+=1/ext2;
		}
	    }
	}
	
	boolean swap=rotScores[0]<rotScores[1];
	templDraw=rotMol[swap ? 0 : 1];
	return swap;
    }
    
    // the currently active template is merely translated, as there is no current atom or bond mapping
    void AdjustTemplateByCoord(double X,double Y)
    {
    	templDraw=template.Clone();

    	double dx=0,dy=0;
	if (templateIdx>0) {dx=template.AtomX(templateIdx); dy=template.AtomY(templateIdx);}
	else if (templateIdx<0)
	{
	    int from=template.BondFrom(-templateIdx),to=template.BondTo(-templateIdx);
	    dx=0.5*(template.AtomX(from)+template.AtomX(to));
	    dy=0.5*(template.AtomY(from)+template.AtomY(to));
	}
    	for (int n=1;n<=template.NumAtoms();n++) templDraw.SetAtomPos(n,template.AtomX(n)-dx+X,template.AtomY(n)-dy+Y);
    }
    
    // places a template, where atoms are mapped
    void TemplateSetByAtom(int JoinAtom)
    {
    	int[] map=new int[templDraw.NumAtoms()];
	int oldNum=mol.NumAtoms();
    	for (int n=1;n<=templDraw.NumAtoms();n++) if (JoinAtom==0 || n!=templateIdx)
	{
	    mol.AddAtom(templDraw.AtomElement(n),templDraw.AtomX(n),templDraw.AtomY(n),
		    	templDraw.AtomCharge(n),templDraw.AtomUnpaired(n));
	}
	for (int n=1;n<=templDraw.NumBonds();n++)
	{
	    int from=templDraw.BondFrom(n);
	    int to=templDraw.BondTo(n);
	    if (JoinAtom>0)
	    {
		if (from==templateIdx) from=JoinAtom; 
		else 
		{
		    if (from>templateIdx) from--;
		    from+=oldNum;
		}
		if (to==templateIdx) to=JoinAtom; 
		else 
		{
		    if (to>templateIdx) to--;
		    to+=oldNum;
		}
	    }
	    else {from+=oldNum; to+=oldNum;}
	    mol.AddBond(from,to,templDraw.BondOrder(n),templDraw.BondType(n));
	}

    	MergeNewAtoms(oldNum);

	ClearTemporary();
	DetermineSize();
	repaint();
    }
    
    // places a template, where bonds are mapped
    void TemplateSetByBond(int JoinBond,boolean Swap)
    {
    	int[] map=new int[templDraw.NumAtoms()];
	int oldNum=mol.NumAtoms();
	int joinFrom=JoinBond>0 ? mol.BondFrom(JoinBond) : 0,joinTo=JoinBond>0 ? mol.BondTo(JoinBond) : 0;
	int newFrom=Swap ? templDraw.BondFrom(-templateIdx) : templDraw.BondTo(-templateIdx);
	int newTo=Swap ? templDraw.BondTo(-templateIdx) : templDraw.BondFrom(-templateIdx);	
	for (int n=1;n<=templDraw.NumAtoms();n++)
	{
	    if (n==newFrom && JoinBond>0) map[n-1]=joinFrom;
	    else if (n==newTo && JoinBond>0) map[n-1]=joinTo;
	    else 
	    {
	    	map[n-1]=mol.AddAtom(templDraw.AtomElement(n),templDraw.AtomX(n),templDraw.AtomY(n),
		    	    	     templDraw.AtomCharge(n),templDraw.AtomUnpaired(n));
	    }
	}
	for (int n=1;n<=template.NumBonds();n++) if (n!=-templateIdx || JoinBond==0)
	{
	    mol.AddBond(map[templDraw.BondFrom(n)-1],map[templDraw.BondTo(n)-1],templDraw.BondOrder(n),templDraw.BondType(n));
	}
	
	MergeNewAtoms(oldNum);
	
	ClearTemporary();
	DetermineSize();
	repaint();
    }
    
    // any atoms of index greater than the watermark are merged with previously defined atoms if they are close
    void MergeNewAtoms(int Watermark)
    {
    	int pos=Watermark+1;
	while (pos<=mol.NumAtoms())
	{
	    int close=0;
	    for (int n=1;n<=Watermark;n++) 
	    {
	    	double dx=mol.AtomX(n)-mol.AtomX(pos),dy=mol.AtomY(n)-mol.AtomY(pos);
		if (dx*dx+dy*dy<0.2*0.2) {close=n; break;}
	    }
    	    if (close>0)
	    {
	    	int[] adj=mol.AtomAdjList(pos);
	    	for (int i=0;i<adj.length;i++) if (mol.FindBond(close,adj[i])==0)
		{
		    int j=mol.FindBond(pos,adj[i]);
		    mol.AddBond(close,adj[i],mol.BondOrder(j));
		}
		mol.DeleteAtomAndBonds(pos);
	    }
	    else pos++;
	}
    }

    // returns true if there are any selected atoms
    boolean AnySelected()
    {
    	if (selected==null) return false;
	for (int n=0;n<mol.NumAtoms();n++) if (selected[n]) return true;
	return false;
    }

    double DragExtendBy(double px,double py)
    {
	double diff=0.2*Math.sqrt(px*px+py*py)/scale;
	if (px<0 && py<0) diff=-diff;
	
	if (diff>=0) return 1+diff;
	else return Math.exp(diff);
    }
    
    // calculate all the wedge bond formations for a given atom for a given chirality (+/-), ranked in order, null if none
    ArrayList<int[]> WedgeFormations(int N,int Chi)
    {
    	if (mol.AtomAdjCount(N)!=3 && mol.AtomAdjCount(N)!=4) return null;
    	int[] adj=mol.AtomAdjList(N);
	for (int i=0;i<adj.length-1;i++) for (int j=i+1;j<adj.length;j++) 
	    if (mol.AtomPriority(adj[i])==mol.AtomPriority(adj[j])) return null;

	int[] badj=new int[adj.length];
	for (int n=0;n<adj.length;n++) badj[n]=mol.FindBond(N,adj[n]);
	
	ArrayList<int[]> perm=new ArrayList<int[]>();

    	// generate all possible sensible wedge combinations
    	if (adj.length==3)
	{
	    for (int i=0;i<3;i++) for (int iz=-1;iz<=1;iz+=2)
	    {
	    	int[] wedges=new int[3];
		for (int n=0;n<3;n++) wedges[n]=0;
		wedges[i]=iz;
		perm.add(wedges);
	    }
	}
	else
	{
	    for (int i=0;i<4;i++) for (int iz=-1;iz<=1;iz+=2)
	    {
	    	int[] wedges=new int[4];
		for (int n=0;n<4;n++) wedges[n]=0;
		wedges[i]=iz;
		perm.add(wedges);
		
		for (int j=i+1;j<4;j++) for (int jz=-1;jz<=1;jz+=2)
		{
	    	    if (/*i==j || */jz==iz) continue;
	    	    wedges=new int[4];
		    for (int n=0;n<4;n++) wedges[n]=0;
		    wedges[i]=iz;
		    wedges[j]=jz;
		    perm.add(wedges);
		}
	    }
	}

	// keep only the ones which indicate the desired enantiomer
	int pos=0;
	while (pos<perm.size())
	{
	    int[] wedges=perm.get(pos);
	    Molecule mchi=mol.Clone();
	    for (int n=0;n<adj.length;n++) 
	    {
	    	mchi.SetBondType(badj[n],wedges[n]<0 ? Molecule.BONDTYPE_DECLINED 
		    	    	       : wedges[n]>0 ? Molecule.BONDTYPE_INCLINED : Molecule.BONDTYPE_NORMAL);
    	    	if (mchi.BondFrom(badj[n])!=N) mol.SetBondFromTo(badj[n],mol.BondTo(badj[n]),mol.BondFrom(badj[n]));

	    }
	    if (mchi.AtomChirality(N)!=Chi) perm.remove(pos); else pos++;
	}
	
	// score each one based on crude aesthetic criteria
	double[] score=new double[perm.size()];
	for (int n=0;n<perm.size();n++)
	{
	    score[n]=0;
	    int[] wedges=perm.get(n);
	    int wcount=0;
	    for (int i=0;i<adj.length;i++) if (wedges[i]!=0)
	    {
	    	wcount++;
		score[n]-=0.5*mol.AtomPriority(adj[i])/mol.NumAtoms();
	    	if (mol.AtomAdjCount(adj[i])==1) score[n]++;
		if (mol.AtomRingBlock(adj[i])>0) 
		{
		    score[n]--;
		    if (mol.AtomRingBlock(N)==mol.AtomRingBlock(adj[i])) score[n]--;
		}
	    }
	    if (adj.length==4 && wcount==2) score[n]++;
	}
	
	// sort best-first
	pos=0;
	while (pos<perm.size()-1)
	{
	    if (score[pos]<score[pos+1])
	    {
	    	int[] w1=perm.get(pos),w2=perm.get(pos+1);
		perm.set(pos+1,w1);
		perm.set(pos,w2);
		double s=score[pos]; score[pos]=score[pos+1]; score[pos+1]=s;
		if (pos>0) pos--;
	    } else pos++;
	}
	
	
	/*System.out.println("PERMSIZE:"+perm.size());
	for (int n=0;n<perm.size();n++)
	{
	    int[] w=perm.get(n);
	    System.out.print("n="+n);
    	    for (int i=0;i<w.length;i++) System.out.print(" "+w[i]);
	    System.out.println(" score="+score[n]);
	}*/

	return perm;
    }
    
    // ------------------ event functions --------------------
    
    // the paint function sets up the basic graphics drawing context, then performs some preliminary transformations of any tools effects
    // that are in progress, hands off all the work to DrawMolecule, then fetches back some of data determined in situ
    
    protected void paintComponent(Graphics gr) 
    {
    	if (autoScale) ScaleToFit();
	// this is the canvas background
	Color b=new Color(255,255,255);
    	gr.setColor(b);
//    	gr.setColor(Color.WHITE);
	gr.fillRect(0,0,getWidth(),getHeight());
    	if (hasBorder)
	{
	    gr.setColor(Color.BLACK);
	    gr.drawRect(0,0,getWidth()-1,getHeight()-1);
	}

    	Graphics2D g=(Graphics2D)gr;
    	g.setRenderingHint(RenderingHints.KEY_ANTIALIASING,RenderingHints.VALUE_ANTIALIAS_ON);
    	DrawMolecule draw=new DrawMolecule(mol,g);
	
	// provide a miscellany of editing data to the drawing class, so that it can represent everything that is going on
	// draw is for chemical/binding: 
	draw.SetBackground(getBackground());
	draw.SetShowHydr(showHydr);
	draw.SetShowMode(showMode);
	draw.SetShowStereo(showSter);
	draw.SetTransform(offsetX,offsetY,scale);
	draw.SetHighlight(highlightAtom,highlightBond);
    	ResetSelected(false);
	draw.SetSelected(selected,dragged);

	if ((tool==TOOL_ATOM && toolAtomDrag) || (tool==TOOL_BOND && toolBondFrom>0))
	    draw.BondInProgress(toolBondFrom,toolBondToX,toolBondToY,toolBondOrder,toolBondType);

    	if (tool==TOOL_ATOM && toolAtomDrag && toolAtomType!=null && toolAtomType.compareTo("C")!=0) 
	    draw.AtomInProgress(toolAtomType,toolBondToX,toolBondToY);
	if (tool==TOOL_BOND && toolBondFrom==0 && toolBondDrag)
	{
	    int i=PickAtom((int)AngToX(toolBondToX),(int)AngToY(toolBondToY));
	    if (i==0 && toolSnap) SnapToolBond();
	    double x1=toolBondFromX,y1=toolBondFromY,x2=toolBondToX,y2=toolBondToY;
	    if (i>0) {x2=mol.AtomX(i); y2=mol.AtomY(i);} 
	    draw.NewBondLine(x1,y1,x2,y2);
	}
	if (toolDragReason==DRAG_SELECT)
	{
	    draw.DragSelect((int)toolDragX1,(int)toolDragY1,(int)toolDragX2,(int)toolDragY2);
	}
    	if ((toolDragReason==DRAG_MOVE || toolDragReason==DRAG_COPY || toolDragReason==DRAG_SCALE) 
    	    && (toolDragX1!=toolDragX2 || toolDragY1!=toolDragY2))
	{
	    if (toolDragReason==DRAG_SCALE)
	    {
	    	double extmul=DragExtendBy(toolDragX2-toolDragX1,toolDragY2-toolDragY1),cx=0,cy=0;
		int count=0;
    	    	for (int n=1;n<=mol.NumAtoms();n++) if (selected[n-1]) {cx+=mol.AtomX(n); cy+=mol.AtomY(n); count++;}
		cx/=count; cy/=count;
		draw.DragScale(cx,cy,extmul);
	    }
	    else
	    {
	    	int dx=(int)(toolDragX2-toolDragX1),dy=(int)(toolDragY2-toolDragY1);
	    	draw.DragMove(dx,dy,toolDragReason==DRAG_COPY);
	    }
	}
	if (toolDragReason==DRAG_ROTATE && (Math.abs(toolDragX2-toolDragX1)>5 || Math.abs(toolDragY2-toolDragY1)>5))
	{
	    double dx=toolDragX2-toolDragX1,dy=toolDragY2-toolDragY1;
	    double th=-Math.atan2(dy,dx)*180/Math.PI;
	    if (toolSnap) th=Math.round(th/15)*15;
	    
	    draw.DragRotate(th,(int)toolDragX1,(int)toolDragY1);
	}
	if (tool==TOOL_TEMPLATE && trackX>=0 && trackY>=0)
	{
	    if (highlightAtom!=0 && templateIdx>0) AdjustTemplateByAtom(highlightAtom);
	    else if (highlightBond!=0 && templateIdx<0) AdjustTemplateByBond(highlightBond);
	    else AdjustTemplateByCoord(XToAng(trackX),YToAng(trackY));

	    draw.OutlineTemplate(templDraw);
	}

	draw.Draw();

    	// fetch some of the calculated properties, which are used for the editing progress
    	px=draw.GetPX(); py=draw.GetPY(); rw=draw.GetRW(); rh=draw.GetRH();
    	bfx=draw.GetBFX(); bfy=draw.GetBFY(); btx=draw.GetBTX(); bty=draw.GetBTY();
    }
    
    // Mouse events: the callbacks for Clicked, Pressed, Released, Dragged and Moved form a slightly complicated interplay of the various
    // tool events. The 'tool' variable, and its various permitted values, should make most of the behaviour reasonably self-explanatory;
    // note that many of the tools have multiple functions which may be sprinkled around the various event callbacks.
    
    public void mouseClicked(MouseEvent e){
    //jm.evers 17/1/2010
	if( e.getButton() == MouseEvent.BUTTON1 && MainApplet.user_selection  && tool == TOOL_SELECT){
	    if( highlightAtom > 0){
		if(highlightAtom > atomselection.length - 1){
		    atomselection = GrowArray(atomselection , highlightAtom+2 );
		}
		if(atomselection[highlightAtom]){
		    atomselection[highlightAtom] = false; // de_select
		}else{
		    atomselection[highlightAtom] = true; // select
		}
	    }
	    if(highlightBond > 0){
		if(highlightBond > bondselection.length - 1){
		    bondselection = GrowArray(bondselection , highlightBond+2 );
		}
		if(bondselection[highlightBond]){
		    bondselection[highlightBond] = false; // de_select
		}else{
		    bondselection[highlightBond] = true; // select
		}
	    }
	    repaint();
	}
	else
    	if (tool==TOOL_CURSOR && selectListen!=null)
	{
	    int i=PickAtom(e.getX(),e.getY());
	    if ((e.getModifiers()&MouseEvent.CTRL_MASK)>0 && i>0 && editable) // select connected component
	    {
	    	if ((e.getModifiers()&MouseEvent.SHIFT_MASK)==0 && selected!=null) for (int n=0;n<mol.NumAtoms();n++) selected[n]=false;
	    	if (selected==null) selected=new boolean[mol.NumAtoms()];
		int cc=mol.AtomConnComp(i);
		for (int n=1;n<=mol.NumAtoms();n++) if (mol.AtomConnComp(n)==cc) selected[n-1]=true;
		repaint();
	    }
	    else if (i>0) selectListen.MolSelected(this,i,e.getClickCount()>1); // notify of atom selection
	    else // notify of bond (or nothing) selection
	    {
	    	i=PickBond(e.getX(),e.getY());
		/*if (i>0)*/ selectListen.MolSelected(this,-i,e.getClickCount()>1); 
		// (0==clicked in general area)
	    }
	}
	else if (tool==TOOL_ROTATOR) // deselect
	{
	    selected=null;
	    ClearTemporary();
	    repaint();
	}
    	else if (tool==TOOL_ERASOR) // delete something, be it atom or bond
	{
	    int i=PickAtom(e.getX(),e.getY());
	    if (i>0) 
	    {
	    	CacheUndo();
	    	mol.DeleteAtomAndBonds(i);
	    }
	    else
	    {
	    	CacheUndo();
	    	i=PickBond(e.getX(),e.getY());
		if (i>0) mol.DeleteBond(i);
	    }
	    if (i>0)
	    {
	    	ClearTemporary();
		DetermineSize();
		repaint();
	    }
	}
    	else if (tool==TOOL_ATOM && e.getButton()==MouseEvent.BUTTON1 && !toolAtomDrag)
	{
	    if (toolAtomEditBox!=null) 
	    {
		CompleteAtomEdit();
		return;
    	    }
	
	    if (toolAtomType!=null)  // add new atom, or change element label
	    {
	    	int i=PickAtom(e.getX(),e.getY());
    	    	CacheUndo();
		if (i==0) 
		{
		    i=mol.AddAtom(toolAtomType,XToAng(e.getX()),YToAng(e.getY()));
    	    	    offsetX=e.getX()/scale-mol.AtomX(i);
	    	    offsetY=e.getY()/scale+mol.AtomY(i);
		}
		else mol.SetAtomElement(i,toolAtomType);
		ClearTemporary();
		
    	    	DetermineSize();
		repaint();
	    } 
	    else // setup new editing box for element
	    {
	    	toolAtomEditX=e.getX(); toolAtomEditY=e.getY();
	    	toolAtomEditSel=PickAtom(toolAtomEditX,toolAtomEditY);
	    	if (toolAtomEditSel==0 && PickBond(e.getX(),e.getY())>0) return;
		
		toolAtomEditBox=new JTextField(toolAtomEditSel>0 ? mol.AtomElement(toolAtomEditSel) : "");
		add(toolAtomEditBox);
		toolAtomEditBox.addFocusListener(this);
		toolAtomEditBox.addKeyListener(this);
		toolAtomEditBox.setLocation(toolAtomEditX-10,toolAtomEditY-10);
		toolAtomEditBox.setSize(20,20);
		toolAtomEditBox.setVisible(true);
		toolAtomEditBox.setSelectionStart(0);
		toolAtomEditBox.setSelectionEnd(toolAtomEditBox.getText().length());
		toolAtomEditBox.grabFocus();
	    }
	}
	else if (tool==TOOL_TEMPLATE && e.getButton()==MouseEvent.BUTTON2) // flip the template, horizontal or vertical
	{
	    boolean vertical=e.isShiftDown();
	    for (int n=1;n<=template.NumAtoms();n++) 
	    	template.SetAtomPos(n,template.AtomX(n)*(vertical?1:-1),template.AtomY(n)*(vertical?-1:1));
    	    templDraw=template.Clone();
    	    repaint();
	}	

	CheckDirtiness();
    }
    
    public void mouseEntered(MouseEvent e) 
    {
    	boolean redraw=false;
	if (tool==TOOL_TEMPLATE && (trackX!=e.getX() || trackY!=e.getY())) redraw=true;
    	trackX=e.getX(); trackY=e.getY();
	if (redraw) repaint();
    }
    
    public void mouseExited(MouseEvent e) 
    {
    	boolean redraw=false;
	if (tool==TOOL_TEMPLATE && (trackX!=e.getX() || trackY!=e.getY())) redraw=true;
    	trackX=-1; trackY=-1;
	if (redraw) repaint();
    }
    
    public void mousePressed(MouseEvent e)
    {
	grabFocus();

    	if ((tool==TOOL_CURSOR || (tool==TOOL_ROTATOR && !AnySelected())) && e.getButton()==MouseEvent.BUTTON1 && editable)
	{ // consider initiating a drag of the select, or translate position variety
    	    highlightAtom=highlightBond=0;
	    boolean shift=(e.getModifiers()&MouseEvent.SHIFT_MASK)>0;
	    boolean ctrl=(e.getModifiers()&MouseEvent.CTRL_MASK)>0;
	    boolean alt=(e.getModifiers()&MouseEvent.ALT_MASK)>0;
	    boolean anySelected=CountSelected()>0;
	    if (tool==TOOL_ROTATOR) {shift=false; ctrl=false; alt=false;} // can only select with rotator
	    if (!ctrl && !alt) 
	    {
	    	ResetSelected(!shift);
	    	int atom=PickAtom(e.getX(),e.getY());
		if (atom>0) selected[atom-1]=true;
		else toolDragReason=DRAG_SELECT;
	    }
	    else if (!shift && ctrl && !alt && anySelected) toolDragReason=DRAG_COPY;
	    else if (!shift && !ctrl && alt && anySelected) toolDragReason=DRAG_MOVE;
	    else if (shift && !ctrl && alt && anySelected) toolDragReason=DRAG_SCALE;

    	    toolDragX1=toolDragX2=e.getX();
	    toolDragY1=toolDragY2=e.getY();
	    repaint();
	}
	else if (tool==TOOL_ERASOR && e.getButton()==MouseEvent.BUTTON1) // initiate a drag-rect-delete sequence
	{
	    highlightAtom=highlightBond=0;
	    ResetSelected(true);
	    toolDragReason=DRAG_SELECT;
    	    toolDragX1=toolDragX2=e.getX();
	    toolDragY1=toolDragY2=e.getY();
	    repaint();
	}
	else if (tool==TOOL_ATOM) // note drag or change atom
	{
	    toolBondFrom=PickAtom(e.getX(),e.getY()); 	    	// in case it gets...
    	    toolAtomSnap=e.getButton()==MouseEvent.BUTTON1; 	// ... dragged later
	}
    	else if (tool==TOOL_BOND && (e.getButton()==MouseEvent.BUTTON1 || e.getButton()==MouseEvent.BUTTON3)) // initiate bond drag
	{
    	    highlightAtom=highlightBond=0;
	    toolBondDrag=false;
	    toolBondFrom=PickAtom(e.getX(),e.getY());
	    toolSnap=e.getButton()==MouseEvent.BUTTON1;
	    if (toolBondFrom>0)
	    {
	    	toolBondToX=mol.AtomX(toolBondFrom);
		toolBondToY=mol.AtomY(toolBondFrom);
		repaint();
	    }
	    toolBondFromX=XToAng(e.getX()); 
	    toolBondFromY=YToAng(e.getY());
	    toolBondHit=PickBond(e.getX(),e.getY());
	}
	else if (tool==TOOL_TEMPLATE && e.getButton()==MouseEvent.BUTTON1) // slap a template right down
	{
	    boolean swap=false;
	    if (highlightAtom!=0 && templateIdx>0) AdjustTemplateByAtom(highlightAtom);
    	    else if (highlightBond!=0 && templateIdx<0) swap=AdjustTemplateByBond(highlightBond);
	    else AdjustTemplateByCoord(XToAng(trackX),YToAng(trackY));
		
	    CacheUndo();
		
	    if (templateIdx>=0) 
	    	TemplateSetByAtom(highlightAtom); 
    	    	else 
		TemplateSetByBond(highlightBond,swap);
	}
	else if (tool==TOOL_ROTATOR && (e.getButton()==MouseEvent.BUTTON1 || e.getButton()==MouseEvent.BUTTON3) && AnySelected())
	{ // initiate a rotation-drag
	    toolDragReason=DRAG_ROTATE;
	    toolSnap=e.getButton()==MouseEvent.BUTTON1;
	    if (highlightAtom>0) {toolDragX1=AngToX(mol.AtomX(highlightAtom)); toolDragY1=AngToY(mol.AtomY(highlightAtom));}
	    else if (highlightBond>0) 
	    {
	    	toolDragX1=AngToX(0.5*(mol.AtomX(mol.BondFrom(highlightBond))+mol.AtomX(mol.BondTo(highlightBond))));
	    	toolDragY1=AngToY(0.5*(mol.AtomY(mol.BondFrom(highlightBond))+mol.AtomY(mol.BondTo(highlightBond))));
	    }
	    else {toolDragX1=e.getX(); toolDragY1=e.getY();}
	    highlightAtom=highlightBond=0;
	    
	    toolDragX2=toolDragX1;
	    toolDragY2=toolDragY1;
	    repaint();
	}
	else if (tool==TOOL_CHARGE && highlightAtom>0) // offset charge
	{
	    int chg=mol.AtomCharge(highlightAtom);
	    if (e.getButton()==MouseEvent.BUTTON1) chg+=toolCharge;
	    else if (e.getButton()==MouseEvent.BUTTON3) chg-=toolCharge;
	    else chg=0;
	    CacheUndo();
	    mol.SetAtomCharge(highlightAtom,chg);
	    repaint();
	}

	CheckDirtiness();
    }
    
    public void mouseReleased(MouseEvent e){
    	if ((tool==TOOL_CURSOR && toolDragReason!=0) || (tool==TOOL_ROTATOR && toolDragReason==DRAG_SELECT) && editable)
	{ // solidify a translate or select
	    toolDragX2=e.getX();
	    toolDragY2=e.getY();
	    double mx=toolDragX2-toolDragX1,my=toolDragY2-toolDragY1;
	    
	    if (toolDragReason==DRAG_SELECT && dragged!=null)
	    {
	    	for (int n=0;n<mol.NumAtoms();n++) selected[n]=selected[n] || dragged[n];
	    }
    	    if (toolDragReason==DRAG_MOVE && selected!=null && mx*mx+my*my>5*5)
	    {
	    	double dx=mx/scale,dy=-my/scale;
		CacheUndo();
		for (int n=1;n<=mol.NumAtoms();n++) if (selected[n-1]) 
		{
		    mol.SetAtomPos(n,mol.AtomX(n)+dx,mol.AtomY(n)+dy);
		}
		ClearTemporary(false);
		DetermineSize();
	    }
            if (toolDragReason==DRAG_COPY && selected!=null && mx*mx+my*my>5*5)
	    {
	    	double dx=(toolDragX2-toolDragX1)/scale,dy=-(toolDragY2-toolDragY1)/scale;
		int oldNumAtoms=mol.NumAtoms(),oldNumBonds=mol.NumBonds();
		int[] newPos=new int[mol.NumAtoms()];
		CacheUndo();
		for (int n=1;n<=oldNumAtoms;n++) if (selected[n-1]) 
		{
		    newPos[n-1]=mol.AddAtom(mol.AtomElement(n),mol.AtomX(n)+dx,mol.AtomY(n)+dy,mol.AtomCharge(n),mol.AtomUnpaired(n));
		}
		for (int n=1;n<=oldNumBonds;n++) if (selected[mol.BondFrom(n)-1] && selected[mol.BondTo(n)-1])
		{
		    mol.AddBond(newPos[mol.BondFrom(n)-1],newPos[mol.BondTo(n)-1],mol.BondOrder(n),mol.BondType(n));
		}

		ClearTemporary();
		selected=new boolean[mol.NumAtoms()];
		for (int n=1;n<=mol.NumAtoms();n++) selected[n-1]=n>oldNumAtoms;
		DetermineSize();
	    }
	    if (toolDragReason==DRAG_SCALE && selected!=null && mx*mx+my*my>5*5)
	    {
		double extmul=DragExtendBy(mx,my);
		double cx=0,cy=0;
		int count=0;
    	    	for (int n=1;n<=mol.NumAtoms();n++) if (selected[n-1]) {cx+=mol.AtomX(n); cy+=mol.AtomY(n); count++;}
		cx/=count; cy/=count;
		CacheUndo();
		for (int n=1;n<=mol.NumAtoms();n++) if (selected[n-1]) 
		{
    	    	    mol.SetAtomPos(n,(mol.AtomX(n)-cx)*extmul+cx,(mol.AtomY(n)-cy)*extmul+cy);
		}
		
		ClearTemporary(false);
		DetermineSize();
	    }

	    toolDragReason=0;
	    dragged=null;
    	    repaint();
	}
	if (tool==TOOL_ERASOR && toolDragReason!=0) // erase selection
	{
	    toolDragX2=e.getX();
	    toolDragY2=e.getY();
	    if (toolDragReason==DRAG_SELECT && dragged!=null)
	    {
	    	for (int n=0;n<mol.NumAtoms();n++) selected[n]=selected[n] || dragged[n];
		DeleteSelected();
		ClearTemporary();
	    }
	    toolDragReason=0;
	    dragged=null;
    	    repaint();
	}
    	else if (tool==TOOL_ROTATOR && toolDragReason==DRAG_ROTATE) // solidify a rotation
	{
	    double dx=toolDragX2-toolDragX1,dy=toolDragY2-toolDragY1;
	    double th=-Math.atan2(dy,dx)*180/Math.PI;
	    if (toolSnap) th=Math.round(th/15)*15;
	    if (Math.abs(th)>1) 
	    {
	    	CacheUndo();
		th=th*Math.PI/180;
		double ax=XToAng(toolDragX1),ay=YToAng(toolDragY1);
		for (int n=1;n<=mol.NumAtoms();n++) if (selected[n-1])
		{
	    	    double rx=mol.AtomX(n)-ax,ry=mol.AtomY(n)-ay;
		    double rth=Math.atan2(ry,rx),ext=Math.sqrt(rx*rx+ry*ry);
		    mol.SetAtomPos(n,ax+ext*Math.cos(rth+th),ay+ext*Math.sin(rth+th));
		}
		ClearTemporary(false);
		DetermineSize();
	    }

	    toolDragReason=0;
	    dragged=null;
    	    repaint();
	}
    	else if (tool==TOOL_ATOM && toolAtomDrag && toolBondFrom>0) // place a new atom-from
	{
	    CacheUndo();
	    mol.AddAtom(toolAtomType,toolBondToX,toolBondToY);
	    mol.AddBond(toolBondFrom,mol.NumAtoms(),1);
	    ClearTemporary();
    	    DetermineSize();
	    toolAtomDrag=false;
	    toolBondFrom=0;
    	    repaint();
	}
    	else if (tool==TOOL_BOND) // bond addition, possibly by adding new atoms, too
	{
	    toolBondToX=XToAng(e.getX());
	    toolBondToY=YToAng(e.getY());

    	    int joinTo=PickAtom(e.getX(),e.getY());
	    if (toolBondFrom>0 && joinTo==0 && toolSnap)
	    {
	    	SnapToolBond();
		joinTo=PickAtom((int)AngToX(toolBondToX),(int)AngToY(toolBondToY));
	    }
	    
	    if (e.getButton()==MouseEvent.BUTTON1 && toolBondFrom==0 && toolBondHit>0) // change hit bond order
	    {
		int i=PickBond(e.getX(),e.getY());
		if (i==toolBondHit)
		{
	    	    CacheUndo();
	    	    if (toolBondOrder==mol.BondOrder(i) && toolBondType==mol.BondType(i)) 
			mol.SetBondFromTo(i,mol.BondTo(i),mol.BondFrom(i));
	    	    mol.SetBondOrder(i,toolBondOrder); 
		    mol.SetBondType(i,toolBondType);
		    ClearTemporary();
		}
	    }
	    else if (toolBondFrom==0) // create a new bond from/in the middle of nowhere, possibly connected to something
	    {
	    	int a1=0,a2=0;
		double x1=0,x2=0,y1=0,y2=0;
	    	if (toolBondDrag)
		{
		    if (toolSnap) SnapToolBond();
		    x1=toolBondFromX;
		    y1=toolBondFromY;
		    a2=PickAtom(e.getX(),e.getY());
		    if (a2>0) {x2=mol.AtomX(a2); y2=mol.AtomY(a2);} else {x2=toolBondToX; y2=toolBondToY;}
		}
		else
		{
		    x1=x2=XToAng(e.getX()); if ((e.getModifiers()&MouseEvent.SHIFT_MASK)>0) {x1-=0.5*IDEALBOND; x2+=0.5*IDEALBOND;}
		    y1=y2=YToAng(e.getY()); if ((e.getModifiers()&MouseEvent.SHIFT_MASK)==0) {y1-=0.5*IDEALBOND; y2+=0.5*IDEALBOND;}
		}
		double dx=x2-x1,dy=y2-y1;
		if (dx*dx+dy*dy>0.5*0.5)
		{
		    CacheUndo();
	    	    a1=mol.AddAtom("C",x1,y1,0,0);
		    if (a2==0) a2=mol.AddAtom("C",x2,y2,0,0);
		    mol.AddBond(a1,a2,toolBondOrder);
		    ClearTemporary();
		}
		repaint();
	    }
	    else if (joinTo>0 && joinTo!=toolBondFrom) // link two atoms together
	    {
	    	CacheUndo();
	    	mol.AddBond(toolBondFrom,joinTo,toolBondOrder);
		mol.SetBondType(mol.NumBonds(),toolBondType);
    	    	ClearTemporary();
	    }
	    else if (toolBondFrom>0) // draw a new bond out to some place not specified by the user, i.e. a healthy guess
	    {
		double dx=toolBondToX-mol.AtomX(toolBondFrom),dy=toolBondToY-mol.AtomY(toolBondFrom);
		if (toolBondFrom==joinTo) 
		{
		    int adj[]=mol.AtomAdjList(toolBondFrom);
		    ArrayList<Double> poss=new ArrayList<Double>();
		    double ax=mol.AtomX(toolBondFrom),ay=mol.AtomY(toolBondFrom);
		    if (adj.length==0) poss.add(0.0);
		    else if (adj.length==1)
		    {
		    	double ang=Math.atan2(mol.AtomY(adj[0])-ay,mol.AtomX(adj[0])-ax)*180/Math.PI;
			if (toolBondOrder!=3)
			{
		    	    poss.add(ang+120);
			    poss.add(ang-120);
			}
			else poss.add(ang+180);
		    }
		    else if (adj.length==2)
		    {
		    	double ang1=Math.atan2(mol.AtomY(adj[0])-ay,mol.AtomX(adj[0])-ax)*180/Math.PI;
		    	double ang2=Math.atan2(mol.AtomY(adj[1])-ay,mol.AtomX(adj[1])-ax)*180/Math.PI;
		    	if (ang2<ang1) ang2+=360;
			if (ang2-ang1<180) poss.add(0.5*(ang1+ang2)+180); else poss.add(0.5*(ang1+ang2));
		    }
		    else for (int n=0;n<adj.length;n++)
		    {
		    	double ang=Math.atan2(mol.AtomY(adj[n])-ay,mol.AtomX(adj[n])-ax)*180/Math.PI;
		    	poss.add(ang+180);
		    }
		    double ang=poss.get(0);
		    if (poss.size()>1)
		    {
			int best=-1;
			double bestScore=0;
			for (int n=0;n<poss.size();n++)
			{
			    double nx=ax+IDEALBOND*Math.cos(poss.get(n)*Math.PI/180);
			    double ny=ay+IDEALBOND*Math.sin(poss.get(n)*Math.PI/180);
			    double score=0;
			    for (int i=1;i<=mol.NumAtoms();i++)
			    {
			    	dx=mol.AtomX(i)-nx;
				dy=mol.AtomY(i)-ny;
			    	score+=1/Math.min(1000,dx*dx+dy*dy);
			    }
			    if (best<0 || score<bestScore) {best=n; bestScore=score;}
			}
			ang=poss.get(best);
		    }
		    
		    dx=IDEALBOND*Math.cos(ang*Math.PI/180);
		    dy=IDEALBOND*Math.sin(ang*Math.PI/180);
		    toolBondToX=ax+dx;
		    toolBondToY=ay+dy;
		}
		if (dx*dx+dy*dy>0.5)
		{
		    CacheUndo();
	    	    mol.AddAtom("C",toolBondToX,toolBondToY);
		    mol.AddBond(toolBondFrom,mol.NumAtoms(),toolBondOrder);
		    mol.SetBondType(mol.NumBonds(),toolBondType);
		    ClearTemporary();
    	    	    DetermineSize();
    		}
	    }

	    toolBondDrag=false;
	    toolBondFrom=0;
	    toolBondHit=0;
	    // jm.evers
//	    if(MainApplet.user_selection){
//		atomselection = GrowArray(atomselection , mol.NumAtoms()+256 );	    
//	        bondselection = GrowArray(bondselection , mol.NumBonds()+256 );	    
//	    }
    	    repaint();
	}

	CheckDirtiness();
    }
    
    public void mouseMoved(MouseEvent e)
    {
    	boolean redraw=false;
	
	if (trackX!=e.getX() || trackY!=e.getY())
	{
	    if (tool==TOOL_TEMPLATE) redraw=true;
	}
	
	trackX=e.getX();
	trackY=e.getY();

    	if (e.getButton()==0)
	{
    	    int mx=e.getX(),my=e.getY();
    	    int newAtom=0,newBond=0;

    	    newAtom=PickAtom(mx,my);
	    if (newAtom==0) newBond=PickBond(mx,my);
	    
	    if (tool==TOOL_TEMPLATE && templateIdx>0) newBond=0;
	    if (tool==TOOL_TEMPLATE && templateIdx<0) newAtom=0;
	    
	    if (newAtom!=highlightAtom || newBond!=highlightBond)
	    {
    		highlightAtom=newAtom;
		highlightBond=newBond;
		redraw=true;
	    }
	}
	
    	if (redraw) repaint();
    }
    
    public void mouseDragged(MouseEvent e)
    {
    	boolean redraw=false;
	if (tool==TOOL_TEMPLATE && (trackX!=e.getX() || trackY!=e.getY())) redraw=true;
    	trackX=e.getX(); trackY=e.getY();
    
    	if ((tool==TOOL_CURSOR && toolDragReason!=0) || (tool==TOOL_ERASOR && toolDragReason!=0) ||
    	    (tool==TOOL_ROTATOR && toolDragReason==DRAG_SELECT))
	{
	    toolDragX2=e.getX();
	    toolDragY2=e.getY();
	    if (toolDragReason==DRAG_SELECT)
	    {
		int x=(int)toolDragX1,y=(int)toolDragY1,w=(int)toolDragX2-x,h=(int)toolDragY2-y;
		if (w<0) {w=-w; x-=w;}
		if (h<0) {h=-h; y-=h;}
		dragged=new boolean[mol.NumAtoms()];
		for (int n=0;n<mol.NumAtoms();n++) dragged[n]=px[n]>=x && px[n]<=x+w && py[n]>=y && py[n]<=y+h;
	    }
    	    redraw=true;
	}
	else if (tool==TOOL_ROTATOR && toolDragReason==DRAG_ROTATE)
	{
	    toolDragX2=e.getX();
	    toolDragY2=e.getY();
	    redraw=true;
	}
	else if (tool==TOOL_ATOM && toolBondFrom!=0)
	{
	    if (!toolAtomDrag)
	    {
	    	double dx=XToAng(e.getX())-mol.AtomX(toolBondFrom),dy=YToAng(e.getY())-mol.AtomY(toolBondFrom);
		if (dx*dx+dy*dy>0.8*0.8) 
		{
		    toolAtomDrag=true;
    	    	    toolBondOrder=1;
		    toolBondType=Molecule.BONDTYPE_NORMAL;
		}
	    }
	    if (toolAtomDrag)
	    {
	    	toolBondToX=XToAng(e.getX());
	    	toolBondToY=YToAng(e.getY());
		if (toolAtomSnap) SnapToolBond();
	    	redraw=true;
	    }
	}
	else if (tool==TOOL_BOND /*&& toolBondFrom!=0*/)
	{
	    toolBondToX=XToAng(e.getX());
	    toolBondToY=YToAng(e.getY());
    	    int joinTo=PickAtom(e.getX(),e.getY());
    	    if (!toolBondDrag)
	    	if (Math.abs(toolBondToX-toolBondFromX)>2/scale || Math.abs(toolBondToY-toolBondFromY)>2/scale) toolBondDrag=true;
	    if (joinTo>0) {toolBondToX=mol.AtomX(joinTo); toolBondToY=mol.AtomY(joinTo);}
	    else if (toolSnap) SnapToolBond();
	    redraw=true;
	}

    	if (redraw) repaint();
	CheckDirtiness();
    }
    
    public void mouseWheelMoved(MouseWheelEvent e)
    {
	if (tool==TOOL_TEMPLATE)
	{
	    double cx=0,cy=0;
	    for (int n=1;n<=template.NumAtoms();n++) {cx+=template.AtomX(n); cy+=template.AtomY(n);}
	    cx/=template.NumAtoms();
	    cy/=template.NumAtoms();
	
	    double accel=e.isShiftDown() ? 3 : 1;
	
	    if (e.isControlDown()) // scale
	    {
	    	double factor=1-0.1*accel*e.getWheelRotation();
	    	for (int n=1;n<=template.NumAtoms();n++) 
		    template.SetAtomPos(n,cx+(template.AtomX(n)-cx)*factor,cy+(template.AtomY(n)-cy)*factor);
	    }
	    else // rotate
    	    {
	    	double radians=5*accel*Math.PI/180*e.getWheelRotation();
		for (int n=1;n<=template.NumAtoms();n++) 
		{
		    double dx=template.AtomX(n)-cx,dy=template.AtomY(n)-cy;
		    double dist=Math.sqrt(dx*dx+dy*dy),theta=Math.atan2(dy,dx);
		    template.SetAtomPos(n,cx+dist*Math.cos(theta+radians),cy+dist*Math.sin(theta+radians));
		}
	    }
    	    templDraw=template.Clone();
    	    repaint();
	}
    }
    
    // Other callbacks...
    
    public void focusGained(FocusEvent e) {}
    public void focusLost(FocusEvent e)
    {
    	if (e.getSource()==toolAtomEditBox) CompleteAtomEdit();
    }
    public void keyPressed(KeyEvent e) {}
    public void keyReleased(KeyEvent e) {}
    public void keyTyped(KeyEvent e) 
    {
    	if (e.getSource()==toolAtomEditBox) 
	{
	    if (e.getKeyChar()=='\n') CompleteAtomEdit();
	}
    }

    public void componentHidden(ComponentEvent e) {}
    public void componentMoved(ComponentEvent e) {}
    public void componentResized(ComponentEvent e)
    {
    	if (autoScale) {ScaleToFit(); repaint();}
    }
    public void componentShown(ComponentEvent e) 
    {
    	if (autoScale) {ScaleToFit(); repaint();}
    }

// jm.evers 13/1/2010 rotating according to applet params ; called by MainPanel.java
    public void RotateMolecule(){
	double Degrees=MainApplet.rotation;
	if(Degrees != 0.0D){
	    double dist;
	    double dx;
	    double dy;
	    double theta;
	    double radians=(double)(Degrees*Math.PI/180);
	    for(int n=1;n<=mol.NumAtoms();n++){ 
    		dx=mol.AtomX(n);
	        dy=mol.AtomY(n);
    		dist=Math.sqrt(dx*dx+dy*dy);
	        theta=Math.atan2(dy,dx);
    		try{
		    mol.SetAtomPos(n,dist*Math.cos(theta+radians),dist*Math.sin(theta+radians));
		}catch(Exception e){System.out.println("problem with rotation : "+e);}
	    }
	    repaint();
	}
    }
    
    public static boolean[] GrowArray(boolean array[], int newlength){
	boolean[] grow;
	int oldlength = array.length;
	grow = new boolean[ newlength ];
	for(int i=0; i < oldlength; i++){
	    grow[i] = array[i];
	}
	return grow;
    } 

}












