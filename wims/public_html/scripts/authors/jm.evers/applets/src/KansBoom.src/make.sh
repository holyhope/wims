#!/bin/sh
name="KansBoom"

htmfile="1.html"

if [ ! -e $htmfile ] ; then
echo "
<html>
<head>testing probability tree applet</head>
<body>
    <script language=\"javascript\" type=\"text/javascript\">                                                                                      
	function READTHIS(){                                                                                                                           
	    var applet_data=document.applets[0].ReadApplet(1);

	    <!--- ReadApplet(0) : gives textdata for probability tree -->
	    <!-- ReadApplet(whatever) gives all objects and coordinates -->
	    
	    <!-- catch some errors before sending the data to wims -->
	    <!-- error_1 = unused_line_error -->
	    <!-- error_2 = too_few_items_per_line -->
	    <!-- error_3 = too_many_items_per_line -->
	    <!-- error_4 = inbalance_too_few_lines -->
	    <!-- error_5 = inbalance_too_many_lines -->
	    <!-- error_6 = text_missing -->
	    <!-- error_7 = lines_missing -->
	    
	    
	    comments=new Array();
	    comments=[\"Your answer (drawing) is empty ???\",
	    \"there are lines with no labels or numbers in your probability tree...\",
	    \"there are lines with not enough labels or numbers in your sketch...\",
	    \"there are lines with more than the nessecary labels and/or numbers in your drawing...\",
	    \"there are not enough lines to match the amount of labels/numbers in your answer... \",
	    \"there are too many lines  to match the amount of labels/numbers in your answer... \",
	    \"You have forgotten to write the numbers and names in the tree...\",
	    \"You have forgotten to draw lines in the probability tree...\"];
	    
	    var remark=\"\";
	    <!-- find some errorcode --> 
	    for(p=0;p<8;p++){
		if(applet_data.indexOf(\"error_\"+p) != -1){remark=\"--> \"+comments[p]+\"\n\"+remark;}
	    }
	    
	    if(remark.length!=0){alert(\"I have some comments on Your drawing:\n\"+remark);return;}
	
	    applet_data=applet_data.split(\"@\");
	    var line_analysis=applet_data[1];
	    var reply=applet_data[0];
	    if(line_analysis.length!=0){
		alert(\"this is the information about the drawing\n\"+line_analysis);
	    }
	    alert(\"the applet will send to wims:\n\"+reply);
	}                                                                                                                                         
    </script>                                                                                                                                  
    <center>
    <applet code=\"KansBoom.class\" archive=\"KansBoom.jar\" width=\"640\" height=\"480\">
	<param name=\"xsize\" value=\"640\">
	<param name=\"ysize\" value=\"480\">
	<param name=\"bgcolor\" value=\"200,215,235\">
	<param name=\"textcolor\" value=\"250,115,50\">
	<param name=\"drawcolor\" value=\"50,50,150\">
	<param name=\"penthickness\" value=\"6\">
	<param name=\"penfontsize\" value=\"22\">
	<param name=\"penfontfamily\" value=\"Helvetica\">
	<param name=\"penfontstyle\" value=\"bold\">
	<param name=\"language\" value=\"fr\">
	<param name=\"textlines\" value=\"8\"> <!-- number of lines in the applet: strings are bound to these lines
	leave blank or remove parma-tag to revert to original behaviour of the drawing applet -->
	<param name=\"textalign\" value=\"vertical\"> <!-- probability tree orientation --> 
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
    #appletviewer 1.html
fi


