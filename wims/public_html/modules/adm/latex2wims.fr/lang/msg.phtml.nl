<p>
<font color=red><b>Fout.</b>
!if fichier iswordof $error
 U moet wel tenminste &eacute;&eacute;n latex bestand invoeren.
!endif

!if document iswordof $error
U moet de naam van een bestaand document binnen uw Modtool account opgegeven.

!endif

!if principal iswordof $error
 Selecteer het [main] hoofbestand.<br>
 Dit moet een geldig latex  .tex bestand zijn.
 
!endif
</font>
!reset error
