!set lang_exists=yes

name_supervisor=administrador
!!name_teacher=Cuentas de profesores
name_addteacher=Nueva cuenta de profesor
!!name_modteacher=$wims_name_modteacher
name_delteacher=Borrar una cuenta de profesor
!!name_student=Cuentas de alumnos
name_addstudent=Nuevo alumno
name_modstudent=Propiedades del alumno
name_delstudent=Borrar un alumno
name_portal=pórtico
name_level=nivel
name_class=clase
name_program=programas
name_course=curso
name_icourse=curso entre clases

name_dellevel0=Borrar el nivel
name_delclass0=Borrar la clase
name_delprogram0=Borrar el programa
name_delcourse0=Borrar el curso
name_deltest0=Borrar la zona de pruebas
name_classproperties=Propiedades de la clase
name_courseproperties=Propiedades del curso
name_levelproperties=Propiedades del nivel
name_programproperties=Propiedades del programa
name_participant=Participantes
name_csv=Cargar los datos de hoja de cálculo: formato
name_backstruct=Hacer una copia de seguridad de la estructura
!set name_gestion=Acceso de gestión
!set name_othergestion=Otros accesos de gestión
!set name_addgestion=Añadir un acceso de gestión

this_level=este nivel
this_class=esta clase
this_prog=este programa
this_course=este curso
this_icourse=este curso

levellist=E1,E2,E3,E4,E5,E6,H1,H2,H3,H4,H5,H6,U1,U2,U3,U4,U5,G,R
levelnames=EPO 1,EPO 2,EPO 3,EPO 4,EPO 5,\
	ESO 1 , ESO 2, ESO 3, ESO 4 / BUP 1, BUP 2, BUP 3, COU ,\
	Universidad año 1,\
	Universidad año 2,\
	Universidad año 3,\
	Universidad año 4,\
	Universidad año 5,\
	Graduate study,\
	Investigación

!set name_hidepass=ocultar las contraseñas
!set name_showpass=mostrar las contraseñas
!set name_IP=Ordenadores seguros
!set name_nonavailable=No disponible
!set name_code=Código
!set name_register=inscripción
!set name_supervisor2=Responsable
!set name_Style= Estilo del programa
!set name_style=obligatorio, optativo
!set name_installation=Instalación automática de los cursos en todas las clases del nivel \
 <br>à toutes les classes du niveau
 !set name_visit= Visitar

!if $job=addcourse
   !set name_course1= No hay ningún programa que puede añadir cursos en esta clase.
   !set name_course2= No hay ninguna clase en la que este programa pueda instalar cursos.
   !set name_course3=Estos son los programas que le permiten a su clase añadir cursos. \
   Pulse sobre el título para añadir un curso.
 !set name_course4= Estas son las clases donde este programa puede instalar más cursos.\
 Pulse en el título para instalar un curso.
!endif
!if $job=class
  !set name_class1= Esta clase aún no tiene cursos.
  !set name_class2=Cursos existentes en esta clase
!endif

!if $job=first
  !set name_first1=Todavía no hay cuentas de profesores.
  !set name_first2=Todavía no hay cuentas de alumnos.
  !set name_first3=Todavía no se ha instalado ningún nivel educativo.
  !set name_first4=Niveles educativos disponibles
!endif

!if $job=level
  !set name_level1=Este nivel todavía no tiene clases.
  !set name_level2=Este nivel todavía no tiene programas educativos.
  !set name_level3=Programas educativos disponibles en este nivel
  !set name_level4=Clases disponibles en este nivel
!endif

!if $job=prog
 !set name_prog1=Zona de pruebas
 !set name_prog2= Este programa no tiene una zona de pruebas
 !set name_prog3=Instalar una zona de pruebas
 !set name_prog4=Este programa todavía no tiene cursos.
 !set name_prog5=Cursos instalados en este programa
 !set name_prog6=Compartir los recursos de otro programa (<b>experimental</b>)
 !set name_prog7=Los recursos de este programa son compartidos por otros programas.
 !set name_prog8=Este programa comparte los recursos pedagógicos del programa
 !set name_prog9=Este programa no tiene cursos interclases.
!endif

!if $job=backstruct
 !set name_backstruct1=Esta es la copia de seguridad

 !set name_backstruct2=Se trata de un fichero en formato csv. Significado de los campos:\
 <p>tipo, código, título, cuenta-del-administrador, contraseña-de-inscripción, \
contraseña-del-profesor, opciones.

!endif

!set name_warning_share= Vous ne pouvez pas effacer ce programme car ses ressources pédagogiques \
sont partagées par d'autres programmes.

!if $job=addclass
!set form_titlename=Títulos de las nuevas clases\
<br><small>(separe los títulos con comas si <br>\
añade varias clases al mismo tiempo)</small>
!exit
!endif

!if $job=addicourse
!set form_caption=Añadir cursos interclases al programa
!set form_titlename=Títulos de los nuevos cursos\
<br><small>(separe los títulos con comas si<br>\
añade varios cursos al mismo tiempo)</small>

!exit
!endif

!if $job=addprog
!set form_titlename=Títulos de los nuevos programas:\
<br><small>(separe los títulos con comas si<br>\
añade varios programas al mismo tiempo)</small>
!exit
!endif
