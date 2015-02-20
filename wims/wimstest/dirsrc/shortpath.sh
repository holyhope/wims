#! /bin/sh

wims_home=`pwd`;

test="1,3
5,1
3,4
1,1
3,1
4,5"

export wims_exec_parm=$test
$wims_home/src/Misc/shortpath
