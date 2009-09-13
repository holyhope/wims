!!!!WARNING Don't use "into" in the translation ...

!if $wims_name_home!=$empty
 !exit
!endif

!! **** Default Names ***
!distribute items Buscar,\
		Al trabajo,Volver al trabajo,\
		Página inicial de WIMS,Introducción/Configuración,Ayuda,Acerca de,\
		Introducción,\
		Cerrar esta ventana,Atrás,\
		Administrador del sitio,Autor de la página,Autores de la página,\
		Traducido por,Salir,\
		Ayuda de WIMS,Referencias,\
		Foro de discusión,Foro,\
		Hoja de trabajo,Herramientas,\
		Copiar a Modtool,\
		Imprimir,\
		Importar a su clase,\
		Versión imprimible,\
		Otro nuevo,\
		(Ir en la) zona prueba,\
		Actualizar esta página,\
		Guardar,\
		si,\
		no,\
		Télécharger,\
		Send,\
		Detalles,\	
	into wims_name_search,\
	wims_name_work,wims_name_resume,\
	wims_name_home,wims_name_intro,wims_name_help,wims_name_about,\
	wims_name_titleintro,\
	wims_name_back,wims_name_back2,\
	wims_name_manager,wims_name_author,wims_name_authors,\
	wims_name_translatedby,wims_name_exit,\
	wims_name_whelp,wims_name_ref,wims_name_forum,wims_name_forums,\
	wims_name_sheet,wims_name_tools,\
	wims_name_modify,wims_name_print,wims_name_import,\
	wims_name_printable,wims_name_renew,wims_name_testgo,\
	wims_name_refresh,wims_name_tosave,\
	wims_name_yes,wims_name_no,wims_name_download,wims_name_send,wims_name_detail

!! **** Permalink Names ***	
!distribute items este módulo, este ejercicio,\
		Indicar, en su sitio,\
		Encubrir estas opciones, \
		Permalink, Lector exportable,\
		copiar y pegar, el vínculo, el código, o, en un correo electrónico,\
		para, solamente,\
		el config actual,\
	into wims_name_this_module, wims_name_this_exercice,\
	wims_name_display,wims_name_on_your_site,\
	wims_name_mask_this,\
	wims_name_permalink,wims_name_embeddable,\
	wims_name_copy_and_paste,wims_name_the_link,wims_name_the_code,wims_name_or,wims_name_in_a_mail,\
	wims_name_for,wims_name_only,\
	wims_name_this_config

!! **** Module About Names ***
!distribute items Nombre,\
		Información sobre este módulo,\
		dirección,\
		Vínculo para marca-página,\
		Descripción,\
		Versión,\
		Versión WIMS <br> requerida,\
		Lengua,\
		Autor,\
		Traductor,\
		Esto es un módulo de,\
		Servidor Interactivo Multifunciones en la Red,\
		Derechos de autor \
	into wims_name_name,\
	wims_name_module_infos,\
	wims_name_Address,\
	wims_name_Link_for_bookmark,\
	wims_name_Description,\
	wims_name_Version,\
	wims_name_Required_WIMS_version,\
	wims_name_Language,\
	wims_name_Author,\
	wims_name_Translator,\
	wims_name_This_is_a_module,\
	wims_name_WIMS_subtitle,\
	wims_name_Copyright


!! **** Class Relative Names ***
!if $wims_class!=$empty
 !distribute items Página principal de la clase,\
		Insertar en una hoja de trabajo,\
		Escribir al profesor, Cerrar la clase,\
		El registro de notas es cerrado.,\
		Ha suspendido el registro de notas.,\
		Activar el registro, suspender el registro,\
		Usted es el profesor de la clase,\
		Registrar los detalles de este ejercicio,\
		Página de gestión de la hoja de trabajo\
		Añadir una secuencia,\
	into wims_name_class_home,wims_name_add,\
	wims_name_wsup,wims_name_visitor,\
	wims_name_scoreclose,\
	wims_name_scoresuspend,\
	wims_name_scorereopen,wims_name_scoreclose2,\
	wims_name_syou,\
	wims_name_exolog,\
	wims_name_sheetmanagement,\
	wims_name_add_sequence

 !set wims_name_score=!nosubst Ha conseguido $[$wims_homeref_got] de \
	$[$wims_homeref_req] puntos en este trabajo. <br>Puntuación media \
	$[$wims_homeref_mean]/10.
 !set wims_name_you=usted es <b>$wims_firstname $wims_lastname</b>, accediendo a
 !if _exam isin $session
  !distribute items Otros ejercicios del examen,\
	Tiempo que permanece para este examen:,\
	cuando se cargue esta página\
	into wims_name_back,wims_name_examremain,wims_name_whenloaded
 !endif
 !if _check isin $session
  !let wims_page_name=Page
 !endif
 !set wims_name_sequence=!defof sequence_Title in wimshome/log/classes/$wims_class/seq/.def
 !default wims_name_sequence=Sequence
