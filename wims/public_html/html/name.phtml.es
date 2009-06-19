!if $wims_name_home!=$empty
 !exit
!endif

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
		Print,\
		Importar a su clase,\
		Versión imprimible,\
		Otro nuevo\
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
	wims_name_printable,wims_name_renew

!if $wims_class!=$empty
 !distribute items Página principal de la clase,\
        Inserte en una hoja de trabajo,\
		Escriba al profesor,Cierre la clase,\
		El registro de puntuación está cerrado.,\
		Ha suspendido el registro de puntuación.,\
		Usted es el profesor de la clase,\
		Registrar los detalles de este ejercicio,\
		Página de gestión de las hojas de trabajo\
	into wims_name_home,wims_name_add,\
	wims_name_wsup,wims_name_visitor,\
	wims_name_scoreclose,\
	wims_name_scoresuspend,\
	wims_name_syou,\
	wims_name_exolog,\
	wims_name_sheetmanagement
 !set wims_name_score=!nosubst Ha conseguido $[$wims_homeref_got] de \
	$[$wims_homeref_req] puntos en este trabajo. <br>Puntuación media \
	$[$wims_homeref_mean]/10.
 !set wims_name_you=usted es <b>$wims_firstname $wims_lastname</b>, accediendo a
 !if _exam isin $session
  !distribute items Otros ejercicios del examen,\
	Tiempo restante de examen:,\
	cuando se cargue esta página\
	into wims_name_back,wims_name_examremain,wims_name_whenloaded
 !endif
 !if _check isin $session
  !let wims_page_name=Page
 !endif
!endif

!if adm/class isin $module
 !distribute line Área de los profesores\
	Área de los estudiantes\
	Clases de ejemplo\
	Autentificación del profesor\
	Autentificación de los participantes\
	Enseñanza primaria\
	Enseñanza secundaria\
	Universidad\
	into wims_name_n_supervisor,wims_name_n_participant,wims_name_n_example,\
	wims_name_n_authsupervisor,wims_name_n_authparticipant,wims_name_n_E,wims_name_n_H,wims_name_n_U
!endif

!if adm/new isin $module
  !distribute line nuevos módulos\
  actualizaciones de módulos\
  últimos cambios del sistema\
  RSS nuevos módulos\
  RSS actualizaciones de módulos\
  into wims_name_mod_new,wims_name_mod_modif,wims_name_mod_sys,wims_name_rss_new,wims_name_rss_modif
!endif

!if $wims_user=$empty
  !distribute line Create a class\
  into wims_name_classcreate
!endif

!if adm/modtool isin $module or adm/createxo isin $module or $wims_user!=$empty
  !distribute line Test the module\
   Document manager\
   Module content\
   Other files\
   Properties\
   Save\
   Check diff\
   Publish it\
   New Module\
   List of modules\
   Binary files\
   Backup the module\
   Modtool\
   Createxo\
   Quicktool\
   Latex2wims\
   Account properties\
   Script Tester\
   OEF Documentation \
   Script Library\
   Answer types\
   Doc technic\
   Back to file list\
   Edit file\
 into wims_name_test,wims_name_docgestion,wims_name_modcontent,wims_name_otherfiles,\
wims_name_properties,wims_name_modsave,wims_name_checkdiff,wims_name_publish,wims_name_createnew,\
wims_name_modlist,wims_name_binfile,wims_name_restore,wims_name_modtool,\
wims_name_createxo,wims_name_quicktool,wims_name_latex2wims,wims_name_account_property,\
wims_name_scripttest,wims_name_docoef,wims_name_docslib,wims_name_docanswer,wims_name_doctec,\
wims_name_back3,wims_name_edfile

!distribute line Back to the exercise creation\
   Model list\
   Prepared models\
into wims_name_backcreatexo,wims_name_modellist,wims_name_model

!distribute line Test\
Modify the source\
Save in the development module\
Save into your class\
Save as a new exercise\
Send an image file\
Replace the old one\
into wims_name_testexo,wims_name_exomodify,\
wims_name_putmodtool,wims_name_putclass,wims_name_newversion,\
wims_name_downloadbinary,wims_name_replace

!endif

!distribute line New document\
New  sheet\
New exam\
New class\
New vote\
New exercise\
Class exercises\
into wims_name_add_doc,wims_name_add_sheet,wims_name_add_exam,wims_name_add_class,wims_name_add_vote,\
wims_name_add_exo,wims_name_classexo

!!! for documents

!distribute items WIMS,Clase,Docs,Arriba,Prev.,Sig.,Hist.,Recargar,\
    Versión interactiva,Versión para imprimir,\
    Volver a doc.,Ayuda,Acerca de,\
    Depósito de archivos,\
    Back to the file list,\
	Página de entrada del documento\
    into wims_name_doch_wims,wims_name_doch_class,wims_name_doch_docs,wims_name_doch_up,\
    wims_name_doch_prev,wims_name_doch_next,wims_name_doch_hist,wims_name_doch_reload,\
    wims_name_doch_interactive,wims_name_doch_printable,\
    wims_name_doch_back,wims_name_doch_help,wims_name_doch_about,\
	wims_name_doch_upload,wims_name_doch_filelist,wims_name_doch_main
    
!if adm/class/cdt isin $module
 !distribute line Add a date\
   Add file\
   Add work\
   Configure\
  into wims_name_adddate,wims_name_addfile,wims_name_addtodo,wims_name_config
!endif


wims_name_supervisor=administrador
wims_name_teacher=Cuentas de profesores
wims_name_addteacher=Nuevo profesor
wims_name_modteacher=Propiedades del profesor
wims_name_delteacher=Borrar un profesor
wims_name_student=Cuentas de alumnos
wims_name_addstudent=Nuevo alumno
wims_name_modstudent=Propiedades del alumno
wims_name_delstudent=Borrar un alumno
wims_name_backstruct=Hacer una copia de seguridad de la estructura

!if config isin $module
 !distribute line Página principal de configuración\
 Gestión de la estructura\
 Copias de seguridad y recuperación\
into wims_name_config, wims_name_struct,wims_name_save

!endif

