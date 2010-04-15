!set wims_module_log=error: $error

!if not_supervisor=$error
 Lo sentimos, pero la operación de preparación / modificación de una hoja
 de trabajo está reservada a los profesores registrados de una clase.
 !exit
!endif

!if bad_class=$error
 Extraño, ¡encuentro que su clase no es válida!
 !exit
!endif

!if $error=no_sheet
 El contenido de un examen debe estar tomado de hojas de trabajo
 activadas (activas o caducadas).
 <p>
 Su clase no tiene aún hojas de trabajo activadas. Por favor, defina
 su hoja de trabajo, ponga los trabajos en ellas y actívelas, antes de
 definir un examen para la clase.
 !exit
!endif

!if bad_exam=$error
 Su número de examen no es válido. ¿Error de software?
 !exit
!endif

!if $error=simuchange
 Esta hoja de examen acaba de cambiar de estado. Por favor
 !href cmd=reply&job=scorereg pulse aquí
 para dar fin a su sesión.
 !exit
!endif

!if already_registered=$error
 Su puntuación ya ha sido registrada.
 !exit
!endif

!if no_more_registration=$error
 Este examen le permite registrar su puntuación en solamente $tries intentos.
 No puede hacer más registros.
 !exit
!endif

!if bad_source=$error
 El número de elemento $bad_source en el fichero fuente que ha enviado no es válido.
 !href cmd=reply&job=prep_putsource&source=$source Corrija los fuentes
 .
 !exit
!endif

!if no_title=$error
 Quiere registrar un examen sin título, lo cual no está permitido.
 ¿Error de manipulación?
 !exit
!endif

!if prep_activate=$error
 Ha solicitado activar el examen $exam, es decir, hacerlo accesible a los
 participantes de la clase. <p>
 Por favor, tenga en cuenta que, una vez activado, no podrá modificar el
 examen. ¿Desea continuar?
 <p><center>
 !href cmd=reply&job=activate Sí, activar
 .&nbsp;&nbsp;
 !href cmd=resume No, cancelar
 .</center>
 !exit
!endif

!if prep_erase=$error
 ¿Confirma que quiere borrar este examen #$exam ($title)?
 <p><center>
 !href cmd=reply&job=erase Sí, borrar
 .&nbsp;&nbsp;
 !href cmd=resume No, cancelar
 .</center>
 !exit
!endif

!if prep_expire=$error
 Este examen número $exam ($title) normalmente expira el $expday
 !item $expmon of $months
 $expyear. ¿Quiere hacerlo expirar ahora?
 <p><center>
 !href cmd=reply&job=expire Sí, expirar
 .&nbsp;&nbsp;
 !href cmd=resume No, cancelar
 . </center>
 <p><b>Observación.</b> Sus estudiantes no pueden continuar trabajando en un
 examen que ha expirado. Pero sus puntuaciones anteriores se conservarán (y se
 tomarán en cuenta en las estadísticas), y siempre podrá consultar estas
 puntuaciones.
 !exit
!endif

!if prep_putsource=$error
 Si tiene el código fuente de un examen salvado anteriormente, puede insertar
 estos fuentes en su examen actual, copiándolos en la siguiente
 ventana, y pulsando entonces en el botón `Enviar'.
 <p>
 De lo contrario,
 !href cmd=resume Volver a la página principal del examen.
 !form reply
 <input type=hidden name="job" value=putsource><center>
 <textarea cols=55 rows=10 name="source">$source</textarea>
 <p><input type=submit value="Enviar">
 </center></form>
 <b>Advertencia</b>. ¡No inserte fuentes modificados! Corre el riesgo de
 inutilizar su examen.
 !exit
!endif

!if nodeactivate=$error
  ¡Desactivarse el examen no puede ya que
  !if badstructure isin $deactivate
  la  estructura de su clase no lo permite!.
  !else
   !if score isin $deactivate
    participantes ya comenzaron a trabajar sobre este examen!
   !else
    comparten sus exámenes con otra clase !
   !endif
  !endif
!endif

!if active_exam=$error
   Afligido, este examen esta activado, por lo tanto no modificable. No se pueden cambiar más los ejercicios dentro.
!exit
!endif

!if $error=prep_noexercise
  El contenido del ejercicio $exo del examen es vacío. Empiece de nuevo.
  !exit
!endif
