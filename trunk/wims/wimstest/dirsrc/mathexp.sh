#! /bin/sh

wims_home=`pwd`;

export wims_exec_parm="extract inequality >
< x^2 >= 0"

$wims_home/public_html/bin/mathexp
