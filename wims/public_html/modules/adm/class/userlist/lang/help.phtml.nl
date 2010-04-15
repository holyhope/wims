

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
$table_tr<td align="center">0<td align="center">$scoremax max(x,y)
 <td>Heel soepel: het maximum van percentage en kwaliteit.
$table_tr<td align="center">1<td align="center">$scoremax x
 <td>Geen rekening houden met het gemiddelde cijfer.
 Als alle werk is afgerond wordt de maximale score getoond.
$table_tr<td align="center">2<td align="center">$scoremax x y<sup>0.3</sup>
 <td> Het gemiddelde van alle scores heeft een klein effect op het cijfer.
$table_tr<td align="center">3<td align="center">$scoremax x y<sup>0.5</sup>
 <td> Meer effect van de gemiddelde score.
$table_tr<td align="center">4<td align="center">$scoremax x y
 <td>
 Om een cijfer $scoremax te behalen moeten alle vereiste punten worden behaalt (100%)
 en geen enkele fout (gemiddelde = 10).
$table_tr<td align="center">5<td align="center">$scoremax x<sup>2</sup> y
 <td>Onafgerond werk wordt extra zwaar bestraft.
$table_tr<td align="center">6<td align="center">$scoremax x<sup>2</sup> y<sup>2</sup>
 <td>Elke fout wordt extra zwaar bestraft.
$table_end <p>



