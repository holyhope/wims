!set wims_module_log=error: $error

!if not_supervisor=$error
    Helaas, maar alleen de docent van deze klas mag heir een bericht schrijven.
 !exit
!endif

!if user_notconnected=$error
 Ce participant n'est plus connecté !
 !exit
!endif



!msg $error
