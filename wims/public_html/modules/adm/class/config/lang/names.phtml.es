!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif

!set classname=<b><font color=green>$wims_classname</font></b>\
 de <b><font color=green>$wims_institutionname</font></b>

!set months=En,Feb,Mar,Abr,May,Jun,Jul,Ag,Sept,Oct,Nov,Dic

!set title=Configuración y Administración

!distribute items encuestas,agenda,\
	cuenta del profesor,mensajes de un foro de discusión,livret de compétences,\
	séquences pédagogiques,messages du forum\
	into name_vote,name_cdt,\
	name_sup,name_forum,name_livret,name_seq,name_forum_mesg

!distribute items zonas,participantes,ejercicios, documentos, profesores,feuilles d'exercices\
into wims_name_zones,wims_name_participants,wims_name_exercises,wims_name_docs,wims_name_teachers,\
name_sheets


!distribute item mensaje del día,\
	ejercicio,hoja de trabajo,examen,documento,participante\
	into name_motd,name_exo,name_sheet,name_exam,name_doc,name_user

!distribute item messages du jour,\
	exercices,feuilles de travail,examens,documents,participants\
	into name_motds,name_exos,name_sheets,name_exams,name_docs,name_users

!if $job=arch
 !set title=Copias de seguridad y Recuperación
 !set name_intro=Puede descargar una copia de seguridad de su clase, en formato   
 !set name_tosend=Para enviar una copia de seguridad de su clase, 
 !set name_namefile=introduzca por favor el nombre del fichero de seguridad
 !set name_help=se le pedirá que seleccione los recursos que quiere recuperar en la clase

 !set name_deposit=!nosubst Su copia de seguridad <tt>$wims_deposit</tt> contiene los recursos\
siguientes. Marque lo que quiera recuperar en su clase.

 !set name_no_restore=I!set no_restore=Imposible hacer la recuperación porque usted comparte las de otra\
	clase. Sólo la clase que originó la participación puede efectuar la recuperación.

 !distribute lines No ha seleccionado nada que recuperar.\
    Recuperar todo salvo la configuración de la clase y la cuenta del profesor.\
    <font color=red>¡Peligro!</font> <small>Ver más abajo.</small>\
   Configuración de la clase.\
   Cuenta del profesor (incluida su contraseña)\
   cuentas de los participantes\
   Cuentas existentes\
   documentos\
   Documentos existentes\
   ejercicios\
   Ejercicios existentes\
   hojas de trabajo\
   Implica la recuperación de los ejercicios.\
   Hojas existentes\
   hojas de examen\
   Implica la recuperación de hojas de trabajo y de ejercicios\
   Exámenes existentes\
   mensajes de discusión\
   Mensajes existentes\
  Registro de las actividades de los participantes y puntuaciones automáticas. Implica la recuperación de cuentas de participantes.\
   Notas introducidas por el profesor\
  Notas existentes\
   un agenda de la classe\
   un agenda existant\
   Un livret de compétences\
   un livret existant\
   Séquences pédagogiques\
   Implique la restauration de feuilles de travail, d'exercices, des examens et des documents\
   Séquences existantes\
   Método de recuperación\
   Remplacement\
Recuperar los recursos seleccionados\
   Fusion\
remplacer les ressources existantes excepté les comptes de  participants et les exercices de la classe. Pour ces derniers, ceux ayant mêmes noms seront remplacés par les données restaurées et les autres seront gardés\
   Restaurer les ressources sélectionnées\
 into name_noselect,name_all,name_danger,name_config,name_teacher,name_part,name_part1,name_doc,\
   name_doc1,name_exo,name_exo1,name_sheet,name_sheet0,name_sheet1,name_exam,name_exam0,name_exam1,name_forum,\
   name_forum1,name_activity,name_manual,name_manual1,name_cdt,name_cdt1,name_livret,name_livret1,name_seq,\
   name_seq0,name_seq1,name_method,name_replace,name_replace1,name_merge,name_merge1,\
   name_selectrestore
   
