!! to translate this help you just have to copy this file with correct extension (fr en de) and translate it !
!!

!let help_isread=yes
Het vaardigheden overzicht geeft een configureerbaar totaal beeld van het niveau van een klas.

Per periode kan de docent een lijst met oefeningen aangeven, waaruit dan met de behaalde scores 
een vaardigheids niveau kan worden berekend.
<p>
Ook kan de docent besluiten  sommige werkbladen niet te laten meetellen voor het bepalemn van het vaardigheids niveau.
Het is mogelijk deze data gedurende meerdere jaren te vervolgen.

Het vaardigheids niveau wordt berekend met :
<center>
!insmath 10 \times \frac{\sum_{i=1}^{N} NM(x_{L[i;1],L[i;2]})}{\sum_{i=1}^{N} \delta_{L[i;1]}}
</center>
waarin
<ul>
 <li> <i>N</i> is het aantal oefeningen is een pariode.</li>
 <li> <i>L</i> is de lijst van werkbladen gedurende een periode. Elk element van deze lijst bevat het werkblad nummer (aangegeven door  L[i;1]) en het nummer van de oefening in het werkblad (aangegeven door L[i;2]).</li>
 <li> 
  !insmath X_{i,j}
  is de kwaliteit voor serie oefeningen <i>j</i> van werkblad <i>i</i>.</li>
 <li> 
  !insmath \delta_i is 1 als het werkblad <i>i</i> niet is gedeactiveerd boor de berekening van het vaardigheids niveau per periode. Een werkblad dat is gedeactiveerd heeft waarde <i>0</i>.
 <li> NM(a) is <i>1</i> als <i>a</i> groter is dan de minimaal vereiste score ; anders <i>0</i> (zet deze minimale score op <i>0</i> om deze optie ongedaan te maken)</li>
</ul>
<p>
<b><u>Opmerking</u></b>: 
Als de status van een werkblad wordt veranderd moeten er op dat moment geen leerlingen met de vaardigheden boekje bezig zijn.