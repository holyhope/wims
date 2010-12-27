/*
    Sketch Elements: Chemistry molecular diagram drawing tool.
    
    (c) 2005 Dr. Alex M. Clark
    
    Released as GNUware, under the Gnu Public License (GPL)
    
    See www.gnu.org for details.
*/

package WIMSchem;

import java.util.*;
import java.io.*;
import java.text.*;
import java.lang.*;
import java.nio.channels.*;

/*
    Handles reading and writing of molecules to and from streams. Two formats are supported: native, which is a direct translation of
    the underlying data content; and a subset of MDL MOL, using only the fields that are relevant to WIMSchem.
*/

public class MoleculeStream{


    // special implementation of the reader for when the format is not known a-priori, or might be a combination-of-two formats
    // as used by the clipboard; do some extra work to try to pull out the WIMSchem file preferentially
    public static Molecule ReadUnknown(InputStream istr) throws IOException 
    {
    	return ReadUnknown(new BufferedReader(new InputStreamReader(istr)));
    }
    
    public static Molecule ReadUnknown(BufferedReader in) throws IOException
    {
    	Molecule mdlmol=null,elmol=null;
	final int BUFFMAX=100000;
	in.mark(BUFFMAX);
	try
	{
	    mdlmol=ReadMDLMOL(in);
	    if (mdlmol!=null) in.mark(BUFFMAX); // so the WIMSchem version could follow
	}
	catch (IOException e) 
	{
	    mdlmol=null;
	    in.reset();
	}
	
	try
	{
	    elmol=ReadNative(in);
	}
	catch (IOException e) {elmol=null;}
	
	if (elmol!=null) return elmol;
	if (mdlmol!=null) return mdlmol;
	
	throw new IOException("Unknown or invalid format.");
    }

    public static Molecule ReadNative(InputStream istr) throws IOException 
    {
    	return ReadNative(new BufferedReader(new InputStreamReader(istr)));
    }
    public static Molecule ReadNative(BufferedReader in) throws IOException
    {
    	Molecule mol=new Molecule();
	final String GENERIC_ERROR="Invalid WIMSchem file.";
	
	try
	{
	    String line=in.readLine();
	    if (!line.startsWith("WIMSchem!")) throw new IOException("Not a WIMSchem file.");
	    int p1=line.indexOf('('),p2=line.indexOf(','),p3=line.indexOf(')');
	    if (p1==0 || p2==0 || p3==0) throw new IOException(GENERIC_ERROR);
	
	    int numAtoms=Integer.parseInt(line.substring(p1+1,p2).trim());
	    int numBonds=Integer.parseInt(line.substring(p2+1,p3).trim());
	    for (int n=0;n<numAtoms;n++) 
	{
	    	line=in.readLine();
		String[] bits=line.split("[\\=\\,\\;]");
		if (bits.length<5) throw new IOException(GENERIC_ERROR);
		int num=mol.AddAtom(bits[0],Double.parseDouble(bits[1].trim()),Double.parseDouble(bits[2].trim()),
		    	    	    Integer.parseInt(bits[3].trim()),Integer.parseInt(bits[4].trim()));
    	    	for (int i=5;i<bits.length;i++) if (bits[i].length()>0)
		{
		    if (bits[i].charAt(0)=='e') mol.SetAtomHExplicit(num,Integer.parseInt(bits[i].substring(1)));
		    else if (bits[i].charAt(0)=='n') mol.SetAtomMapNum(num,Integer.parseInt(bits[i].substring(1)));
		}
	    }
	    for (int n=0;n<numBonds;n++)
	    {
	    	line=in.readLine();
		String[] bits=line.split("[\\-\\=\\,]");
		if (bits.length<4) throw new IOException(GENERIC_ERROR);
		mol.AddBond(Integer.parseInt(bits[0].trim()),Integer.parseInt(bits[1].trim()),
		    	    Integer.parseInt(bits[2].trim()),Integer.parseInt(bits[3].trim()));
	    }
	    line=in.readLine();
	    if (line.compareTo("!FIN")!=0) throw new IOException(GENERIC_ERROR);
	}
	catch (Exception e)
	{
	    throw new IOException(GENERIC_ERROR);
	}

    	return mol;
    }
    
