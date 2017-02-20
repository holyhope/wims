#! /bin/sh

wims_home=`pwd`;

export w_huffman_radix=4
export wims_exec_parm="0.16, 0.39, 0.55"
$wims_home/src/Misc/huffman
