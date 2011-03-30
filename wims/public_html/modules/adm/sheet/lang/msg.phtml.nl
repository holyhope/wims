
!set wims_module_error=error: $error

<b>$wims_name_Error</b>.

!if bad_sheet iswordof $error
 Ongeldige naam voor een werkblad.
 !exit
!endif

!if too_many_print iswordof $error
U hebt te veel verzoeken gedaan tot het aanmaken van een printer versie 
 !href cmd=reply&job=read $wims_name_back2
 !exit
!endif

