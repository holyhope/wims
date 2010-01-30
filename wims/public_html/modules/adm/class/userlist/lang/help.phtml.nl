
!if $special_parm!=$empty
 !changeto lang/help.$moduclass_lang/$special_parm.phtml
!endif

!read adm/title.phtml 3\
\
De moeilijkheidsgraad van Werkbladen
<p>
De WIMS server berekend een tweetal gemiddelden voor het werk dat leerlingen doen per werkblad
Een percentage van het behaalde aantal punten met betrekking tot het totaal aantal benodigde punten 
en een gemiddelde van alle cijfers behaald voor opgaven in een werkblad
Laten we <em><b>x</b></em> het percentage zijn en <em><b>y</b></em>  de gemiddelde score (beiden dus tussen 0 en 1)
dan is dit de berekenings wijze van het "echte" cijfer:

<p>$table_header 
$table_hdtr<th>Moeilijkheidsgraad<th>Formule<th>Verklaring
$table_tr<td align=center>0<td align=center>$scoremax max(x,y)
 <td>Heel soepel: het maximum van percentage en kwaliteit.
$table_tr<td align=center>1<td align=center>$scoremax x
 <td>Geen rekening houden met het gemiddelde cijfer.
  You get maximum of grade once all the required work is done.
$table_tr<td align=center>2<td align=center>$scoremax x y<sup>0.3</sup>
 <td>Average of scores has only slight effect over the grade.
$table_tr<td align=center>3<td align=center>$scoremax x y<sup>0.5</sup>
 <td>More effect of average of scores.
$table_tr<td align=center>4<td align=center>$scoremax x y
 <td>To have a grade of $scoremax, you must gather all required points
  (100%) without making any error (average=10).
$table_tr<td align=center>5<td align=center>$scoremax x<sup>2</sup> y
 <td>Unfinished work is over-punished.
$table_tr<td align=center>6<td align=center>$scoremax x<sup>2</sup> y<sup>2</sup>
 <td>Any mistake is over-punished.
$table_end <p>



