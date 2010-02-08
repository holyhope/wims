!set lang_exists=yes

!set name_intromain=Esta utilidad le permite al administrador del sitio llevar en línea el mantenimiento\
 de la instalación WIMS. El acceso a ella está controlado estrictamente mediante\
 definiciones en el fichero de configuración 

!!!list
 !distribute lines Tras la compilación es necesario configurar la seguridad de la instalación. ¡Por favor ejecute bin/wrapuid como root!\
   Lista de tareas que puede realizar en línea\
   Configuración\
   Chequeo del sistema\
   tras la adición de nuevos recursos (módulos, hojas de trabajo) al servidor.\
   Check/maintain\
   Create/maintain\
into name_warning,name_online,name_configuration,name_checklist,name_mkindex,name_checkmaintain,\
  name_createmaintain

!!help

!set name_warning_help=Por favor use los enlaces de ayuda específicos de los distintos temas de ayuda.

!set name_visit=Visitar

if $job=access
 !set title=Configuración de la normativa de acceso
 !set name_subtitle=Definición de la normativa de acceso
 !exit
!endif

!if $job=activ
  !set title=Actividades actuales del servidor
  !distribute lines Hora del servidor\
    Media de carga\
    minuto\
    minutos\
    hora\
    houras\
    últimos\
    since\
    Número de peticiones\
    Sesiones activas en los últimos 10 minutos\
    Sesión\
    IP del cliente\
    Peticiones\
    Módulo\
  into name_servor_time,name_Load,name_min,name,name_hour,name_hours,name_last,name_since,\
   name_requests,name_activesessions,name_session,name_IP,name_Requests,name_module
 !exit
!endif

!if $job=attrib
  !set title=Comprobación de los permisos de los ficheros
  
  !distribute lines  Todos los permisos de acceso de esta instalación de WIMS están en modo seguro.\
  Los siguientes archivos/directorios pueden ser leídos por otros y no deberían\
  Hay un número muy grande de ficheros y directorios legibles por otros, lo que no debería de ocurrir.\
   El problema sólo se ha corregido de forma parcial. Por favor\
   repita el proceso de nuevo \
   hasta que no queden ficheros/directorios con permisos incorrectos\
   Lista de los permisos corregidos esta vez\
   Los siguientes archivos/directorios tienen el permiso de escritura abierto a otros, lo que no debería de ocurrir\
   Hay un gran número de ficheros/directorios que tienen el permiso de ejecución abierto a otros, lo que no debería de ocurrir.\
   Hay un gran número de ficheros/directorios que tienen el permiso de ejecución abierto a otros, lo que no debería de ocurrir.\
   El dueño de los siguientes ficheros/directorios no es WIMS.\
   Los siguientes directorios/ficheros deben tener el permiso de ejecución abierto a todo el mundo, y no lo tienen.\
into name_attrib1,name_attrib2,name_attrib3,name_attrib4,name_repeat,\
  name_attrib5,name_attrib6,name_attrib7,name_attrib8,name_attrib9,name_attrib10,
  name_attrib11
  
  !set name_warning1=WIMS directories should not contain files belonging to others.\
  Now you MUST manually check the origin of these files, and either erase\
  them, or change their ownership.
  !set name_warning2=Importante recomendación de seguridad: por favor compruebe\
   el dueño de los ficheros <tt>public_html/bin/ch..root</tt>,\
   <tt>public_html/bin/wrap..exec</tt> and <tt>bin/wimsd</tt>.\
   Esto es crucial para la seguridad de su instalación. Para ello\
   debe ejecutar el guión bin/wrapuid como root.
 !set name_warning3=Estos permisos erróneos constituyen un riesgo de seguridad para su instalación.\
  El problema acaba de ser corregido, pero debe estar alerta y comprobar\
  los permisos de acceso con más frecuencia. Si reaparece el mismo problema,\
  debe plantearse la posibilidad de una intrusión en su sistema, y los datos\
  de este servidor pueden estar en peligro.
 !exit
!endif

!if $job=backup

 !distribute lines  La realización de copias de seguridad de los datos no está activada en este servidor.\
   Pulse aquí\
   para configurar la salvaguardia diaria automática de los datos.\
   Última salvaguardia de los datos\
   Descargar las copias de seguridad\
   Para recuperar una copia de seguridad vieja, escriba el nombre del fichero (debe ser un archivo *.tgz)\
   Necesitará una conexión rápida si el fichero que quiere descargar es grande.\
into name_backup,name_click,name_daily,name_last,name_download,name_restore,name_fast
 !exit
!endif