    public static void WriteNative(OutputStream ostr,Molecule mol) throws IOException
    {
	WriteNative(new BufferedWriter(new OutputStreamWriter(ostr)),mol);
    }
    public static void WriteNative(BufferedWriter out,Molecule mol) throws IOException
    {
	DecimalFormat fmt=new DecimalFormat("0.0000",new DecimalFormatSymbols(Locale.US));

    	out.write("WIMSchem!("+mol.NumAtoms()+","+mol.NumBonds()+")\n");
	for (int n=1;n<=mol.NumAtoms();n++)
	{
	    String hy=mol.AtomHExplicit(n)!=Molecule.HEXPLICIT_UNKNOWN ? ("e"+mol.AtomHExplicit(n)) : ("i"+mol.AtomHydrogens(n));
	    out.write(mol.AtomElement(n)+"="+fmt.format(mol.AtomX(n))+","+fmt.format(mol.AtomY(n))+";"+
	    	    	    	    	    	    	    	    	mol.AtomCharge(n)+","+mol.AtomUnpaired(n)+","+hy);
    	    if (mol.AtomMapNum(n)>0) out.write(",n"+mol.AtomMapNum(n));
    	    out.write("\n");
	}
	for (int n=1;n<=mol.NumBonds();n++)
	{
	    out.write(mol.BondFrom(n)+"-"+mol.BondTo(n)+"="+mol.BondOrder(n)+","+mol.BondType(n)+"\n");
	}
	out.write("!FIN\n");
	
	out.flush();
    }

    // jm.evers
    // testing with a "convenient way to produce a "Native string" to be used as wims $variable in javascript. 
    public static void WriteNative2JavaScript(OutputStream ostr,Molecule mol) throws IOException {
	WriteNative2JavaScript(new BufferedWriter(new OutputStreamWriter(ostr)),mol);
    }
    public static void WriteNative2JavaScript(BufferedWriter out,Molecule mol) throws IOException {
    	DecimalFormat fmt=new DecimalFormat("0.0000",new DecimalFormatSymbols(Locale.US));
	
    	out.write("\"WIMSchem!("+mol.NumAtoms()+","+mol.NumBonds()+")\\n\"+");
	for (int n=1;n<=mol.NumAtoms();n++)
	{
	    String hy=mol.AtomHExplicit(n)!=Molecule.HEXPLICIT_UNKNOWN ? ("e"+mol.AtomHExplicit(n)) : ("i"+mol.AtomHydrogens(n));
	    out.write("\""+mol.AtomElement(n)+"="+fmt.format(mol.AtomX(n))+","+fmt.format(mol.AtomY(n))+";"+
	    	    	    	    	    	    	    	    	mol.AtomCharge(n)+","+mol.AtomUnpaired(n)+","+hy);
    	    if (mol.AtomMapNum(n)>0) out.write(",n"+mol.AtomMapNum(n));
    	    out.write("\\n\"+");
	}
	for (int n=1;n<=mol.NumBonds();n++)
	{
	    out.write("\""+mol.BondFrom(n)+"-"+mol.BondTo(n)+"="+mol.BondOrder(n)+","+mol.BondType(n)+"\\n\"+");
	}
	out.write("\"!FIN\"");
	
	out.flush();
    }
    
