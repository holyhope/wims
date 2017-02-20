
!if $special_parm!=$empty and $special_parm_!=$empty
 !changeto lang/help.$moduclass_lang/$special_parm.phtml
!endif

!read adm/title.phtml 1\
\
De moeilijkheidsgraad van Werkbladen
!if $wims_user=supervisor
<p>
De WIMS server berekend een tweetal gemiddelden voor het werk dat leerlingen doen per werkblad
Een percentage van het behaalde aantal punten met betrekking tot het totaal aantal benodigde punten
en een gemiddelde van alle cijfers behaald voor opgaven in een werkblad
Laten we <em><b>x</b></em> het percentage zijn en <em><b>y</b></em>  de gemiddelde score (beiden dus tussen 0 en 1)
dan is dit de berekening van het "echte" cijfer:
</p>

!reset table_center
$table_header
$table_hdtr<th>Moeilijkheidsgraad</th><th>Formule</th><th>Verklaring</th></tr>
$table_tr<td>0</td><td>$scoremax max(x,y)
 </td><td>Heel soepel: het maximum van percentage en kwaliteit.</td></tr>
$table_tr<td>1</td><td>$scoremax x
 </td><td>Geen rekening houden met het gemiddelde cijfer.
 Als alle werk is afgerond wordt de maximale score getoond.</td></tr>
$table_tr<td>2</td><td>$scoremax x y<sup>0.3</sup>
 </td><td> Het gemiddelde van alle scores heeft een klein effect op het cijfer.</td></tr>
$table_tr<td>3</td><td>$scoremax x y<sup>0.5</sup>
 </td><td> Meer effect van de gemiddelde score.</td></tr>
$table_tr<td>4</td><td>$scoremax x y
 </td><td>
 Om een cijfer $scoremax te behalen moeten alle vereiste punten worden behaalt (100%)
 en geen enkele fout (gemiddelde = 10).</td></tr>
$table_tr<td>5</td><td>$scoremax x<sup>2</sup> y
 </td><td>Onafgerond werk wordt extra zwaar bestraft.</td></tr>
$table_tr<td>6</td><td>$scoremax x<sup>2</sup> y<sup>2</sup>
 </td><td>Elke fout wordt extra zwaar bestraft.</td></tr>
$table_end

En niveau 0 et 1, si la note de qualité est
inférieure à 1 pour un exercice, le pourcentage de points acquis
est mis à 0% pour cet exercice lors du calcul de I ;
si la note de qualité est comprise entre 1 et 2,
le pourcentage de réussite pour cet exercice est divisé par 2 lors du calcul de I.

!else
Pour cette feuille, votre enseignant a choisi le mode de calcul suivant
de la note.
Pour chacun des indicateurs suivants, on calcule la moyenne pour votre travail pour :
<ul>
<li>
!if $help_sw=0
  le quotient I des points cumulés par le nombre de points demandés 10*n
!endif
!if $help_sw=1
la moyenne I des n meilleures notes,
!endif
!if $help_sw=2
 le minimum I des n meilleures notes
!endif
</li>
<li>
la qualité Q des points obtenus sur les exercices.
</li>
</ul>

Si la note de qualité est inférieure à 1 pour un exercice,
I est mis à 0 pour cet exercice  ;
si la note de qualité est comprise entre 1 et 2,
I est divisé par 2 lors du calcul de la note de la feuille.

</p><p>
Ces moyennes sont ramenées entre 0 et 1 et
 la note de la feuille est calculée comme
\($scoremax * $(list[$help_level+1;]) \)
!endif
