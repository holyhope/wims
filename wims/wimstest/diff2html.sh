#! /bin/sh
SRC="wimstest/ALLOEF";
IND1="ALLOEFHTML";
IND="wimstest/$IND1";
OUT="$IND/index.html";
mkdir -p $IND
 echo '<!DOCTYPE html PUBLIC "-//IETF//DTD HTML 2.0//EN"><html><head><title>Enscript Output</title></head><body><ul>' > $OUT
>> $OUT
for j in `ls $SRC/*` ; do
   jj=`basename $j`
   enscript --color -w html -2 --header="<a href=\"$OUT\">retour</a>" -Ediffu $j -o $IND/$jj.html ;
   echo "<li><a href=\"$jj.html\">$jj</a></li>" >> $OUT
done

echo "</ul></body></html>" >> $OUT
