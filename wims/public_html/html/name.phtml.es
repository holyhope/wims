!!!!WARNING If you have to put "into" in the translation, write into$  ...

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
		Cargar a distancia,\
		Enviar,\
		Detalles,\
		Mostrar,\
		Corregir,\
		¡Atención!,\
		¡Felicidades!,\
		o,\
		Explicaciones,\
		Ejercicio,\
		Hoja,\
		Cuenta,\
		Entrar,\
		Notas,\
		Notas,\
		Examen,\
		Recorrer el sitio,\
		Volver al menú,\
		Fecha de expiración,\
		Error,\
		Série suivante,Série précédente,\
		Example,\
		Encuesta,\
		Conditions générales d'utilisation,\
		Besoin d'aide ?,\
 into wims_name_search,\
	wims_name_work,wims_name_resume,\
	wims_name_home,wims_name_intro,wims_name_help,wims_name_about,\
	wims_name_titleintro,\
	wims_name_back,wims_name_back2,\
	wims_name_manager,wims_name_author,wims_name_authors,\
	wims_name_translatedby,wims_name_exit,\
	wims_name_whelp,wims_name_reference,wims_name_forum,wims_name_forums,\
	wims_name_sheet,wims_name_tools,\
	wims_name_modify,wims_name_print,wims_name_import,\
	wims_name_printable,wims_name_renew,wims_name_testgo,\
	wims_name_refresh,wims_name_tosave,\
	wims_name_yes,wims_name_no,wims_name_download,wims_name_send,wims_name_detail,\
	wims_name_Show,wims_name_Edit,wims_name_warning,wims_name_Congratulations,wims_name_or,\
	wims_name_Explanations,wims_name_Exercise,wims_name_Sheet,wims_name_Account,wims_name_Enter,\
	wims_name_Score1,wims_name_myscore,wims_name_Examen,wims_name_browse,wims_name_menuback,\
	wims_name_expiration,wims_name_Error,wims_name_nextseries,wims_name_previousseries,\
	wims_name_Example,wims_name_Vote,wims_name_cgu,wims_name_feedbackexo

!! **** Permalink Names ***
!distribute items este módulo, este ejercicio,\
		Indicar, en su sitio,\
		Encubrir estas opciones, \
		Permaenlace, Lector exportable,\
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

!! the following sentences can be changed according to language if needed
!set wims_name_display1=!nosubst $wims_name_display $wims_name_this_module $wims_name_on_your_site
!set wims_name_display2=!nosubst $wims_name_copy_and_paste $wims_name_the_link $wims_name_on_your_site $wims_name_or $wims_name_in_a_mail
!set wims_name_display3=!nosubst $wims_name_copy_and_paste $wims_name_the_code $wims_name_on_your_site
!set wims_name_permalink1=!nosubst $wims_name_permalink $wims_name_for $wims_name_this_module

!! **** Module About Names ***
!distribute items Nombre,\
        À propos des icones,\
		Información sobre este módulo,\
		Información sobre este ejercicio,\
		dirección,\
		Vínculo para marca-página,\
		Descripción,\
		Versión,\
		Versión WIMS <br> requerida,\
		Lengua,\
		Autor,\
		Maintainer,\
		Traductor,\
		Esto es un módulo de,\
		Servidor Interactivo Multifunciones en la Red,\
		Derechos de autor,\
		Palabras clave,\
		Correo electrónico del traductor,\
		Correo electrónico del autor,\
		Dominio,\
		Tipo,\
		Nivel(x),\
		Mecanismo de puntuación <br><small>(ejercicio/recreación)</small>,\
		Programas informáticos de apoyo<br>necesarios,\
		Server Time,\
		Data module,\
		Developped on WIMS,\
		Publication center,\
        Download center,\
	    Syntax,\
        Meaning,\
	into wims_name_name,\
	wims_name_iconabout,\
	wims_name_module_infos,\
	wims_name_exo_infos,\
	wims_name_Address,\
	wims_name_Link_for_bookmark,\
	wims_name_Description,\
	wims_name_Version,\
	wims_name_Required_WIMS_version,\
	wims_name_Language,\
	wims_name_Author,\
	wims_name_Maintainer,\
	wims_name_Translator,\
	wims_name_This_is_a_module,\
	wims_name_WIMS_subtitle,\
	wims_name_Copyright,wims_name_Keywords,\
	wims_name_tr_email,wims_name_auth_email,\
	wims_name_Domain,wims_name_Type,wims_name_Levels,\
	wims_name_Scoring,\
	wims_name_require,wims_name_server_time,wims_name_datamodule,\
	wims_name_devwims,wims_name_publish_center,wims_name_download_center,\
	wims_name_Syntax,wims_name_Meaning