    // jm.evers
    // testing with a "convenient way to produce a "MDLMol string" to be used as wims $variable in javascript. 
    public static void WriteMDLMol2JavaScript(OutputStream ostr,Molecule mol) throws IOException {
	WriteMDLMol2JavaScript(new BufferedWriter(new OutputStreamWriter(ostr)),mol);
    }
    public static void WriteMDLMol2JavaScript(BufferedWriter out,Molecule mol) throws IOException {
        DecimalFormat fmt=new DecimalFormat("0.0000",new DecimalFormatSymbols(Locale.US));
    	out.write("\"\\nWIMSchem molfile\\n\\n\"+");
	out.write("\""+intrpad(mol.NumAtoms(),3)+intrpad(mol.NumBonds(),3)+"  0  0  0  0  0  0  0  0999 V2000\\n\"+");
	String line;
	for (int n=1;n<=mol.NumAtoms();n++)
	{
	    String str="\"   "+fmt.format(mol.AtomX(n)); 
	    line=rep(" ",10-str.length())+str;
	    str=fmt.format(mol.AtomY(n)); 
	    line+=rep(" ",10-str.length())+str;
	    line+="    0.0000 ";
	    str=mol.AtomElement(n);
	    line+=str+rep(" ",4-str.length())+"0";
	    
	    int chg=mol.AtomCharge(n),spin=mol.AtomUnpaired(n),mapnum=mol.AtomMapNum(n);
	    if (chg>=-3 && chg<=-1) chg=4-chg;
    	    else if (chg==0 && spin==2) chg=4;
	    else if (chg<1 || chg>3) chg=0;
	    line+=intrpad(chg,3)+"  0  0  0  0  0  0  0"+intrpad(mapnum,3)+"  0  0";
	    
	    out.write(line+"\\n\"+");
	}
	
	for (int n=1;n<=mol.NumBonds();n++)
	{
	    int type=mol.BondOrder(n);
	    if (type<1 || type>3) type=1;
	    int stereo=mol.BondType(n);
	    if (stereo==Molecule.BONDTYPE_NORMAL) {}
	    else if (stereo==Molecule.BONDTYPE_INCLINED) {stereo=1; type=1;}
	    else if (stereo==Molecule.BONDTYPE_DECLINED) {stereo=6; type=1;}
	    else if (stereo==Molecule.BONDTYPE_UNKNOWN) {stereo=4; type=1;}
	    else stereo=0;

    	    out.write("\""+intrpad(mol.BondFrom(n),3)+intrpad(mol.BondTo(n),3)+intrpad(type,3)+intrpad(stereo,3)+"  0  0  0\\n\"+");
	}
	
	int count=0;
	line="";
	for (int n=1;n<=mol.NumAtoms();n++) if (mol.AtomCharge(n)!=0)
	{
	    line+=intrpad(n,4)+intrpad(mol.AtomCharge(n),4);
	    count++;
	    if (count==8)
	    {
		out.write("\"M  CHG"+intrpad(count,3)+line+"\\n\"+");
	    	count=0; line="";
	    }
	}
	if (count>0) out.write("\"M  CHG"+intrpad(count,3)+line+"\\n\"+");
	
	count=0;
	line="";
	for (int n=1;n<=mol.NumAtoms();n++) if (mol.AtomUnpaired(n)!=0)
	{
	    line+=intrpad(n,4)+intrpad(mol.AtomUnpaired(n),4);
	    count++;
	    if (count==8)
	    {
		out.write("\"M  RAD"+intrpad(count,3)+line+"\\n\"+");
	    	count=0; line="";
	    }
	}
	if (count>0) out.write("\"M  RAD"+intrpad(count,3)+line+"\\n\"");
	
	out.write("\"M  END\\n\"");
	out.flush();
    }
    

    //jm.evers
    // converting a molecule to a string in native fileformat.Used for comparing MDLMol js-string with student drawing
    public static String Molecule2String(Molecule mol) throws IOException {
	DecimalFormat fmt=new DecimalFormat("0.0000",new DecimalFormatSymbols(Locale.US));
    	String i="WIMSchem!("+mol.NumAtoms()+","+mol.NumBonds()+")\n";
	for (int n=1;n<=mol.NumAtoms();n++)
	{
	    String hy=mol.AtomHExplicit(n)!=Molecule.HEXPLICIT_UNKNOWN ? ("e"+mol.AtomHExplicit(n)) : ("i"+mol.AtomHydrogens(n));
	    i=i+mol.AtomElement(n)+"="+fmt.format(mol.AtomX(n))+","+fmt.format(mol.AtomY(n))+";"+mol.AtomCharge(n)+","+mol.AtomUnpaired(n)+","+hy;
    	    if (mol.AtomMapNum(n)>0) i=i+",n"+mol.AtomMapNum(n);
    	    i=i+"\n";
	}
	for (int n=1;n<=mol.NumBonds();n++)
	{
	    i=i+mol.BondFrom(n)+"-"+mol.BondTo(n)+"="+mol.BondOrder(n)+","+mol.BondType(n)+"\n";
	}
	i=i+"!FIN\n";
	return i;
    }



