/*   
 *  Configuration: config.html
 *  Status: Free
 *  Java Boutique:Upload Date October 11, 1999
 *  Author: Saket Kumar
 *  download from: http:*javaboutique.internet.com/PieChart/index.html
 *  PieChart.java  for Drawing Bar Chart.
 *  slightly altered: J.M. Evers 
 *  extra params: degree,radian,rounding etc etc                                                                                                           
 *  This program is free software; you can redistribute it and/or modify                                       
 *  it under the terms of the GNU General Public License as published by                                       
 *  the Free Software Foundation; either version 2 of the License, or                                          
 *  (at your option) any later version.                                                                        
 *                                                                                                             
 *  This program is distributed in the hope that it will be useful,                                            
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                                             
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                                              
 *  GNU General Public License for more details.                                                               
 *                                                                                                             
 *  You should have received a copy of the GNU General Public License                                          
 *  along with this program; if not, write to the Free Software                                                
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                                                  
 */  


/*
* adapted for WIMS by jm.evers
* public JS functions: ReadApplet()
* public JS functions: SetApplet()
*
*
*
*/
import java.awt.*;
import java.io.*;
import java.lang.*;
import java.applet.Applet;
import java.util.*;
import java.io.PrintStream;

public class PieChart extends java.applet.Applet {

    String	title;
    Font        font;
    FontMetrics fontMetrics;
    int		titleHeight = 15;
    int		columns;
    public int 	round=1000;
    public float values[];
    Color       colors[];
    public String labels[];
    public float percent[];
    public float angle[];
    public float degree[];
    public float radian[];
    public float rawinput[];
    int		maxLabelWidth = 0;
    int         maxValueWidth = 0;
    int		max = 0;
    int         strWidth=0;
    public boolean showLabel=true;   // Whether to display the label or not
    public boolean showPercent=false; // Whether to display percentage or not
    public boolean showRadians=false; // Whether to display radians or not
    public boolean showDegrees=false; // Whether to display degrees or not
    public boolean showInput=true; // Whether to display raw input numbers
    String      unit; // Whether to display a unit for rawinput values?

    int lx=0,ly=0;          //For Writing Label
    int cx=0,cy=0;          //Center of Circle

