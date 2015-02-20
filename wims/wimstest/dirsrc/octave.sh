#! /bin/sh

wims_home=`pwd`;

export tmp_dir=$wims_home/wimstest

#export wims_exec_parm="about"
#$wims_home/src/Interfaces/octave
#echo "\n"

export wims_exec_parm="2+4"
$wims_home/src/Interfaces/octave
