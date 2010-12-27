/*
    WIMSchem Elements: Chemistry molecular diagram drawing tool.
    
    (c) 2005 Dr. Alex M. Clark
    
    Released as GNUware, under the Gnu Public License (GPL)
    
    See www.gnu.org for details.
*/

package WIMSchem;

import java.util.*;

/*
    Internal molecule datastructure, which captures the basic information about a molecule as envisaged by the traditional diagram
    notation. The core data is stored as a list of labelled nodes (atoms) and labelled edges (bonds). Besides very basic editing and
    convenient object manipulation, a few computed properties are available, some of which are cached.
*/

public class Molecule
{
    class Atom
    {
    	String Element;
	double X,Y;
	int Charge,Unpaired;
	int HExplicit; 
	int MapNum;
    }
    class Bond
    {
    	int From,To;
	int Order,Type;
    }
    
    public static final int HEXPLICIT_UNKNOWN=-1;
    
    public static final int BONDTYPE_NORMAL=0;
    public static final int BONDTYPE_INCLINED=1;
    public static final int BONDTYPE_DECLINED=2;
    public static final int BONDTYPE_UNKNOWN=3;
    
    public static final String[] ELEMENTS={null,
	"H","He","Li","Be","B","C","N","O","F","Ne","Na","Mg","Al","Si","P","S","Cl","Ar","K","Ca","Sc","Ti","V","Cr","Mn","Fe","Co",
	"Ni","Cu","Zn","Ga","Ge","As","Se","Br","Kr","Rb","Sr","Y","Zr","Nb","Mo","Tc","Ru","Rh","Pd","Ag","Cd","In","Sn","Sb","Te","I",
	"Xe","Cs","Ba","La","Ce","Pr","Nd","Pm","Sm","Eu","Gd","Tb","Dy","Ho","Er","Tm","Yb","Lu","Hf","Ta","W","Re","Os","Ir","Pt","Au",
	"Hg","Tl","Pb","Bi","Po","At","Rn","Fr","Ra","Ac","Th","Pa","U","Np","Pu","Am","Cm","Bk","Cf","Es","Fm","Md","No","Lr"};

    public static final double[] WEIGHTS={0.0,
	1.00794,4.002602,6.941,9.01218,10.811,12.011,14.00674,15.9994,18.998403,20.1797,
	22.989768,24.305,26.981539,28.0855,30.973762,32.066,35.4527,39.948,39.0983,40.078,
	44.95591,47.88,50.9415,51.9961,54.93805,55.847,58.9332,58.6934,63.546,65.39,
	69.723,72.61,74.92159,78.96,79.904,83.8,85.4678,87.62,88.90585,91.224,
	92.90638,95.94,97.9072,101.07,102.9055,106.42,107.8682,112.411,114.818,118.71,
	121.760,127.6,126.90447,131.29,132.90543,137.327,138.9055,140.115,140.90765,144.24,
	144.9127,150.36,151.965,157.25,158.92534,162.50,164.93032,167.26,168.93421,173.04,
	174.967,178.49,180.9479,183.84,186.207,190.23,192.22,195.08,196.96654,200.59,
	204.3833,207.2,208.98037,208.9824,209.9871,222.0176,223.0197,226.0254,227.0278,232.0381,
	231.03588,238.0289,237.048,244.0642,243.0614,247.0703,247.0703,251.0796,252.083,257.0951,
	258.1,259.1009,262.11};                                                                                                              
                                
	

    boolean invalMinMax=false;
    double minX=0,minY=0,maxX=0,maxY=0;
    ArrayList<Atom> atoms=new ArrayList<Atom>();
    ArrayList<Bond> bonds=new ArrayList<Bond>();
    
    // computed graph topology properties
    int graph[][]=null;
    int ringID[]=null,compID[]=null,priority[]=null;
    ArrayList<Object> ring5=null,ring6=null,ring7=null; // common ring sizes
    
    // computed stereochemistry properties
    public static final int STEREO_NONE=0; // topology does not allow any stereoisomers
    public static final int STEREO_POS=1; // R or Z, depending on type
    public static final int STEREO_NEG=2; // S or E, depending on type
    public static final int STEREO_UNKNOWN=3; // topology allows stereoisomers, but wedges/geometry do not resolve which
    int chiral[]=null; // (per atom)
    int cistrans[]=null; // (per bond)

    // data for calculation of implicit hydrogens
    static final String[] HYVALENCE_EL={"C","N","O","S","P"};
    static final int[]   HYVALENCE_VAL={ 4,  3,  2,  2,  3 };
    
    // ------------------ public functions --------------------

    public Molecule()
    {
    }


    // returns an equivalent replica of the molecule
    public Molecule Clone()
    {
    	Molecule mol=new Molecule();
	for( int n=1;n<=NumAtoms();n++)
	{
	    Atom a=atoms.get(n-1);
	    int num=mol.AddAtom(a.Element,a.X,a.Y,a.Charge,a.Unpaired);
	    mol.SetAtomHExplicit(num,AtomHExplicit(n));
	    mol.SetAtomMapNum(num,AtomMapNum(n));
	}
	for( int n=1;n<=NumBonds();n++)
	{
	    Bond b=bonds.get(n-1);
	    mol.AddBond(b.From,b.To,b.Order,b.Type);
	}
	return mol;
    }

    
    // ----- fetching information directly from the datastructures ----
        
    public int NumAtoms() {return atoms.size();}
    public int NumBonds() {return bonds.size();}
    
