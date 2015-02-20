#! /bin/sh

wims_home=`pwd`;
export pari_ray=" "
export tmp_dir=$wims_home/wimstest

#export wims_exec_parm="about"
#$wims_home/src/Interfaces/pari
#echo "\n"

export wims_exec_parm="2+4"
$wims_home/src/Interfaces/pari
