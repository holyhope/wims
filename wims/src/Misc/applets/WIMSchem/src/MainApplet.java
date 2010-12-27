/*
    WIMSchem: modified version of SketchEl.
    Elements: Chemistry molecular diagram drawing tool.
    
    (c) 2005 Dr. Alex M. Clark
    
    Released as GNUware, under the Gnu Public License (GPL)
    
    See www.gnu.org for details.
*/

package WIMSchem;

import java.io.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import java.net.*;

public class MainApplet extends JApplet implements ComponentListener{
    
    // amateur solutions...
    MainPanel mainPanel=null;
    MainPanel Language=null;
    MainPanel Translation=null;
    static String[] tools={"TOOL_CURSOR","TOOL_ROTATOR","TOOL_ERASOR","TOOL_DIALOG","TOOL_EDIT","TOOL_SETATOM",
    "TOOL_SINGLE","TOOL_DOUBLE","TOOL_TRIPLE","TOOL_ZERO","TOOL_INCLINED","TOOL_DECLINED","TOOL_UNKNOWN",
    "TOOL_CHARGE","TOOL_UNDO","TOOL_REDO","TOOL_TEMPLATE","TOOL_CUT","TOOL_COPY","TOOL_PASTE","TOOL_UNSELECT","TOOL_SELECT"};
    static String[] menus={"MENU_BLOCK","MENU_SELECT","MENU_TRANSFORM","MENU_ZOOM","MENU_SHOW","MENU_HYDROGEN","MENU_STEREO","MENU_HELP"};
    public boolean[] selected_tools;
    public boolean[] selected_menus;
    public static Properties translation=new Properties();
    public String Correct_answer="";
    public String feedback="";
    public boolean continu=true;
    public String replytext="";
    public String Student_answer="";
    public String language;
    public int typeset=0;
    public String plain_formula_ca="";
    public String html_formula_ca="";
    public String latex_formula_ca="";
    public String plain_formula_sa="";
    public String html_formula_sa="";
    public String latex_formula_sa="";
    static int N=Molecule.ELEMENTS.length;
    public int[] charge_ca;// charge of the atom
    public int[] radical_ca;// radicals?
    public int[] charge_sa;// charge of the atom
    public int[] radical_sa;// radicals?
    public String[] elements_ca;
    public String[] elements_sa;
    public int[] hydro_ca;
    public int[] hydro_sa;
    double weight_ca=0;
    double weight_sa=0;
    String html_smiles_ca="";
    String html_smiles_sa="";
    public int num_sa=0;
    public int num_ca=0;
    public int bond_sa=0;
    public int bond_ca=0;
    public String[] my_atoms;
    public boolean ViewH;
    public boolean ViewC;
    public static String[] templateURL;
    public static int[] ExternalAtomSelection;
    public static Color SelectedAtomColorArray[];
    public static int[] ExternalBondSelection;
    public static Color SelectedBondColorArray[];
    public static double rotation;
    public static boolean once=true;
    public static Color DefaultAtomSelectionColor; 
    public static Color DefaultBondSelectionColor;
    public int alpha = 100;
    public static boolean user_selection;

    public void init(){
	getUserSelection();
	if(user_selection){
	    getAlpha();
	    GetDefaultAtomSelectionColor();
	    GetDefaultBondSelectionColor();
	}
	ExternalAtomSelection = SetAtomSelection();
	ExternalBondSelection = SetBondSelection();
	getRotation();
	templateURL=GetTemplateURL();
	ViewH=ViewHydrogen();
	ViewC=ViewCarbon();
	selected_tools=getTools();
	selected_menus=getMenus();
	my_atoms=GetMyAtoms();
	language=getLanguage();
	translation=loadProperties(language);
	getContentPane().setLayout(new BorderLayout());
    	mainPanel=new MainPanel(null,false,true,null,language,translation,selected_tools,selected_menus,my_atoms,ViewH,ViewC);
	getContentPane().add(mainPanel,BorderLayout.CENTER);
	Molecule mol=ParseParams();
	if (mol!=null){mainPanel.SetMolecule(mol);}	
	addComponentListener(this);
	GetFile();
    	repaint(1000);
    }
    

    public void getUserSelection(){
	String Param=getParameter("user_selection");
	if(Param != null && Param.length()>0){
	    if(Param.equalsIgnoreCase("yes") || Param.equals("1")){
		user_selection = true;
	    }
	    else
	    {
		user_selection = false;
	    }
	}
    }