    public String AtomElement(int N) {return atoms.get(N-1).Element;}
    public double AtomX(int N) {return atoms.get(N-1).X;}
    public double AtomY(int N) {return atoms.get(N-1).Y;}
    public int AtomCharge(int N) {return atoms.get(N-1).Charge;}
    public int AtomUnpaired(int N) {return atoms.get(N-1).Unpaired;}
    public int AtomHExplicit(int N) {return atoms.get(N-1).HExplicit;}
    public int AtomMapNum(int N) {return atoms.get(N-1).MapNum;}
    
    public int BondFrom(int N) {return bonds.get(N-1).From;}
    public int BondTo(int N) {return bonds.get(N-1).To;}
    public int BondOrder(int N) {return bonds.get(N-1).Order;}
    public int BondType(int N) {return bonds.get(N-1).Type;}
    
    // ----- modifying information in the datastructures ----

    // adds an atom to the end of the molecule; it is fairly reasonable to assume that the new one will be at position==NumAtoms(),
    // and that all other atoms will be in the same places, but the position is returned for convenience
    public int AddAtom(String Element,double X,double Y) {return AddAtom(Element,X,Y,0,0);}
    public int AddAtom(String Element,double X,double Y,int Charge,int Unpaired)
    {
    	if( X<minX || NumAtoms()==0) minX=X;
	if( X>maxX || NumAtoms()==0) maxX=X;
	if( Y<minY || NumAtoms()==0) minY=Y;
	if( Y>maxY || NumAtoms()==0) maxY=Y;
	
    	Atom a=new Atom();
	a.Element=Element;
	a.X=X;
	a.Y=Y;
	a.Charge=Charge;
	a.Unpaired=Unpaired;
	a.HExplicit=HEXPLICIT_UNKNOWN;
	atoms.add(a);
	TrashGraph();
    	return atoms.size();
    }
    public void SetAtomElement(int N,String Element) {atoms.get(N-1).Element=Element; TrashPriority();}
    public void SetAtomPos(int N,double X,double Y) 
    {
    	atoms.get(N-1).X=X; 
	atoms.get(N-1).Y=Y;
	invalMinMax=true;
	TrashStereo();
    }
    public void SetAtomCharge(int N,int Charge) {atoms.get(N-1).Charge=Charge; TrashPriority();}
    public void SetAtomUnpaired(int N,int Unpaired) {atoms.get(N-1).Unpaired=Unpaired; TrashPriority();}
    public void SetAtomHExplicit(int N,int HExplicit) {atoms.get(N-1).HExplicit=HExplicit; TrashPriority();}
    public void SetAtomMapNum(int N,int MapNum) {atoms.get(N-1).MapNum=MapNum;}
    
    // adds an atom the end of the molecule; the position of the new bond is returned for convenience
    public int AddBond(int From,int To,int Order) {return AddBond(From,To,Order,BONDTYPE_NORMAL);}
    public int AddBond(int From,int To,int Order,int Type)
    {
    	Bond b=new Bond();
	b.From=From;
	b.To=To;
	b.Order=Order;
	b.Type=Type;
	bonds.add(b);
	TrashGraph();
	return bonds.size();
    }
    
    public void SetBondFromTo(int N,int From,int To) 
    {
    	bonds.get(N-1).From=From; 
	bonds.get(N-1).To=To;
	TrashGraph();
    }
    public void SetBondOrder(int N,int Order) {bonds.get(N-1).Order=Order; TrashPriority();}
    public void SetBondType(int N,int Type) {bonds.get(N-1).Type=Type; TrashStereo();}
    
    // deletes the indicated atom, and also any bonds which were connected to it
    public void DeleteAtomAndBonds(int N)
    {
    	for( int n=0;n<NumBonds();)
	{
	    Bond b=bonds.get(n);
	    if( b.From==N || b.To==N) bonds.remove(n);
	    else
	    {
	    	if( b.From>N) b.From--;
		if( b.To>N) b.To--;
		n++;
	    }
	}
	atoms.remove(N-1);
	invalMinMax=true;
	TrashGraph();
    }
    public void DeleteBond(int N)
    {
    	bonds.remove(N-1);
	TrashGraph();
    }
     
    // ----- fetching information which is computed from the underlying data, usually cached -----
     
    public double MinX() {if( invalMinMax) DetermineMinMax(); return minX;}
    public double MaxX() {if( invalMinMax) DetermineMinMax(); return maxX;}
    public double MinY() {if( invalMinMax) DetermineMinMax(); return minY;}
    public double MaxY() {if( invalMinMax) DetermineMinMax(); return maxY;}
    public double RangeX() {return maxX-minX;}
    public double RangeY() {return maxY-minY;}
    
    // return the index of the bond, if any, which connects the two indicated atoms
    public int FindBond(int A1,int A2)
    {
    	for( int n=1;n<=NumBonds();n++) 
	{
	    if( BondFrom(n)==A1 && BondTo(n)==A2) return n;
	    if( BondTo(n)==A1 && BondFrom(n)==A2) return n;
	}
	return 0;
    }

    // for a bond, returns the end which is not==Ref; return value will be From,To or 0    
    public int BondOther(int N,int Ref)
    {
    	if( BondFrom(N)==Ref) return BondTo(N);
	if( BondTo(N)==Ref) return BondFrom(N);
	return 0;
    }

    // returns whether an atom logically ought to be drawn "explicitly";if false, it is a carbon which should be just a dot
    public boolean AtomExplicit(int N) 
    {
    	if( atoms.get(N-1).Element.compareTo("C")!=0 || atoms.get(N-1).Charge!=0 || atoms.get(N-1).Unpaired!=0) return true;
	for( int n=0;n<bonds.size();n++) if( bonds.get(n).From==N || bonds.get(n).To==N) return false;
	return true;
    }
    