    public static Molecule ReadMDLMOL(BufferedReader in) throws IOException
    {
    	Molecule mol=new Molecule();
    	final String GENERIC_ERROR="Invalid MDL MOL file.";

	try
	{
	    String line=null;
	    for (int n=0;n<4;n++) line=in.readLine();
	    if (!line.substring(34,39).equals("V2000")) throw new IOException(GENERIC_ERROR);
	    int numAtoms=Integer.parseInt(line.substring(0,3).trim());
	    int numBonds=Integer.parseInt(line.substring(3,6).trim());
	    for (int n=0;n<numAtoms;n++)
	    {
	    	line=in.readLine();
		
		double x=Double.parseDouble(line.substring(0,10).trim());
		double y=Double.parseDouble(line.substring(10,20).trim());
		String el=line.substring(31,34).trim();
		int chg=Integer.parseInt(line.substring(36,39).trim()),rad=0;
		int mapnum=Integer.parseInt(line.substring(60,63).trim());
		
		if (chg<=3) {}
		else if (chg==4) {chg=0; rad=2;}
		else chg=4-chg;
				
		mol.AddAtom(el,x,y,chg,rad);
		mol.SetAtomMapNum(mol.NumAtoms(),mapnum);
	    }
	    for (int n=0;n<numBonds;n++)
	    {
	    	line=in.readLine();
		
		int from=Integer.parseInt(line.substring(0,3).trim()),to=Integer.parseInt(line.substring(3,6).trim());
		int type=Integer.parseInt(line.substring(6,9).trim()),stereo=Integer.parseInt(line.substring(9,12).trim());
		
		if (from==to || from<1 || from>numAtoms || to<1 || to>numAtoms) throw new IOException(GENERIC_ERROR);
		
		int order=type>=1 && type<=3 ? type : 1;
		int style=Molecule.BONDTYPE_NORMAL;
		if (stereo==1) style=Molecule.BONDTYPE_INCLINED;
		else if (stereo==6) style=Molecule.BONDTYPE_DECLINED;
		// !! supposed to be for double bonds... else if (stereo==3 || stereo==4) style=Molecule.BONDTYPE_UNKNOWN;

    	        mol.AddBond(from,to,order,style);
	    }
	    while (true)
	    {
	    	line=in.readLine();
		if (line.startsWith("M  END")) break;
		
		int type=0;
		if (line.startsWith("M  CHG")) type=1;
		else if (line.startsWith("M  RAD")) type=2;
		if (type>0)
		{
		    int len=Integer.parseInt(line.substring(6,9).trim());
		    for (int n=0;n<len;n++)
		    {
		    	int apos=Integer.parseInt(line.substring(9+8*n,13+8*n).trim());
			int aval=Integer.parseInt(line.substring(13+8*n,17+8*n).trim());
			if (type==1) mol.SetAtomCharge(apos,aval); else mol.SetAtomUnpaired(apos,aval);
		    }
		}
	    }
	}
	catch (Exception e) {throw new IOException(GENERIC_ERROR+"hier");}

    	return mol;
    }
    

