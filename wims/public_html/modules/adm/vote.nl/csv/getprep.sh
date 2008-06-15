#! /bin/sh

sdir=$w_wims_home/$w_wims_sesdir
mkdir -p $sdir/getfile
mv -f $sdir/$w_infile $sdir/getfile/$w_outfile