!distribute lines Backup resources restored to the class\
   Restoration of participant accounts (as well as activity register) is refused because there is not enough space left.\
   Class expiration date has been modified after restoration, because the uploaded date is\
 into name_restore1,name_restore2,name_restore3

 !distribute items unrecognizable, too early, too late into ebad,eearly,elate

 !distribute lines Lo sentimos, no se ha podido guardar su clase. Error interno.\
  Este es el fichero en el que ha guardado su clase\
  Cliquez dessus pour l'enregistrer sur votre ordinateur.\
  También puede hacer una\
  Copia selectiva de seguridad\
  \
  pour modifier le fichier de sauvegarde ci-dessus et enregistrez-le.\
 into name_download1,name_download2,name_download3,name_download4,\
   name_selective1,name_selective2,name_selective3

 !set name_download5= El tamaño de este fichero de seguridad puede superar el límite autorizado\
 para su envío al servidor. Para reducir el tamaño del fichero, puede hacer una
 
 !goto commun
!endif

!if $job=clean
 !set title=Eliminación de la clase
 !set name_lines=líneas en los registros de actividad de participantes.
 !set name_empty=¡Su clase está vacía! No hay recursos en su clase que puedan borrarse.
 !set name_no_erase=No se pueden eliminar porque usted está compartiendo los de otra clase.

 !distribute lines Eliminar todo lo que se pueda eliminar\
   También se borrarán los registros de actividad\
   También se borrarán las hojas de examen\
   Hacer una copia de seguridad de la clase\
   Les ressources actuelles de votre classe\
 into name_cleanall,name_erase1,name_warning_exam,name_saveclass,name_ressource
  !set name_warning_clean=¡Los recursos borrados desde esta página no se pueden recuperar!
 !goto commun
!endif

!if $job=neighbor
 !set title=Clases vecinas
  !set name_noclass=No puede definir clases vecinas porque no hay ninguna otra clase en\
 este sitio.
 !set name_toomany=Il y a trop de classes virtuelles sur le site. Donnez un mot clé pour\
  rechercher les classes qui vous concernent&nbsp;
 !set name_toomany2=Il y a encore trop de classes correspondant à votre recherche. Veuillez\
  donner un mot clé plus précis.

 !distribute lines Rechercher une classe\
  Aucune classe n'est trouvée pour votre recherche. Réessayez.\
  Afficher les classes d'exemple du serveur\
  Les relations de voisinage entre des classes virtuelles permettent l'échange de ressources et/ou déplacement entre les classes.\
  Cliquez sur le nom d'une classe pour changer vos relations de voisinage avec elle.\
  Clases en el mismo idioma que la suya\
  Clases en otro idioma\
  Ejemplos\
