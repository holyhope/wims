#! /bin/sh

wims_home=`pwd`;
export tmp_dir=$wims_home/wimstest
export gap_command="/Applications/gap4r7/bin/gap.sh -T -m 64M -L workspace"
#export wims_exec_parm="about"
#$wims_home/src/Interfaces/gap
#echo "\n"

export wims_exec_parm="2^17-1"
$wims_home/src/Interfaces/gap