    public static void WriteMDLMOL(OutputStream ostr,Molecule mol) throws IOException
    {
	WriteMDLMOL(new BufferedWriter(new OutputStreamWriter(ostr)),mol);
    }
    public static void WriteMDLMOL(BufferedWriter out,Molecule mol) throws IOException
    {
    	DecimalFormat fmt=new DecimalFormat("0.0000",new DecimalFormatSymbols(Locale.US));
    	out.write("\nWIMSchem molfile\n\n");
	out.write(intrpad(mol.NumAtoms(),3)+intrpad(mol.NumBonds(),3)+"  0  0  0  0  0  0  0  0999 V2000\n");
    	
	String line;
	
	for (int n=1;n<=mol.NumAtoms();n++)
	{
	    String str=fmt.format(mol.AtomX(n)); 
	    line=rep(" ",10-str.length())+str;
	    str=fmt.format(mol.AtomY(n)); 
	    line+=rep(" ",10-str.length())+str;
	    line+="    0.0000 ";
	    str=mol.AtomElement(n);
	    line+=str+rep(" ",4-str.length())+"0";
	    
	    int chg=mol.AtomCharge(n),spin=mol.AtomUnpaired(n),mapnum=mol.AtomMapNum(n);
	    if (chg>=-3 && chg<=-1) chg=4-chg;
    	    else if (chg==0 && spin==2) chg=4;
	    else if (chg<1 || chg>3) chg=0;
	    line+=intrpad(chg,3)+"  0  0  0  0  0  0  0"+intrpad(mapnum,3)+"  0  0";
	    
	    out.write(line+"\n");
	}
	
	for (int n=1;n<=mol.NumBonds();n++)
	{
	    int type=mol.BondOrder(n);
	    if (type<1 || type>3) type=1;
	    int stereo=mol.BondType(n);
	    if (stereo==Molecule.BONDTYPE_NORMAL) {}
	    else if (stereo==Molecule.BONDTYPE_INCLINED) {stereo=1; type=1;}
	    else if (stereo==Molecule.BONDTYPE_DECLINED) {stereo=6; type=1;}
	    else if (stereo==Molecule.BONDTYPE_UNKNOWN) {stereo=4; type=1;}
	    else stereo=0;

    	    out.write(intrpad(mol.BondFrom(n),3)+intrpad(mol.BondTo(n),3)+intrpad(type,3)+intrpad(stereo,3)+"  0  0  0\n");
	}
	
	int count=0;
	line="";
	for (int n=1;n<=mol.NumAtoms();n++) if (mol.AtomCharge(n)!=0)
	{
	    line+=intrpad(n,4)+intrpad(mol.AtomCharge(n),4);
	    count++;
	    if (count==8)
	    {
		out.write("M  CHG"+intrpad(count,3)+line+"\n");
	    	count=0; line="";
	    }
	}
	if (count>0) out.write("M  CHG"+intrpad(count,3)+line+"\n");
	
	count=0;
	line="";
	for (int n=1;n<=mol.NumAtoms();n++) if (mol.AtomUnpaired(n)!=0)
	{
	    line+=intrpad(n,4)+intrpad(mol.AtomUnpaired(n),4);
	    count++;
	    if (count==8)
	    {
		out.write("M  RAD"+intrpad(count,3)+line+"\n");
	    	count=0; line="";
	    }
	}
	if (count>0) out.write("M  RAD"+intrpad(count,3)+line+"\n");
	
	out.write("M  END\n");
	out.flush();
    }
    
    public static void WriteCMLXML(OutputStream ostr,Molecule mol) throws IOException
    {
	WriteCMLXML(new BufferedWriter(new OutputStreamWriter(ostr)),mol);
    }
    public static void WriteCMLXML(BufferedWriter out,Molecule mol) throws IOException
    {
    	out.write("<cml>\n");
	out.write("  <molecule>\n");

	out.write("    <atomArray>\n");
	for (int n=1;n<=mol.NumAtoms();n++)
	{
	    out.write("      <atom id=\"a"+n+"\" elementType=\""+mol.AtomElement(n)+"\""+
	    	    	    	 " x2=\""+mol.AtomX(n)+"\" y2=\""+mol.AtomY(n)+"\" hydrogenCount=\""+mol.AtomHydrogens(n)+"\"/>\n");
	}
	out.write("    </atomArray>\n");
	
	out.write("    <bondArray>\n");
	for (int n=1;n<=mol.NumBonds();n++)
	{
	    out.write("      <bond id=\"b"+n+"\" atomRefs2=\"a"+mol.BondFrom(n)+" a"+mol.BondTo(n)+"\" order=\""+mol.BondOrder(n)+"\"/>\n");
	}
	out.write("    </bondArray>\n");
	
	out.write("  </molecule>\n");
	out.write("</cml>\n");
	out.flush();
    }
    