!endif

!if adm/class isin $module
 !distribute line Zona de los Profesores \
	Zona de los estudiantes\
	Clases de ejemplo\
	Autentificación del profesor\
	Autentificación de los participantes\
	Enseñanza primaria\
	Enseñanza secundaria\
	Universidad\
	Lista de clases \
    Lista de clases y pórticos \
    Clase individual\
    Agrupación de clases \
    Pórtico de establecimiento \
	into wims_name_n_supervisor,wims_name_n_participant,wims_name_n_example,\
	wims_name_n_authsupervisor,wims_name_n_authparticipant,wims_name_n_E,wims_name_n_H,wims_name_n_U,\
	wims_name_classlist,wims_name_portal_list,\
	wims_name_create_class,wims_name_create_superclass,wims_name_create_portal
!endif

!if adm/new isin $module
  !distribute line Nuevos módulos\
  Módulos actualizados \
  Cambios en el sistema \
  RSS Nuevos módulos\
  RSS Módulos actualizados \
  into wims_name_mod_new,wims_name_mod_modif,wims_name_mod_sys,wims_name_rss_new,wims_name_rss_modif
!endif

!if $wims_user=$empty
  !distribute line Crear una clase \
  into wims_name_classcreate
!endif

!if adm/modtool isin $module or adm/createxo isin $module or $wims_user!=$empty
  !distribute line Probar el módulo \
   Gestor de documento \
   Contenido del módulo \
   Otros archivos \
   Propiedades \
   Guardar\
   Diferencias \
   Publicar \
   Nuevo Módulo \
   Lista de los módulos \
   Depósito de archivos \
   Restauración \
   Propiedades de la cuenta \
   Probador de programas \
   Documentación OEF \
   Biblioteca de programas \
   Tipos de respuestas posibles \
   Doc técnica \
   Volver a la lista de archivos \
   Cambiar el archivo \
   Cambiar\
   Atras\
   Eliminar\
   Acción\
 into wims_name_test,wims_name_docgestion,wims_name_modcontent,wims_name_otherfiles,\
wims_name_properties,wims_name_modsave,wims_name_checkdiff,wims_name_publish,wims_name_createnew,\
wims_name_modlist,wims_name_binfile,wims_name_restore,\
wims_name_account_property,\
wims_name_scripttest,wims_name_docoef,wims_name_docslib,wims_name_docanswer,wims_name_doctec,\
wims_name_back3,wims_name_edfile,wims_name_change,wims_name_up,wims_name_erase,wims_name_action

!distribute line Volver a la página de creación de ejercicios \
   Lista de modelos \
   Modelos preparados \
into wims_name_backcreatexo,wims_name_modellist,wims_name_model

!distribute line Probar el ejercicio \
Volver a confia2qcm\
Volver a createqcm\
Modificar el programa \
Poner en el módulo de desarrollo \
Poner este ejercicio en la clase \
Guardar como nuevo ejercicio \
Enviar un archivo de imagen \
Reemplazar el anterior\
eliminar este ejercicio\
into wims_name_testexo,wims_name_backconfia2qcm,wims_name_backcreateqcm,wims_name_exomodify,\
wims_name_putmodtool,wims_name_putclass,wims_name_newversion,\
wims_name_downloadbinary,wims_name_replace,wims_name_exoerase

!endif

!distribute line Nuevo documento \
Nueva hoja \
Nuevo examen \
Nueva clase \
Nuevo cuestionario \
Nuevo ejercicio \
Ejercicios de la clase \
into wims_name_add_doc,wims_name_add_sheet,wims_name_add_exam,wims_name_add_class,wims_name_add_vote,\
wims_name_add_exo,wims_name_classexo

!!! for documents

!distribute items WIMS,Clase,Docs,Arriba,Atras.,Sig.,Hist.,Recargar,\
    Versión interactiva,Versión para imprimir,\
    Volver a doc.,Ayuda,Acerca de,\
    Depósito de archivos,\
    Volver a la lista de archivos,\
    Página de entrada del documento\
    into wims_name_doch_wims,wims_name_doch_class,wims_name_doch_docs,wims_name_doch_up,\
    wims_name_doch_prev,wims_name_doch_next,wims_name_doch_hist,wims_name_doch_reload,\
    wims_name_doch_interactive,wims_name_doch_printable,\
    wims_name_doch_back,wims_name_doch_help,wims_name_doch_about,\
	wims_name_doch_upload,wims_name_doch_filelist,wims_name_doch_main