  public synchronized void init() {
    String temp;font = new java.awt.Font("Sanserif", Font.BOLD, 12);
    fontMetrics = getFontMetrics(font);
    String bgColor=getParameter("bgcolor"); // Background color of Chart
    if (bgColor==null)
       setBackground(Color.white);
    else{
        if (bgColor.equals("red")) {
            setBackground(Color.red);
        } else if (bgColor.equals("green")) {
            setBackground(Color.green);
        } else if (bgColor.equals("blue")) {
            setBackground(Color.blue);
        } else if (bgColor.equals("pink")) {
            setBackground(Color.pink);
        } else if (bgColor.equals("orange")) {
            setBackground(Color.orange);
        } else if (bgColor.equals("magenta")) {
            setBackground(Color.magenta);
        } else if (bgColor.equals("cyan")) {
            setBackground(Color.cyan);
        } else if (bgColor.equals("white")) {
            setBackground(Color.white);
        } else if (bgColor.equals("yellow")) {
            setBackground(Color.yellow);
        } else if (bgColor.equals("gray")) {
            setBackground(Color.gray);
        } else if (bgColor.equals("darkGray")) {
            setBackground(Color.darkGray);
	    } else {
        setBackground(Color.white);
	    }
    }
    title = getParameter("title"); // Title of the Pie Chart
    if (title == null) {title = "WIMS Pie Chart";}

    unit = getParameter("unit"); // Title of the Pie Chart
    if (unit == null) {unit = "";}
    
    temp = getParameter("columns");
    if (temp == null) { columns = 5;} else {columns = Integer.parseInt(temp);}

    temp = getParameter("rounding");
    if (temp != null){round = Integer.parseInt(temp);if ( round < 1){ round=100;}}

    temp = getParameter("showdegrees");
    if (temp == null){showDegrees = false;}
    else
    {
	if (temp.equalsIgnoreCase("YES")){showDegrees = true;}
	if (temp.equalsIgnoreCase("NO")){showDegrees = false;}
    }
    temp = getParameter("showradians");
    if (temp == null){showRadians = false;}
    else
    {
	if (temp.equalsIgnoreCase("YES")){showRadians = true;}
	if (temp.equalsIgnoreCase("NO")){showRadians = false;}
    }

    temp = getParameter("showinput");
    if (temp == null){showInput = true;}
    else
    {
	if (temp.equalsIgnoreCase("YES")){showInput = true;}
	if (temp.equalsIgnoreCase("NO")){showInput = false;}
    }

    temp = getParameter("showlabel");
    if (temp == null) {showLabel = false;} 
    else 
    {
	if (temp.equalsIgnoreCase("YES")){showLabel = true;}
	if (temp.equalsIgnoreCase("NO")){showLabel = false;}
    }

    temp = getParameter("showpercent");
    if (temp == null) {showPercent = false;}
    else
    { 
        if (temp.equalsIgnoreCase("YES")){showPercent = true;}
        if (temp.equalsIgnoreCase("NO")){showPercent = false;}
    }
    
    radian = new float[columns];
    degree = new float[columns];
    rawinput = new float[columns];
    values = new float[columns];
    colors = new Color[columns];
    labels = new String[columns];
    percent= new float[columns];
    angle  = new float[columns];
    
    
    String tmp=null; 
    float totalValue=0;
    for (int i=0; i < columns; i++) {
	tmp=getParameter("Pvalue" + (i+1));
	float f = Float.valueOf(tmp.trim()).floatValue();
        values[i] =f;
	float t = Float.valueOf(tmp).floatValue();
	rawinput[i]=t;
        totalValue +=  values[i];
	// parse the label for this column
        temp = getParameter("P" + "label"+ (i+1) );
        labels[i] = (temp == null) ? "" : temp;
        maxLabelWidth = Math.max(fontMetrics.stringWidth((String)(labels[i])),maxLabelWidth);
	// parse the color attribute for this column
        temp = getParameter("P" + "color"+ (i+1) );
        if (temp != null) {
        if (temp.equals("red")) {
		    colors[i] = Color.red;
        } else if (temp.equals("green")) {
		    colors[i] = Color.green;
        } else if (temp.equals("blue")) {
		    colors[i] = Color.blue;
        } else if (temp.equals("pink")) {
		    colors[i] = Color.pink;
        } else if (temp.equals("orange")) {
		    colors[i] = Color.orange;
        } else if (temp.equals("magenta")) {
		    colors[i] = Color.magenta;
        } else if (temp.equals("cyan")) {
		    colors[i] = Color.cyan;
        } else if (temp.equals("white")) {
		    colors[i] = Color.white;
        } else if (temp.equals("yellow")) {
		    colors[i] = Color.yellow;
        } else if (temp.equals("gray")) {
		    colors[i] = Color.gray;
        } else if (temp.equals("darkGray")) {
		    colors[i] = Color.darkGray;
		} else {
		    colors[i] = Color.gray;
		}
	    } else {
		colors[i] = Color.gray;
	    }
    }
    float multiFactor = 100 / totalValue;

	for (int i=0; i < columns; i++) {
        percent[i]= (float) (Math.round(round*values[i] * multiFactor))/round;
        angle[i]  = (float) (Math.round(round*3.6*values[i] * multiFactor))/round;  // Calculation of Angle (360/100)
	degree[i] = (float) (Math.round(round*percent[i] * 3.6))/round ;
	radian[i] = (float) (Math.round(round*angle[i]/180))/round; // * pi rad !!!
    }

  }

// paint method

