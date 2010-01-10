!goto $wims_read_parm
!exit

:dependancies

<center><b>Score drempels</b></center>
Een student moet eerst de gewenst score hebben behaald voordat de volgende opdracht mag worden gedaan.[drempel] <br>
Bijvoorbeeld:<font color=blue><tt>1:50,2:30,3+4+5:60</tt></font> betekend:
de student moet 50% van de opdracht 1 goed hebben,30% van opdracht 2 en een gemiddelde score van 60% over de opdrachten 3,4 en 5

!exit

:allowtype

<center><b>Cijfer registratie</b> </center>

In de selectieve mode, kan de cijfer registratie worden ingesteld via openings- en sluitingstijden.
Voeg de woorden <font color=blue><b><tt>&gt;aaaammjj.hh:mm</tt></b></font>
(de openingstijd voor cijfer registratie) en/of <font color=blue><b><tt>&lt;aaaammjj.hh:mm</tt></b></font> (de sluitingstijd voor cijfer registratie).<br>
Deze tijden moeten wel in de lokale tjd van de SERVER zijn en onderling gescheiden door spaties

