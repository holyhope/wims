!set wims_module_log=error: $error

!if $error iswordof already_exist baddocnumber not_supervisor insert_fail
  !goto $error
!else
 !msg $error
 !exit
!endif

:already_exist
    Het document dat u wilt toevoegen , bestaat reeds in uw klas.
!exit

:baddocnumber
 Les informations que vous avez saisies ne correspondent pas à un document enregistré de la classe.
!exit

:not_supervisor
Seul l'administrateur de la classe peut mener cette action.
!exit

:insert_fail
vous essayez d'insérer un module non autorisé.
!exit
