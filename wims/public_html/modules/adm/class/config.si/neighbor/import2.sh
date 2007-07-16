#! /bin/sh
#
# Recense new resources on the neighbor class.
#
# Output line: resource_type resource_name type
# type=1: new type=2: exist but different

mdir=`pwd`

nei=$w_wims_home/log/classes/$w_nei
cd $w_wims_home/log/classes/$w_wims_class
cldir=`pwd`
cd $nei
ndir=`pwd`
cd $cldir

if [ $w_itype = motd ]; then
 cp $nei/.motd .
 echo success
 exit
fi

if [ $w_itype = exo ]; then
 mkdir -p src def
 cp $nei/src/$w_iname src
 exoroot=`echo $w_iname | sed 's/\.oef$//'`
 if [ -d $nei/src/images/$exoroot ]; then
  mkdir -p src/images
  cp -R $nei/src/images/$exoroot src/images
 fi
 cd $cldir
 msg=`src2def oef`
 echo success
 echo "$msg"
 exit
fi

if [ $w_itype = sheet ]; then
 cp $nei/sheets/.sheet$w_iname sheets/.sheet$w_replace
 echo success
 exit
fi

if [ $w_itype = exam ]; then
 cp $nei/exams/.exam$w_iname exams/.exam$w_replace
 echo success
 exit
fi

if [ $w_itype = doc ]; then
 rm -fR doc/c$w_replace 2>/dev/null
 mkdir -p doc >/dev/null
 cp -R $nei/doc/c$w_iname doc/c$w_replace
 echo success
 exit
fi

