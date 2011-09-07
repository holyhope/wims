!set wims_module_log=ERROR $error

<span class="wims_warning">$wims_name_Error</span>.

!if $error=bad_password
 Contraseña no reconocida. Por favor vuelva a intentarlo pasados unos segundos.
 <form action="#" name="chrono">
 ¡<span class="wims_warning">$wims_name_warning</span>! ¡Cualquier contraseña enviada en los próximos 5 segundos
 será rechazada!
 <input size=1 name="clock"> </form>
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
  <center>
  <input type="submit" value="$wims_name_tosave">
  </center>
 </form>
 !exit
!endif

!msg $error

