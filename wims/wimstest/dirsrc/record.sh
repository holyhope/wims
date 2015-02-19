#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";

$wims_home/src/wims test $wims_dirtest record 't'
