!if $rounding=-1
    roundingtext=
    !exit
!endif
###afronding 
!if $rounding=0
    roundingtext=Ik verwacht hier een <em>exact</em> antwoord<br />Let op: <b>1/3</b> i.p.v. 0.333 en <b>sqrt(2)</b> i.p.v. 1,414
    !exit
!endif

!if $rounding=1000000
    roundingtext=Je mag hier afgeronde antwoorden geven<br />Bereken dan zo nauwkeurig mogelijk met je grafische rekenmachine<br />En geef je eindantwoord in tenminste <b>twee decimalen nauwkeurig</b> op.
    !exit
!endif

!if $rounding=100000
    roundingtext=Je mag hier afgeronde antwoorden geven<br />.Rond in dat geval je antwoord af op tenminste <b>vijf</b> decimalen nauwkeurig af.
    !exit
!endif

!if $rounding=10000
    roundingtext=Je mag hier afgeronde antwoorden geven.<br />Rond in dat geval je antwoord af op tenminste <b>vier</b> decimalen nauwkeurig af.
    !exit
!endif

!if $rounding=1000
    roundingtext=Je mag hier afgeronde antwoorden geven.<br />Rond in dat geval je antwoord af op tenminste <b>drie</b> decimalen nauwkeurig af.
    !exit
!endif

!if $rounding=100
    roundingtext=Je mag hier afgeronde antwoorden geven.<br />Rond dan je antwoord  op tenminste <b>twee</b> decimalen nauwkeurig af.
    !exit
!endif

!if $rounding=10
    roundingtext=Je mag hier afgeronde antwoorden geven.<br />Rond dan je antwoord op tenminste <b>&eacute;&eacute;n</b> decimaal nauwkeurig af. 
    !exit
!endif
!if $rounding=1
	roundingtext=Je mag hier afgeronde antwoorden geven.<br />Rond dan je antwoord af op <b>een geheel getal</b>.
    !exit
!endif	
	
	