into name_research,name_noclass,name_exampleclass,name_help,name_changeneigh,\
  name_samelanguage,name_otherlanguage,name_example

 distribute lines Declaración vecindad\
   Compartir un recurso\
   por usted\
   por otro\
   Relaciones mutuas de compartir activas.\
   Usted comparte sus recursos.\
   Comparte sus recursos.\
   Permisos mutuos para compartir.\
   Tiene permiso para compartir sus recursos.\
   Le permite compartir sus recursos.\
   Detener la relación de compartir.\
   Compartir\
   les importer tous\
   Ressources d'enseignement\
   Importer d'autres ressources\
   Clases que pueden compartir los recursos de su clase\
   Recurso permitido\
   Activo\
   Lista de otras clases\
   Info recursos compartidos\
   Afficher les classes d'exemple du serveur\
 into name_declaration,name_sharing,name_byyou,name_other,name_actif,name_share1,name_share2,\
 name_permit1,name_permit2,name_permit3,name_stopsharing,name_share,name_everybodyimport,name_teaching,\
 name_otherone,name_classsharing,name_ressourceallowed,name_active,name_listclass,name_info,name_exampleclass,\
 name_import_resource,name_youcan,name_fromtheclass,name_click_ok
 
 !set name_nonewres=!nosubst Il n'y a aucun (nouveau) type de ressources dans la classe \
  <em><font color=blue>$nei_description</font></em> qu'elle vous autorise à partager. 

 !set name_newres=!nosubst La classe <em><font color=blue>\
  $nei_description</font></em> vous <b>autorise</b> à partager ses

 !set name_chooseres=!nosubst Choisissez les ressources que vous <b>autorisez</b> la classe <em><font color=blue>\
  $nei_description</font></em> à partager&nbsp; (<i>sélectionnez puis cliquez sur <tt>$wims_name_tosave</tt></i>)

 !set name_warning_authorized=!nosubst La classe <em><font color=blue>$nei_description</font></em>\
  vous autorise à partager certaines ressources. Vous ne devez pas l'autoriser à partager les mêmes ressources \
  sous peine de confusion. Commencez par vous entendre avec elle et avec toutes les classes avec lesquelles vous\
  voulez partager des ressources.
 
 !distribute lines Relaciones con la clase\
   no ha declarado la suya como vecina\
   le acepta como vecina\
   avec\
   Comparte ya los recursos siguientes de la clase\
   no tiene recursos que usted pueda importar\
   tiene los siguientes recursos importables\
   Mismo título en la clase destino\
   Vacía\
   en preparación\
   Sustituir\
   Este login ya se está usando en su clase\
   Un participante borrado sigue existiendo en su clase\
   Importación a partir de la clase\
   Transferido con éxito\
   cuentas de participantes de la clase vecina\
   Comprobar el resultado\
 into name_neighbor_relation,name_text1,name_text2,name_with,name_sharealready,\
   name_no_ressource,name_importable,name_same_title,name_empty,name_inpreparation,\
   name_replace,name_existinglogin,name_part_erased,name_import,name_transfered,\
   name_neigh_account,name_verify

 !set name_inactif=!subst El(la) $(name_$itype) ha sido puesto(a) en estado inactivo para permitirle \
  modificarlo si lo desea.

 !set name_accept=!nosubst ¿Acepta usted la clase <em><font color=blue>\
$nei_description</font></em> como vecina suya?
   
 !if $job2=stopshare
  !set title=Dejar de compartir un recurso
  !set name_warning=Su clase tiene un registro de actividades activo y los\
 recursos compartidos no están vacíos. Si deja de compartir este recurso\
 ahora, ya no podrá volver a compartirlo más tarde. <p>\
 ¿Está seguro de querer dejar de compartir definitivamente este recurso?
 !set name_stop=dejar de compartirlo.
 !endif
 !if $job2=sharelist
  !set title= Información sobre recursos compartidos.
  !set name_sharelist=!nosubst Comparte $(name_$rec) de
  !distribute lines No comparte ningún recurso de otras clases.\
  Comparte recursos de otras clases\
  into name_noresource,name_resource
  !endif
  
  !if $job2=addshare
  !set title=Compartir los recursos de una clase
  !set name_class_share=La clase <em><font color=blue>$nei_description</font></em></b>\
   le permite compartir sus recursos siguientes.
  !distribute lines disponible\
    Ya está compartiendo.\
    No puede compartirlos porque ya comparte los de otra clase.\
     limpiar sus propios recursos\
    si es posible.\
     ¡Es muy peligroso compartir la cuenta del profesor!\
  into name_available,name_actually_sharing,name_nosharing,name_cleanup,name_ifpossible,\
    name_dangerous
  
  !set name_warning1=No puede compartirlos porque ha permitido a otras clases compartir\
   SUS recursos del mismo tipo. No está autorizado compartir en cascada. Por tanto debe \
   primero poner fin a los permisos para compartir por\
   parte de la otra clase antes de poder compartir los de la clase
  !set name_warning2=!nosubst No puede compartirlos porque sus propios $(name_$r) no están vacíos.\
   Antes de compartir, debe primero
  !set name_warning_erase=!nosubst  ¡Al compartir va a BORRAR sus $(name_$r) existentes!\
     Se perderán definitivamente si no tiene una copia de seguridad.
   
  !endif
  
  !distribute items ---,<small>el profesor</small>,\
	<small>los participantes</small>,\
	<small>profesor y participantes</small> into n_n0, n_n1, n_n2, n_n3
	
 !goto commun