    // uses either explicit or computed number to determine how many hydrogens the atom has; the field for explicit hydrogens takes
    // absolute preference, if it has its default value of 'unknown', the number is computed by looking up the hydrogen capacity for
    // the element (most of which are zero), subtracting the total of bond orders, then returning the difference, or zero; the calculation
    // tends to err on the side of too few, since the concept is just an aid to drawing organic structures, not a cheminformatic attempt
    // to compensate for 2 1/2 decades of bad file formats
    // (note: returns "implicit"+"explicit", but does NOT count "actual" hydrogens, i.e. those which have their own atom nodes)
    public int AtomHydrogens(int N) 
    {
    	int hy=AtomHExplicit(N);
	if( hy!=HEXPLICIT_UNKNOWN) return hy;
	for( int n=0;n<HYVALENCE_EL.length;n++) if( HYVALENCE_EL[n].compareTo(AtomElement(N))==0) {hy=HYVALENCE_VAL[n]; break;}
	if( hy==HEXPLICIT_UNKNOWN) return 0;
	int ch=AtomCharge(N);
	if( AtomElement(N).compareTo("C")==0) ch=-Math.abs(ch);
	hy+=ch-AtomUnpaired(N);
	for( int n=1;n<=NumBonds();n++) if( BondFrom(n)==N || BondTo(n)==N) hy-=BondOrder(n);
	return hy<0 ? 0 : hy;
    }
     
    // returns the numerical ID of the ring block in which the atom resides, or 0 if it is not in a ring   
    public int AtomRingBlock(int N)
    {
    	if( graph==null) BuildGraph();
	if( ringID==null) BuildRingID();
    	return ringID[N-1];
    }
    // returns whether or not a bond resides in a ring (i.e. ring block of each end is the same and nonzero)
    public boolean BondInRing(int N)
    {
    	int r1=AtomRingBlock(BondFrom(N)),r2=AtomRingBlock(BondTo(N));
    	return r1>0 && r1==r2;
    }
    
    // returns the connected component ID of the atom, always 1 or more
    public int AtomConnComp(int N)
    {
    	if( graph==null) BuildGraph();
    	if( compID==null) BuildConnComp();
	return compID[N-1];
    }
    
    // returns the number of neighbours of an atom
    public int AtomAdjCount(int N)
    {
    	if( graph==null) BuildGraph();
	return graph[N-1].length;
    }
    
    // returns the actual adjacency list of an atom; unfortunately this has to make a clone of the array, since the numbers are converted
    // to 1-based indices, and we would not want callers modifying it anyway
    public int[] AtomAdjList(int N)
    {
    	if( graph==null) BuildGraph();
	int[] adj=graph[N-1].clone();
	for( int n=0;n<adj.length;n++) adj[n]++;
	return adj;
    }
    
    // returns atom-based priority according to the Cahn-Ingold-Prelog rules
    public int AtomPriority(int N)
    {
    	if( graph==null) BuildGraph();
    	if( compID==null) BuildConnComp();
	if( priority==null) BuildPriority();
	return priority[N-1];
    }
    
    // return the tetrahedral chirality of the given atom
    public int AtomChirality(int N)
    {
    	if( graph==null) BuildGraph();
    	if( compID==null) BuildConnComp();
	if( priority==null) BuildPriority();
    	if( chiral==null) BuildChirality();
	return chiral[N-1];
    }
    
    // return the cis/trans style stereochemistry of the given bond
    public int BondStereo(int N)
    {
    	if( graph==null) BuildGraph();
    	if( compID==null) BuildConnComp();
	if( priority==null) BuildPriority();
    	if( cistrans==null) BuildCisTrans();
	return cistrans[N-1];
    }
    
    // returns _all_ rings of indicated size; each item in the array list is an array of int[Size], a consecutively ordered array of atom 
    // numbers; uses a recursive depth first search, which must be bounded above by Size being small in order to avoid exponential blowup
    public int[][] FindRingSize(int Size) 
    {
    	ArrayList<Object> rings=null;
    	if( Size==5 && ring5!=null) rings=ring5;
	if( Size==6 && ring6!=null) rings=ring6;
	if( Size==7 && ring7!=null) rings=ring7;
    
    	if( rings==null)
	{
    	    if( graph==null) BuildGraph();
	    if( ringID==null) BuildRingID();

	    rings=new ArrayList<Object>();
	    for( int n=1;n<=NumAtoms();n++) if( ringID[n-1]>0) 
	    {
		int path[]=new int[Size];
		path[0]=n;
		RecursiveRingFind(path,1,Size,ringID[n-1],rings);
	    }

	    if( Size==5) ring5=rings;
	    if( Size==6) ring6=rings;
	    if( Size==7) ring7=rings;
	}
	
	int ret[][]=new int[rings.size()][];
	for( int n=0;n<rings.size();n++) ret[n]=((int[])rings.get(n)).clone();
	return ret;
    }
    
