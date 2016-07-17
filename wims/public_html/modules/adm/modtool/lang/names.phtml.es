!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif

!set name_auth=Autenticación del desarrollador
!set name_prop=Propiedades
!set name_modname=!nosubst Lista de módulos para <em>$(auth_name[1]) $(auth_name[2])</em>
!set name_create=Crear un módulo
!set name_diff=Comprobar las diferencias
!! must be the same as wims_name_modcontent in html/names.phtml.$lang
!! dont succeed not to duplicate
!set name_flist=Lista de ficheros
!set name_files_binfile=Ficheros binarios
!set name_del=Borrar un módulo
!set name_size=Tamaño
!set name_publish=!nosubst Publicar $i_title<br /><span class="tt">$mod</span>
!set name_publication=Publication
!set name_validation_message=Demander au gestionnaire du site de vérifier l'installation.
!set name_compile=Compile latex2wims
!set name_backup=Backup
!set name_edfile=File modification
!set name_showfile=File content

!distribute line Files OEF/src\
Files OEF/src/cpp\
Editable data files\
Translation files\
Configuration files\
into name_files_src,name_files_cpp, name_files_other,name_files_lang,name_files_phtml

!! wims_name_properties
!set name_index=Propiedades

!set name_file=Ficheros binarios existentes
!set name_file1=Fichero
!set name_nofile= Ningún fichero depositado en el módulo.
!set name_depos=Depositar un fichero
!set name_in_module=en el módulo
!set name_replace=un fichero para sustituirlo&nbsp;
!set name_addfile=Añadir otro fichero&nbsp;
!set name_successfile=The file has been uploaded in the module.

!set name_help_addfile=Le nom <span class="tt wims_fname">name_file</span> ne doit contenir\
  que de caractères alphanumériques sans accents ni espaces (ne pas mettre de signe -).
!set name_help_addfile_src=the name of a file of the OEF exercise source\
   must be of the form <span class="tt"> src/name_file.oef</span>
!set name_help_addfile_cpp=Le nom du fichier contenant le source d'un fichier ccp d'un exercice OEF\
 doit être de la forme <span class="tt wims_fname">src/cpp/name_file.cpp</span>.
!set name_help_addfile_other=Le nom du fichier doit être de la forme \
 <span class="tt wims_fname">name_file</span>.
!set name_help_addfile_lang=Le nom du fichier doit être de la forme \
 <span class="tt wims_fname">lang/name_file.xx</span> où\
 <span class="tt wims_fname">xx</span> est le symbole représentant la langue.
!set name_help_addfile_phtml=Vous pouvez modifier certains de ces fichiers pour\
   une configuration plus poussée de votre module.

!set name_gestion=Para ver los ficheros del documento, pulsen el vínculo <span class="wims_button disabled">$wims_name_docgestion</span>
!set name_your_module=Su módulo
!set name_file2=contiene los ficheros siguientes
!set name_updateadress=Ponga la dirección al día
!set name_simpl_address=La dirección de este módulo es una dirección simplificada
!set gnu=!nosubst &copy; $year (<a href=\"COPYING\">GNU GPL</a>)

!set name_type=OEF,documento, ejercicio, herramienta, recreación, deducción
!set name_zone=Zona
!set name_Category=Categoría
!set name_category=!nosubst $wims_name_Type
!set name_createnew=Nuevo módulo
!set name_noquicktool=Quicktool no esta instalado en este servidor
!set name_rename=cambiar nombre
!set name_duplicate=duplicar
!set name_increment=¡No olvidan incrementarlo cuando publican una nueva versión!
!set name_backto=!nosubst Volver a $otit
!set name_this1=de se nuevo módulo
!set name_this2=del módulo actualmente en desarrollo
!set name_levellist=E: escuela primaria; H: escuela secundaria; U: universidad; <br />G: estudio doctoral; R: investigación

!set name_accountchange=Cambiar las propiedades de su cuenta de desarrollo
!set name_empty=deje el campo <span class="wims_label"> contraseña</span> vacío si quieren conservar el antiguo
!set name_change=Se cambió la contraseña de su cuenta.

!set name_translation_language=Other languages

!distribute lines Test options\
  Formula\
  Low image,High image, Mathml\
  Zoom\
  Letter spacing\
  normal,spaced\
  Size of the mathematical formulas\
into name_optiontest,name_formule,name_useropts1, name_useropts2,name_fonte,name_useropts3,\
  name_useropts4

!if $job=modname
  !set name_moddevcnt=!nosubst Tienen $totalcnt módulos en desarrollo.
  !set name_limited=!nosubst lista limitada a $maxlist módulos

  !distribute lines No mostrar más que los módulos cuya dirección contiene\
  Presione el título de un módulo para trabajar\
   No tienen aún módulo en desarrollo. Pulse aquí para \
   Restaurar un fichero de protección\
  into name_browselist,name_clicktitle,name_nomodule,name_restore
!endif

!distribute lines Copiar, cambiar nombre, duplicar, cambiar nombre\
 into name_choice
!set name_move=$(name_choice[2])
!set name_copy=$(name_choice[3])

!if $job iswordof move copy
  !distribute lines Hacer una copia\
   Cambiar el nombre del módulo va a romper las hojas de trabajo que lo utilizan. Garantizan que no es el caso\
 into name_copy,name_warning1
!set name_public_module=!nosubst el módulo público <span class="tt wims_fname">$original2</span>) en su espacio \
de desarrollo bajo la dirección
!set name_warning2=Cambiar el nombre o duplicar un módulo de dirección pública puede conducir a la duplicación \
  de su publicación. ¡Sea muy prudente! Cambiar el nombre o duplicar un módulo de dirección pública\
  puede conducir a la duplicación de su publicación. ¡Sea muy prudente!\
  <p>Si quieren hacer pruebas sobre el módulo, eligen la zona <span class="wims_fname">pruebas</span>.
