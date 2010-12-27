/*
    WIMSchem Elements: Chemistry molecular diagram drawing tool.
    
    (c) 2007 Dr. Alex M. Clark
    
    Released as GNUware, under the Gnu Public License (GPL)
    
    See www.gnu.org for details.
*/

package WIMSchem;

import java.util.*;
import java.text.*;
import java.awt.*;
import java.awt.geom.*;

/*
    A class dedicated to the drawing of a molecule. Lifecycle: provide the minimal input data, add any additional parameters as necessary,
    draw onto a canvas of some kind, possibly grab back some data, then destroy.
*/

public class DrawMolecule
{
    Molecule mol;
    Graphics2D g;

    Color backgr=Color.WHITE;
    Color colHighlight=null,colSelected=null,colDragged=null;
    //,colExternalSelection=null;
    boolean showHydr=false;
    int showMode=SHOW_ALL_ELEMENTS;
    boolean showSter=false;
    
    double offsetX=0,offsetY=0; // in Angstrom units
    double scale=DEFSCALE; // pixels per Angstrom

    String[] atomLabel=null;
    boolean[] expl=null;
    int[] hcount=null;
    double[] px=null,py=null,rw=null,rh=null;
    double[][] bfx=null,bfy=null,btx=null,bty=null;
    int[] hdir=null;

    Font font=null,smallFont=null,boldFont=null;
    FontMetrics metrics=null,smallMetrics=null,boldMetrics=null;
    int txh=0;


    boolean[] selected=null,dragged=null;
    int highlightAtom=0,highlightBond=0;

    boolean bondInProgress=false;
    int bipFrom,bipOrder,bipType;
    double bipToX,bipToY;
    
    boolean atomInProgress=false;
    String aipLabel;
    double aipToX,aipToY;
    
    boolean newBondLine=false;
    double nblX1,nblY1,nblX2,nblY2;

    boolean dragSelect=false;
    int dslX1,dslY1,dslX2,dslY2;
    
    boolean dragScale=false;
    double dscCX,dscCY,dscExtMul;

    boolean dragMove=false;
    double dmvDX,dmvDY;
    boolean dmvCopy;
    
    boolean dragRotate=false;
    double droTheta;
    int droX,droY;
    
    boolean outlineTemplate=false;
    Molecule oltMol;
    // jm.evers 27/12/2008   
    boolean viewC=MainPanel.viewC;
    //
    // public constants
    public static final double DEFSCALE=20; // default # Angstroms per pixel
    public static final int SHOW_ELEMENTS=0;
    public static final int SHOW_ALL_ELEMENTS=1;
    public static final int SHOW_INDEXES=2;
    public static final int SHOW_RINGID=3;
    public static final int SHOW_PRIORITY=4;
    public static final int SHOW_MAPNUM=5;

    // constructor

    public DrawMolecule(Molecule Mol,Graphics2D Gr)
    {
    	mol=Mol;
	g=Gr;
    }
    
    // methods to provide other drawing options...
    
    public void SetBackground(Color Col) {backgr=Col;}
    public void SetShowHydr(boolean ShowH) {showHydr=ShowH;}
    public void SetShowMode(int Mode) {showMode=Mode;}
    public void SetShowStereo(boolean ShowSter) {showSter=ShowSter;}
    public void SetTransform(double OX,double OY,double Scale) {offsetX=OX; offsetY=OY; scale=Scale;}
    public void SetSelected(boolean[] Selected,boolean[] Dragged) {selected=Selected; dragged=Dragged;}
    public void SetHighlight(int Atom,int Bond) {highlightAtom=Atom; highlightBond=Bond;}

    public void BondInProgress(int From,double X,double Y,int Order,int Type)
    {
    	bondInProgress=true;
	bipFrom=From;
	bipToX=X;
	bipToY=Y;
	bipOrder=Order;
	bipType=Type;
    }
    public void AtomInProgress(String Label,double X,double Y)
    {
    	atomInProgress=true;
	aipLabel=Label;
	aipToX=X;
	aipToY=Y;
    }
    public void NewBondLine(double X1,double Y1,double X2,double Y2)
    {
    	// !! bond order and type should be accounted for...
    	newBondLine=true;
	nblX1=X1;
	nblY1=Y1;
	nblX2=X2;
	nblY2=Y2;
    }
    public void DragSelect(int X1,int Y1,int X2,int Y2)
    {
    	dragSelect=true;
	dslX1=X1;
	dslY1=Y1;
	dslX2=X2;
	dslY2=Y2;
    }
    public void DragScale(double CX,double CY,double ExtMul)
    {
    	dragScale=true;
	dscCX=CX;
	dscCY=CY;
	dscExtMul=ExtMul;
    }
    public void DragMove(double DX,double DY,boolean Copy)
    {
    	dragMove=true;
	dmvDX=DX;
	dmvDY=DY;
	dmvCopy=Copy;
    }
    public void DragRotate(double Theta,int X,int Y)
    {
    	dragRotate=true;
    	droTheta=Theta;
	droX=X;
	droY=Y;
    }
    public void OutlineTemplate(Molecule Templ)
    {
    	outlineTemplate=true;
    	oltMol=Templ;
    }
    
    // methods to extract calculated properties for future reference
    
    public double[] GetPX() {return px;}
    public double[] GetPY() {return py;}
    public double[] GetRW() {return rw;}
    public double[] GetRH() {return rh;}
    public double[][] GetBFX() {return bfx;}
    public double[][] GetBFY() {return bfy;}
    public double[][] GetBTX() {return btx;}
    public double[][] GetBTY() {return bty;}
    
    // perform the actual drawing
    
    public void Draw()
    {
    	SetupColours();
	SetupFonts();
	SetupLabels();
	SetupPositions();
	SetupHydrogens();
	DrawBacklighting();
	// jm.evers
	DrawExternalAtomSelection();
	DrawBonds();
	DrawAtoms();
	DrawEffects();
	DrawAnnotations();
	DrawCorrections();
    }
    
