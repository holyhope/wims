/*
*********************************************************************************
* J.M. Evers 19/11/2009*
* This is all amateur scriblings... So no copyrights.*
* This source code file, and compiled classes derived from it,*
* can be used and distributed without restriction, including for commercial use*
* No warrenty whatoever*
*********************************************************************************

I've used some code from X.Gang's input applet , to make it "compatibel"
with existing usage...although not thoroughly tested :(
And Gang's applet was an extended version of the original draw.java distributed with java applets as demo.
This work was GNU 

And the Javia-libs however are excellent java and are GNU.

1) Syntax ; similar (...) to flydraw
    [filled || dashed]
    object coordinate_data,color [optional ,alpha,linewidth]

2) Compatibility with Input.java ex Gang
    Use the normal applet params for Input.java [e.g without the script]
    
    Or abandon the input_applet_params and let the script to produce the background image: 
    userdraw points | line | lines | mlines | multilines | (f)polygon | vector | (f)circle | (f)rect | semiline | points | curve
    controls yes/no [use the direct reply buttons]
    pointstyle cross | dot : only for userdrawing

    new: right mousebutton removes parts of drawing
    The result can be read through usual direct contact with wims.cgi
    or via Javascript using ReadApplet() : 
    in this case the answers will be in the coordinate system of the drawing
    [xrange/yrange] and always a list x1,y1,x2,y2,x3,y3.....
    
3) Using the applet as an drawable image [mouse drawinteraction] + coordinates display
    mouse yes
    userdraw points | line | lines | mlines | multilines | (f)polygon | (f)rect | vector | (f)circle | semiline | points | curve
    coordinates yes/no  or left out
    pointstyle cross | dot
    
    Drawing can be read via Javascript using ReadApplet() : 
    The answers will be in the coordinate system of the drawing
    [xrange/yrange] and always a list x1,y1,x2,y2,x3,y3.....
    
    
4) Using the applet as an non_user_drawable image with coordinates display
    mouse no
    coordinates yes

5) Using the applet as a normal Fly image
    mouse no
    coordinates no 
    [this is default]


6) Script syntax [a sort of fly-script]
mouse yes
userdraw [(f)circle,(f)rect,line,multilines,point, etc]
xrange int,int
yrange int,int
linewidth int
transparent color [,alpha]
dline || line x1,y1,x2,y2,color [,alpha,linewidth]
dhline || hline x1,x1,color [,alpha,linewidth]
dvline || vline x1,x1,color [,alpha,linewidth]
darrow || arrow x1,y1,x2,y2,head_factor(0.0001 - 0.99999),color [,alpha,linewidth
dpoly || poly || fpoly x1,y1...x_n,y_n,color [,alpha,linewidth]
drect || rect || frect x1,y1,x2,y2,color [,alpha,linewidth]
dtriangle || triangle || ftrianlge x1,y1,x2,y2,x3,y3,color [,alpha,linewidth]
points x1,y1,x2,y2...x_n,y_n,color [,alpha,linewidth]
point x,y,color [,alpha,linewidth]
pointstyle cross | dot : only for userdrawing
dcircle || circle || fcircle xc,yc,r,color [,alpha,linewidth]
dellipse || ellipse || fellipse xc,yc,r1,r2,color [,alpha,linewidth]
farc || arc xc,yc,radius,start_angle,end_angle,color [,alpha]
dgrid || grid xmajor,ymajor,xminor,yminor,color_mayor,color_minor,linewidth,linewidth [,alpha_major,alpha_minor]
    example: grid 1,1,0.5,0.5,red,blue,2,1,190,120
parallel x1,y1,x2,y2,dx,dy,n,color [,alpha,linewidth]
plotsteps [int] default ysize
dcurve || curve || function in x,color [,alpha,linewidth]
image x1,y1,url // x & y are in coordinate system xrange/yrange
text x,y,fontname,fontsize,the_text_without_comma,color [,alpha] few latexstrings allowed rightarrow alpha beta Beta
textup x,y,angle,fontname,fontsize,some_the_text_without_comma,color [,alpha]  : angle = clockwise rotation in degrees
tex | latex  x1,x2,latexstring.bgcolor,fgcolor[,bg_alpha,fg_alpha]
scalelatex 1,1,width,height,latexstring,bgcolor,fgcolor[,bg_alpha,fg_alpha]
xscale x1,x1_name,x2,x2_name,x3,x3_name,....,fontsize,fontname,color,linewidth
yscale y1,y1_name,y2,y2_name,y3,y3_name,....,fontsize,fontname,color,linewidth
xlabel x_axis-name,fontsize,fontname,[fontcolor,alpha]
ylabel y_axis-name,fontsize,fontname,[fontcolor,alpha]
precision 100 // 2 decimals for reading coords with "mouse yes"
xlogscale xstart,xend,color[alpha,linewidth]
ylogscale ystart,yend,color[alpha,linewidth]
debug yes //some info on loading script and other trouble

todo:
- Animating curves [very hard?]
- Animated gif as background
<html>
 <body>
    <script type="text/javascript">
	function ReadThis(){
	    reply = document.getElementById('FlyApplet').ReadApplet();
	    alert("answer is a list of coordinates \n"+reply);
	}
    </script>
    <applet id="FlyApplet" name="FlyApplet" code="FlyApplet.class" archive="FlyApplet.jar" width="500" height="500">
	<param name="file" value="serveradres_scriptfile">
    </applet>
    <br>
    <input type="button" name="flyapplet1" value="Read Drawing" onclick="javascript:ReadThis();">
 </body>
</html>
*/


import java.applet.*;
import java.lang.Math;
import java.io.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.StringTokenizer;
import javax.swing.*;
import java.net.*;
import java.awt.geom.AffineTransform;
import java.awt.font.TextLayout;
import java.awt.font.FontRenderContext;
import org.javia.arity.Symbols;
import org.javia.arity.SyntaxException;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import atp.sHotEqn;

public class FlyApplet extends JApplet{
    FlyApplet_panel panel;
    FlyApplet_controls controls;
    String flyscript;
    double xmin=-10D,xmax=10D;
    double ymin=-10D,ymax=10D;
    int xsize,ysize;
    URL url;
    int object_count=0;    
    int image_count=0;    
    int user_object_count=0;
    Vector objects = new Vector();
    Vector user_objects = new Vector();
    int linewidth = 1;
    int alpha=255;
    int fontsize = 18;
    int plotjump;
    int inputs = 20; // max inputfields
    TextArea inputfield[];
    int inputfieldindex=0;
    String fontname = "TimesRoman";
    Font font;
    Font textfieldfont;
    int plotsteps=500;
    public Color clickcolor = new Color(0,0,0);
    Color bgcolor = new Color(255,255,255);
    String replystring;
    public static String prompt="OK";
    public static String retry="Erase";
    URL backurl;
    Graphics2D backg;
    BufferedImage bg; // background image
    double precision = 100D;
    boolean mouse = false;
    boolean debug = false;
    boolean use_controls = false; // wims buttons
    boolean use_coords = false; // show x/y
    boolean dashed=false;
    boolean cross = true;
    Symbols symbols;
    boolean use_xscale=false;
    boolean use_yscale=false;
    boolean use_ylog=false;
    boolean use_xlog=false;
    boolean use_inputarea=false;
    public sHotEqn TeX;
    public void init() {
/*
    GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
    String[] fontNames = ge.getAvailableFontFamilyNames();
    Font[] allFonts = ge.getAllFonts();
    for(int i=0;i<allFonts.length;i++){
	System.out.println("allFont["+i+"]="+allFonts[i].toString());
    }
*/    	
	URL url;
	Dimension appletSize = this.getSize();
	ysize = appletSize.height;
	xsize = appletSize.width;
	plotjump=ysize;
	String parmstr;
	// do we use a script ?
	parmstr=getParameter("file");
	symbols=new Symbols();
	if ( parmstr!=null && parmstr.length()>0){
	    boolean go=true;
	    try{
		flyscript = load(parmstr);
	    }catch(Exception e){System.out.println("could not set parameter \"file\" to "+parmstr+"\n"+e);go=false;}
	    if(go){
		bg = new BufferedImage(xsize,ysize, BufferedImage.TYPE_INT_ARGB );
	        backg = (Graphics2D) bg.getGraphics();
		ReadFlyScript(flyscript);
		// nothing to draw just pointing}
		if(!mouse){FlyApplet_panel.ctype=FlyApplet_panel.NULL;}
	    }
	}
	// see if Gang's params are set; if so use these settings for the drawing etc.
	try{
	    parmstr=getParameter("type");
	    if( parmstr != null || parmstr.length() > 3 ){
		use_controls = true;
		parmstr.toLowerCase(); parmstr.trim();
		FlyApplet_panel.ctype=FlyApplet_panel.NULL;
		if(parmstr.compareTo("curve")==0) FlyApplet_panel.ctype=FlyApplet_panel.CURVE;
		if(parmstr.compareTo("rectangle")==0) FlyApplet_panel.ctype=FlyApplet_panel.RECT;
	        if(parmstr.compareTo("rect")==0) FlyApplet_panel.ctype=FlyApplet_panel.RECT;
    		if(parmstr.compareTo("circle")==0) FlyApplet_panel.ctype=FlyApplet_panel.CIRCLE;
	        if(parmstr.compareTo("lines")==0) FlyApplet_panel.ctype=FlyApplet_panel.LINES;
	        if(parmstr.compareTo("mlines")==0) FlyApplet_panel.ctype=FlyApplet_panel.MLINES;
	        if(parmstr.compareTo("multilines")==0) FlyApplet_panel.ctype=FlyApplet_panel.MLINES;
	        if(parmstr.compareTo("segments")==0) FlyApplet_panel.ctype=FlyApplet_panel.LINES;
	        if(parmstr.compareTo("line")==0) FlyApplet_panel.ctype=FlyApplet_panel.LINE;
	        if(parmstr.compareTo("sline")==0) FlyApplet_panel.ctype=FlyApplet_panel.SLINE;
	        if(parmstr.compareTo("semiline")==0) FlyApplet_panel.ctype=FlyApplet_panel.SLINE;
	        if(parmstr.compareTo("seg")==0) FlyApplet_panel.ctype=FlyApplet_panel.SEG;
	        if(parmstr.compareTo("segment")==0) FlyApplet_panel.ctype=FlyApplet_panel.SEG;
    	        if(parmstr.compareTo("poly")==0) FlyApplet_panel.ctype=FlyApplet_panel.POLY;
	        if(parmstr.compareTo("polygon")==0) FlyApplet_panel.ctype=FlyApplet_panel.POLY;
	        if(parmstr.compareTo("points")==0) FlyApplet_panel.ctype=FlyApplet_panel.POINTS;
	        if(parmstr.compareTo("vec")==0) FlyApplet_panel.ctype=FlyApplet_panel.VEC;
	        if(parmstr.compareTo("vector")==0) FlyApplet_panel.ctype=FlyApplet_panel.VEC;
	        
	    }
	    parmstr=getParameter("replyurl");
	    if(parmstr!=null && parmstr.length()>0){ replystring = parmstr;}
	    else{ replystring="http://localhost/wims.cgi?";}
	    
	    parmstr=getParameter("retry");
	    if(parmstr!=null && parmstr.length()>0){retry = parmstr;}
	
	    parmstr=getParameter("prompt");
	    if(parmstr!=null && parmstr.length()>0){prompt=parmstr;}
	    
	    parmstr=getParameter("dashed");
	    if(parmstr!=null && parmstr.length()>0){ dashed = true;}
	    
	    parmstr=getParameter("linewidth");
	    if(parmstr!=null && parmstr.length()>0){linewidth =  Integer.parseInt(parmstr);}
	    
	    parmstr=getParameter("alpha");
	    if(parmstr!=null && parmstr.length()>0){
		alpha =  Integer.parseInt(parmstr);
		clickcolor = MakeTransparent(clickcolor,alpha);
	    }

	    parmstr=getParameter("pointstyle");
	    if(parmstr!=null && parmstr.length()>0){if(parmstr.equalsIgnoreCase("dot")){cross = false;}}
	    
	    parmstr=getParameter("background");
	    if (parmstr!=null && parmstr.length()>0){
		try {url=new URL(parmstr);}
		catch (MalformedURLException e) {url=null;}
		if(url != null){
		    try{
			bg = (BufferedImage) ImageIO.read(url); 
	    	    }catch(IOException e){DeBug("can not load image from "+url+"\n"+e); bg = null;}	
		}
	    }
	    parmstr=getParameter("bgcolor");
	    if(parmstr!=null && parmstr.length()>0) {
		bgcolor=Color.decode(parmstr);
		if(bgcolor==null) bgcolor=Color.white;
	    }
	    else bgcolor=Color.white;
	
	}catch(Exception e){DeBug("Applet will not run in Gang's Input.java mode");}
	
	if(use_coords){
	    textfieldfont = new Font("Helvetica", Font.BOLD, 16); 
	}
	setLayout(new BorderLayout());
	panel=new FlyApplet_panel(bgcolor,clickcolor,bg,linewidth,xsize,ysize,dashed,use_coords,precision,xmin,ymin,xmax,ymax,textfieldfont,cross);
	
	controls=new FlyApplet_controls(panel,this);
	add("Center", panel);
	if(use_controls){add("South",controls);}
    }//init end

    public void destroy() {
        remove(panel);
	if(use_controls){remove(controls);}
    }

    public void replyback() {
	try {backurl=new URL(panel.points2string(replystring));}
	catch (MalformedURLException e) {backurl=null;}
	getAppletContext().showDocument(backurl,"_self");
	destroy();
    }
    
    public String ReadText(){
	String reply = "";
	if(use_inputarea){
	    boolean first = true;
	    for(int i = 0; i < inputfieldindex ;i++){
		if(first){
		    reply = inputfield[i].getText();
		    first= false;
		}
		else
		{
		    reply = reply + "," + inputfield[i].getText();
		}
	    }
	}
	return reply;    
    }

    public String ReadDrawing(){
	String reply = "";
	if((panel.Coords2String()).length() == 0){reply = "error";}else{reply=panel.Coords2String();}
	return reply;    
    }
    
    public String getAppletInfo() {
        return "Interactive image & draw applet for WIMS.\nUsing Javia libs for curve plotting\nDerived from X.Gang's Input.java\nSun's Draw.java";
    }

    public void DeBug(String error){
	if(debug){
	    System.out.println(error);
	}
    }
    public void ReadFlyScript(String s){
        StringTokenizer lines = new StringTokenizer(s, "\n");
        int m=lines.countTokens();
        String tmp;
	for(int i=0 ; i<m ;i++){
	    tmp = lines.nextToken();
	    DeBug("reading script line "+i+": "+tmp);
	    if( tmp.indexOf("#") == 0 || tmp.indexOf("%") == 0 ){DeBug("ignoring line "+i); }
	    else{
	    if(!ExecuteCommand(tmp)){DeBug("line "+i+" : "+tmp);}
	    }
	}
	prepaint();// create the image in background.
    }