    public void getAlpha(){
	String AlphaParam=getParameter("color_alpha");
	if(AlphaParam != null && AlphaParam.length()>0){
	    alpha = Integer.parseInt(AlphaParam);
	}
    }
    
    public void GetDefaultAtomSelectionColor(){
	String DefaultParam = getParameter("default_atom_select_color");
	if(DefaultParam != null && DefaultParam.length()>0){
	    String k;int R1=0,G1=0,B1=0,rgb=0;
	    StringTokenizer q = new StringTokenizer(DefaultParam, ",");
	    for( int a=0; a<3 ; a++){
		k=q.nextToken();
		rgb=Integer.parseInt(k, 10);
		if(rgb<0){rgb=0;}if(rgb>255){rgb=255;}
		if(a == 0){R1 = rgb;}
		else
		if(a == 1){G1 = rgb;}
		else B1 = rgb;
	    }
	    DefaultAtomSelectionColor = new Color(R1,G1,B1,alpha);	    
	}
	else
	{
	    DefaultAtomSelectionColor = new Color(0,0,255,100);
	}
    }

    public void GetDefaultBondSelectionColor(){
	String DefaultParam = getParameter("default_bond_select_color");
	if(DefaultParam != null && DefaultParam.length()>0){
	    String k;int R1=0,G1=0,B1=0,rgb=0;
	    StringTokenizer q = new StringTokenizer(DefaultParam, ",");
	    for( int a=0; a<3 ; a++){
		k=q.nextToken();
		rgb=Integer.parseInt(k, 10);
		if(rgb<0){rgb=0;}if(rgb>255){rgb=255;}
		if(a == 0){R1 = rgb;}
		else
		if(a == 1){G1 = rgb;}
		else B1 = rgb;
	    }
	    DefaultBondSelectionColor = new Color(R1,G1,B1,alpha);	    
	}
	else
	{
	    DefaultBondSelectionColor = new Color(255,0,0);
	}
    }

    public int[] SetAtomSelection(){
	String param = getParameter("select_atoms");
	if(param != null && param.length()>0){
	    String k;int rgb=0;int R1=255;int G1=0;int B1=0;//red
	    param=param.replaceAll(";",",");param=param.replaceAll(":",",");
	    StringTokenizer i = new StringTokenizer(param, ",");
	    int max=i.countTokens();
	    ExternalAtomSelection = new int[max];
	    SelectedAtomColorArray = new Color[max];
	    String ColorParam;
	    for(int p=0;p<max;p++){
		ExternalAtomSelection[p] = Integer.parseInt(i.nextToken());
	        // now try to find the color belonging to this selected atom
	        ColorParam=getParameter("select_atom_color"+ExternalAtomSelection[p]);
		if(ColorParam != null && ColorParam.length()>0){
		    ColorParam=ColorParam.replaceAll(":",",");ColorParam=ColorParam.replace(";",",");
		    StringTokenizer q = new StringTokenizer(ColorParam, ",");
		    for( int a=0; a<3 ; a++){
			k=q.nextToken();
		        rgb=Integer.parseInt(k, 10);
			if(rgb<0){rgb=0;}if(rgb>255){rgb=255;}
		        if(a == 0){R1 = rgb;}
			else
		        {
			    if(a == 1){G1 = rgb;}
			    else{B1 = rgb;}
			}
		    }
		    SelectedAtomColorArray[p] = new  Color(R1,G1,B1,alpha);
		}
	        else
		{
		    SelectedAtomColorArray[p] = DefaultAtomSelectionColor;
		}
	    }
	}else{ ExternalAtomSelection = null;}
	return ExternalAtomSelection;
    }

    public int[] SetBondSelection(){
	String param = getParameter("select_bonds");
	if(param != null && param.length()>0){
	    String k;int rgb=0;int R1=255;int G1=0;int B1=0;String ColorParam;
	    param=param.replaceAll(";",",");param=param.replaceAll(":",",");
	    StringTokenizer i = new StringTokenizer(param, ",");
	    int max=i.countTokens();
	    ExternalBondSelection = new int[max];
	    SelectedBondColorArray = new Color[max];
	    for(int p=0;p<max;p++){
		ExternalBondSelection[p] = Integer.parseInt(i.nextToken());
	        // now try to find the color belonging to this selected bond 
	        ColorParam=getParameter("select_bond_color"+ExternalBondSelection[p]);
		if(ColorParam != null && ColorParam.length()>0){
		    ColorParam=ColorParam.replaceAll(":",",");ColorParam=ColorParam.replace(";",",");
		    StringTokenizer q = new StringTokenizer(ColorParam, ",");
		    for( int a=0; a<3 ; a++){
			k=q.nextToken();
		        rgb=Integer.parseInt(k, 10);
			if(rgb<0){rgb=0;}if(rgb>255){rgb=255;}
		        if(a == 0){R1 = rgb;}
			else
		        {
			    if(a == 1){G1 = rgb;}
			    else{B1 = rgb;}
			}
		    }
		    SelectedBondColorArray[p] = new  Color(R1,G1,B1);
		}
	        else
		{
		    SelectedBondColorArray[p] = DefaultBondSelectionColor;
		}
	    }
	}else{ ExternalBondSelection = null;}
	return ExternalBondSelection;
    }
    
