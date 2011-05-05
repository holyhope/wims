!set wims_module_log=error: $error
<b>$wims_name_Error</b>.
!if $error iswordof toomanycomp
  !goto $error
!else
 !msg $error
 !exit
!endif

:toomanycomp
 No pueden añadir más competencias, el límite es de $maxcomp !
!exit
