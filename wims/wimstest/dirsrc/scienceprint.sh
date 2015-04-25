#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";

test="901234567890123,-1,0
9012345678901234,-1,0
901234567890123*10^70,-1,0
9012345678901234*10^70,-1,0"

for a in $test; do
  $wims_home/src/Misc/scienceprint/scienceprint $a;
done;
