#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";

$wims_home/src/wims test $wims_dirtest eval 'test1 test2 test3 test4'

$wims_home/src/wims test $wims_dirtest eval 'test5 test6'
