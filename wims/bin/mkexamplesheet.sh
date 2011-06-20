#! /bin/sh
#
# script to look at each example class and copy sheet in public_html/bases/sheet/$class_lang/$class_level/$class_number/
# to be execute at before each realize of a wims package.
#
# authors : F. Guerimand
# mail : fwguerima@free.fr
# this script is launch by mkindex. Don't use it directly
# 

whome="$1"
if [ -z "$whome" ]; then
 echo "don't use this script directly. execute mkindex";
 exit
fi;
target="$whome/public_html/bases/sheet";
#target="$whome/fabtest"
cd $whome/log/classes/;
clist=`ls -d [0-9]*`;
for cls in $clist; do
 if [ $cls -lt 9000 ]; then
  level=`awk -F'=' '$1=="!set class_level" {print $2; exit}' ./$cls/.def`;
  lang=`awk -F'=' '$1=="!set class_lang" {print $2; exit}' ./$cls/.def`;
  sup=`awk -F'=' '$1=="!set class_supervisor" {print $2; exit}' ./$cls/.def`;
  email=`awk -F'=' '$1=="!set class_email" {print $2; exit}' ./$cls/.def`;
  if [ -n "$level" -a -n "$lang" ]; then
   cd $cls/sheets/;
   echo "--------------- $cls ; $level ; $lang"
   slist=`ls .sheet[0-9]*`;
   tmptarget="$target/$lang/$level/$cls";
   mkdir -p $tmptarget;
   for sh in $slist; do
    num=${sh##.sheet};
    # test if statut of sheet is non 0
    statut=`awk -v no="$num" 'BEGIN{cpt=0;} {a=substr($0,1,1); if(a==":")cpt++; if(cpt==no){print($0);exit;}}' .sheets`;
    if [ "$statut" != ":0" ]; then
     entete=`awk '{a=substr($0,1,1); if(a==":")exit; else print($0);}' $sh`;
     namesh=${sh##.};
     if [ -n "$entete" ]; then
      #First case : information is in file .sheet$i : keep it (but not title and desc)
      echo "$sh : direct copy";
      title=`awk -v no="$num" 'BEGIN{cpt=0;l=0;} {a=substr($0,1,1); if(a==":")cpt++; if(cpt==no){l++;if(l==3){print($0);exit;}} }' .sheets`;
      desc=`awk -v no="$num" 'BEGIN{cpt=0;l=0;} {a=substr($0,1,1); if(a==":")cpt++; if(cpt==no){l++;if(l==4){print($0);exit;}} }' .sheets`;
      echo "$title
$desc" >$tmptarget/$namesh.def;
      awk 'FNR>2{print $0}' $sh >>$tmptarget/$namesh.def;
     else
      #second case : information not in file .sheet$i : make it with files .sheets and .def.
      dt=`perl -e 'for (@ARGV) {@S=stat($_); print scalar(localtime($S[9]))}' $sh`
      dt=${dt##* };
      title=`awk -v no="$num" 'BEGIN{cpt=0;l=0;} {a=substr($0,1,1); if(a==":")cpt++; if(cpt==no){l++;if(l==3){print($0);exit;}} }' .sheets`;
      desc=`awk -v no="$num" 'BEGIN{cpt=0;l=0;} {a=substr($0,1,1); if(a==":")cpt++; if(cpt==no){l++;if(l==4){print($0);exit;}} }' .sheets`;
      keyword=`awk -v no="$num" 'BEGIN{cpt=0;l=0;} {a=substr($0,1,1); if(a==":")cpt++; if(cpt==no){l++;if(l==6){print($0);exit;}} }' .sheets`;
      echo "$sh : make presentation";
      echo "$title
$desc
??,$dt
2
$level

$keyword
$sup
$email" > $tmptarget/$namesh.def;
      cat $sh >> $tmptarget/$namesh.def;
     fi;
    else
     echo "$sh : EMPTY sheet";
    fi;
   done;
   cd ../..;
  else
   echo "-----------------------NOTHING ---------- $cls ; $level ; $lang";
  fi;
 fi;
done;


