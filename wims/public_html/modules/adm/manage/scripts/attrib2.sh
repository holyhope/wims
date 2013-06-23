#! /bin/sh

cd ..
test=`find $wims_exec_parm -perm +22 \! -type l 2>/dev/null | head -1000`
test2=`find $w_nowrite2 -maxdepth 0 -perm +22 \! -type l 2>/dev/null | head -1000`
echo "$test
$test2" | head -60
if [ ! -z "$test$test2" ]; then chmod og-w $test $test2; fi

