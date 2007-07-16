!if $afrondingsfactor=
    !exit
!endif    
###afronding 
!if $afrondingsfactor=0
    AFRONDING=<font size="-1">Ik verwacht hier een <em>exact</em> antwoord<br>\
    Let op: <b>1/3</b> i.p.v. 0.333 en <b>sqrt(2)</b> i.p.v. 1,414</font>
    !exit
!endif

!if $afrondingsfactor=1000000
    AFRONDING=<font size="-1" >Je mag hier afgeronde antwoorden geven<br>\
    Bereken dan zo nauwkeurig mogelijk met je grafische rekenmachine<br>\
    En geef je eindantwoord in tenminste <b>twee decimalen nauwkeurig</b> op.</font>
    !exit
!endif

!if $afrondingsfactor=10000
    AFRONDING=<font size="-1">Je mag hier afgeronde antwoorden geven<br>\
    Rond in dat geval je antwoord af op tenminste <b>vier</b> decimalen nauwkeurig af.</font>
    !exit
!endif

!if $afrondingsfactor=1000
    AFRONDING=<font size="-1">Je mag hier afgeronde antwoorden geven<br>\
    Rond in dat geval je antwoord af op tenminste <b>drie</b> decimalen nauwkeurig af.</font>
    !exit
!endif

!if $afrondingsfactor=100
    AFRONDING=<font size="-1">Je mag hier afgeronde antwoorden geven<br>\
    Rond dan je antwoord  op tenminste <b>twee</b> decimalen nauwkeurig af.</font>
    !exit
!endif

!if $afrondingsfactor=10
	AFRONDING=<font size="-1">Je mag hier afgeronde antwoorden geven<br>\
	Rond dan je antwoord op tenminste <b>&eacute;&eacute;n</b> decimaal nauwkeurig af.</font> 
    !exit
!endif
!if $afrondingsfactor=1
	AFRONDING=<font size="-1">Je mag hier afgeronde antwoorden geven<br>\
	Rond dan je antwoord af op <b>een geheel getal</b>.</font>
    !exit
!endif	
	
	
