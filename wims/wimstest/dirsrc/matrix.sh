#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";

test="test1"

for a in $test; do
 $wims_home/src/wims test $wims_dirtest matrix $a
done;
