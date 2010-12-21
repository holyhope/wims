#!/bin/sh

if [ ! -e 1.html ] ; then
echo "<html>
<head></head>
    <body>
    	<applet width = \"640\" height = \"480\" codebase=\".\" archive=\"Plot.jar\" code=\"ptolemy.plot.PlotApplet\"> 
	    <param name = \"progressbar\" value = \"true\">
            <param name = \"scriptable\" value = \"false\">
	    <param name = \"background\" value = \"#ffffff\"> 
	    <param name = \"name\" value = \"PlotApplet\">
	    <param name=\"title\" value=\"in the titel, htmlsyntax like &quot; &amp; &auml; &rarr; &pi; &quot; , is allowed\">
	    <param name=\"xlabel\" value=\"x-as label\">
	    <param name=\"ylabel\" value=\"y-as label\">
	    <param name=\"grid\" value=\"on\">
	    <param name=\"color\" value=\"on\">
	    <param name=\"xmin\" value=\"0\">
	    <param name=\"xmax\" value=\"6\">
	    <param name=\"ymax\" value=\"5\">
	    <param name=\"ymin\" value=\"-5\">
	    <param name=\"color\" value=\"on\">
	    <param name=\"smooth\" value=\"0\">
	    <param name=\"function\" value=\"tan(x),sin(x),cos(x),2*cos(x),cos(2*x),1/cos(x)\">                                                                                              
	    <param name=\"names\" value=\"curve 1:tan(x),curve 2: sin(x),curve 3:cos(x),2*cos(x),cos(2*x),1/cos(x)\">
	    <param name=\"plotsteps\" value=\"100\">
	    <param name=\"normalexponent\" value=\"yes\"> 		
	</applet>
	<br>
	data loaded by function param:
	&lt;param name=\"function\" value=\"tan(x),sin(x),cos(x),2*cos(x),cos(2*x),1/cos(x)\"&gt;
	<p>Applet htmlcode:<br>
	<tt>
	&lt;applet width = \"640\" height = \"480\" codebase=\".\" archive=\"Plot.jar\" code=\"ptolemy.plot.PlotApplet\"&gt;<br> 
	    &lt;param name = \"progressbar\" value = \"true\"&gt;<br>
            &lt;param name = \"scriptable\" value = \"false\"&gt;<br>
	    &lt;param name = \"background\" value = \"#ffffff\"&gt;<br> 
	    &lt;param name = \"name\" value = \"PlotApplet\"&gt;<br>
	    &lt;param name=\"title\" value=\"titel htmlsyntax: &amp; pi ... &pi;\"&gt;<br>
	    &lt;param name=\"xlabel\" value=\"x-as label\"&gt;<br>
	    &lt;param name=\"ylabel\" value=\"y-as label\"&gt;<br>
	    &lt;param name=\"grid\" value=\"on\"&gt;<br>
	    &lt;param name=\"color\" value=\"on\"&gt;<br>
	    &lt;param name=\"xmin\" value=\"0\"&gt;<br>
	    &lt;param name=\"xmax\" value=\"6\"&gt;<br>
	    &lt;param name=\"ymax\" value=\"5\"&gt;<br>
	    &lt;param name=\"ymin\" value=\"-5\"&gt;<br>
	    &lt;param name=\"color\" value=\"on\"&gt;<br>
	    &lt;param name=\"smooth\" value=\"0\"&gt;<br>
	    &lt;param name=\"function\" value=\"tan(x),sin(x),cos(x),2*cos(x),cos(2*x),1/cos(x)\"&gt;<br>                                                                                              
	    &lt;param name=\"names\" value=\"curve 1:tan(x),curve 2: sin(x),curve 3:cos(x),2*cos(x),cos(2*x),1/cos(x)\"&gt;<br>
	    &lt;param name=\"plotsteps\" value=\"100\"&gt;<br>
	    &lt;param name=\"normalexponent\" value=\"yes\"&gt;&lt;!-- used for logscales:  if set 1.0&times;10<sup>3</sup> in stead of 1.0E3 --&gt;<br> 		
	&lt;/applet&gt;<br> 
	</tt>
	Other means of loading data:<br>
	&lt;param name=\"file\" value=\"http://localhost/wims/wims.cgi?session=$session&cmd=getfile&special_parm=mydata\"&gt;<br><br>
	example of a single line datafile:<br>
	\"TitleText: Software Downloads;XRange: 0,10;YRange: 0,10000;# Manually specify X ticks;# Note that the 0 and 10 point result in clipping of the rectangles.;XTicks: 1993 0, 1994 1, 1995 2, 1996 3, 1997 4, 1998 5, 1999 6, 2000 7, 2001 8, 2002 9, 2003 10;XLabel: Year;YLabel: Downloads;Marks: none;Lines: off;# Width and offset of bars;Bars: 0.5, 0.2;NumSets: 3;;DataSet: program a;0, 100;1, 300;2, 600;3, 1000;4, 4000;5, 6000;6, 3000;7, 1000;8, 400;9, 0;10, 0;;DataSet: program b;0, 0;1, 0;2, 50;3, 100;4, 800;5, 400;6, 1000;7, 5000;8, 2000;9, 300;10, 0;;DataSet: program c;0, 0;1, 0;2, 0;3, 10;4, 100;5, 400;6, 2000;7, 5000;8, 9000;9, 7000;10, 1000\"
<p>
    Or by direct file in a directory
	<tt>?&lt;param name=\"dataurl\" value=\"../data/thisdata.txt\"&gt;</tt><br>
	An example of a multiline datafile:<br>
<tt>
TitleText: Software Downloads<br>
XRange: 0,10<br>
YRange: 0,10000<br>
# Manually specify X ticks<br>
# Note that the 0 and 10 point result in clipping of the rectangles.<br>
XTicks: 1993 0, 1994 1, 1995 2, 1996 3, 1997 4, 1998 5, 1999 6, 2000 7, 2001 8, 2002 9, 2003 10<br>
XLabel: Year<br>
YLabel: Downloads<br>
Marks: none<br>
Lines: off<br>
# Width and offset of bars<br>
Bars: 0.5, 0.2<br>
NumSets: 3<br>
<br>
DataSet: program a<br>
0, 100<br>
1, 300<br>
2, 600<br>
3, 1000<br>
4, 4000<br>
5, 6000<br>
6, 3000<br>
7, 1000<br>
8, 400<br>
9, 0<br>
10, 0<br>
<br>
DataSet: program b<br>
0, 0<br>
1, 0<br>
2, 50<br>
3, 100<br>
4, 800<br>
5, 400<br>
6, 1000<br>
7, 5000<br>
8, 2000<br>
9, 300<br>
10, 0<br>
<br>
DataSet: program c<br>
0, 0<br>
1, 0<br>
2, 0<br>
3, 10<br>
4, 100<br>
5, 400<br>
6, 2000<br>
7, 5000<br>
8, 9000<br>
9, 7000<br>
10, 1000<br>
</tt>
    </body>
</html>
" >> 1.html
fi

#find ./build -type f -name "*.class" -exec rm "{}" ";" 
rm Plot.jar*
ant -v jar -l log.txt
rm -rf ~/.java
if [ -e "Plot.jar" ] ; then
    mozilla file://`pwd`/1.html
    tar cvzf Plot.src.tar.gz ./ptolemy build.xml make.sh 1.html ./examples
    #appletviewer ./1.html
else
    echo "build failed"
    tail -f -n 30 log.txt
fi
