#! /bin/sh

cat $w_src >>$w_dest
stat -c'%s' $w_dest

