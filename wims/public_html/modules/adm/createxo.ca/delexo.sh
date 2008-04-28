#! /bin/sh
# We use shell script to output oef source file, because
# otherwise the $ sign will be substituted.


logd=$w_wims_home/log/classes/$w_wims_class/src
oefname=$logd/$wims_exec_parm.oef

if [ ! -f "$oefname" ]; then exit; fi

cat $oefname
rm -f $oefname >/dev/null
rm -fR $oefname $logd/images/$wims_exec_parm >/dev/null

cd modules/classes/$w_lang
src2def oef

