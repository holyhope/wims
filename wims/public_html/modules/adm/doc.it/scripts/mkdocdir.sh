#!/bin/sh

d=$w_wims_home/$w_Docdir
dd=$d/$w_doc
if [ ! -d $d ]; then mkdir $d; fi
if [ ! -d $dd ]; then
 mkdir $dd
 mkdir $dd/src
fi
