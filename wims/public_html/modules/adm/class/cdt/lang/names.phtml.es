!set lang_exists=yes

!if $job=adddate
  !set cdt_subtitle=A�adir/modificar una fecha
  !goto common
!endif

!if $job=addtodo
  !set cdt_subtitle=A�adir deberes
  !goto common
!endif

!if $job=logfile
  !set cdt_subtitle=Ficha de registro
  !set name_text=Ah� tienes el registro de las conexiones al cuaderno de texto de la clase
  !goto common
!endif

!if $job=config
  !set cdt_subtitle=Ficha de registro
  !set name_link=Nombre del v�nculo sobre la p�gina inicial
  !set name_intro=Ah� tienes los par�metros que pueden cambiar
  !set name_see=Ver
  !set name_see2=el fichero de conexi�n al cuaderno de texto de la clase
  !set name_reversedate=Affichage des informations dans l'ordre inverse de leur date
  !goto common
!endif

!if $job=file
  !set name_erasedfile=!nosubst El fichero <b>$erase</b> fue borrado.
  !set name_depos=Pueden depositar un fichero&nbsp;
  !set name_available=Ficheros disponibles en
  !set name_erase=Borrar un fichero
  !set name_nodeposit=No pueden depositar m�s fichero ya que su contenido es muy cercano de, \
  o sobrepas�, el l�mite de espacio disco autorizado. Afligido.
  !set name_explanation1=!nosubst Estos ficheros son accesibles con ayuda de la variable\
  <span class="tt wims_code_variable">\filedir</span>. \
  Por ejemplo,\
  <p class="wimscenter">\
 <span class="tt wims_address">&lt;a href="\filedir/$f1"&gt;$f1&lt;/a&gt;</span>\
 </p>\
 crea un v�nculo hacia el fichero <a href="$m_filedir/$f1">$f1</a>.\
 Pueden tambi�n escribir

 !set name_explanation2=para incluir el fichero de imagen <span class="tt">myfile.jpg</span> en la p�gina.\
 <br />Los ficheros depositados son solamente accesibles a los participantes de la clase.

!set name_availablespace=Espacio disco disponible al principio&nbsp;,Espacio libre
  !goto common
!endif

!if $job=helplink
  !set name_Add=Para a�adir un objeto, pulsar el v�nculo correspondiente.
  !set name_exam=Ex�menes&nbsp;
  !goto common
!endif

:common
!distribute line el trabajo efectuado\
el trabajo pendiente\
entre el\
y el\
A�adir un examen\
A�adir una hoja de ejercicios\
para el\
Trabajo pendiente \
Deberes\
Numero de fechas a mostrar\
Trabajo pendiente para el \
Trabajo efectuado\
Sesi�n de\
caracteres\
Ninguna informaci�n\
Ninguna informaci�n para este d�a\
Ninguna informaci�n para este per�odo\
D�a\
Asignaturas\
En clase\
Dado el\
No hay trabajo que hacer para el\
Ins�rer une ressource de la classe\
le\
into name_done,name_todo,name_between,name_and,name_addexam,name_addsheet,name_for,name_worktodo,\
name_work,name_nb_date,name_todo2,name_workdone,name_session,\
name_character,name_noinfo1,name_noinfo2,name_noinfo3,\
name_Day,name_discipline,name_inclass,name_giventhe,name_nowork,\
name_help_add,name_the

!set name_workfor=$name_work $name_for

!set name_warning1=Si no escriben una segunda fecha, efectuar�n \
una investigaci�n sobre la primera fecha.

