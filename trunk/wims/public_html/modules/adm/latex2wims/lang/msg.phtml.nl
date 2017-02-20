<b>$wims_name_Error</b>.

!if fichier iswordof $error
 U moet wel tenminste één latex bestand invoeren.
 !reset error
!endif

!if document iswordof $error
U moet de naam van een bestaand document binnen uw Modtool account opgegeven.
  !reset error
!endif

!if principal iswordof $error
 Selecteer het [main] hoofdbestand.<br />
 Dit moet een geldig latex  *.tex bestand zijn.
 !reset error
!endif

!if documentempty iswordof $error
 Eerst een module van het type "document" aanmaken in "Modtool".
 !reset error
!endif

!msg $error
!reset error
