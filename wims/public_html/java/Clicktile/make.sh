#!/bin/sh
rm -rf ~/.java                                                                                                                             
rm *.class
javac -verbose -source 1.4 -target 1.4 *.java
jar cvf Clicktile.jar *.class

#appletviewer 1.html
mozilla file://`pwd`/1.html
