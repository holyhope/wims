!set wims_module_log=ERROR $error

<span class="wims_warning">$wims_name_Error</span>.

!if $error=bad_password
Het wachtwoord is afgekeurd. Probeer na 5 seconden opnieuw.<br> 
 <form action="#" name="chrono">
 <span class="wims_warning">$wims_name_warning</span>! 
 Elk wachtwoord dat binnen de volgende 5 seconden wordt ingevuld, wordt afgekeurd !
 
 <input size=1 name="clock"> </form>
 !exit
!endif

!if $error=in_exam
Je kan niet van klas veranderen tijdens een overhoring !
 !exit
!endif

!if $error=recent_rafale
Dit account is i.v.m. verdachte activiteiten, voor 10 minuten geblokkeerd ! 
 !exit
!endif

!msg $error


