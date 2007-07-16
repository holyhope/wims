#! /bin/sh

cd ..
wims_home=`pwd`
cd log
dat=`date`
cat >>wims.conf.old <<@

----------------------------------------------------------
##########################################################
#  wims.conf backup saved on $dat
##########################################################
@

tail -1000 wims.conf.old >wims.conf.old2
mv wims.conf.old2 wims.conf.old
cat wims.conf >>wims.conf.old
mv wims.conf2 wims.conf 2>/dev/null
chmod og-rwx wims.conf
rm -f $wims_home/tmp/wimslogd.pid
pwd

