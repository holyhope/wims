#! /bin/sh

cd ..
i=`id -un`
find $wims_exec_parm \! -user $i | head -60 | grep -v '^chroot/usr/bin/\[$'

