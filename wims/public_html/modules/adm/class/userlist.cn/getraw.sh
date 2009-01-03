#! /bin/sh

log_dir=$w_wims_home/log/classes/$w_wims_class;
cat $log_dir/score/$w_getraw $log_dir/noscore/$w_getraw 2>/dev/null | sort >$session_dir/user.getraw;

if [ ! -s "$session_dir/user.getraw" ]; then
 echo "No work has been done by this participant up to now."
 exit
fi
if [ "$w_test" = "no" ]; then
 echo "    Date.Hour 	session	Sheet exo requete"
 echo "------------------------------------------------------------"
 cat $session_dir/user.getraw | cut -d"	" -f2 --complement;
else
 echo "    Date.Hour 	session	sheet exo requete 	connection"
 echo "------------------------------------------------------------"
 cat $session_dir/user.getraw;
fi;

