// J.M.Evers 16/2/2008 
// This is all amateur scriblings...so No Copyrights
// the applet presents a simple grid...E6/H1 pupils will be asked to
// determine the perimetre and surface area (or ratio of these) of a "freestyle" figure
// build from at least $x squares...
// In the non-interactive mode, a random figure will be shown.
// size_x and size_y may be different: the perimetre will be a float : calulated with x=1 y=size_y/size_x 

// example html page:
//<html>
//	<body>
//		<script language="javascript" type="text/javascript">
//			function lees(){
// 				var input=document.applets[0].ReadApplet(); 
// 				alert(input);
//    				//<--- applet returns: String S=total+","+original+","+changed+","+cnt;
//    				//!! total squares,left original squares,changed squares,perimetre of changed squares
//    				//-->
// 			}
//		</script>
//		<applet id="MathView" code="rooster.class" codebase="." archive="rooster.jar" width="640" height="480">
//	    		<param name="max_x" value="5">
//	    		<param name="max_y" value="5">	    
//	    		<param name="size_x" value="25">
//	    		<param name="size_y" value="50">
//	    		<param name="color1" value="25:100:76">
//	    		<param name="color2" value="orange">
//	    		<param name="interactive" value="0">
//		</applet>
//		<p>
//		<input type="button" name=".....TEST......" value=".....TEST....." onclick="javascript:lees();">
//	</body>
//</html>
// 
// color1="background"
// color2="clicked" in "interactive"=1
// color2="questioncolor" in "interactive"=0
// color may also be "red","green","blue","orange","yellow"

import java.applet.*;
import java.awt.*;
import java.awt.event.*;                                                                                                                        
import java.util.*;
import java.lang.Math;                                                                                                                        

public class rooster extends Applet implements Runnable{
    private static final int serialVersionUID = 1;
    int max_x=20;int max_y=20;
    int rooster[][];
    // = new int[max_y+2][max_x+2];
    int dx;int dy;Thread thread = null;
    Image plaatje;Graphics tekening;
    int hokje_x=20;int hokje_y=20;
    int xsize=hokje_x*max_x;
    int ysize=hokje_y*max_y;
    int R1=111;int G1=222;int B1=040;   
    int R2=040;int G2=222;int B2=111;   
    int interactive=1;

    public void init(){
	String c;
	c=getParameter("color1");
	if(c!=null && c.length()>0){
	    // don't know how to do this in 1 regexp
	    if(c.indexOf(',')== -1 && c.indexOf(':')== -1 && c.indexOf(';')== -1 ){
		if(c.equalsIgnoreCase("red")){R1=255;G1=0;B1=0;}
		else
		if(c.equalsIgnoreCase("green")){R1=0;G1=255;B1=0;}
		else
		if(c.equalsIgnoreCase("blue")){R1=0;G1=0;B1=255;}
		else
		if(c.equalsIgnoreCase("orange")){R1=238;G1=154;B1=0;}
		else
		if(c.equalsIgnoreCase("yellow")){R1=255;G1=255;B1=0;}
		else
		if(c.equalsIgnoreCase("purple")){R1=160;G1=32;B1=240;}
		else{R1=255;G1=0;B1=0;}
	    }
	    else
	    {
		c=c.replace(':',',');c=c.replace(';',',');
		StringTokenizer q = new StringTokenizer(c, ",");
		String k;int rgb;
		for( int a=0; a<3 ; a++){
		    k=q.nextToken();
		    rgb=Integer.parseInt(k, 10);
		    if(rgb<0){rgb=0;}
		    if(rgb>255){rgb=255;}
		    if(a==0){R1=rgb;}
		    if(a==1){G1=rgb;}
		    if(a==2){B1=rgb;}
		}
	    }
	}

	c=getParameter("color2");
	if(c!=null && c.length()>0){
	    if(c.indexOf(',')== -1 && c.indexOf(':')== -1 && c.indexOf(';')== -1 ){
		if(c.equalsIgnoreCase("red")){R2=255;G2=0;B2=0;}
		else
		if(c.equalsIgnoreCase("green")){R2=0;G2=255;B2=0;}
		else
		if(c.equalsIgnoreCase("blue")){R2=0;G2=0;B2=255;}
		else
		if(c.equalsIgnoreCase("orange")){R2=238;G2=154;B2=0;}
		else
		if(c.equalsIgnoreCase("yellow")){R2=255;G2=255;B2=0;}
		else
		if(c.equalsIgnoreCase("purple")){R2=160;G2=32;B2=240;}
		else{R2=0;G2=0;B1=255;}
	    }
	    else
	    {
		c=c.replace(':',',');c=c.replace(';',',');
		StringTokenizer q = new StringTokenizer(c, ",");
		String k;int rgb;
		for( int a=0; a<3 ; a++){
		    k=q.nextToken();
		    rgb=Integer.parseInt(k, 10);
		    if(rgb<0){rgb=0;}
		    if(rgb>255){rgb=255;}
		    if(a==0){R2=rgb;}
		    if(a==1){G2=rgb;}
		    if(a==2){B2=rgb;}
		}
	    }
	}

	c=getParameter("max_x");
	if(c!=null && c.length()>0){
	    max_x = Integer.parseInt(c, 10);
	    if(max_x>20){max_x=20;}
	    if(max_x<3){max_x=3;}                                                                                                              
        }
	c=getParameter("max_y");
	if(c!=null && c.length()>0){
	    max_y = Integer.parseInt(c, 10);
	    if(max_y>20){max_y=20;}
	    if(max_y<3){max_y=3;}                                                                                                              
        }                                                                                                                              
	c=getParameter("size_x");
	if(c!=null && c.length()>0){
	    hokje_x = Integer.parseInt(c, 10);
	    if(hokje_x>60){hokje_x=60;}
	    if(hokje_x<20){hokje_x=20;}
        }
	c=getParameter("size_y");
	if(c!=null && c.length()>0){
	    hokje_y = Integer.parseInt(c, 10);
	    if(hokje_y>60){hokje_y=60;}
	    if(hokje_y<20){hokje_y=20;}
        }

	xsize=hokje_x*(max_x+2);
	ysize=hokje_y*(max_y+2);
	rooster=new int[max_y+2][max_x+2];
	plaatje = createImage(xsize,ysize);
	tekening = plaatje.getGraphics();
	// hele veld met 0 == wit    
	for(int x=0;x<max_x+2;x++){;
	    for(int y=0;y<max_y+2;y++){
		rooster[y][x]=0;
	    }
	}

	c=getParameter("interactive");
	if(c.equals("0")){
	    interactive=0;
	    double p;
	    for(int x=1;x<max_x+1;x++){
		for(int y=1;y<max_y+1;y++){
		    p=Math.random();
		    if(p<0.5){rooster[y][x] = -1;}else{rooster[y][x] = 1;}
		}
	    }
	}
	// plaatje tussen x=1 ...max_x+1 x=0/x=max_x+2===0
	if(interactive==1){
	    for(int x=1;x<max_x+1;x++){;
		for(int y=1;y<max_y+1;y++){
		    rooster[y][x]=1;
		}
	    }
	    addMouseListener(
		new MouseAdapter(){
		    public void mousePressed(MouseEvent e){
			dx = e.getX() / hokje_x;
			dy = e.getY() / hokje_y;
			if(dx<max_x+1 && dy<max_y+1 && dx>0 && dy>0){
			    rooster[dy][dx] = -1 * rooster[dy][dx];
			    //System.out.println("rooster[dy][dx]="+rooster[dy][dx]+" dx="+dx+" dy="+dy);
			    repaint();
			}
		    }
		}
	    );
	}
    }

