!if $special_parm!=$empty
 !read help/$special_parm.phtml
 !goto end
!endif

!if $login=$empty
 Esta herramienta permite la creación y el desarrollo en línea de módulos de actividades WIMS ordinarios.
 <p>
Tal módulo puede ser un ejercicio de plena potencia (comparado a los ejercicios OEF que son más fáciles de escribir pero tienen capacidades limitadas&nbsp;; ver
 !href module=adm/createxo Createxo
 ) or a sophisticated computational tool. o una herramienta de cálculo sofisticada. Deben escribirle en la lengua interpretada de WIMS, tal como se explica en
 !href target=wims_help module=help/wimsdoc WIMS technical documentation
.
 <p>
 Si se interesan, se puede pedir a
 !mailurl $wims_site_manager the manager of this WIMS site\
WIMS Modtool id
 una identificación de acceso/contraseña de desarrollador que les permitirá utilizar esta herramienta.
 !exit
!endif

!if $mod=$empty
 Para trabajar sobre un módulo, deben en primer lugar crearlo. Para crear un
 nuevo módulo, hay que presionar los vínculos convenientes y luego llenar los formularios
 a tal efecto.
 <p>
!endif

Quiere consultar
 !href target=wims_help module=help/wimsdoc WIMS technical documentation
 con el fin de conocer la estructura de un módulo WIMS así como el sintaxis y el formato de su contenido.

Encontrarán aquí la
!href target=wims_help module=adm/createxo $wims_name_docoef
<p>
Indicaciones especiales&nbsp;:
<ol>
<li><p>Para eliminar errores de un fichero, pueden colocar una línea
<pre>
$!debug ...
</pre>
en este fichero, donde… puede ser cualquier cadena de texto. Cuando
prueban su módulo, la ejecución va a par a esta línea y el contenido de… se les mostrará. Si… incluye variables,
se substituyen estos últimos según las normas
habituales de sustitución de variables de WIMS.

</ol>

:end
