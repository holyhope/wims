!set lang_exists=yes
!set classname=<b><font color=green>$wims_classname</font></b>\
 from <b><font color=green>$wims_institutionname</font></b>

!if $activetest<=0
!! !let wims_name_sheetadmin=Page of preparation
 !set name_title=!nosubst Preparation of sheet $sheet
!else
!! !let wims_name_sheetadmin=Page of management
 !set name_title=!nosubst Management of sheet $sheet
!endif

!read adm/lang/date.phtml.$lang
!!---------------------
!!  old part of names.phtml
!!
!set classname=<b><font color=green>$wims_classname</font></b>
 de <b><font color=green>$wims_institutionname</font></b>

!set months=enero,febrero,marzo,abril,mayo,junio,julio,agosto,septiembre,octubre,noviembre,diciembre

!set wims_name_endexam=Terminar esta sesión de examen
!set wims_name_scoreexam=Mi puntuación

!set wims_name_mainpage=Página principal del examen
!set name_dependency=Dependencias de las puntuaciones&nbsp;
!set name_Options=Opciones
!set name_All=Todas
!set name_title=Preparación del examen
!set name_expire=Darlo por expirado ahora mismo
!set name_done=hecho

!distribute items poids,Coeficiente,Puntuación\
into name_weight,name_coeff,name_Score

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
!! new part

!set statutname=!defof SU_Uprep,SU_Uprep,SU_Ac,SU_Ex,SU_Hi in wimshome/public_html/modules/home/names.$lang
!set statutaction=Activate,Expire,Deactivate,Invisible,Visible,$wims_name_erase

!! -------------- title description for file examinfo.phtml
!let name_shinfo=!nosubst $wims_name_title,$wims_name_Status,\
Text of explanation,\
Expiration date,,Score registation,for all sharing classes :,Remarks,Duration of an exam session,Number of trials per exam session

!! ------- value for description of option
!set name_desc_title=!nosubst limited to $title_limit characters
!set name_desc_desc=!nosubst limited to $desc_limit characters; html tags and links are allowed

!!set name_desc_dependancy=Score dependencies means that a participant must get required scores in other exercises of the sheet before he/she can do this one. For example, <font color=blue><tt>1:50,2:30,3+4+5:60</tt></font> means that the participant must get 50% success on exercise 1, 30% success on exercise 2,  and an average of 60% success on exercises 3,4,5.

!set name_desc_comment=Only visible for teachers.
!set name_desc_duration=in minutes
!let name_mkexam=Make the exam
!let name_allowtype=open to all, open for simulation,closed to all,open to following hosts (and/or hours) :
!let name_shinfo_cutt=Cut times

!! définition des noms pour les liens dans le menubox (définis par wims_menu_items)
!distribute items Participants' view,\
		Add another exercise,\
		add a series of exercises,\
into wims_name_participantview,wims_name_addexo,wims_name_addsexo


!! différents commentaires de la page de gestion
!distribute lines General information&nbsp;\
Content of the exam&nbsp;\
This exam has no content yet.\
into name_info,name_content,name_warning

!! titre du tableau de contenu de l'examen (file examcontent.phtml)
!let name_extab=!nosubst No,$wims_name_title,Content,$name_weight,$name_dependency,$wims_name_comment,$name_Options,$wims_name_action

!set name_contenu=Choose content
!let name_cpsheet1=You will add each exercise of the sheet at the end of the exam. Each exercise will have weight put to 1 and title put to sheet exercise title or to generic word below :
!let name_cpsheet2=Sheet
!let name_cpsheet3=Generic title word
!let name_cpsheet4=Exercise will be numeroted

!set name_warning_nonfinished=Todavía no ha completado todos los ejercicios de este examen. Si los acaba\
  ahora congelará la puntuación y consumirá una oportunidad de hacer\
  el examen, y tendrá que empezar desde el principio la próxima vez.<p>\
  ¿Seguro que quiere terminarlos?

!let name_selectsheet=Afficher seulement les exercices de la feuille