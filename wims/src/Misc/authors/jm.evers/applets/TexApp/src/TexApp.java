/*

*********************************************************************************
* J.M. Evers 19/11/2009								*
* This is all amateur scriblings... So no copyrights.				*
* This source code file, and compiled classes derived from it,			*
* can be used and distributed without restriction, including for commercial use	*
* No warrenty whatoever								*
*********************************************************************************

ATP library is GNU :see ./atp/gpl.txt

Example:
<html>
    <body bgcolor=#0000ff onload="javascript:SetSize('TexApp');">
        <script type="text/javascript">                                                 
	function remove(t){
	    document.getElementById(t).width = 1;
	    document.getElementById(t).height = 1;	
	}
	                                                       
    	function SetSize(t){                         
	    var size = new Array(2);
	    size = document.getElementById(t).getPrefferedSize();
	    document.getElementById(t).width = size[0];
	    document.getElementById(t).height = size[1];
	    document.getElementById('showme').innerHTML='<hr><font color=red><b>preffered height = '+size[1]+'<br>preffered width = '+size[0]+'</b></font>';
	    
        } 
    	function ReadApplet(t){                         
	    var reply = document.getElementById(t).ReadApplet();
	    document.getElementById('showme').innerHTML='<hr><font color=red><b>'+reply+'</b></font>';
        } 
	
	function ExtraInput(t){
	    document.getElementById('TexApp').changeInputfields(t);
	}
	</script>
	<div id="showme"></div>
	<table ><tr valign=middle ><th>
	<font color=red>
	this is some text...
	</font>
	</th>
	<th>
	<applet id="TexApp" codebase="build" archive="DragStuff.jar" code="TexApp.class" width="1" height="1">
            <param name="latex" value="\left\{ \begin{array}{l} 4 \times \euro = \\ 4 \times \euro = \\ 4 \times \euro = \end{array} "> <!-- values, plain latex no ":" or ";" allowed -->                                

	    <!-- optional -->
	    <param name="latex_bgcolor" value="0,0,255"><!-- rgb or #ffffff default white -->
	    <param name="latex_fgcolor" value="255,0,0"><!-- rgb or #ffffff  default black -->
	    <param name="latex_fontsize" value="18"><!-- rgb  or #ffffff  default black -->
	    
	    <!-- optional inputfield after the latex image -->
	    <param name="status" value="done"><!-- string : wims variable $status  done/waiting -->
	    <param name="inputfields" value="3"><!-- int : optional : default 0 : number of inputfields on top of eachother-->
	    <param name="inputfield_width" value="120"><!-- int : default 10 : width in px of inputfield-->
	    <param name="inputfield_height" value="120"><!-- optional int : default fontsize in px : height in px of inputfield-->
	    <param name="inputfield_fontsize" value ="18"><!-- int : default 10 -->
	    <param name="inputfield_bgcolor" value="0,0,255"><!-- rgb or #ffffff  default white -->
	    <param name="inputfield_fgcolor" value="255,0,0"><!-- rgb or #ffffff  default black -->
	    <param name="inputfield_editable" value="1,1,1"><!-- field 1 is editable, field 2 is editable... default all editable -->
	    <param name="inputfield_values" value="12,44,"><!--  optional for correct answers: field 1 = "12", field 2 = "44" field3= "" field4 = "22" -->
	    NO JAVA
	</applet>
	</th>
	<th>
	<font color=red>
	and this is the rest...</font>
	</th></tr>
	</table>
	<p>
	<font color=white>
	For applet autoscaling, the applet_tag "width" should be less than 10 : width="1"<br>
	The autoscaling SetSize() javascript_function could be called from the htmlpage "body onload".<br>
	Or in WIMS:<br>
	!set wims_html_onload=javascript:SetSize('TexApp');
	<br>
	If the applet has a width &gt; 10 , no autoscaling is performed.
	</font>
	<br>
	<input type="button" name="ReadApplet()" value="ReadApplet()" onclick="javascript:ReadApplet('TexApp');">
	<input type="button" name="SetSize()" value="SetSize()" onclick="javascript:SetSize('TexApp');">
	<input type="button" name="remove()" value="remove()" onclick="javascript:remove('TexApp');">
	<br>
	<input type="button" name="extra inputfield" value="extra inputfield" onclick="javascript:ExtraInput('1');">
	<input type="button" name="remove inputfield" value="remove inputfield" onclick="javascript:ExtraInput('-1');">
    </body>
</html>


*/    

import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.util.StringTokenizer;
import atp.sHotEqn; 

public class TexApp extends Applet {

