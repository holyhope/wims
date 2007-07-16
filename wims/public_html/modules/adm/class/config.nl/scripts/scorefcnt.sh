#! /bin/sh

if [ -z "$wims_exec_parm" ]; then
 cd $w_wims_home/log/classes/$w_wims_class
else
 cd $w_wims_home/$wims_exec_parm
fi

rm -f score/supervisor >/dev/null
m=`cat score/* 2>/dev/null | grep -c .`
n=`cat noscore/* 2>/dev/null | grep -c .`
echo "$m $n"

