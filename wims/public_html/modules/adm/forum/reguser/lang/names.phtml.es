!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif

!set lang_fr=francés
!set lang_en=inglés
!set lang_es=español

!distribute lines Inscripción de un participante en un foro de discusión\
  Este sitio no contiene actualmente foros de discusión. ¡Lo sentimos, inténtelo más adelante!\
  está protegido por contraseña. Tiene que introducir la contraseña para inscribirse.\
  Escribir al propietario\
  opcional\
  ¡Bienvenido/a\
  No ha dado una dirección de correo válida.\
  Con dirección de correo\
  Para verificar la exactitud de su contraseña, vuélvala a escribir otra vez más\
  Lista de foros de este sitio\
into title,name_noforum,name_passw,name_write_owner,name_optional,name_hello,\
  name_email1,name_email2,name_email3,name_forumlist

!set name_obtain_passw=!nosubst <b>Nota</b>. Si el propietario ($supervisor) de este foro \
  le permite el acceso, deberá darle la contraseña de acceso

  
!set name_inscription=!nosubst Para poder inscribirse como participante en $forumname, por favor, \
  rellene la siguiente información:
 
!set name_password1=Este será el identificador que usará después para acceder al foro de discusión.\
  Por favor, elija una palabra que contenga entre 4 y 16 caracteres (dígitos o letras sin acentuar).
!set name_password2=La contraseña debe contener entre 4 y 16 caracteres (dígitos o letras sin acentuar)

!set name_inscription2=!nosubst Se está registrando como participante en $forumname, con \
  identificador de usuario &nbsp;
!exit

:welcome
 Bienvenido/a a $forumname.
  Ya es miembro de este foro de discusión, con identificador de 
  usuario ``<b><font color=green>$login</font></b>''. <p>
  Ahora puede
  !href module=adm/forum/forum&forum=$forum&type=authuser acceder
  al foro de discusión.

!exit
 
:code
 $forumname no permite la inscripción anónima. Utiliza la dirección de
  correo electrónico que ha proporcionado para identificarle 
  (con el objeto de prevenir abusos).
  <p>
  Para verificar la validez de su dirección de correo, el servidor
  le ha enviado una clave secreta a su cuenta de correo. Por favor, lea este
  e-mail, y copie la clave aquí:
!exit