    // compare to another molecule instance; null is equivalent to empty; return values:
    //     -1 if Mol < Other
    //	    0 if Mol == Other
    //	    1 if Mol > Other 
    //  can be used to sort molecules, albeit crudely; does not do any kind of canonical preprocessing
    public int CompareTo(Molecule Other)
    {
    	if( Other==null) return NumAtoms()==0 ? 0 : 1; // null is equivalent to empty
	if( NumAtoms()<Other.NumAtoms()) return -1;
	if( NumAtoms()>Other.NumAtoms()) return 1;
	if( NumBonds()<Other.NumBonds()) return -1;
	if( NumBonds()>Other.NumBonds()) return 1;
	
	for( int n=1;n<=NumAtoms();n++)
	{
	    int c=AtomElement(n).compareTo(Other.AtomElement(n));
	    if( c!=0) return c;
	    if( AtomX(n)<Other.AtomX(n)) return -1; if( AtomX(n)>Other.AtomX(n)) return 1;
	    if( AtomY(n)<Other.AtomY(n)) return -1; if( AtomY(n)>Other.AtomY(n)) return 1;
	    if( AtomCharge(n)<Other.AtomCharge(n)) return -1; if( AtomCharge(n)>Other.AtomCharge(n)) return 1;
	    if( AtomUnpaired(n)<Other.AtomUnpaired(n)) return -1; if( AtomUnpaired(n)>Other.AtomUnpaired(n)) return 1;
	    if( AtomHExplicit(n)<Other.AtomHExplicit(n)) return -1; if( AtomHExplicit(n)>Other.AtomHExplicit(n)) return 1;
 	}
	for( int n=1;n<=NumBonds();n++)
	{
	    if( BondFrom(n)<Other.BondFrom(n)) return -1; if( BondFrom(n)>Other.BondFrom(n)) return 1;
	    if( BondTo(n)<Other.BondTo(n)) return -1; if( BondTo(n)>Other.BondTo(n)) return 1;
	    if( BondOrder(n)<Other.BondOrder(n)) return -1; if( BondOrder(n)>Other.BondOrder(n)) return 1;
	    if( BondType(n)<Other.BondType(n)) return -1; if( BondType(n)>Other.BondType(n)) return 1;
 	}
	
    	return 0;
    }

    // lookup the atomic number for the element, or return 0 if not in the periodic table
    int AtomicNumber(int N) {return AtomicNumber(AtomElement(N));}
    int AtomicNumber(String El)
    {
    	for( int n=1;n<ELEMENTS.length;n++) if( ELEMENTS[n].compareTo(El)==0) return n;
	return 0;
    }

    // takes the indicated molecular fragment and appends it to the end of the current molecule, with order preserved
    public void Append(Molecule Frag)
    {
	int base=NumAtoms();
	for( int n=1;n<=Frag.NumAtoms();n++)
	{
	    int num=AddAtom(Frag.AtomElement(n),Frag.AtomX(n),Frag.AtomY(n),Frag.AtomCharge(n),Frag.AtomUnpaired(n));
	    SetAtomHExplicit(num,Frag.AtomHExplicit(n));
	    SetAtomMapNum(num,Frag.AtomMapNum(n));
	}
	for( int n=1;n<=Frag.NumBonds();n++)
	{
	    AddBond(Frag.BondFrom(n)+base,Frag.BondTo(n)+base,Frag.BondOrder(n),Frag.BondType(n));
	}
    }

    // returns a molecule which is smaller than the current one, according to the mask (which must be of size #atoms); boundary cases
    // are a null molecule or cloned copy
    public Molecule Subgraph(boolean[] Mask)
    {
	int[] invidx=new int[NumAtoms()];
	int sum=0;
	for( int n=0;n<NumAtoms();n++) if( Mask[n]) invidx[n]=++sum; else invidx[n]=0;
	if( sum==0) return new Molecule();
	if( sum==NumAtoms()) return Clone();
	
	Molecule frag=new Molecule();
	for( int n=1;n<=NumAtoms();n++) if( Mask[n-1])
	{
	    int num=frag.AddAtom(AtomElement(n),AtomX(n),AtomY(n),AtomCharge(n),AtomUnpaired(n));
	    frag.SetAtomHExplicit(num,AtomHExplicit(n));
	    frag.SetAtomMapNum(num,AtomMapNum(n));
	}
	for( int n=1;n<=NumBonds();n++) 
	{
	    int from=invidx[BondFrom(n)-1],to=invidx[BondTo(n)-1];
	    if( from>0 && to>0) frag.AddBond(from,to,BondOrder(n),BondType(n));
	}
	
	return frag;
    }

    
    // convenient debugging mechanism
    public void Dump()
    {
    	System.out.println("#Atoms="+NumAtoms()+" #Bonds="+NumBonds());
	for( int n=0;n<NumAtoms();n++)
	{
	    Atom a=atoms.get(n);
	    System.out.println(" A"+(n+1)+": "+a.Element+"="+a.X+","+a.Y+";"+a.Charge+","+a.Unpaired);
	}
	for( int n=0;n<NumBonds();n++)
	{
	    Bond b=bonds.get(n);
	    System.out.println(" B"+(n+1)+": "+b.From+"-"+b.To+"="+b.Order+","+b.Type);
	}
    }

    // ------------------ private functions --------------------
    
    // for when the connectivity changes somehow; abandon graph properties
    void TrashGraph()
    {
    	graph=null;
	ringID=null;
	ring5=null;
	ring6=null;
	ring7=null;
	compID=null;
	TrashPriority();
    }
    void TrashPriority() 
    {
    	priority=null;
	TrashStereo();
    }
    void TrashStereo()
    {
	chiral=null;
	cistrans=null;
    }
    
