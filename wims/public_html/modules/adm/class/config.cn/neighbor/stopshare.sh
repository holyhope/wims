#! /bin/sh

mdir=`pwd`

nei=$w_wims_home/log/classes/$w_nei
cd $w_wims_home/log/classes/$w_wims_class
cldir=`pwd`

if [ "$w_stoprec" = "sheet" ]; then
 rm -fR sheets .[0-9]*
 cp -R $nei/sheets $nei/.[0-9]* .
 exit
fi

if [ "$w_stoprec" = "exam" ]; then
 rm -fR exams .E[0-9]*
 cp -R $nei/exams $nei/.E[0-9]* .
 exit
fi

if [ "$w_stoprec" = "doc" ]; then
 rm -fR doc
 cp -R $nei/doc .
 exit
fi

if [ "$w_stoprec" = "vote" ]; then
 rm -fR vote
 cp -R $nei/vote .
 exit
fi

if [ "$w_stoprec" = "cdt" ]; then
 rm -fR cdt
 cp -R $nei/cdt .
 exit
fi

if [ "$w_stoprec" = "forum" ]; then
 rm -fR forum
 cp -R $nei/forum .
 exit
fi

if [ "$w_stoprec" = "user" ]; then
 rm -fR .users .userlist
 cp -R $nei/.users $nei/.userlist .
 exit
fi

if [ "$w_stoprec" = "sup" ]; then
 rm -f supervisor
 cp $nei/supervisor .
 exit
fi

if [ "$w_stoprec" = "motd" ]; then
 rm -f .motd
 cp $nei/.motd .
 exit
fi

if [ "$w_stoprec" = "exo" ]; then
 rm -fR src def Ex*
 cp -R $nei/src .
 cp -R $nei/def .
 cp $nei/Exindex .
 cp $nei/Extitles .
 exit
fi