    public void getRotation(){
	String rot = getParameter("rotation");
	if(rot != null && rot.length()>0){
	    rotation = Double.parseDouble(rot);
	}else{rotation = 0.0D;}
    }

    public static byte [] loadURL(URL url) throws IOException {
    // jm.evers :handy functions !!! not mine :(
        int bufSize = 1024 * 2;
	byte [] buf = new byte[bufSize];
	ByteArrayOutputStream bout = new ByteArrayOutputStream();
	BufferedInputStream   in   = new BufferedInputStream(url.openStream());
	int n;
	while ((n = in.read(buf)) > 0) {
    	    bout.write(buf, 0, n);
	}
	try 
	{ in.close(); } catch (Exception ignored) { }
	return bout.toByteArray();
    }

    public static String loadFile(String fname) throws IOException {
    // jm.evers :handy functions !!! not mine :(
	byte[] bytes = loadURL(new URL("file:" + fname));
	return new String(bytes);
    }
    
    public static String load(String fileOrURL) throws IOException {
    // jm.evers :handy functions !!! not mine :(
	try {
	    URL url = new URL(fileOrURL);
	    return new String(loadURL(url));
	} catch (Exception e) {
	return loadFile(fileOrURL);
	}
    }
    
    public String[] GetTemplateURL(){
	// jm.evers : retreive an unknown amount of templates via params called template1,template2...
	// these templates will be called by Template.java
	String parm=getParameter("template1");
	if( parm != null && parm.length()!=0 ){
	    int p=0;
	    while( parm!=null && parm.length()!=0 ){
		p++;
		parm=getParameter("template"+p);
	    }
	    String[] templateURL=new String[p-1];
	    for(int s=1;s<p;s++){
		parm=getParameter("template"+s);
	        templateURL[s-1]=parm;
	    }
	    return templateURL;
	}
	else
	{
	    return null;
	}
    }
    
    public void GetFile(){
    //jm.evers : try to load a file as string from the URL given in the params
	String filename=getParameter("file");
	if (filename!=null){
	    try
	    {
		// jm.evers: is param showfile is set, draw to canvas...
		String showfile=getParameter("showfile");
		if(showfile.equalsIgnoreCase("yes") ||  showfile.equals("1")){
		    String DemoMol=(load(filename)).toString();
		    if(DemoMol.indexOf("WIMSchem!")!=-1 && DemoMol.indexOf("!FIN")!=-1){
			AppendMoleculeNative(DemoMol);
		    }
		    else
		    {
			if( DemoMol.indexOf("molfile")!=-1){
			    AppendMoleculeMDLMol(DemoMol);
			}
			else
			{
			    System.out.println("Unknown filetype or corrupt file "+filename+"\n"+DemoMol);
			}
		    }
		}
		else
		{
		    Correct_answer=(load(filename)).toString();
		    GetQuestion(Correct_answer);
		}
	    }
	    catch (Exception e){System.out.println("Could not load "+filename);continu=false;}
	}
	else
	{
	    System.out.println("param \"file\" is empty\nWill not use fileloading");
	}
    }	

    public String getLanguage(){
    	// jm.evers: reading language. default english
	String param = getParameter("language");
	if(param != null){param = param.toLowerCase();}else{param = "en";}
	return param;
    }

    public Boolean ViewHydrogen(){
    	// jm.evers: reading hydrogen param. 27/12/2008
	String param = getParameter("show_hydrogen");
	boolean h=true;
	if(param != null){param = param.toLowerCase();
	    if(param.equals("0") || param.equals("no")){
		h=false;
	    }
	}
	return h;
    }

    public Boolean ViewCarbon(){
    	// jm.evers: reading elements param. 27/12/2008
	String param = getParameter("show_carbon");
	boolean c=true;
	if(param != null){param = param.toLowerCase();
	    if(param.equals("0") || param.equals("no")){
		c=false;
	    }
	}
	return c;
    }