    public void prepaint(){
	if(object_count >0){
	    int l=1;
	    for(int i=0;i<object_count;i++){
		if(objects.elementAt(i) instanceof FlyArrow){
		    if(((FlyArrow)objects.elementAt(i)).getDashed() == true){
			backg.setStroke(
			    new BasicStroke(
				((FlyArrow)objects.elementAt(i)).getLineWidth(), 
				BasicStroke.JOIN_ROUND,
				BasicStroke.JOIN_BEVEL,
				1,
				new float[] {9},  0
			    )
			);
		    }
		    else
		    { 
			backg.setStroke(
			    new BasicStroke(
		    		((FlyArrow)objects.elementAt(i)).getLineWidth(),
			        BasicStroke.JOIN_ROUND,
				BasicStroke.JOIN_BEVEL
				)
			);
		    }
		    backg.setColor(((FlyArrow)objects.elementAt(i)).getColor());
		    int mx[] = ((FlyArrow)objects.elementAt(i)).getX();
		    int my[] = ((FlyArrow)objects.elementAt(i)).getY();
		    backg.drawLine( mx[0],my[0],mx[1],my[1]);
		    backg.drawLine( mx[2],my[2],mx[1],my[1]);
		    backg.drawLine( mx[3],my[3],mx[1],my[1]);
		}
		else
		if(objects.elementAt(i) instanceof FlyInput){
		    int index = ((FlyInput)objects.elementAt(i)).getIndex();
		    inputfield[index] = new TextArea( ((FlyInput)objects.elementAt(i)).getValue() ,100,1,3);
		    add(inputfield[index]);
		    inputfield[index].setFont( ((FlyInput)objects.elementAt(i)).getFont() );
		    inputfield[index].setBackground( ((FlyInput)objects.elementAt(i)).getBgcolor() );
		    inputfield[index].setForeground( ((FlyInput)objects.elementAt(i)).getFgcolor() );
		    inputfield[index].setBounds(
			((FlyInput)objects.elementAt(i)).getX(),
			((FlyInput)objects.elementAt(i)).getY(),
			((FlyInput)objects.elementAt(i)).getXsize(),
			((FlyInput)objects.elementAt(i)).getYsize()
		    );
		    inputfield[index].setEditable(((FlyInput)objects.elementAt(i)).getEditable());
		    inputfield[index].setVisible(true);
		}
		else
		if(objects.elementAt(i) instanceof FlyLatex){
		    backg.drawImage(((FlyLatex)objects.elementAt(i)).getLatex(),((FlyLatex)objects.elementAt(i)).getX(),((FlyLatex)objects.elementAt(i)).getY(),this);
		}
		else
		if(objects.elementAt(i) instanceof FlyXscale){
		    if(((FlyXscale)objects.elementAt(i)).use_xscale()){
			backg.setStroke( new BasicStroke(((FlyXscale)objects.elementAt(i)).getLineWidth()));
			backg.setColor(((FlyXscale)objects.elementAt(i)).getColor());
			backg.setFont(((FlyXscale)objects.elementAt(i)).getFont());
			FontMetrics fm = backg.getFontMetrics(((FlyXscale)objects.elementAt(i)).getFont());
			int h = fm.getHeight();
			int w = 0;
			int y0 =(int)( y2px(0));
			int xtics[] = ((FlyXscale)objects.elementAt(i)).getX();
			String[] xlabels = ((FlyXscale)objects.elementAt(i)).getXlabel();
			for(int p=0;p<xtics.length;p++){
			    if(xlabels[p] != null){
				w = (int) (fm.stringWidth(xlabels[p])/2);
				backg.drawLine(xtics[p],y0 - h/4,xtics[p],y0 + h/4);
				backg.drawString(xlabels[p],xtics[p] - w,y0 + h);
			    }
			}
		    }
		}
		else
		if(objects.elementAt(i) instanceof FlyYscale){
		    if(((FlyYscale)objects.elementAt(i)).use_yscale()){
			backg.setStroke( new BasicStroke(((FlyYscale)objects.elementAt(i)).getLineWidth()));
			backg.setColor(((FlyYscale)objects.elementAt(i)).getColor());
			backg.setFont(((FlyYscale)objects.elementAt(i)).getFont());
			FontMetrics fm = backg.getFontMetrics(((FlyYscale)objects.elementAt(i)).getFont());
			int h = fm.getHeight();
			int w = 0;
			int x0 =(int)( x2px(0));
			int ytics[] = ((FlyYscale)objects.elementAt(i)).getY();
			String[] ylabels = ((FlyYscale)objects.elementAt(i)).getYlabel();
			for(int p=0;p<ytics.length;p++){
			    if(ylabels[p] != null){
				w = fm.stringWidth(ylabels[p]+" ");
				backg.drawLine(x0 - h/4,ytics[p],x0 + h/4,ytics[p]);
				backg.drawString(ylabels[p],x0 - w - h/3 , ytics[p]+h/4);
			    }
			}
		    }
		}
		else
		if(objects.elementAt(i) instanceof FlyArc){
		    if(((FlyArc)objects.elementAt(i)).getDashed() == true){
			backg.setStroke(
			    new BasicStroke(
				((FlyArc)objects.elementAt(i)).getLineWidth(), 
				BasicStroke.JOIN_ROUND,
				BasicStroke.JOIN_BEVEL,
				1,
				new float[] {9},  0
			    )
			);
		    }
		    else
		    { 
			backg.setStroke( new BasicStroke(((FlyArc)objects.elementAt(i)).getLineWidth()));
		    }
		    backg.setColor(((FlyArc)objects.elementAt(i)).getColor());
		    if( ((FlyArc)objects.elementAt(i)).getFilled() ){
			backg.fillArc(
			((FlyArc)objects.elementAt(i)).getXc(),
		        ((FlyArc)objects.elementAt(i)).getYc(),
			((FlyArc)objects.elementAt(i)).getW(),
		        ((FlyArc)objects.elementAt(i)).getH(),
		        ((FlyArc)objects.elementAt(i)).getAngle1(),
		        ((FlyArc)objects.elementAt(i)).getAngle2());
		    }
		    else
		    {
			backg.drawArc(
			((FlyArc)objects.elementAt(i)).getXc(),
			((FlyArc)objects.elementAt(i)).getYc(),
		        ((FlyArc)objects.elementAt(i)).getW(),
			((FlyArc)objects.elementAt(i)).getH(),
		        ((FlyArc)objects.elementAt(i)).getAngle1(),
		        ((FlyArc)objects.elementAt(i)).getAngle2());
		    }
		}
		else
	    	if (objects.elementAt(i) instanceof FlyText){
		    backg.setColor(((FlyText)objects.elementAt(i)).getColor());
		    backg.setFont(((FlyText)objects.elementAt(i)).getFont());
		    AffineTransform at = new AffineTransform();
		    at.rotate(Math.PI*2*(((FlyText)objects.elementAt(i)).getRotation())/360,((FlyText)objects.elementAt(i)).getX(),((FlyText)objects.elementAt(i)).getY());
		    backg.setTransform(at);
		    backg.drawString(
		    ((FlyText)objects.elementAt(i)).getTXT(),
		    ((FlyText)objects.elementAt(i)).getX(),
		    ((FlyText)objects.elementAt(i)).getY()
		    );		    
		    at = new AffineTransform(); // reset otherwise all will be rotated...
		    at.rotate(0);backg.setTransform(at);
		}
		else
	    	if (objects.elementAt(i) instanceof FlyGrid){
		    // minor first
		    if(((FlyGrid)objects.elementAt(i)).getDashed() == true){
			backg.setStroke(
			    new BasicStroke(
				((FlyGrid)objects.elementAt(i)).getLineWidth_minor(), 
				BasicStroke.JOIN_ROUND,
				BasicStroke.JOIN_BEVEL,
				1,
				new float[] {9},  0
			    )
			);
		    }
		    else
		    { 
			backg.setStroke( new BasicStroke(((FlyGrid)objects.elementAt(i)).getLineWidth_minor()));
		    } 
		    backg.setColor(((FlyGrid)objects.elementAt(i)).getColor_minor());
		    int mx[] = ((FlyGrid)objects.elementAt(i)).getX_minor();
		    int my[] = ((FlyGrid)objects.elementAt(i)).getY_minor();
		    for(int p=0;p<mx.length;p++){
			backg.drawLine( mx[p],0,mx[p],ysize);
		    }
		    for(int p=0;p<my.length;p++){
			backg.drawLine(0,my[p],xsize,my[p]);
		    }
		    if(((FlyGrid)objects.elementAt(i)).getDashed() == true){
			backg.setStroke(
			    new BasicStroke(
				((FlyGrid)objects.elementAt(i)).getLineWidth_major(), 
				BasicStroke.JOIN_ROUND,
				BasicStroke.JOIN_BEVEL,
				1,
				new float[] {9},  0
			    )
			);
		    }
		    else
		    { 
			backg.setStroke( new BasicStroke(((FlyGrid)objects.elementAt(i)).getLineWidth_major()));
		    } 
		    int Mx[] = ((FlyGrid)objects.elementAt(i)).getX_major();
		    int My[] = ((FlyGrid)objects.elementAt(i)).getY_major();
		    backg.setColor(((FlyGrid)objects.elementAt(i)).getColor_major());
		    for(int p=0;p<Mx.length;p++){
			backg.drawLine( Mx[p],0,Mx[p],ysize);
		    }
		    for(int p=0;p<My.length;p++){
			backg.drawLine(0,My[p],xsize,My[p]);
		    }
		}
		else
	    	if (objects.elementAt(i) instanceof FlyLine){
		    if(((FlyLine)objects.elementAt(i)).getDashed() == true){
			backg.setStroke(
			    new BasicStroke(
				((FlyLine)objects.elementAt(i)).getLineWidth(), 
				BasicStroke.JOIN_ROUND,
				BasicStroke.JOIN_BEVEL,
				1,
				new float[] {9},  0
			    )
			);
		    }
		    else
		    { 
			backg.setStroke( new BasicStroke(((FlyLine)objects.elementAt(i)).getLineWidth()));
		    }
		    backg.setColor(((FlyLine)objects.elementAt(i)).getColor());
		    backg.drawLine(
		    ((FlyLine)objects.elementAt(i)).getX1(),
		    ((FlyLine)objects.elementAt(i)).getY1(),
		    ((FlyLine)objects.elementAt(i)).getX2(),
		    ((FlyLine)objects.elementAt(i)).getY2()
		    );
		}
		else
	    	if (objects.elementAt(i) instanceof FlyParallel){
		    if(((FlyParallel)objects.elementAt(i)).getDashed() == true){
			backg.setStroke(
			    new BasicStroke(
				((FlyParallel)objects.elementAt(i)).getLineWidth(), 
				BasicStroke.JOIN_ROUND,
				BasicStroke.JOIN_BEVEL,
				1,
				new float[] {9},  0
			    )
			);
		    }
		    else
		    { 
			backg.setStroke( new BasicStroke(((FlyParallel)objects.elementAt(i)).getLineWidth()));
		    }
		    backg.setColor(((FlyParallel)objects.elementAt(i)).getColor());
		    int x1[]=(((FlyParallel)objects.elementAt(i)).getX1());
		    int y1[]=(((FlyParallel)objects.elementAt(i)).getY1());
		    int x2[]=(((FlyParallel)objects.elementAt(i)).getX2());
		    int y2[]=(((FlyParallel)objects.elementAt(i)).getY2());
		    for( int p = 0 ; p<x1.length; p++){
			backg.drawLine(x1[p],y1[p],x2[p],y2[p]);
		    }
		}
		else
	    	if (objects.elementAt(i) instanceof FlyPoly){
		    if(((FlyPoly)objects.elementAt(i)).getDashed() == true){
			backg.setStroke(
			    new BasicStroke(
				((FlyPoly)objects.elementAt(i)).getLineWidth(), 
				BasicStroke.JOIN_ROUND,
				BasicStroke.JOIN_BEVEL,
				1,
				new float[] {9},  0
			    )
			);
		    }
		    else
		    { 
			backg.setStroke( new BasicStroke(((FlyPoly)objects.elementAt(i)).getLineWidth()));
		    }
		    backg.setColor(((FlyPoly)objects.elementAt(i)).getColor());
		    Polygon poly = new Polygon(
		    (((FlyPoly)objects.elementAt(i)).getX()),
		    (((FlyPoly)objects.elementAt(i)).getY()),
		    (((FlyPoly)objects.elementAt(i)).getX()).length
		    );
		    if( ((FlyPoly)objects.elementAt(i)).getFilled()){ backg.fillPolygon(poly);}
		    else{ backg.drawPolygon(poly);}
		}
		else
	    	if (objects.elementAt(i) instanceof FlyPlot){
		    if(((FlyPlot)objects.elementAt(i)).getDashed() == true){
			backg.setStroke(
			    new BasicStroke(
				((FlyPlot)objects.elementAt(i)).getLineWidth(), 
				BasicStroke.JOIN_ROUND,
				BasicStroke.JOIN_BEVEL,
				1,
				new float[] {9},  0
			    )
			);
		    }
		    else
		    { 
			backg.setStroke( new BasicStroke(((FlyPlot)objects.elementAt(i)).getLineWidth()));
		    }
		    backg.setColor(((FlyPlot)objects.elementAt(i)).getColor());
		    int x[]=(((FlyPlot)objects.elementAt(i)).getX());
		    int y[]=(((FlyPlot)objects.elementAt(i)).getY());
		    for(int p=0;p<x.length - 1;p++){
			if(y[p] < ysize && y[p+1] < ysize ){
			    backg.drawLine(x[p],y[p],x[p+1],y[p+1]);
			}else{p++;}
		    }
		}
		else
	    	if (objects.elementAt(i) instanceof FlyImage){
		    backg.drawImage(
			(((FlyImage)objects.elementAt(i)).getImage()),
			(((FlyImage)objects.elementAt(i)).getX()),
			(((FlyImage)objects.elementAt(i)).getY()),
			this
		    );
		}
		else
	    	if (objects.elementAt(i) instanceof FlyPoints){
		    l = ((FlyPoints)objects.elementAt(i)).getLineWidth();
		    backg.setStroke( new BasicStroke(l));
		    backg.setColor(((FlyPoints)objects.elementAt(i)).getColor());
		    int x[]=(((FlyPoints)objects.elementAt(i)).getX());
		    int y[]=(((FlyPoints)objects.elementAt(i)).getY());
		    for(int p=0;p<x.length;p++){
			backg.fillOval(x[p],y[p], l, l);
		    }
		}
		else
	    	if (objects.elementAt(i) instanceof FlyPoint){
		    l = ((FlyPoints)objects.elementAt(i)).getLineWidth();
		    backg.setStroke( new BasicStroke(l));
		    backg.setColor(((FlyPoint)objects.elementAt(i)).getColor());
		    int x=(((FlyPoint)objects.elementAt(i)).getX());
		    int y=(((FlyPoint)objects.elementAt(i)).getY());
		    backg.fillOval(x,y, l, l);
		}
		else
	    	if (objects.elementAt(i) instanceof FlyRect){
		    if(((FlyRect)objects.elementAt(i)).getDashed() == true){
			backg.setStroke(
			    new BasicStroke(
				((FlyRect)objects.elementAt(i)).getLineWidth(), 
				BasicStroke.JOIN_ROUND,
				BasicStroke.JOIN_BEVEL,
				1,
				new float[] {9},  0
			    )
			);
		    }
		    else
		    { 
			backg.setStroke( new BasicStroke(((FlyRect)objects.elementAt(i)).getLineWidth()));
		    }
		
		    backg.setColor(((FlyRect)objects.elementAt(i)).getColor());
		    if(((FlyRect)objects.elementAt(i)).getFilled()){
			backg.fillRect(
			((FlyRect)objects.elementAt(i)).getX(),
		        ((FlyRect)objects.elementAt(i)).getY(),
			((FlyRect)objects.elementAt(i)).getW(),
		        ((FlyRect)objects.elementAt(i)).getH());
		    }
		    else
		    {
			backg.drawRect(
			((FlyRect)objects.elementAt(i)).getX(),
			((FlyRect)objects.elementAt(i)).getY(),
			((FlyRect)objects.elementAt(i)).getW(),
			((FlyRect)objects.elementAt(i)).getH());
		    }
		}
		else
		if (objects.elementAt(i) instanceof FlyXlabel){
		    backg.setColor(((FlyXlabel)objects.elementAt(i)).getColor());
		    backg.setFont(((FlyXlabel)objects.elementAt(i)).getFont());
		    FontMetrics fm = backg.getFontMetrics(((FlyXlabel)objects.elementAt(i)).getFont());
		    int h = fm.getHeight();
		    int w = fm.stringWidth(((FlyXlabel)objects.elementAt(i)).getXlabel()+" ");
		    int y =(int) (y2px(0) + 1.5*h);
		    int x = (int) (x2px(xmax) - w);
		    backg.drawString(((FlyXlabel)objects.elementAt(i)).getXlabel(),x,y);
		}
		else
		if (objects.elementAt(i) instanceof FlyYlabel){
		    backg.setColor(((FlyYlabel)objects.elementAt(i)).getColor());
		    backg.setFont(((FlyYlabel)objects.elementAt(i)).getFont());
		    FontMetrics fm = backg.getFontMetrics(((FlyYlabel)objects.elementAt(i)).getFont());
		    int h = fm.getHeight();
		    int w = fm.stringWidth(((FlyYlabel)objects.elementAt(i)).getYlabel()+" ");
		    int x =(int) (x2px(0) - w);
		    int y = (int) (y2px(ymax) + h);
		    backg.drawString(((FlyYlabel)objects.elementAt(i)).getYlabel(),x,y);
		}		
	    	if (objects.elementAt(i) instanceof FlyCircle){// nothing yet x;y;width px;height px
		    if(((FlyCircle)objects.elementAt(i)).getDashed() == true){
			backg.setStroke(
			    new BasicStroke(
				((FlyCircle)objects.elementAt(i)).getLineWidth(), 
				BasicStroke.JOIN_ROUND,
				BasicStroke.JOIN_BEVEL,
				1,
				new float[] {9},  0
			    )
			);
		    }
		    else
		    { 
			backg.setStroke( new BasicStroke(((FlyCircle)objects.elementAt(i)).getLineWidth()));
		    }
		    backg.setColor(((FlyCircle)objects.elementAt(i)).getColor());
		    if(((FlyCircle)objects.elementAt(i)).getFilled()){
			backg.fillOval(
			((FlyCircle)objects.elementAt(i)).getXc(),
		        ((FlyCircle)objects.elementAt(i)).getYc(),
			((FlyCircle)objects.elementAt(i)).getW(),
		        ((FlyCircle)objects.elementAt(i)).getH());
		    }
		    else
		    {
			backg.drawOval(
			((FlyCircle)objects.elementAt(i)).getXc(),
			((FlyCircle)objects.elementAt(i)).getYc(),
		        ((FlyCircle)objects.elementAt(i)).getW(),
			((FlyCircle)objects.elementAt(i)).getH());
		    }
		}
	    }
	}
    }


