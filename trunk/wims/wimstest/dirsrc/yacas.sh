#! /bin/sh

wims_home=`pwd`;
export tmp_dir=$wims_home/wimstest

#export wims_exec_parm="about"
#$wims_home/src/Interfaces/yacas
#echo "\n"

export wims_exec_parm="2^17-1"
$wims_home/public_html/bin/yacas