!endif

!if $job=connect
 !set title=Conectar a otros servidores / plataformas
 !set name_listserver=Lista de conexiones de los servidores
 
 !distribute lines Probar una conexión a servidor\
   Probar una clase conectada\
   Añadir la conexión a un servidor\
   Administrar una clase conectada\
   local class, remote class\
   class definition, user list, score averages, score details,all but class definition\
   Clase remota\
   Servidor remoto\
   Synchronize\
 (with the other one) for\
   Administrar\
   Eliminar \
   La conexión al servidor remoto funciona.\
   Se ha añadido la conexión a su clase, pero el servidor remoto devuelve un mensaje de error\
  Esta clase no tiene conexiones a otros servidores.\
  La conexión ha sido rechazada por el servidor remoto. Mensaje de error\
  Clase remota a prueba\
  La conexión funciona. La clase remota devuelve datos\
  Para conectarse a una clase en el servidor de más arriba, por favor especifique\
  Identificador de la clase remota\
  Si la clase remota está vacía, el servidor creará una nueva clase en el servidor remoto, duplicando las propiedades de esta.\
  Actualizar automáticamente la clase remota con los cambios efectuados\
  Permitir que la clase remota modifique esta\
  This class has no connections to other servers.\
  Ha declarado las siguientes conexiones a otros servidores.\
  Servidor\
  En estos momentos, este servidor WIMS permite conexiones desde los siguientes servidores.\
 into wims_name_connecttest,wims_name_classtest,wims_name_addconnection,wims_name_connectmanage,name_prompt1,\
   name_prompt2,name_synchronize,name_withotherone,name_remoteclass,name_remoteserver,wims_name_Manage,\
   wims_name_destroy,name_working,name_error1,name_errornoreply,name_errorreject,name_check,name_data,\
   name_toconnect,name_identifier,name_help,name_automatically,name_allow,name_noconnection,name_declaration,\
   wims_name_server,name_listserver

 !goto commun
!endif

!if $job=access
 !set title=Configuración del acceso a los recursos
 !goto commun
!endif

!if $job=grestrict
 !set title=Restricción del acceso a la puntuación
 !goto commun
!endif

!if $job=present
 !set title=Configuración de la apariencia de la clase
 !goto commun
!endif

!if $job=oefdefault
 !set title=Parametrización por defecto de los módulos OEF
 !distribute lines Une série aura\
   Niveau de sévérité\
   Chronomètre\
   secondes\
   Nombre de réponses affichées dans les QCM\
   Donner une solution (si disponible) ?\
   jamais,si la note est non maximale,toujours\
   Toujours afficher une bonne réponse dans les QCM.\
   Pénalité pour mauvaise réponse dans les QCM.\
   Afficher la bonne réponse.\
   Permettre les indications (si disponibles).\
  into name_series,name_severity,name_chrono,name_secondes,name_qcm,\
    name_solution,name_prompt,name_prompt1,name_prompt2,name_prompt3,name_prompt4

   !set name_warning=Vous pouvez mettre deux nombres dans le chronomètre, une petite\
     limite suivie d'une plus grande. Dans ce cas, la première limite déclenche \
   la réduction du score, qui sera à  0 quand la seconde limite est atteinte.
  
 !goto commun
!endif

 de la actividad de gestión de su clase (usted debe ser el origen de toda
esta actividad; de lo contrario, será necesario comprobar que no se ha 
producido una filtración de su contraseña de profesor).

<li><p>Configurar las
!href cmd=renew&job=grestrict restricciones a nivel de clase
 de los sitios que tienen acceso a las calificaciones.