!! **** Class Relative Names ***
!if $wims_class!=$empty
 !distribute items Página principal de la clase,Insertar en una hoja de trabajo,\
		Escribir al profesor, Salir,\
		El registro de notas es cerrado.,\
		Ha suspendido el registro de notas.,\
		Activar el registro, suspender el registro,\
		Usted es el profesor de la clase,\
		Registrar los detalles de este ejercicio,\
		Página de gestión de la hoja de trabajo,\
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
	$[$wims_homeref_req] puntos en este trabajo, calidad \
	$[$wims_homeref_mean]/10.
 !set wims_name_you=usted es <b>$wims_firstname $wims_lastname</b>, perteneciendo a
 !if _exam isin $session
  !distribute items Otros ejercicios del examen,\
	Tiempo que permanece para este examen&nbsp;:,\
	cuando se cargue esta página\
	into wims_name_back,wims_name_examremain,wims_name_whenloaded
 !endif
 !if _check isin $session
  !let wims_page_name=Page
 !endif
 !set wims_name_sequence=!defof sequence_Title in wimshome/log/classes/$wims_class/seq/.def
 !default wims_name_sequence=Secuencia
 !set wims_name_sequences=secuencias

 !set wims_name_exceeded=Su clase superó el espacio disco autorizado en el servidor.\
  La gestión de la clase no está ya disponible. ¡Afligido!<p>Les sugerimos interrogar al administrador del sitio\
  para aumentar el espacio disco autorizado para las clases virtuales.

 !set wims_name_reaching_limit=Su clase alcanza el límite de espacio disco autorizado.\
  Una vez este límite pasado, se bloqueará la gestión de la clase!
  
 !set wims_name_chseries=!nosubst Enregistrer les modifications sur la série d'exercices $(special_parm4[2]) feuille $(special_parm4[1])
!endif

!!!if adm/class isin $module or adm/manage isin $module
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
!!!endif

!if adm/new isin $module
  !distribute line Nuevos módulos\
  Módulos actualizados \
  Cambios en el sistema \
  RSS Nuevos módulos\
  RSS Módulos actualizados \
  into wims_name_mod_new,wims_name_mod_modif,wims_name_mod_sys,wims_name_rss_new,wims_name_rss_modif
!endif

  !distribute line Crear una clase \
  into wims_name_classcreate

!if adm/modtool isin $module or adm/createxo isin $module or $wims_user!=$empty or $module!=
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
   Para utilizar esta actividad, debe activar java en su navigador.\
   Fecha\
   Añadir\
   Suprimir\
   Source\
   Salir\
 into wims_name_test,wims_name_docgestion,wims_name_modcontent,wims_name_otherfiles,\
wims_name_properties,wims_name_modsave,wims_name_checkdiff,wims_name_publish,wims_name_createnew,\
wims_name_modlist,wims_name_binfile,wims_name_restore,\
wims_name_account_property,\
wims_name_scripttest,wims_name_docoef,wims_name_docslib,wims_name_docanswer,wims_name_doctec,\
wims_name_back3,wims_name_edfile,wims_name_change,wims_name_up,wims_name_erase,wims_name_action,\
wims_name_nojava,wims_name_date,wims_name_add0,wims_name_delete,wims_name_source,\
wims_name_visitor

!distribute line Volver a la página de creación de ejercicios \
   Lista de modelos \
   Modelos preparados \
into wims_name_backcreatexo,wims_name_modellist,wims_name_model

!distribute line Probar el ejercicio \
Volver a confia2qcm\
Volver a createqcm\
Modificar el programa fuente \
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

!!! para documentos  en particular...

