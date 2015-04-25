#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";

test="test1 test2 test3 test4 test5
test11 test12 test13 test14 test15
test21 test22 test23 test24 test25
test31 test32 test33"

for a in $test; do
 $wims_home/src/wims test $wims_dirtest sort $a
done;