<li><p>Otras definiciones de seguridad en
!href cmd=renew&job=list la configuración de la clase
.
!if $job=security
 !set title=Actividades de gestión de seguridad disponibles
 !set name_see_activity2=usted debe ser el origen de toda esta actividad; de lo contrario, \
  será necesario comprobar que no se ha producido una filtración de su contraseña de profesor
 !set name_see_activity1=Ver el registro
 !distribute lines Configurar las restricciones a nivel de clase\
  de los sitios que tienen acceso a las calificaciones.\
 Otras definiciones de seguridad en\
 la configuración de la clase\
 into name_restriction1,name_restriction2,name_otherrestriction1,name_otherrestriction2
 !goto commun
!endif

!if $job=authtype
 !set title=Autenticación por un anuario ldap
 !set name_intro_authtype=Sélectionnez <tt>ldap</tt> et remplissez cette page si \
   vous désirez utiliser une authentification par un annuaire ldap.
 !goto commun
!endif

!if $job=import
 !set code1=Aucun
 !set code2=$wims_name_yes mais différent
 !set code3=$wims_name_yes, actif et différent
!endif

!if $job=propagate
  !if $wims_supertype=2
   !set name_thisclass=du portail
   !set name_subclasses=sous-classes
  !else
   !set name_thisclass=de la zone actuelle
   !set name_subclasses=zones dépendantes
  !endif
   
 !distribute lines Las configuraciones han sido enviadas a las $name_subclasses con éxito\
  Puede elegir enviar las configuraciones siguientes $name_thisclass a todas sus $name_subclasses\
 into name_propagate_succes,name_propagate_choose

 !set name_warning=Note que las $name_subclasses no repercutirán los cambios posteriores de las\
  configuraciones $name_thisclass. Debe volver a enviar los cambios cada vez que quiera \
  que se apliquen a las $name_subclasses.

!endif

!if $job=log
  !set name_warning_log=Aquí se encuentra el registro de ciertas actividades de administración de\
su clase. Este registro le permite comprobar si hay actividades sospechosas.
!endif

!if $job=index
 !set title=!nosubst Actualisation de l'index $tit
 !set name_done=Fait.
 !set name_result=Résultat du script

  !if $job2=structure
   !set tit=des zones
  !endif
  !if $job2=userlist
   !set tit=des participants
  !endif
  !if $job2=teacherlist
   !set tit=des enseignants
  !endif
  !if $job2=oef
   !set tit=des exercices
  !endif
  !if $job2=doc
   !set tit=des documents
  !endif
!endif

!if $job=list
  !distribute line Nombre del Centro\
    Nombre de la clase\
    Opciones\
    Modtool Account\
    Bloqueo de conexión\
    Best scores (number / anonymity)\
    Límite del número de participantes\
    Fecha de expiración\
    Grabación de los ejercicios\
    Grabación de los exámenes\
    visibles par les élèves\
    Modifier l'apparence \
    Preferencias personales\
    Enviar las configuraciones a las zonas inferiores\
    Clases vecinas\
    Otros servidores\
    Utiliser une authentification\
    des participants par annuaire ldap\
    Actualiser les index\
   dont le changement de\
    Faire une sauvegarde ou restauration de la classe\
    Restricciones de recursos\
    restreindre les sites \
    pour lequels les scores sont enregistrés\
    Eliminación selectiva\
   Configurer les\
    Utilización actual del espacio de disco\
    el límite es\
  into name_name_institution,name_name_class,name_optionword,name_devaccount,name_lock_level,\
    name_bestscore,name_limit,name_expirationdate,name_register_exo,name_register_exam,\
    name_visible,name_apparence,name_pref,name_dependant_zone,name_neigh,name_link,name_useauth,name_ldap,name_index,\
    name_change,name_load,name_restriction1,name_restriction2,name_score,name_clean,\
    name_config,name_disk,name_limit

!endif