    // private methods
    
    // decides on particular colors
    void SetupColours()
    {
	if (colHighlight==null) colHighlight=backgr.darker();
	if (colSelected==null) colSelected=new Color(colHighlight.getRed(),colHighlight.getGreen(),255);
	if (colDragged==null) colDragged=new Color(colHighlight.getRed(),192,255);
	//if (colExternalSelection==null) colExternalSelection=new Color(255,0,0,50);
	
    }

    // creates the fonts and metrics
    void SetupFonts()
    {
    
    	font=new Font("SansSerif",Font.PLAIN,(int)(0.7*scale));
	g.setFont(font);
	metrics=g.getFontMetrics();
	txh=(int)(metrics.getAscent()*0.85);
	
	smallFont=new Font("SansSerif",Font.PLAIN,(int)(0.35*scale));
	g.setFont(smallFont);
	smallMetrics=g.getFontMetrics();
	
	boldFont=new Font("SansSerif",Font.BOLD,(int)(0.7*scale));
	g.setFont(boldFont);
	boldMetrics=g.getFontMetrics();
    	font=new Font("SansSerif",Font.PLAIN,(int)(0.7*scale));



    }
    
    // decides what exactly needs to be drawn for each atom label
    void SetupLabels(){
    	if (selected==null) selected=new boolean[mol.NumAtoms()];
	if (dragged==null) dragged=new boolean[mol.NumAtoms()];
    
    	if (atomLabel!=null && expl!=null && hcount!=null) return;
    
    	atomLabel=new String[mol.NumAtoms()];
	expl=new boolean[mol.NumAtoms()];
	hcount=new int[mol.NumAtoms()];
	for (int n=1;n<=mol.NumAtoms();n++){
	    // jm.evers: to accomodate param elements="no" ... only for Carbon 
	    // all other elements will still be shown, ofcourse
	    if( mol.AtomElement(n).equals("C") && viewC == false  && (showMode==SHOW_ELEMENTS || showMode==SHOW_ALL_ELEMENTS  )) atomLabel[n-1]=mol.AtomMapNum(n)>0 ? String.valueOf(mol.AtomMapNum(n)) : "";
	    else if (showMode==SHOW_ELEMENTS) atomLabel[n-1]=mol.AtomExplicit(n) ? mol.AtomElement(n) : "";
	    else if (showMode==SHOW_ALL_ELEMENTS) atomLabel[n-1]=mol.AtomElement(n);
	    else if (showMode==SHOW_INDEXES) atomLabel[n-1]=String.valueOf(n);
	    else if (showMode==SHOW_RINGID) atomLabel[n-1]=String.valueOf(mol.AtomRingBlock(n));
	    else if (showMode==SHOW_PRIORITY) atomLabel[n-1]=String.valueOf(mol.AtomPriority(n));
	    else if (showMode==SHOW_MAPNUM) atomLabel[n-1]=mol.AtomMapNum(n)>0 ? String.valueOf(mol.AtomMapNum(n)) : "";
	    else atomLabel[n-1]="?";
	    expl[n-1]=atomLabel[n-1].length()>0;
	    hcount[n-1]=showHydr && (showMode==SHOW_ELEMENTS || showMode==SHOW_ALL_ELEMENTS) && expl[n-1] ? mol.AtomHydrogens(n) : 0;
	}
    }
    
