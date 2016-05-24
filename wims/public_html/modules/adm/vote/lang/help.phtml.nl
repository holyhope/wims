!if $special_parm!=$empty
 !changeto help/$module_language/$special_parm.phtml
!endif

!if $wims_user!=supervisor
    Er is geen helppagina voor studenten.
 !tail
 !exit
!endif

!if $wims_read_parm=$empty
De inhoud van de stemming / verkiezing kan een HTML tekst zijn, met dezelfde WIMS uitbreidingen als voor de "forum-berichten",
plus de volgende extra commando's <dl>
 <dt><span class="tt wims_code_variable">\menu{JA,NEE}</span>
	<dd>Menu Keuze.

 <dt><span class="tt wims_code_variable">\list{A,B,C,D}</span>
	<dd>Een keuze d.m.v. een rij verticale "radiobuttons"
	</dd>
 <dt><span class="tt wims_code_variable">\radio{zeer slecht, slecht,redelijk, prima}</span>
	<dd>Een keuze d.m.v. een rij horizontale "radiobuttons"
	</dd>
 <dt><span class="tt wims_code_variable">\checkbox{A,B,C,D}</span>
	<dd>Several choices by horizontal buttons.
	</dd>
 <dt><span class="tt wims_code_variable">\uservar{vname,val0,val1,...}</span>
	<dd>Registreer de keuze in een variabele <span class="tt">vname</span> voor elke student afzonderlijk.
	De waarde van deze variabele is default <span class="tt">val0</span> , en <span class="tt">val1</span>
	als de student kiest voor de eerste optie, etc.<br />
	Deze variabele kan worden gebruikt om de toegang tot werkbladen en toetsen
	tot op de individuele student te regelen.
	Vermeld de variabele
	<span class="tt wims_code_variable">\vname</span> in de lijst met restricties van de bestreffende
	werkbladen of toetsen.
	In dat geval is het ook mogelijk het maximale aantal deelnemers aan te geven.
	Laat elke keuze beginnen met dit getal gevolgs door een dubbele punt <span class="tt wims_code_words">:</span>
	Bijvoorbeeld:
<pre>
\list{12:Sessie 1 om 8.00,
16:Sessie 2 om 10.00,
21:Sessie 3 om 13.00}
</pre>
Attention cependant, utiliser la même variable technique dans plusieurs questionnaire peut générer des conflits.
  </dd>
<dt><span class="tt wims_code_variable">\textarea</span>
   <dd>Een tekst invoerveld, alleen te gebruiken bij een anoniem enquete.
	</dd>
</dl>

Een enquete mag tot $max_parms keuzevelden bevatten.

!tail
!exit
!endif

!if generalinfo iswordof $wims_read_parm
<ul>
 <li><b>$wims_name_title</b> : de titel van de vragenlijst.</li>
 <li><b>$wims_name_Type</b>:
  <ul>
   <li><b>$name_anonymous </b>:
   In een anonieme stemming weet niemand wat de ander heeft geantwoord.
   Het is ook onmogelijk om terug te gaan en het antwoord te veranderen.
</li>
   <li><b>$name_trace met log files</b>:
   Dit type is te vergelijken met een anonoieme stemming.
   Het verschil is dat antwoorden aan de deelnemer zijn gekoppeld, zonder dat de naam van deze deelnemer bekend is.
   </li>
   <li><b>$name_nominative</b>:
   Alle antwoorden van de deelnemers zijn te raadplegen.
   (open antwoorden kunnen niet worden ingezet bij dit type.)
   </li>
</ul>
 </li>
 <li><b>$wims_name_Status</b>:
     <ul>
      <li><b>$name_0</b>: de stemming kan worden veranderd, deelnemers kunnen nu de stemming niet zien.</li>
      <li><b>$name_1</b>: de stemming kan niet worden veranderd, deelnemers nu kunnen de vragen beantwoorden</li>
      <li><b>$name_2</b>: de stemming kan niet worden veranderd, deelnemers nu kunnen de vragen niet beantwoorden </li>
      <li><b>$name_3</b>: de stemming kan niet worden veranderd, deelnemers kunnen nu de stemming niet zien.</li>
     </ul>
 </li>
 <li><b>$name_result</b>:
 als de resultaten bekend zijn, kunnen alle deelnemers deze inzien nadat ze hebben gestemd.
 sld de resultaten nog niet bekend zijn gemaakt, kan alleen de supervisor van een klas deze inzien.
 <li><b>$name_whovote</b>:
 als deze lijst bekend gemaakt is, kunnen zowel de supervisor en de deelnemers deze lijst inzien.
 Tenzij er niet genoeg stemmen zijn uitgebracht, dan kan niemand deze lijst inzien.
</ul>
 !goto guidedmode
!tail
!exit
!endif

!if guidedmode iswordof $wims_read_parm
:guidedmode
De volgende modes zijn mogelijk
<ul><li>
  <b>$name_free</b> :
  er kan een enquete of stemming worden aangemaakt, zie voor de configuratie instellingen de help pagina.
  </li><li>
!readproc adm/lang/sheetexam.phtml.$lang
  <b>$name_accessvar</b> :
  dmv dit formulier kan de openings- en sluitingstijden voor werkbladen en/of toetsen worden ingesteld
  Met behulp hiervan kan toegang tot  op individueel niveau worden ingeregeld.
  Hiertoe kan eenvoudig<span class="tt wims_code_variable">mijn_variabele</span> worden gedefinieerd als
  <span class="tt wims_code_variable">\mijn_variabele</span> in het daartoe bestemde veld van het werkblad of proefwerk in kwestie
   <span class="tt wims_code_words">$(name_shinfo[6])</span>.
  </li><li>
  <b>$name_group</b> :
  Er kunnen ook groepjes studenten worden gedfinieerd.
  Er wordt dan weer een naam van de variabele gevraagd; bijvoorbeeld
   <span class="tt wims_code_variable">mijn_inhaal_groepje_variabele</span>.
   Met behulp van deze variabele kunnen leerlingen worden toegevoegd.
   Of emails worden verstuurd naar de deelnemers; lijsten met cijfers worden gesorteerd etc.
   Meerdere toepassingen worden nog ontwikkeld.
  </li>
<li>Attention cependant, utiliser la même variable technique dans plusieurs questionnaire peut générer des conflits.</li></ul>

Let op dat de variabele naam uniek is voor de klas en dat deze variabele niet in gebruik is door WIMS.
Bijvoorbeeld nooit variabelen gebruiken met namen als  <span class="tt wims_code_variable">exam1</span>, ... , <span class="tt wims_code_variable">sheet1</span>, ...,
<span class="tt wims_code_variable">manual1</span>, ...).
!tail
!exit
!endif
!tail

