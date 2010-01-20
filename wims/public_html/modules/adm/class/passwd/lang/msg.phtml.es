!if $wims_module_log=$empty
 !set wims_module_log=error: $error
!endif

!if not_supervisor=$error
 Lo sentimos, pero sólo los profesores están autorizados a cambiar la
 contraseña de la clase.
 !exit
!endif

!if not_secure=$error
 Lo sentimos, pero la contraseña de una clase sólo se puede modificar
 en conexiones desde estaciones de trabajo seguras. Por favor utilice
 !href module=adm/class/config la herramienta de configuración de la clase
 para definir estaciones de trabajo seguras, y conéctese desde una de ellas
 para cambiar esta contraseña.
 !exit
!endif

!if bad_class=$error
 ¡Qué extraño, he encontrado que su clase no es válida!
 !exit
!endif

!if discord iswordof $error
 El cambio de contraseña ha sido rechazado: la nueva contraseña no
 coincide.
 !exit
!endif

!if bad_pass=$error
 Su nueva contraseña contiene caracteres ilegales.<p>
 Por favor utilice una contraseña que sólo contenga cifras o letras sin
 acentos ni espacios entre ellas.
 !exit
!endif

!if bad_class_password iswordof $error
 ¡La contraseña actual no es correcta!<p>
 ¿Es usted de verdad el profesor de esta clase?
 !exit
!endif

!if bad_user iswordof $error
 Fallo: no hay ningún participante con el nombre de <tt>$part</tt>
 en la clase.
 !exit
!endif

!if bad_user_password iswordof $error
 ¡La contraseña actual no es correcta!<p>
 El cambio de contraseña ha sido rechazado.
 !exit
!endif

!if success iswordof $error
 La contraseña ha sido modificada.
 !exit
!endif

!if fail iswordof $error
 El programa no ha podido grabar su nueva contraseña.
 Se trata de un error interno; por favor contacte con el administrador del sitio.
 !exit
!endif

!if too_long iswordof $error
 Error: la nueva contraseña es demasiado larga.
 !exit
!endif

!if too_short iswordof $error
 Error: la nueva contraseña es demasiado corta.
 !exit
!endif

!if nothing_to_do iswordof $error
 No se ha realizado ninguna acción porque la nueva contraseña es igual a la antigua.
 !exit
!endif
