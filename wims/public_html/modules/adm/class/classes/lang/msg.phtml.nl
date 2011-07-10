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

!if $error=no_cgu
 Vous n'avez pas accepté les confitions générales d'utilisation de ce serveur.
 Vous devez d'abord accepter les CGU avant de pouvoir vous identifier.
 !form reply
  !formcheckbox agreecgu list yes prompt $name_acceptcgu
  .[
  !href cmd=help $name_seecgu
  ]
  !let save_logincgu=$auth_user
  <br>
  <input type="submit" value="$wims_name_tosave">
 </form>
 !exit
!endif

!msg $error


