!set wims_module_log=error: $error

<span class="wims_warning">$wims_name_Error</span>.

!if not_supervisor=$error
 Lo sentimos pero la operación de preparación /modificación de una hoja
 de trabajo está reservada a los profesores registrados de la clase.
 !exit
!endif

!if not_superclass=$error
 Operación prohibida porque usted participa en una agrupación de clases.
 Únicamente el administrador de la agrupación puede realizarla.
 !exit
!endif

!if no_login iswordof $error
 Los datos que ha enviado deben tener obligatoriamente una columna
 correspondiente a los identificadores de usuario de los participantes.
 !exit
!endif

!if bad_filename iswordof $error
 Su fichero no parece ser un fichero de hoja de cálculo en formato de texto.
 :csvformat
 Por favor guarde los datos en formato de texto (con los valores separados
 or comas o tabuladores y las extensiones .csv, .tsv o .txt), antes de
 enviarlo a la clase.
 !exit
!endif

!if binary_upload iswordof $error
 ¡Sus datos de hoja de cálculo están en formato binario! Este formato no
 está reconocido, lo sentimos.
 <p>
 !goto csvformat
!endif

!if no_manual iswordof $error
 Por favor primero
 !href module=adm/class/grades cree una columna de notas manuales
 antes de enviar datos en ella.
 !exit
!endif

!if not_secure iswordof $error
 Sólo se aceptan el envío y recepción de datos procentes de hojas de cálculo en
 conexiones desde estaciones de trabajo seguras. Por favor compruebe la
 configuración de su clase.
 !exit
!endif

!if bad_user=$error
 Error de llamada: el participante <span class="tt wims_login">$checkuser</span> no existe.
 !exit
!endif

!if $error iswordof login_missing login_empty
!! login_missing: not find in the ldap for example : should be more precise ??
   Some login have not been found.
 !exit
!endif

!if bad_exo=$error
 El artículo que se quiere verificar no existe.
 !exit
!endif

!if bad_op=$error
 Operación incorrecta. Cierre la ventana.
 !exit
!endif
!if too_big=$error
  The number of columns of the spreadsheet is too big (greater than $TOO_BIG).
  If you need the details of the exercices, you can do it sheet by sheet or
  exam by exam. The file to download does not give you all the informations you asked.
 !exit
!endif
!msg $error

