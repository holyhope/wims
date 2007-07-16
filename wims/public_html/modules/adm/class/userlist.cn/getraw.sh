#! /bin/sh

log_dir=$w_wims_home/log/classes/$w_wims_class
cat $log_dir/score/$w_getraw $log_dir/noscore/$w_getraw 2>/dev/null | sort >$session_dir/user.getraw

if [ ! -s "$session_dir/user.getraw" ]; then
 echo "No work has been done by this participant up to now."
 exit
fi

echo "    Date.Hour 	session	sheet ex request 	connection"
echo "------------------------------------------------------------"
cat $session_dir/user.getraw

