!set wims_module_log=error: $error

!if not_supervisor=$error
    Helaas, maar alleen de docent van deze klas mag heir een bericht schrijven.
 !exit
!endif

!if bad_class=$error
    Vreemd, maar ik zie dat uw klas niet geldig is !
 !exit
!endif

!if bad_user=$error
    Vreemd, maar ik kan deze student niet vinden in uw klas !
 !exit
!endif