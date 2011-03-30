!set wims_module_log=error: $error

!if $error iswordof already_exist
  !goto $error
!else
 !msg $error
 !exit
!endif

:already_exist=$error
    Het document dat u wilt toevoegen , bestaat reeds in uw klas.
!exit
