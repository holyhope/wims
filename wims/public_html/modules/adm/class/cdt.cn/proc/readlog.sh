#! /bin/sh

echo "<pre>"
if [ "$w_test" = "no" ]; then
 tac $w_wims_home/log/classes/$w_wims_class/cdt/connect.log | cut -d" " -f1,3,4
else
 tac $w_wims_home/log/classes/$w_wims_class/cdt/connect.log
fi;
echo "</pre>"
