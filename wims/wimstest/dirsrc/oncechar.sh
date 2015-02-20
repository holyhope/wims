#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";

export oncechar="atb"
$wims_home/src/Misc/oncechar < $wims_dirtest/testonechar