    public void init(){
    	setLayout(null);
        Dimension appletSize = getSize();
	if( appletSize.width < 10 ){ resize = true; xsize = 0; ysize = 0; }
	else { resize = false; xsize = appletSize.width; ysize = appletSize.height; }
    	latex_bgcolor = colorParam("latex_bgcolor", Color.white);
	latex_fgcolor = colorParam("latex_fgcolor", Color.black);
	f1 = getInt("latex_fontsize",16);
	f2 = f1-2;
	f3 = f1-4;
	f4 = f1-6;
	inputs = getInt("inputfields",0);
	if(inputs > 0 ){ 
	    inputwidth = getInt("inputfield_width",0);
	}
	Get_Latex();
	if(inputs >0 ){ reinit();}
	setBackground(latex_bgcolor);
    }
    
    public void reinit(){
	fontsize = getInt("inputfield_fontsize", 12);
	inputheight = getInt("inputfield_height",fontsize);
	int ygap = (int) ( ysize - inputs*inputheight)/(inputs+1);
	if(ygap < 0){ 
	    ygap = 0 ; 
	    inputheight = (int) ysize / inputs;
	}
	if(fontsize > inputheight - 4){
	    fontsize = inputheight - 4; if(fontsize < 6 ){ fontsize = 6;}
	}
    	myfont = new Font("Helvetica", 1, fontsize);
    	textfield_bgcolor = colorParam("inputfield_bgcolor", Color.white);
        textfield_fgcolor = colorParam("inputfield_fgcolor", Color.black);
    	getEditable("inputfield_editable");
    	getValues("inputfield_values");
    	inputfield = new TextField[inputs];
	int ystart = ygap;
    	for(int i = 0; i < inputs; i++){
    	    inputfield[i] = new TextField(values[i],inputwidth);
	    this.add(inputfield[i]);
    	    inputfield[i].setFont(myfont);
    	    inputfield[i].setBackground(textfield_bgcolor);
    	    inputfield[i].setForeground(textfield_fgcolor);
   	    inputfield[i].setBounds(xsize - inputwidth,ystart,inputwidth,inputheight);
    	    inputfield[i].setEditable(editable[i]);
    	    inputfield[i].setVisible(true);
	    ystart = ystart + inputheight + ygap ;
	}
	repaint();
    }
    
    public void changeInputfields(int p){ // javascript
	if(inputs == 0){ return; } // no inputfields defined...no need to generate them
	for(int k = 0;k < inputs; k++){
	    this.remove(inputfield[k]);
	}
	inputs = inputs + p;
	if(inputs < 1){inputs = 1;} 
	reinit();
    }
    
    public int[] getPrefferedSize(){ 
    // auto resize applet !
    // javascript reading preffered size of applet: use in wims_html_onload
    // only called if width_applet_tag < 10
	prefferedsize = new int[2];
	prefferedsize[0] = xsize;
	prefferedsize[1] = ysize;
	return prefferedsize;
    }
    
    public Color MakeTransparent(Color color, int i){
        return new Color(color.getRed(), color.getGreen(), color.getBlue(), i);
    }

    public Color colorParam(String s, Color color){
        String s1 = getParameter(s);
        if(s1 != null && s1.length() != 0){
            s1 = s1.replaceAll(":", ",");
            s1 = s1.replaceAll(";", ",");
	    if( s1.indexOf(',') > 0 ){
        	StringTokenizer stringtokenizer = new StringTokenizer(s1, ",");
        	int i = stringtokenizer.countTokens();
        	if(i < 3 || i > 4){ return color;}
        	int ai[] = new int[i + 1];
        	for(int j = 0; j < i; j++){
            	    ai[j] = Integer.parseInt(stringtokenizer.nextToken());
            	    if(ai[j] > 255 || ai[j] < 0){ ai[j] = 0;}
        	}
		if(i == 3)
            	    color = new Color(ai[0], ai[1], ai[2]);
        	else
            	    color = new Color(ai[0], ai[1], ai[2], ai[3]);
    	    }
	    else
	    {
		try{ color = Color.decode( s1 );}catch(Exception e){System.out.println("could not parse "+s);}
		return color;
	    }
	}
        return color;
    }

    public void getValues(String s){
        String s1 = getParameter(s);
        values = new String[inputs];
        for(int i = 0; i < inputs; i++){ values[i] = " ";}
	if( s1 != null && s1.length() != 0){
	    s1 = s1.replaceAll(":", ",");
	    s1 = s1.replaceAll(";", ",");
	    s1 = s1.replaceAll(",", " ,");
	    StringTokenizer stringtokenizer = new StringTokenizer(s1, ",");
	    int j = stringtokenizer.countTokens();
    	    for(int k = 0; k < Math.min(j,inputs) ; k++){
        	values[k] = stringtokenizer.nextToken();
	    }
	}
    }

    public boolean getStatus(){
        String s1 = getParameter("status");
	if( s1 != null && s1.length() != 0){
	    if( s1.equals("done")){
		return true;
	    }
	}
	return false;
    }

