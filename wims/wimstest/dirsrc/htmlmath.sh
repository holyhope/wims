#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";

export wims_rawmath_variables=T,x
export wims_rawmath_functions=toto
export wims_warn_rawmath=
export htmlmath_gtlt=
export force_mathml=


test="t1 t2 t3 t4
t5 t6 t7"

for a in $test; do
 $wims_home/src/wims test $wims_dirtest htmlmath $a
done;
