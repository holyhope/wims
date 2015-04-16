#! /bin/sh

wims_home=`pwd`;
export w_curvecomp_1="0,92,1,92,2,92,3,92"
export w_curvecomp_2="46,41,48,41,50,45"
export w_curvecomp_tolerance="40"
export w_curvecomp_xrange="0,208"
export w_curvecomp_yrange="0,220"

$wims_home/src/Misc/curvecomp
