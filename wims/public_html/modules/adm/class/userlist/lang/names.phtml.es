!set lang_exists=yes

!if $wims_read_parm!=
 !goto $wims_read_parm
!endif

!set classname=<div class="wims_classname">$wims_classname<div>\
 de <b><font color=green>$wims_institutionname</font></b>

!set months=enero,febrero,marzo,abril,mayo,junio,julio,agosto,septiembre,octubre,noviembre,diciembre

!distribute line Media de la clase\
Media\
Media de las notas positivas\
Media global\
into name_classAverage,name_Average,name_posAverage,name_globalaverage

!set name_partdeleted=Participantes borrados
!set wims_name_reg_ex=Lista de los ejercicios grabados
!set name_transfer=Transferir sus actividades desde otras clases

!set name_thsheet=Número,título,puntos<br>requeridos,peso,puntos<br>obtenidos,%,Calidad&nbsp,severidad,nota
!set name_minmax=mín/media/máx de la clase&nbsp;

!set name_manualscore=Notas asignadas por el profesor
!set name_autoscore=Notas registradas por el servidor
!set name_manual_notes=global,prof.,auto
!set name_examnote=Notas de exámenes

!set name_severitylevels=Niveles de severidad de las hojas de trabajo
!set name_formula=Número,Peso,Nivel
!set name_sheetstatut=prep,activa,expirada,ocultada

!distribute items Examen,Hoja,Ejercicio,Comienzo,Puntuación,Sesión,Terminado&nbsp;,equiv.\
into name_Exam,name_Sheet,name_Exercise,name_Start,name_Score,name_Session,\
name_done,name_equiv

!set name_formula_comment=Puede definir los niveles de severidad y los pesos de las hojas de trabajo\
en la tabla siguiente. Las notas serán calculadas con un máximo =
!set name_formula2=Notas calculadas sobre un máximo de $scoremax
!set name_pickup=Seleccione las hojas para <br>mostrar los resultados por hoja&nbsp;
!set name_warning= Ha efectuado una petición ilegal.

!set name_click=Pulse sobre un nombre para ver los detalles de su trabajo.
!set name_affi=la calidad, el trabajo efectuado, las notas
!set name_workdetail=Detalles del trabajo de
!set name_activesession=Este participante tiene una sesión de examen activa&nbsp;

!distribute items Estación de conexión, Tiempo restante, Sesión de examen de ,minutos\
into name_connecting,name_remaining_time,name_exam_session,name_minutes

!set name_noyetparticipant=Esta clase no tiene ningún participante aún.

!if $manual>0
 !set name_manual_explanation=<b>Explicaciones.</b> En las columnas de <tt>media</tt>,\
<tt>auto</tt>  se refiere a la media
de las notas calculadas a partir de las puntuaciones obtenidas en las hojas de trabajo,\
 <tt>prof.</tt> se refiere a la media de las notas asignadas manualmente por el profesor.\
La nota <tt>global</tt> se calcula a partir de las otras dos, mediante la fórmula
!endif

!set name_title_showsheet=!nosubst Detalles del trabajo sobre la hoja $numshowsheet<br>$sh_title
!set name_percentagegot=Porcentaje de los puntos obtenidos
!set name_qualitygot=Calidad del trabajo calculada sobre un máximo de 10
!set name_percentagedone=Porcentaje de trabajo efectuado
!set name_post=Mostrar

!if $job=userprop
  !distribute items Cambiar,Número de inscripción,Comentarios,URL de una fotografía,Variables (técnicas),\
  Contraseña de la clase,Introduzca la contraseña para la inscripción de participantes\
  into name_change,name_regnum,name_comments,name_photourl,name_vars,\
  name_classpassword,name_enterpassword
  !goto end
!endif

!if $job=examcheck
 !set name_title_examcheck=!nosubst Detalles de los exámenes hechos por $user_lastname, $user_firstname
 !set name_no_exampart=Este participante no ha realizado aún ningún examen.
 !set name_exampart=Sesiones de examen efectuadas por este participante (pulse sobre un \
  ejercicio para ver su contenido):
 !goto end
