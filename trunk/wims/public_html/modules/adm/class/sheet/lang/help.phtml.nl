!if $wims_read_parm!=$empty
 !goto $wims_read_parm
!endif

:dependancies
!read adm/title.phtml 1\
$(name_shtab[6])

  De cijfer afhankelijkheden wil zeggen:<br />
  een student moet eerst de gewenst score hebben behaald voordat de volgende opdracht mag worden gedaan.
  [drempel]
  Bijvoorbeeld:
  <span class="tt wims_code_words">1:50,2:30,3+4+5:60</span>
  betekend: de student moet 50% van de opdracht 1 goed hebben,
  30$ van opdracht 2 en een gemiddelde score van 60% over de opdrachtwn 3,4 en 5.

<br class="spacer" />
!if $wims_read_parm!=$empty
 !exit
!endif

:allowtype
!read adm/title.phtml 1\
Informatie over het scoringssysteem

De scoreregistratie tijdstippen kan worden ingesteld
door de volgende woorden
toe te voegen:
<span class="tt wims_code_words">
&gt;yyyymmdd.hh:mm</span></b></font>
(begin tijd) en/of
<span class="tt wims_code_words">
&lt;yyyymmdd.hh:mm</span></b></font>
(eind tijd).
Deze tijden moeten in de lokale SERVER tijd zijn en door spaties worden gescheiden van de andere instellingen.

!! for translation copy the part of the lang/help.phtml.fr corresponding to the record :variable
!read lang/help.phtml.fr variable

!exit

:feedback
!read adm/title.phtml 1\
$(name_shtab[10])

Hier kan een link naar een WIMS document of oefening worden aangegeven.
Deze link (eerste item) is alleen zichtbaar als de score voor het werk lager is dan de ingestelde limiet score.
Deze limiet score (1 - 10) voor de actieve help kan worden ingesteld (tweede item).
Syntax voor speciale helppagina's:
<ul><li>
Een algemeen toegankelijke WIMS module of document: <span class="tt wims_address">module=xxx</span>
(syntax gelijk aan : <span class="wims_button disabled">$wims_name_about</span>).
</li><li>
Een oefening (via createxo) alleen toegankelijk in uw klas (dus eigen werk) : <span class="tt wims_address">module=classes/nl&exo=naam_van_de_oefening</span>.
 De <span class="tt">naam_van_de_oefening</span> is de oefening zonder extensie <span class="tt">.oef</span>).
</li><li>
Een document in uw klas :<span class="tt wims_address">module=adm/doc&doc=c1&+block=naam_van_het_blok</span>
</li></ul>
Extra parameters kunnen worden toegevoegd  (zie ook <span class="wims_button disabled">$wims_name_about</span>)

In het onderstaande voorbeeld zal , als het cijfer lager is dan een 5 , een WIMS document uit uw klas worden getoond.
En wel uit document <span class="tt">c2</span> de pagina op blok <span class="tt">aaa</span>.
<pre>module=adm/doc&doc=c2&+block=aaa,5</pre>


In het onderstaande voorbeeld wordt doorverwezen naar specifieke oefening uit een OEF module "H5/set/oefset.fr".
<pre>module=H6/set/oefset.fr&cmd=new&exo=traduction1,10</pre>

In het onderstaande voorbeeld wordt doorverwezen naar specifieke oefening uit een Schaersvoorde module "H4/stat/stat-4.nl".
<pre>module=H4/stat/stat-4.nl&taal=nl&subject=5&level=2&total_exos=1&rounding=-1&usage=2&cmd=new,10</pre>

En mettant deux nombres (dont le deuxième est strictement positif), le bouton
apparaît lorsque le score est compris entre le second nombre
et le premier nombre : par exemple, si vous mettez,
<pre>module=H6/set/oefset.fr&cmd=new&exo=traduction1,11,10</pre>
le bouton apparait lorsque le score est de 10 et c'est le mot $wims_name_feedbackplus
qui apparait. Si le deuxième nombre est 0, le comportement est le même que s'il
n'existait pas.


U kunt ook een Help-koppeling ook invoegen aan een werkblad. Klik op de link <span class="wims_button disabled"> $ wims_name_addh </span> in het menu
!exit

:series
!! for translation copy the part of the lang/help.phtml.fr corresponding to the record :series
!read lang/help.phtml.fr series

!exit
