#! /bin/sh

wims_home=`pwd`;
export pari_ray=" "
export tmp_dir=$wims_home/wimstest
export pari_command="gp -f -q -p 150000"
#export wims_exec_parm="about"
#$wims_home/src/Interfaces/pari
#echo "\n"

export wims_exec_parm="2^17-1"
$wims_home/src/Interfaces/pari
#there is a seed in pari.c so change each time
#export wims_exec_parm="random\(500)"
#$wims_home/src/Interfaces/pari
#export wims_exec_parm="parirandom(10000)"
#$wims_home/src/Interfaces/pari
