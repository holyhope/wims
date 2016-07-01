!if $wims_read_parm!=$empty
 !goto $wims_read_parm
!else
 Geen help-pagina aanwezig.
 !exit
!endif

:listvar
Met deeze module kunnen techniosche variabelen worden gedeklareerd:
<ul>
 <li> aanmaken  van technische variabelen (maximaal $MAXtechvar) ;</li>
 <li> varanderen van de lijst met waarden voor deze variabelen ;</li>
 <li> inzien en veranderen van de technische variabelen voor elke deelnemer;</li>
</ul>
<br/>

Er zijn een tweetal types technische variabelen :
<ul>
 <li> Lokale variabelen : deze kan een docent aanmaken en veranderen (maixmumaal aantal $MAXtechvar).</li>
 <li> Globale variabelen : deze variabelen horen de hele school of instituut waar uw klas onderdeel van is. Deze variabelen zijn alleen veranderbaar door de supervisor van de school of instituut.Als docent kun u deze globale variabelen wel gebruiken (om te filteren etc)</li>
</ul>

!exit