    // configure the positions of all of the atoms, and their associated bonds; apply whatever aesthetic corrections are deemed necessary
    void SetupPositions()
    {
    	if (px!=null && py!=null && rw!=null && rh!=null && bfx!=null && bfy!=null && btx!=null && bty!=null) return;
	
	px=new double[mol.NumAtoms()];
	py=new double[mol.NumAtoms()];
	rw=new double[mol.NumAtoms()];
	rh=new double[mol.NumAtoms()];
	bfx=new double[3][mol.NumBonds()+1];
	bfy=new double[3][mol.NumBonds()+1];
	btx=new double[3][mol.NumBonds()+1];
	bty=new double[3][mol.NumBonds()+1];

    	for (int n=1;n<=mol.NumAtoms();n++)
	{
	    px[n-1]=AngToX(mol.AtomX(n));
	    py[n-1]=AngToY(mol.AtomY(n));
	    if (expl[n-1])
	    {
	    	if (mol.AtomMapNum(n)==0)
		    rw[n-1]=0.5*metrics.stringWidth(atomLabel[n-1]);
		else
		    rw[n-1]=0.5*boldMetrics.stringWidth(atomLabel[n-1]);
	    	rh[n-1]=0.5*(metrics.getAscent()+metrics.getDescent());
	    }
	    else
	    {
	    	rw[n-1]=rh[n-1]=txh*0.4;
	    }
	}
	
    	// figure out which double bonds should go on one particular side
	int bondside[]=new int[mol.NumBonds()];
	for (int n=0;n<mol.NumBonds();n++) bondside[n]=0;
	int ring6[][]=mol.FindRingSize(6),nring6=ring6.length;
	for (int n=0;n<ring6.length;n++) // convert to bond indexes
	{
	    int a=ring6[n][0];
	    for (int i=0;i<6;i++) ring6[n][i]=mol.FindBond(ring6[n][i],i==5 ? a : ring6[n][i+1]);
	}
	int r6score[]=new int[ring6.length];
	while (true)
	{
	    int best=-1;
	    for (int n=0;n<nring6;n++)
	    {
	    	r6score[n]=0;
	    	for (int i=0;i<6;i++) if (mol.BondOrder(ring6[n][i])==2 && bondside[ring6[n][i]-1]==0) r6score[n]++;
		if (r6score[n]>0 && (best<0 || r6score[n]>r6score[best])) best=n;
	    }
	    if (best<0) break;
	    for (int n=0;n<6;n++)
	    {
	    	int bond=ring6[best][n];
		if (mol.BondOrder(bond)!=2 || bondside[bond-1]!=0) continue;
		int from=mol.BondFrom(bond),to=mol.BondTo(bond);
		int numLeft=0,numRight=0,numFrom=0,numTo=0;
		double thbond=Math.atan2(mol.AtomY(to)-mol.AtomY(from),mol.AtomX(to)-mol.AtomX(from));
		for (int i=0;i<6;i++) if (i!=n)
		{
		    int o=mol.BondOther(ring6[best][i],from);
		    double theta;
		    if (o>0)
		    {
    	    	    	theta=Math.atan2(mol.AtomY(o)-mol.AtomY(from),mol.AtomX(o)-mol.AtomX(from));
			numFrom++;
		    }
		    else
		    {
		    	o=mol.BondOther(ring6[best][i],to);
			if (o>0)
			{
			    theta=Math.atan2(mol.AtomY(o)-mol.AtomY(to),mol.AtomX(o)-mol.AtomX(to));
			    numTo++;
			}
		    	else continue;
		    }
		    theta=theta-thbond;
		    theta+=theta>Math.PI ? -2*Math.PI : theta<-Math.PI ? 2*Math.PI : 0;
		    if (theta<0) numLeft++; 
		    if (theta>0) numRight++;
		}
    	    	if (numFrom>0 && numTo>0) bondside[bond-1]=numLeft>numRight ? -1 : 1;
	    }
	    if (best<nring6-1) ring6[best]=ring6[--nring6];
	}
	// remaining bonds, if they are in a ring or are unevenly balanced
	for (int n=1;n<=mol.NumBonds();n++) if (mol.BondOrder(n)==2 && bondside[n-1]==0)
	{
	    int from=mol.BondFrom(n),to=mol.BondTo(n);
	    int[] adj1=mol.AtomAdjList(from),adj2=mol.AtomAdjList(to);
	    if (adj1.length>=3 && adj2.length>=3 && !mol.BondInRing(n)) continue; // evenly balanced chain bond, leave in middle
	    if ((adj1.length==1 && adj2.length>=3) || (adj2.length==1 && adj1.length>=3)) continue; // ketone-like bond
	    int numLeft=0,numRight=0,numFrom=0,numTo=0;
	    double thbond=Math.atan2(mol.AtomY(to)-mol.AtomY(from),mol.AtomX(to)-mol.AtomX(from));
	    for (int i=0;i<adj1.length;i++) if (adj1[i]!=to)
	    {
	    	double theta=Math.atan2(mol.AtomY(adj1[i])-mol.AtomY(from),mol.AtomX(adj1[i])-mol.AtomX(from))-thbond;
		theta+=theta>Math.PI ? -2*Math.PI : theta<-Math.PI ? 2*Math.PI : 0;
		int v=mol.BondInRing(n) && mol.AtomRingBlock(from)==mol.AtomRingBlock(adj1[i]) ? 2 : 1;
		if (theta<0) numLeft+=v; 
		if (theta>0) numRight+=v;
	    }
	    for (int i=0;i<adj2.length;i++) if (adj2[i]!=from)
	    {
	    	double theta=Math.atan2(mol.AtomY(adj2[i])-mol.AtomY(to),mol.AtomX(adj2[i])-mol.AtomX(to))-thbond;
		theta+=theta>Math.PI ? -2*Math.PI : theta<-Math.PI ? 2*Math.PI : 0;
		int v=mol.BondInRing(n) && mol.AtomRingBlock(to)==mol.AtomRingBlock(adj2[i]) ? 2 : 1;
		if (theta<0) numLeft+=v; 
		if (theta>0) numRight+=v;
	    }
    	    if (numLeft!=numRight) bondside[n-1]=numLeft>numRight ? -1 : 1;
	}
	
	int extraAtom=bondInProgress ? 1 : 0;
	
	// define positions for the bonds
	for (int n=1;n<=mol.NumBonds() + extraAtom;n++)
	{
	    int from,to,order,type,side;
	    double x1,y1,x2,y2,w1,h1,w2,h2;
	    boolean expl1,expl2;
	    if (n<=mol.NumBonds())
	    {
	    	from=mol.BondFrom(n); to=mol.BondTo(n); order=mol.BondOrder(n); type=mol.BondType(n); side=bondside[n-1];
	    	x1=px[from-1]; y1=py[from-1]; x2=px[to-1]; y2=py[to-1];
	    	w1=rw[from-1]; h1=rh[from-1]; w2=rw[to-1]; h2=rh[to-1];
		expl1=expl[from-1]; expl2=expl[to-1];
	    }
	    else // bond "in progress"
	    {
	    	from=bipFrom; to=0; order=bipOrder; type=bipType; side=0;
	    	x1=px[from-1]; y1=py[from-1]; x2=AngToX(bipToX); y2=AngToY(bipToY);
	    	w1=rw[from-1]; h1=rh[from-1]; w2=0; h2=0;
		expl1=expl[from-1]; expl2=false;
	    }

	    double dx=x2-x1,dy=y2-y1;
	    if (Math.abs(dx)<0.001)
	    {
	    	dx=0;
	    	if (expl1) y1+=h1 * (dy>0 ? 1 : -1);
		if (expl2) y2+=h2 * (dy>0 ? -1 : 1);
	    }
	    else if (Math.abs(dy)<0.001) 
	    {
	    	dy=0;
	    	if (expl1) x1+=w1 * (dx>0 ? 1 : -1);
		if (expl2) x2+=w2 * (dx>0 ? -1 : 1);
	    }
	    else
	    {
	    	double xy=Math.abs(dx/dy),yx=Math.abs(dy/dx);
	    	if (expl1)
		{
		    x1+=(w1*h1*xy/(xy*h1+w1)) * (dx>0 ? 2 : -2);
	    	    y1+=(w1*h1*yx/(yx*h1+w1)) * (dy>0 ? 2 : -2);
		}
	    	if (expl2)
		{
		    x2+=(w2*h2*xy/(xy*h2+w2)) * (dx>0 ? -2 : 2);
	    	    y2+=(w2*h2*yx/(yx*h2+w2)) * (dy>0 ? -2 : 2);
		}
	    }
	    
	    for (int i=0;i<3;i++) {bfx[i][n-1]=x1; bfy[i][n-1]=y1; btx[i][n-1]=x2; bty[i][n-1]=y2;}
	    
	    if (order==2 || order==3) 
	    {
	    	double norm=0.15*scale/Math.sqrt(dx*dx+dy*dy);
		double ox=Math.signum(dy)*Math.ceil(norm*Math.abs(dy)*(order==3 ? 1 : 0.5));
		double oy=-Math.signum(dx)*Math.ceil(norm*Math.abs(dx)*(order==3 ? 1 : 0.5));
		if (order==2)
		{
		    bfx[0][n-1]+=ox*(side-1); bfy[0][n-1]+=oy*(side-1); btx[0][n-1]+=ox*(side-1); bty[0][n-1]+=oy*(side-1);
		    bfx[1][n-1]+=ox*(side+1); bfy[1][n-1]+=oy*(side+1); btx[1][n-1]+=ox*(side+1); bty[1][n-1]+=oy*(side+1);
		    
		    if (n<=mol.NumBonds() && side!=0 && mol.AtomRingBlock(from)>0 && mol.BondInRing(n))
		    {
		    	int w=side<0 ? 0 : 1;
			if (!expl1) {bfx[w][n-1]+=norm*dx; bfy[w][n-1]+=norm*dy;}
			if (!expl2) {btx[w][n-1]-=norm*dx; bty[w][n-1]-=norm*dy;}
		    }
		}
		else
		{
		    bfx[1][n-1]-=ox; bfy[1][n-1]-=oy; btx[1][n-1]-=ox; bty[1][n-1]-=oy;
		    bfx[2][n-1]+=ox; bfy[2][n-1]+=oy; btx[2][n-1]+=ox; bty[2][n-1]+=oy;
		}
	    }
	}
	// special case for non-ring non-explicit double bond endpoints... neighbouring single bonds get snapped "to"
	for (int n=1;n<=mol.NumAtoms();n++) if (atomLabel[n-1].length()==0 && mol.AtomRingBlock(n)==0)
	{
	    boolean any=false;
	    double dpx1=0,dpy1=0,dpx2=0,dpy2=0;
	    for (int i=1;i<=mol.NumBonds();i++) if (mol.BondOrder(i)==2)
	    {
	    	if (mol.BondFrom(i)==n) {dpx1=bfx[0][i-1]; dpy1=bfy[0][i-1]; dpx2=bfx[1][i-1]; dpy2=bfy[1][i-1]; any=true; break;}
	    	if (mol.BondTo(i)==n) {dpx1=btx[0][i-1]; dpy1=bty[0][i-1]; dpx2=btx[1][i-1]; dpy2=bty[1][i-1]; any=true; break;}
	    }
	    if (!any) continue;
	    for (int i=1;i<=mol.NumBonds();i++) if (mol.BondOrder(i)==1)
	    {
	    	if (mol.BondFrom(i)==n)
		{
		    double dx1=dpx1-btx[0][i-1],dy1=dpy1-bty[0][i-1];
		    double dx2=dpx2-btx[0][i-1],dy2=dpy2-bty[0][i-1];
		    if (dx1*dx1+dy1*dy1<dx2*dx2+dy2*dy2) {bfx[0][i-1]=dpx1; bfy[0][i-1]=dpy1;} else {bfx[0][i-1]=dpx2; bfy[0][i-1]=dpy2;}
		}
		else if (mol.BondTo(i)==n)
		{
		    double dx1=dpx1-bfx[0][i-1],dy1=dpy1-bfy[0][i-1];
		    double dx2=dpx2-bfx[0][i-1],dy2=dpy2-bfy[0][i-1];
		    if (dx1*dx1+dy1*dy1<dx2*dx2+dy2*dy2) {btx[0][i-1]=dpx1; bty[0][i-1]=dpy1;} else {btx[0][i-1]=dpx2; bty[0][i-1]=dpy2;}
		}
	    }
	}
	
    }
    
