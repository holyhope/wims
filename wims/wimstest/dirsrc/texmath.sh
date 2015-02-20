#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";

$wims_home/src/wims test $wims_dirtest texmath 'add2 add2p add3'
$wims_home/src/wims test $wims_dirtest texmath 'sign doublesign'
$wims_home/src/wims test $wims_dirtest texmath 'mul div divp muldiv muldivp'
$wims_home/src/wims test $wims_dirtest texmath 'exp ind num num2 sci'
$wims_home/src/wims test $wims_dirtest texmath 'matrix matrix2'
$wims_home/src/wims test $wims_dirtest texmath 'stars names names2 sums'
$wims_home/src/wims test $wims_dirtest texmath 'relations relationempty relationempty2 relationempty3'
$wims_home/src/wims test $wims_dirtest texmath 'mixed1 mixed2 mixed3 mixed4 mixed5'
$wims_home/src/wims test $wims_dirtest texmath 'par stupid warn1ok warn1'



exit

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%        Remarks           %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Parentheses : some useless parentheses are removed, not all (multiple parentheses are "halved").

Matrices : matrix of size 1 is not treated as a matrix (see par)

Maxima constants : not interpreted, hence some results may be false (names2 gives atan(1)=1/4) if void constant is replaced by 1.

Spaces : the number 1 is often treated differently than other ; this
difference makes a difference in the space characters for instance
between 1+x and 2+x


Braces : as writen in techdoc, the expression should be a
"machine-understandable mathematical expression". In particular if
braces appear, no treatment is done (see warn1)

Stars : double star is power ; a sole star in exponent remains as is.