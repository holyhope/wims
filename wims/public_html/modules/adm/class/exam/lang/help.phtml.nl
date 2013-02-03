!goto $wims_read_parm

:allowtype
<p class="wimscenter"><b>Openingstijden van een proefwerk</p>
 U kunt openingstijden definieren voor dit proefwerk, door het toevoegen van woorden
 <span class="tt wims_code_words">
&gt;yyyymmdd.hh:mm</span>
 (openingstijd) en/of
 <span class="tt wims_code_words">
&lt;yyyymmdd.hh:mm</span>
 (sluitingstijd). 
 Deze tijden moeten worden aangegeven in de lokale tijd van deze SERVER,
 en moeten worden gescheiden door spaties.
 <br />
 Formaat van de tijden <span class="tt wims_code_words">yyyymmdd.hh:mm</span> (bij meerdere opties deze scheiden door spaties).

!! for translation copy the part of the lang/help.phtml.fr corresponding to the record :variable
:variable
<p>
Om de toegang tot (werkbladen,toetsen) op de server te individualiseren, 
kan men gebruik maken van een variabele (naam).
Deze variabele moet worden gedefinieerd voor elke deelnemer en volgens specifieke voorschriften.
(handmatig in het studenten account of via een spreadsheet)
Deze individuele toegang kan worden geconfigureerd bij "enquete/stemming" onder "begeleidde mode"
(zie hiervoor de betreffende helppagina's)
</p>

!if $wims_read_parm!=$empty
 !exit
!endif

:dependency
 <p class="wimscenter" style="font-weight:bold;">Score drempels</p>  
Score drempels dit wil zeggen dat een deelnemer/leerling een bepaalde hoeveelheid punten <br />
moet behalen voor dat de volgende som/opdracht uit het proefwerk bereikbaar wordt.<br />
We noemen dit toets-type een "drempel toets".<br />
Bijvoorbeeld:  <span class="tt wims_code_words">1:50,2:30,3+4+5:60</span>wil zeggen dat<br />
de leerling minimaal 50% goed moet hebben van opdracht 1, 30% van opdracht 2 en opdracht 3,4,5 samen gemiddeld minimaal 60%.
!if $wims_read_parm!=$empty
 !exit
!endif

:options
 <p class="wimscenter" style="font-weight:bold;">Opties.</p>
Er is op dit moment slechts één optie beschikbaar :
<ul>
<li><em>autogen</em><br />
Alleen voor experts en voor het handmatig bijwerken van score resultaten.<br />
Autogen: betekent dat de oefening automatisch wordt uitgevoerd [automatische piloot...],<br />
zelfs als de gebruiker nergens op klikt.<br />
De gebruiker kan dit proefwerk dan raadplegen als de score registratie is afgelopen en de sessie reeds is afgesloten.
</li>
</ul>
!if $wims_read_parm!=$empty
 !exit
!endif

:contenu
  <p class="wimscenter" style="font-weight:bold;">Inhoud van een proefwerk</p>
Een oefening kan willekeurig worden genomen uit de lijst van bestaande oefeningen uit de werkbladen.<br />
Vink de werkbladen aan in de onderstaande lijst als kandidaten voor dit proefwerk.
!if $wims_read_parm!=$empty
 !exit
!endif
