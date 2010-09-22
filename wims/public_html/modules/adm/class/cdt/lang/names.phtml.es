!set lang_exists=yes

!set classname=<b><font color="green">$wims_classname</font></b>\
 de <b><font color="green">$wims_institutionname</font></b>

!!!set months=enero, febrero, marzo, abril, mayo, junio, julio, agosto, septiembre, octubre, noviembre, diciembre

!if $job=adddate
  !set cdt_subtitle=Añadir/modificar  una fecha
  !goto common
!endif

!if $job=addtodo
  !set cdt_subtitle=Añadir deberes
  !goto common
!endif

!if $job=logfile
  !set cdt_subtitle=Ficha de registro
  !set name_text=Ahí tienes el registro de las conexiones al cuaderno de texto de la clase
  !goto common
!endif

!if $job=config
  !set cdt_subtitle=Ficha de registro
  !set name_link=Nombre del vínculo sobre la página inicial
  !set name_intro=Ahí tienes los parámetros que pueden cambiar
  !set name_see=Ver
  !set name_see2=el fichero de conexión al cuaderno de texto de la clase
  !goto common
!endif

!if $job=file
  !set name_erasedfile=!nosubst El fichero <b>$erase</b> fue borrado.
  !set name_depos=Pueden depositar un fichero&nbsp;
  !set name_available=Ficheros disponibles en
  !set name_erase=Borrar un fichero
  !set name_nodeposit=No pueden depositar más fichero ya que su contenido es muy cercano de, \
  o sobrepasó, el límite de espacio disco autorizado. Afligido.
  !set name_explanation1=!nosubst Estos ficheros son accesibles con ayuda de la variable\
  <tt>\filedir</tt>. \
  Por ejemplo,\
  <p><center>\
 <tt>&lt;a href="\filedir/$f1"&gt;$f1&lt;/a&gt;</tt>\
 </center> <p>\
 crea un vínculo hacia el fichero <a href="$m_filedir/$f1">$f1</a>.\
 Pueden también escribir

 !set name_explanation2=para incluir el fichero de imagen <tt>myfile.jpg</tt> en la página.\
 <p>Los ficheros depositados son solamente accesibles a los participantes de la clase.

!set name_availablespace=Espacio disco disponible al principio&nbsp;,Espacio libre
  !goto common
!endif

!if $job=helplink
  !set name_Add=Para añadir un objeto, pulsar el vínculo correspondiente.
  !set name_exam=Exámenes&nbsp;
  !goto common
!endif

:common
!distribute line el trabajo efectuado\
el trabajo pendiente\
entre el\
y el\
Añadir un examen\
Añadir una hoja de ejercicios\
para el\
Trabajo pendiente \
Deberes\
Numero de fechas a mostrar\
Trabajo pendiente para el \
Trabajo efectuado\
Sesión de\
caracteres\
Ninguna información\
Ninguna información para este día\
Ninguna información para este período\
Día\
Asignaturas\
En clase\
Dado el\
No hay trabajo que hacer para el\
into name_done,name_todo,name_between,name_and,name_addexam,name_addsheet,name_for,name_worktodo,\
name_work,name_nb_date,name_todo2,name_workdone,name_session,\
name_character,name_noinfo1,name_noinfo2,name_noinfo3,\
name_Day,name_discipline,name_inclass,name_giventhe,name_nowork

!set name_workfor=$name_work $name_for

!set name_warning1=Si no escriben una segunda fecha, efectuarán \
una investigación sobre la primera fecha.

!set name_date=!nosubst $jday/$jmonth/$jyear
!set name_date2=!nosubst $jday2/$jmonth2/$jyear2