!set name_warning3=Si ya publicaron este módulo, quiere cambiar esta dirección exactamente según \
  su dirección pública. Si no arriesgan una duplicación de su publicación.</p>
!endif

!if $job=auth
  !set name_intro=Esta herramienta es para desarrollar en línea, módulos para WIMS. \
    Es una herramienta sofisticada y solamente desarrolladores registrados podrán \
    acceder a ella. <p> Por favor, introduzca los datos de su identificación.</p>

  !distribute lines escriba\
   al encargado de este servidor\
   si ha olvidado su contraseña.\
    Si usted tiene interés en desarrollar módulos WIMS, por favor\
    para conseguir una identificación de desarrollador (usuario, contraseña).\
    También usted puede usar\
    para escribir ejercicios interactivos de una manera fácil, sin necesidad de identificación.\
  into name_manager,name_forget,name_developer,name_identification,name_createxo1,\
    name_createxo2

!endif

!if $job=backup
 !set name_save=Ahí tienes el fichero de protección del módulo
 !set name_internal_error= Error interno: imposible de generar el fichero de protección. Quiere contactar el
!endif

!if $job=publish
  !distribute lines Nombre de su cuenta de publicación \
  Tipo de publicación\
  versión desarrollo, versión estable - modificar un módulo existente, versión estable - añadir un nuevo módulo\
  Es una traducción ¿de un módulo que existe <br /> creado por otro autor?\
  Modificantes autorizados\
  ¡Lea esto en primer lugar!\
  El módulo publicado aparecerá en el motor de búsqueda del sitio de aquí a algunos minutos.\
  Si es un error, quiere pedir al gestor del lugar retirar manualmente el módulo que publicaron.\
  Van a recibir un correo electrónico que confirma la recepción del envío.\
  De acuerdo, ande\
  The following domains do not exist\
 into name_publishaccount,name_publishtype,name_prompt,name_translation,name_authorized,name_readhelp,\
   name_local,name_error,name_emailsend,name_goahead,name_warning_nodomain

 !set name_warning0=!nosubst Este módulo tiene una dirección pública. Deben publicarle pues en el centro de\
   publicación $publishname
 !set name_warning01=Quiere entrar su identificación de publicación.
 !set name_warning1=¿Incrementaron la versión del módulo, si publican una nueva versión de un \
   módulo existente? Si no, nadie pondrá al día su nueva versión.
 !set name_warning2=Su módulo tiene una dirección local. No pueden publicarle sino sobre el espacio local \
   de este servidor. ¿Quieren seguir?
 !set name_warning3=La principal ventaja de una publicación en el espacio local es evidenciar \
  el módulo en el motor de búsqueda del servidor local.
  !set name_cheat1=!nosubst Este módulo declara que se satisface con WIMS-$Wver2,\
 mientras que se desarrolló probablemente o modificado bajo este servidor que es \
 de versión $wims_version. Deben poner al día el fichero ÍNDICE del módulo \
 modificando la versión de wims en <span class="tt"> Propiedades< /tt>.
  !set name_cheat2= ¡Si están seguros de lo que hicieron, pueden engañar \
 para hacer creer a los servidores que están en un servidor antiguo (OPERACIÓN MUY ARRIESGADA)!
  !set name_warning_domain=!nosubst You should check the properties of the module and\
     use domains and keywords which are in the helps of the field\
     <span class="wims_label">$wims_name_Domain</span> and \
     <span class="wims_label">$wims_name_Keywords</span>. \
     If none of them is convenient, you could help us by sending your propositions to

  !set name_warning_domain2=!nosubst Click on the field help\
     <span class="wims_label">$wims_name_Domain</span> or\
     <span class="wims_label">$wims_name_Keywords</span> to find the list
  !set name_warning_keywords=!nosubst To improve the referencement of public modules,\
   check the domains and keywords (see the field helps\
   <span class="wims_label">$wims_name_Domain</span> and \
   <span class="wims_label">$wims_name_Keywords</span>),\
   use the technical english versions.\
   You could help us by sending new propositions for domains and keywords to