    // for drawn-in hydrogens, work out which quadrant they are to be drawn on; done by working out angles to bonds, and finding the
    // lowest sum total of distance; note values: 1=east,2=north,3=west,4=south (+N*90 degrees)
    void SetupHydrogens()
    {
	hdir=new int[mol.NumAtoms()];
	
	for (int n=1;n<=mol.NumAtoms();n++)
    	{
	    hdir[n-1]=0; 
	    if (hcount[n-1]==0) continue;
	    int bonds[]=mol.AtomAdjList(n);
	    int avoid1=0,avoid2=20,avoid3=10,avoid4=20; 
	    for (int i=0;i<bonds.length + (bondInProgress && bipFrom==n ? 1 : 0);i++)
	    {
	    	double x=i<bonds.length ? mol.AtomX(bonds[i]) : bipToX,y=i<bonds.length ? mol.AtomY(bonds[i]) : bipToY;
	    	double theta=Math.atan2(y-mol.AtomY(n),x-mol.AtomX(n))*180/Math.PI;
		double dt1=0-theta,dt2=90-theta,dt3=180-theta,dt4=270-theta;
		dt1=Math.abs(dt1+(dt1<-180 ? 360:0)+(dt1>180 ? -360 : 0));
		dt2=Math.abs(dt2+(dt2<-180 ? 360:0)+(dt2>180 ? -360 : 0));
		dt3=Math.abs(dt3+(dt3<-180 ? 360:0)+(dt3>180 ? -360 : 0));
		dt4=Math.abs(dt4+(dt4<-180 ? 360:0)+(dt4>180 ? -360 : 0));
		avoid1+=dt1<80 ? 80-dt1 : 0;
		avoid2+=dt2<80 ? 80-dt2 : 0;
		avoid3+=dt3<80 ? 80-dt3 : 0;
		avoid4+=dt4<80 ? 80-dt4 : 0;
	    }
	    if (avoid1<=avoid2 && avoid1<=avoid3 && avoid1<=avoid4) hdir[n-1]=1;
	    else if (avoid3<=avoid2 && avoid3<=avoid4) hdir[n-1]=3;
	    else if (avoid2<=avoid4) hdir[n-1]=2;
	    else hdir[n-1]=4;
	}
    }
    
