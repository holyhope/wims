#! /bin/sh

cd ..
test=`find $wims_exec_parm -perm +11 -type f 2>/dev/null | head -1000`
echo "$test" | head -60
if [ ! -z "$test" ]; then chmod og-x $test; fi

