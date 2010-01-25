!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif

!set name_title=nombre del foro
!set name_description=descripción del foro
!set name_supervisor=nombre del propietario
!set name_email=dirección de correo electrónico
!set name_password=contraseña del foro
!set name_passsup=contraseña del propietario

!set forumname=<b><font color=green>$title</font></b>

!set months=enero,febrero,marzo,abril,mayo,junio,julio,agosto,septiembre,octubre,noviembre,diciembre

!distribute lines Creación de un foro de discusión\
  Reiniciar la operación.s\
  Nombre completo del propietario (es decir, usted)\
  su foro de discusión no se creará, a menos que dé una dirección de correo válida y funcional en este momento\
  Elija la contraseña del propietario\
  Elija una contraseña para el foro de discusión\
  entre 4 y 16 caracteres, dígitos o letras sin acento\
  Continuar\
  ¡Bienvenido/a\
  Contraseña del propietario\
  Contraseña del foro de discusión\
  Clave del foro\
  caracteres\
into title_title,name_restart,name_name_owner,name_warning1,name_choosepass1,name_choosepass2,\
  name_instruction,name_continue,name_hello,name_ownerpass,name_forumpass,name_code,\
  name_characters

!set name_name_forum=!nosubst Nombre del foro (a lo sumo $titlelim caracteres)

!set name_help1=Esta contraseña le permitirá acceder al foro de discusión como su\
  propietario. Debería ser la única persona que la conozca.

!set name_help2=Esta palabra clave será necesaria para la inscripción de los usuarios al\
  foro; por tanto, podrá proporcionársela a quienes desee que participen en el foro. 
!set name_warning=Si crea un foro de discusión en este sitio WIMS, deberá asumir \
 la responsabilidad de su mantenimiento. <p>\
 Para crear su foro de discusión, por favor, rellene la siguiente información:
 
 
!set name_warning2= <b>Atención</b> Esta clave es de un solo uso. ¡No puede utilizarla para\
 conectarse al foro de discusión!
 
!exit

:step1
Está creando el foro de discusión $forumname en el sitio WIMS
 $httpd_HTTP_HOST.
 <p>
 Si encuentra un error en la información anterior, por favor
 !href module=$module&cmd=reply&step=0 corríjala.
 <p>De lo contrario, para verificar la corrección de las contraseñas,
 por favor, vuélvalas a escribir. 
 !exit
 
:step2
Ahora necesita una clave para finalizar la operación de creación de un
 nuevo foro de discusión bajo WIMS en este sitio $http_HTTP_HOST. <p>
 Esta clave se le acaba de enviar a la dirección de correo que proporcionó
 ``<tt>$email</tt>''. Por favor, compruebe su correo (espere unos minutos si
 es necesario), y lea el mensaje que se le ha enviado.
 Busque la clave incluida en el mensaje y cópiela a continuación.
 !exit
 
 :step3
Se ha creado el foro de discusión $forumname. ¡Felicidades, y diviértase!<p>
 Puede acceder al foro
 !href module=adm/forum/forum desde aquí
.

!exit