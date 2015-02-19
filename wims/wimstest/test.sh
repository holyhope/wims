#! /bin/sh
### execute from wims_home

wims_home=`pwd`;
wims_dirsrc="$wims_home/wimstest/dirsrc";

for i in `ls $wims_dirsrc/*.sh`; do echo "$i\n"; $i ; done