    // update the cache of atom range
    void DetermineMinMax()
    {
    	invalMinMax=false;
	if( NumAtoms()==0) 
	{
	    minX=maxX=minY=maxY=0; 
	    return;
	}
    	minX=maxX=AtomX(1);
	minY=maxY=AtomY(1);
	for( int n=2;n<=NumAtoms();n++)
	{
	    double x=AtomX(n),y=AtomY(n);
	    minX=Math.min(minX,x);
	    maxX=Math.max(maxX,x);
	    minY=Math.min(minY,y);
	    maxY=Math.max(maxY,y);
	}
    }

    // update the cache of the molecular graph, in adjacency format, rather than the edge list format; the former is much better for
    // graph algorithms, the latter much more suited to capturing sketcher-ish information content; note that the graph indices are
    // zero-based
    void BuildGraph()
    {
    	graph=new int[NumAtoms()][];
	for( int n=1;n<=NumBonds();n++)
	{
	    int bf=BondFrom(n)-1,bt=BondTo(n)-1;
	    if( bf==bt) continue; // ouch!
	    int lf=graph[bf]==null ? 0 : graph[bf].length,lt=graph[bt]==null ? 0 : graph[bt].length;
	    int bl[]=new int[lf+1];
	    for( int i=0;i<lf;i++) bl[i]=graph[bf][i];
	    bl[lf]=bt;
	    graph[bf]=bl;
	    bl=new int[lt+1];
	    for( int i=0;i<lt;i++) bl[i]=graph[bt][i];
	    bl[lt]=bf;
	    graph[bt]=bl;
	}
	for( int n=0;n<NumAtoms();n++) if( graph[n]==null) graph[n]=new int[0];
	
	/*for( int n=0;n<NumAtoms();n++) 
	{
	    System.out.print("#"+n+":");
	    for( int i=0;i<graph[n].length;i++) System.out.print(" "+graph[n][i]);
	    System.out.println();
	}*/
    }
    
    // passes over the graph establishing which component each atom belongs to
    void BuildConnComp()
    {
    	compID=new int[NumAtoms()];
	for( int n=0;n<NumAtoms();n++) compID[n]=0;
	int comp=1;
	compID[0]=comp;

    	// (not very efficient, should use a stack-based depth first search)
	while (true)
	{
	    boolean anything=false;
	    for( int n=0;n<NumAtoms();n++) if( compID[n]>0)
	    {
	    	for( int i=0;i<graph[n].length;i++) if( compID[graph[n][i]]==0)
		{
		    compID[graph[n][i]]=comp;
		    anything=true;
		}
	    }
	    
	    if( !anything)
	    {
	    	for( int n=0;n<NumAtoms();n++) if( compID[n]==0) {compID[n]=++comp; anything=true; break;}
		if( !anything) break;
	    }
	}
    }

    // generates Cahn-Ingold-Prelog priority for each atom, where degeneracies are indicated by having the same number
    void BuildPriority()
    {
    	// build a graph representation which has entries replicated according to bond order
    	int cipgr[][]=new int[NumAtoms()][];
	for( int n=0;n<NumAtoms();n++) if( cipgr[n]==null) 
	{
	    cipgr[n]=new int[AtomHydrogens(n+1)];
	    for( int i=0;i<cipgr[n].length;i++) cipgr[n][i]=-1;
	}
	for( int n=1;n<=NumBonds();n++)
	{
	    int bf=BondFrom(n)-1,bt=BondTo(n)-1,bo=BondOrder(n);
	    if( bf==bt || bo==0) continue;
	    int lf=cipgr[bf].length,lt=cipgr[bt].length;
	    int bl[]=new int[lf+bo];
	    for( int i=0;i<lf;i++) bl[i]=cipgr[bf][i];
	    for( int i=0;i<bo;i++) bl[lf++]=bt;
	    cipgr[bf]=bl;
	    bl=new int[lt+bo];
	    for( int i=0;i<lt;i++) bl[i]=cipgr[bt][i];
	    for( int i=0;i<bo;i++) bl[lt++]=bf;
	    cipgr[bt]=bl;
	}

    	// seed the priorities with atomic number
    	priority=new int[NumAtoms()];
	boolean anyActualH=false;
	for( int n=0;n<NumAtoms();n++) {priority[n]=AtomicNumber(n+1); if( priority[n]==1) anyActualH=true;}
	
	// pass through and reassign priorities as many times as necessary, until no change
	int prigr[][]=new int[NumAtoms()][];
	while (true)
	{
	    // make an equivalent to cipgr which has priorities instead of indices
	    for( int n=0;n<NumAtoms();n++) 
	    {
	    	prigr[n]=new int[cipgr[n].length];
		for( int i=0;i<prigr[n].length;i++) if( cipgr[n][i]<0) prigr[n][i]=1; else prigr[n][i]=priority[cipgr[n][i]];
		int p=0;
		while (p<prigr[n].length-1)
		{
		    if( prigr[n][p]<prigr[n][p+1]) {
		    	int i=prigr[n][p]; prigr[n][p]=prigr[n][p+1]; prigr[n][p+1]=i;
			if( p>0) p--;
		    } else p++;
		}
	    }
	    
	    // divide each priority category into groups, then for each of these groups, split the contents out and reassign
	    int groups[][]=SortAndGroup(priority);
    	    int nextpri=anyActualH ? 0 : 1;
    	    boolean repartitioned=false;
	    
	    for( int n=0;n<groups.length;n++)
	    {
	    	// sort the groups according to their cipgr contents
	    	int p=0;
		while (p<groups[n].length-1)
		{
		    int i1=groups[n][p],i2=groups[n][p+1];
		    int cmp=0,sz=Math.max(prigr[i1].length,prigr[i2].length);
		    for( int i=0;i<sz;i++)
		    {
		    	int v1=i<prigr[i1].length ? prigr[i1][i] : 0,v2=i<prigr[i2].length ? prigr[i2][i] : 0;
    	    	    	if( v1<v2) {cmp=-1; break;}
    	    	    	if( v1>v2) {cmp=1; break;}
		    }
		    if( cmp>0) {groups[n][p]=i2; groups[n][p+1]=i1; if( p>0) p--;}
		    else p++;
		}
		
		for( int i=0;i<groups[n].length;i++) 
		{
		    if( i==0) nextpri++;
		    else if( prigr[groups[n][i]].length!=prigr[groups[n][i-1]].length) {nextpri++; repartitioned=true;}
		    else
		    {
		    	for( int j=0;j<prigr[groups[n][i]].length;j++) 
			    if( prigr[groups[n][i]][j]!=prigr[groups[n][i-1]][j]) {nextpri++; repartitioned=true; break;}
		    }
		    
		    priority[groups[n][i]]=nextpri;
		}
	    }

    	    if( !repartitioned) break;
	}
    }