:commun
!distribute line Autenticación\
Preferencias\
Restricción de acceso\
Parametrización OEF\
Clases vecinas\
Gestión de la seguridad\
Eliminación selectiva\
Actualisar\
Otros servidores\
Contraseñas\
zonas inferiores\
Apariencia\
Restricción de la puntuación\
Dirección de una plataforma\
de\
External authentification\
into wims_name_config_auth,wims_name_config_pref,wims_name_config_restr,wims_name_config_oef,\
wims_name_config_neigh,wims_name_config_secure,wims_name_config_clean,wims_config_refresh,\
wims_name_config_otherserver,wims_name_config_passwd,wims_name_config_propagate,wims_name_config_present,\
wims_name_config_score,wims_name_config_ent,name_of,wims_name_external_auth

!distribute lines Estaciones de trabajo seguras\
   Hoja de estilo\
   Logo de la clase\
   Posición del logo\
   arriba a la izquierda, arriba a la derecha\
   Tema de estilo de la clase\
   Juego de iconos\
   Nivel académico\
   Ordenadores autorizados a las notas\
   Contraseña de inscripción\
   Contraseña de profesor\
   Límites de registro de ejercicios y exámenes\
   Vínculos sobre una plataforma o una página Internet\
   Color de fondo de las páginas\
   Color de fondo de los menús\
   Couleur des liens dans les menús\
   Imagen de fondo de las páginas\
   transferir un fichero css\
   Gama de colores de los resultados (de 0 a 10)\
  into name_secure,name_css,name_logo,name_position_logo,name_logo_side,name_theme,\
   name_theme_icon,name_level,name_security,name_password,name_supass,name_exolog,name_ent,\
   name_background_color,name_menu_color,name_refmenu_color,name_image,name_css_transfer,name_colorscore

!set name_content_style = Puede definir aquí la hoja de estilo de la clase:\
<br>(lorsque <tt>$name_css</tt>  est sur <tt>class</tt>)&nbsp;:

!set name_content_style2=o copiar aquí la hoja de estilo de la clase

!exit
:arch
 Ha enviado unos recursos guardados a partir de otra clase.
 Si usted recupera recursos incompatibles en su clase, quedará inutilizable.
 !href cmd=help&special_parm=dependencies ¿Por qué?
 <p>
 !href cmd=reply&job=list Deténgase
 si no está completamente seguro de lo que está haciendo (en todo caso, 
 guarde una copia del estado actual antes de continuar).
 
 :arch_end
 
<p><b>IMPORTANTE</b>. 
1. No hay verificación de los datos que ha enviado y el sistema no
autoriza la modificación manual de los archivos de copia de seguridad.
Los errores introducidos por una modificación manual de los archivos
puede ocasionar comportamientos imprevisibles en su clase.
<p>
2. Salvo en caso de absoluta necesidad, evite recuperar
<font color=red>la configuración de la clase</font> y
<font color=red>la cuenta del profesor</font>.
Los errores en los datos enviados para estos dos campos pueden hacer
perder por completo el control de su clase.
<p>
3. Puede utilizar la copia de seguridad de una clase para instalar una
nueva. En este caso, evite recuperar los registros de la actividades y las
notas y puntuaciones (manuales y automáticas). Estos dos tipos de recursos 
no pueden borrarse una vez instalados (medida de seguridad). Y muchas 
operaciones de mantenimiento de la clase son imposibles cuando la clase 
contiene calificaciones.

!exit

:clean
<b>ATENCIÓN</b>. No puede borrar recursos de la clase
 cuando ya han comenzado las actividades de los participantes.
 <p>
 Esta es una medida de seguridad importante. Si no le gusta
 esta limitación, piense en los dos siguientes aspectos:
 <p>
 Por un lado supongamos que un estudiante le roba la contraseña. Si entra
 en esta página para borrarlo todo, los otros estudiantes que no tienen
 culpa de nada lo van a pasar mal, y las actividades pedagógicas que había
 preparado usted resultarán muy perjudicadas.
 <p>
 Por otro lado, los diferentes recursos de la clase son interdependientes.
 Si borra ciertos recursos sin borrar los que dependen de ellos, la
 clase ya no funcionará.
 !href cmd=help&special_parm=dependencies Ejemplos.
 <p>
 De todas formas, si quiere hacer desaparecer de verdad esta clase, siempre puede
 borrarla (poniendo como fecha de expiración la de hoy la clase desaparecerá
 mañana por la mañana), o
 <a href="mailto:$wims_site_manager?subject=Por favor borre mi clase">pedir
 al administrador del sitio</a> que la borre por usted.
 !exit
 
 :clean2
 <p><b>Observaciones</b>. 1. Sólo se puede acceder a esta página mientras 
