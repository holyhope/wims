#!/bin/sh
name="VrijeInvulVeld"

htmfile="1.html"

if [ ! -e $htmfile ] ; then
echo "
<html>
<head>test vrije invulveld</head>
<body>
    <script language=\"javascript\" type=\"text/javascript\">                                                                                      
	function READTHIS(){                                                                                                                           
	    var reply=document.applets[0].ReadApplet(1);
	    alert(\"the applet will send to wims:\n\"+reply);
	}                                                                                                                                         
    </script>                                                                                                                                  
    <center>
    <applet code=\"VrijeInvulVeld.class\" archive=\"VrijeInvulVeld.jar\" width=\"640\" height=\"480\">
	<param name=\"xsize\" value=\"300\">
	<param name=\"ysize\" value=\"300\">
	<param name=\"bgcolor\" value=\"255,255,255\">
	<param name=\"textcolor\" value=\"250,0,0\">
	<param name=\"drawcolor\" value=\"30,120,10\">
	<param name=\"penthickness\" value=\"2\">
	<param name=\"penfontsize\" value=\"18\">
	<param name=\"penfontfamily\" value=\"Helvetica\">
	<param name=\"penfontstyle\" value=\"bold\">
	<param name=\"language\" value=\"nl\">
	<param name=\"text\" value=\"yes\"> <!-- if 0/no no text -->
	<param name=\"line\" value=\"yes\"> <!-- if 0/no no lines -->
	<param name=\"rect\" value=\"0\"> <!-- if 0/no no rec -->
	<param name=\"ellipse\" value=\"0\"> <!-- if 0/no no ellipse -->
	<param name=\"arrow\" value=\"0\"> <!-- if 0/no no arrows -->
	<param name=\"grid\" value=\"yes\"> <!-- will produce a grid -->
	<param name=\"textlines\" value=\"10\"> <!-- number of lines in the applet: strings are bound to these lines leave blank or remove parma-tag to revert to original behaviour of the drawing applet -->
	<param name=\"textalign\" value=\"vertical\"> <!-- or horizontal probability tree orientation --> 
    </applet>
    <input type=\"button\" name=\".....TEST......\" value=\".....TEST.....\" onclick=\"javascript:READTHIS();\">
</body>
</html>
" > $htmfile

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
    jar cvf $name.jar *.class
    echo "
    Making source archive
    "
    rm -v *.class
    tar cvzf $name.src.tar.gz $name.java make.sh
    echo "
    appletviewer
    
    "
    mozilla file://`pwd`/1.html
#    appletviewer 1.html
fi


