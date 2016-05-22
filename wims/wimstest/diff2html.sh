#! /bin/sh

IND="ALLOEFHTML"
mkdir -p $IND
 echo '<!DOCTYPE html PUBLIC "-//IETF//DTD HTML 2.0//EN"><HTML><HEAD><TITLE>Enscript Output</TITLE></HEAD><BODY><ul>' > index.html
>> index.html
for j in `ls ALLOEF/*` ; do
   jj=`basename $j`
   enscript --color -w html -2 --header="<a href=\"index.html\">retour</a>" -Ediffu $j -o ALLOEFHTML/$jj.html ;
   echo "<li><a href="$IND/$jj.html">$jj</a>" >> index.html
done

echo "</ul></body></html>" >> index.html
