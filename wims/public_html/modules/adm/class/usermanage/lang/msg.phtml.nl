!set wims_module_log=error: $error

<span class="wims_warning">$wims_name_Error</span>.

!if not_supervisor=$error
Helaas, deze handeling is alleen voorbehouden voor de supervisor van een klas. 
 !exit
!endif

!if bad_classpass=$error
Helaas, niet het juiste wachtwoord ingevuld.
De gegevens worden niet gewijzigd. 
 !exit
!endif

!if bad_user=$error
De student <span class="tt wims_login">$checkuser</span> komt niet voor in de database.
!exit
!endif

!msg $error