    public String[] GetMyAtoms(){
    	// jm.evers: reading atoms from params
	String param = getParameter("atoms");
	if(param != null){
	    //System.out.println("found Atoms: "+param);
	    my_atoms=AtomString2AtomArray(param);
	    return my_atoms;
	}
	else{
	    return null;
	}
    }
    
    public String ReadAtomSelection(){
	boolean[] S = EditorPane.atomselection;
	String selection="";
	for (int p=1;p<S.length;p++){ // starts with 1
	    if(S[p]){ // is selected
		if(selection != ""){ 
		    selection=selection +","+p;
		}
		else{
		    selection=""+p;
		}
	    }
	}
	return selection;
    }

    public String ReadBondSelection(){
	boolean[] S = EditorPane.bondselection;
	String selection="";
	for (int p=0;p<S.length;p++){
	    if(S[p]){ // is selected
		if(selection == ""){
		    selection = ""+p;
		}
		else{
		    selection=selection+","+p;
		}
	    }
	}
	return selection;
    }
    
    public String[] AtomString2AtomArray(String t){
	//jm.evers: parsing params into array...fieldseparators are "," ":" ";" " "
	StringTokenizer q;
	if(t.indexOf(",")!=-1){
	    q = new StringTokenizer(t, ",");
	}
	else
	{
	    if(t.indexOf(":")!=-1){
		q = new StringTokenizer(t, ":");	
	    }
	    else
	    {
		if(t.indexOf(";")!=-1){
		    q = new StringTokenizer(t, ";");	
		}
		else
		{
		    if(t.indexOf(" ")>2){
			q = new StringTokenizer(t, " ");	
		    }
		    else
		    {
			return null;
		    }
		}
	    }
	}
	int max=q.countTokens();if( max > 50 ){ max = 50;}
	String[] tmp=new String[max];String s="";
	for( int p = 0 ; p<max ; p++){
	    s=q.nextToken();
	    //System.out.println("found atom "+s);
	    if(s.length()==1 || s.length()==2){
		tmp[p]=s;
		//System.out.println("added");
	    }
	}
	return tmp;
    }     
    
    public boolean[] getMenus(){
	// jm.evers: configuring menus through appletparams
	String param;
	selected_menus=new boolean[8];
	for(int p=0;p<8;p++){
	    param=getParameter(menus[p]);
	    if(param!=null){
		if(param.equalsIgnoreCase("yes") || param.equals("1")){
		    selected_menus[p]=true;
		}
		else
		{
		    selected_menus[p]=false;
		}
	    }
	    else
	    {
		selected_menus[p]=true;
	    }
	}
	return selected_menus;
    
    }
    
    public boolean[] getTools(){
	// jm.evers: configuring toolbar through appletparams
	String param;
	selected_tools=new boolean[22];//adjust if more buttons are added MainPanel en here
	for(int p=0;p<22;p++){//adjust if more buttons are added MainPanel en here
	    param=getParameter(tools[p]);
	    if(param!=null){
		if(param.equalsIgnoreCase("yes") || param.equals("1")){
		    selected_tools[p]=true;
		}
		else
		{
		    selected_tools[p]=false;
		}
	    }
	    else
	    {
		selected_tools[p]=false;
	    }
	}
	return selected_tools;
    }
    
    public Properties loadProperties (String lang){
	translation=new Properties();
	// jm.evers : trying global properties file with translations
	try{
	    InputStream in = getClass().getResourceAsStream("/lang/WIMSchemProperties_"+lang+".properties");
	    translation.load(in);in.close();
	    return translation;
	} 
	catch (Exception e){ System.out.println("error reading /lang/WIMSchemProperties_"+lang+".properties\n"+e);}         
            return null;                                                                                                               
    }  


    public String getAppletInfo(){
    	return  translation.getProperty("WIMSchem_Applet_Description");
    }

    // if the source webpage wishes to supply a molecule at startup time, there is a slightly cumbersome way to accomplish this:
    // the <params> tag may be used; "nlines" should have the total number of lines of text, and each "line{#}" (e.g. "line1", "line50",
    // etc.) should contain the content; the string that emerges should be either WIMSchem native format, or MDL MOL
    
