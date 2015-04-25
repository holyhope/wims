#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";

test="test"

for a in $test; do
 $wims_home/src/wims test $wims_dirtest hex $a
done;
