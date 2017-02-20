#!/bin/sh
oeffile="wims_mathml_info.oef"
phtmlfile="wims_mathml_info.phtml"
htmlfile="wims_mathml_info.html"
idx=`date +%s`
listfile="/tmp/list.$idx"
if [ -e wims_mathml.l ] ; then
    echo "\statement{
    <table summary=\"mathml_info.oef\">
    <tr><td>latex command</td><td></td><td>Unicode</td></tr>
    "> $oeffile
    echo "
    <table summary=\"mathml_info.oef\">
    <tr><td>latex command</td><td></td><td>Unicode</td></tr>
    "> $phtmlfile
    echo "
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">
<html>
    <head>
	    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">
	    <title>
		    Latex supported in wims_mathml
	    </title>
    </head>
    <body>
    <table summary=\"latex commands\" style=\"font-size:8px\"><tr>" > $htmlfile
firstletter="a"
Tr=4;
# 5 columns... !
echo  "		<th>Environments</td><th>\begin{env}&sdot;&sdot;&sdot;\end{env}</th>" >> $htmlfile 
p=0
e=$(($Tr - 2))
while [ $p -le $e ] ;do
    echo "<td>&nbsp;</td>" >> $htmlfile
    p=$(($p+1))
done
echo "</tr><tr>" >> $htmlfile

a=0
for p in matrix pmatrix bmatrix  Bmatrix vmatrix Vmatrix smallmatrix cases dcases align* align aligned gathered split array alignat svg equation eqnarray ; do
    echo "<td>$p</td>" >> $htmlfile
    a=$(($a+1))
    if [ $a -gt $Tr ] ; then
	echo "</tr><tr>" >> $htmlfile
	a=0
    fi
done
p=0
e=$(($Tr - $a))
while [ $p -le $e ] ;do
    echo "<td>&nbsp;</td>" >> $htmlfile
    p=$(($p+1))
done
echo "</tr><tr>" >> $htmlfile

    cat wims_mathml.l | grep "^\"" | awk -F\" '{if($2 != "<" && length($2)>5) print $2}' | tr '&{([]})#\' ' ' | sort -duif> $listfile
    p=0
    a=0
    while [ $a -le $Tr ] ; do
	echo "<th>$firstletter</th>\c" >> $htmlfile
	a=$((a+1))
    done
    echo "</tr><tr>">> $htmlfile
    while read line ; do
	letter_one=$( set -f; printf "%c " $line )
	letter_one=`echo $letter_one | tr '[:upper:]' '[:lower:]'`
	if [ "$letter_one" != "$firstletter" ] ; then
	    firstletter=$letter_one
	    a=$p
	    while [ $a -le $Tr ] ; do
		echo  "<td>&nbsp;</td>" >> $htmlfile
		a=$((a+1))
	    done
	    echo  "</tr><tr>" >> $htmlfile
	    a=0
	    while [ $a -le $Tr ] ; do
		echo  "<th>$firstletter</th>" >> $htmlfile
		a=$((a+1))
	    done
	    echo  "</tr><tr>" >> $htmlfile
	    p=0
	fi
	chk=`echo $line | wc -c | tr -d '[:blank:]'`
	if [ $chk -gt 1 ] ; then
	    echo "<td>\\\\$line\c</td>" >> $htmlfile
	    echo "<tr><td>&bsol;$line</td><td>:</td><td>\( \\$line \)</td></tr>" >> $oeffile
	    echo "<tr><td>&bsol;$line</td><td>:</td><td>
!insmath \\$line
</td></tr>" >> $phtmlfile
	    p=$((p+1))
	    if [ $p -gt $Tr ] ; then
		echo  "</tr><tr>">> $htmlfile
	        p=0
	    fi
	fi
    done < "$listfile"
    rm $listfile
    echo "	</tr>
	</table>
    </body>
</html>
">> $htmlfile  
echo "</table>
}" >> $oeffile
echo "</table>
" >> $phtmlfile
else
    place=`pwd`
    echo "
    
    no file called \"wims_mathml.l\" in this script directory $place ! 
    
    "
    read whatever
fi