    private Molecule ParseParams(){
    	try
	{
	    String str=getParameter("nlines");
	    if (str==null) return null;
	    int nlines=Integer.valueOf(str).intValue();
	    if (nlines<3 || nlines>10000) return null; // insanity

	    StringBuffer buff=new StringBuffer();
	    for (int n=1;n<=nlines;n++)
	    {
	    	str=getParameter("line"+n);
		if (str==null) return null;
    	    	for (int i=0;i<str.length();i++) 
		{
		    if (str.charAt(i)=='_') str=str.substring(0,i)+" "+str.substring(i+1); else break;
		}
		buff.append(str+"\n");
	    }
	    
	    Molecule mol=MoleculeStream.ReadNative(new BufferedReader(new StringReader(buff.toString())));
	    if (mol.NumAtoms()>0) return mol;
	    return null;
	}
	catch (Exception e) 
	{
	    JOptionPane.showMessageDialog(null,translation.getProperty("Unable_to_parse_parameter_molecule")+e.getMessage(),"zog",JOptionPane.ERROR_MESSAGE); 
	}

    	return null;
    }
    
    // methods intended to interact with Javascript
    // replace the current molecule with the content of the string, which can be any of the formats which WIMSchem
    // is able to read out from a file; returns true if successful
    public boolean SetMoleculeNative(String Source) {
    	try
	{
	    Molecule mol=MoleculeStream.ReadNative(new BufferedReader(new StringReader(Source.toString())));
	    //Molecule mol=MoleculeStream.ReadUnknown(new BufferedReader(new StringReader(Source)));
    	    mainPanel.SetMolecule(mol);
	    mainPanel.repaint();
	    return true;
	}
	catch (IOException e) { System.out.println("error"+e);}
	return false;
    }

    public boolean SetMoleculeMDLMol(String Source) {
    	try
	{
	    Molecule mol=MoleculeStream.ReadMDLMOL(new BufferedReader(new StringReader(Source.toString())));
	    //Molecule mol=MoleculeStream.ReadUnknown(new BufferedReader(new StringReader(Source)));
    	    mainPanel.SetMolecule(mol);
	    mainPanel.repaint();
	    return true;
	}
	catch (IOException e) { System.out.println("error"+e);}
	return false;
    }
    
    // appends the indicated molecular source to the current molecule, in the same way as the paste feature; otherwise works
    // the same as SetMolecule
    public boolean AppendMoleculeNative(String Source){
    	try
	{
	    Molecule mol=MoleculeStream.ReadNative(new BufferedReader(new StringReader(Source.toString())));
    	    mainPanel.AddMolecule(mol);
	    mainPanel.repaint();
	    return true;
	}
	catch (IOException e) {System.out.println("error"+e);}
	
	return false;
    }

    public boolean AppendMoleculeMDLMol(String Source){
    	try
	{
	    Molecule mol=MoleculeStream.ReadMDLMOL(new BufferedReader(new StringReader(Source.toString())));	
    	    mainPanel.AddMolecule(mol);
	    mainPanel.repaint();
	    return true;
	}
	catch (IOException e) {System.out.println("error"+e);}
	
	return false;
    }
    
    // return the string representation of the molecule, in WIMSchem native format
    public String GetMoleculeNative(){
    	try
	{
	    StringWriter sw=new StringWriter();
	    BufferedWriter bw=new BufferedWriter(sw);
	    MoleculeStream.WriteNative(bw,mainPanel.MolData());
	    return sw.toString();
	}
	catch (IOException e) {System.out.println("error"+e);}
	
	return null;
    }
    
    // return the string representation of the molecule, in MDL MOL-file format
    public String GetMoleculeMDLMol(){
    	try
	{
	    StringWriter sw=new StringWriter();
	    BufferedWriter bw=new BufferedWriter(sw);
	    MoleculeStream.WriteMDLMOL(bw,mainPanel.MolData());
	    return sw.toString();
	}
	catch (IOException e) {System.out.println("error"+e);}
	
	return null;
    }

