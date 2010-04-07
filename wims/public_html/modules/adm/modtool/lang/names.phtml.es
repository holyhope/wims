!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif

!set name_auth=Autenticación del desarrollador
!set name_prop=Propiedades
!set name_modname=Lista de módulos para <em>$auth_name</em>
!set name_create=Crear un módulo
!set name_diff=Comprobar las diferencias
!set name_flist=Lista de ficheros
!set name_binfile=Ficheros binarios
!set name_del=Borrar un módulo
!set name_size=Tamaño
!set name_publish=!nosubst Publicar <em>$i_title</em><br>\
	<tt><font size="+0">$mod</font></tt>

!set name_file=Ficheros binarios existentes
!set name_nofile= Ningún fichero depositado en el módulo.
!set name_depos=Depositar un fichero
!set name_in_module=en el módulo
!set name_replace=un fichero para sustituirlo&nbsp;
!set name_addfile=Añadir otro fichero&nbsp;
!set name_gestion=para ver los ficheros del documento, pulsen el vínculo <tt>$wims_name_docgestion</tt>
!set name_your_module=Su módulo
!set name_file2=contiene los ficheros siguientes
!set name_updateadress=Ponga la dirección al día
!set name_simpl_address=La dirección de este módulo es una dirección simplificada
!set gnu=&copy; $year (<a href=COPYING>GNU GPL</a>)

!set name_type=ejercicio, herramienta, documento, recreación, OEF, deducción
!set name_zone=Zona
!set name_category=Categoría
!set name_createnew=Nuevo módulo
!set name_noquicktool=Quicktool no esta instalado en este servidor
!set name_rename=cambiar nombre
!set name_duplicate=duplicar
!set name_increment=¡No olvidan incrementarlo cuando publican una nueva versión!
!set name_backto=!nosubst Volver a $otit
!set name_this1=de se nuevo módulo
!set name_this2=del módulo actualmente en desarrollo
!set name_levellist=E: escuela primaria; H: escuela secundaria; U: universidad; <br>G: estudio doctoral; R: investigación

!set name_accountchange=Cambiar las propiedades de su cuenta de desarrollo
!set name_empty=deje el campo “<tt> contraseña< /tt> “vacío si quieren conservar el antiguo
!set name_change=Se cambió la contraseña de su cuenta.

!if $job=modname
  !set name_moddevcnt=!nosubst Tienen $totalcnt módulos en desarrollo.
  !set name_limited=!nosubst lista limitada a $maxlist módulos

  !distribute lines No mostrar más que los módulos cuya dirección contiene\
  Presione el título de un módulo para trabajar\
   No tienen aún módulo en desarrollo. Pulse aquí para \
   Restaurar un fichero de protección\
  into name_browselist,name_clicktitle,name_nomodule,name_restore
!endif

!if $job iswordof move copy
  !distribute lines Copiar, cambiar nombre, duplicar, cambiar nombre\
   Hacer una copia\
   Cambiar el nombre del módulo va a romper las hojas de trabajo que lo utilizan. Garantizan que no es el caso\
into name_choice,name_copy,name_warning1
!set name_public_module=!nosubst el módulo público<tt>$original2</tt>) en su espacio \
de desarrollo bajo la dirección
!set name_warning2=Cambiar el nombre o duplicar un módulo de dirección pública puede conducir a la duplicación \
  de su publicación. ¡Sea muy prudente! Cambiar el nombre o duplicar un módulo de dirección pública\
  puede conducir a la duplicación de su publicación. ¡Sea muy prudente!\
  <p>Si quieren hacer pruebas sobre el módulo, eligen la zona <tt>pruebas/tt>.
!set name_warning3=Si ya publicaron este módulo, quiere cambiar esta dirección exactamente según \
  su dirección pública. Si no arriesgan una duplicación de su publicación.
!endif

