!set wims_module_log=error: $error

!if not_supervisor=$error
 Lo sentimos, pero la operación de preparación / modificación de una hoja
 de trabajo está reservada a los profesores registrados de la clase.
 !exit
!endif

!if bad_class=$error
 ¡Es extraño, pero su clase me aparece como no válida!
 !exit
!endif

!if bad_source=$error
 El elemento número $bad_source del fichero fuente que acaba de enviar no es válido.
 !href cmd=reply&job=prep_putsource&source=$source Corrija los fuentes
 .
 !exit
!endif

!if bad_sheet=$error
 Su número de hoja de trabajo no es válida. ¿Error del software?
 !exit
!endif

!if no_title=$error
 Ha intentado grabar una hoja de trabajo sin título, lo cual no está
 permitido. ¿Error de manipulación?
 !exit
!endif

!if $error=not_secure
 Esta operación sólo puede ser realizada desde una estación de trabajo segura.
 !if $sec=$empty
  No ha definido estaciones de trabajo seguras. Acceso prohibido. Puede
  solicitar al administrador del sitio que lo haga por usted.
 !else
  Acceso prohibido.
 !endif
 !exit
!endif

!if $error=sharing_sheet
 <font color=red><b>¡¡¡Peligro!!!</b></font>
 ¡Sus hojas están siendo compartidas por otras clases!
 !if $wims_ismanager<2
  Deberá pedir al administrador del sitio que desactive la hoja
  por usted.
  !exit
 !endif
 Se arriesga a poner las clases vecinas en un desorden total si desactiva
 esta hoja. Por consiguiente esta operación está <b>fuertemente desaconsejada</b>.
 <p>
 ¿De verdad quiere desactivar la hoja?
 <p><center>
 !href cmd=reply&job=deactivate&confirm=yes $wims_name_yes; $(statutaction[3])
.&nbsp;&nbsp;
 !href cmd=resume $wims_name_no; $wims_name_giveup
. </center>
 <p>
 <b>¡Antes de continuar, pida al menos a los profesores de las clases vecinas que
 hagan copias de seguridad de sus clases!</b> Cuando los problemas aparezcan, aunque sea
 después de varios meses, estará obligado a volver al estado ANTERIOR a la
 desactivación, y perderá todo lo ocurrido DESPUÉS, ¡y esto para todas las clases
 que comparten la hoja! Esperamos haberle avisado suficientemente.
 !exit
!endif

!if $error=sheet_in_exam
 Imposible desactivar esta hoja, porque tiene exámenes 
 basados en su contenido.
 !exit
!endif

!if $error=non_empty_activities
 ¡Quiere desactivar la hoja $sheet cuando los participantes ya han empezado
 a trabajar en ella!
 <p>
 !if share iswordof $confirmed
  Además la hoja la comparten otras clases, que pueden estar trabajando en ella 
  y tener puntuaciones también. Por tanto está prohibido desactivarla.
  !exit
 !endif
 Todas las puntuaciones obtenidas en el trabajo en esta hoja quedarán borradas
 si la desactiva. ¿Está usted seguro de querer hacerlo?
 <p><center>
 !href cmd=reply&job=deactivate&confirm=yes $wims_name_yes; $(statutaction[3])
.&nbsp;&nbsp;
 !href cmd=resume $wims_name_no; $wims_name_giveup
. </center> <p>
 Lista de cuentas que ya han trabajado en esta hoja:
 <p>
 <tt>$worktest</tt>
 <p>
 <b>Nota</b>. Esta acción no debe realizarse salvo si se trata de una clase de 
 pruebas. ¡No siga adelante si los participantes son sus verdaderos alumnos!
 !exit
!endif

!if prep_activate=$error
 Ha solicitado activar la hoja de trabajo $sheet, es decir, hacerla 
 accesible a los participantes de la clase. <p>
 Por favor tenga en cuenta que, una vez activada una hoja de trabajo, no 
 puede ser modificada sin previamente desactivarla, y la desactivación de 
 la hoja conlleva la pérdida de las puntuaciones que se han conseguido en 
 el trabajo en la misma, si dicha desactivación no está prohibida 
 por la situación.
 <p>
 ¿Desea continuar?
 <p><center>
 !href cmd=reply&job=activate $wims_name_yes; $(statutaction[1])
 .&nbsp;&nbsp;
 !href cmd=resume $wims_name_no; $wims_name_giveup
 . </center>
 !exit
!endif

!if prep_erase=$error
 ¿Realmente quiere borrar la hoja de trabajo #$sheet ($title)?
 <p><center>
 !href cmd=reply&job=erase $wims_name_yes; $wims_name_erase
.&nbsp;&nbsp;
 !href cmd=resume $wims_name_no ; $wims_name_giveup
.</center>
 !exit
!endif

!if prep_expire=$error
 Esta hoja número $sheet ($title) expira normalmente el $expday
 !item $expmon of $months
 $expyear. ¿Quiere hacerla expirar ahora?
 <p><center>
 !href cmd=reply&job=expire $wims_name_yes ; $(statutaction[2])
 .&nbsp;&nbsp;
 !href cmd=resume $wims_name_no ; $wims_name_giveup
 . </center>
 <p><b>Nota.</b> Sus estudiantes no pueden continuar trabajando en una hoja
 que ha expirado. Pero las puntuaciones anteriores se conservarán (y se tomarán en 
 cuenta en las estadísticas), y puede seguir consultándolas.
 !exit
!endif

!if prep_putsource=$error
 Si tiene el fichero fuente de una hoja de trabajo guardada anteriormente, puede
 insertarlo directamente en la hoja actual, copiando estos 
 fuentes en la ventana siguiente, y pulsando después el botón <tt>Enviar</tt>.
 También puede utilizar este formulario para insertar los fuentes de una
 hoja pública por el proceso de copiar y pegar.
 <p>
 !set wims_menu_items=!append line sheetadmin,1,cmd=resume \
to $wims_menu_items

 !form reply
 <input type=hidden name=job value=putsource><center>
 <textarea cols=55 rows=10 name=source>$source</textarea>
 <p><input type=submit value="$wims_name_send">
 </center></form>
 <b>Atención</b>. ¡No inserte un fichero fuente modificado! Se arriesga a
 inutilizar su hoja de trabajo.
 !exit
!endif

!if prep_modify=$error
 !set cnt=!recordcnt wimshome/log/classes/$wims_class/sheets/.sheet$sheet
 !if $modif>$cnt or $modif<1
  Has enviado una solicitud no válida. Ignorada.
 !else
  !set exo=!record $modif of wimshome/log/classes/$wims_class/sheets/.sheet$sheet
  !changeto exomodify.phtml $exo
 !endif
 !exit
!endif

!if $error=toolate
 $name_expiration1 ($l_date). $name_expiration2

<p>
!href cmd=resume $wims_name_back2
 ($wims_name_sheetmanagement)

 !exit
!endif
!msg $error