!if $job=badconf
  
  !set name_warning1=!nosubst ¡El fichero $fname tiene permisos de lectura por todo el mundo!\
   Hay un riesgo serio de que se haya producido una filtración de la configuración \
   del administración del sitio y/o su contraseña. DEBE cambiar ahora mismo las \
   propiedades de $fname haciéndolo legible sólo por su dueño,
  !set name_warning2=y aumentar la seguridad de las definiciones del fichero en tanto sea posible.
  !set name_warning3=y definir una nueva contraseña de administrador.
  !set name_warning4=Una vez haya hecho esto vuelva a intentar abrir esta página.

 !exit
!endif

!if $job iswordof class bestclass
  !set title=
  !distribute lines Pulse aquí\
   para configurar la normativa de acceso del sitio con respecto a las clases virtuales.\
    There is no virtual class corresponding to your search. \
    Lista de clases de este sitio\
    creada\
    expira\
    se refiere al número de horas de conexión acumuladas en el último mes.\
    best class activity on this period.\
    Participant\
    List of independent classes\
    means cumulative hour.student connexion since\
    best class of cumulative connection hours since\
    Your WIMS virtual class\
    List of classes\
    carga\
    format\
  into name_click,name_config,name_noclass,name_list,name_created,name_expire,name_cumul,name_best,\
  name_part,name_listindependant,name_cumul_student,name_bestcumul,name_yourclass,name_listclass,\
  name_load,name_format
 
  !set name_search1=There are many virtual classes on this site. To find a class, please type a search keyword.
  !set name_search2=There are still too many classes corresponding to your search word. Please give a more precise word.
  !set name_total=!nosubst There are $nbcls class groups or classes in this serveur.
  
  if $job2 iswordof modify erase
  !set title=
  !distribute lines Propiedades importantes de la clase virtual \
     de\
     número de serie\
     Esta clase viene con la distribución de WIMS.\
     Contraseña del profesor\
     Contraseña para la inscripción de participantes\
     Borrar esta contraseña hace que todo el mundo pueda acceder a la clase.\
     Estaciones de trabajo seguras\
     Fecha de expiración\
     notificar al superviso\
     de la clase acerca de sus cambios.\
     Otras clases\
     Limit of participants\
    Are you sure you want to erase this class?\
    Your WIMS virtual class\
    WIMS class modification\
  into name_prop,name_of,name_serial,name_distrib,name_supervisor_p,name_supervisor_r,\
    name_warning,name_secure,name_expire,name_notify,name_change,name_other,name_limit,name_erase,\
    name_yourclass,name_yourclassmod
  !set name_creation=!nosubst is created on $class_creation and
  !set name_expires=expires on
  
  !set name_remark=<b>Nota</b>. Los cambios en estos campos sólo tienen sentido si es el \
     profesor responsable de la clase el que los solicita (y ha perdido el  control de la clase).\
     Usted probablemente debería
!exit
!endif

 !exit
!endif

!if $job=conf
  !set title=!nosubst Configuración de $cattit
  !distribute lines La configuración no ha cambiado porque no ha hecho modificaciones.\
     por defecto\
   into name_config,name_default
 
  !set name_updated=!nosubst   El fichero <tt>wims.conf</tt> hasido actualizado. Puede recuperar \
  la información de configuración antigua en <tt>$backdir/wims.conf.old</tt>.
  
  !set name_warning=<<b>Nota</b>. Los parámetros con un asterisco `*' en su título son importantes.\
Los que tienen un signo de peligro `!' pueden dañar la instalación si comete algún error.\
De todas formas recuerde que si borra el fichero <tt>log/wims.conf</tt>\
volverá a empezar con una configuración por defecto. También puede recuperar\
las configuraciones guardadas en el directorio log.
!!confcat=6
 !distribute lines Click here\
   for backup management and\
   here\
  for manual module management.\
 into name_click,name_backup,name_here,name_manual
!!ressources
  !set name_config_site=para configurar las normas de restricción de acceso del sitio.

!!graphics and software 
   !distribute line para comprobar los efectos de la nueva configuración.\
   Compruebe las aplicaciones de cálculo utilizadas por numerosos módulos de WIMS\
   si quiere comprobar las aplicaciones gráficas\
   orden\
   importancia\
   disponibilidad\
   No disponible\
   Ejemplo de módulos que dependen de él\
   to check the effect of the new setup\
   Este software va normalmente incluido en la distribución de WIMS. Quizás  haya fallado su compilación o usted la ha excluido deliberadamente.\
 into name_check,name_checksoftware,name_checkgraphics,name_command,name_importance,\
   name_availability,name_Unavailable,name_dependingonit,name_fail,name_refresh
   
   
!set name_warning_program=WIMS no ha podido encontrar los siguientes programas que usan algunos de sus\
 módulos. Estas aplicaciones o bien no están instaladas en el sistema\
 (en cuyo caso por favor instálelas) o bien están instaladas en un directorio\
 que no está incluido en el parámetro PATH (ruta) en