    // examines the beginning of a file and decides whether it can be considered a database of structures which this class is capable
    // of reading...
    // (NB: currently this includes MDL SD-files, and nothing else)
    static boolean ExamineIsDatabase(FileInputStream istr) throws IOException 
    {
    	long lastpos=istr.getChannel().position();
	boolean isdb=FindNextPosition(istr,0)>=0;
    	istr.getChannel().position(lastpos);
	return isdb;
    }
    
    static long FindNextPosition(FileInputStream istr,long startpos) throws IOException
    {
    	FileChannel fch=istr.getChannel();
	fch.position(startpos);
	long pos=startpos,size=fch.size(),nextpos=-1;
	
	String rec="";
	while (nextpos<size)
	{
	    int inp=istr.read();
	    pos++;
	    if (inp<0) break;
	    char ch=(char)inp;
	    if (ch=='\r') continue;
	    rec=rec.concat(String.valueOf(ch));
	    if (rec.endsWith("$$$$\n")) {nextpos=pos; break;}
	}
	if (nextpos<0) return -1;

	try
	{
	    BufferedReader in=new BufferedReader(new StringReader(rec));
	    Molecule mol=ReadMDLMOL(in);
	    if (mol==null) nextpos=-1;
	}
	catch (IOException e) {nextpos=-1;}
	
	return nextpos;
    }
    
    static Molecule FetchFromPosition(FileInputStream istr,long pos) throws IOException
    {
    	istr.getChannel().position(pos);
	return ReadMDLMOL(new BufferedReader(new InputStreamReader(istr)));
    }
    
    // miscellaneous help
    
    static String intrpad(int Val,int Len)
    {
    	String str=Integer.toString(Val);
	str=rep(" ",Len-str.length())+str;
	if (str.length()>Len) str=str.substring(0,Len);
	return str;
    }
    static String rep(String Ch,int Len)
    {
    	if (Len<=0) return "";
    	String str=Ch;
	while (str.length()<Len) str=str+Ch;
	return str;
    }

