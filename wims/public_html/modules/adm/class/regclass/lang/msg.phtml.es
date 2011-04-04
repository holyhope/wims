!set wims_module_log=error: $error

!if no_subclass iswordof $error
 No está autorizado para crear subclases en la situación actual.
 !set restart=no
 !exit
!endif

!if no_right iswordof $error
 Lo sentimos, no está autorizado a crear clases virtuales en este sitio.
 Por favor
 !mailurl $wims_site_manager contacte con el administrador del sitio\
Creación de una clase virtual
 para recibir más información.
 !set restart=no
 !exit
!endif

!if not_manager iswordof $error
 Lo sentimos, sólo el administador del sitio está autorizado para
 crear un portal de centro educativo.
 !exit
!endif

!if getpass iswordof $error
 !if $sendmail!=$empty
  <font size="+1"><center>La contraseña se envió a la dirección electrónica $sendmail.</center></font>
  <p>
 !endif
 !if $regpass!=$empty
  Lo sentimos, su contraseña no es correcta. Vuelva a intentarlo.
 !else
  !set cname=!item $cltype+1 of clases virtuales,,agrupaciones de clases,,\
        portales de centro
  La creación de $cname en este sitio está protegida por una contraseña.
  Debe introducir esta contraseña antes de continuar.
 !endif
 <p>
 !form reply
  <input type="hidden" name="step" value="0">
  Introduzca la contraseña: <input size="16" name="regpass" type="password">
 </form> <p>
 Nota. Puede solicitar la contraseña necesaria para la creación
 de clases virtuales al
 !mailurl $wims_site_manager administrador\
Contraseña para la creación de clases virtuales
 de este sitio WIMS.
 !set restart=no
 !exit
!endif

!if getid iswordof $error
 !if $regpass$regid!=$empty
  Lo sentimos, su contraseña no es correcta. Vuelva a intentarlo.
 !else
  La creación de clases virtuales en este sitio está protegida por un
  sistema de autentificación. Identifíquese por favor.
 !endif
 <p>
 !form reply
  <p><table border="0" cellspacing="5">
  <tr><td align="right">
  Introduzca el nombre de su cuenta:</td><td><input size="20" name="regid"></td>
  </tr><tr><td align="right">
  Y la contraseña:</td><td><input size="16" name="regpass" type="password">
  <input type="submit" value="De acuerdo"></td>
  </tr></table>
 </form> <p>
 Nota. Por favor escriba al
 !mailurl $wims_site_manager administrador\
Contraseña para la creación de clases virtuales
 de este sitio si desea una cuenta con permisos para la creación de
 clases virtuales.
 !set restart=no
 !exit
!endif

!if class_quota=$error
 Está autorizado a instalar hasta un total de $r_quota1 clases. Ha llegado
 al total; ya no puede añadir más.
 !set restart=no
 !exit
!endif

!if bad_secure=$error
 ¡Su puesto actual no forma parte de su definición de acceso
asegurado (<tt>$secure</tt>)&nbsp;! Es un error probablemente
que tendría la consecuencia de prohibirles el acceso de control de su clase.
 <p>
Lea atentamente la documentación siguiente. Si no comprenden todavía,
dejan este campo vacío (se les enviarán códigos secretos temporales
para las operaciones sensibles), o ponen la palabra <tt>all< /tt>
para desactivar esta medida de seguridad.

 <p><hr><p>
 !read help/hosts.phtml
 !reset secure
 !exit
!endif

!if has_empty=$error
 No ha proporcionado todas las informaciones necesarias para la creación
 de una clase. Por favor complete sus datos antes de enviarlos.
 !exit
!endif

!if too_short=$error
 El campo de datos ``$(name_$error_subject)'' parece demasiado corto.
 !exit
!endif

!if bad_date=$error
 La fecha de expiración no es correcta.
 !exit
!endif

!if anti_date=$error
 Su clase tiene una fecha de expiración anterior a la de hoy. ¡Habría
 expirado antes de ser creada!
 !exit
!endif

!if bad_level=$error
 Valor de nivel incorrecto.
 !exit
!endif

!if bad_email=$error
 Su dirección de correo electrónico es visiblemente inválida.
 <p>
La creación de clases sólo puede tener éxito si
 proporciona SU VERDADERA dirección de correo.
 !exit
!endif

!if existing=$error
 La clase $classname parece que ya existe. No puede volver a crear la
 misma clase.
 !exit
!endif

!if pass_discord=$error
 La contraseña que ha vuelto a teclear no se corresponde con la primera.
 En consecuencia no se ha realizado la creación de la clase; puede volver a
 intentarlo.
 !exit
!endif

!if bad_pass=$error
 Su $(name_$error_subject) contiene caracteres ilegales. <p>
 Por favor utilice una contraseña que contenga únicamente cifras o letras
 sin acentos y sin espacios entre ellas.
 !exit
!endif

!if bad_code=$error
 No ha tecleado la clave correcta para la clase. ¿Es correcta la dirección
 electrónica que nos ha proporcionado?<p>
 Este fallo ha quedado registrado.
 !exit
!endif

!if define_fail=$error or abuse=$error
 El servidor no ha podido añadir su clase a la base de datos.
 Se trata de un error interno del programa.
 <p>
 Por favor informe del problema al
 !mailurl $wims_site_manager administrador de este sitio\
user registration failure
. ¡Gracias!
 !exit
!endif

!if duplicate=$error
 Ha intentado volver a crear una clase ya creada. ¿Quizás ha hecho click
 en el botón <tt>actualizar</tt>? En todo caso ya existe su clase
 $classname y esta segunda tentativa de creación se ha ignorado. <p>
 !read lang/links.phtml.$modu_lang
 !exit
!endif

