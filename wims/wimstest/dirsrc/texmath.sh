#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";

$wims_home/src/wims test $wims_dirtest texmath 'add2 add2p add3'
$wims_home/src/wims test $wims_dirtest texmath 'sign doublesign'
$wims_home/src/wims test $wims_dirtest texmath 'mul div muldiv muldivp'
$wims_home/src/wims test $wims_dirtest texmath 'exp ind num'
$wims_home/src/wims test $wims_dirtest texmath 'mixed1 mixed2 mixed3 mixed4 mixed5'
$wims_home/src/wims test $wims_dirtest texmath 'stupid warn1ok warn1'
