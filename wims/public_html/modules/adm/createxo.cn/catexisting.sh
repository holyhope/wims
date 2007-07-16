#! /bin/sh
# We use shell script to output oef source file, because
# otherwise the $ sign will be substituted.

if [ -z "$w_catmodule" ]; then
 classd=$w_wims_home/log/classes/$w_wims_class
 oefname=$classd/src/$wims_exec_parm.oef
else
 moduled=modules/$w_catmodule
 test1=`grep -E '^[[:blank:]]*category[[:blank:]]*=.*oef' $moduled/INDEX`
 test2=`grep -E '^[[:blank:]]*copyright[[:blank:]]*=.*COPYING' $moduled/INDEX`
 if [ -z "$test1" ] || [ -z "$test2" ]; then
  rm -f $w_wims_home/$w_wims_sesdir/user-deposit 2>/dev/null
  exit
 fi
 oefname=$moduled/src/$wims_exec_parm.oef
fi
logd=$w_wims_home/log/classes/$w_wims_class/src/images
sesd=$w_wims_home/$w_wims_sesdir

if [ -f $oefname ]; then 
 cat $oefname >$sesd/user-deposit
 cat $oefname >$sesd/submit.oef
 if [ -d $logd/$wims_exec_parm ]; then
  rm -fr $sesd/getfile/oefimg 2>/dev/null
  mkdir -p $sesd/getfile/oefimg 2>/dev/null
  . $w_wims_home/bin/dircptest
  $dircp $logd/$wims_exec_parm/* $sesd/getfile/oefimg 2>/dev/null
 fi
 echo yes
else
 rm -f $w_wims_home/$w_wims_sesdir/user-deposit 2>/dev/null
fi

