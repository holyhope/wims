#!/bin/sh

rm -rf ~/.java
rm *.class
javac -source 1.4 -target 1.4 *.java
jar cvf WClock.jar *.class
tar cvzf WClock.src.tar.gz *.java test.html make.sh

mozilla file://`pwd`/test.html
#appletviewer test.html