    public static String GetSmiles(Molecule mol){
    // jm.evers
    // all very clumsy...there must be another/better way of doing this proper !
	int a;int b;int p=0;int H1=0;int H2=0;int C1=0;int C2=0;String c1="";;String c2="";
	String smile="";int M=mol.NumBonds();int N=mol.NumAtoms();
	try{
	    if(N==1){
		if(mol.AtomHExplicit(1)!=Molecule.HEXPLICIT_UNKNOWN){
		    H1=mol.AtomHExplicit(1);
		}
		else
		{
		    H1=mol.AtomHydrogens(1);
		} 
		C1=mol.AtomCharge(1);
	        if(C1 != 0){
	    	    if(C1>0){
			if(C1==1){
			    c1="<sup><small><b>+</b></small></sup>";
			}
			else
			{
			    c1="<sup><small><b>"+C1+"+</b></small></sup>";
			}
		    }
		    else
		    {
			C1=-1*C1;
			if(C1 == 1){
			    c1="<sup><small><b>-</b></small></sup>";
			}
			else
			{
			    c1="<sup><small><b>"+C1+"-</b></small></sup>";
			}    
		    }
		}
		else
		{
		    c1 = "";
		}
		if(H1 != 0){
		    if(H1 == 1){
			smile=mol.AtomElement(1)+c1+"H";
		    }
		    else
		    {
			smile=mol.AtomElement(1)+c1+"H<sub><small>"+H1+"</small></sub>";
		    }
		}
		else
		{
		    smile=mol.AtomElement(1)+c1;
		}	
	    }
	    else
	    {
		int[] From=new int[M+1];
		int[] To=new int[M+1];
		boolean[] Fdone=new boolean[N+1];
		boolean[] Tdone=new boolean[N+1];
		boolean test=true;
		for(int n=1;n<=M;n++){
	    	    From[n]=mol.BondFrom(n);
	    	    To[n]=mol.BondTo(n);
		}
		for(int n=0;n<=N;n++){
		    Fdone[n]=false;
		    Tdone[n]=false;
		}
		for(int n=1;n<=M;n++){
		    test=true;a=From[n];b=To[n];p=1;
		    if(mol.AtomHExplicit(a)!=Molecule.HEXPLICIT_UNKNOWN){
			H1=mol.AtomHExplicit(a);
		    }
		    else
		    {
			H1=mol.AtomHydrogens(a);
		    } 
		    if(mol.AtomHExplicit(b)!=Molecule.HEXPLICIT_UNKNOWN){
			H2=mol.AtomHExplicit(b);
		    }
		    else
		    {
	    		H2=mol.AtomHydrogens(b);
		    }
		    C1=mol.AtomCharge(a);
		    C2=mol.AtomCharge(b);
		    if(C1 != 0){
			if(C1>0){
			    if(C1==1){
				c1="<sup><small><b>+</b></small></sup>";
			    }
			    else
			    {
				c1="<sup><small><b>"+C1+"+</b></small></sup>";
			    }
			}
			else
			{
			    C1=-1*C1;
			    if(C1 == 1){
				c1="<sup><small><b>-</b></small></sup>";
			    }
			    else
			    {
				c1="<sup><small><b>"+C1+"-</b></small></sup>";
			    }    
			}
		    }
		    else
		    {
			c1 = "";
		    }
		    if(C2 != 0){
			if(C2>0){
		    	    if(C2==1){
				c2="<sup><small><b>+</b></small></sup>";
			    }
		    	    else
			    {
				c2="<sup><small><b>"+C2+"+</b></small></sup>";
			    }
			}
			else
			{
			    C2=-1*C2;
		    	    if(C2 == 1){
		    		c2="<sup><small><b>-</b></small></sup>";
			    }
			    else
			    {
				c2="<sup><small><b>"+C2+"-</b></small></sup>";
			    }    
			}
		    }
		    else
		    {
			c2 = "";
		    }
	    
		    while(test && p<=M){
			if(!Fdone[a] && !Tdone[a]){
			    if(H1 != 0){
				if(H1 == 1){
				    smile=smile+"("+(mol.AtomElement(a))+c1+"H)"+(htmlbond(mol.BondOrder(a)));
				}
				else
				{
				    smile=smile+"("+(mol.AtomElement(a))+c1+"H<sub><small>"+H1+"</small></sub>)"+(htmlbond(mol.BondOrder(a)));
				}
			    }
			    else
			    {
				smile=smile+(mol.AtomElement(a))+c1+(htmlbond(mol.BondOrder(a)));
			    }
			    Fdone[a]=true;
	    		}

			if(!Tdone[b] && !Fdone[b]){
			    if(n<M){
				if(H2 != 0){
				    if(H2 == 1){
					smile=smile+"("+(mol.AtomElement(b))+c2+"H)"+(htmlbond(mol.BondOrder(b))) ;
				    }
				    else
				    {
					smile=smile+"("+(mol.AtomElement(b))+c2+"H<sub><small>"+H2+"</small></sub>)"+(htmlbond(mol.BondOrder(b))) ;
				    }
				}
				else
				{			
				    smile=smile+(mol.AtomElement(b))+c2+(htmlbond(mol.BondOrder(b))) ;
				}
			    }
			    else
			    {
				if( H2 != 0){
				    if( H2 == 1){
					smile=smile+"("+(mol.AtomElement(b))+c2+"H)";
				    }
				    else
				    {
					smile=smile+"("+(mol.AtomElement(b))+c2+"H<sub><small>"+H2+"</small></sub>)";
				    }
				}
				else
				{
				    smile=smile+(mol.AtomElement(b))+c2;
				}
			    }
			    Tdone[b]=true;
			}
			if(Tdone[b] || Fdone[a]){
			    test=false;
			}
		        p++;
		    }
		}
	    }
	    return smile;
	}
	catch (Exception e){return "error \n Are You drawing more than 1 molecule ???";}
    }
    
    public static String htmlbond(int order){
    // jm.evers
	String s="&minus";
	if(order == 0){ 
	    s="\u22Ef";
	}
	else
	{
	    if(order == 1){ 
		s="&minus;";
	    }
	    else
	    {
		if(order == 2){
		    s="=";
		}
		else
		{
		    if(order == 3){
			s="&equiv;";
		    }
		}
	    }
	}
	return s;
    }


}
