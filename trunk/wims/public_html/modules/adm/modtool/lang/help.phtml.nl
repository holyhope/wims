!if $special_parm!=$empty
 !read help/$special_parm.phtml
 !goto end
!endif

!if $login=$empty
<p>
 Dit is een hulpmiddel voor het online ontwikkelen van complete WIMS modules.
 </p><p>
 Een dergelijke module kan een "full-power" oefening zijn
 (vergeleken met de Createxo OEF oefeningen; welke gemakkelijker te maken zijn,
  maar hierdoor natuurlijk ook iets aan mogelijkheden inboeten.
  Zie hiervoor
 !href module=adm/createxo Createxo
 ) of bijvoorbeeld een zeer speciale wiskundige toepassing.
 Deze modules worden geschreven in de <b>WIMS programeertaal</b> [phtml] zoals beschreven in de
 !href target=wims_help module=help/wimsdoc WIMS technische documentatie
.
 </p><p>
 Als U geinteresseerd bent, kan via
 !mailurl $wims_site_manager de systeembeheerder\
 WIMS Modtool id

 een ontwikkelaars account (login naam en wachtwoord) worden aangevraagd.
 </p>
 !exit
!endif

!if $mod=$empty
<p>
 Om aan een module te kunnen werken, moeten we er wel eerst eentje aanmaken.
 Voor het maken van een nieuwe module, moet U dus op de juiste links klikken
 en alle benodigde module administratie invoeren.
 </p>
!endif
<p>
Lees eerst de
 !href target=wims_help module=help/wimsdoc WIMS technische documentatie
 voor de structuur van zo'n WIMS module en uiteraard de syntax van de WIMS programmeertaal.
</p><p>
Speciale hints:
</p>
<ol>
<li>Om een file te kunnen debuggen, plaats dan de regel
<pre>
$!debug ...
</pre>
in deze file ; <b>...</b> kan elke tekst-string zijn.
Wanneer U nu deze module uittest, stopt de uitvoering van Uw programma precies
op deze regel, en laat U dan de inhoud van <b>...</b> zien.
Is <b>...</b> een variabele, wordt deze gesubstitueerd volgens de normale WIMS substitutieregels.

</li></ol>

:end
