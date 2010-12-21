#!/bin/sh

ant -v clean
ant -v

if [ -e "dist/sinus.jar" ] ; then
    #mozilla file://`pwd`/1.html
    appletviewer 1.html & 
else
    echo "build failed"
    tail log.txt
    read whatever
fi