!if $job=auth
  !set name_intro=Esta herramienta es para desarrollar en línea, módulos para WIMS. \
    Es una herramienta sofisticada y solamente desarrolladores registrados podrán \
    acceder a ella. <p> Por favor, introduzca los datos de su identificación.

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
  Es una traducción ¿de un módulo que existe <br> creado por otro autor?\
  Modificantes autorizados\
  ¡Lea esto en primer lugar!\
  El módulo publicado aparecerá en el motor de búsqueda del sitio de aquí a algunos minutos.\
  Si es un error, quiere pedir al gestor del lugar retirar manualmente el módulo que publicaron.\
  Van a recibir un correo electrónico que confirma la recepción del envío.\
  De acuerdo, ande\
 into name_publishaccount,name_publishtype,name_prompt,name_translation,name_authorized,name_readhelp,\
   name_local,name_error,name_emailsend,name_goahead

 !set name_warning0=!nosubst Este módulo tiene una dirección pública. Deben publicarle pues en el centro de\
   publicación $publishname (<tt>$centralhost</tt>). Quiere entrar su identificación de publicación.
 !set name_warning1=¿Incrementaron la versión del módulo, si publican una nueva versión de un  \
   módulo existente? Si no, nadie pondrá al día su nueva versión.
 !set name_warning2=Su módulo tiene una dirección local. No pueden publicarle sino sobre el espacio local  \
   de este servidor. ¿Quieren seguir?
!set name_warning3=La principal ventaja de una publicación en el espacio local es evidenciar \
  el módulo en el motor de búsqueda del servidor local.
!set name_cheat1=!nosubst Este módulo declara que se satisface con WIMS-$Wver2,\
 mientras que se desarrolló probablemente o modificado bajo este servidor que es  \
 de versión $wims_version. Deben poner al día el fichero ÍNDICE del módulo \
 modificando la versión de wims en <tt> Propiedades< /tt>.
!set name_cheat2= ¡Si están seguros de lo que hicieron, pueden engañar \
 para hacer creer a los servidores que están en un servidor antiguo (OPERACIÓN MUY ARRIESGADA)!

!endif

!if $job=diff
  !distribute lines Ninguna diferencia se encuentra entre la versión de desarrollo y la versión pública del servidor.\
  Demasiadas diferencias existen entre la versión de desarrollo y la versión pública del servidor.\
  Diferencias entre la versión de desarrollo y la versión pública del servidor&nbsp;:\
into name_diff1,name_diff2,name_diff3
!endif

!if $job=restore

 !set name_warning1=Su fichero no tiene el aire de un fichero de protección de un módulo&nbsp;!<p> \
   No pueden restaurar un fichero sino si fue telecargado antes a partir de Modtool. Vuelva a intentar.

 !distribute lines  No pude reconocer su fichero como una protección de módulo. Error en el fichero&nbsp;!\
   Ninguna diferencia se encuentra entre el módulo existente (en su espacio de desarrollo) y lo salvaguarda.\
   Demasiada diferencia existe entre el módulo existente (en su espacio de desarrollo) y la salvaguarda.\
   Diferencias entre el módulo existente (en su espacio de desarrollo) y la salvaguarda&nbsp;\
   Dé el fichero de protección que debe restaurarse\
   hacer mostrar las diferencias entre los módulos en primer lugar.\
   Ir a trabajar sobre el módulo\
   Módulo restaurado\
  into name_norecognize,name_diff1,name_diff2,name_diff3,name_restore,name_show_diff,name_gotowork,\
    name_restored

!set name_illegal= ¡Su protección contiene ficheros de tipos ilegales! Restauración imposible.\
 <p> ¿Es una protección de una antigua versión? Ahora deben copiar los ficheros uno a uno
!set name_warning2=Solas las protecciones desde Modtool o los ficheros cargados a distancia \
   desde el centro de publicación  <a href="$downloadsite">$downloadsite</a>\
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

<p>
Está  seguro de querer borrar el módulo

!exit
:delconfirm
El fichero
 <font color=blue><em>$fname</em></font>
 del módulo
 <font color=blue><em>$title</em></font> esta borrado.
!exit

:delfile

Está  seguro de querer borrar el módulo
<font color=blue><em>$fname</em></font>
del módulo
<font color=blue><em>$title</em></font>&nbsp;?
!exit
