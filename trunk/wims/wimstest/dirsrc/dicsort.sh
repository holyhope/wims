#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";

export dicsort_separator=":";
$wims_home/src/Misc/dicsort $wims_dirtest/dic
