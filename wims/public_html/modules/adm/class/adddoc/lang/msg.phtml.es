!set wims_module_log=error: $error

!if $error iswordof already_exist
  !goto $error
!else
 !msg $error
 !exit
!endif

:already_exist
 El documento que desea insertar ya existe en la clase.
!exit
