#!/bin/sh


if [ ! -e test.html ] ; then

echo "
<html>
 <body>
    <script type=\"text/javascript\">
	function ReadThis1(){
	    reply = document.getElementById('FlyApplet').ReadApplet();
	    alert(\"answer is a list of coordinates \n\"+reply);
	}    
	function ReadThis2(){
	    reply = document.getElementById('Input').ReadApplet();
	    alert(\"input applet:\n\"+reply);
	}    
    </script>
    <table>
	<tr>
	<th>
	<table><tr>
	<td>
	    <applet id=\"FlyApplet\" name=\"FlyApplet\" code=\"FlyApplet.class\" archive=\"FlyApplet.jar\" width=\"500\" height=\"500\">
		<param name=\"file\" value=\"fly.script\">
	    </applet>
	    <center>
		<input type=\"button\" name=\"flyapplet1\" value=\"Read Drawing\" onclick=\"javascript:ReadThis1();\">
	    </center>
	</td>
	<td>
	    <applet id=\"Input\" name=\"Input\" code=\"FlyApplet.class\" archive=\"FlyApplet.jar\" width=\"500\" height=\"500\">
		<param name=\"type\" value=\"circle\">
		<param name=\"bgcolor\" value=\"red\">
		<param name=\"linewidth\" value=\"34\">
		<param name=\"dashed\" value=\"yes\">
		<param name=\"alpha\" value=\"65\">
		<param name=\"pointstyle\" value=\"dot\">
		<param name=\"retry value=\"Effacer\">
		<param name=\"prompt\" value=\"Envoyer\">
		<param name=\"replyurl\" value=\"http://localhost/wims/wims.cgi?\">
	    </applet>
	    <center>
		<input type=\"button\" name=\"flyapplet2\" value=\"Read Drawing\" onclick=\"javascript:ReadThis2();\">
	    </center>
	</td>
	</tr>
	</table>
	</th>
	</tr>
	<tr>
	<td>
<ol>
<li> Syntax ; similar (...) to flydraw <br>
    fobject || dobject coordinate_data,color [optional ,alpha,linewidth]<br>

    fobject : filled object like frect fpoly fellipse fcircle ftriangle<br>
    dobject : dashed draw object like drect dpoly...

<li>  Compatibility with Input.java ex Gang<br>
    Use the normal applet params for Input.java [e.g without the script]<br>
    added params :<br>
    <param name=\"dashed\" value=\"yes\"> yes/no
    <param name=\"linewidth\" value=\"4\"> int
    <param name=\"alpha\" value=\"123\"> [0-255]
    <br><br>
    Or abandon the input_applet_params and let the script produce the background image:<br> 
    userdraw points || line || lines || polygon || vector || circle || semiline || points || curve<br>
    controls yes/no [use the direct reply buttons]<br>
    pointstyle cross/dot : only for userdrawing<br>
<br>
    new: right mousebutton removes parts of drawing<br>
    The result can be read through usual direct contact with wims.cgi<br>
    or via Javascript using ReadApplet() : <br>
    in this case the answers will be in the coordinate system of the drawing<br>
    [xrange/yrange] and always a list x1,y1,x2,y2,x3,y3.....<br>
    
<li> Using the applet as an drawable image [mouse drawinteraction] + coordinates display<br>
    mouse yes<br>
    userdraw points || line || lines || polygon || vector || circle || semiline || points || curve<br>
    coordinates yes/no  or left out<br>
    pointstyle cross || dot<br>
    
    Drawing can be read via Javascript using ReadApplet() :<br> 
    The answers will be in the coordinate system of the drawing<br>
    [xrange/yrange] and always a list x1,y1,x2,y2,x3,y3.....<br>
    
    
<li> Using the applet as an non_user_drawable image with coordinates display<br>
    mouse no<br>
    coordinates yes<br>

<li> Using the applet as a normal Fly image<br>
    mouse no<br>
    coordinates no <br>
    [this is default]<br>


<li> Script syntax [a sort of fly-script]<br>
<pre>
xrange int,int
yrange int,int
linewidth int
transparent color [,alpha]

dline || line x1,y1,x2,y2,color [,alpha,linewidth]
dhline || hline x1,x1,color [,alpha,linewidth]
dvline || vline x1,x1,color [,alpha,linewidth]
darrow || arrow x1,y1,x2,y2,head_factor(0 - 1),color [,alpha,linewidth]  // arrowhead is no good...

dpoly || poly || fpoly x1,y1...x_n,y_n,color [,alpha,linewidth]
drect || rect || frect x1,y1,x3,y3,color [,alpha,linewidth]
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

precision 100 // 2 decimals for reading coords with \"mouse yes\"

debug yes //some info on loading script and other trouble
</pre>
</ol>
</td>
</tr>
    </table>
 </body>
</html>
" > test.html


fi 

rm *.jar
# clean deployment cache !!!
 rm -rf ~/.java
find . -name "*.class" -exec rm -v "{}" ";"
rm -rf build

mkdir -p build/org/javia/arity
mkdir build/atp
cp atp/*gif ./build/atp

javac -target 1.4 -source 1.4 org/javia/arity/*.java
javac -target 1.4 -source 1.4  atp/*.java
javac -target 1.4 -source 1.4   *.java

if [ -e FlyApplet.class ] ; then
    mv *.class ./build
    mv org/javia/arity/*.class ./build/org/javia/arity
    mv atp/*.class ./build/atp
    cd build
    jar cvf FlyApplet.jar *.class org atp
    mv FlyApplet.jar ..
    cd ..
    tar cvzf FlyApplet.src.tar.gz *.java org test.html atp  make.sh fly.script CHANGELOG
    appletviewer test.html
#    mozilla file://`pwd`/test.html
else
    echo "compile error"
    read hmmm
fi



