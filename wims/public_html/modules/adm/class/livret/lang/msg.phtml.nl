!set wims_module_log=error: $error
<b>$wims_name_Error</b>.
!goto $error
!exit

:toomanycomp
    Er kunnen geen nieuwe vaardigheden meer worden toegevoegd : de limiet is $maxcomp ! 
!exit

!msg $error