#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";

test="var1 var2
bound1 bound2 bound3 bound4 bound5 bound6 bound7"

for a in $test; do
 $wims_home/src/wims test $wims_dirtest execution $a
done;
