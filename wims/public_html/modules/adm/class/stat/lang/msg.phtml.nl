!set wims_module_log=error: $error

!if not_supervisor=$error
 Helaas, het maken en veranderen van een werkblad is alleen voor de supervisor van een klas.
 !exit
!endif

!if bad_class=$error
 Vreemd, ik zie dat deze klas niet geldig is !
 !exit
!endif

