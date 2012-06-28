!set wims_module_log=error: $error

!if not_supervisor=$error
    Helaas, maar alleen de docent van deze klas mag hier een bericht schrijven.
 !exit
!endif

!if user_notconnected=$error
    Deze deelnemer is niet ingelogd !
 !exit
!endif



!msg $error
