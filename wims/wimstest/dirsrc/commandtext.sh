#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";

test="test1 test2 test3 test4
test5 test6 test7 test8
test9 test10 test11 test12
test13 test14"

for a in $test; do
 $wims_home/src/wims test $wims_dirtest commandtext $a
done;