    // jm.evers 1/2010 select atoms with select_colors & select_atoms via applet param
    void DrawExternalAtomSelection(){
	if(MainApplet.ExternalAtomSelection !=  null){
	    for (int n=1;n<=mol.NumAtoms();n++){
		for(int i=0;i<MainApplet.ExternalAtomSelection.length;i++){
		    if( n == MainApplet.ExternalAtomSelection[i]){
			g.setColor(MainApplet.SelectedAtomColorArray[i]);
		    	double ext=Math.max(rw[n-1]*1.2,rh[n-1]*1.2);
			g.fill(new Ellipse2D.Double(px[n-1]-ext,py[n-1]-ext,2*ext,2*ext));
		    }
		}
	    }
	}
    }
    // draws various types of highlighting, if appropriate
    void DrawBacklighting()
    {
	for (int n=1;n<=mol.NumAtoms();n++)
	{	    
    	    boolean drag=false;
	    if (dragged!=null) drag=dragged[n-1];
	    
	    // 12/2009 jm.evers fix trouble with invisble loose C atoms...paint loose C's
	    // System.out.println(mol.AtomAdjCount(n));
	    if( mol.AtomElement(n).equals("C") && viewC == false){
		if(mol.AtomAdjCount(n) == 0){
		    double ext=Math.max(rw[n-1]*1.2,rh[n-1]*1.2);
		    g.setColor(colDragged);
		    g.fill(new Ellipse2D.Double(px[n-1]-ext,py[n-1]-ext,2*ext,2*ext));
		}
	    }
	    if (selected[n-1] || n==highlightAtom || drag)
	    {
    	    	g.setColor(selected[n-1] ? colSelected : drag ? colDragged : colHighlight);
		double ext=Math.max(rw[n-1]*1.2,rh[n-1]*1.2);
		g.fill(new Ellipse2D.Double(px[n-1]-ext,py[n-1]-ext,2*ext,2*ext));
	    }
	}

    	if (highlightBond!=0) for (int n=0;n==0 || n<mol.BondOrder(highlightBond) && n<3;n++)
	{
	    int bn=highlightBond-1;
	    double x1=bfx[n][bn],y1=bfy[n][bn],x2=btx[n][bn],y2=bty[n][bn];
	    double dx=x2-x1,dy=y2-y1;
	    double norm=0.15*scale/Math.sqrt(dx*dx+dy*dy);
	    double ox=norm*dy,oy=-norm*dx;
	    Polygon pgn=new Polygon();
	    pgn.addPoint((int)Math.round(x1+oy*0.5),(int)Math.round(y1-ox*0.5));
	    pgn.addPoint((int)Math.round(x1-ox),(int)Math.round(y1-oy));
	    pgn.addPoint((int)Math.round(x2-ox),(int)Math.round(y2-oy));
	    pgn.addPoint((int)Math.round(x2-oy*0.5),(int)Math.round(y2+ox*0.5));
	    pgn.addPoint((int)Math.round(x2+ox),(int)Math.round(y2+oy));
	    pgn.addPoint((int)Math.round(x1+ox),(int)Math.round(y1+oy));
	    g.fill(pgn);
	}
    }

