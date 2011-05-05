!set wims_module_log=error: $error
<b>$wims_name_Error</b>.
!if $error iswordof toomanycomp
  !goto $error
!else
 !msg $error
 !exit
!endif


:toomanycomp
    Er kunnen geen nieuwe vaardigheden meer worden toegevoegd : de limiet is $maxcomp ! 
!exit

!msg $error