#!/bin/sh

name="Rekenmachien"
htmfile="1.html"

if [ ! -e $htmfile ] ; then
echo "
<html>
<head></head>
<body>
    <script language=\"javascript\" type=\"text/javascript\">                                                                                      
	function READTHIS(){                                                                                                                           
	    var input=document.getElementById(\"calculator\").ReadApplet();
	    if(input.indexOf(\"error\")!=-1){
		alert(input);
	    }
	    else
	    {                                                                               
		alert(\"the applet will send:\n\"+input);
	    }
	}                                                                                                                                         
    </script>                                                                                                                                  
    <center>
    <applet id=\"calculator\" code=\"$name.class\"  archive=\"$name.jar\" width=\"120\" height=\"60\">
	<!-- defaults should be OK ... but if needed override with these params -->
	<param name=\"frame_xsize\" value=\"300\"> <!-- xsize of popup frame -->
	<param name=\"frame_ysize\" value=\"240\"> <!-- ysize of popup frame -->
	<param name=\"location_x\" value=\"300\"> <!-- x location of popup frame -->
	<param name=\"location_y\" value=\"300\"> <!-- y location of popup frame -->
	<param name=\"decimals\" value=\"6\"> <!-- precision: number of decimals -->
	<param name=\"fontsize1\" value=\"10\"> <!-- input fontsize -->
	<param name=\"fontsize2\" value=\"10\"> <!-- output / remarks fontsize -->
	<param name=\"fontsize3\" value=\"16\"> <!-- popup frame fontsize -->
	<param name=\"language\" value=\"en\"> <!-- en,nl,fr,de -->
	<param name=\"pencolor1\" value=\"10,3,2\"> <!-- input foreground color -->
	<param name=\"pencolor2\" value=\"10,3,2\"> <!-- input foreground color -->
	<param name=\"bgcolor1\" value=\"200,250,255\"> <!-- input background color -->
	<param name=\"bgcolor2\" value=\"245,255,255\"> <!-- canvas background color -->
    </applet>
    <input type=\"button\" name=\"Send\" value=\"Send\" onclick=\"javascript:READTHIS();\">
</body>
</html>" > $htmfile

fi

rm *.class 2>/dev/null
rm -rf ~/.java 2>/dev/null 

javac -verbose -source 1.4 -target 1.4 *.java

if [ ! -e "$name.class" ] ; then
    echo "Hmmm...compilation went wrong ?!"
    read anything
else
    echo "
    Making jar file
    
    "
    jar cvf $name.jar *.class org/javia/arity/*.class
    echo "
    Making source archive
    "
    tar cvzf $name.src.tar.gz *.java make.sh org/javia/arity/*.java 1.html
    echo "
    appletviewer
    
    "
#firefox file://`pwd`/1.html
   appletviewer 1.html
fi