!set name_imagemagick=<b>ERROR</b>! No hemos encontrado una instancia funcional de ImageMagick en su sistema.\
 Sin este paquete la mayoría de las imágenes y animaciones de WIMS estarán mal.\
 En consecuencia le recomendamos vivamente que instale ImageMagick antes de continuar.
 
!set name_dynamic=Comprobar las imágenes dinámicas (puede plantearse hacerlo en distintos navegadores)

!set name_tex=Esta fórmula usa una inserción dinámica escrita en TeX. Debería verse correctamente, a no ser \
 que TeX no esté instalado correctamente en su sistema.\
 Puede cambiar la escala de cambio del tamaño de los tipos de letra TeX si aparecen\
 demasiado grandes o demasiado pequeños

!set name_drawing=Las siguientes dos imágenes han sido generadas por la utilidad interna\
  de dibujo dinámico. La primera es una imagen estática, la segunda es animada.\
  ¿Las ve correctamente? De lo contrario pruebe otros formatos gráficos y de animación.


!set name_gnuplot1=La siguiente representación gráfica usa gluplot.
!set name_gnuplot2= Las curvas deben tener colores 
diferentes. Si el resultado no es correcto pruebe con distintos formatos gráficos.
!set name_povray1=La siguiente imagen de traza de rayos es independiente de los formatos anteriores. \
Si no aparece, entonces
!set name_povray2=no está correctamente instalado.

 !exit
!endif


!if $job=crontab
  !set title=Mantenimiento diario automático
 !distribute  Se ha encontrado una tarea cron (crontab) instalada a mano. Debe o bien continuar admnistrando las tareas de cron de forma manual o bien borrar este fichero crontab antes de pasar a utilizar la herramienta en línea. ¡Nunca use esta herramienta si tiene un crontab personalizado!\
    Error extraño: no pudo recuperar mi directorio de trabajo. Compruebe su instalación: no funciona normalmente.\
   Trabajos de mantenimiento disponibles\
   Copia de seguridad de los datos a last\
   elija una hora en la que el servidor no esté ocupado\
   Contabilidad de la actividad (necesaria para las estadísticas del sitio)\
into name_manually,name_warning,name_strange,name_available,name_daily,name_notbusy,name_accounting


 !exit
!endif

!if $job=del1
  !set name_warning=¿Está seguro de que quiere borrar la cuenta de desarrollador
  
 !exit
!endif

!if $job=developer
  !set title=
  !set wims_name_adddevel=Añadir una nueva cuenta de desarrollador
  !set wims_name_develaccount=Lista de cuentas de desarrolladores
  !set name_dev=Desarrolladores de módulos registrados en este servidor
  !set name_visit=Visitar
  !set name_allowed=Desarrolladores a los que se les permite instalar módulos en el subdirectorio\
   local del sitio (escriba sus identificadores de usuario)

 !exit
!endif

!if $job=file
  !distribute lines Este es el fichero que va a descargar\
      ¿De verdad quiere borrar el fichero\
     modificado por última vez\
     bytes\
     es una image\
     es un fichero binario\
     es demasiado largo para poder mostrarlo o editarlo.\
     Este fichero pertenece a la distribución, no debería ser modificado.\
     Descargar el fichero\
     Contenido de\
   into name_file,name_erase,name_last,name_bytes,name_image,name_binary,name_toolong,\
   name_distrib,name_download,name_content
     
!exit
!endif

!if $job=fs
!distribute lines Directorio actual\
  Subdirectorios (pulse para ir)\
  Enlaces simbólicos\
  Añadirle un nuevo fichero\
  Ficheros\
  No hay ningún fichero normal en este directorio.\
into name_current,name_sub,name_symbolic,name_add,name_files,name_file

 !exit
!endif

!if $job=no_right
  !set name_warning=Lo sentimos pero no se ha identificado correctamente como administrador\
de este sitio. No está autorizado a acceder a este módulo.
!exit
!endif
!if $job=mkindex
  !set title=Reconstrucción del índice de recursos
  !distribute lines Se ha planificado la reconstrucción del índice de recursos. Recibirá un correo electrónico con el resultado de la reconstrucción.\
    La reconstrucción del índice de recursos ocupa muchos recursos del servidor,y debe ser evitada cuando el servidor se encuentre muy ocupado.\
    Resultado de la última reconstrucción del índice de recursos, el $lastdate\
    Pulse aquí\
    para reiniciar una reconstrucción del índice de recursos (no debería).\
    para iniciar la reconstrucción del índice de recursos.\
  into name_scheduled,name_rebuilding,name_result,name_click,name_restart,name_start
!exit
!endif

