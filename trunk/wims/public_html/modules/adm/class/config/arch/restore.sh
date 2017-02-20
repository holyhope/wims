#! /bin/sh

mdir=`pwd`
cd $w_wims_home/$w_wims_sesdir
sdir=`pwd`
cldir=$w_wims_home/log/classes/$w_wims_class
cd $cldir
cldir=`pwd`
cd $sdir

cd $cldir
if [ "$w_def" = "y" ]; then
 cp .def .def.bak
fi
if [ "$w_sup" = "y" ]; then
 cp supervisor supervisor.bak
fi
rm -Rf $w_eraselist 2>/dev/null
cd $sdir/upload/class
cp -pR $w_copylist $cldir

if [ "$w_user" = "y" ]; then
 echo user-install
fi

if [ "$w_exo" = "y" ]; then
 cd $cldir
 mkdir -p def
 src2def oef
 echo exo-install
fi

cd $sdir
rm -fR upload/class