    // compute the chirality values for each atom centre
    void BuildChirality()
    {
    	chiral=new int[NumAtoms()];
	
	boolean haswedge[]=new boolean[NumAtoms()];
	for( int n=0;n<NumAtoms();n++) haswedge[n]=false;
	for( int n=1;n<=NumBonds();n++) if( BondType(n)==BONDTYPE_INCLINED || BondType(n)==BONDTYPE_DECLINED) haswedge[BondFrom(n)-1]=true;
	
	int pri[]=new int[4];
	double x[]=new double[4],y[]=new double[4],z[]=new double[4];
	
	for( int n=0;n<NumAtoms();n++)
	{
	    chiral[n]=STEREO_NONE;
	    if( !(graph[n].length==4 || (graph[n].length==3 && AtomHydrogens(n+1)==1))) continue;

	    for( int i=0;i<graph[n].length;i++)
	    {
	    	pri[i]=priority[graph[n][i]];
		x[i]=AtomX(graph[n][i]+1)-AtomX(n+1);
		y[i]=AtomY(graph[n][i]+1)-AtomY(n+1);
		z[i]=0;
		if( haswedge[n]) 
		    for( int j=1;j<=NumBonds();j++) if( BondFrom(j)==n+1 && BondTo(j)==graph[n][i]+1)
		{
		    if( BondType(j)==BONDTYPE_INCLINED) z[i]=1;
		    if( BondType(j)==BONDTYPE_DECLINED) z[i]=-1;
		    break;
		}
	    }
	    if( graph[n].length==3) {pri[3]=0; x[3]=0; y[3]=0; z[3]=0;}
	    
	    int p=0;
	    while (p<3) 
	    {
	    	if( pri[p]>pri[p+1])
		{
		    int i; double d;
		    i=pri[p]; pri[p]=pri[p+1]; pri[p+1]=i;
		    d=x[p]; x[p]=x[p+1]; x[p+1]=d;
		    d=y[p]; y[p]=y[p+1]; y[p+1]=d;
		    d=z[p]; z[p]=z[p+1]; z[p+1]=d;
		    if( p>0) p--;
		}
		else p++;
	    }
	    if( (pri[0]==0 && pri[1]==1) || pri[0]==pri[1] || pri[1]==pri[2] || pri[2]==pri[3]) continue; // no topological chirality
	    
	    chiral[n]=STEREO_UNKNOWN;
	    if( z[0]==0 && z[1]==0 && z[2]==0 && z[3]==0) continue; // all atoms are in-plane
	    
	    boolean sane=true;
	    for( int i=0;i<4;i++) if( pri[0]!=0)
	    {
	    	double r=x[i]*x[i]+y[i]*y[i]+z[i]*z[i];
		if( r<0.01*0.01) {sane=false; break;}
		r=1/Math.sqrt(r);
		x[i]=x[i]*r; y[i]=y[i]*r; z[i]=z[i]*r;
	    }
	    if( !sane) continue;
	    
	    if( pri[0]==0) // build a position for the implicit H
	    {
	    	x[0]=-(x[1]+x[2]+x[3]);
	    	y[0]=-(y[1]+y[2]+y[3]);
	    	z[0]=-(z[1]+z[2]+z[3]);
	    	double r=x[0]*x[0]+y[0]*y[0]+z[0]*z[0];
		if( r<0.01*0.01) {sane=false; break;}
		r=1/Math.sqrt(r);
		x[0]=x[0]*r; y[0]=y[0]*r; z[0]=z[0]*r;
	    }
	    if( !sane) continue;
	    
	    double R=0,S=0;
	    for( int i=1;i<=6;i++)
	    {
	    	int a=0,b=0;
		if      (i==1) {a=1; b=2;} else if( i==2) {a=2; b=3;} else if( i==3) {a=3; b=1;}
		else if( i==4) {a=2; b=1;} else if( i==5) {a=3; b=2;} else if( i==6) {a=1; b=3;}
		double xx=y[a]*z[b]-y[b]*z[a] - x[0];
		double yy=z[a]*x[b]-z[b]*x[a] - y[0];
		double zz=x[a]*y[b]-x[b]*y[a] - z[0];
		if( i<=3) R+=xx*xx+yy*yy+zz*zz; else S+=xx*xx+yy*yy+zz*zz;
	    }
	    chiral[n]=R>S ? STEREO_POS : STEREO_NEG;
	}
    }
    
