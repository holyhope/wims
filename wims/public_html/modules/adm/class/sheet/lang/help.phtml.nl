!if $wims_read_parm!=$empty
 !goto $wims_read_parm
!endif

:dependancies
!read adm/title.phtml 1\
$(name_shtab[6])

  De cijfer afhankelijkheden wil zeggen:<br>
  een student moet eerst de gewenst score hebben behaald voordat de volgende opdracht mag worden gedaan.
  [drempel]
  Bijvoorbeeld:
  <tt class="wims_code_words">1:50,2:30,3+4+5:60</tt>
  betekend: de student moet 50% van de opdracht 1 goed hebben,
  30$ van opdracht 2 en een gemiddelde score van 60% over de opdrachtwn 3,4 en 5.

<div class="emptyline"></div>
!if $wims_read_parm!=$empty
 !exit
!endif

:allowtype
!read adm/title.phtml 1\
Informatie over het scoringssysteem

De scoreregistratie tijdstippen kan worden ingesteld 
door de volgende woorden 
toe te voegen:
<tt class="wims_code_words">
&gt;yyyymmdd.hh:mm</tt></b></font>
(begin tijd) en/of
<tt class="wims_code_words">
&lt;yyyymmdd.hh:mm</tt></b></font>
(eind tijd). 
Deze tijden moeten in de lokale SERVER tijd zijn en door spaties worden gescheiden van de andere instellingen.


!exit

:feedback
!read adm/title.phtml 1\
$(name_shtab[10])

Hier kan een link naar een WIMS document of oefening worden aangegeven.
Deze link (eerste item) is alleen zichtbaar als de score voor het werk lager is dan de ingestelde limiet score.
Deze limiet score (1 - 10) voor de actieve help kan worden ingesteld (tweede item).
Syntax voor speciale helppagina's:
<ul><li>
Een algemeen toegankelijke WIMS module of document: <tt class="wims_address">module=xxx</tt>
(syntax gelijk aan : <span class="wims_button disabled">$wims_name_about</span>).
</li><li>
Een oefening (via createxo) alleen toegankelijk in uw klas (dus eigen werk) : <tt class="wims_address">module=classes/nl&exo=naam_van_de_oefening</tt>.
 De <tt>naam_van_de_oefening</tt> is de oefening zonder extensie <tt>.oef</tt>).
</li><li>
Een document in uw klas :<tt class="wims_address">module=adm/doc&doc=c1&+block=naam_van_het_blok</tt>
</li></ul>
Extra parameters kunnen worden toegevoegd  (zie ook <span class="wims_button disabled">$wims_name_about</span>)

In het onderstaande voorbeeld zal , als het cijfer lager is dan een 5 , een WIMS document uit uw klas worden getoond.
En wel uit document <tt>c2</tt> de pagina op blok <tt>aaa</tt>. 
<pre>module=adm/doc&doc=c2&+block=aaa,5</pre>


In het onderstaande voorbeeld wordt doorverwezen naar specifieke oefening uit een OEF module "H5/set/oefset.fr".
<pre>module=H6/set/oefset.fr&cmd=new&exo=traduction1,10</pre>

In het onderstaande voorbeeld wordt doorverwezen naar specifieke oefening uit een Schaersvoorde module "H4/stat/stat-4.nl".
<pre>module=H4/stat/stat-4.nl&taal=nl&subject=5&level=2&total_exos=1&rounding=-1&usage=2&cmd=new,10</pre>

!exit

