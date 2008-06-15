#! /bin/sh
 packs=$wims_exec_parm
 adresse=packs.shtooka.net
 echo $packs ; 
 
cd scripts/data/swac ; 
 for i in $packs; do
  echo $i ; 
  wget http://$adresse/$i/$i.mp3.tar; echo "wget $adresse/$i/$i.mp3.tar" ;
  tar xf $i.mp3.tar;
  mkdir -p $i;
  rm -r $i/mp3;
  mv home/www/packs/$i/mp3 $i/mp3;
  rm -r home; rm $i.mp3.tar ;
  cd $i;
##  mv index.tags.txt index.tags.txt_1 ;
##  wget http://$adresse/$i/ogg/index.tags.txt ;
##  echo "wget http://$adresse/$i/ogg/index.tags.txt ";
##  rm index.tags.txt_1 ;
 cd .. ;\
done ;
cd $w_wims_home/scripts/data/swac ; 
./mkindex ; 