    // draws all of the bonds
    void DrawBonds(){
	boolean foundselected;
	for (int n=1;n<=mol.NumBonds()+(bondInProgress ? 1 : 0);n++){
	    g.setColor(Color.black);
	    double x1=bfx[0][n-1],y1=bfy[0][n-1],x2=btx[0][n-1],y2=bty[0][n-1],dx=x2-x1,dy=y2-y1;
	    int order=n<=mol.NumBonds() ? mol.BondOrder(n) : bipOrder;
	    int type=n<=mol.NumBonds() ? mol.BondType(n) : bipType;
	    boolean mappedBond=n<=mol.NumBonds() ? (mol.AtomMapNum(mol.BondFrom(n))>0 && mol.AtomMapNum(mol.BondTo(n))>0) : false;
	    // jm.evers
	    if(MainApplet.user_selection){
		if( EditorPane.bondselection.length > mol.NumBonds()){ // userbased click selection
		    if( EditorPane.bondselection[n] ){
			g.setColor(MainApplet.DefaultBondSelectionColor);
		    }
		}
		else
		{
		    EditorPane.bondselection = EditorPane.GrowArray(EditorPane.bondselection,mol.NumBonds()+32);
		}
	    }
	    if( MainApplet.ExternalBondSelection != null ){ // for answer molecule ; set by params
		for(int i=0;i<MainApplet.ExternalBondSelection.length;i++){
		    if( n == MainApplet.ExternalBondSelection[i]){
			g.setColor(MainApplet.SelectedBondColorArray[i]);
		    }
		}
	    }
	    if (type==Molecule.BONDTYPE_INCLINED)
	    {	
	    	double norm=0.15*scale/Math.sqrt(dx*dx+dy*dy);
		double ox=norm*dy,oy=-norm*dx;
		Polygon pgn=new Polygon();
		pgn.addPoint((int)Math.round(x1),(int)Math.round(y1));
		pgn.addPoint((int)Math.round(x2-ox),(int)Math.round(y2-oy));
		pgn.addPoint((int)Math.round(x2+ox),(int)Math.round(y2+oy));
		g.fill(pgn);
	    }
	    else if (type==Molecule.BONDTYPE_DECLINED)
	    {
	    	int nsteps=(int)Math.ceil(Math.sqrt(dx*dx+dy*dy)*0.15);
	    	double norm=0.15*scale/Math.sqrt(dx*dx+dy*dy);
		double ox=norm*dy,oy=-norm*dx;
		for (int i=0;i<=nsteps+1;i++)
		{
		    double cx=x1+i*dx/(nsteps+1),cy=y1+i*dy/(nsteps+1);
		    double ix=ox*i/(nsteps+1),iy=oy*i/(nsteps+1);
    	    	    g.setStroke(new BasicStroke((float)(0.05*scale)));
		    g.draw(new Line2D.Double(cx-ix,cy-iy,cx+ix,cy+iy));
		}
	    }
	    else if (type==Molecule.BONDTYPE_UNKNOWN)
	    {
	    	int nsteps=(int)Math.ceil(Math.sqrt(dx*dx+dy*dy)*0.2);
	    	double norm=0.2*scale/Math.sqrt(dx*dx+dy*dy);
		double ox=norm*dy,oy=-norm*dx;
		for (int i=0;i<=nsteps;i++)
		{
		    double ax=x1+i*dx/(nsteps+1),ay=y1+i*dy/(nsteps+1);
		    double cx=x1+(i+1)*dx/(nsteps+1),cy=y1+(i+1)*dy/(nsteps+1);
		    double bx=(ax+cx)/2,by=(ay+cy)/2;
		    int sign=i%2==0 ? 1 : -1;
    	    	    g.setStroke(new BasicStroke((float)(0.05*scale)));
		    g.draw(new QuadCurve2D.Double(ax,ay,bx+sign*ox,by+sign*oy,cx,cy));
		}
	    }
	    else if (order==0)
	    {
	    	int nsteps=(int)Math.ceil(Math.sqrt(dx*dx+dy*dy)*0.10);
		float radius=(float)(mappedBond ? 0.2*scale : 0.1*scale);
		for (int i=0;i<=nsteps+1;i++)
		{
		    double cx=x1+i*dx/(nsteps+1),cy=y1+i*dy/(nsteps+1);
		    g.fill(new Ellipse2D.Double(cx-0.05*scale,cy-0.05*scale,radius,radius));
		}
	    }
	    else
	    {
		float thickness=(float)(mappedBond ? 0.125*scale : 0.075*scale);
    	    	g.setStroke(new BasicStroke(thickness,BasicStroke.CAP_ROUND,BasicStroke.JOIN_ROUND));
	    	for (int i=order<=3 ? order-1 : 2;i>=0;i--)
		    g.draw(new Line2D.Double(bfx[i][n-1],bfy[i][n-1],btx[i][n-1],bty[i][n-1]));
	    }
	}
    }
    
