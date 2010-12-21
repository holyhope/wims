#!/bin/sh

name="Plinko-II"
#gifs="ok.gif nok.gif"
htmfile="1.html"
rm *.class
rm -rf ~/.java
javac -verbose -source 1.4 -target 1.4 *.java

jar cvf $name.jar *.class $gifs
tar cvzf $name.src.tar.gz  $gifs *.java *.html make.sh README
mozilla file://`pwd`/1.html
#appletviewer 1.html