    // computer the cis/trans stereochemistry for each bond
    void BuildCisTrans()
    {
    	cistrans=new int[NumBonds()];
	int sf[]=new int[2],st[]=new int[2];
	
	for( int n=0;n<NumBonds();n++) 
	{
	    cistrans[n]=STEREO_NONE;
	    int bf=BondFrom(n+1)-1,bt=BondTo(n+1)-1;
	    if( BondOrder(n+1)!=2 || graph[bf].length<=1 || graph[bt].length<= 1 || graph[bf].length>3 || graph[bt].length>3) continue;

    	    int nf=0,nt=0;
    	    for( int i=0;i<graph[bf].length;i++) if( graph[bf][i]!=bt) sf[nf++]=graph[bf][i];
    	    for( int i=0;i<graph[bt].length;i++) if( graph[bt][i]!=bf) st[nt++]=graph[bt][i];

    	    if( nf==1) {if( AtomHydrogens(bf+1)!=1 || priority[sf[0]]==1) continue;}
	    else 
	    {
	    	if( priority[sf[0]]==priority[sf[1]]) continue;
		if( priority[sf[0]]<priority[sf[1]]) {int i=sf[0]; sf[0]=sf[1]; sf[1]=i;}
	    }
	    
    	    if( nt==1) {if( AtomHydrogens(bt+1)!=1 || priority[st[0]]==1) continue;}
	    else 
	    {
	    	if( priority[st[0]]==priority[st[1]]) continue;
		if( priority[st[0]]<priority[st[1]]) {int i=st[0]; st[0]=st[1]; st[1]=i;}
	    }
	
	    cistrans[n]=STEREO_UNKNOWN;

	    double xa=AtomX(bf+1),ya=AtomY(bf+1),xb=AtomX(bt+1),yb=AtomY(bt+1);
    	    double tha0=Math.atan2(yb-ya,xb-xa),thb0=Math.PI+tha0;
    	    double tha1=Math.atan2(AtomY(sf[0]+1)-ya,AtomX(sf[0]+1)-xa);
    	    double tha2=nf==2 ? Math.atan2(AtomY(sf[1]+1)-ya,AtomX(sf[1]+1)-xa) : ThetaObtuse(tha0,tha1);
    	    double thb1=Math.atan2(AtomY(st[0]+1)-yb,AtomX(st[0]+1)-xb);
    	    double thb2=nt==2 ? Math.atan2(AtomY(st[1]+1)-yb,AtomX(st[1]+1)-xb) : ThetaObtuse(thb0,thb1);
	    tha1-=tha0; tha2-=tha0; thb1-=thb0; thb2-=thb0;
	    tha1+=(tha1<-Math.PI ? 2*Math.PI : 0)+(tha1>Math.PI ? -2*Math.PI : 0);
	    tha2+=(tha2<-Math.PI ? 2*Math.PI : 0)+(tha2>Math.PI ? -2*Math.PI : 0);
	    thb1+=(thb1<-Math.PI ? 2*Math.PI : 0)+(thb1>Math.PI ? -2*Math.PI : 0);
	    thb2+=(thb2<-Math.PI ? 2*Math.PI : 0)+(thb2>Math.PI ? -2*Math.PI : 0);

    	    final double SMALL=5*Math.PI/180; // basically colinear
    	    if( Math.abs(tha1)<SMALL || Math.abs(tha2)<SMALL || Math.abs(thb1)<SMALL || Math.abs(thb2)<SMALL) continue;
    	    if( Math.abs(tha1)>Math.PI-SMALL || Math.abs(tha2)>Math.PI-SMALL) continue;
    	    if( Math.abs(thb1)>Math.PI-SMALL || Math.abs(thb2)>Math.PI-SMALL) continue;
	    tha1=Math.signum(tha1); tha2=Math.signum(tha2); thb1=Math.signum(thb1); thb2=Math.signum(thb2);
	    if( tha1==tha2 || thb1==thb2) continue;
	    if( tha1*thb1<0) cistrans[n]=STEREO_POS;
	    if( tha1*thb1>0) cistrans[n]=STEREO_NEG;
	}
    }

    // generally useful function which takes a list of numbers and sorts them, then bins the unique values into sub-arrays
    // (note: inefficient implementation, but could be improved easily enough)
    public static int[][] SortAndGroup(int[] Val)
    {
    	ArrayList<Integer> unique=new ArrayList<Integer>();
	for( int n=0;n<Val.length;n++) unique.add(Val[n]);
    	Collections.sort(unique);
	int p=0;
	while (p<unique.size()-1)
	{
	    if( unique.get(p)==unique.get(p+1)) unique.remove(p); else p++;
	}

	int ret[][]=new int[unique.size()][];
	
	for( int n=0;n<Val.length;n++)
	{
	    int grp=unique.indexOf(Val[n]);
	    int[] cnt=new int[ret[grp]==null ? 1 : ret[grp].length+1];
	    for( int i=0;i<cnt.length-1;i++) cnt[i]=ret[grp][i];
	    cnt[cnt.length-1]=n;
	    ret[grp]=cnt;
	}
	
	return ret;
    }

