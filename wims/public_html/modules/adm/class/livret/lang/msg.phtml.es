!set wims_module_log=error: $error
<b>$wims_name_Error</b>.
!goto $error
!exit

:toomanycomp
 No pueden añadir más competencias, el límite es de $maxcomp !
!exit

!msg $error