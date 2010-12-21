#!/bin/sh

rm *.class
rm *.jar
javac  *.java

if [ -e ChemInputApplet.class  ] &&  [ -e ChemInputFrame.class  ] &&  [ -e ChemInputCanvas.class  ] ; then      
    jar cvf ChemInput.jar *.class
#    ./jarsign.sh
    rm -rf ~/.java
    tar cvzf ChemInput.src.tar.gz test.html *.java make.sh jarsign.sh
    appletviewer test.html
#    mozilla file:///`pwd`/test.html
    rm *.class
else
    echo "trouble"
    read HMMM
fi