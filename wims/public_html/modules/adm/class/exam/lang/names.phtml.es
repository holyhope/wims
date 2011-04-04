!set lang_exists=yes

!set wims_name_mainpage=Página principal del examen
!set name_title=Preparación del examen

!if $activetest<=0
 !let wims_name_sheetadmin=Página de preparación
 !set name_title=!nosubst Preparación del exament
!else
 !let wims_name_sheetadmin=Página de gestión
 !set name_title=!nosubst Gestión del examen
!endif

!read adm/lang/date.phtml.$lang
!read adm/lang/sheetexam.phtml.$lang

!! ---------------------------------------------------------------------------------------------------
!! ancien fichier name du module exam.fr

!set wims_name_scoreexam=!nosubst $wims_name_myscore

!set name_Options=Opciones
!set name_All=Todas

!set name_expire=Darlo por expirado ahora mismo
!set name_done=hecho

!distribute lines Terminar esta sesión de examen\
Volver a trabajar en el examen\
Punto de vista del profesor sobre el examen\
Presentación a los participantes\
Detalle de la puntuación actual\
¡Este examen está vacío! No se le ha asignado nada. Posiblemente un error de manipulación de su supervisor.Contenido del examen\
Contenido del examen\
Actualmente, este examen está cerrado a su conexión.\
Solo puede realizar una vez este examen.\
por lo tanto no puede mejorar su puntuación.\
Es su último intento disponible. ¡Preste atención!\
la cuenta atrás comenzará, y se incrementará en 1 el número de intentos.\
la cuenta atrás comenzará.\
Requiere el éxito sobre otros ejercicios\
Puntuación de esta sesión del examen\
into wims_name_endexam,wims_name_backexam,wims_name_teacherview,name_presentation,\
name_scoreexam,name_empty,name_content,name_examclosed,name_exam1,name_exam5,\
name_lasttry,name_exam7,name_exam8,name_depend,name_scoreexam2

!set name_exam2=!nosubst Puede registrar hasta $stries puntuaciones en este examen.
!set name_exam3=!nosubst Ya ha terminado su sesión de examen con $tried ensayos,
!set name_exam4=!nosubst Ya lo ha intentado $tried veces,
!set name_exam6=!nosubst Y todavía puede hacer $tryremain nuevos intentos.

!set name_exam9=!nosubst Tiene $sdure minutos para trabajar en el examen.
     Cuando pulse en un ejercicio de los anteriores,

!set name_simulation=Este examen está en modo simulación. Funciona exactamente igual
que el examen verdadero pero no se puede guardar la puntuación y el intento no se tendrá en cuenta.

!set wims_name_examremain=Tiempo restante de examen: $

!distribute lines pendiente\
 Todavía no ha comenzado a trabajar en este examen.\
 Comenzar a trabajar.\
 La puntuación actual no se tomará en cuenta, porque el examen está en modo simulación.\
into name_pending,name_begin1,name_begin2,name_simulation2

!set name_timeleft=!nosubst ¡Se acabó el tiempo! Ya ha usado los $sdure minutos permitidos para este examen.
!set name_realscore=!nosubst Su puntuación real para esta hoja de examen es $lastscore
!set name_bestscore =!nosubst Su mejor puntuación para este examen es $lastscore (la mejor puntuación es la que se tomará en cuenta).


!! ---------------------------
!! nueva parte

!set statutname=$(wims_name_shstatus[1]),$wims_name_shstatus

!set name_desc_duration=en minutos
!let name_mkexam=Crear el examen

!let name_shinfo_cutt=Horas de corte

!! distintos comentarios de la página de gestión
!distribute lines Información general&nbsp;\
Contenido del examen&nbsp;\
Este examen no tiene aún contenido.\
into name_info,name_content,name_warning

!! título del cuadro de contenido del examen (file examcontent.phtml)
!let name_extab=!nosubst $wims_name_number,$wims_name_title,Content,$name_weight,$name_dependency,$wims_name_comment,$name_Options,$wims_name_action

!set name_contenu=Elección del contenido
!let name_cpsheet1=Van a añadir una vez cada serie de ejercicios de la hoja siguiente tras los ejercicios ya presentes. Cada ejercicio tendrá como peso 1. Si no llenan el campo de texto abajo, conservará el título que tenía en la hoja de ejercicios.
!let name_cpsheet3=Título de ejercicio genérico
!let name_cpsheet4=se numerarán los ejercicios

!set name_warning_nonfinished=Todavía no ha completado todos los ejercicios de este examen. Si los acaba\
  ahora congelará la puntuación y consumirá una oportunidad de hacer\
  el examen, y tendrá que empezar desde el principio la próxima vez.<p>\
  ¿Seguro que quiere terminarlos?
