#! /bin/sh

rm -f $w_dest
cp $w_src $w_dest 2>/dev/null
stat -c'%s' $w_dest

