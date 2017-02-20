#! /bin/sh

cd $wims_server_base/..
dir=`pwd`
for f in $wims_exec_parm
do
 test=`stat -Lt $f | cut -d' ' -f4 | grep '..[048c]0'`
 if [ -e $f ] && [ -z "$test" ]; then
  chmod og-rwx $f
  echo $dir/$f
 fi
done

