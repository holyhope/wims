!set wims_module_log=ERROR $error

!if $error=bad_password
 Contraseña no reconocida. Por favor vuelva a intentarlo pasados unos segundos.
 <form action="#" name="chrono">
 ¡<span class="wims_warning">$wims_name_warning</span>! ¡Cualquier contraseña enviada en los próximos 5 segundos
 será rechazada!
 <input size="1" name="clock" /> </form>
 !exit
!endif

!if $error=in_exam
 No puede cambiar de clase cuando está haciendo un examen.
 !exit
!endif

!if $error=recent_rafale
 Esta cuenta está bloqueada durante 10 minutos debido a actividades irregulares.
 !exit
!endif

!if $error=no_cgu
No han aceptado las condiciones generales de uso de este servidor (UGC).
Primero debe aceptar los términos de uso antes identificarle.
 !form reply
  !formcheckbox agreecgu list yes prompt $name_acceptcgu
  [
  !href cmd=help $name_seecgu
  ]
  !let save_logincgu=$auth_user
  <div class="wimscenter wimsform">
  <input type="submit" value="$wims_name_tosave" />
  </div>

!formend
 !exit
!endif

!if $error=bad_loginmail
 Votre identifiant n'est pas reconnu ou vous n'avez pas défini d'adresse électronique lors de votre inscription.
 <br />
 Demandez à votre enseignant de vous attribuer un nouveau mot de passe.
 <form action="#" name="chrono">
 <span class="wims_warning">$wims_name_warning</span> ! Cette procédure de récupération de mot de passe est désactivée pendant 5 secondes &nbsp;!
 <input size="1" name="clock" /> </form>
 !exit
!endif

!msg $error

