#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";
oef2wims_mdef="oefenv"
export oef2wims_mdef
mkdir -p $wims_home/wimstest/tmp/diroef
for a in `ls $wims_dirtest/diroef` ; do
 echo $a
 $wims_home/src/OefMsg2wims/oef2wims $wims_dirtest/diroef/$a $wims_home/wimstest/tmp/diroef/b
 perl -pi -e 's/ +\n/\n/g' $wims_home/wimstest/tmp/diroef/b
 mv -f  $wims_home/wimstest/tmp/diroef/b $wims_home/wimstest/tmp/diroef/$a
done
