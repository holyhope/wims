#! /bin/sh
### execute from wims_home

wims_home=`pwd`;
wims_dirsrc="$wims_home/wimstest/dirsrc";
wims_tmp="$wims_home/wimstest/tmp";
wims_res="$wims_home/wimstest/dirres";
mkdir -p $wims_home/wimstest/tmp

if [ "$1" ] ; then
  for a in $(seq $#) ; do opt=$1;
    $wims_dirsrc/$opt.sh > $wims_tmp/$opt;
    echo $opt:
    shift
  done;
else
  for i in `ls $wims_dirsrc/*.sh`; do
   j=`basename $i .sh`; echo "Testing $j... \c"
   $i > $wims_tmp/$j 2>&1
   if ! cmp $wims_tmp/$j $wims_res/$j; then
     diff -c $wims_res/$j $wims_tmp/$j > $wims_tmp/$j.diff;
     echo "BUG"
   else
     echo "OK"
   fi
  done
fi ;