    public void GetQuestion(String i){
	//jm.evers: 
	// called by javascript to "upload" the chemical from a javascript variable. [a wims "record" in my modules]
	// and the same javascript function could call "CompareNative()" to compare this molecule with the drawing  
	// OR
	// if <param name="file" value="http://whatever_wims_server/filename"> is set
	feedback="";
	if(i.indexOf("WIMSchem!")!=-1 && i.indexOf("!FIN")!=-1){
	    //Correct_answer=i.replaceAll(" ","");continu=true;
	    //System.out.println("found Native WIMSchem file :"+Correct_answer);
	    System.out.println("Native fileformat detected");
		Molecule elmol=new Molecule();
		try
		{
		    elmol=MoleculeStream.ReadNative(new BufferedReader(new StringReader(i.toString())));
		    System.out.println("Native stringfile converted to molecule");
		}
		catch (IOException e) {System.out.println("error"+e);continu=false;}
		// then convert molecule to Native string...
		try
		{
		    Correct_answer=MoleculeStream.Molecule2String(elmol);
		    continu=true;
		}
		catch (IOException e) {System.out.println("error"+e+"trouble with converting native molecule to string:"+i );continu=false;}
	}
	else
	{
	    if( i.indexOf("molfile")!=-1){
		System.out.println("molfile detected");
		// first convert MDMOL to molecule
		Molecule mdmol=new Molecule();
		try
		{
		    mdmol=MoleculeStream.ReadMDLMOL(new BufferedReader(new StringReader(i.toString())));
		    System.out.println("MDMOL file converted to molecule");
		}
		catch (IOException e) {System.out.println("error"+e);continu=false;}
		// then convert molecule to Native string...
		try
		{
		    Correct_answer=MoleculeStream.Molecule2String(mdmol);
		    continu=true;
		}
		catch (IOException e) {System.out.println("error"+e+"trouble with converting molecule to string:"+i );continu=false;}
	    }
	    else
	    {
		if(Correct_answer.length() == 0){
		    feedback=translation.getProperty("empy_string_question");continu=false;
		}
		else
		{
		    feedback=translation.getProperty("invalid_question");continu=false;
		}
	    }
	}
    }
    
    public String ReadApplet(){
	//jm.evers:
	// return info of the shown molecule... e.g. using the applet as image viewer
	// accet
    	try
	{
	    StringWriter sw=new StringWriter();BufferedWriter bw=new BufferedWriter(sw);MoleculeStream.WriteNative(bw,mainPanel.MolData());
	    Correct_answer=sw.toString();Correct_answer=Correct_answer.replaceAll(" ","");
	    if(Correct_answer.indexOf("WIMSchem!")!=-1 || Correct_answer.indexOf("!FIN")!=-1){
		if(Correct_answer.length() < 22){// !WIMSchem(0,0) \n !FIN 
		    feedback=translation.getProperty("empty_answer");continu=false;
		}
	    }
	    else
	    {
		continu=false;feedback=translation.getProperty("no_sketchfile_answer");
	    }
	}
	catch (IOException e) {System.out.println("error"+e);continu=false;feedback=translation.getProperty("no_sketchfile_answer");}
	AnalyseMolecule(Correct_answer,false);
	html_smiles_ca=MoleculeStream.GetSmiles(mainPanel.MolData());
	return 	weight_ca+"\n"+plain_formula_ca+"\n"+html_formula_ca+"\n"+html_smiles_ca+"\n"+latex_formula_ca;
    }
    
    public String CompareNative(){ 
	// jm.evers: 
	// only usefull if called [javascript] together with GetQuestion(). See example in javascript !
	System.out.println("entering function CompareNative()");
    	try
	{
	    StringWriter sw=new StringWriter();BufferedWriter bw=new BufferedWriter(sw);
	    MoleculeStream.WriteNative(bw,mainPanel.MolData());
	    Student_answer=sw.toString();Student_answer=Student_answer.replaceAll(" ","");
	    System.out.println("Student answer is:"+Student_answer);
	    
	    if(Student_answer.indexOf("WIMSchem!")!=-1 || Student_answer.indexOf("!FIN")!=-1){
		if(Student_answer.length() < 22){// !WIMSchem(0,0) \n !FIN 
		    feedback=translation.getProperty("empty_answer");;
		    continu=false;
		}
	    }
	    else
	    {
		continu=false;
		feedback=translation.getProperty("no_sketchfile_answer");
	    }
	}
	catch (IOException e) {System.out.println("error"+e);continu=false;feedback=translation.getProperty("no_sketchfile_answer");}

	if(continu){
	    feedback="";num_sa=0;num_ca=0;bond_sa=0;bond_ca=0;weight_sa=0.0;weight_ca=0.0;
	    AnalyseMolecule(Student_answer,true);
	    AnalyseMolecule(Correct_answer,false);
	    double score=getScore();
	    // a smiles representation -at least it could look like smiles ...
	    html_smiles_sa=MoleculeStream.GetSmiles(mainPanel.MolData());
	    try {
		html_smiles_ca=MoleculeStream.GetSmiles(MoleculeStream.ReadNative(new BufferedReader(new StringReader(Correct_answer))));
	    }
	    catch(IOException e) { System.out.println("error"+e);}
	    return score+"\n"+weight_sa+"\n"+weight_ca+"\n"+plain_formula_sa+"\n"+plain_formula_ca+"\n"+html_formula_sa+"\n"+html_formula_ca+"\n"+html_smiles_sa+"\n"+html_smiles_ca+"\n"+latex_formula_sa+"\n"+latex_formula_ca+"\n"+feedback+"\n@"+Student_answer+"\n@"+Correct_answer;
	}
	else
	{
	    return "error\n"+feedback;
	}
    }
    
