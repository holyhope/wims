#!/bin/sh
# copy manually the *.properties files to the build-tree...if changed/edited
#

find ./build -type f -name "*.class" -exec rm "{}" ";"                                                                                    
ant -v -l log.txt

cd build/classes
jar cvf MathView.jar *

rm -rf ~/.java
appletviewer 1.html
#mozilla file://`pwd`/1.html
