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

!read lang/help.phtml.fr feedback

!exit