    public void AnalyseMolecule(String S , boolean whatisit){
	// jm.evers
	// whatisit=false : correct answer e.g. from javascript by wims.
	// whatisit=true  : student drawing
	// reading data , preparing representation formulas
	if(whatisit){System.out.println("analysing student reply");}else{System.out.println("analysing correct answer");}
	String[] s=S.split("\n");String[] atom;int s1=s[0].indexOf('(');int s2=s[0].indexOf(',');int s3=s[0].indexOf(')');
	int n_s=Integer.parseInt(s[0].substring(s1+1,s2).trim());int b_s=Integer.parseInt(s[0].substring(s2+1,s3).trim());
	String[] E_s=new String[n_s];int[] H_s=new int[n_s];int[] C_s=new int[n_s];int[] R_s=new int[n_s];
	int[] this_A=new int[N];int[] this_C=new int[N];int[] this_R=new int[N];int[] this_H=new int[N];
	String plainformula="";String htmlformula="";String latexformula="";
	String R_plain="";String R_html="";String R_latex="";
	String C_plain="";String C_html="";String C_latex="";
	String sign;
	double weight_s=0.0D;int r=0;
	
	// loop only through the atom part of the file-string 
	for( int p=0; p<n_s ;p++){
	    atom=s[p+1].split("[\\=\\,\\;]"); //first line is mimetype
	    E_s[p]=atom[0];r=0;
	    for(int n=0;n<N;n++){
		if(atom[0].equals(Molecule.ELEMENTS[n])){
		    weight_s=(double)(weight_s + Molecule.WEIGHTS[n]);
		    this_A[n]++;r=n;n=N;
		}
	    }
	    C_s[p]=Integer.parseInt(atom[3]);
	    this_C[r]=C_s[p];
	    R_s[p]=Integer.parseInt(atom[4]);
	    this_R[p]=R_s[p];
	    if( atom[5].indexOf("i")!=-1){
		atom[5]=atom[5].replaceAll("i","");H_s[p]=Integer.parseInt(atom[5]);this_H[r]=H_s[p];this_A[1]=this_A[1]+H_s[p];//hydrogen
	    }
	    else
	    {
		atom[5]=atom[5].replaceAll("e","");H_s[p]=Integer.parseInt(atom[5]);this_H[r]=H_s[p];this_A[1]=this_A[1]+H_s[p];//hydrogen
	    }	    
	    weight_s=(double)(weight_s + H_s[p]);
	}

	if(this_A[6]!=0){
	    if(this_R[6] != 0){R_plain="\u2022";R_latex="^{^{\\cdot}}";R_html="<sup>&cdot;</sup>";}
	    if(this_C[6] != 0){
		if(this_C[6]>0){sign="+";}else{sign="-";this_C[6]=(int) (Math.abs(this_C[6]));}
		C_plain=this_C[6]+sign;C_latex="^{"+this_C[6]+sign+"}";C_html="<sup><small>"+this_C[6]+sign+"</small></sup>";
	    }
	    if(this_A[6] == 1 ){// C1 is not done:  CH4
		plainformula="C"+C_plain+R_plain+" ";
	        htmlformula="<font size=+1><tt>C"+C_html+R_html+"</tt></font>";
		latexformula="\\Bf{C"+C_latex+R_latex+"}";
	    }
	    else
	    {//C2H5OH
		plainformula="C"+C_plain+R_plain+this_A[6];
		htmlformula="<font size=+1><tt>C"+C_html+R_html+"</tt></font><sub><small>"+this_A[6]+"</small></sub>";
		latexformula="\\Bf{C"+C_latex+R_latex+"}_{"+this_A[6]+"}";
	    }
	}
	// the rest
	for(int p = 0; p<N; p++){
	    if( p == 6 ){ p = 7;} // we already covered carbon
	    if( this_A[p] != 0 ){
		R_plain="";R_html="";R_latex="";C_plain="";C_html="";C_latex="";sign="";
		if( this_R[p] != 0 ){ R_plain=this_R[p]+"\u2022";R_latex="^{^{"+this_R[p]+"\\cdot}}";R_html="<sup><sup>"+this_R[p]+"&cdot;</sup></sup>";}
		if( this_C[p] != 0 ){ if( this_C[p]>0 ){ sign="+"; } else { sign="-"; this_C[p]=-1*this_C[p];}C_plain=this_C[p]+sign;C_latex="^{"+this_C[p]+sign+"}";C_html="<sup><small>"+this_C[p]+sign+"</small></sup>";}
		if( this_A[p] == 1 ){
		    plainformula=plainformula+" "+Molecule.ELEMENTS[p]+""+C_plain+""+R_plain;
		    htmlformula=htmlformula+" <font size=+1><tt>"+Molecule.ELEMENTS[p]+C_html+R_html+"</tt></font>";
		    latexformula=latexformula+"\\,\\Bf{"+Molecule.ELEMENTS[p]+C_latex+R_latex+"}";
		}
		else
		{
		    plainformula=plainformula+" "+Molecule.ELEMENTS[p]+""+C_plain+""+R_plain+""+this_A[p];
		    htmlformula=htmlformula+" <font size=+1><tt>"+Molecule.ELEMENTS[p]+C_html+R_html+"</tt></font><sub><small>"+this_A[p]+"</small></sub>";
		    latexformula=latexformula+"\\,\\Bf{"+Molecule.ELEMENTS[p]+C_latex+R_latex+"}_{"+this_A[p]+"}";
		}
	    }
	}
	
	if(whatisit){// these are used for getting a score
	    elements_sa=E_s;hydro_sa=H_s;charge_sa=C_s;radical_sa=R_s;weight_sa=weight_s;
	    plain_formula_sa=plainformula;html_formula_sa=htmlformula;latex_formula_sa=latexformula;num_sa=n_s;bond_sa=b_s;
	}
	else
	{
	    elements_ca=E_s;hydro_ca=H_s;charge_ca=C_s;radical_ca=R_s;weight_ca=weight_s;
	    plain_formula_ca=plainformula;html_formula_ca=htmlformula;latex_formula_ca=latexformula;num_ca=n_s;bond_ca=b_s;
	}
    }// end AnalyseMolecule()

