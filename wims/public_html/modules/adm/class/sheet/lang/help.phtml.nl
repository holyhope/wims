!goto $wims_read_parm
!exit

:dependancies

<center><b>$(name_shtab[6])</b></center>
  De cijfer afhankelijkheden wil zeggen:<br>
  een student moet eerst de gewenst score hebben behaald voordat de volgende opdracht mag worden gedaan.
  [drempel]
  Bijvoorbeeld:
  <font color=blue><tt>1:50,2:30,3+4+5:60</tt></font>
  betekend: de student moet 50% van de opdracht 1 goed hebben,
  30$ van opdracht 2 en een gemiddelde score van 60% over de opdrachtwn 3,4 en 5
!exit

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

:sheetpage

<center><b>Het gebruik van een document als werkblad presentatie pagina</b></center>

Het is ook mogelijk het adres van een document blok
(zoals <tt>c1/main</tt>) als presentatie pagina voor een werkblad te gebruiken.
Het document zelf hoeft niet op "leesbaar" voor studenten te staan.
<p>
Dit veld niet invullen als de standaard werkblad presentatie wordt gebruikt.
<p>
Links naar de individuele oefeningen moeten worden gedefinieerd met het commando
<tt>\exercise</tt>.
De volgende variabelen zijn ook bruikbaar :
<ul>
 <li><tt>\scorerequire</tt> Het minimaal vereiste punten aantal voor een oefening
 <li><tt>\scoregot</tt> Het aantal verkregen punten van de student voor elke oefening
 <li><tt>\scoremean</tt> De gemiddelde score van de student voor elke oefening
 <li><tt>\expiration</tt> De einddatum van dit werkblad , yyyymmdd
 <li><tt>\today</tt> De datum [vandaag], yyyymmdd
</ul>