la página está en preparación. Una vez que han comenzado las actividades de 
los participantes, ya no es posible borrar los recursos.
<p>
2. Los recursos compartidos por varias clases sólo pueden borrarse
desde la clase maestra que comparte. Las otras clases deben
primero
!href cmd=reply&job=neighbor&job2=sharelist dejar de compartir
 los recursos antes de borrarlos.

!exit

:connect_first_info
La conexión a servidores/plataformas permite que su clase se comunique directamente con
una clase en otro servidor WIMS u otra plataforma web de e-learning. Los participantes
pueden navegar de forma transparente entre las clases conectadas.
<p>
En particular, puede crear una réplica de esta clase en un servidor WIMS remoto,
de forma que si el servidor local queda inutilizable momentáneamente, el trabajo
puede continuar en la clase espejo. Las puntuaciones logradas en la réplica 
pueden fusionarse más tarde.
!exit
:connect_first

Este servidor WIMS no ha declarado ningún servidor remoto que admita 
 conexiones. Para utilizar esta capacidad de conexión, el
 <a href="mailto:$wims_site_manager?subject=conexión a servidor">administrador
 del sitio</a> debe declarar el servidor remoto, y el servidor remoto debe también
 declarar que este servidor WIMS tiene permiso de conexión.
 (El administrador del sitio puede consultar el fichero
 <tt>$basedir/log/classes/.connections/myself</tt> en busca de detalles de
 cómo declarar conexiones a sitios).
 !exit
 
:import2
  La hoja de trabajo que quiere importar puede utilizar ejercicios
   definidos en la clase vecina.
   <p>
   Si los mismos ejercicios no existen en la suya, la hoja importada
   no funcionará correctamente. Por favor verifique con cuidado que todos
   los ejercicios de la clase vecina tiene su réplica en la suya.
!exit
:import3
 Las hojas de examen se basan en las hojas
   de trabajo para constituir sus contenidos. <p>
   Importar una hoja de examen no tiene sentido si no tiene exactamente las
   mismas hojas de trabajo que la clase vecina y si estas hojas no están
   dispuestas en el mismo orden en las dos clases.
   <p>
   De no ser así, con seguridad la hoja de examen importada tendrán 
   comportamientos erráticos.
!exit 
:import4

Está a punto de sustituir un(a) $(name_$itype)
  present(e) en su clase por el recurso importado. No habrá ninguna
  oportunidad de volver atrás tras esta operación.
!exit

:import5
  No se ha añadido a su clase ninguna cuenta de participante. Compruebe
 si su clase está llena (y si queda espacio en el sitio web para añadir
 nuevos participantes).
!exit

:auth1
A esta herramienta de configuración sólo puede accederse desde las 
estaciones de trabajo seguras.
<p>
Como no ha definido ninguna estación de trabajo segura, vamos a
realizar la autentificación enviándole un código secreto a su dirección 
de correo electrónico.
Por favor lea el correo, busque el código y tecléelo debajo.
!exit
:auth2
<b>Notas</b>. Esta autentificación sirve para asegurarse de que aunque
se perdiera o robaran su contraseña, los daños a su clase serían limitados.
El proceso de autentificación es mucho más sencillo si define estaciones
de trabajo seguras de forma correcta, conservando un alto nivel de seguridad.

!exit

:download
<b>Nota</b>. Según las actividades de la clase, normalmente son los 
registros de las actividades de los participantes, los mensajes de 
discusión y los documentos de la clase los que componen la mayor parte 
del tamaño. Puede plantearse la posibilidad de hacer varias copias 
selectivas de seguridad para los diferentes recursos.

!exit