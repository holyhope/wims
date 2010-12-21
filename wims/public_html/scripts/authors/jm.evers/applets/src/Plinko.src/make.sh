#!/bin/sh

# should run on Mac_OSX ?

name="Plinko"
htmfile="1.html"

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
    jar cvf $name.jar *.class sounds
    echo "
    Making source archive
    
    "
    tar cvzf $name.src.tar.gz  sounds *.java *.html make.sh README
    echo "
    appletviewer
    
    "
    #mozilla file://`pwd`/1.html
    appletviewer 1.html
fi