    // draw the atoms proper, as well as standard annotations such as hydrogen atoms and charges
    void DrawAtoms(){
    	// atoms first
	for (int n=1;n<=mol.NumAtoms();n++){
	    // jm.evers 20/2/2010 show nonvisible 
	    if (atomLabel[n-1].length()==0 && viewC) continue;
	    if( MainApplet.user_selection){ 
		if(EditorPane.atomselection.length > mol.NumAtoms() ){//jm.evers
		    if( EditorPane.atomselection[n] ){
    			g.setColor(MainApplet.DefaultAtomSelectionColor);
			double ext=Math.max(rw[n-1]*1.2,rh[n-1]*1.2);
			g.fill(new Ellipse2D.Double(px[n-1]-ext,py[n-1]-ext,2*ext,2*ext));
		    }
		}else{
		    EditorPane.atomselection = EditorPane.GrowArray(EditorPane.atomselection,mol.NumAtoms()+32);
		}
	    }
	    g.setColor(showMode==SHOW_INDEXES ? Color.BLUE : showMode==SHOW_RINGID ? Color.RED : 
	    showMode==SHOW_PRIORITY ? Color.GREEN.darker() : showMode==SHOW_MAPNUM ? Color.MAGENTA : Color.BLACK);
	    double hx=px[n-1],hy=py[n-1] -0.1*metrics.getAscent(); // (& little fudge for font alignment)
	    g.setFont(mol.AtomMapNum(n)>0 && (showMode==SHOW_ELEMENTS || showMode==SHOW_ALL_ELEMENTS) ? boldFont : font);
	    g.drawString(atomLabel[n-1],(float)(hx-rw[n-1]),(float)(hy+0.5*metrics.getAscent()));
	    if (hcount[n-1]>0){
		int bigHWid=metrics.stringWidth("H");
		int subHWid=hcount[n-1]>1 ? smallMetrics.stringWidth(String.valueOf(hcount[n-1])) : 0;
		if (hdir[n-1]==1) {hx+=rw[n-1]; hy+=0.5*metrics.getAscent();}
		else if (hdir[n-1]==3) {hx-=rw[n-1]+bigHWid+subHWid; hy+=0.5*metrics.getAscent();}
		else if (hdir[n-1]==2) {hx-=rw[n-1]; hy-=0.5*metrics.getAscent();}
		else if (hdir[n-1]==4) {hx-=rw[n-1]; hy+=1.5*metrics.getAscent();}
	    	g.setFont(font);
		// hydrogen color
	    	g.setColor(Color.BLACK);
		g.drawString("H",(float)hx,(float)hy);
		if (hcount[n-1]>1) {
    	    	    g.setFont(smallFont);
		    g.drawString(String.valueOf(hcount[n-1]),(float)hx+bigHWid,(float)hy);
		}
	    }
	}
	
	// annotations next
	final int ANNOT_PLUS=1,ANNOT_MINUS=2,ANNOT_RAD=3;
	ArrayList<Integer> annot=new ArrayList<Integer>();
	double usz=scale*0.3;

	for (int n=1;n<=mol.NumAtoms();n++)
	{
	    annot.clear();
	    int chg=mol.AtomCharge(n);
	    while (chg<0) {annot.add(ANNOT_MINUS); chg++;}
	    while (chg>0) {annot.add(ANNOT_PLUS); chg--;}
	    int rad=mol.AtomUnpaired(n);
	    while (rad>0) {annot.add(ANNOT_RAD); rad--;}
	    
	    if (annot.size()==0) continue;
	    
    	    double bw=annot.size()*usz,bh=usz;
	    final int ANG_INCR=5,CLOCK_SZ=360/ANG_INCR,SAMP_SZ=3*CLOCK_SZ;
	    double bestAng=0,bestExt=0,bestScore=Double.MAX_VALUE;
	    for (int i=1;i<=3;i++) for (int j=0;j<CLOCK_SZ;j++)
	    {
	    	double ang=j*ANG_INCR;
		if (hdir[n-1]==1 && (ang<=45 || ang>=315)) continue;
		if (hdir[n-1]==4 && ang>=45 && ang<=135) continue;
		if (hdir[n-1]==3 && ang>=135 && ang<=225) continue;
		if (hdir[n-1]==2 && ang>=225 && ang<=315) continue;
		
		double ext=0.5*(rw[n-1]+rw[n-1])+i*scale*0.25;
		double from45=Math.min(Math.abs(315-ang + (ang<135 ? -360 : 0)),90);
		double score=10*ext + 0.01*from45;
		if (score>bestScore) continue;
	
	    	double ax=px[n-1]+ext*Math.cos(ang*Math.PI/180.0);
	    	double ay=py[n-1]+ext*Math.sin(ang*Math.PI/180.0);
		
    	    	for (int k=1;k<=mol.NumBonds();k++)
		{
    	    	    double dsq=0;
    	    	    double x1=px[mol.BondFrom(k)-1],y1=py[mol.BondFrom(k)-1],x2=px[mol.BondTo(k)-1],y2=py[mol.BondTo(k)-1];
		    double vx=x2-x1,vy=y2-y1,wx=ax-x1,wy=ay-y1;
		    double c1=vx*wx+vy*wy;
		    if (c1<=0) dsq=(ax-x1)*(ax-x1)+(ay-y1)*(ay-y1);
		    else 
		    {
		    	double c2=vx*vx+vy*vy;
			if (c2<=c1) dsq=(ax-x2)*(ax-x2)+(ay-y2)*(ay-y2);
			else
			{
			    double b=c1/c2;
			    double bx=x1+b*vx,by=y1+b*vy;
			    dsq=(ax-bx)*(ax-bx)+(ay-by)*(ay-by);
			}
		    } 
		    
		    score+=100/Math.max(dsq,0.0001);
		}		
	
    	    	if (score<bestScore) 
		{
	    	    bestAng=ang;
		    bestExt=ext;
		    bestScore=score;
		}
	    }
	    
	    double ax=px[n-1]+bestExt*Math.cos(bestAng*Math.PI/180.0)-0.5*bw;
	    double ay=py[n-1]+bestExt*Math.sin(bestAng*Math.PI/180.0)-0.5*bh;
    	    g.setColor(Color.BLACK);
	    for (int i=0;i<annot.size();i++)
	    {
	    	int type=annot.get(i).intValue();
		double x1=ax+0.2*usz,x2=ax+0.8*usz,y1=ay+0.2*usz,y2=ay+0.8*usz;
	    	if (type==ANNOT_MINUS || type==ANNOT_PLUS)
		{
		    g.draw(new Line2D.Double(x1,0.5*(y1+y2),x2,0.5*(y1+y2)));
		}
		if (type==ANNOT_PLUS)
		{
		    g.draw(new Line2D.Double(0.5*(x1+x2),y1,0.5*(x1+x2),y2));
		}
		if (type==ANNOT_RAD)
		{
	    	    g.fill(new Ellipse2D.Double(ax+0.2*usz,ay+0.2*usz,0.6*usz,0.6*usz));
		}
	    	ax+=usz;
	    }
	}
    }
    
    // draw the less common annotations, such as stereo labels, atom mapping numbers, etc.
    void DrawAnnotations()
    {
    	if (showSter)
	{
	    for (int n=1,chi;n<=mol.NumAtoms();n++) if ((chi=mol.AtomChirality(n))!=Molecule.STEREO_NONE)
	    {
	    	String label=chi==Molecule.STEREO_POS ? "R" : chi==Molecule.STEREO_NEG ? "S" : "R/S";
	    	g.setColor(Color.BLUE);
    	    	g.setFont(font);
	    	g.drawString(label,(float)(px[n-1]-0.5*metrics.stringWidth(label)),(float)(py[n-1]+metrics.getHeight()));
	    }
	    for (int n=1,chi;n<=mol.NumBonds();n++) if ((chi=mol.BondStereo(n))!=Molecule.STEREO_NONE)
	    {
	    	String label=chi==Molecule.STEREO_POS ? "Z" : chi==Molecule.STEREO_NEG ? "E" : "E/Z";
		int i1=mol.BondFrom(n)-1,i2=mol.BondTo(n)-1;
	    	g.setColor(Color.BLUE);
    	    	g.setFont(font);
	    	g.drawString(label,(float)(0.5*(px[i1]+px[i2]-metrics.stringWidth(label))),
		    	    	   (float)(0.5*(py[i1]+py[i2]+metrics.getHeight())));
	    }
	}
    }