!distribute items WIMS,Clase,Docs,Arriba,Atras,Sig.,Hist.,Recargar,\
	Versión interactiva,Versión para imprimir,\
	Volver a doc.,Ayuda,Acerca de,\
	Depósito de archivos,\
	Volver a la lista de archivos,\
	Página de entrada del documento\
	Transfert,\
	into wims_name_doch_wims,wims_name_doch_class,wims_name_doch_docs,wims_name_doch_up,\
	wims_name_doch_prev,wims_name_doch_next,wims_name_doch_hist,wims_name_doch_reload,\
	wims_name_doch_interactive,wims_name_doch_printable,\
	wims_name_doch_back,wims_name_doch_help,wims_name_doch_about,\
	wims_name_doch_upload,wims_name_doch_filelist,wims_name_doch_main,wims_name_doch_transfer

!! for sequence et document

!distribute line Documento\
ocultado, visible \
Título \
Reorganización por secuencias \
Insertar en la clase \
Crear un nuevo documento \
Documento de prueba\
Estatuto\
Insertar\
En preparación,Activo,Expirado,Expirado+Oculto\
ni leer ni escribir en,leer pero no escribir en,leer y escribir en\
Número\
into wims_name_doc,wims_name_status,wims_name_title,wims_name_reorder,wims_name_adddoc,\
wims_name_createdoc,wims_name_doctry,wims_name_Status,wims_name_Insert,wims_name_shstatus,\
wims_name_Docstatus,wims_name_number

 !distribute line Añadir una fecha \
   Añadir un archivo \
   Añadir deberes \
   Configurar \
   Abandonar \
   Cuaderno de textos\
  into wims_name_adddate,wims_name_addfile,wims_name_addtodo,wims_name_config,wims_name_giveup,\
  wims_name_cdt

!set wims_name_supervisor=administrador
!set wims_name_Supervisor=Administrador
!set wims_name_namestudent=Alumno
!set wims_name_nameteacher=Profesor
!set wims_name_teacher=Cuentas de profesores
!set wims_name_addteacher=Nueva cuenta de profesor
!set wims_name_modteacher=Propiedades del profesor
!set wims_name_delteacher=Borrar a un profesor
!set wims_name_student=Cuentas de alumnos
!set wims_name_addstudent=Nuevo alumno
!set wims_name_modstudent=Propiedades del alumno
!set wims_name_delstudent=Borrar a un alumno
!set wims_name_group= Pórtico
!set wims_name_portal= Pórtico
!set wims_name_level=Nivel
!set wims_name_class=Clase
!set wims_name_program=Programa
!set wims_name_course=Curso
!set wims_name_icourse=Curso de interclase
!set wims_name_backstruct=Hacer una copia de seguridad de la estructura

!if config isin $module or $module=home
 !distribute line Página principal de configuración\
 Gestión de la estructura\
into wims_name_config, wims_name_struct
!endif

!set wims_name_save=Copias de seguridad y recuperación
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

!if adm/class isin $module or reguser isin $module or $wims_class!=$empty
!distribute line Lista de los participantes\
List of teachers\
Resultados del participante \
Cerrar esta sesión de examen\
Detalles de su trabajo\
Eliminar el participante \
Datos brutos\
Cambiar su contraseña\
Datos tratados\
Cuaderno de competencias \
into wims_name_part_list,wims_name_teacherlist,wims_name_scores,wims_name_partexamclose,wims_name_workdetail,\
wims_name_delprep,wims_name_rawdata,wims_name_passwd,wims_name_getraw,wims_name_livret
!endif

!if adm/manage isin $module
  !distribute line Otras tareas de mantenimiento \
  into wims_name_sitegestion
!endif

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
cuidado, las modificaciones hechadas no se salvarán si cambian esta opción en curso de redacción\
into wims_name_active, wims_name_desactive,wims_name_speck_warning

!distribute items Apellido,Nombre,Contraseña,Correo electrónico,Identificador de usuario,Repita la contraseña,Comentario \
into wims_name_lastname, wims_name_firstname,wims_name_Password,wims_name_email,\
wims_name_Login,wims_name_repeat_pass,wims_name_comment

!distribute line Trombinoscopio\
Envío de correos electrónicos\
into wims_name_photoboard,wims_name_sendmail

!distribute items Profesor,Administrador,Alumno\
into wims_name_nameteacher,wims_name_Supervisor,wims_name_namestudent

!if $module isitemof home,adm/class/sheet,adm/class/exam
 !set wims_name_actionlist=Activar,expirar,desactivar,Ocultar,Mostrar,$wims_name_erase
!endif
