#! /bin/sh

basedir=`pwd`
sessiond=$w_wims_home/$w_wims_sesdir
Logd=$w_wims_home/log/classes/$w_wims_class
logd=$Logd/src
classb=$basedir/modules/classes
classd=$classb/$w_lang
oefname=$sessiond/submit.oef

if [ ! -d $classd ]; then exit; fi

namesuffix=
if [ ! -z "$w_existing" ]; then 
 namebase=$w_existing
else
 if [ -f $logd/$w_oef_fname.oef ]; then
  if diff -b -B -q $oefname $logd/$w_oef_fname.oef >/dev/null; then
   echo fail already
   exit
  fi
  max_suffix=20
  namesuffix=2
  while [ -f $logd/$w_oef_fname$namesuffix.oef -a $namesuffix -lt $max_suffix ]; 
  do
   if diff -b -B -q $oefname $logd/$w_oef_fname$namesuffix.oef >/dev/null; then
    echo fail already
    exit
   fi
   namesuffix=$(($namesuffix+1))
  done
  if [ $namesuffix -gt $(($max_suffix-1)) ]; then
   echo fail name_exhaust
   exit
  fi
 fi
 namebase=$w_oef_fname$namesuffix
fi
 
if [ ! -d "$logd" ]; then
  mkdir $logd >/dev/null
fi
cp -f $oefname $logd/$namebase.oef >/dev/null
cd $classd
msg=`src2def oef`

if [ -d $sessiond/getfile/oefimg ]; then
 mkdir -p $logd/images/$namebase
 rm -f $logd/images/$namebase/* 2>/dev/null
 cp -pPR $sessiond/getfile/oefimg/* $logd/images/$namebase >/dev/null
fi

if [ -f $Logd/def/$namebase.def ]; then 
 echo success $namebase
else
 echo fail unknown
fi
echo "$msg"

