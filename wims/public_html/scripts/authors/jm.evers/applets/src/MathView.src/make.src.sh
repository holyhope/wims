#!/bin/sh
find ./build -type f -name "*.class" -exec rm "{}" ";"
cd ..   
tar cvzf MathView.src.tar.gz MathView.src
mv MathView.src.tar.gz MathView.src