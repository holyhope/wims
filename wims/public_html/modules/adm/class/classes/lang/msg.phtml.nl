!set wims_module_log=ERROR $error

<b>Fout</b>.

!if $error=bad_password
Het wachtwoord is afgekeurd. Probeer na een paar seconden opnieuw.<br> 
 <form action="#" name=chrono>
 <b><font color=red>Attentie</font></b>! 
 Elk wachtwoord dat binnen de volgende 5 seconden wordt ingevuld, wordt afgekeurd !
 
 <input size=1 name=clock> </form>
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