    // draw the effects of various editing-in-progress actions
    void DrawEffects()
    {
    	if (atomInProgress)
	{
	    g.setColor(Color.BLUE);
	    g.setFont(font);
	    double tx=AngToX(aipToX),ty=AngToY(aipToY);
	    g.drawString(aipLabel,(float)(tx-0.5*metrics.stringWidth(aipLabel)),(float)(ty+0.4*metrics.getAscent()));
	}

    	if (newBondLine)
	{
	    g.setColor(Color.BLACK);
	    g.draw(new Line2D.Double(AngToX(nblX1),AngToY(nblY1),AngToX(nblX2),AngToY(nblY2)));
    	}
	
	if (dragSelect)
	{
	    g.setXORMode(Color.YELLOW);
	    int x=dslX1,y=dslY1,w=dslX2-dslX1,h=dslY2-dslY1;
	    if (w<0) {w=-w; x-=w;}
	    if (h<0) {h=-h; y-=h;}
	    g.drawRect(x,y,w,h);
	    g.setXORMode(Color.BLACK);
	}
	
	if (dragScale)
	{
	    g.setColor(Color.BLACK);
    	    g.setStroke(new BasicStroke(1.1F));
	    for (int n=1;n<=mol.NumAtoms();n++) if (selected[n-1])
	    {
	    	double sx=AngToX((mol.AtomX(n)-dscCX)*dscExtMul+dscCX),sy=AngToY((mol.AtomY(n)-dscCY)*dscExtMul+dscCY);
    	    	g.draw(new Ellipse2D.Double(sx-scale*0.3,sy-scale*0.3,scale*0.6,scale*0.6));
	    }
    	}
	
	if (dragMove)
	{
	    g.setColor(Color.BLACK);
    	    g.setStroke(new BasicStroke(1.1F));
	    for (int n=1;n<=mol.NumAtoms();n++) if (selected[n-1])
	    {
	    	double sx=px[n-1]+dmvDX,sy=py[n-1]+dmvDY;
    	    	g.draw(new Ellipse2D.Double(sx-scale*0.3,sy-scale*0.3,scale*0.6,scale*0.6));
		if (dmvCopy)
		{
		    g.draw(new Line2D.Double(sx-scale*0.15,sy,sx+scale*0.15,sy));
		    g.draw(new Line2D.Double(sx,sy-scale*0.15,sx,sy+scale*0.15));
		}
	    }
    	}
	
    	if (dragRotate)
	{
	    double thrad=droTheta*Math.PI/180;
	    g.setColor(Color.RED);
	    g.setStroke(new BasicStroke(0.5F,BasicStroke.CAP_ROUND,BasicStroke.JOIN_ROUND,1F,new float[]{2,2},0));
	    g.draw(new Line2D.Double(droX,droY,droX+50,droY));
	    g.setStroke(new BasicStroke(1F));
	    g.draw(new Line2D.Double(droX,droY,droX+50*Math.cos(-thrad),droY+50*Math.sin(-thrad)));
	    g.draw(new Arc2D.Double(droX-20,droY-20,40,40,0,droTheta,Arc2D.OPEN));

    	    int ty=(int)((droTheta>25 || (droTheta<0 && droTheta>=-25)) ? droY-5 : droY+5+txh);
	    DecimalFormat fmt=new DecimalFormat("0");
	    g.drawString((droTheta>0?"+":"")+fmt.format(Math.round(droTheta)),(int)(droX+25),ty);
	    
	    double ax=XToAng(droX),ay=YToAng(droY);
    	    g.setStroke(new BasicStroke(1.1F));
	    for (int n=1;n<=mol.NumAtoms();n++) if (selected[n-1])
	    {
	    	double rx=mol.AtomX(n)-ax,ry=mol.AtomY(n)-ay;
		double rth=Math.atan2(ry,rx),ext=Math.sqrt(rx*rx+ry*ry);
		rx=ax+ext*Math.cos(rth+thrad);
		ry=ay+ext*Math.sin(rth+thrad);
		g.draw(new Ellipse2D.Double(AngToX(rx)-scale*0.3,AngToY(ry)-scale*0.3,scale*0.6,scale*0.6));
	    }
	}
		    
    	if (outlineTemplate)
	{
	    g.setColor(new Color(128,128,128));
    	    g.setStroke(new BasicStroke(1));
	    for (int n=1;n<=oltMol.NumBonds();n++)
	    {
	    	int from=oltMol.BondFrom(n),to=oltMol.BondTo(n);
		g.draw(new Line2D.Double(AngToX(oltMol.AtomX(from)),AngToY(oltMol.AtomY(from)),
		    	    	    	 AngToX(oltMol.AtomX(to)),AngToY(oltMol.AtomY(to))));
	    }
	}
    }
    
    // bring attention to structures which are malformed
    void DrawCorrections()
    {
	// see if any atoms severely overlap, and if so, draw a red circle around them
	for (int i=1;i<=mol.NumAtoms()-1;i++)
	for (int j=i+1;j<=mol.NumAtoms();j++)
	{
	    double dx=mol.AtomX(i)-mol.AtomX(j),dy=mol.AtomY(i)-mol.AtomY(j);
	    if (dx*dx+dy*dy<0.2*0.2)
	    {
	    	g.setColor(Color.RED);
	    	g.setStroke(new BasicStroke(0.5F));
	    	g.draw(new Ellipse2D.Double(px[i-1]-scale*0.25,py[i-1]-scale*0.25,scale*0.5,scale*0.5));

	    }
	}
    }
    
    // translation of screen & molecule coordinates    
    double AngToX(double AX) {return (offsetX+AX)*scale;}
    double AngToY(double AY) {return (offsetY-AY)*scale;}
    double XToAng(double PX) {return (PX/scale)-offsetX;}
    double YToAng(double PY) {return (-PY/scale)+offsetY;}
}
