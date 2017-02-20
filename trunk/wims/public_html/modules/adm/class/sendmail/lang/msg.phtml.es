!set wims_module_log=error: $error

!if error=nosupervisoremail
  No indicaron correo electrónico. No les es pues posible enviar un correo electrónico.
 !exit
!endif

!if empty_msg=$error
 ¡Su mensaje es vacío!
 !exit
!endif

!if empty_user=$error
 No seleccionaron a ningún participante. Compruebe los filtros.
 !exit
!endif

!if empty_mailuser=$error
 Ningún de los participantes seleccionados tiene correo electrónico
 !exit
!endif

!if noclass=$error
 Vous n'êtes pas identifié dans une classe. Ne jouez pas avec la barre d'adresse du navigateur !
 !exit
!endif

!if notsupervisor=$error
 Vous n'êtes pas l'enseignant de cette classe. Ne jouez pas avec la barre d'adresse du navigateur !
 !exit
!endif

!msg $error
