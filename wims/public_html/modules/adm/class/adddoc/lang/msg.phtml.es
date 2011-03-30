!set wims_module_log=error: $error

!if $error iswordof already_exist
  !goto $error
!else
 !msg $error
 !exit
!endif

:already_exist
 Le document que vous voulez insérer existe déjà dans votre classe.
!exit
