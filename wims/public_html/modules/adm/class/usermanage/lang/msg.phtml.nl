!set wims_module_log=error: $error

<span class="wims_warning">$wims_name_Error</span>.

!if not_supervisor=$error
Helaas, deze handeling is alleen voor de supervisor van een klas bedoeld. 
 !exit
!endif

!if bad_classpass=$error
Helaas, U hebt niet het juiste wachtwoord ingevuld.
U kunt dus de gegevens niet wijzigen. 
 !exit
!endif

!if bad_user=$error
De student <span class="tt wims_login">$checkuser</span> komt niet voor in de database.
!exit
!endif

!msg $error

