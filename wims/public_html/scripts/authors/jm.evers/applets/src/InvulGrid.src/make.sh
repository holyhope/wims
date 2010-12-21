#!/bin/sh

rm ~/.java
ant -v

if [ -e dist/InvulGrid.jar ] ; then
    tar cvzf InvulGrid.src.tar.gz src test.html build.xml make.sh
    appletviewer test.html
fi