!if $job=mod2
  !set name_error1=!nosubst <b>Error</b>. El identificador de usuario (login) <tt>$devlogin</tt> \
 está ya siendo usado por otra cuenta. Por favor escoja otro identificador.
  !set name_error2=!nosubst <b>Error</b>. No ha introducido el campo <tt>$badfield</tt> correctamente.\ 
 Por favor corríjalo.
  
!exit
!endif

!if $job=modform
  !set name_modification= Modificación de las propiedades de una cuenta de desarrollador\
    (deje el campo de la contraseña en blanco si no desea modificar la contraseña).
 !set name_add= Para crear una nueva cuenta de desarrollador especifique por favor (todos \
     los campos son obligatorios):
!exit
!endif

!if $job iswordof modify erase
  !set title=
  !distribute lines Propiedades importantes de la clase virtual \
     de\
     número de serie\
     Esta clase viene con la distribución de WIMS.\
     Contraseña del profesor\
     Contraseña para la inscripción de participantes\
     Borrar esta contraseña hace que todo el mundo pueda acceder a la clase.\
     Estaciones de trabajo seguras\
     Fecha de expiración\
     notificar al superviso\
     de la clase acerca de sus cambios.\
     Otras clases\
     Limit of participants\
    Are you sure you want to erase this class?\
    Your WIMS virtual class\
    WIMS class modification\
  into name_prop,name_of,name_serial,name_distrib,name_supervisor_p,name_supervisor_r,\
    name_warning,name_secure,name_expire,name_notify,name_change,name_other,name_limit,name_erase,\
    name_yourclass,name_yourclassmod
  !set name_creation=!nosubst is created on $class_creation and
  !set name_expires=expires on
  
  !set name_remark=<b>Nota</b>. Los cambios en estos campos sólo tienen sentido si es el \
     profesor responsable de la clase el que los solicita (y ha perdido el  control de la clase).\
     Usted probablemente debería
!exit
!endif


!if $job=module
  !set name_scheduled=!nosubst  Se ha recibido la petición de ejecutar su orden $auto. El resultado \
   se le enviará por correo electrónico.<p> Por favor no repita la orden hasta que se haya completado su ejecución.
  !distribute lines  entre los anuncios de módulos\
    módulos de la zona\
    y categoría\
    modificados al menos hace\
    días\
  into name_mod,name_zone,name_cat,name_change,name_ago
  
  !distribute lines Error en la descarga del módulo \
      Error al instalar/actualizar\
      Instalación/actualización de\
       Deberá\
       éxito.\
       probarlo\
       reconstruir el índice de módulos\
       Instalar\
       Actualizar\
       contra\
       Cambios\
       Nueva versión de\
       Módulo nuevo\
        Tiene que\
      después de una actualización de módulos.\
      Pulse aquí\
      para configurar la actualización diaria automática de módulos.\
      You can also update\
    into name_error1,name_error2,name_install,name_successful,name_need,name_test,name_rebuild,name_Install,\
      name_Update,name_versus,name_Changes,name_version,name_newmodule,name_youneed,name_after,\
      name_click,name_automatic,name_rss

!!check
!distribute lines No se ha hallado ningún anuncio de módulo que se corresponda con su búsqueda.\
    Pulse en la dirección de un módulo para comprobar/instalar/actualizarlo.\
    Se han hallado versiones nuevas\
    Se han hallado versiones nuevas\
    actualizar todo\
    instalar todos\
    actualizado<br>por\
    Nueva<br>versión\
    Hallados módulos nuevos\
    Versión del<br>servidor
    hecho público<br>por\
  into name_check1,name_click,name_foundv,name_foundm,name_all_u,name_all_i,name_updated,name_newv,name_newm,name_server,name_published

!exit
!endif

!if $job=restore

   !set name_warning1=Archivo comprimido en mal estado: no se ha encontrado ningún contenido en él.
   !set name_warning2=Se han recuperado/instalado con éxito datos en los siguientes directorios
 !exit
!endif
 
!if $job=sess
  !set title=Sesión de usuario
  !distribute lines Contenido de la sesión\
    Contenido del fichero de variables de la sesión\
    Contenido del fichero\
    Lista de sesiones activas\
  into name_content_s,name_content_v,name_content_f,name_listsessions
!exit
!endif

!if $job=upload
 !set name_warning=Para subir recursos al servidor, inserte el cdrom o pendrive usb que contiene\
el recurso y busque el fichero "wims-resource.tgz" en el siguiente campo de entrada
 !set name_need=Necesitará una conexión rápida si el fichero que va a subir es grande.
!exit
!endif

!if $job=wrongpass
  !set name_warning=Ha introducido una contraseña errónea.
  !set name_try=Vuelva a intentarlo
!exit
!endif

!if $job=rss
   !set title= Rebuild RSS feed
   !set name_start=to start RSS Feed rebuilding.
 !exit
!endif