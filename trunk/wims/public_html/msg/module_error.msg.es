
	    Fichero de mensajes de error de WIMS, versión española.

Environment variable substitutions are valid (variable names start by `$').

A line starting with ':' at the FIRST column is a tag line. Text following
this line will be printed if the tag equals error type; tag line with empty
tag is valid for all error types.

Nothing before the first tag line will be printed; so put comments simply
at the beginning of the file (or after a fictive tag).


:antidated_version
 Este módulo requiere al menos WIMS-$module_wims_version, pero el 
 servidor sólo está en la versión $wims_version.
 <p>
 Módulo mal instalado.

:append_syntax
  Error de sintaxis en `append'.

:bad_allow
  El campo ``allow'' en la definición de variable no es válido.

:bad_cmd
  El comando ``$wims_error_data'' no es válido.  

:bad_index
  El valor del índice no es válido.

:bad_var_def
  Archivo var.def no válido.

:cannot_create_session_directory
  No puedo crear el directorio de sesión.

:cannot_create_session_number
  No puedo crear el número de sesión.

:comp_syntax
  Error de sintaxis en la función compare(): $wims_error_data.

:debug
  Salida de depuración:
$debug

:defn_too_long
  Cadena de definición demasiado larga.

:executable
 WIMS no puede procesar el fichero $executable, puesto que se trata de un fichero
 ejecutable.

:file_access_denied
 El acceso al fichero ``$wims_error_data'' ha sido rechazado por razones de
 seguridad.

:file_name_too_long
 El nombre del fichero es demasiado largo:
 ``$wims_error_data''

:file_too_long
  La longitud del archivo ``$wims_error_data'' excede el límite.
  
:for_syntax
  Error de sintaxis en el `for'.

:getscore_syntax
  Error de sintaxis en `getscore'.

:illegal_cmd
  La orden ``$wims_error_data'' es ilegal:
  No debería intentar acceder a los directorios padre en el nombre de la orden.
  
:illegal_fname
  El nombre del archivo ``$wims_error_data'' es ilegal:
  No se permite acceder a los archivos a través de sus directorios padre.

:illegal_name
  El nombre de la variable ``$wims_bad_name'' es incorrecto.

:illegal_plot_cmd
  La cadena de parámetros para gnuplot puede que contenga caracteres ilegales.
  No se permite el uso de tuberías en esta cadena (un apóstrofo 
  seguido de `<').
  
:label_not_found
  Imposible encontrar la etiqueta ``$wims_error_data''

:mathsubst_syntax
  Error de sintaxis en  ``mathsubst''.

:multiple_declaration
  Se ha declarado la variable ``$wims_bad_name'' en varias ocasiones.

:name_is_reserved
  El nombre ``$wims_reserved_name'' está reservado para uso interno de 
  este servidor. No deberá usarlo en su módulo. Por favor, elija otro
  nombre para su variable.

:name_too_long
  Nombre de variable demasiado largo.

:next_without_for
  `next' sin `for'.
  (¿Hay un goto que salte dentro de un bucle `for'?)

:no_double_quote
  No se permiten dobles " comillas en los parámetros de una orden, debido
  a razones de seguridad. Lo sentimos.
  
:no_of
  Error de sintaxis. La sintaxis es: $wims_error_data ??? of ???

:not_trusted
  El módulo $module no tiene privilegios para ejecutar guiones privados 
  o comandos administrativos.

:output_too_long
  La longitud de la página html de salida ha excedido el límite.
  Si no lo planeó así (en este caso, divida la página), es probable
  que se deba a un bucle infinito.
  
:parm_too_long
  La cadena de parámetros ha excedido la longitud máxima.
  
:replace_syntax
  Error de sintaxis en `replace'.

:subst_exceeded
  Demasiadas sustituciones en una cadena. (¿Hay un bucle infinito de 
  sustituciones?)

:syntax_error
  Error de sintaxis en la orden.

:text_bad_table
  La tabla para inserción de textos está corrupta.

:timeup
 Se ha interrumpido el procesamiento de su petición porque requiere
 demasiado tiempo.

:too_few_columns
  A la definición de la variable le faltan campos.

:too_many_fors
  El número de bucles `for' ha excedido el límite.

:too_many_gotos
  Demasiados goto's (o de bucles `for'). Está limitado el 
  número de goto's.
  
:too_many_ins
  El número de inserciones dinámicas (instex, insplot) ha excedido el
  límite.

:too_many_nested_read
  El número de ejecuciones de ficheros anidadas ha superado el límite. Compruebe si el
  fichero no se está leyendo a sí mismo.

:too_many_variables
  El número de variables definidas en var.def ha excedido el límite.

:tr_syntax
  Error de sintaxis para `translate'.

:unmatched_parentheses
  Error de sintaxis. Los paréntesis no corresponden.

:workfile_too_long
  El módulo contiene un archivo que excede la longitud máxima permitida.

:zero_step
  No se puede ejecutar un bucle `for' con paso (`step') cero.
 
:

</p>
Si ve este mensaje, generalmente se deberá a un error en el módulo 
`$module'.

Por favor contacte con el desarrollador del módulo para informarle del error.