   public void paint(Graphics g){
      tekening.setColor(Color.white);
      tekening.fillRect(0,0,xsize,ysize);

      for(int t1 = 0;t1 < max_x+2;t1 ++){
         for(int t2 = 0;t2 < max_y+2;t2 ++){
	    if(rooster[t2][t1]!=0){
		if(rooster[t2][t1] == 1){tekening.setColor(new Color(R1,G1,B1));}else{tekening.setColor(new Color(R2,G2,B2));}
		tekening.fill3DRect(hokje_x*t1,hokje_y*t2,hokje_x,hokje_y,true);
            }
	 }
      }
      g.drawImage(plaatje,0,0,this);
   }

   public void start(){
      if(thread == null){
         thread = new Thread(this);
         thread.start();
      }
   }

   public void stop(){
      thread =  null;
   }

   public void run(){
      while(thread != null){
         try{
            Thread.sleep(100);
         }
         catch (InterruptedException e){
         }
      }
   }

   public void update( Graphics g ){
      paint( g ) ;
   }
   
   public String ReadApplet(){
	// x==1
	double hy=1.000*hokje_y;
	double hx=1.000*hokje_x;
	double factor=hy/hx;
	//double hy=Double.valueOf(hokje_y);
	//double hx=Double.valueOf(hokje_x);
	//double factor=hy/hx;
        int changed=0;int original=0;int total=0;
        // rooster[y][x]=0 white border
        // rooster[y][x]=-1 clicked
        // rooster[y][x]=1  unchanged
        for(int t1 = 0;t1 < max_x+2;t1 ++){
    	    for(int t2 = 0;t2 < max_y+2;t2 ++){
		if(rooster[t2][t1] == -1){ changed++; total++;  }
		if(rooster[t2][t1] ==  1){ original++; total++; }
    	    }
        }

        double border[][]=new double[max_y+4][2*max_x+4];
        int c1;int c2;double t=0;
        for( c1 = 1; c1 < max_x+1 ;c1++){
    	    for( c2 =1; c2 < max_y+1 ;c2++){
		if(rooster[c2][c1] == -1 ){t=0;
		    if((rooster[c2][c1-1] != -1) && (rooster[c2][c1+1] != -1) ){t=t+factor*2;}else{if( (rooster[c2][c1-1] != -1) || (rooster[c2][c1+1] != -1) ){t=t+factor;}}
		    if( (rooster[c2-1][c1] != -1) && (rooster[c2+1][c1] != -1) ){t=t+2;}else{if( (rooster[c2-1][c1] != -1) || (rooster[c2+1][c1] != -1) ){t=t+1;}}
		    border[c2][c1]=t;
		}
	    }
	}
	double cnt=0;
	for( c1=1 ; c1<max_x+1 ; c1++ ){
	    for( c2=1 ; c2<max_y+1 ; c2++ ){
		cnt=cnt+border[c2][c1];
	    }
	}
        String S=total+","+original+","+changed+","+cnt;
        return S;
    }
}
