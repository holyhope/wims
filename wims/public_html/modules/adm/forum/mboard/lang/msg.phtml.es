!! This file contains error messages. It will be processed
!! whenever the variable `error' is not empty.

!set errorhead=<b>Error.</b>

!if forum_not_exist = $error
 $errorhead Ha solicitado un foro de discusión que no existe.
 Lo sentimos.
 !set fatal=yes
 !exit
!endif

!if no_read_right = $error
 $errorhead No está autorizado a acceder a este foro de discusión.
 Lo siento.
 !set fatal=si
 !exit
!endif

!if no_subject = $error
 $errorhead Por favor, añada un tema a su mensaje.
 !exit
!endif

!if translation_fail = $error
 $errorhead El software haencontrado un error interno y es incapaz de
 interpretar su mensaje. Lo sentimos.
 !if $wims_exec_error!=$empty
  <p>
  Tipo de error: <tt>$wims_exec_error</tt>
 !endif
 !exit
!endif

!if open_tag = $error
 <b>Aviso.</b>
 Su mensaje parecer acabar en una etiqueta html no cerrada. Por
 favor, compruebe el texto que escribe con cuidado. <p>
 Su mensaje se mostrará como un archivo html. Así, si está escribiendo
 desigualdades, por favor ponga un espacio después del signo `&lt;', o
 proteja las desigualdades como fórmulas matemáticas
 (encerrándolas entre el par de paréntesis \( y \) ).
 !exit
!endif

!if bad_message = $error
 $errorhead El mensaje que quería leer no existe en este foro de
 discusión. Por favor, compruebe su petición.
 !exit
!endif

!if erased_message = $error
 $errorhead El mensaje que quería leer ha sido borrado.
 !exit
!endif

!if $error=no_send_right
 $errorhead No tiene autorización para enviar un mensaje a este foro.
 Lo sentimos.
 <p>
 !href cmd=reply&job=list&mlist=.newlist Lista de mensajes.
 !exit
!endif

!if $error=email_required
 $errorhead Debe dar su dirección de correo para poder enviar un mensaje
 a este panel.
 <br>
 <b>ATENCIÓN.</b> ¡El servidor verificará esta dirección! Por lo tanto, no
 dé una dirección falsa.
 !set job=compose
 !exit
!endif

!if $error=bad_email
 $errorhead No dió una dirección de correo válida. Por favor,
 corríjala.
 !set job=compose
 !exit
!endif

!if $error=bad_sendcode
 $error_head Su mensaje no ha sido aceptado porque la clave secreta que
 escribió no es correcta.
 <p>
 Por favor, verifique la dirección de correo que ha dado, pulse en el botón
 `enviar' otra vez, y después espere a que le llegue una NUEVA clave
 secreta por correo electrónico.
 !set job=compose
 !exit
!endif

!if $error=not_owner
 $error_head Solamente el propietario de un foro de discusión está autorizado a
 configurarlo.
 <p>
 !set job=list
 !exit
!endif

!if auth_failure = $error
 $errorhead Fallo de autentificación. <p>
 !set fatal=yes
 !exit
!endif

!msg $error