!set name_warning_keywords_unknown=The following keywords are not in the official \
 list of WIMS keywords.
 !set name_warning_keywords2=Only official keywords will be proposed using autocompletion\
 in the search engine. Have you checked that all keywords\
 you are proposing have no equivalent in the "official" list ? Remember that\
 all words in the title or description are also taken into account by the search engine.
 !set name_warning_suggestion=You could help us by sending new propositions for domains and keywords to
!endif

!if $job=diff
  !distribute lines Ninguna diferencia se encuentra entre la versión de desarrollo y la versión pública del servidor.\
  Demasiadas diferencias existen entre la versión de desarrollo y la versión pública del servidor.\
  Diferencias entre la versión de desarrollo y la versión pública del servidor&nbsp;:\
into name_diff1,name_diff2,name_diff3
!endif

!if $job=restore
 !set name_warning1=Su fichero no tiene el aire de un fichero de protección de un módulo&nbsp;!<p> \
   No pueden restaurar un fichero sino si fue telecargado antes a partir de Modtool. Vuelva a intentar.</p>

 !distribute lines No pude reconocer su fichero como una protección de módulo. Error en el fichero&nbsp;!\
   Ninguna diferencia se encuentra entre el módulo existente (en su espacio de desarrollo) y lo salvaguarda.\
   Demasiada diferencia existe entre el módulo existente (en su espacio de desarrollo) y la salvaguarda.\
   Diferencias entre el módulo existente (en su espacio de desarrollo) y la salvaguarda&nbsp;\
   Dé el fichero de protección que debe restaurarse\
   hacer mostrar las diferencias entre los módulos en primer lugar.\
   Ir a trabajar sobre el módulo\
   Módulo restaurado\
  into name_norecognize,name_diff1,name_diff2,name_diff3,name_restoref,name_show_diff,name_gotowork,\
    name_restored

!set name_illegal= ¡Su protección contiene ficheros de tipos ilegales! Restauración imposible.\
 <p> ¿Es una protección de una antigua versión? Ahora deben copiar los ficheros uno a uno</p>
!set name_warning2=Solas las protecciones desde Modtool o los ficheros cargados a distancia \
   desde el centro de publicación <a href="$downloadsite">$downloadsite</a>\
   se aceptan. Ninguna modificación manual del fichero de archivos se autoriza.
!set name_warning_diff=!nosubst Este módulo va a sustituir completamente al módulo existente a la misma dirección,  \
  sin posibilidad de vuelta. Pero pueden

!endif

!exit
:del
 Un módulo borrado
lo es definitivamente.
!href cmd=reply&jobreq=backup $wims_name_modsave

<p>
<b>Y no olvidan</b> : Una clase virtual o una hoja de
trabajo que hace referencia a su módulo no funcionarán
ya si se borra este módulo.

</p><p>
Está seguro de querer borrar el módulo
!!</p> close after the name of the module
!exit
:delconfirm
El fichero
 <span class="wims_fname">$fname</span>
 del módulo
 <span class="wims_mod_title">$title</span> esta borrado.
!exit

:delfile

Está seguro de querer borrar el módulo
<span class="wims_fname">$fname</span>
del módulo
<span class="wims_mod_title">$title</span>&nbsp;?
!exit