    // update the ring-block-identifier for each atom
    void BuildRingID()
    {
    	ringID=new int[NumAtoms()];
	if( NumAtoms()==0) return;
	boolean visited[]=new boolean[NumAtoms()];
	for( int n=0;n<NumAtoms();n++) 
	{
    	    ringID[n]=0;
	    visited[n]=false;
	}

	int path[]=new int[NumAtoms()+1],plen=0,numVisited=0;
	boolean rewound=false;
	while (true)
	{
	    int last,current;

	    if( plen==0) // find an element of a new component to visit
	    {
	    	last=-1;
	    	for( current=0;visited[current];current++) {}
	    }
	    else
	    {
	    	last=path[plen-1];
	    	current=-1;
	    	for( int n=0;n<graph[last].length;n++) if( !visited[graph[last][n]]) {current=graph[last][n]; break;}
	    }
	    
	    /*System.out.print("numVisited="+numVisited+" last="+last+" current="+current+" path=");
	    for( int n=0;n<plen;n++) System.out.print(path[n]+" ");
	    System.out.println();*/
	    
    	    if( current>=0 && plen>=2) // path is at least 2 items long, so look for any not-previous visited neighbours
	    {
	    	int back=path[plen-1];
    	    	//System.out.println(" back="+back);
		for( int n=0;n<graph[current].length;n++) 
		{
		    int join=graph[current][n];
		    //System.out.println(" join="+join+" visited[join]="+visited[join]);
		    if( join!=back && visited[join])
		    {
			//System.out.print(" path:");

    	    	    	path[plen]=current;
			for( int i=plen;i==plen || path[i+1]!=join;i--)
			{
		    	    //System.out.print(" "+path[i]);

			    int id=ringID[path[i]];
			    if( id==0) ringID[path[i]]=last;
			    else if( id!=last)
			    {
				for( int j=0;j<NumAtoms();j++) if( ringID[j]==id) ringID[j]=last;
			    }
			}
			//System.out.println();
		    }
		}
	    }
	    if( current>=0)  // can mark the new one as visited
	    {
	    	visited[current]=true;
		path[plen++]=current;
		numVisited++;
		rewound=false;
	    }
	    else // otherwise, found nothing and must rewind the path
	    {
	    	plen--;
	    	rewound=true;
	    }
	    
	    if( numVisited==NumAtoms()) break;
	}
	
	// the ring ID's are not necessarily consecutive, so reassign them to 0=none, 1..NBlocks
	int nextID=0;
	for( int i=0;i<NumAtoms();i++) if( ringID[i]>0)
	{
	    nextID--;
	    for( int j=NumAtoms()-1;j>=i;j--) if( ringID[j]==ringID[i]) ringID[j]=nextID;
	}
	for( int i=0;i<NumAtoms();i++) ringID[i]=-ringID[i];
    }
    
    // ring hunter: recursive step; finds, compares and collects
    void RecursiveRingFind(int[] Path,int PSize,int Capacity,int RBlk,ArrayList<Object> Rings)
    {
    	// not enough atoms yet, so look for new possibilities
    	if( PSize<Capacity)
	{
	    int last=Path[PSize-1];
	    for( int n=0;n<graph[last-1].length;n++)
	    {
	    	int adj=graph[last-1][n]+1;
		if( ringID[adj-1]!=RBlk) continue;
	    	boolean fnd=false;
		for( int i=0;i<PSize;i++) if( Path[i]==adj) {fnd=true; break;}
		if( !fnd)
		{
		    int newPath[]=Path.clone();
		    newPath[PSize]=adj;
		    RecursiveRingFind(newPath,PSize+1,Capacity,RBlk,Rings);
		}
	    }
	    return;
	}
	
	// path is full, so make sure it eats its tail
	int last=Path[PSize-1];
	boolean fnd=false;
	for( int n=0;n<graph[last-1].length;n++) if( graph[last-1][n]+1==Path[0]) {fnd=true; break;}
	if( !fnd) return;
	
	// reorder the array then look for duplicates
	int first=0;
	for( int n=1;n<PSize;n++) if( Path[n]<Path[first]) first=n;
	int fm=(first-1+PSize)%PSize,fp=(first+1)%PSize;
	boolean flip=Path[fm]<Path[fp];
	if( first!=0 || flip)
	{
	    int newPath[]=new int[PSize];
	    for( int n=0;n<PSize;n++) newPath[n]=Path[(first+(flip ? PSize-n : n))%PSize];
	    Path=newPath;
	}
		
	for( int n=0;n<Rings.size();n++)
	{
	    int[] look=(int[])Rings.get(n);
	    boolean same=true;
	    for( int i=0;i<PSize;i++) if( look[i]!=Path[i]) {same=false; break;}
	    if( same) return;
	}
	
	Rings.add(Path);
    }
    
    // returns the angle maximally equidistant from Th1 and Th2
    double ThetaObtuse(double Th1,double Th2)
    {
    	double dth=Th2-Th1;
	while (dth<-Math.PI) dth+=2*Math.PI;
	while (dth>Math.PI) dth-=2*Math.PI;
	return dth>0 ? Th1-0.5*(2*Math.PI-dth) : Th1+0.5*(2*Math.PI+dth);
    }
    
    
    public void RotateMolecule(double Degrees){
	Degrees=MainApplet.rotation;
	System.out.println("rotating..."+Degrees+" degrees");
	double dist;
	double dx;
	double dy;
	double theta;
	double radians=(double)(Degrees*Math.PI/180);
	System.out.println("num atoms= "+NumAtoms());
	for(int n=1;n<=NumAtoms();n++){ 
	    dx=AtomX(n);
	    dy=AtomY(n);
	    dist=Math.sqrt(dx*dx+dy*dy);
	    theta=Math.atan2(dy,dx);
	    try{
		SetAtomPos(n,dist*Math.cos(theta+radians),dist*Math.sin(theta+radians));
	    }
	    catch(Exception e){System.out.println("problem with rotation "+e);}
	}
    }
}