    public void getEditable(String s){
        editable = new boolean[inputs];
	if( getStatus() ){ // status = done : no editing allowed
    	    for(int i = 0; i < inputs; i++){ editable[i] = false ;}
	}
	else
	{
    	    String s1 = getParameter(s);
    	    for(int i = 0; i < inputs; i++){ editable[i] = true;}
	    if(s1 != null){
    		s1 = s1.replaceAll(":", ",");
    	        s1 = s1.replaceAll(";", ",");
    		StringTokenizer stringtokenizer = new StringTokenizer(s1, ",");
    	        int j = stringtokenizer.countTokens();
		for(int k = 0; k < Math.min(inputs,j); k++)
    		{
		    try{
        		String s2 = stringtokenizer.nextToken();
    	    	        if(s2.equals("0") || s2.equalsIgnoreCase("no"))
            	    	    editable[k] = false;
        		else
            		    editable[k] = true;
		    }
		    catch(Exception e){}
    		}
	    }
	}
    }

    public int getInt(String s, int i){
        String s1 = getParameter(s);
	if( s1 != null && s1.length()!=0){
    	    try{
        	i = Integer.parseInt(s1);
    	    }
    	    catch(Exception exception){
        	System.out.println(" can not parse parameter "+s);
    	    }
	}
        return i;
    }

    public boolean getBool(String s, boolean flag){
        String s1 = getParameter(s);
        if(s1 != null){
            if(s1.equals("1") || s1.equalsIgnoreCase("yes") || s1.equalsIgnoreCase("true"))
                return true;
            if(s1.equals("0") || s1.equalsIgnoreCase("no") || s1.equalsIgnoreCase("false"))
                return false;
        }
        return flag;
    }

    public void Get_Latex(){
	String r1 = getParameter("latex");
	if(r1 == null || r1.length() == 0){
	    System.out.println("can not read parameter \"latex\"");
	    r1="error_{parameter empty}";
	}
	StringTokenizer stringtokenizer_r = new StringTokenizer(r1, ",");
	int j = stringtokenizer_r.countTokens();
	Latex = new String[j];
	icon = new BufferedImage[j];
	Ylatex = new int[j];
	for(int k = 0; k < j ;k++){                                                                                                        
            Latex[k] = stringtokenizer_r.nextToken();
        }
	if(resize){
	    int gap=0;
	    int actualsize[] = new int[2];
    	    for(int k = 0; k < j; k++){
		sHotEqn shoteqn = new sHotEqn();
	        shoteqn.setFontsizes(f1,f2,f3,f4);
		shoteqn.setEquation(Latex[k]);
		icon[k] = shoteqn.mkImage(latex_bgcolor, latex_fgcolor,400,400, false, 1, 1, false);
	        Ylatex[k] = ysize ;
		actualsize = shoteqn.getActualSize();
	        if(actualsize[0] > xsize){ xsize = actualsize[0]; }
		ysize = ysize + actualsize[1] + gap;
	        icon[k] = shoteqn.mkImage(latex_bgcolor, latex_fgcolor, actualsize[0], actualsize[1], false, 1, 1, false);
	    }
	    xsize = xsize + inputwidth;
	}
	else
	{
    	    for(int k = 0; k < j; k++){
		sHotEqn shoteqn = new sHotEqn();
	        shoteqn.setFontsizes(f1,f2,f3,f4);
		shoteqn.setEquation(Latex[k]);
    	    	icon[k] = shoteqn.mkImage(latex_bgcolor, latex_fgcolor, xsize - inputwidth, ysize/j, false, 1, 1, false);
	        Ylatex[k] = k*ysize/j ;
	    }
	}
    }

    public void paint(Graphics g)
    {
	update(g);
    }

    public void update(Graphics g)
    {
	for(int p = 0 ; p < icon.length ; p++)
	{
	    g.drawImage(icon[p],0,Ylatex[p],this);
	}
    }

    public String ReadApplet(){
	String reply="";
	if(inputs > 0){
	    try{
	    reply = inputfield[0].getText();
	    for(int i = 1 ; i < inputs ; i++)
	    {
		reply = reply + "," + inputfield[i].getText();
	    }
	    }catch(Exception e){System.out.println("ReadApplet error :"+e);}
	}
	else
	{
	    reply = "error no inputfields defined via params...";
	}
	return reply;
    }

    public void run(){}

    public void start(){}

    public void stop(){}

    public void destroy(){}

    TextField inputfield[];
    public int[] prefferedsize;
    public int inputs,Ylatex[],inputwidth=0,inputheight=0,xsize,ysize,fontsize,f1,f2,f3,f4;
    public Color textfield_bgcolor,textfield_fgcolor,latex_bgcolor,latex_fgcolor;
    public String Latex[],values[];;    
    boolean editable[],resize;
    public sHotEqn HSD;
    BufferedImage icon[];
    Font myfont;
}
