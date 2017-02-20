#! /bin/sh

log_dir=$w_wims_home/log/classes/$w_wims_class
cat $log_dir/score/$w_getraw $log_dir/noscore/$w_getraw 2>/dev/null | sort >$session_dir/user.getraw

