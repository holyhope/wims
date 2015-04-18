#! /bin/sh

wims_home=`pwd`;
export tmp_dir=$wims_home/wimstest
export m2_command="/Applications/Macaulay2-1.7/bin/m2"
#export wims_exec_parm="about"
#$wims_home/src/Interfaces/m2
#echo "\n"

export wims_exec_parm="2^17-1"
$wims_home/src/Interfaces/m2
