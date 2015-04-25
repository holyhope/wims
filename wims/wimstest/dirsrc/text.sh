#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";

test="line item word1 word2
accent1 accent2 accent3
parent1 parent2
position1 position2 position3 position4
detag1
select1 select2
getopt1 getopt2 getopt3 getopt4 getopt5 getopt6
nonempty1 nonempty2 nonempty3
declosing1 declosing2 declosing3
testline1 testline2 testline3 testline4 testline5 testline6 testline testline8"

for a in $test; do
 $wims_home/src/wims test $wims_dirtest text $a
done;
