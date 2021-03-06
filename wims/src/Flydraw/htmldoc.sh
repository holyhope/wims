#! /bin/sh

cd `dirname $0`
lang=$1
if [ -n "$lang" ] ; then file="commands.$lang" ; else file="commands" ; lang="en"; fi;

echo "
!! This file is automatically generated! Do not edit by hand.
"

if [ "$lang" = en ] ;  then echo "
<p>Each command takes one line.</p>
<p>In the following table, <span class=\"tt\">[color]</span>
may be either a color name, or 3 integers between 0 and 255, separated by commas,
for the values of red,green,blue.</p>
"
drawing="Drawing commands"
synonym="Synonymes"
fi ; 

if [ "$lang" = fr ] ; then echo "
<p>Chaque commande prend une ligne.</p>
<p>Dans la table suivante <span class=\"tt\">[color]</span>
peut 阾re un nom de couleur ou 3 entiers 0 entre 255, s閜ar閟 par des virgules,
correspondant aux valeurs de  rouge, vert, bleu.
</p>
"
drawing="Commandes"
synonym="Synonymes"
fi ;

if [ "$lang" = cn ] ;  then echo "
<p>每条命令占一行.</p>
<p>在下表中, <span class=\"tt\">[色彩]</span>
可以是色彩名, 或3个用逗号分隔的0到255的整数, 分别代表红绿蓝三种颜色.
</p>
"
drawing="作图命令"
synonym="同义词"
fi 
echo "!reset table_center
 \$table_header
 <caption>$drawing</caption>
 \$table_hdtr<th colspan=\"5\">\$wims_name_name - \$wims_name_Syntax</th></tr>
 \$table_hdtr<th colspan=\"2\">$synonym</th>
 <th colspan=\"3\">\$wims_name_Meaning</th></tr>
"
awk 'BEGIN {a=10}
	substr($0,1,1)==":" {a=0}
	{a++}
	a==1 {print "$table_tr<td colspan=\"5\" class=\"nowrap tt\">"substr($0,2)"</td></tr>"}
	a==2 {print "$table_tr<td colspan=\"2\"><span class=\"tt\">"$0"&nbsp;</span></td>"}
	a==3 {print "<td colspan=\"3\">"$0"</td></tr>"}
	' $file

echo "\$table_end"
