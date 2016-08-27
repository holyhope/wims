!set wims_module_log=error: $error

!default name_passsup=$wims_name_Password ($name_sup)
!default name_password=$wims_name_Password ($name_classesss)
!default wims_name_institution=$name_Name_portal
!default wims_name_description=$wims_name_name $name_classesss

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
  <div class="wimscenter">La contraseña se envió a la dirección electrónica $sendmail.
  </div>

 !endif
 !if $regpass!=$empty
  Lo sentimos, su contraseña no es correcta. Vuelva a intentarlo.
 !else
  !set cname=!item $cltype+1 of clases virtuales,,agrupaciones de clases,,\
        portales de centro
  La creación de $cname en este sitio está protegida por una contraseña.
  Debe introducir esta contraseña antes de continuar.
 !endif

 !form reply
  <input type="hidden" name="step" value="0" />
  Introduzca la contraseña: <input size="16" name="regpass" type="password" />

!formend
 <div>
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

 !form reply
  <table class="wimscenter wimsnoborder">
  <tr><td style="text-align:right">
  Introduzca el nombre de su cuenta:</td><td><input size="20" name="regid" /></td>
  </tr><tr><td style="text-align:right">
  Y la contraseña:</td><td><input size="16" name="regpass" type="password" />
  <input type="submit" value="$wims_name_tosave" /></td>
  </tr></table>

!formend

 Nota. Por favor escriba al
 !mailurl $wims_site_manager administrador\
Contraseña para la creación de clases virtuales
 de este sitio si desea una cuenta con permisos para la creación de
 clases virtuales.
 </p>
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
asegurado (<span class="tt wims_code_words">$secure</span>)&nbsp;! Es un error probablemente
que tendría la consecuencia de prohibirles el acceso de control de su clase.
 <p>
Lea atentamente la documentación siguiente. Si no comprenden todavía,
dejan este campo vacío (se les enviarán códigos secretos temporales
para las operaciones sensibles), o ponen la palabra <tt class="wims_code_words">all< /tt>
para desactivar esta medida de seguridad.

 </p><hr />
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
 El campo de datos <span class="tt wims_code_words">$(wims_name_$(error_subject))</span> parece demasiado corto.
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
 </p>
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
 Su $(name_$(error_subject)) contiene caracteres ilegales.
 Por favor utilice una contraseña que contenga únicamente cifras o letras
 sin acentos y sin espacios entre ellas.
 !exit
!endif

!if bad_code=$error
 No ha tecleado la clave correcta para la clase. ¿Es correcta la dirección
 electrónica que nos ha proporcionado?<p>
 Este fallo ha quedado registrado.
 </p>
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
</p>
 !exit
!endif

!if duplicate=$error
 Ha intentado volver a crear una clase ya creada. ¿Quizás ha hecho click
 en el botón <span class="tt">actualizar</span>? En todo caso ya existe su clase
 $classname y esta segunda tentativa de creación se ha ignorado.
  <div>
 !read adm/lang/links.phtml.$modu_lang
 </div>
 !exit
!endif

!if classdontexists=$error
 Cette classe n'existe pas.
 !exit
!endif

!if notexempleclass=$error
 Cette classe n'est pas une classe d'exemple : impossible de la copier.
 !exit
!endif

!if badcpmethod=$error
 Méthode de copie impossible à identifier. Recommencer l'opération. Si l'erreur persiste contacter l'administrateur du serveur.
 !exit
!endif

!if cloningnotallow=$error
 La duplication de cette classe n'est pas autorisée par son administrateur.
 !exit
!endif

!if badcloningpwd=$error
 Mauvais mot de passe de duplication.
 !exit
!endif

!if disallowcloning=$error
 Aucune duplication de cette classene peut être réalisée.
 !exit
!endif

!msg $error

