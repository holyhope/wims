<p>
<b>$wims_name_Error</b>.
</p>
!if fichier iswordof $error
 U moet wel tenminste één latex bestand invoeren.
!endif

!if document iswordof $error
U moet de naam van een bestaand document binnen uw Modtool account opgegeven.

!endif

!if principal iswordof $error
 Selecteer het [main] hoofbestand.<br />
 Dit moet een geldig latex  .tex bestand zijn.
 
!endif

!reset error
