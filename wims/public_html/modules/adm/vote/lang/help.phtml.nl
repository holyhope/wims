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
<p><dt><tt class="wims_code_variable">\menu{JA,NEE}</tt>
	<dd>Menu Keuze.

<p><dt><tt class="wims_code_variable">\list{A,B,C,D}</tt>
	<dd>Een keuze d.m.v. een rij verticale "radiobuttons"

<p><dt><tt class="wims_code_variable">\radio{zeer slecht, slecht,redelijk, prima}</tt>
	<dd>Een keuze d.m.v. een rij horizontale "radiobuttons"

<p><dt><tt class="wims_code_variable">\uservar{vname,val0,val1,...}</tt>
	<dd>Registreer de keuze in een variabele <tt>vname</tt> voor elke student afzonderlijk.
	De waarde van deze variabele is default <tt>val0</tt> , en <tt>val1</tt> 
	als de student kiest voor de eerste optie, etc.<p>
	Deze variabele kan worden gebruikt om de toegang tot werkbladen en toetsen
	tot op de individuele student te regelen.
	Vermeld de variabele 
	<tt class="wims_code_variable">\vname</tt> in de lijst met restricties van de bestreffene werkbladen of toetsen
<p><dt><tt class="wims_code_variable">\textarea</tt>
<dd>Een tekst invoerveld, 
alleen te gebruiken bij een anoniem enquete.
</dl>

Een enquete mag tot 64 keuzevelden bevatten.

!tail
!exit
!endif

!if generalinfo iswordof $wims_read_parm
<ul>
 <li><b>$wims_name_title</b> : the title of the questionnaire.</li>
 <li><b>$wims_name_Type</b>: 
  <ul>
   <li><b>$name_anonymous </b>: in an anonymous questionnaire nobody knows 
   who answered what (it is for instance impossible to go back 
   and double check what your own answer was.)
</li>
   <li><b>$name_trace with log files</b>: this type is similar to the anonymous type questionnaire 
   except that the answers provided by a participant can be identified, 
   however  the identity of the participant is not revealed.</li>
   <li><b>$name_nominative</b>:  each participant's answers can be consulted ( the "free response" 
   area cannot be used with this type of questionnaire.)</li>
</ul>
 </li>
 <li><b>$wims_name_Status</b>: refers to one of the statuses described below:
     <ul>
      <li><b>$name_0</b>: the questionnaire can be modified, the participants cannot see it.</li>
      <li><b>$name_1</b>: the questionnaire cannot be modified, the participants can respond to the questions</li>
      <li><b>$name_2</b>: the questionnaire cannot be modified, the participants cannot respond to the questions </li>
      <li><b>$name_3</b>: the questionnaire cannot be modified, the participants cannot see the questions.</li>
     </ul>
 </li>
 <li><b>$name_result</b>: if the results are published, the participants can consult 
 them after having voted, if not, only the administrator of the class can access the results.
 <li><b>$name_whovote</b>: if this list is published, both the administrator of the class
 and the participants can consult the list ( providing that there are enough participants who have voted),
 if not, nobody can see who has voted.
</ul> 
!tail
!exit
!endif
!tail