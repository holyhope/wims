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
    De algemene voorwaarden voor het gebruik van deze server zijn nog niet geaccepteerd.
    Geef eerst goedkeuring aan deze algemene voorwaarden: 
 !form reply
  !formcheckbox agreecgu list yes prompt $name_acceptcgu
  [
  !href cmd=help $name_seecgu
  ]
  !let save_logincgu=$auth_user
  <center>
  <input type="submit" value="$wims_name_tosave">
  </center>
 </form>
 !exit
!endif

!if $error=bad_loginmail
 Votre identifiant n'est pas reconnu ou vous n'avez pas défini d'adresse électronique lors de votre inscription. 
 <br>
 Demandez à votre enseignant de vous attribuer un nouveau mot de passe.
 <form action="#" name="chrono">
 <span class="wims_warning">$wims_name_warning</span> ! Cette procédure de récupération de mot de passe est désactivée pendant 5 secondes &nbsp;!
 <input size=1 name="clock"> </form>
 !exit
!endif

!msg $error


