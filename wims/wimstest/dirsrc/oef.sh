#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";
oef2wims_mdef="oefenv"
export oef2wims_mdef

$wims_home/src/OefMsg2wims/oef2wims $wims_dirtest/oef $wims_home/wimstest/tmp/oef1
perl -pi -e 's/ +\n/\n/g' $wims_home/wimstest/tmp/oef1
cp -f  $wims_home/wimstest/tmp/oef1 $wims_home/wimstest/tmp/oef