    public double getScore(){
	System.out.println("entering function getScore()");
	// jm.evers:
	// comparing the molecules studentanswer [sa] and correct answer [ca]
	// giving somekind of score: ofcourse any "score < 10" is technically plain wrong !!
	// feedback is not yet operational...because it gives disturbing messages :(
	int hit=0;String tmp_remark="";
	boolean[] done=new boolean[num_sa];
	double finalscore=0.0D;
	for(int p=0;p<num_sa;p++){
	    done[p]=true;
	}
	if( num_ca == num_sa  && bond_ca == bond_sa ){
	    for( int c=0; c < num_ca ; c++){
		for( int s=0; s < num_sa ;s++){
		    if(done[s]){
			if( elements_ca[c].equals(elements_sa[s]) && charge_ca[c] == charge_sa[s] && radical_ca[c] == radical_sa[s] && hydro_ca[c] == hydro_sa[s]){
			    done[s]=false;
			    hit++;s=num_sa;break;
			}
			else
			{
			    if( elements_ca[c].equals(elements_sa[s]) ){
				if( charge_ca[c] != charge_sa[s] ){ tmp_remark="wrong_charge "+elements_ca[c]+"="+charge_ca[c]+",";}
			        if( radical_ca[c] != radical_sa[s] ){ tmp_remark="wrong_radical "+elements_ca[c]+"="+radical_ca[c]+",";}
				if( hydro_ca[c] != hydro_sa[s] ){ tmp_remark="wrong_amount_hydrogen "+elements_ca[c]+"="+hydro_ca[c]+","; }
			    }
			}
		    }
		}
	    }
	}	
	feedback=feedback+tmp_remark;
	if(num_ca > num_sa){
	    finalscore=(double)(10*hit/num_ca);
	}
	else
	{
	    finalscore=(double)(10*hit/num_sa);
	}
	System.out.println("finalscore="+finalscore);
	return finalscore;
    }

    public void componentHidden(ComponentEvent e){}
    public void componentMoved(ComponentEvent e){}
    public void componentResized(ComponentEvent e){}
    public void componentShown(ComponentEvent e){
    mainPanel.ScaleToFit();
    mainPanel.repaint();
    }

}


