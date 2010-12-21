#!/bin/sh

name="GetallenLijn"
htmfile="1.html"

if [ ! -e $htmfile ] ; then
echo "
<html>
<head></head>
<body>
    <script language=\"javascript\" type=\"text/javascript\">                                                                                      
	function READTHIS(){                                                                                                                           
	    var input=document.applets[0].ReadApplet();
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
    <applet code=\"$name.class\"  archive=\"$name.jar\" width=\"600\" height=\"240\">
	<param name=\"xmax\" value=\"150\">
	<param name=\"fontsize\" value=\"36\">
	<param name=\"join\" value=\"yes\"> <!-- append arrows? if \"no\" all arrows start in 0 -->
	<param name=\"exercise\" value=\"\"><!-- could be something like: + 1 -3*-5 + -4= -->
	<param name=\"language\" value=\"nl\">
	<param name=\"pencolor\" value=\"10,3,2\"> <!-- input foreground color -->
	<param name=\"bgcolor1\" value=\"200,250,255\"> <!-- input background color -->
	<param name=\"bgcolor2\" value=\"245,255,255\"> <!-- canvas background color -->
    </applet>
    <input type=\"button\" name=\".....TEST......\" value=\".....TEST.....\" onclick=\"javascript:READTHIS();\">
</body>
</html>" > $htmfile

fi

rm *.class 2>/dev/null
rm -rf ~/.java 2>/dev/null 

javac -verbose -source 1.4 -target 1.4 $name.java

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
    tar cvzf $name.src.tar.gz $name.java make.sh org/javia/arity/*.java
    echo "
    appletviewer
    
    "
#    mozilla file://`pwd`/1.html
    appletviewer 1.html
fi


