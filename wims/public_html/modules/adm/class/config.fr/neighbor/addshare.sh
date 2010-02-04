#! /bin/sh

# ne semble plus utilisé remplacé par adm/class/addshare
# ajout du exit le 29/6/2009

exit;

mdir=`pwd`

nei=$w_wims_home/log/classes/$w_nei
cd $w_wims_home/log/classes/$w_wims_class
cldir=`pwd`

if [ "$w_addshare" = "sheet" ]; then
 rm -fR sheets .[0-9]*
 mkdir -p $nei/sheets
 ln -s $nei/sheets .
 cp $nei/.[0-9]* .
 exit
fi

if [ "$w_addshare" = "exam" ]; then
 rm -fR exams .E[0-9]*
 mkdir -p $nei/exams
 ln -s $nei/exams .
 cp $nei/.E[0-9]* .
 exit
fi

if [ "$w_addshare" = "doc" ]; then
 rm -fR doc
 mkdir -p $nei/doc
 ln -s $nei/doc .
 exit
fi

if [ "$w_addshare" = "vote" ]; then
 rm -fR vote
 mkdir -p $nei/vote
 ln -s $nei/vote .
 exit
fi

if [ "$w_addshare" = "cdt" ]; then
 rm -fR cdt
 mkdir -p $nei/cdt
 ln -s $nei/cdt .
 exit
fi

if [ "$w_addshare" = "forum" ]; then
 rm -fR forum
 mkdir -p $nei/forum
 ln -s $nei/forum .
 exit
fi

if [ "$w_addshare" = "user" ]; then
 rm -fR .users .userlist
 mkdir -p $nei/.users
 ln -s $nei/.users $nei/.userlist .
 exit
fi

if [ "$w_addshare" = "sup" ]; then
 rm -fR supervisor
 ln -s $nei/supervisor .
 exit
fi

if [ "$w_addshare" = "motd" ]; then
 rm -fR .motd
 ln -s $nei/.motd .
 exit
fi

if [ "$w_addshare" = "exo" ]; then
 rm -fR src def Ex*
 mkdir -p $nei/src $nei/def
 touch $nei/Exindex
 touch $nei/Extitles
 ln -s $nei/src .
 ln -s $nei/def .
 ln -s $nei/Exindex .
 ln -s $nei/Extitles .
 exit
fi

