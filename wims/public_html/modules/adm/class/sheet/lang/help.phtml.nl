!if $wims_read_parm!=$empty
 !goto $wims_read_parm
!endif

:dependancies

<center><b>$(name_shtab[6])</b></center>
  De cijfer afhankelijkheden wil zeggen:<br>
  een student moet eerst de gewenst score hebben behaald voordat de volgende opdracht mag worden gedaan.
  [drempel]
  Bijvoorbeeld:
  <font color=blue><tt>1:50,2:30,3+4+5:60</tt></font>
  betekend: de student moet 50% van de opdracht 1 goed hebben,
  30$ van opdracht 2 en een gemiddelde score van 60% over de opdrachtwn 3,4 en 5

!if $wims_read_parm!=$empty
 !exit
!endif

:allowtype
<center><b>Informatie over het scoringssysteem</b></center> 
De scoreregistratie tijdstippen kan worden ingesteld 
door de volgende woorden 
toe te voegen:
<font color=blue><b>
<tt>&gt;yyyymmdd.hh:mm</tt></b></font>
(begin tijd) en/of
<font color=blue><b>
<tt>&lt;yyyymmdd.hh:mm</tt></b></font>
(eind tijd). 
Deze tijden moeten in de lokale SERVER tijd zijn en door spaties worden gescheiden van de andere instellingen.
</small>

!exit