!! for sequence et document

!distribute line Document\
ocultado, visible \
Título \
Reorganización por secuencias \
Inserción en la clase \
Crear un nuevo documento \
trabajar en un documento de prueba\
Estatuto \
into wims_name_doc,wims_name_status,wims_name_title,wims_name_reorder,wims_name_adddoc,\
wims_name_createdoc,wims_name_doctry,wims_name_Status

 !distribute line Añadir una fecha \
   Añadir un archivo \
   Añadir deberes \
   Configurar \
   Abandonar \
  into wims_name_adddate,wims_name_addfile,wims_name_addtodo,wims_name_config,wims_name_giveup


!set wims_name_supervisor=administrador
!set wims_name_teacher=Cuentas de profesores
!set wims_name_addteacher=Nuevo profesor
!set wims_name_modteacher=Propiedades del profesor
!set wims_name_delteacher=Borrar a un profesor
!set wims_name_student=Cuentas de alumnos
!set wims_name_addstudent=Nuevo alumno
!set wims_name_modstudent=Propiedades del alumno
!set wims_name_delstudent=Borrar a un alumno
!set wims_name_group= Pórtico 
!set wims_name_portal= Pórtico 
!set wims_name_level=nivel
!set wims_name_class=clase
!set wims_name_program=programa
!set wims_name_course=curso
!set wims_name_icourse=curso de interclase
!set wims_name_backstruct=Hacer una copia de seguridad de la estructura

!if config isin $module
 !distribute line Página principal de configuración\
 Gestión de la estructura\
 Copias de seguridad y recuperación\
into wims_name_config, wims_name_struct,wims_name_save

!endif
!set wims_name_backgateway= Gestión de 

!distribute line Añadir un curso \
Añadir un curso interclase \
Añadir una clase \
Añadir un programa \
Añadir un nivel \
login de gestión \
Cambiar de zona \
into wims_name_addcourse,wims_name_addicourse,wims_name_addclass,wims_name_addprog,wims_name_addlevel,\
wims_name_login,wims_name_chzone

!distribute line Estadísticas de actividad \
Actividades globales de los participantes \
Cambiar el baremo \
Notas manualmente asignadas \
Conexión hoja de cálculo \
into wims_name_class_stat,wims_name_activity,wims_name_formula,wims_name_grades,\
wims_name_csv

!if adm/class/userlist isin $module
!distribute line Lista de los participantes\
Resultados del participante \
Cerrar esta sesión de examen\
Detalles de su trabajo\
Suprimir el participante \
Datos brutos\
cambiar su contraseña\
Datos tratados\
Cuaderno de competencias \
into wims_name_part_list,wims_name_scores,wims_name_partexamclose,wims_name_workdetail,\
wims_name_delprep,wims_name_rawdata,wims_name_passwd,wims_name_getraw,wims_name_livret
!endif

!if adm/manage isin $module
  !distribute line Otras tareas de mantenimiento \
  into wims_name_sitegestion
!endif

!!if adm/class/livret isin $module
!! !if $wims_user=supervisor
!!  !let tmp= Gestión de los participantes y notas 
!! !else 
!!  !let tmp= Mis notas 
!! !endif
!! !distribute line Nueva competencia \
!!Configurar \
!!$tmp\
!!Cuaderno de la clase \
!!Cuaderno de competencias \
!!  into wims_name_add_competence,wims_name_config,wims_name_go_userlist,wims_name_cls_livret,wims_name_livret 
!!endif

!if $wims_user=supervisor
 !distribute line Volver a la página del profesor \
 into wims_name_backteacher
!endif

!distribute lines Modtool\
   Createxo\
   Quicktool\
   Latex2wims\
   into wims_name_modtool,wims_name_createxo,wims_name_quicktool,wims_name_latex2wims

!distribute line activar el editor HTML \
desactivar el editor HTML \
attention, les modifications faites ne seront pas sauvées si vous changez cette option en cours de rédaction\
into wims_name_active, wims_name_desactive,wims_name_speck_warning

!distribute items Apellido,Nombre,Contraseña,Correo electrónico,Identificador de usuario \
into wims_name_lastname, wims_name_firstname,wims_name_Password,wims_name_email,\
wims_name_Login
