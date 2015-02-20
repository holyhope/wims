#! /bin/sh
### execute from wims_home

wims_home=`pwd`;
wims_dirsrc="$wims_home/wimstest/dirsrc";
wims_tmp="$wims_home/wimstest/tmp";
mkdir -p $wims_home/wimstest/tmp

if [ "$1" ] ; then
  for a in $(seq $#) ; do opt=$1;
    $wims_dirsrc/$opt.sh > $wims_tmp/$opt;
    echo $opt:
    shift
  done;
else
  for i in `ls $wims_dirsrc/*.sh`; do
   j=`basename $i .sh`; echo $j
   $i > $wims_tmp/$j
  done
fi ;