  public synchronized void paint(Graphics g) {
    int  x=0;
    int  y=0;
    int width=0,height=0;
    int ax=0,ay=0;          //For Drawing Black line from center to Peripherial
    int px=0,py=0;          //For Writing Percentage
    int radius=0;
    width=height=Math.min((getSize().width - 100),(getSize().height - 100));
    x=y=50;

    if ( getSize().width > width ){
        x = (getSize().width - width ) /2 ; 
    }

    cx = x + width/2;
    cy = y + height/2;
    radius = width/2;

    // Draw the Title of the Chart on Top of the Applet

    strWidth=fontMetrics.stringWidth(title);
    Font fnt = new java.awt.Font("Sanserif", Font.BOLD, 16);
    g.setFont(fnt);
    g.setColor(Color.red);
    g.drawString(title,((getSize().width - strWidth )/2),15);
    g.setFont(font);
    int initAngle=90;
    int sweepAngle=0;
    int incSweepAngle=0;
    int incLabelAngle= (int) (angle[0]/2);

    for (int i=0; i < columns; i++) {
        sweepAngle = (int) Math.round(angle[i]);
        g.setColor((Color)colors[i]);

        if (i==(columns-1)){
            sweepAngle = 360 - incSweepAngle;
            g.fillArc(x,y,width,height,initAngle,(-sweepAngle));
            g.setColor(Color.black);
            g.drawArc(x,y,width,height,initAngle,(-sweepAngle));

            lx = (int) (cx + ( radius * Math.cos((incLabelAngle * 3.14f/180) - 3.14f/2)));
            ly = (int) (cy + ( radius * Math.sin((incLabelAngle * 3.14f/180) - 3.14f/2)));
	    adjustLabel(i);
	    int ly2=ly+15;

            if (showLabel)
	    {
            	g.drawString((String)labels[i] ,lx,ly);
		
		if (showDegrees){g.drawString(String.valueOf(degree[i]) + "\u00b0" ,lx,ly2);}
		
		else
		{ 
		    if (showRadians){g.drawString( String.valueOf(radian[i]) +"\u03c0 rad" ,lx,ly2);}
		    else
		    {
			if (showPercent){g.drawString( String.valueOf(percent[i]) +" %" ,lx,ly2);}
			else
			{
			    if (showInput){g.drawString( String.valueOf(rawinput[i])+"  "+unit,lx,ly2);}
			}
		    }
		}
            }
	    else
	    {
		if (showDegrees){g.drawString(String.valueOf(degree[i]) + "\u00b0" ,lx,ly2);}
		
		else
		{ 
		    if (showRadians){g.drawString( String.valueOf(radian[i]) +"\u03c0 rad" ,lx,ly2);}
		    else
		    {
			if (showPercent){g.drawString( String.valueOf((Math.round(round*percent[i]))/round) +" %" ,lx,ly2);}
			else
			{
			    if (showInput){g.drawString( String.valueOf(rawinput[i])+"  "+ unit,lx,ly2);}
			}
		    }
		}
	    }
            break;
        }

        g.fillArc(x,y,width,height,initAngle,(-sweepAngle));
        g.setColor(Color.black);
        g.drawArc(x,y,width,height,initAngle,(-sweepAngle));
        incSweepAngle +=sweepAngle;

        ax = (int) (cx + ( radius * Math.cos((incSweepAngle * 3.14f/180) - 3.14f/2)));
        ay = (int) (cy + ( radius * Math.sin((incSweepAngle * 3.14f/180) - 3.14f/2)));
        g.drawLine(cx,cy,ax,ay);

        lx = (int) (cx + ( radius * Math.cos((incLabelAngle * 3.14f/180) - 3.14f/2)));
        ly = (int) (cy + ( radius * Math.sin((incLabelAngle * 3.14f/180) - 3.14f/2)));
        adjustLabel(i);
	int ly2=ly+15;	        
	if (showLabel){
            g.drawString((String)labels[i],lx,ly);
	    if ( showDegrees){g.drawString(String.valueOf(degree[i]) + "\u00b0" ,lx,ly2);}
	    else
	    {
		if ( showRadians){g.drawString(String.valueOf(radian[i])+"\u03c0 rad" ,lx,ly2);}
		else
		{
		    if (showPercent){g.drawString( String.valueOf(percent[i]) +" %" ,lx,ly2);}
		    else
		    {
			if (showInput){g.drawString( String.valueOf(rawinput[i])+"  "+unit,lx,ly2);}
		    }
		}
    	    }
	}
	else
	{
	    if ( showDegrees){g.drawString(String.valueOf(degree[i]) + "\u00b0" ,lx,ly2);}
	    else
	    {
		if ( showRadians){g.drawString(String.valueOf(radian[i])+"\u03c0 rad" ,lx,ly2);}
		else
		{
		    if (showPercent){g.drawString( String.valueOf((Math.round(round*percent[i]))/round) +" %" ,lx,ly2);}
		    else
		    {
			if (showInput){g.drawString( String.valueOf(rawinput[i])+"  "+unit,lx,ly2);}
		    }
		}	
    	    }
	}
        incLabelAngle = incLabelAngle + (int) (angle[i]/2 + angle[i+1]/2);
        initAngle += (-sweepAngle);
    }
    g.setColor(Color.black);
    g.drawLine(cx,cy,cx,cy-radius);
  }

