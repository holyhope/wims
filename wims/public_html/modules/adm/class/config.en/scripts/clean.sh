#! /bin/sh

mdir=`pwd`
cd $w_wims_home/$w_wims_sesdir
sdir=`pwd`
cldir=$w_wims_home/log/classes/$w_wims_class
cd $cldir
cldir=`pwd`
cd $sdir

cd $cldir
rm -Rf $w_dirs 2>/dev/null
mkdir -p $w_dirlist

if [ "$w_exo" = "y" ]; then
 cd $cldir
 rm -f Exindex Extitles 2>/dev/null
 src2def oef
fi

