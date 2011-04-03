!if $special_parm!=$empty
 !changeto help/$module_language/$special_parm.phtml
 !endif

!if $wims_user!=supervisor
    Er is geen helppagina voor studenten.
 !tail
 !exit
!endif

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