    public boolean ExecuteCommand(String line){ // analyze script line by line
	String[] words = String2Array(line); // command,x,y,z,blah blah,1,2,3
        boolean filled = false;
        boolean dashed = false;
	String cmd = words[0].toLowerCase();
        Color color = new Color(0,0,0,1); // use black as default	
        if(cmd.equals("debug")){// linewidth 5
	    debug = true;
	    try{
	    if(words[1] != null){
		if(words[1].equalsIgnoreCase("no") || words[1].equalsIgnoreCase("off") || words[1].equals("0")){debug = false;}
		}else{
		    debug = true;
		}
	    }catch(Exception e){}
	    return debug;
	}
	else
	// check on key_char "d" or "f" as first letter in command
        if(cmd.indexOf("f") == 0 ){
	    filled = true;DeBug("setting filled");
	}
	else
	if(cmd.indexOf("d") == 0){
	    dashed = true;DeBug("setting dashed"); // drect dline dpoly
	}
	else
	if(cmd.equals("xrange")){
	    boolean ok=true;
	    try{ xmin = symbols.eval(words[1]);}catch(SyntaxException e){ok=false;DeBug("could not set xmin : error "+e);}
	    try{ xmax = symbols.eval(words[2]);}catch(SyntaxException e){ok=false;DeBug("could not set xmax : error "+e);}
	    if(ok){
		if( xmax < xmin){
		    double t = xmin;
	    	    xmin = xmax;
		    xmax= t;
	    	    DeBug("xmin is larger than xmax...correcting :xmin ="+xmin+" xmax ="+xmax);
		}
		else
		{
		    if( xmax == xmin){
			xmin=-1*(Math.abs(xmin));xmax=Math.abs(xmax);
		    }
		}
		return true;
	    } 
	    else 
	    { 
		return false; 
	    }
	}
	else
	if(cmd.equals("scalelatex") || cmd.equals("scaletex")){
	// scalelatex 1,1,width,height,latexstring,bgcolor,fgcolor,bg_alpha,fg_alpha
	    TeX = new sHotEqn();int x;int y;int w;int h;
	    Color bgc = bgcolor;
	    Color fgc = clickcolor;
	    try{ 
		x = (int) x2px(symbols.eval(words[1]));
		y = (int) y2px(symbols.eval(words[2]));
		w = (int) (symbols.eval(words[3]));
		h = (int) (symbols.eval(words[4]));
		w = (int) (w*xsize/(Math.abs(xmax - xmin)));
		h = (int) (h*ysize/(Math.abs(ymax - ymin)));
	    }catch( SyntaxException e ){ DeBug("could not set x/y  error :"+e); return false;}
	    
	    try{
		bgc = GetInternalColorCode(words[6]);
		fgc = GetInternalColorCode(words[7]);
	    }catch(Exception e){DeBug("will use default colors for latex image");}
	    try{alpha = Integer.parseInt(words[8]);bgc = MakeTransparent(bgc,alpha);}catch(Exception e){}
	    try{alpha = Integer.parseInt(words[9]);fgc = MakeTransparent(fgc,alpha);}catch(Exception e){}
	    TeX.setEquation(words[5]);
	    BufferedImage img = TeX.mkImage(bgc,fgc,xsize,ysize);
	    BufferedImage scaled_image = new BufferedImage(w,h, BufferedImage.TYPE_INT_ARGB );
	    Graphics2D g2d = (Graphics2D) scaled_image.getGraphics();
	    AffineTransform affinetransform = AffineTransform.getScaleInstance((double) w / (double)img.getWidth(), (double) h / (double)img.getHeight());
	    g2d.drawRenderedImage(img, affinetransform);
	    img = scaled_image;
	    try{
		objects.add(new FlyLatex(x,y,img));
		object_count++;
		DeBug("loaded tex string as image");
		return true;
	    }catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.equals("latex") || cmd.equals("tex")){
	    TeX = new sHotEqn();int x;int y;
	    Color fgc = clickcolor;
	    Color bgc = bgcolor;
	    try{ 
		x = (int) x2px(symbols.eval(words[1]));
		y = (int) y2px(symbols.eval(words[2]));
	    }catch( SyntaxException e ){ DeBug("could not set x/y  error :"+e); return false;}
	    try{
		bgc = GetInternalColorCode(words[4]);
		fgc = GetInternalColorCode(words[5]);
	    }catch(Exception e){DeBug("will use default colors for latex image");}
	    try{
		alpha = Integer.parseInt(words[6]);bgc = MakeTransparent(bgc,alpha);
		alpha = Integer.parseInt(words[7]);fgc = MakeTransparent(fgc,alpha);
	    }catch(Exception e){}
	    TeX.setEquation(words[3]);
	    BufferedImage img = TeX.mkImage(bgc,fgc,xsize,ysize);
	    try{
		objects.add(new FlyLatex(x,y,img));
		object_count++;
		DeBug("loaded tex string as image");
		return true;
	    }catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.equals("yrange")){
	    boolean ok=true;
	    try{ ymin = symbols.eval(words[1]);}catch(SyntaxException e){ok=false;DeBug("could not set ymin : error "+e);}
	    try{ ymax = symbols.eval(words[2]);}catch(SyntaxException e){ok=false;DeBug("could not set ymax : error "+e);}
	    if(ok){
		if(ymax < ymin){
		    double t = ymin;
	    	    ymin = ymax;
	    	    ymax= t;
	    	    DeBug("ymin is larger than ymax...correcting :ymin ="+ymin+" ymax ="+ymax);
		}
		else
		{
		    if( ymax == ymin ){
			ymin=-1*(Math.abs(ymin));ymax=Math.abs(ymax);
		    }
		}
		return true;
	    }
	    else
	    { 
		return true; 
	    }
	}
	else
        if(cmd.equals("transparent")){
    	    try{
    		bgcolor = GetInternalColorCode(words[1]);// transparent blue,100
	        alpha = Integer.parseInt(words[2]);
    		bgcolor = MakeTransparent(bgcolor,alpha);
	        this.setBackground(bgcolor);
	    }
	    catch(Exception e){
	    	bgcolor = GetInternalColorCode(words[1]);// transparent blue
		bgcolor = MakeTransparent(bgcolor,0);
		this.setBackground(bgcolor);
	    }
	    DeBug("setting transparent color to :"+bgcolor);
	    return true;
	}
	else
	if(cmd.equals("clickcolor")){
	    try{
		clickcolor = GetInternalColorCode(words[1]);// transparent blue,100
		alpha = Integer.parseInt(words[2]);
		clickcolor = MakeTransparent(clickcolor,alpha);
	    }
	    catch(Exception e){
		try{
		    clickcolor = GetInternalColorCode(words[1]);// transparent blue
		    clickcolor = MakeTransparent(clickcolor,255);
		}catch(Exception ex){DeBug("unable to set color to "+words[1]+" will use default :"+clickcolor);}
	    }
	    DeBug("setting mouse clickcolor to :"+clickcolor);
	    return true;
	}
	else
	if(cmd.equals("precision")){// 1000 -> 3 decimals
	    try{precision = new  Double(words[1]).doubleValue(); DeBug("setting precision to :"+precision);}
	    catch(Exception e){ DeBug("could not set precision");return false;}
	    return true;
	}
	else
	if(cmd.equals("coordinates")){
	    try{
		if(words[1].equalsIgnoreCase("yes") || words[1].equals("1")  ){use_coords = true;}else{use_coords = false;}// of no use without a mouse
	    }catch(Exception e){use_coords = false;DeBug("Setting "+words[0]+" to false");}
	    return true;
	}
	else
	if(cmd.equals("controls")){ // wims control buttons
	    try{
		if(words[1].equalsIgnoreCase("yes") || words[1].equals("1") ){use_controls=true;}else{use_controls=false;}
	    }catch(Exception e){DeBug("Setting "+words[0]+" to false");return false;}	
	}
	else
	if(cmd.equals("replyurl")){ // wims reply url
	    try{replystring = words[0];return true; }catch(Exception e){DeBug("Could not read "+words[0]);return false;}
	}
	else
	if(cmd.equals("pointstyle")){ // draw dot or cross
	    try{    
		if(words[1].equalsIgnoreCase("cross")){cross = true;return true;}
		else
		if(words[1].equalsIgnoreCase("dot")){cross = false;return true;}
	    }catch(Exception e){cross = false;DeBug("Setting "+words[0]+" to false");}
	    return true;
	}
	else
	if(cmd.equals("userdraw")){ // drawing primitives ex-wims
	    try{
		if(words[1].equalsIgnoreCase("points")||words[1].equalsIgnoreCase("point")){FlyApplet_panel.ctype=8;}
		else
		if(words[1].equalsIgnoreCase("line")){FlyApplet_panel.ctype=4;}
		else
		if(words[1].equalsIgnoreCase("mlines")){FlyApplet_panel.ctype=10;}
		else
		if(words[1].equalsIgnoreCase("multilines")){FlyApplet_panel.ctype=10;}
		else
		if(words[1].equalsIgnoreCase("circle")){FlyApplet_panel.ctype=2;}
		else
		if(words[1].equalsIgnoreCase("fcircle")){FlyApplet_panel.ctype=2;FlyApplet_panel.filled=true;}
		else
		if(words[1].equalsIgnoreCase("segment") || words[1].equalsIgnoreCase("seg")){FlyApplet_panel.ctype=6;}
		else
		if(words[1].equalsIgnoreCase("rect") || words[1].equalsIgnoreCase("rectangle") ){FlyApplet_panel.ctype=1;}
		else
		if(words[1].equalsIgnoreCase("frect") || words[1].equalsIgnoreCase("frectangle") ){FlyApplet_panel.ctype=1;FlyApplet_panel.filled=true;}
		else
		if(words[1].equalsIgnoreCase("lines") || words[1].equalsIgnoreCase("segments") ){FlyApplet_panel.ctype=3;}
		else
		if(words[1].equalsIgnoreCase("vector") || words[1].equalsIgnoreCase("vec")){FlyApplet_panel.ctype=9;}
		else
		if(words[1].equalsIgnoreCase("fpolygon") || words[1].equalsIgnoreCase("fpoly")){FlyApplet_panel.ctype=7;FlyApplet_panel.filled=true;}
		else
		if(words[1].equalsIgnoreCase("polygon") || words[1].equalsIgnoreCase("poly")){FlyApplet_panel.ctype=7;}
		else
		if(words[1].equalsIgnoreCase("curve")){FlyApplet_panel.ctype=0;}
		else
		if(words[1].equalsIgnoreCase("sline") || words[1].equalsIgnoreCase("semiline")){FlyApplet_panel.ctype=5;}
		else{DeBug("could not set "+words[0]+" : "+words[1]) ; return false;}
		
	    }catch(Exception e){DeBug("could not set "+words[0]+" : "+words[1]);return false;}
	    DeBug("setting drawing primitive to "+words[1]);
	    return true;
	}
	else
	if(cmd.equals("inputfields") || cmd.equals("inputs")){ // number of inputfields
	    try{ 
		inputs = (int) symbols.eval(words[1]);
	    }catch( SyntaxException e ){DeBug("could not parse number of inputs  :"+e+"\n will use default = 20");}
	    return true;
	}
	else
//	 inputfield x,y,width,height,font,fontsize,bgcolor,fgcolor,editable,value
	if(cmd.equals("inputfield") || cmd.equals("input")){
	    inputfield  = new TextArea[inputs];
	    int x;
	    int y;
	    int w = 50;
	    int h = 25;
	    int fontsize = 12;
	    String fontname = "Times";
	    Color bgc = bgcolor;
	    Color fgc = clickcolor;
	    boolean editable = true;
	    String value = "";
	    try{ 
		x = (int) x2px(symbols.eval(words[1]));
		y = (int) y2px(symbols.eval(words[2]));
	    }catch( SyntaxException e ){ DeBug("could not parse inputfield  x/y param ; error :"+e); return false;}
	    if( words[3].length() != 0 && words[3] != null){
		try{
		    w = (int) ((symbols.eval(words[3]))*xsize/(Math.abs(xmax - xmin)));
		}catch(SyntaxException e){}
	    }else{ DeBug("could not parse inputfield width param. will use default.");}
	    if( words[4].length() != 0 && words[4] != null){
		try{
		    h = (int) ((symbols.eval(words[4]))*ysize/(Math.abs(ymax - ymin)));
		}catch(SyntaxException e){}
	    }else{ DeBug("could not parse inputfield height param. will use default.");}
	    try{
		fontname = words[5];
		fontsize = Integer.parseInt(words[6]);
		bgc = GetInternalColorCode(words[7]); // final word ?
		fgc = GetInternalColorCode(words[8]); // final word ?
	    
	    }catch( Exception e ){ DeBug("could not parse inputfield  font and color  params. will use defaults ; error :"+e);}
	    Font f  = new Font(fontname,Font.PLAIN,fontsize);
	    try{
		if( words[9].length() != 0 && words[9] != null){
		    if( words[9].equals("no") || words[9].equals("0") || words[9].equals("false")){   
			editable = false; 
		    }
		}else{ DeBug("could not parse inputfield editable param. will use true");}
		if( words[10].length() != 0 && words[10] != null ){
		    value = words[10];
		}else{ DeBug("could not parse inputfield value param. will use empty string.");}
	    }catch(Exception e){}
	    try{objects.add(new FlyInput(x,y,w,h,f,bgc,fgc,inputfieldindex,editable,value));inputfieldindex++;use_inputarea = true; object_count++;return true;}
	    catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.equals("mouse")){// mouse : yes/no 1/0
	    try{
		if(words[1].equalsIgnoreCase("yes") || words[1].equalsIgnoreCase("1")){ mouse=true;}else{mouse=false;}//check if "param mouse" is set  
	    }catch(Exception e){DeBug("could not set "+words[0]);}
	    return true;
	}
	else
	if(cmd.equals("linewidth") || cmd.equals("thickness")){// linewidth 5
	    try{linewidth = Integer.parseInt(words[1]);}catch(Exception e){ return false;}
	    return true;
	}
	else
	if(cmd.equals("image") || cmd.equals("background")){// linewidth 5
	    try {url = new URL(words[words.length-1]);}catch (Exception e) {url = null;DeBug("could not load image "+words[words.length-1]);}
	    if(url != null){
		int x=0;int y=0;
		try{
		    x = (int) x2px(symbols.eval(words[1]));
		    y = (int) y2px(symbols.eval(words[2]));

		}catch(SyntaxException e){ DeBug("Could not set leftcorner of image error :"+e); return false;}
		BufferedImage img; 
		try{
		    img = ImageIO.read(url);
		    if( x == 0 && y == 0 ){ // scale the image
			try{
			    BufferedImage scaled_image = new BufferedImage(xsize,ysize, BufferedImage.TYPE_INT_ARGB );
			    Graphics2D g2d = (Graphics2D) scaled_image.getGraphics();
			    AffineTransform affinetransform = AffineTransform.getScaleInstance((double)xsize / (double)img.getWidth(), (double)ysize / (double)img.getHeight());
			    g2d.drawRenderedImage(img, affinetransform);
			    img = scaled_image;
			    DeBug("scaling image to "+xsize+"x"+ysize);
			}
			catch(Exception e){DeBug("could not scale image ! ..."+e);}
	    	    }
		    else
		    {
			DeBug("not scaling image.\nTip: if you want to scale the image to the applet_size \nuse the syntax :\nimage "+xmin+","+ymax+","+url);
		    }
		}catch(IOException e){DeBug("can not load image from "+url+"\n"+e); return false;}	
	
		try{
		    objects.add(new FlyImage(x,y,img));
		    object_count++;
		    DeBug("loaded image from "+url);
		    return true;
		}catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	    }
	    return false;
	}
	else
	if(cmd.indexOf("arrow") !=-1){
	    int x[] = new int[4];
	    int y[] = new int[4];
	    try{ 
		x[0] = (int) x2px(symbols.eval(words[1]));
		y[0] = (int) y2px(symbols.eval(words[2]));
		x[1] = (int) x2px(symbols.eval(words[3]));
		y[1] = (int) y2px(symbols.eval(words[4])); 
	    }catch( SyntaxException e ){ DeBug("could not set x/y  error :"+e); return false;}
	    int deltaX = x[1] - x[0];
	    int deltaY = y[1] - y[0];
	    double frac = 1.0D;
	    try{ frac = symbols.eval(words[5]);}catch( SyntaxException e ){ DeBug("error "+e);}
	    x[2] = x[0] + (int)((1-frac)*deltaX + (0.5+linewidth/20)*frac*deltaY);
	    y[2] = y[0] + (int)((1-frac)*deltaY - (0.5+linewidth/20)*frac*deltaX);
	    x[3] = x[0] + (int)((1-frac)*deltaX - (0.5+linewidth/20)*frac*deltaY);
	    y[3] = y[0] + (int)((1-frac)*deltaY + (0.5+linewidth/20)*frac*deltaX);
	    color = GetInternalColorCode(words[6]);
	    try{alpha = Integer.parseInt(words[7]);color = MakeTransparent(color,alpha);
	    try{linewidth = Integer.parseInt(words[8]);}catch(Exception e){DeBug("no linewidth given...using previous value "+linewidth );}
	    }catch(Exception e){} 
	    try{objects.add(new FlyArrow(x,y,color,linewidth,filled,dashed));object_count++;return true;}
	    catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.indexOf("ylogscale") != -1){//Math.pow(10, p)
	// ylogscale ystart,yend,color[alpha,linewidth]
	    double exp = 10.0D;
	    int y1,y2;
	    boolean newsyntax=true;
	    try{
		y1=Integer.parseInt(words[1]);
		y2=Integer.parseInt(words[2]);
	    }catch(Exception e){
		y1=(int) ymin;
		y2=(int) ymax;
		newsyntax=false;
	    }
	    int num = (int) (exp*(y2-y1));
 	    int X1[] = new int[num];int X2[] = new int[num];
	    int Y1[] = new int[num];int Y2[] = new int[num];
	    int c=0;double m0;double m1;
	    for(int p=y1; p<y2;p++){
		m0 = Math.pow(exp,p);m1=0;
		for(int i=0;i<exp;i++){
		    X1[c]=0;
		    X2[c]=xsize;
		    m1 = m0 + m1;
		    Y1[c] = (int) (y2px(Math.log(m1)/(Math.log(exp))));
		    Y2[c] = Y1[c];
		    c++;
		}
	    }
	    if(newsyntax){
		color = GetInternalColorCode(words[3]);
		try{alpha = Integer.parseInt(words[4]);color = MakeTransparent(color,alpha);
		try{linewidth = Integer.parseInt(words[5]);}catch(Exception e){DeBug("no linewidth given...using previous value "+linewidth );}
		}catch(Exception e){}	    
	    }
	    else
	    {
		color = GetInternalColorCode(words[1]);
		try{alpha = Integer.parseInt(words[2]);color = MakeTransparent(color,alpha);
		try{linewidth = Integer.parseInt(words[3]);}catch(Exception e){DeBug("no linewidth given...using previous value "+linewidth );}
		}catch(Exception e){}
	    }
	    try{objects.add(new FlyParallel(X1,Y1,X2,Y2,color,linewidth,dashed));object_count++;return true;}
	    catch(Exception e){DeBug("could not set ylogscale : ylogscale ymin,ymax,color [,alpha,linewidth] ");}
	}
	else	
	if(cmd.indexOf("xlogscale") != -1){//Math.pow(10, p)
	    // xlogscale xstart,xend,color[alpha,linewidth]
	    double exp = 10.0D;
	    int x1,x2;
	    boolean newsyntax=true;
	    try{
		x1=Integer.parseInt(words[1]);
		x2=Integer.parseInt(words[2]);
	    }catch(Exception e){
		x1=(int) xmin;
		x2=(int) xmax;
		newsyntax=false;
	    }
	    int num = (int) (exp*(x2-x1));
 	    int X1[] = new int[num];int X2[] = new int[num];
	    int Y1[] = new int[num];int Y2[] = new int[num];
	    int c=0;double m0;double m1;
	    for(int p=x1; p<x2;p++){
		m0 = Math.pow(exp,p);m1=0;
		for(int i=0;i<exp;i++){
		    Y1[c]=0;
		    Y2[c]=ysize;
		    m1 = m0 + m1;
		    X1[c] = (int) (x2px(Math.log(m1)/(Math.log(exp))));
		    X2[c] = X1[c];
		    c++;
		}
	    }
	    if(newsyntax){
		color = GetInternalColorCode(words[2]);
		try{alpha = Integer.parseInt(words[3]);color = MakeTransparent(color,alpha);
		try{linewidth = Integer.parseInt(words[4]);}catch(Exception e){DeBug("no linewidth given...using previous value "+linewidth );}
		}catch(Exception e){}
	    }
	    else
	    {
		color = GetInternalColorCode(words[1]);
		try{alpha = Integer.parseInt(words[2]);color = MakeTransparent(color,alpha);
		try{linewidth = Integer.parseInt(words[3]);}catch(Exception e){DeBug("no linewidth given...using previous value "+linewidth );}
		}catch(Exception e){}
	    }	
	    try{objects.add(new FlyParallel(X1,Y1,X2,Y2,color,linewidth,dashed));object_count++;return true;}
	    catch(Exception e){DeBug("could not set ylogscale ");}
	}
	else
	if(cmd.indexOf("xlabel") != -1){
	    // xlabel x_axis-name,fontsize,fontname,[fontcolor,alpha]
	    int fontsize = 12;
	    String fontname = "Times";
	    String xl="x-axis";
	    color = Color.black;
	    try{
		xl = words[1];
		fontsize = Integer.parseInt(words[2]);
	    }catch(Exception e){DeBug("could not parse params for xlabel...use\n xlabel X-axis_name,fontsize,fontname,color,alpha ");return false;}
	    try{
		fontname = words[3];
		color = GetInternalColorCode(words[4]);
		try{
		    alpha = Integer.parseInt(words[5]);		
		    color = MakeTransparent(color,alpha);
		}catch(Exception e){}
	    }catch(Exception e){DeBug("can not read alpha : will use defaults");}
	    font  = new Font(fontname,Font.PLAIN,fontsize);
	    try{objects.add(new FlyXlabel(xl,font,color));object_count++;return true;}
	    catch(Exception e){DeBug("could not set xlabel ");}
	}
	else
	if(cmd.indexOf("ylabel") != -1){
	    // xlabel x_axis-name,fontsize,fontname
	    int fontsize = 12;
	    String fontname = "Times";
	    String yl="y-axis";
	    color = Color.black;
	    try{
		yl = words[1];
		fontsize = Integer.parseInt(words[2]);
	    }catch(Exception e){DeBug("could not parse params for ylabel...use\n ylabel y-axis_name,fontsize,fontname,color,alpha ");return false;}
	    try{
		color = GetInternalColorCode(words[4]);
		fontname = words[3];
		try{
		    alpha = Integer.parseInt(words[5]);
		    color = MakeTransparent(color,alpha);
		}catch(Exception e){}
	    }catch(Exception e){DeBug("can not read alpha : will use defaults");}
	    font  = new Font(fontname,Font.PLAIN,fontsize);
	    try{objects.add(new FlyYlabel(yl,font,color));object_count++;return true;}
	    catch(Exception e){DeBug("could not set xlabel ");}
	}
	else
	if(cmd.indexOf("xscale") != -1){
	    use_xscale = true;
	    //xscale x1,x1_name,x2,x2_name,x3,x3_name,....,fontsize,fontname,color,linewidth
	    //xscale -1,pi,0,0,1,pi,2,pi,22,Times,green,2
	    int dl = words.length - 4;
	    int xscale[] = new int[(dl)/2];
	    String xname[] = new String[(dl)/2];
	    try{
		int i=0;
		for(int p = 1 ; p < dl;p = p+2){
		    xscale[i] = (int)(x2px(symbols.eval(words[p])));
		    xname[i] = LaTeX2Uni(words[p+1]);
		    i++;
		}
	    }catch(SyntaxException e){DeBug("could not parse xscale param \n syntax is mandatory !\n xscale x1,x1_name,x2,x2_name,..., fontsize,fontname,color,linewidth \n : error "+ e);return false;}
	    try{
		fontsize = Integer.parseInt(words[dl]);
		fontname = words[dl+1];
		color = GetInternalColorCode(words[dl+2]); // final word ?
		linewidth = Integer.parseInt(words[dl+3]);
	    }catch(Exception e){DeBug("could not parse X fontparams : error "+ e);return false;}
		
	    font  = new Font(fontname,Font.PLAIN,fontsize);

	    try{
		objects.add(new FlyXscale(xscale,xname,use_xscale,font,color,linewidth));
		object_count++;return true;
	    }
	    catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.indexOf("yscale") != -1){
	    use_yscale = true;
	    //yscale y1,y1_name,y2,y2_name,y3,y3_name,....,fontsize,fontname,color,linewidth
	    int dl = words.length - 4;
	    int yscale[] = new int[(dl)/2];
	    String yname[] = new String[(dl)/2];
	    try{
		int i=0;
		for(int p = 1 ; p < dl;p = p+2){
		    yscale[i] =(int) (y2px(symbols.eval(words[p])));
		    yname[i] = LaTeX2Uni(words[p+1]);
		    i++;
		}
	    }catch(SyntaxException e){DeBug("could not parse yscale param \n syntax is mandatory !\n yscale y1,y1_name,y2,y2_name,..., fontsize,fontname,color,linewidth \n : error "+ e);return false;}
	    
	    try{
	    	fontsize = Integer.parseInt(words[dl]);
		fontname = words[dl+1];
		color = GetInternalColorCode(words[dl+2]);
		linewidth = Integer.parseInt(words[dl+3]);
	    }catch(Exception e){DeBug("could not parse Y fontparams : error "+ e);return false;}
		
	    font  = new Font(fontname,Font.PLAIN,fontsize);
	    
	    try{
		objects.add(new FlyYscale(yscale,yname,use_yscale,font,color,linewidth));
		object_count++;return true;
	    }
	    catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.indexOf("grid") !=-1){ //grid 1,1,0.5,0.5,red,blue,1,1
	    // step size in coords 
	    double Mx=1.0D,My=1.0D,mx=0.5D,my=0.5D;		 
	    try{ 
		Mx = symbols.eval(words[1]);
		My = symbols.eval(words[2]);
		mx = symbols.eval(words[3]);
		my = symbols.eval(words[4]);
	    }catch(SyntaxException e ) {DeBug("could not set x/y-major x/y minor : error "+e);return false; }
	    // calculate number of lines == length of array
	    int M1= (int) Math.abs((xmax-xmin)/Mx);// number of major vertical lines
	    int M2= (int) Math.abs((ymax-ymin)/My);// number of major horizontal lines
	    int m1= (int) Math.abs((xmax-xmin)/mx);// number of minor vertical lines
	    int m2= (int) Math.abs((ymax-ymin)/my);// number of minor horizontal lines
	    int[] xminor= new int[m1];
	    int[] yminor= new int[m2];
	    int[] xmajor= new int[M1];
	    int[] ymajor= new int[M2];
	    int Ml=2;//defaults 
	    int ml=1;
	    double s;
	    s=ymin;
	    for(int p=0;p<m2;p++){
		s = s + my;
		yminor[p] = (int) y2px(s);
	    }
	    s=ymin;
	    for(int p=0;p<M2;p++){
		s = s + My;
		ymajor[p] = (int) y2px(s);
	    }	    
	    s=xmin;
	    for(int p=0;p<m1;p++){
		s = s + mx;
		xminor[p] = (int) x2px(s);// convert to pixels 
	    }
	    s=xmin;
	    for(int p=0;p<M1;p++){
		s = s + Mx;
		xmajor[p] = (int) x2px(s);
	    }	    
	    Color Mc = GetInternalColorCode(words[5]); 
	    Color mc = GetInternalColorCode(words[6]); 
	    try{
		Ml=Integer.parseInt(words[7]);
		ml=Integer.parseInt(words[8]);
		alpha = Integer.parseInt(words[9]);Mc = MakeTransparent(Mc,alpha);
		alpha = Integer.parseInt(words[10]);mc = MakeTransparent(mc,alpha);
	    }catch(Exception e){DeBug("no alpha colors in grid defined.");}
	    try{objects.add(new FlyGrid(xmajor,ymajor,xminor,yminor,Mc,mc,Ml,ml,dashed));
		DeBug("setting grid ");
		object_count++;return true;
	    }catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.equals("plotsteps")){// linewidth 5
	    try{plotsteps = Integer.parseInt(words[1]);}catch(Exception e){DeBug("failed setting plotsteps :"+e);}
	    return true;
	}
	if(cmd.equals("plotjump")){// linewidth 5
	    try{plotjump = Integer.parseInt(words[1]);}catch(Exception e){DeBug("failed setting plotjump :"+e);}
	    return true;
	}
	else
	if(cmd.indexOf("parallel")!=-1 ){
	    int x1=1,y1=1,x2=1,y2=1,dx=1,dy=1;
	    try{ 
		x1 = (int) x2px(symbols.eval(words[1]));
		y1 = (int) y2px(symbols.eval(words[2]));
		x2 = (int) x2px(symbols.eval(words[3]));
		y2 = (int) y2px(symbols.eval(words[4]));
		dx = (int) (xsize*(symbols.eval(words[5]))/(xmax - xmin));
		dy = (int) (ysize*(symbols.eval(words[6]))/(ymax - ymin));
	    }catch( SyntaxException e ){ DeBug("Could not set x/y , error : "+e); return false; }
	    int num = Integer.parseInt(words[7]);
	    int X1[] = new int[num];
	    int X2[] = new int[num];
	    int Y1[] = new int[num];
	    int Y2[] = new int[num];
	    for(int i=0;i<num;i++){
		X1[i] = x1 + i*dx;
		Y1[i] = y1 - i*dy;
		X2[i] = x2 + i*dx;
		Y2[i] = y2 - i*dy;
	    }
	    color = GetInternalColorCode(words[8]);
	    try{alpha = Integer.parseInt(words[9]);color = MakeTransparent(color,alpha);
	    try{linewidth = Integer.parseInt(words[10]);}catch(Exception e){DeBug("no linewidth given...using previous value "+linewidth );}
	    }catch(Exception e){}
	    try{objects.add(new FlyParallel(X1,Y1,X2,Y2,color,linewidth,dashed));object_count++;return true;}
	    catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.indexOf("curve") !=-1 || cmd.indexOf("function") !=-1 || cmd.indexOf("plot") !=-1){ 
	    String  fx = words[1];
	    double step  = (xmax-xmin)/plotsteps;
	    int x[] = new int[plotsteps+1];
	    int y[] = new int[plotsteps+1];
	    int s=0;int dist;int xx;int yy;double py;
	    for (double px = xmin ; px < xmax; px=px+step){
		x[s] = (int) x2px(px);
		try { 
		    py = symbols.eval( fx.replaceAll( "x","("+px+")" ));
		    if( (Double.toString(py)).equals("NaN")){DeBug("skipping x="+x[s]+" -> NaN"); s = s - 1;}
		    else { y[s] = (int) y2px( py ); if(y[s] > ysize+plotjump){ y[s] = ysize;}}
		} catch (SyntaxException e ) {DeBug("error "+e);s=s-1;}
		s++;
	    }
	    int tmpx[]=new int[s];// correcting array_size for skipped points
	    int tmpy[]=new int[s];
	    int i=0;
	    for(int p=0;p<s;p++){
		tmpx[i] = x[p];
		tmpy[i] = y[p];
		i++;
	    }
	    x = tmpx;
	    y = tmpy;
	    color = GetInternalColorCode(words[2]);
	    try{alpha = Integer.parseInt(words[3]);color = MakeTransparent(color,alpha);}catch(Exception e){}
	    try{linewidth = Integer.parseInt(words[4]);}catch(Exception e){DeBug("no linewidth given...using previous value "+linewidth );}
	    try{objects.add( new FlyPlot(x,y,color,linewidth,filled,dashed));object_count++;return true;}
	    catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.equals("textup") || cmd.equals("rotatetext")  ){ 
	    // text x,y,angle,fontname,fontsize,the_text_without_comma,color [,alpha]
	    int x=0,y=0;
	    try{ 
		x = (int) x2px(symbols.eval(words[1]));
		y = (int) y2px(symbols.eval(words[2]));
	    } catch ( SyntaxException e ){ DeBug("Could not set x/y , error : "+e); return false; }
	    int angle = Integer.parseInt(words[3]);
	    if(words[4] != null){fontname = words[4];DeBug("setting fontname to :"+fontname);} // font
	    if(words[5] != null){fontsize = Integer.parseInt(words[5]);}
	    String txt = LaTeX2Uni(words[6]); // the text with spaces...
	    color = GetInternalColorCode(words[7]);
	    try{alpha = Integer.parseInt(words[8]);color = MakeTransparent(color,alpha);}catch(Exception e){}
	    try{ font = new Font(fontname,Font.PLAIN,fontsize);}catch(Exception e){DeBug("could nol load font"+fontname);}
	    try{objects.add(new FlyText(x,y,angle,font,txt,color));object_count++;return true;}catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.equals("text") ){ 
	    // text x,y,fontname,fontsize,the_text_without_comma,color [,alpha]
	    int x=0,y=0;
	    try{ 
		x = (int) x2px(symbols.eval(words[1]));
		y = (int) y2px(symbols.eval(words[2]));
	    } catch ( SyntaxException e ){ DeBug("Could not set x/y , error : "+e); return false; }
	    if(words[3] != null){fontname = words[3];DeBug("setting fontname to :"+fontname);} // font
	    if(words[4] != null){fontsize = Integer.parseInt(words[4]);}
	    String txt = LaTeX2Uni(words[5]); // the text with spaces...
	    color = GetInternalColorCode(words[6]);
	    int angle = 0;
	    try{ alpha = Integer.parseInt(words[7]);color = MakeTransparent(color,alpha);}catch(Exception e){}
	    try{ font  = new Font(fontname,Font.PLAIN,fontsize);DeBug("font = :"+font);}catch(Exception e){DeBug("could nol load font"+fontname);}
	    try{ objects.add(new FlyText(x,y,angle,font,txt,color));object_count++;return true;}catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.indexOf("ellips")!=-1 || cmd.indexOf("oval") != -1){
	    int xc=0,yc=0,w=0,h=0;
	    try{ 
		xc = (int) x2px(symbols.eval(words[1]));
		yc = (int) y2px(symbols.eval(words[2]));
		 w = (int) c2px(symbols.eval(words[3]));
		 h = (int) c2px(symbols.eval(words[4]));
	    } catch ( SyntaxException e ){ DeBug("Could not set x/y , error : "+e); return false; }
	    color = GetInternalColorCode(words[5]);
	    try{ alpha = Integer.parseInt(words[6]);color = MakeTransparent(color,alpha);
	    try{ linewidth = Integer.parseInt(words[7]);}catch(Exception e){DeBug("no linewidth given...using previous value "+linewidth );}
	    }catch(Exception e){} // syntax line 1,0,2,0,blue,123 [alpha =123
	    try{ objects.add(new FlyCircle(xc-w/2,yc-h/2,w,h,color,linewidth,filled,dashed));object_count++;return true;}catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.indexOf("arc")!=-1 ){ // arc xc,yc,R,angle1,angle2,color [,alpha,line]
	    int xc=0,yc=0,r=0,a1=0,a2=0;
	    try{
		 xc = (int) x2px(symbols.eval(words[1]));
		 yc = (int) y2px(symbols.eval(words[2]));
		 r  = (int) c2px(symbols.eval(words[3]));
		a1 = (int) (symbols.eval(words[4]));
		a2 = (int) (symbols.eval(words[5]));
	    } catch ( SyntaxException e ){ DeBug("Could not set xc,yc,radius or angles : "+e); return false; }

	    a2=Math.abs(a2-a1);// 
	    color = GetInternalColorCode(words[6]);
	    try{alpha = Integer.parseInt(words[7]);color = MakeTransparent(color,alpha);
	    try{linewidth = Integer.parseInt(words[8]);}catch(Exception e){DeBug("no linewidth given...using previous value "+linewidth );}
	    }catch(Exception e){} 
	    try{objects.add(new FlyArc(xc-r,yc-r,2*r,2*r,a1,a2,color,linewidth,filled,dashed));object_count++;return true;}catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(words[0].indexOf("circle")!= -1){ // circle xc,yc,R,color [,alpha,line]
	    int xc=0,yc=0,r=0;
	    try{
		 xc = (int) x2px(symbols.eval(words[1]));
		 yc = (int) y2px(symbols.eval(words[2]));
		 r  = (int) c2px(symbols.eval(words[3]));
	    } catch ( SyntaxException e ){ DeBug("Could not set x/y , error : "+e); return false; }
	    color = GetInternalColorCode(words[4]);
	    try{alpha = Integer.parseInt(words[5]);color = MakeTransparent(color,alpha);
	    try{linewidth = Integer.parseInt(words[6]);}catch(Exception e){DeBug("no linewidth given...using previous value "+linewidth );}
	    }catch(Exception e){} // syntax line 1,0,2,0,blue,123 [alpha =123
	    // Oval x,y,w,h
	    try{objects.add(new FlyCircle(xc-r,yc-r,2*r,2*r,color,linewidth,filled,dashed));object_count++;return true;}catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.equals("vline") || cmd.equals("vlines") || cmd.equals("verticalline") ||
	cmd.equals("dvline") || cmd.equals("dvlines") || cmd.equals("dverticalline")
	 ){
	    int x1=0,x2=0;
	    try{
		 x1 = (int) x2px(symbols.eval(words[1]));
		 x2 = (int) x2px(symbols.eval(words[2]));
	    } catch ( SyntaxException e ){ DeBug("Could not set x/y , error : "+e); return false; }

	    int y1 = (int) y2px(ymin-1);
	    int y2 = (int) y2px(ymax+1);
	    color = GetInternalColorCode(words[3]);
	    try{alpha = Integer.parseInt(words[4]);color = MakeTransparent(color,alpha);
	    try{linewidth = Integer.parseInt(words[5]);}catch(Exception e){DeBug("no linewidth given...using previous value "+linewidth );}
	    }catch(Exception e){} // syntax line 1,0,2,0,blue,123 [alpha =123
	    try{objects.add(new FlyLine(x1,y1,x1,y2,color,linewidth,dashed));object_count++;return true;}catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.equals("hline") || cmd.equals("hlines") || cmd.equals("horizontalline") ||
	    cmd.equals("dhline") || cmd.equals("dhlines") || cmd.equals("dhorizontalline") 
	 ){
	    int x1=0,y1=0;
	    try{
		 x1 = (int) x2px(symbols.eval(words[1]));
		 y1 = (int) y2px(symbols.eval(words[2]));
	    } catch ( SyntaxException e ){ DeBug("Could not set x/y , error : "+e); return false; }
	    x1=(int) x2px(xmin-1);
	    int x2=(int) x2px(xmax+1);
	    color = GetInternalColorCode(words[3]);
	    try{alpha = Integer.parseInt(words[4]);color = MakeTransparent(color,alpha);
	    try{linewidth = Integer.parseInt(words[5]);}catch(Exception e){DeBug("no linewidth given...using previous value "+linewidth );}
	    }catch(Exception e){} // syntax line 1,0,2,0,blue,123 [alpha =123
	    try{objects.add(new FlyLine(x1,y1,x2,y1,color,linewidth,dashed));object_count++;return true;}catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.equals("line") || cmd.equals("lines") ||
	    cmd.equals("dline") || cmd.equals("dlines") 
	 ){
	    int x1=0,y1=0,x2=0,y2=0;
	    try{
		 x1 = (int) x2px(symbols.eval(words[1]));
		 y1 = (int) y2px(symbols.eval(words[2]));
		 x2 = (int) x2px(symbols.eval(words[3]));
		 y2 = (int) y2px(symbols.eval(words[4]));
	    } catch ( SyntaxException e ){ DeBug("Could not set x/y , error : "+e); return false; }
	    color = GetInternalColorCode(words[5]);
	    try{alpha = Integer.parseInt(words[6]);color = MakeTransparent(color,alpha);
	    try{linewidth = Integer.parseInt(words[7]);}catch(Exception e){DeBug("no linewidth given...using previous value "+linewidth );}
	    }catch(Exception e){} // syntax line 1,0,2,0,blue,123 [alpha =123
	    try{objects.add(new FlyLine(x1,y1,x2,y2,color,linewidth,dashed));object_count++;return true;}
	    catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(words[0].indexOf("triangle")!=-1){
	    int x1=0,y1=0,x2=0,y2=0,x3=0,y3=0;
	    try{
		 x1 = (int) x2px(symbols.eval(words[1]));
		 y1 = (int) y2px(symbols.eval(words[2]));
		 x2 = (int) x2px(symbols.eval(words[3]));
		 y2 = (int) y2px(symbols.eval(words[4]));
		 x3 = (int) x2px(symbols.eval(words[5]));
		 y3 = (int) y2px(symbols.eval(words[6]));
	    } catch ( SyntaxException e ){ DeBug("Could not set x/y , error : "+e); return false; }

	    int x[] = new int [4];
	    int y[] = new int [4];
	    x[0]=x1;y[0]=y1;
	    x[1]=x2;y[1]=y2;
	    x[2]=x3;y[2]=y3;
	    x[3]=x1;y[3]=y1;
	    color = GetInternalColorCode(words[7]);
	    try{alpha = Integer.parseInt(words[8]);color = MakeTransparent(color , alpha);
	    try{linewidth = Integer.parseInt(words[9]);}catch(Exception e){DeBug("no linewidth given...using previous value "+linewidth );}
	    }catch(Exception e){}
	    try{objects.add(new FlyPoly(x,y,color,linewidth,filled,dashed));object_count++;}
	    catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(words[0].indexOf("rect")!=-1 || cmd.indexOf("square")!=-1 ){
	    int x1=0,y1=0,x2=0,y2=0;
	    try{
		 x1 = (int) x2px(symbols.eval(words[1]));
		 y1 = (int) y2px(symbols.eval(words[2]));
		 x2 = (int) x2px(symbols.eval(words[3]));
		 y2 = (int) y2px(symbols.eval(words[4]));
	    } catch ( SyntaxException e ){ DeBug("Could not set x/y , error : "+e); return false; }

	    int x[] = new int [5];
	    int y[] = new int [5];
	    x[0]=x1;y[0]=y1;
	    x[1]=x1;y[1]=y2;
	    x[2]=x2;y[2]=y2;
	    x[3]=x2;y[3]=y1;
	    x[4]=x1;y[4]=y1;
	    color = GetInternalColorCode(words[5]);
	    try{alpha = Integer.parseInt(words[6]);color = MakeTransparent(color , alpha);
	    try{linewidth = Integer.parseInt(words[7]);}catch(Exception e){DeBug("no linewidth given...using previous value "+linewidth );}
	    }catch(Exception e){}
	    try{objects.add(new FlyPoly(x,y,color,linewidth,filled,dashed));object_count++;return true;}
	    catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.indexOf("poly") != -1){
	    int n=words.length;
	    int tmpx[] = new int[n] ;int tmpy[] = new int[n];
	    boolean found_color=false;
	    String x1="";String y1="";int c=0;
	    for(int i=1; i<n;i=i+2){
		x1=words[i];
		found_color=ColorOrNumber(x1);
		if(!found_color){
		    y1=words[i+1];
		    try{
			tmpx[c] = (int) x2px(symbols.eval(x1));
		        tmpy[c] = (int) y2px(symbols.eval(y1));
			c++;
		    } catch ( SyntaxException e ){ DeBug("Could not set x/y , error : "+e); return false; }
		}	
		else
		{ 		    
		    color = GetInternalColorCode(x1);
		    found_color=true;// now se if next word is alpha...
		    try{alpha = Integer.parseInt(words[i+1]);color = MakeTransparent(color , alpha);}catch(Exception e){DeBug("no alpha value given to polygon");}
		    try{linewidth = Integer.parseInt(words[i+2]);}catch(Exception e){DeBug("no linewidth given...using previous value "+linewidth );}
		    i=n+1;
		}
	    }
	    try{
		int x[] = new int[c-1];
		int y[] = new int[c-1];
		for(int p=0;p<c-1;p++){
		    x[p]=tmpx[p];
		    y[p]=tmpy[p];
		}
		objects.add(new FlyPoly(x,y,color,linewidth,filled,dashed));object_count++;return true;
	    }catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	else
	if(cmd.equals("point") || cmd.equals("points")){// points x1,y1,x2,y2,x3,y3,x4,y4.....blue,123 or point x1,y1,x2,y2,x3,y3,x4,y4.....blue
	    int n=words.length; int c=0;
	    double tmpx[] = new double[n] ;double tmpy[] = new double[n];
	    boolean found_color=false;
	    String x1="";String y1="";
	    for(int i=1;i<n;i=i+2){
		x1=words[i];
		found_color=ColorOrNumber(x1);
		if(found_color){
		    color = GetInternalColorCode(x1);
		    try{alpha = Integer.parseInt(words[i+1]);color = MakeTransparent(color , alpha); found_color=true;}catch(Exception e){found_color=false;}
		    if(found_color){try{ linewidth = Integer.parseInt(words[i+2]);}catch(Exception e){}}
		    i=n;
		}	
		else
		{ 		    
		    y1=words[i+1];
		    try{
			tmpx[c] = (int) x2px(symbols.eval(x1));
		        tmpy[c] = (int) y2px(symbols.eval(y1));
			c++;
		    } catch ( SyntaxException e ){ DeBug("Could not set x/y , error : "+e); return false; }

		}
	    }
	    int x[] = new int[c];
	    int y[] = new int[c];
	    for(int p=0;p<c;p++){
		x[p]=(int)(tmpx[p] - linewidth/2);// a point is a filledOval
		y[p]=(int)(tmpy[p] - linewidth/2);
	    }
	    try{ objects.add(new FlyPoints(x,y,color,linewidth));object_count++;}catch(Exception e){DeBug("failed adding "+words[0]+" exception = "+e); return false;}
	}
	return true;
    }
 
    public Color MakeTransparent(Color color, int alpha){
    // adds/replaces alpha in a given color.
	return new Color(color.getRed(),color.getGreen(),color.getBlue(),alpha);
    }

    public double c2px(double c){//  coords to pixel
	double C = c*xsize/(xmax - xmin);
	return C;
    }

    public double x2px(double x){ // x-coords to pixel
	double X = x*xsize/(xmax - xmin) -  xsize*xmin/(xmax - xmin);
	return X;
    }

    public double y2px(double y){ // y-coords to pixel
	double Y = -1*y*ysize/(ymax-ymin) + ymax*ysize/(ymax-ymin);
	return Y;
    }

    public boolean ColorOrNumber(String s){ // checks if netx item in cmd-string is a color or a number, to allow compact syntax: line x1,y1,x2,y2,color,alpha,linewidth
    try{ symbols.eval(s); return false;} catch ( SyntaxException e ){ return true;}
    }

    public Color GetInternalColorCode(String color){// reads name and compares is caseinsnsitive with rgb.txt; returns matching color; alpha=255
	boolean found=false;
	Color k = new Color(0,0,0,255);
	for(int i=0;i<colornames.length;i++){
	    if(colornames[i].equalsIgnoreCase(color)){//R,G,B,alpha
		k = new Color(colors[i][0],colors[i][1],colors[i][2],colors[i][3]);
		found=true;
		break;
	    }
	}
	if(!found){DeBug("could not find color named "+color+"\nwill use black instead");}
	return k;
    }
    
    // jm.evers; handy functions, not invented here :(
    public byte [] loadURL(URL url) throws IOException {
        int bufSize = 1024 * 2;
	byte [] buf = new byte[bufSize];
	ByteArrayOutputStream bout = new ByteArrayOutputStream();
	BufferedInputStream   in   = new BufferedInputStream(url.openStream());
	int n;
	while ((n = in.read(buf)) > 0){
	    bout.write(buf, 0, n);
	}
	try { in.close(); } catch (Exception ignored) { }
	return bout.toByteArray();
    }

    public String loadFile(String fname) throws IOException {
        byte[] bytes = loadURL(new URL("file:" + fname));
	return new String(bytes);
    }

    public String load(String fileOrURL) throws IOException {
	try {	URL url = new URL(fileOrURL);
		return new String(loadURL(url));
	} catch(Exception e){ return loadFile(fileOrURL);}
    }
    
    // a listuniq on arrays ...uses System.arraycopy
    public int[] ListUniq(int[] array){
	Arrays.sort(array);
	int k = 0;
        for (int i = 0; i < array.length; i++){
	    if (i > 0 && array[i] == array[i -1] )
	    continue;
	    array[k++] = array[i];
	}
	int [] unique = new int[k];
        System.arraycopy(array, 0, unique, 0, k);
	return unique;
    }
    
    public String[] String2Array(String s){//syntax: command  x,y,a,q,color,blah blah blah,4,5
	s=s.replaceAll(",,",", ,"); 
	s=s.replaceAll("\t",""); 
	//s=s.replaceAll("   ","  "); 
	StringTokenizer st =  new StringTokenizer(s,",");
	int m=st.countTokens();
	String[] reply = new String[m+1];
	String first = st.nextToken();//command  x
	StringTokenizer temp =  new StringTokenizer(first," ");
	reply[0]=temp.nextToken(); //command
	reply[1]=temp.nextToken(); // x
	for(int i=2;i<m+1;i++){
	    reply[i] = st.nextToken();// y,a,q,color,blah blah blah,4,5
	}
	return reply;    
    }
    
    public String LaTeX2Uni(String S){
	for(int i=0; i<LaTeX.length;i++){
	    if( S.indexOf(LaTeX[i]) != -1 ){
		S = S.replaceAll(LaTeX[i],Unicode[i]);
	    }
	}
	return S;
    }
    
    public static int chars = 98;

    public static String Unicode[] = {
        "\u03B1", "\u0391", "\u03B2", "\u0392", "\u03B3", "\u0393", "\u03B4", "\u0394", "\u03B5", "\u0395", 
        "\u03D5", "\u03A6", "\u03C6", "\u03B3", "\u0393", "\u03B7", "\u0397", "\u03B9", "\u0399", "\u03BA", 
        "\u039A", "\u03BB", "\u039B", "\u03BC", "\u039C", "\u03BD", "\u039D", "\u03BF", "\u03A9", "\u03C0", 
        "\u03A0", "\u03C7", "\u03A7", "\u03C1", "\u03A1", "\u03C3", "\u03A3", "\u03C4", "\u03A4", "\u03C5", 
        "\u03A5", "\u03C8", "\u03A8", "\u03C9", "\u03A9", "\u03BE", "\u039E", "\u03C7", "\u03A7", "\u03B6", 
        "\u0396", "\u03B8", "\u0398", "\u0024", "%", "&", "\247", "\251", "\256", "\u2030", 
        "\275", "\u2153", "\274", "\276", "\u2154", "\261", "\u2202", "\u2206", "\u221E",
	"\u22C1","\u22C0","\u22C0","\u2027","\u2027","\u00F7","\u2115","\u2124","\u211A","\u211D","\u2216",
	"f\u00AF\u00B9(x)","\u2208","\u22C0","\u22C1","\u2209","rightarrow","\u21D4","\u221E","\u2192",
	"\u00B2log","\u00B3log","\u2074log","\u2075log","\u2076log","\u2077log","\u2078log","\u2079log",
	"\u221b","\u221c","\u2075sqrt","\u2076sqrt","\u2077sqrt","\u2078sqrt","\u2079sqrt","\u221a",
	"\u20AC"
    };
    public static String LaTeX[] = {
       " alpha "," Alpha ", " beta "," Beta "," gamma "," Gamma "," delta "," Delta "," epsilon "," Epsilon ", 
       " phi "," Phi "," varphi "," gamma "," Gamma "," eta "," Eta "," iota "," I "," kappa ", 
       " Kappa "," lambda "," Lambda "," mu "," Mu "," nu "," Nu "," omikron "," Omikron "," pi ", 
       " Pi "," chi "," Chi "," rho "," Rho "," sigma "," Sigma "," tau "," Tau "," uu ", 
       " Uu "," psi "," Psi "," omega "," Omega "," chi "," Chi "," ypsilon "," Ypsilon "," zeta ", 
       " Zeta "," theta "," Theta "," dollar "," percent "," ampersand "," paragraph "," copyright "," trademark "," promille ", 
       " half "," third "," quarter "," threequarters "," twothirds "," pm "," partial "," deltaop "," infty ",
	" of "," et "," en ","cdot"," times "," div "," N  "," Z "," Q "," R "," \\ ",
	" f^-1(x) "," isin  "," and  "," or "," notin  "," --> "," => "," inf "," -> ",
	"log2","log3","log4","log5","log6","log7","log8","log9",
	"sqrt3","sqrt4","sqrt5","sqrt6","sqrt7","sqrt8","sqrt8","sqrt",
	" euro "
    };

// /usr/X11R6/lib/X11/rgb.txt

    int colors[][]={
    {255,255,255,255},{255,0,0,255},{0,255,0,255},{0,0,255,255},{255,255,0,255},
    {255,250,250,255},{248,248,255,255},{248,248,255,255},{245,245,245,255},{245,245,245,255},{220,220,220,255},{255,250,240,255},{255,250,240,255},
    {253,245,230,255},{253,245,230,255},{250,240,230,255},{250,235,215,255},{250,235,215,255},{255,239,213,255},{255,239,213,255},{255,235,205,255},{255,235,205,255},
    {255,228,196,255},{255,218,185,255},{255,218,185,255},{255,222,173,255},{255,222,173,255},{255,228,181,255},{255,248,220,255},{255,255,240,255},{255,250,205,255},
    {255,250,205,255},{255,245,238,255},{240,255,240,255},{245,255,250,255},{245,255,250,255},{240,255,255,255},{240,248,255,255},{240,248,255,255},{230,230,250,255},
    {255,240,245,255},{255,240,245,255},{255,228,225,255},{255,228,225,255},{255,255,255,255},{0,0,0,255},{47,79,79,255},{47,79,79,255},{47,79,79,255},{47,79,79,255},
    {105,105,105,255},{105,105,105,255},{105,105,105,255},{105,105,105,255},{112,128,144,255},{112,128,144,255},{112,128,144,255},{112,128,144,255},{119,136,153,255},
    {119,136,153,255},{119,136,153,255},{119,136,153,255},{190,190,190,255},{190,190,190,255},{211,211,211,255},{211,211,211,255},{211,211,211,255},{211,211,211,255},
    {25,25,112,255},{25,25,112,255},{0,0,128,255},{0,0,128,255},{0,0,128,255},{100,149,237,255},{100,149,237,255},{72,61,139,255},{72,61,139,255},{106,90,205,255},{106,90,205,255},
    {123,104,238,255},{123,104,238,255},{132,112,255,255},{132,112,255,255},{0,0,205,255},{0,0,205,255},{65,105,225,255},{65,105,225,255},{0,0,255,255},{30,144,255,255},
    {30,144,255,255},{0,191,255,255},{0,191,255,255},{135,206,235,255},{135,206,235,255},{135,206,250,255},{135,206,250,255},{70,130,180,255},{70,130,180,255},{176,196,222,255},
    {176,196,222,255},{173,216,230,255},{173,216,230,255},{176,224,230,255},{176,224,230,255},{175,238,238,255},{175,238,238,255},{0,206,209,255},{0,206,209,255},{72,209,204,255},
    {72,209,204,255},{64,224,208,255},{0,255,255,255},{224,255,255,255},{224,255,255,255},{95,158,160,255},{95,158,160,255},{102,205,170,255},{102,205,170,255},{127,255,212,255},
    {0,100,0,255},{0,100,0,255},{85,107,47,255},{85,107,47,255},{143,188,143,255},{143,188,143,255},{46,139,87,255},{46,139,87,255},{60,179,113,255},{60,179,113,255},{32,178,170,255},
    {32,178,170,255},{152,251,152,255},{152,251,152,255},{0,255,127,255},{0,255,127,255},{124,252,0,255},{124,252,0,255},{0,255,0,255},{127,255,0,255},{0,250,154,255},{0,250,154,255},
    {173,255,47,255},{173,255,47,255},{50,205,50,255},{50,205,50,255},{154,205,50,255},{154,205,50,255},{34,139,34,255},{34,139,34,255},{107,142,35,255},{107,142,35,255},
    {189,183,107,255},{189,183,107,255},{240,230,140,255},{238,232,170,255},{238,232,170,255},{250,250,210,255},{250,250,210,255},{255,255,224,255},{255,255,224,255},
    {255,255,0,255},{255,215,0,255},{238,221,130,255},{238,221,130,255},{218,165,32,255},{184,134,11,255},{184,134,11,255},{188,143,143,255},{188,143,143,255},{205,92,92,255},
    {205,92,92,255},{139,69,19,255},{139,69,19,255},{160,82,45,255},{205,133,63,255},{222,184,135,255},{245,245,220,255},{245,222,179,255},{244,164,96,255},{244,164,96,255},
    {210,180,140,255},{210,105,30,255},{178,34,34,255},{165,42,42,255},{233,150,122,255},{233,150,122,255},{250,128,114,255},{255,160,122,255},{255,160,122,255},{255,165,0,255},
    {255,140,0,255},{255,140,0,255},{255,127,80,255},{240,128,128,255},{240,128,128,255},{255,99,71,255},{255,69,0,255},{255,69,0,255},{255,0,0,255},{255,105,180,255},
    {255,105,180,255},{255,20,147,255},{255,20,147,255},{255,192,203,255},{255,182,193,255},{255,182,193,255},{219,112,147,255},{219,112,147,255},{176,48,96,255},
    {199,21,133,255},{199,21,133,255},{208,32,144,255},{208,32,144,255},{255,0,255,255},{238,130,238,255},{221,160,221,255},{218,112,214,255},{186,85,211,255},{186,85,211,255},
    {153,50,204,255},{153,50,204,255},{148,0,211,255},{148,0,211,255},{138,43,226,255},{138,43,226,255},{160,32,240,255},{147,112,219,255},{147,112,219,255},{216,191,216,255},
    {255,250,250,255},{238,233,233,255},{205,201,201,255},{139,137,137,255},{255,245,238,255},{238,229,222,255},{205,197,191,255},{139,134,130,255},{255,239,219,255},
    {238,223,204,255},{205,192,176,255},{139,131,120,255},{255,228,196,255},{238,213,183,255},{205,183,158,255},{139,125,107,255},{255,218,185,255},{238,203,173,255},
    {205,175,149,255},{139,119,101,255},{255,222,173,255},{238,207,161,255},{205,179,139,255},{139,121,94,255},{255,250,205,255},{238,233,191,255},{205,201,165,255},
    {139,137,112,255},{255,248,220,255},{238,232,205,255},{205,200,177,255},{139,136,120,255},{255,255,240,255},{238,238,224,255},{205,205,193,255},{139,139,131,255},
    {240,255,240,255},{224,238,224,255},{193,205,193,255},{131,139,131,255},{255,240,245,255},{238,224,229,255},{205,193,197,255},{139,131,134,255},{255,228,225,255},
    {238,213,210,255},{205,183,181,255},{139,125,123,255},{240,255,255,255},{224,238,238,255},{193,205,205,255},{131,139,139,255},{131,111,255,255},{122,103,238,255},
    {105,89,205,255},{71,60,139,255},{72,118,255,255},{67,110,238,255},{58,95,205,255},{39,64,139,255},{0,0,255,255},{0,0,238,255},{0,0,205,255},{0,0,139,255},{30,144,255,255},
    {28,134,238,255},{24,116,205,255},{16,78,139,255},{99,184,255,255},{92,172,238,255},{79,148,205,255},{54,100,139,255},{0,191,255,255},{0,178,238,255},{0,154,205,255},
    {0,104,139,255},{135,206,255,255},{126,192,238,255},{108,166,205,255},{74,112,139,255},{176,226,255,255},{164,211,238,255},{141,182,205,255},{96,123,139,255},{198,226,255,255},
    {185,211,238,255},{159,182,205,255},{108,123,139,255},{202,225,255,255},{188,210,238,255},{162,181,205,255},{110,123,139,255},{191,239,255,255},{178,223,238,255},
    {154,192,205,255},{104,131,139,255},{224,255,255,255},{209,238,238,255},{180,205,205,255},{122,139,139,255},{187,255,255,255},{174,238,238,255},{150,205,205,255},
    {102,139,139,255},{152,245,255,255},{142,229,238,255},{122,197,205,255},{83,134,139,255},{0,245,255,255},{0,229,238,255},{0,197,205,255},{0,134,139,255},{0,255,255,255},
    {0,238,238,255},{0,205,205,255},{0,139,139,255},{151,255,255,255},{141,238,238,255},{121,205,205,255},{82,139,139,255},{127,255,212,255},{118,238,198,255},{102,205,170,255},
    {69,139,116,255},{193,255,193,255},{180,238,180,255},{155,205,155,255},{105,139,105,255},{84,255,159,255},{78,238,148,255},{67,205,128,255},{46,139,87,255},{154,255,154,255},
    {144,238,144,255},{124,205,124,255},{84,139,84,255},{0,255,127,255},{0,238,118,255},{0,205,102,255},{0,139,69,255},{0,255,0,255},{0,238,0,255},{0,205,0,255},{0,139,0,255},
    {127,255,0,255},{118,238,0,255},{102,205,0,255},{69,139,0,255},{192,255,62,255},{179,238,58,255},{154,205,50,255},{105,139,34,255},{202,255,112,255},{188,238,104,255},
    {162,205,90,255},{110,139,61,255},{255,246,143,255},{238,230,133,255},{205,198,115,255},{139,134,78,255},{255,236,139,255},{238,220,130,255},{205,190,112,255},
    {139,129,76,255},{255,255,224,255},{238,238,209,255},{205,205,180,255},{139,139,122,255},{255,255,0,255},{238,238,0,255},{205,205,0,255},{139,139,0,255},{255,215,0,255},
    {238,201,0,255},{205,173,0,255},{139,117,0,255},{255,193,37,255},{238,180,34,255},{205,155,29,255},{139,105,20,255},{255,185,15,255},{238,173,14,255},{205,149,12,255},
    {139,101,8,255},{255,193,193,255},{238,180,180,255},{205,155,155,255},{139,105,105,255},{255,106,106,255},{238,99,99,255},{205,85,85,255},{139,58,58,255},{255,130,71,255},
    {238,121,66,255},{205,104,57,255},{139,71,38,255},{255,211,155,255},{238,197,145,255},{205,170,125,255},{139,115,85,255},{255,231,186,255},{238,216,174,255},{205,186,150,255},
    {139,126,102,255},{255,165,79,255},{238,154,73,255},{205,133,63,255},{139,90,43,255},{255,127,36,255},{238,118,33,255},{205,102,29,255},{139,69,19,255},{255,48,48,255},
    {238,44,44,255},{205,38,38,255},{139,26,26,255},{255,64,64,255},{238,59,59,255},{205,51,51,255},{139,35,35,255},{255,140,105,255},{238,130,98,255},{205,112,84,255},
    {139,76,57,255},{255,160,122,255},{238,149,114,255},{205,129,98,255},{139,87,66,255},{255,165,0,255},{238,154,0,255},{205,133,0,255},{139,90,0,255},{255,127,0,255},
    {238,118,0,255},{205,102,0,255},{139,69,0,255},{255,114,86,255},{238,106,80,255},{205,91,69,255},{139,62,47,255},{255,99,71,255},{238,92,66,255},{205,79,57,255},{139,54,38,255},
    {255,69,0,255},{238,64,0,255},{205,55,0,255},{139,37,0,255},{255,0,0,255},{238,0,0,255},{205,0,0,255},{139,0,0,255},{255,20,147,255},{238,18,137,255},{205,16,118,255},{139,10,80,255},
    {255,110,180,255},{238,106,167,255},{205,96,144,255},{139,58,98,255},{255,181,197,255},{238,169,184,255},{205,145,158,255},{139,99,108,255},{255,174,185,255},{238,162,173,255},
    {205,140,149,255},{139,95,101,255},{255,130,171,255},{238,121,159,255},{205,104,137,255},{139,71,93,255},{255,52,179,255},{238,48,167,255},{205,41,144,255},{139,28,98,255},
    {255,62,150,255},{238,58,140,255},{205,50,120,255},{139,34,82,255},{255,0,255,255},{238,0,238,255},{205,0,205,255},{139,0,139,255},{255,131,250,255},{238,122,233,255},
    {205,105,201,255},{139,71,137,255},{255,187,255,255},{238,174,238,255},{205,150,205,255},{139,102,139,255},{224,102,255,255},{209,95,238,255},{180,82,205,255},{122,55,139,255},
    {191,62,255,255},{178,58,238,255},{154,50,205,255},{104,34,139,255},{155,48,255,255},{145,44,238,255},{125,38,205,255},{85,26,139,255},{171,130,255,255},{159,121,238,255},
    {137,104,205,255},{93,71,139,255},{255,225,255,255},{238,210,238,255},{205,181,205,255},{139,123,139,255},{0,0,0,255},{0,0,0,255},{3,3,3,255},{3,3,3,255},{5,5,5,255},{5,5,5,255},
    {8,8,8,255},{8,8,8,255},{10,10,10,255},{10,10,10,255},{13,13,13,255},{13,13,13,255},{15,15,15,255},{15,15,15,255},{18,18,18,255},{18,18,18,255},{20,20,20,255},{20,20,20,255},
    {23,23,23,255},{23,23,23,255},{26,26,26,255},{26,26,26,255},{28,28,28,255},{28,28,28,255},{31,31,31,255},{31,31,31,255},{33,33,33,255},{33,33,33,255},{36,36,36,255},{36,36,36,255},
    {38,38,38,255},{38,38,38,255},{41,41,41,255},{41,41,41,255},{43,43,43,255},{43,43,43,255},{46,46,46,255},{46,46,46,255},{48,48,48,255},{48,48,48,255},{51,51,51,255},{51,51,51,255},
    {54,54,54,255},{54,54,54,255},{56,56,56,255},{56,56,56,255},{59,59,59,255},{59,59,59,255},{61,61,61,255},{61,61,61,255},{64,64,64,255},{64,64,64,255},{66,66,66,255},{66,66,66,255},
    {69,69,69,255},{69,69,69,255},{71,71,71,255},{71,71,71,255},{74,74,74,255},{74,74,74,255},{77,77,77,255},{77,77,77,255},{79,79,79,255},{79,79,79,255},{82,82,82,255},{82,82,82,255},
    {84,84,84,255},{84,84,84,255},{87,87,87,255},{87,87,87,255},{89,89,89,255},{89,89,89,255},{92,92,92,255},{92,92,92,255},{94,94,94,255},{94,94,94,255},{97,97,97,255},{97,97,97,255},
    {99,99,99,255},{99,99,99,255},{102,102,102,255},{102,102,102,255},{105,105,105,255},{105,105,105,255},{107,107,107,255},{107,107,107,255},{110,110,110,255},{110,110,110,255},
    {112,112,112,255},{112,112,112,255},{115,115,115,255},{115,115,115,255},{117,117,117,255},{117,117,117,255},{120,120,120,255},{120,120,120,255},{122,122,122,255},
    {122,122,122,255},{125,125,125,255},{125,125,125,255},{127,127,127,255},{127,127,127,255},{130,130,130,255},{130,130,130,255},{133,133,133,255},{133,133,133,255},
    {135,135,135,255},{135,135,135,255},{138,138,138,255},{138,138,138,255},{140,140,140,255},{140,140,140,255},{143,143,143,255},{143,143,143,255},{145,145,145,255},
    {145,145,145,255},{148,148,148,255},{148,148,148,255},{150,150,150,255},{150,150,150,255},{153,153,153,255},{153,153,153,255},{156,156,156,255},{156,156,156,255},
    {158,158,158,255},{158,158,158,255},{161,161,161,255},{161,161,161,255},{163,163,163,255},{163,163,163,255},{166,166,166,255},{166,166,166,255},{168,168,168,255},
    {168,168,168,255},{171,171,171,255},{171,171,171,255},{173,173,173,255},{173,173,173,255},{176,176,176,255},{176,176,176,255},{179,179,179,255},{179,179,179,255},
    {181,181,181,255},{181,181,181,255},{184,184,184,255},{184,184,184,255},{186,186,186,255},{186,186,186,255},{189,189,189,255},{189,189,189,255},{191,191,191,255},
    {191,191,191,255},{194,194,194,255},{194,194,194,255},{196,196,196,255},{196,196,196,255},{199,199,199,255},{199,199,199,255},{201,201,201,255},{201,201,201,255},
    {204,204,204,255},{204,204,204,255},{207,207,207,255},{207,207,207,255},{209,209,209,255},{209,209,209,255},{212,212,212,255},{212,212,212,255},{214,214,214,255},
    {214,214,214,255},{217,217,217,255},{217,217,217,255},{219,219,219,255},{219,219,219,255},{222,222,222,255},{222,222,222,255},{224,224,224,255},{224,224,224,255},
    {227,227,227,255},{227,227,227,255},{229,229,229,255},{229,229,229,255},{232,232,232,255},{232,232,232,255},{235,235,235,255},{235,235,235,255},{237,237,237,255},
    {237,237,237,255},{240,240,240,255},{240,240,240,255},{242,242,242,255},{242,242,242,255},{245,245,245,255},{245,245,245,255},{247,247,247,255},{247,247,247,255},
    {250,250,250,255},{250,250,250,255},{252,252,252,255},{252,252,252,255},{255,255,255,255},{255,255,255,255},{169,169,169,255},{169,169,169,255},{169,169,169,255},
    {169,169,169,255},{0,0,139,255},{0,0,139,255},{0,139,139,255},{0,139,139,255},{139,0,139,255},{139,0,139,255},{139,0,0,255},{139,0,0,255},{144,238,144,255},{144,238,144,255}};

    String[] colornames={ "white","red","green","blue","orange",
   "snow","ghostwhite","GhostWhite","whitesmoke","WhiteSmoke","gainsboro","floralwhite","FloralWhite","oldlace","OldLace",
   "linen","antiquewhite","AntiqueWhite","papayawhip","PapayaWhip","blanchedalmond","BlanchedAlmond","bisque","peachpuff","PeachPuff",
   "navajowhite","NavajoWhite","moccasin","cornsilk","ivory","lemonchiffon","LemonChiffon","seashell","honeydew","mintcream","MintCream",
   "azure","aliceblue","AliceBlue","lavender","lavenderblush","LavenderBlush","mistyrose","MistyRose","white","black","darkslategray",
   "DarkSlateGray","darkslategrey","DarkSlateGrey","dimgray","DimGray","dimgrey","DimGrey","slategray","SlateGray","slategrey",
   "SlateGrey","lightslategray","LightSlateGray","lightslategrey","LightSlateGrey","gray","grey","lightgrey","LightGrey","lightgray",
   "LightGray","midnightblue","MidnightBlue","navy","navyblue","NavyBlue","cornflowerblue","CornflowerBlue","darkslateblue",
   "DarkSlateBlue","slateblue","SlateBlue","mediumslateblue","MediumSlateBlue","lightslateblue","LightSlateBlue","mediumblue",
   "MediumBlue","royalblue","RoyalBlue","blue","dodgerblue","DodgerBlue","deepskyblue","DeepSkyBlue","skyblue","SkyBlue",
   "lightskyblue","LightSkyBlue","steelblue","SteelBlue","lightsteelblue","LightSteelBlue","lightblue","LightBlue","powderblue",
   "PowderBlue","paleturquoise","PaleTurquoise","darkturquoise","DarkTurquoise","mediumturquoise","MediumTurquoise","turquoise",
   "cyan","lightcyan","LightCyan","cadetblue","CadetBlue","mediumaquamarine","MediumAquamarine","aquamarine","darkgreen","DarkGreen",
   "darkolivegreen","DarkOliveGreen","darkseagreen","DarkSeaGreen","seagreen","SeaGreen","mediumseagreen","MediumSeaGreen",
   "lightseagreen","LightSeaGreen","palegreen","PaleGreen","springgreen","SpringGreen","lawngreen","LawnGreen","green","chartreuse",
   "mediumspringgreen","MediumSpringGreen","greenyellow","GreenYellow","limegreen","LimeGreen","yellowgreen","YellowGreen",
   "forestgreen","ForestGreen","olivedrab","OliveDrab","darkkhaki","DarkKhaki","khaki","palegoldenrod","PaleGoldenrod",
   "lightgoldenrodyellow","LightGoldenrodYellow","lightyellow","LightYellow","yellow","gold","lightgoldenrod","LightGoldenrod",
   "goldenrod","darkgoldenrod","DarkGoldenrod","rosybrown","RosyBrown","indianred","IndianRed","saddlebrown","SaddleBrown",
   "sienna","peru","burlywood","beige","wheat","sandybrown","SandyBrown","tan","chocolate","firebrick","brown","darksalmon",
   "DarkSalmon","salmon","lightsalmon","LightSalmon","orange","darkorange","DarkOrange","coral","lightcoral","LightCoral",
   "tomato","orangered","OrangeRed","red","hotpink","HotPink","deeppink","DeepPink","pink","lightpink","LightPink","palevioletred",
   "PaleVioletRed","maroon","mediumvioletred","MediumVioletRed","violetred","VioletRed","magenta","violet","plum","orchid",
   "mediumorchid","MediumOrchid","darkorchid","DarkOrchid","darkviolet","DarkViolet","blueviolet","BlueViolet","purple",
   "mediumpurple","MediumPurple","thistle","snow1","snow2","snow3","snow4","seashell1","seashell2","seashell3","seashell4",
   "AntiqueWhite1","AntiqueWhite2","AntiqueWhite3","AntiqueWhite4","bisque1","bisque2","bisque3","bisque4","PeachPuff1","PeachPuff2",
   "PeachPuff3","PeachPuff4","NavajoWhite1","NavajoWhite2","NavajoWhite3","NavajoWhite4","LemonChiffon1","LemonChiffon2",
   "LemonChiffon3","LemonChiffon4","cornsilk1","cornsilk2","cornsilk3","cornsilk4","ivory1","ivory2","ivory3","ivory4","honeydew1",
   "honeydew2","honeydew3","honeydew4","LavenderBlush1","LavenderBlush2","LavenderBlush3","LavenderBlush4","MistyRose1","MistyRose2",
   "MistyRose3","MistyRose4","azure1","azure2","azure3","azure4","SlateBlue1","SlateBlue2","SlateBlue3","SlateBlue4","RoyalBlue1",
   "RoyalBlue2","RoyalBlue3","RoyalBlue4","blue1","blue2","blue3","blue4","DodgerBlue1","DodgerBlue2","DodgerBlue3","DodgerBlue4",
   "SteelBlue1","SteelBlue2","SteelBlue3","SteelBlue4","DeepSkyBlue1","DeepSkyBlue2","DeepSkyBlue3","DeepSkyBlue4","SkyBlue1","SkyBlue2",
   "SkyBlue3","SkyBlue4","LightSkyBlue1","LightSkyBlue2","LightSkyBlue3","LightSkyBlue4","SlateGray1","SlateGray2","SlateGray3",
   "SlateGray4","LightSteelBlue1","LightSteelBlue2","LightSteelBlue3","LightSteelBlue4","LightBlue1","LightBlue2","LightBlue3",
   "LightBlue4","LightCyan1","LightCyan2","LightCyan3","LightCyan4","PaleTurquoise1","PaleTurquoise2","PaleTurquoise3","PaleTurquoise4",
   "CadetBlue1","CadetBlue2","CadetBlue3","CadetBlue4","turquoise1","turquoise2","turquoise3","turquoise4","cyan1","cyan2","cyan3",
   "cyan4","DarkSlateGray1","DarkSlateGray2","DarkSlateGray3","DarkSlateGray4","aquamarine1","aquamarine2","aquamarine3","aquamarine4",
   "DarkSeaGreen1","DarkSeaGreen2","DarkSeaGreen3","DarkSeaGreen4","SeaGreen1","SeaGreen2","SeaGreen3","SeaGreen4","PaleGreen1",
   "PaleGreen2","PaleGreen3","PaleGreen4","SpringGreen1","SpringGreen2","SpringGreen3","SpringGreen4","green1","green2","green3",
   "green4","chartreuse1","chartreuse2","chartreuse3","chartreuse4","OliveDrab1","OliveDrab2","OliveDrab3","OliveDrab4","DarkOliveGreen1",
   "DarkOliveGreen2","DarkOliveGreen3","DarkOliveGreen4","khaki1","khaki2","khaki3","khaki4","LightGoldenrod1","LightGoldenrod2",
   "LightGoldenrod3","LightGoldenrod4","LightYellow1","LightYellow2","LightYellow3","LightYellow4","yellow1","yellow2","yellow3",
   "yellow4","gold1","gold2","gold3","gold4","goldenrod1","goldenrod2","goldenrod3","goldenrod4","DarkGoldenrod1","DarkGoldenrod2",
   "DarkGoldenrod3","DarkGoldenrod4","RosyBrown1","RosyBrown2","RosyBrown3","RosyBrown4","IndianRed1","IndianRed2","IndianRed3",
   "IndianRed4","sienna1","sienna2","sienna3","sienna4","burlywood1","burlywood2","burlywood3","burlywood4","wheat1","wheat2","wheat3",
   "wheat4","tan1","tan2","tan3","tan4","chocolate1","chocolate2","chocolate3","chocolate4","firebrick1","firebrick2","firebrick3",
   "firebrick4","brown1","brown2","brown3","brown4","salmon1","salmon2","salmon3","salmon4","LightSalmon1","LightSalmon2","LightSalmon3",
   "LightSalmon4","orange1","orange2","orange3","orange4","DarkOrange1","DarkOrange2","DarkOrange3","DarkOrange4","coral1","coral2",
   "coral3","coral4","tomato1","tomato2","tomato3","tomato4","OrangeRed1","OrangeRed2","OrangeRed3","OrangeRed4","red1","red2","red3",
   "red4","DeepPink1","DeepPink2","DeepPink3","DeepPink4","HotPink1","HotPink2","HotPink3","HotPink4","pink1","pink2","pink3","pink4",
   "LightPink1","LightPink2","LightPink3","LightPink4","PaleVioletRed1","PaleVioletRed2","PaleVioletRed3","PaleVioletRed4","maroon1",
   "maroon2","maroon3","maroon4","VioletRed1","VioletRed2","VioletRed3","VioletRed4","magenta1","magenta2","magenta3","magenta4","orchid1",
   "orchid2","orchid3","orchid4","plum1","plum2","plum3","plum4","MediumOrchid1","MediumOrchid2","MediumOrchid3","MediumOrchid4",
   "DarkOrchid1","DarkOrchid2","DarkOrchid3","DarkOrchid4","purple1","purple2","purple3","purple4","MediumPurple1","MediumPurple2",
   "MediumPurple3","MediumPurple4","thistle1","thistle2","thistle3","thistle4","gray0","grey0","gray1","grey1","gray2","grey2","gray3",
   "grey3","gray4","grey4","gray5","grey5","gray6","grey6","gray7","grey7","gray8","grey8","gray9","grey9","gray10","grey10","gray11",
   "grey11","gray12","grey12","gray13","grey13","gray14","grey14","gray15","grey15","gray16","grey16","gray17","grey17","gray18","grey18",
   "gray19","grey19","gray20","grey20","gray21","grey21","gray22","grey22","gray23","grey23","gray24","grey24","gray25","grey25","gray26",
   "grey26","gray27","grey27","gray28","grey28","gray29","grey29","gray30","grey30","gray31","grey31","gray32","grey32","gray33","grey33",
   "gray34","grey34","gray35","grey35","gray36","grey36","gray37","grey37","gray38","grey38","gray39","grey39","gray40","grey40","gray41",
   "grey41","gray42","grey42","gray43","grey43","gray44","grey44","gray45","grey45","gray46","grey46","gray47","grey47","gray48","grey48",
   "gray49","grey49","gray50","grey50","gray51","grey51","gray52","grey52","gray53","grey53","gray54","grey54","gray55","grey55","gray56",
   "grey56","gray57","grey57","gray58","grey58","gray59","grey59","gray60","grey60","gray61","grey61","gray62","grey62","gray63","grey63",
   "gray64","grey64","gray65","grey65","gray66","grey66","gray67","grey67","gray68","grey68","gray69","grey69","gray70","grey70","gray71",
   "grey71","gray72","grey72","gray73","grey73","gray74","grey74","gray75","grey75","gray76","grey76","gray77","grey77","gray78","grey78",
   "gray79","grey79","gray80","grey80","gray81","grey81","gray82","grey82","gray83","grey83","gray84","grey84","gray85","grey85","gray86",
   "grey86","gray87","grey87","gray88","grey88","gray89","grey89","gray90","grey90","gray91","grey91","gray92","grey92","gray93","grey93",
   "gray94","grey94","gray95","grey95","gray96","grey96","gray97","grey97","gray98","grey98","gray99","grey99","gray100","grey100",
   "darkgrey","DarkGrey","darkgray","DarkGray","darkblue","DarkBlue","darkcyan","DarkCyan","darkmagenta","DarkMagenta","darkred",
   "DarkRed","lightgreen","LightGreen"};

}


class FlyArc {
    int xc,yc,w,h;
    int linewidth;
    int a1,a2;
    Color color;
    boolean filled,dashed;
    
    public FlyArc(  int xc , int yc, int w, int h , int a1, int a2, 
		    Color color, int linewidth , boolean filled, boolean dashed )
    {
	this.xc = xc;
	this.yc = yc;
        this.h = h;
        this.w = w;
	this.a1 = a1;
	this.a2 = a2;
        this.color = color;
        this.linewidth = linewidth;
	this.filled = filled;
	this.dashed = dashed;
    }
    
   public int getXc()        { return xc; } 
   public int getYc()        { return yc; } 
   public int getH()         { return h; } 
   public int getW()         { return w; } 
   public int getLineWidth() { return linewidth;}
   public int getAngle1() { return a1;}
   public int getAngle2() { return a2;}   
   public Color getColor()   { return color;} 
   public boolean getFilled(){ return filled;} 
   public boolean getDashed(){ return dashed;} 

}

class FlyCircle {
    int xc,yc,w,h;
    Color color;
    int linewidth;
    boolean filled;
    boolean dashed;
    
    public FlyCircle(int xc, int yc , int w, int h, Color color , int linewidth , boolean filled , boolean dashed ){
	this.xc = xc;
	this.yc = yc;
        this.h = h;
        this.w = w;
        this.color = color;
        this.linewidth = linewidth;
	this.filled = filled;
   }
   public int getXc() { return xc; } 
   public int getYc() { return yc; } 
   public int getH() { return h; } 
   public int getW() { return w; } 
   public int getLineWidth() { return linewidth; }
   public Color getColor(){ return color;} 
   public boolean getFilled(){ return filled;} 
   public boolean getDashed(){ return dashed;} 
} 

class FlyLine {
    int x1,y1,x2,y2;
    Color color;
    int linewidth;
    boolean dashed;
    
    public FlyLine(int x1, int y1 , int x2 , int y2, Color color , int linewidth, boolean dashed ){
	this.x1 = x1;
	this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
        this.color = color;
        this.linewidth = linewidth;
        this.dashed = dashed;
   }
   public int getX1() { return x1; } 
   public int getY1() { return y1; } 
   public int getX2() { return x2; } 
   public int getY2() { return y2; } 
   public int getLineWidth() { return linewidth; }
   public Color getColor(){ return color;} 
   public boolean getDashed(){ return dashed;} 
} 

class FlyRect{
    int x,y,w,h;
    Color color;
    int linewidth;
    boolean filled;
    boolean dashed;
    
    public FlyRect(int x,int y ,int w ,int h, Color color , int linewidth , boolean filled, boolean dashed ){
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
        this.color = color;
	this.linewidth = linewidth;
        this.filled = filled;
        this.dashed = dashed;
   }
   public int getX() { return x; } 
   public int getY() { return y; } 
   public int getW() { return w; } 
   public int getH() { return h; } 
   public int getLineWidth() { return linewidth; }
   public Color getColor(){ return color;}
   public boolean getFilled(){ return filled;} 
   public boolean getDashed(){ return dashed;} 
} 


class FlyParallel {
    int x1[];
    int y1[];
    int x2[];
    int y2[];
    Color color;
    int linewidth;
    boolean dashed;
    
    public FlyParallel(int x1[],int y1[] , int x2[],int y2[] , Color color , int linewidth , boolean dashed ){
        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
        this.color = color;
        this.linewidth = linewidth;
        this.dashed = dashed;
   }
   public int[] getX1() { return x1; } 
   public int[] getY1() { return y1; } 
   public int[] getX2() { return x2; } 
   public int[] getY2() { return y2; } 
   public int getLineWidth() { return linewidth; }
   public Color getColor(){ return color;}
   public boolean getDashed(){ return dashed;} 
} 

class FlyPoly {
    int x[];
    int y[];
    Color color;
    int linewidth;
    boolean filled;
    boolean dashed;
    
    public FlyPoly(int x[],int y[] , Color color , int linewidth , boolean filled, boolean dashed ){
        this.x = x;
        this.y = y;
        this.color = color;
        this.linewidth = linewidth;
        this.filled = filled;
        this.dashed = dashed;
   }
   public int[] getX() { return x; } 
   public int[] getY() { return y; } 
   public int getLineWidth() { return linewidth; }
   public Color getColor(){ return color;}
   public boolean getFilled(){ return filled;} 
   public boolean getDashed(){ return dashed;} 
} 

class FlyLatex {
    int x;
    int y;
    BufferedImage latex;
    
    public FlyLatex(int x,int y ,BufferedImage latex ){
        this.x = x;
        this.y = y;
	this.latex = latex;
   }
   public int getX() { return x; } 
   public int getY() { return y; } 
   public BufferedImage getLatex() { return latex;}
} 

class FlyPlot{
    int x[];
    int y[];
    Color color;
    int linewidth;
    boolean filled;
    boolean dashed;
    
    public FlyPlot(int x[],int y[] , Color color , int linewidth , boolean filled, boolean dashed ){
        this.x = x;
        this.y = y;
        this.color = color;
        this.linewidth = linewidth;
        this.filled = filled;
        this.dashed = dashed;
   }
   public int[] getX() { return x; } 
   public int[] getY() { return y; } 
   public int getLineWidth() { return linewidth; }
   public Color getColor(){ return color;}
   public boolean getFilled(){ return filled;} 
   public boolean getDashed(){ return dashed;} 
} 


class FlyArrow {
    int x[];
    int y[];
    Color color;
    int linewidth;
    boolean filled;
    boolean dashed;
    
    public FlyArrow(int x[],int y[] , Color color , int linewidth , boolean filled , boolean dashed){
        this.x = x;
        this.y = y;
        this.color = color;
        this.linewidth = linewidth;
	this.filled = filled;
	this.dashed = dashed;
   }
   public int[] getX() { return x; } 
   public int[] getY() { return y; } 
   public int getLineWidth() { return linewidth; }
   public Color getColor(){ return color;} 
   public boolean getFilled(){ return filled;} 
   public boolean getDashed(){ return dashed;}    
} 

class FlyPoints {
    int x[];
    int y[];
    Color color;
    int linewidth;
    
    public FlyPoints(int x[],int y[] , Color color , int linewidth){
        this.x = x;
        this.y = y;
        this.color = color;
        this.linewidth = linewidth;
   }
   public int[] getX() { return x; } 
   public int[] getY() { return y; } 
   public int getLineWidth() { return linewidth; }
   public Color getColor(){ return color;} 
} 

class FlyXlabel {
    String Xlabel;
    Font font;
    Color color;
    public FlyXlabel(String Xlabel, Font font , Color color ){
        this.Xlabel = Xlabel;
	this.font = font;
	this.color = color;
   }
   
   public String getXlabel() { return Xlabel; } 
   public Font getFont() { return font; } 
   public Color getColor() { return color; }
} 

class FlyYlabel {
    String Ylabel;
    Font font;
    Color color;
    public FlyYlabel(String Ylabel, Font font , Color color ){
        this.Ylabel = Ylabel;
	this.font = font;
	this.color = color;
   }
   
   public String getYlabel() { return Ylabel; } 
   public Font getFont() { return font; } 
   public Color getColor() { return color; }
} 


class FlyXscale {
    int x[];
    String Xlabel[];
    boolean use_xscale;
    Font font;
    Color color;
    int linewidth;
    
    public FlyXscale(int x[], String Xlabel[], boolean use_xscale, Font font , Color color , int linewidth){
        this.x = x;
        this.Xlabel = Xlabel;
        this.use_xscale = use_xscale;
	this.font = font;
	this.color = color;
	this.linewidth = linewidth;
   }
   
   public int[] getX() { return x; } 
   public boolean use_xscale() { return use_xscale; }
   public String[] getXlabel() { return Xlabel; } 
   public Font getFont() { return font; } 
   public Color getColor() { return color; }
   public int getLineWidth() { return linewidth; }
    
} 

class FlyYscale {
    int y[];
    String Ylabel[];
    boolean use_yscale;
    Font font;
    Color color;
    int linewidth;

    public FlyYscale( int y[], String Ylabel[],boolean use_yscale,Font font , Color color , int linewidth){
        this.y = y;
        this.Ylabel = Ylabel;
        this.use_yscale = use_yscale;
	this.font = font;
	this.color = color;
	this.linewidth = linewidth;
   }
   
   public int[] getY() { return y; } 
   public boolean use_yscale() { return use_yscale; }
   public String[] getYlabel() { return Ylabel; } 
   public Font getFont(){return font;}
   public Color getColor(){return color;}
   public int getLineWidth() { return linewidth; }
} 

class FlyInput {
    int x;
    int y;
    int xsize;
    int ysize;
    int index;
    Font font;
    Color bgcolor;    
    Color fgcolor;
    String value;
    boolean editable;
    
    public FlyInput( int x, int y, int xsize, int ysize, Font font , Color bgcolor, Color fgcolor, int index,boolean editable,String value ){
        this.x = x;
        this.y = y;
        this.xsize = xsize;
        this.ysize = ysize;
	this.font = font;
	this.bgcolor = bgcolor;
	this.fgcolor = fgcolor;
	this.index = index;
	this.editable = editable;
	this.value = value;
   }
   
   public int getX() { return x; } 
   public int getY() { return y; } 
   public int getXsize() { return xsize; } 
   public int getYsize() { return ysize; } 
   public Font getFont(){return font;}
   public Color getBgcolor(){return bgcolor;}
   public Color getFgcolor(){return fgcolor;}
   public int getIndex(){return index; } 
   public boolean getEditable(){return editable;}
   public String getValue(){return value;}
   
} 

class FlyPoint {
    int x;
    int y;
    Color color;
    int linewidth;
    Font font;
    
    public FlyPoint(int x,int y , Color color , int linewidth){
        this.x = x;
        this.y = y;
        this.color = color;
        this.linewidth = linewidth;
   }
   public int getX() { return x; } 
   public int getY() { return y; } 
   public int getLineWidth() { return linewidth; }
   public Color getColor(){ return color;}
   public Font getFont(){ return font;} 
} 

class FlyGrid {
    int x_major[];
    int x_minor[];
    int y_major[];
    int y_minor[];
    Color color_major;
    Color color_minor;
    int linewidth_major;
    int linewidth_minor;
    boolean dashed;
    
    public FlyGrid(int x_major[] , int y_major[] , int x_minor[] , int y_minor[] , 
    Color color_major , Color color_minor , int linewidth_major , int linewidth_minor, boolean dashed ){
        this.x_minor = x_minor;
        this.y_minor = y_minor;
        this.x_major = x_major;
        this.y_major = y_major;
        this.color_major = color_major;
        this.color_minor = color_minor;
        this.linewidth_major = linewidth_major;
        this.linewidth_minor = linewidth_minor;
        this.dashed = dashed;
   }
   public int[] getX_major() { return x_major; } 
   public int[] getY_major() { return y_major; } 
   public int[] getX_minor() { return x_minor; } 
   public int[] getY_minor() { return y_minor; } 
   public int getLineWidth_major() { return linewidth_major; }
   public int getLineWidth_minor() { return linewidth_minor; }
   public Color getColor_major(){ return color_major;} 
   public Color getColor_minor(){ return color_minor;} 
   public boolean getDashed(){ return dashed;} 
} 

class FlyImage {
    int x;
    int y;
    BufferedImage image;
    
    public FlyImage(int x,int y , BufferedImage image ){
        this.x = x;
        this.y = y;
	this.image = image;
   }
   public int getX() { return x; } 
   public int getY() { return y; } 
   public BufferedImage getImage(){ return image;} 
} 

class FlyText {
    int x;
    int y;
    int angle;
    Font font;
    String txt;
    Color color;
    
    public FlyText(int x,int y , int angle , Font font, String txt, Color color ){
        this.x = x;
        this.y = y;
	this.angle = angle;
        this.color = color;
        this.font = font;
	this.txt = txt;
   }
   public int getX() { return x; } 
   public int getY() { return y; } 
   public int getRotation() { return angle; } 
   public Font getFont() { return font; }
   public Color getColor(){ return color;} 
   public String getTXT(){ return txt;} 
}

class FlyReply{
    String reply;
    int x;
    int y;
    public FlyReply(String reply, int x, int y){
	this.reply = reply;
	this.x = x;
	this.y = y;
    }
    
    public String getReply(){return reply;}
    public int getX(){return x;}
    public int getY(){return y;}
}

class FlyApplet_panel extends JPanel implements MouseListener, MouseMotionListener {
    public static final int CURVE=0, RECT=1, CIRCLE=2, LINES=3, LINE=4,
     SLINE=5,SEG=6,POLY=7,POINTS=8,VEC=9,MLINES=10,NULL=-1;
    public static int ctype;
    static int ll=4;
    Image bg;
    Vector lines=new Vector(16384);
    int x1,y1;
    int x2,y2;
    int radius;
    double Radius;//in coords
    int drag;
    int st;
    double xmin,ymin,xmax,ymax,precision;
    int xsize,ysize,linewidth;
    boolean dashed,use_coords,stopdrawing;
    boolean display_coords = true;
    boolean cross = true;
    public static boolean filled = false;
    public static String coordinates=" ";
    Font font;
    Color fgcolor;
    Color bgcolor; 
    public static FontMetrics fm;

    public FlyApplet_panel(Color Bgcolor,Color Fgcolor, Image gotbg , int LineWidth , int Xsize ,int Ysize, boolean Dashed,
     boolean Use_Coords , double Precision , double Xmin,double Ymin,double Xmax,double Ymax,Font Font, boolean Cross ){
	bgcolor=Bgcolor;
	fgcolor =Fgcolor;
	setBackground(bgcolor);
	setForeground(fgcolor);
	bg=gotbg;
	dashed = Dashed;
	linewidth = LineWidth;
	st=0;
	xmin=Xmin;
	xmax=Xmax;
	ymin=Ymin;
	ymax=Ymax;
	font = Font;
	xsize=Xsize;
	ysize=Ysize;
	use_coords = Use_Coords;
	cross = Cross;
	precision = Precision;
	addMouseMotionListener(this);
	addMouseListener(this);
    }
   
    public String points2string(String rep) {
	StringBuffer buf=new StringBuffer(16384);
	buf.append(rep);
	switch(ctype) {
	    case NULL:break;
	    case POLY:
	    case POINTS:
	    case LINES:
	    case MLINES:
	    case CURVE: {
		int i, np;
		Point p=null;
		np=lines.size();
		for(i=0;i<np;i++) {
		    p=(Point)lines.elementAt(i);
		    buf.append(p.x).append(",").append(p.y).append(";");
		}
		break;
	    }
	    case SLINE:
	    case LINE:
	    case SEG:
	    case VEC:
	    case RECT: {
		if(st>0) {
		    buf.append(x1).append(",").append(y1).append(",").append(x2).append(",").append(y2);
		}
		break;
	    }
	    case CIRCLE: {
		if(st>0) {
		    buf.append(x1).append(",").append(y1).append(",").append(radius);
		}
		break;
	    }
	}
	return buf.toString();
    }

    public String Coords2String(){// returns values in the coordsystem xrang/yrange and rounded to "precision" 
	StringBuffer buf=new StringBuffer(16384);
//	if(lines.size() == 0){return "error";}
//	else{
	    if( (ctype == 1 || ctype == 4 || ctype == 5 || ctype == 6 || ctype == 9 ) && st>0){
		buf.append(px2x(x1)).append(",").append(py2y(y1)).append(",").append(px2x(x2)).append(",").append(py2y(y2));
	    }
	    else
	    if( ctype == 2 && st>0 ){
		buf.append(px2x(x1)).append(",").append(py2y(y1)).append(",").append((Math.round(precision*Radius))/precision);
	    }
	    else{
		int i, np;
	        Point p=null;
		np=lines.size();
	        for(i=0;i<np;i++){
	    	    p=(Point)lines.elementAt(i);
		    if(i != 0){
			buf.append(",").append(px2x(p.x)).append(",").append(py2y(p.y));
		    }else{
			buf.append(px2x(p.x)).append(",").append(py2y(p.y));// single point
		    }
		}
	    }
//	}
	
	return buf.toString();
    }
   
    public void retry() {
	lines.removeAllElements();
	st=0; repaint();
    }

    public void mouseDragged(MouseEvent e) {
	int t=lines.size();
	int dr;
        e.consume();
	switch(ctype) {
	    case NULL:break;
	    case CURVE: {
		if(t<2000) {
		    x1=e.getX(); y1=e.getY();
		    lines.addElement(new Point(x1, y1));
		    repaint();
		}
		st=2; return;
	    }
	    default: {
		dr=drag; mouseMoved(e); drag=dr+1;
		return;
	    }
	}
    }

    public void mouseMoved(MouseEvent e) {
        e.consume(); drag=0;
	if(use_coords){
	    double mx = px2x(e.getX());
	    double my =  py2y(e.getY());
	    if(ctype == 2){
	    coordinates = "(" + mx + ":" + my + ")" + " R="+Radius;
	    }else{coordinates = "(" + mx + ":" + my + ")";}
	    repaint();
	}
	switch(ctype) {
	    case NULL:break;
	    case POLY:{if(stopdrawing){mouseExited(e);return;}}
	    case POINTS:
	    case MLINES:
	    case LINES:if(st==1){mouseClicked(e);}return;
	    case CURVE: {
		if(st==0) return; else st=1;
		x2=e.getX(); y2=e.getY(); break;
	    }
	    case CIRCLE:
	    case SLINE:
	    case LINE:
	    case SEG:
	    case VEC:
	    case RECT: {
		if(st!=1) return;
		x2=e.getX(); y2=e.getY();
		radius=(int) Math.sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
		Radius=(double) (Math.round(precision*(Math.sqrt((px2x(x2)-px2x(x1))*(px2x(x2)-px2x(x1))+(py2y(y2)-py2y(y1))*(py2y(y2)-py2y(y1))))))/precision;
		break;
	    }
	    default:return;
	}
	if(ctype!=POINTS) repaint();
    }

    public void mousePressed(MouseEvent e) {
	mouseClicked(e);
        e.consume();
	switch(ctype) {
	    case NULL:break;
	    case CURVE: {
		mouseClicked(e);
		if(st>0) return;
		x1=e.getX(); y1=e.getY(); x2=x1; y2=y1;
		lines.removeAllElements();
		lines.addElement(new Point(x1,y1));
		repaint(); st=2;
		return;
	    }
	    case POLY:{if(stopdrawing){mouseExited(e);return;}}
	    case POINTS:
	    case MLINES: {
		x2=e.getX(); y2=e.getY();
		if(st==0) lines.removeAllElements();
		lines.addElement(new Point(x2,y2));
		st=1;  repaint(); return;
	    }
	    case LINES: {
		x2=e.getX(); y2=e.getY();
		if(st==0) lines.removeAllElements();
		lines.addElement(new Point(x2,y2));
		st=1; x1=x2; y1=y2; repaint(); return;
	    }
	    case CIRCLE:
	    case SLINE:
	    case LINE:
	    case SEG:
	    case VEC:
	    case RECT: {
		x2=e.getX(); y2=e.getY();
		switch(st) {
		    case 2:
		    case 0: x1=x2; y1=y2; radius=0; st=1; repaint(); return;
		    case 1: {
			radius=(int) Math.sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
			//Radius=(double) Math.sqrt((px2x(x2)-px2x(x1))*(px2x(x2)-px2x(x1))+(py2y(y2)-py2y(y1))*(py2y(y2)-py2y(y1)));
			st=2; return;
		    }
		}		
		break;
	    }
	    default: return;
	}
    }

    public void mouseReleased(MouseEvent e) {
	e.consume();
	switch(ctype) {
	    case NULL:break;
	    case CURVE: {
		if(st==2) return;
		x2=e.getX(); y2=e.getY();
		if(st==0) lines.removeAllElements();
		lines.addElement(new Point(x2,y2));
		st=1; x1=x2; y1=y2;
		return;
	    }
	    case POINTS: return;
	    default: {
		if(st>0 && drag>=8) mousePressed(e);
		return;
	    }
	}
    }

    public void mouseEntered(MouseEvent e) {
	display_coords=true;
    }

    public void mouseExited(MouseEvent e) {
	display_coords=false;if(use_coords){repaint();}
	if(ctype!=CURVE && ctype!=LINES && ctype!=POLY) return;
	e.consume();
	x2=x1; y2=y1;
	repaint();
    }

    public void mouseClicked(MouseEvent e){
	if( e.getButton() == MouseEvent.BUTTON3){//right mouse click removes stuff 
	    stopdrawing = false;
	    switch(ctype) {
		case NULL:break;
		case CURVE:
	        case POLY:if(lines.size()>0){RemoveRange(lines.size()-1,lines.size());x1=e.getX();y1=e.getY();repaint();}return;
	        case POINTS:RemoveElement(e.getX(),e.getY());repaint();return;
	        case MLINES:if(lines.size()>0){RemoveRange(lines.size()-1,lines.size());x1=e.getX();y1=e.getY();repaint();}return;
	        case LINES:if(lines.size()>0){RemoveRange(lines.size()-1,lines.size());x1=e.getX();y1=e.getY();repaint();}return;
	        case CIRCLE:RemoveElement(e.getX(),e.getY());repaint();return;
	        case SLINE:RemoveElement(e.getX(),e.getY());repaint();return;
	        case LINE:RemoveElement(e.getX(),e.getY());repaint();return;
		case SEG:RemoveElement(e.getX(),e.getY());repaint();return;
	        case VEC:RemoveElement(e.getX(),e.getY());repaint();return;
	        case RECT:RemoveElement(e.getX(),e.getY());repaint();return;
		default : return;
	    }
	}
    }
    
    public void repaint(Graphics g){
	update(g);
    }
    
    public void update(Graphics g){
	paintComponent(g);
    }

    public void RemoveRange(int i,int ii){
	if(i == 0){lines.removeAllElements();}
	else{
	    for(int p=i;p<ii;p++){
		lines.remove(p);
	    }
	}
    }
    public void RemoveElement(int x,int y){
	Point p=null;
	int np=lines.size();
	int marge=2*linewidth;
	for(int i=0;i<np;i++){
	    p=(Point)lines.elementAt(i);
	    if(p.x-marge < x  && p.x+marge > x && p.y-marge < y  && p.y+marge > y){
		lines.remove(i);
		break;
	    } 
	}
    }
    public void paintComponent(Graphics g1){
	g1.clearRect(0,0,xsize,ysize); 
	Graphics2D g = (Graphics2D) g1;
	if(bg!=null) g.drawImage(bg,0,0,this);
	if(dashed){
	    g.setStroke(new BasicStroke(linewidth,BasicStroke.JOIN_ROUND,BasicStroke.JOIN_BEVEL,1,new float[] {9},0));                                                                                        
	}else{
	    g.setStroke( new BasicStroke(linewidth));
	}
	int np=lines.size();
	Point pp;
	if(use_coords && display_coords){
	    g.setFont(font);
	    g.setColor(Color.black);
	    g.drawString(coordinates,0,20);
	    g.setColor(fgcolor);
	}
	switch(ctype) {
	    case POINTS: {
		if(np>0) for (int i=0; i < np; i++) 
		  pointPaint(g,(Point)lines.elementAt(i),cross);
		break;
	    }
	    case POLY:
	    case CURVE:
	    case MLINES:{                                                                                                                  
                if(np>0) {                                                                                                                 
                    Point p1,p2;                                                                                                           
                    if(np%2 == 1){                                                                                                         
                        p1=(Point)lines.elementAt(np - 1);                                                                                 
                        paintPoint(g,p1.x,p1.y,true);                                                                                      
                    }                                                                                                                      
                    else                                                                                                                   
                    {                                                                                                                      
                        p1=(Point)lines.elementAt(np - 1);                                                                                 
                        p2=(Point)lines.elementAt(np - 2);                                                                                 
                        paintPoint(g,p1.x,p1.y,true);                                                                                      
                        paintPoint(g,p2.x,p2.y,true);                                                                                      
                    }                                                                                                                      
                    for (int i=0; i < np - 1; i=i+2) {                                                                                     
                        p1=(Point)lines.elementAt(i);                                                                                      
                        p2=(Point)lines.elementAt(i+1);                                                                                    
                        g.drawLine(p1.x, p1.y, p2.x, p2.y);                                                                                
                    }                                                                                                                      
                                                                                                                                           
                }                                                                                                                          
                break;                                                                                                                     
            }
	    case LINES: {
		if(np>0) {
		    pp=(Point)lines.elementAt(0);
		    for (int i=1; i < np; i++) {
			Point p=(Point)lines.elementAt(i);
			g.drawLine(pp.x, pp.y, p.x, p.y);
			pp=p;
		    }
		    if (st==1) g.drawLine(x1, y1, x2, y2);
		}
		if(ctype==POLY && np>1) {
		    // filled
		    if(!filled){
			Point p1=(Point)lines.elementAt(0);
			Point p2=(Point)lines.elementAt(np-1);
			if(st==0){ g.drawLine(p1.x,p1.y,p2.x,p2.y); } else { g.drawLine(p1.x,p1.y,x2,y2);}
		    }
		    else
		    {
			int xpoly[] = new int[np];
			int ypoly[] = new int[np];
			for(int i=0;i<np;i++){
			    Point p=(Point)lines.elementAt(i);
			    xpoly[i] = p.x;
			    ypoly[i] = p.y;
			}
			g.fillPolygon(xpoly,ypoly,np);
		    }
		}
		break;
	    }
	    case SEG:
	    case VEC:
	    case SLINE:
	    case LINE:
	    case RECT: {
		if(st>0) {
		    int xx1,yy1,xx2,yy2;
		    int X1,Y1,X2,Y2,max;
		    xx1=Math.min(x1,x2); yy1=Math.min(y1,y2);
		    xx2=Math.max(x1,x2); yy2=Math.max(y1,y2);
		    max=Math.max(Math.abs(x2-x1),Math.abs(y2-y1));
		    if(max<10) max=10;
		    max=500/max+1;
		    switch(ctype) {
			case RECT:if(!filled){g.drawRect(xx1,yy1,xx2-xx1,yy2-yy1);}else{g.fillRect(xx1,yy1,xx2-xx1,yy2-yy1);} break;
			case SLINE: {
			    g.fillOval(x1-2,y1-2,4,4);
			    g.drawLine(x1,y1,max*x2-(max-1)*x1,max*y2-(max-1)*y1); break;
			}
			case LINE: {
			    g.fillOval(x1-2,y1-2,4,4);
			    g.fillOval(x2-2,y2-2,4,4);
			    g.drawLine(max*x1-(max-1)*x2,max*y1-(max-1)*y2,
				       max*x2-(max-1)*x1,max*y2-(max-1)*y1); break;
			}
			case SEG: g.drawLine(x1,y1,x2,y2); break;
			case VEC: {
			    g.drawLine(x1,y1,x2,y2);
			    if(radius > 5) { /* arrow head */
				double dx,dy,dd[];
				int xx[], yy[];
				dd=new double[6];
				xx=new int[3];
				yy=new int[3];
				//double l=12;
				double l=linewidth;
				double fat=linewidth*0.3;
				xx[0]=x2;yy[0]=y2;
				dx=x1-x2; dy=y1-y2;
				dd[0]=l*dx/radius; dd[1]=l*dy/radius;
				dd[2]=dd[0]+dd[1]*fat; dd[3]=dd[1]-dd[0]*fat;
				dd[4]=dd[0]-dd[1]*fat; dd[5]=dd[1]+dd[0]*fat;
				xx[1]=(int) (dd[2]+xx[0]);
				yy[1]=(int) (dd[3]+yy[0]);
				xx[2]=(int) (dd[4]+xx[0]);
				yy[2]=(int) (dd[5]+yy[0]);
				g.fillPolygon(xx,yy,3);
			    }
			    break;
			}
		    }
		}
		break;
	    }
	    case CIRCLE: {
		if(st>0) {
		    pointPaint(g,new Point(x1,y1),cross);
		    if(!filled){
			g.drawOval(x1-radius,y1-radius,radius*2,radius*2);
		    }else{g.fillOval(x1-radius,y1-radius,radius*2,radius*2);}
		}
		break;
	    }
	}
    }
    
   void pointPaint(Graphics g, Point p, boolean cross) {
	if(cross){
	    g.drawLine(p.x-ll,p.y+ll,p.x+ll,p.y-ll);
	    g.drawLine(p.x+ll,p.y+ll,p.x-ll,p.y-ll);
	}else{
	    g.fillOval(p.x - linewidth,p.y - linewidth , 2*linewidth, 2*linewidth);
	}
    }
   void paintPoint(Graphics g,int x, int y, boolean cross) {                                                                               
        if(cross){                                                                                                                         
            g.drawLine(x-ll,y+ll,x+ll,y-ll);                                                                                               
            g.drawLine(x+ll,y+ll,x-ll,y-ll);                                                                                               
        }else{                                                                                                                             
            g.fillOval(x - linewidth,y - linewidth , 2*linewidth, 2*linewidth);                                                            
        }                                                                                                                                  
    } 

    public double px2x(int px){ //pixel to x-coords 
	double X =  px*(xmax - xmin)/xsize + xmin;
	X = (Math.round(precision*(X)))/precision;
	return X;
    }
    public double py2y(int py){ // pixel to x-coords 
	double Y =ymax -  py*(ymax - ymin)/ysize;
	Y = (Math.round(precision*(Y)))/precision;
	return Y;
    }
}// end FlyApplet_panel


class FlyApplet_controls extends Panel implements ActionListener {
   FlyApplet ci;
   FlyApplet_panel targ;
   Button retry, ok;
   
   public FlyApplet_controls(FlyApplet_panel pan, FlyApplet cci) {
       this.ci=cci;
       targ=pan;
       setLayout(new GridLayout());
       setBackground(Color.white);
       retry=new Button(FlyApplet.retry);
       retry.addActionListener(this);
       ok=new Button(FlyApplet.prompt);
       ok.addActionListener(this);
       add(retry); add(ok);
   }

   public void actionPerformed(ActionEvent e) {
       Object src=e.getSource();
       if(src == retry) targ.retry();
       if(src == ok) ci.replyback();
   }
  
}
