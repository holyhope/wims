#! /bin/sh
# too long for the moment
# do it by hand with $wims/bin/swac
swac=scripts/data/swac
cd $swac; 
./mkindex ;
!exit


# packs=$wims_exec_parm
#adresse=download.shtooka.net
# echo $packs ; 
# swac=scripts/data/swac
# cd $swac; 
# for i in $packs; do
#  j=${i}_mp3 ;
#  wget http://$adresse/$j.tar; echo "wget $adresse/$j.tar" ;
#  tar xf $j.tar;
# if [-d "$j"]  then cd  $j ; cp -r * ../$i/ ; cd $swac; fi ;
# rm $j.tar ; rm -r $j;
# echo "$i" >> version ;
#done ;
#cd scripts/data/swac ; cp version.tmp version ; rm version.tmp; 

