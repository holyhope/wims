!set wims_module_log=error: $error

!if no_forum=$error
 No ha indicado en qué foro de discusión quiere inscribirse.
 <p>
 !href module=adm/forum/forum Lista de foros de discusión
.
 !exit
!endif

!if bad_forum=$error
 ¡Parece que el foro de discusión que ha elegido no existe!
 Si no se trata de un error del software, entonces el foro de discusión
 ha expirado, o usted está jugando con el sitio (en este caso, tenga en
 cuenta que sus actividades se están registrando).
 !exit
!endif

!if no_register=$error
 El foro de discusión <em>$em_title</em> no permite la inscripción
 en línea de usuarios. Por favor,
 !mailurl $mb_email contacte con su propietario
 si quiere participar.
 !exit
!endif

!if no_real=$error
 No ha dado sus apellidos y su nombre.
 !exit
!endif

!if no_email=$error
 Es obligatorio dar una dirección de correo electrónico real para poder 
 inscribirse en 
 este foro de discusión (¡el servidor verificará la dirección antes
 de autorizar la inscripción!)
 !exit
!endif

!if bad_login=$error
 Su identificador de usuario contiene caracteres ilegales. <p>
 Por favor, use una palabra que contenga únicamente dígitos o letras
 sin acentuar, y sin espacios.
 !exit
!endif

!if auth_fail=$error
 La clave secreta que ha introducido no es correcta. Ha fallado
 la inscripción.
 !exit
!endif

!if bad_pass=$error
 Su contraseña contiene caracteres ilegales. <p>
 Por favor, use una contraseña que contenga únicamente dígitos o
 letras sin acentuar, y sin espacios.
 !exit
!endif

!if login_size=$error
 Su identificador de usuario es demasiado
 !if $n<4
  corto
 !else
  largo
 !endif
 Debe contener entre 4 y 16 caracteres.
 !exit
!endif

!if pass_size=$error
 Su contraseña es demasiado
 !if $n<4
  corta
 !else
  larga
 !endif
 Debe contener entre 4 y 16 caracteres.
 !exit
!endif

!if bad_forumpass=$error
 Su contraseña para <b><font color=green>$title</font></b>
 no es correcta. Por lo tanto, no está autorizado a inscribirse 
 en este foro de discusión. Lo sentimos.
 !exit
!endif

!if login_double=$error
 El identificador de usuario ``<b><font color=green>$login</font></b>''
 ya se está usando en
 <p><center>
 <b><font color=green>$title</font></b>.
 </center> <p>
 Por favor, compruebe si estaba inscrito; de lo contrario, por favor
 elija otro nombre de acceso.
 !exit
!endif

!if pass_error=$error
 La contraseña que ha vuelto a teclear no se corresponde con la primera. Por
 lo tanto, su inscripción se ha ignorado. Inténtelo otra vez.
 !exit
!endif

!if insert_fail=$error
 El software no ha podido incluir su inscripción en la base de datos.
 Hay un error interno. Lo sentimos.
 !exit
!endif

!if site_complete=$error
 El número de usuarios inscritos ha alcanzado el máximo permitido
 por este foro de discusión ($user_limit).
 El servicio de inscripción se ha cerrado,
 lo sentimos. <p>
 !exit
!endif

!if internal_total=$error
 Error interno del software: no se ha podido determinar el número de
 usuarios inscritos.
 !exit
!endif

