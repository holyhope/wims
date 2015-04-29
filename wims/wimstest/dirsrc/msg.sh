#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";
w_msg2wims_primitives="if ifval for while
    reload fold ref link docform form resource calcform embed
    exercise tool doc example help adm tooltip href slib
    def define comment draw canvasdraw audio"
export w_msg2wims_primitives


$wims_home/src/OefMsg2wims/msg2wims $wims_dirtest/msg $wims_home/wimstest/tmp/msg1

perl -pi -e 's/ +\n/\n/' $wims_home/wimstest/tmp/msg1
cp -f $wims_home/wimstest/tmp/msg1 $wims_home/wimstest/tmp/msg
