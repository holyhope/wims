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
 <dt><tt class="wims_code_variable">\menu{JA,NEE}</tt>
	<dd>Menu Keuze.

 <dt><tt class="wims_code_variable">\list{A,B,C,D}</tt>
	<dd>Een keuze d.m.v. een rij verticale "radiobuttons"
	</dd>
 <dt><tt class="wims_code_variable">\radio{zeer slecht, slecht,redelijk, prima}</tt>
	<dd>Een keuze d.m.v. een rij horizontale "radiobuttons"
	</dd> 
 <dt><tt class="wims_code_variable">\checkbox{A,B,C,D}</tt>
	<dd>Several choices by horizontal buttons.
	</dd>
 <dt><tt class="wims_code_variable">\uservar{vname,val0,val1,...}</tt>
	<dd>Registreer de keuze in een variabele <tt>vname</tt> voor elke student afzonderlijk.
	De waarde van deze variabele is default <tt>val0</tt> , en <tt>val1</tt> 
	als de student kiest voor de eerste optie, etc.<p>
	Deze variabele kan worden gebruikt om de toegang tot werkbladen en toetsen
	tot op de individuele student te regelen.
	Vermeld de variabele 
	<tt class="wims_code_variable">\vname</tt> in de lijst met restricties van de bestreffende 
	werkbladen of toetsen.
	In dat geval is het ook mogelijk het maximale aantal deelnemers aan te geven.
	Laat elke keuze beginnen met dit getal gevolgs door een dubbele punt <tt class="wims_code_words">:</tt>
	Bijvoorbeeld:
<pre>
\list{12:Sessie 1 om 8.00,
16:Sessie 2 om 10.00, 
21:Sessie 3 om 13.00}
</pre>
	</dd>
<dt><tt class="wims_code_variable">\textarea</tt>
   <dd>Een tekst invoerveld, alleen te gebruiken bij een anoniem enquete.
	</dd>
</dl>

Een enquete mag tot 64 keuzevelden bevatten.

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
!tail
!exit
!endif
!tail
