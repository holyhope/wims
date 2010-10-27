!set lang_exists=yes
!set name_user=!nosubst $wims_firstname $wims_lastname.
!set monthnames=enero,febrero,marzo,abril,mayo,junio,julio,agosto,septiembre,octubre,noviembre,diciembre
!set name_wroteon=wrote on
!set name_default=Forum de la classe

!distribute item <i>Subject:</i> <b>,</b> into subj1,subj2
!distribute item <hr>,<hr> into body1,body2

!distribute line Lista de mensajes.\
	Lista de los mensajes por hilo\
	Leer un mensaje\
	Componer un nuevo mensaje\
	Escribir una contestación\
	Reseña de su mensaje\
	Enviar el mensaje\
	Configurar el foro\
	List by subjects\
	into n_list,n_thread,n_read,n_compose,n_follow,n_preview,n_send,n_config,n_subjectlist

!set wims_name_compose=$n_compose
!set n_welcome=Bienvenido/a
!set n_otherforums=Otros foros de discusión
!set n_list_subject_month =Lista de mensajes del mes de
!set n_email=correo electrónico
!set n_list_month = Lista de mensajes del mes de
!set n_most=los más
!set n_old=recientes primero,antiguos primero
!set n_new=Nuevo mensaje
!set n_archives=Archivos mensuales
!set n_following=Continuación de
!set n_reverse=Orden inverso
!set n_recent=Últimos mensajes
!set n_erased=borrado
!set n_send=Enviar el mensaje
!set n_edit=Volver a editarlo
!set n_emptymsg= ¡Su mensaje está vacío!
!set n_listforum=Lista de foros de discusión accesibles en este servidor.
!set n_by=por
!set n_newfollow= El nuevo sigue a
!set n_subject=Tema
!set n_content=Cuerpo del mensaje
!set n_preview=Vista previa
!set n_send0=Enviar
!set n_origin=Mensaje original
!set n_help=Ayuda
!set n_mathhelp=sobre cómo escribir fórmulas matemáticas en sus mensajes.
!set n_yourname= Nombre
!set n_cautious=<b>Atención.</b> Su mensaje no será aceptado, a menos que dé una \
  dirección de correo electrónico QUE FUNCIONE.
!set n_anonymous=visitante anónimo.
!set n_emptyforum=Este foro está vacío todavía.No accessible message is found corresponding to your request. Sorry.
!set n_erasedmsg=Mensaje borrado
!set n_nomessage=Ningún mensaje accesible corresponde a su petición. Lo sentimos.
!set n_with=incluyendo
!set n_or=or
!set n_without=sin incluir
!set n_citation= cita
!set n_source=Sin formatear
!set n_format=Formateado
!set n_erase=borrar
!set n_follow_c=Contestación con cita
!set n_follow_nc=Contestación sin cita
!set n_add= Su mensaje se ha añadido al foro.
!set n_bydate=Por fechas
!set n_bysubject=Por tema
!set n_prec=Anterior
!set n_first=Primero que sigue
!set n_allfollowing=Todas las contestaciones
!set $n_statusask= Este foro de discusión no acepta mensajes anónimos. Utiliza la \
 dirección de correo electrónico actual que usted ha proporcionado\
 para verificar su identidad, con objeto de evitar abusos.\
 <p>\
 Para verificar la validez de su dirección de correo, el servidor le ha\
 enviado una clave secreta por correo. Por favor lea ese e-mail,\
 y copie la clave aquí:
!set n_warning=Se añadió un mensaje al foro. No responder a este mensaje.
 !set n_thread=Por hilos
!if $job=compose and $c_prec!=$empty
 !set n_compose=Contestar
!endif

!set name_prompt=Actividad desconocida

!distribute line Parámetros del foro de discusión que puede cambiar.\
  ¿Quién puede leer los mensajes\
  todos los participantes, sólo usted\
  todos (inscritos o no), usuarios inscritos solamente, nadie excepto usted\
  ¿Quién puede enviar mensajes\
  todos los participantes,participantes con comprobación del correo electrónico,solamente usted\
  visitantes con dirección de correo electrónico o inscritos,sólo los usuarios inscritos,usuarios con comprobación del correo electrónico,nadie excepto usted\
 into name_introconfig, name_whoread,name_prompt1,name_prompt2,name_whosend,name_prompt3,name_prompt4
