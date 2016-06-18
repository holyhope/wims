#!/bin/sh
wims_home=`pwd`;
dir=$wims_home/wimstest/flydraw
flydraw=$wims_home/src/Flydraw/flydraw
mkdir -p $dir/tmp

check(){
    cmp --quiet -i 8:8 $dir/tmp/$f.gif $dir/targets/$f.gif
    case "$?" in
	0) echo "OK, test $f passed."
	   ok=$((ok+1))
	   ;;
	1) echo "FAIL: images differ with test $f"
	   nok=$((nok+1))
	   ;;
	2) echo "FAIL: something is wrong with $f, maybe some missing file?"
	   ;;
	*) echo "BAAAD! this should never happen!"
	   exit2
	   ;;
    esac
}

#----------------- INITIALISATIONS ------------------------
ok=0
nok=0

rm -f $dir/tmp/*.gif

#------------------- TESTS ---------------------------------
echo "---------- TESTING FLYDRAW --------------"


list=`ls $dir/src`;
for f in $list; do
 draw_content=`cat $dir/src/$f`
 $flydraw <<@
$draw_content
output $dir/tmp/$f.gif
@
check
done;


#---------------------- SUMMARY -----------------------
echo "------- END OF TEST FOR FLYDRAW ---------"
echo "Tests passed: $ok"
echo "Tests failed: $nok"
echo "-----------------------------------------"

#------------- Return non-zero value if failed --------
if [ "$nok" -gt 0 ]; then
    exit 1
fi