  private void adjustLabel(int i){
    if ( (lx > cx) && (ly < cy) ){
        lx +=5;
        ly -=5;
    }

    if ( (lx > cx) && (ly > cy) ){
        lx +=5;
        ly +=10;
    }

    if ( (lx < cx) && (ly > cy) ){
        strWidth=fontMetrics.stringWidth(labels[i]);
        lx -= strWidth+5;
        if (lx < 0)
            lx=0;
    }

    if ( (lx < cx) && (ly < cy) ){
        strWidth=fontMetrics.stringWidth(labels[i]);
        lx -= strWidth+5;
        if (lx < 0)
           lx=0;
    }
  }
  
  
// 	jm.evers 3/2008 modification to avoid intervening of WIMS in the update of the applet
// 	that was a real waste of recources !!!
//   	public static String replace(String source, String pattern, String replace){
//	if (source!=null){
//	    final int len = pattern.length();                                                                                          
//            StringBuffer sb = new StringBuffer();                                                                                      
//            int found = -1;                                                                                                            
//            int start = 0;                                                                                                             
//            while( (found = source.indexOf(pattern, start) ) != -1) {                                                                  
//                sb.append(source.substring(start, found));                                                                             
//                sb.append(replace);                                                                                                    
//                start = found + len;                                                                                                   
//            }                                                                                                                          
//            sb.append(source.substring(start));                                                                                            
//            return sb.toString();                                                                                                          
//            }                                                                                                                              
//        else return "";                                                                                                                    
//    }   
  
  public String ReadApplet(){
  // ATTENTION  MSIE-6 ? will not accept an array[]:it must be a string!!!
    int len=values.length;String reply="";
    if(len==0){
	reply="error empty answer";
    }
    else
    {
	float p;String l="";
	for(int i=0 ; i<len;i++){
	    l=labels[i];
	    p=rawinput[i];
	    reply=reply+"segment "+i+" [ "+l+" ] = "+p+"\n";
	}
    }
    return reply;
  }
  // SetApplet() is called by javascript
  // it reads the inputfield on the page...strips..."sends" them to the applet
  // use a comma seperated list...   
  // we cannot handle "pi" or "+" or "-" or "*" or "/" etc
  // JAVASCRIPT SHOULD DEAL WITH THIS !!!!!!   
  public void SetApplet( String i){
    String tmp="";float input;
    StringTokenizer R = new StringTokenizer(i,",");
    int max=R.countTokens();
    float value[]=new float[max];float sum=0;
    for(int p=0;p<max;p++){
	tmp=R.nextToken();
	if(tmp.length()==0){tmp="0";}
	input=Float.valueOf(tmp).floatValue();
	System.out.println("input = " + input +"\n"); 
	rawinput[p]=input;
	value[p]=input;
	sum=sum+input;
    }
    for(int p=0;p<max;p++){
	input=value[p];
	// we show the correct circlediagram...maybe the sum of the degrees were != 360 ...we don't care
	angle[p] = 360*input/sum;
	percent[p] = 100*input/sum;
	radian[p] = (float) (input/sum);
	degree[p] = 360*input/sum;
    }
    repaint(); 
  }
  /// end jm.evers 3/2008
}

