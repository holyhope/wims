
!set wims_module_log=error: $error $wims_class

<b>$wims_name_Error</b>.

!if not_secure iswordof $error
 !if $code!=$empty
 Incorrecte geheime code.
 !else
 Deze module is alleen bereikbaar voor een "secure host".
 !endif
Toegang geweigerd !
 !exit
!endif

!if checkhost iswordof $error
Uw huidige ipadres staat niet in de nieuwe lijst van "secure hosts".
Waarschijnlijk is dit een klein foutje.
En ik zal dus de "secure host" datalijst niet bijwerken.
 !exit
!endif

!if bad_file iswordof $error
Helaas, maar ik kan de <em>$wims_deposit</em> file niet als een klas backup archief bestand identificeren.
Of er is  een verkeerd bestand gestuurd of het backup archief zelf is corrupt.
 
 !exit
!endif

!if empty_file iswordof $error
Er is geen backup archief aangetroffen in uw bestand 
<span class="tt wims_fname">$wims_deposit</span>.
 !exit
!endif

!if no_upload iswordof $error
De gestuurde data zijn ongeldig ! Probeer het nog eens.
 !exit
!endif

!if remote_sharing iswordof $error
Een "buurt-klas" deelt enkele bronnen uit uw klas.<br />
U kunt alleen wijzigingen aanbrengen in materiaal dat niet gedeeld wordt met anderen.<br />
Voor beide klassen moet U de deling van materiaal beeindigen.
 !exit
!endif

!if share_dep iswordof $error
 Het delen van materiaal moet wel de afhankelijkeheden respecteren: voordat er 
 !if sheet iswordof $error 
  oefeningen uit werkbladen gedeeld kunnen worden.
 !else 
  !if exam iswordof $error 
   oefeningen en werkbladen uit examens gedeeld kunnen worden.
  !else 
   !if livret iswordof $error 
    oefeningen en werkbaden voor de vereiste raport competenties gedeeld kunnen worden.
   !endif 
  !endif 
 !endif
!exit 
!endif

!if stopshare_dep iswordof $error
 Voordat gedeeld materiaal be&iuml;ndigd kan worden, moeten wel de afhankelijkeheden gerespecteerd worden : 
 !if sheet iswordof $error 
  denk aan proefwerken en raport competenties en hun bijhorende werkbladen.
 !else 
  !if exo iswordof $error 
   denk aan werkbladen en de bijhorende oefeningen.
  !endif 
 !endif 
 !exit 
!endif

!if not_neighbor iswordof $error
U hebt geen erkende buurklassen. 
 <br />
Besef goed dat een klas pas echt een buur klas is als dit door <b>beide</b> klassen wordt erkend !


 !exit
!endif

!if localmirror iswordof $error
Het spiegelen/kopieren van een klas op de zelfde server heeft geen nut! 
 !exit
!endif

!if toobigfile iswordof $error
 Het bestand is te groot: de ingestelde limiet is 12K.
 !exit
!endif

!msg $error