!endif
!if $job=getraw
  !set name_title_getraw=!nosubst Detalles del trabajo de $name_student1 <br>(datos en bruto)
  !goto end
!endif

!set name_direct_score=lista y notas en directo

!if $job=transfer
   !set name_title_transfer=Transferencia de las actividades
   !distribute items Unir, Sustituir,Examinar\
   into name_merge, name_replace,name_show
 !set name_error1=<b>Error</b>. El participante no está inscrito en ningún curso que corresponda\
     a la clase actual y que pueda recibir la transferencia desde
 !set name_error2=<b>Erreur</b>.<b>Erreur</b> d'identifiant des classes. \
    Fausse manoeuvre ou bogue du logiciel ? 
!set name_activities=!nosubst Détail des activités dans $i (limité à 1000 lignes).
!set name_totransfer=Estos son los otros cursos en los que ha realizado actividades el participante.\
  Pulse sobre una acción para hacer la transferencia.

!endif

!if $job=recover
  !set name_empty= No se ha dado de baja a ningún participante de esta clase.
  !set name_click=Pulse sobre un identificador de usuario (login) \
     para volver a incluir al participante en la clase.
!endif

!if $job=delprep
  !set name_delete=!nosubst ¿Está seguro de que quiere dar de baja a  <b><em>$lastname, $firstname</em></b> de su clase?
!endif

!if $job=csv
  !distribute lines  Este es el fichero\
    que puede descargar y abrir con su hoja de cálculo\
    que vous pouvez télécharger et ouvrir dans votre logiciel tableur préféré.\
    Cambios en la información sobre los participantes\
    Nuevos participantes \
    La incorporación de nuevos participantes será ignorada porque no queda espacio libre.\
    La información sobre los participantes no se ha modificado porque se han enviado calificaciones.\
    Se han ignorado en sus datos las notas calculadas por el servidor (medias y puntuaciones de hojas de trabajo/exámenes) porque no pueden ser modificadas.\
    Datos ignorados relativos a los participantes borrados\
    Los identificadores de usuario siguientes no existen y no pueden ser añadidos a causa de errores o insuficiencia de información en los datos enviados\
    Los identificadores de usuario siguientes no existen y no pueden ser añadidos a causa de errores o insuficiencia de información en los datos enviados\
    Sólo se graban calificaciones manuales para las columnas existentes.\
    No se ha producido ningún cambio en los datos enviados con respecto a los datos existentes en la clase.\
    Vérifier les notes\
    Para $wims_name_download los datos de la clase en la hoja de cálculo, especifique\
    El formato\
    Columnas\
    Para $wims_name_send los datos de su hoja de cálculo a la clase, especifique\
    El fichero de datos\
    Formatos aceptados\
  into name_file,name_download,name_infochanged,name_added,name_warning1,name_warning2,\
    name_warning3,name_warning4,name_nologin1,name_nologin2,name_manual1,name_data1,\
    name_check,name_data2,name_format,name_column,name_data3,name_data,name_format2
  

  !set name_deposit=!nosubst  El fichero de hoja de cálculo <tt>$wims_deposit</tt> ha sido reconocido correctamente.
!endif

!set name_topten=!nosubst Top $class_topscores de las medias de la clase
:end
!exit

:transfer
<b>Notas</b>. <ol>
<li>"Unir" quiere decir unificar los conjuntos de actividades de los dos cursos.
<li>"Sustituir" se refiere  a que las actividades del otro curso van a eliminar 
completamente las de este. La sustitución no se realizará si el primero está vacío.
<li>Las puntuaciones de los exámenes y las actividades no puntuadas siempre se unifican.
<li>El registro de los detalles de los ejercicios o de los exámenes no se transfiere.
<li>Después de la operación (de unir o sustituir), se borrarán los registros de las
actividades del participante en el otro curso.
</ol>
