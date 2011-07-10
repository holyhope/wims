!set wims_module_log=error: $error
!read adm/class/classname.phtml $description\
$institution

!if bad_classtype=$error
 La inscripción de participantes no está autorizada en esta zona.
 !exit
!endif

!if no_class=$error
 ¡La clase que ha escogido parece no existir!
 Si no se trata de un fallo del programa, entonces es que la clase ha
 expirado o usted está jugando con el sitio (y en tal caso sepa que todas sus
 acciones están siendo registradas).
 !exit
!endif

!if complete=$error
La clase que ha elegido está al completo. No quedan plazas disponibles.
 Lo sentimos.
 !exit
!endif

!if no_real=$error
 No ha proporcionado sus apellidos ni su nombre.
 !exit
!endif

!if login_size=$error
 su identificador de usuario es demasiado
 !if $n<4
  corto.
 !else
  largo.
 !endif
 Debe contener entre 4 y 16 caracteres.
 !exit
!endif

!if pass_size=$error
 su contraseña es demasiado
 !if $n<4
  corta.
 !else
  larga.
 !endif
 Debe contener entre 4 y 16 caracteres.
 !exit
!endif

!if bad_classpass=$error
 Su contraseña para la clase
 $classname
 no es correcta. No está autorizado a inscribirse en
 esta clase. Lo sentimos.
 !exit
!endif

!if login_double=$error
 El identificador de usuario <tt class="wims_login">$login</tt>
 está ya siendo utilizado en la clase
 $classname.
 Por favor compruebe si no estaba ya inscrito; en caso contrario
 elija otro identificador de usuario.
 !exit
!endif

!if pass_error=$error
 La contraseña que ha vuelto a teclear no se corresponde con la primera.
 Por tanto su inscripción no se ha tenido en cuenta; puede intentarlo de nuevo.
 !exit
!endif

!if insert_fail=$error
 El programa no ha podido añadir su inscripción en la base de datos.
 Se trata de un error interno.
 <p>
 Por favor comunique el problema al
 !mailurl $wims_site_manager administrador de este sitio\
user registration failure
. ¡Gracias!
 !exit
!endif

!if site_complete=$error
 El número de usuarios inscritos ha alcanzado el límite autorizado por
 este sitio ($wims_user_limit). El servicio de inscripción se ha cerrado,
 lo sentimos. <p>
 Puede
 !mailurl $wims_site_manager escribir al administador del sitio\
site user limit
 para pedirle que aumente este límite o que le
 !href $ conecte a WIMS como visitante
. <p>
 !exit
!endif

!if internal_total=$error
 Error interno del programa: fallo en la determinación del número de usuarios
inscritos.
 !exit
!endif

!if no_cgu=$error
 Si vous n'acceptez pas les conditions générales d'utilisation, vous ne pouvez pas vous inscrire.
 !exit
!endif


!msg $error

