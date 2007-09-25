#! /bin/sh

cd ..
testd=`find $wims_exec_parm -follow -type d \! -perm -11 2>/dev/null | head -100`
testf=`find $w_wexec2 -follow -type f \! -perm -11 2>/dev/null | head -100`
test="$testd $testf"
echo "$test" | head -60
if [ ! -z "$testd$testf" ]; then chmod a+rx $test; fi

