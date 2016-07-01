
!let help_isread=yes
!if $wims_read_parm!=$empty
    !goto $wims_read_parm
!endif
Het vaardigheden (completenties) overzicht geeft een totaalbeeld van het niveau van een klas.

Per periode kan de docent een lijst met oefeningen aangeven, waaruit dan met de behaalde scores 
een vaardigheidsniveau wordt gevormd.
<p>
Ook kan de docent besluiten sommige werkbladen niet te laten meetellen voor het bepalen van het vaardigheidsniveau.
Het is mogelijk deze data gedurende meerdere jaren te vervolgen.
</p><p>
Het vaardigheidsniveau wordt berekend met :
<p><p class="wimscenter">
!insmath 10 \times \frac{\sum_{i=1}^{N} NM(x_{L[i;1],L[i;2]})}{\sum_{i=1}^{N} \delta_{L[i;1]}}
</p>
waarin
<ul>
 <li> <i>N</i> is het aantal oefeningen is een periode.</li>
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
Als de status van een werkblad wordt veranderd moeten er op dat moment geen leerlingen met de vaardighedenboekje bezig zijn.
</p>

!exit

:color
Bij elke kleur kan ook een kleine tekst worden getoond in de tabel met competenties.
<br />
Kleuren zonder begeleidende tekst worden bepaald door de behaalde scores.
<br />
Als ger geen speciale kleuren worden vastgesteld, wordt het algemene kleur&amp;score schema gebruikt.

!exit
