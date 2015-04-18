#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";

$wims_home/src/wims test $wims_dirtest text 'line item word1 word2'

$wims_home/src/wims test $wims_dirtest text 'accent1 accent2'
