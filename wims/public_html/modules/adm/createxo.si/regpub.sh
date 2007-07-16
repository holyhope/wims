#! /bin/sh

sessiond=$w_wims_home/$w_wims_sesdir
pubd=modules/incoming
oefname=$sessiond/submit.oef

namesuffix=
max_suffix=20
if [ -f $pubd/src/$w_oef_fname.oef ]; then
 if diff -b -B -q $oefname $pubd/src/$w_oef_fname.oef >/dev/null; then
  echo fail already
  exit
 fi
 namesuffix=2
 while [ -f $pubd/src/$w_oef_fname$namesuffix.oef -a $namesuffix -lt $max_suffix ]; 
 do
  if diff -b -B -q $oefname $pubd/src/$w_oef_fname$namesuffix.oef >/dev/null; then
   echo fail already
   exit
  fi
  namesuffix=$(($namesuffix+1))
 done
 if [ "$namesuffix" -gt $(($max_suffix-1)) ]; then
  echo fail name_exhaustpub
  exit
 fi
fi
namebase=$w_oef_fname$namesuffix
 
cp -f $oefname $pubd/src/$namebase.oef
cd $pubd
msg=`src2def oef`

if [ -f def/$namebase.def ]; then 
 echo success $namebase
else
 echo fail unknown
fi

echo "$msg"
