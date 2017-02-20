 !goto $wims_read_parm

:1
Una <span class="wims_emph">agrupación de clases</span> permite a los
 profesores intercambiar o compartir materiales pedagógicos, y a los
 alumnos pasar de una clase a otra sin tener que volver a introducir la
 contraseña. Puede crear aquí su <span class="wims_emph">página de entrada</span>.
 <p>
 Una <span class="wims_emph">estructura de centro educativo</span> es un conjunto
 multinivel de clases virtuales, capaz de dar respuesta a las necesidades
 de un centro educativo al completo: bases de datos de alumnos y de
 profesores, diferentes niveles de enseñanza, programas, asignaturas y
 clases de alumnos, responsabilidades de los profesores, etc.
 Puede crear aquí su página inicial, llamada también
 <span class="wims_emph">portal</span>.
 </p>
 !exit
:2
<p>
  La creación
 !if $Cltype<2
   de una <span class="wims_emph">clase</span>
   es una operación reservada a los <span class="wims_emph">profesores</span>.
 !else
   !if $Cltype=2
    de una <span class="wims_emph">página de entrada a una $name_classe</span>
   !else
    de una <span class="wims_emph">$name_classe</span>
   !endif
   es una operación reservada a un <span class="wims_emph">administrador</span>
  (que puede ser un profesor).
 !endif
 Necesitará una dirección de correo activa para poder hacerlo.
 Después de crear su  $name_classe,
 ha de asumir la responsabilidad de su mantenimiento. </p><p>
 Para crear su $name_classe, por favor, rellene la siguiente información.
 </p>
!exit

:step1
 ¡Bienvenido/a, $supervisor!<p>
 Está creando
 !if $Cltype<2
  la
 !else
  el
 !endif
 $name_classe $classname en el sitio WIMS $httpd_HTTP_HOST,
 !if $Cltype=1
 !let tmp=!positionof item $ilevel in $wims_listlevel
  de nivel <span class="wims_emph">$(name_wims_listlevel[$tmp])</span>,
 !endif
 que expirará el $exp_day/$exp_month/$exp_year. El número
 máximo de participantes es de $ilimit;
 la inscripción está
 !if $pword!=$empty
  protegida por la contraseña $name_classesss.
 !else
  abierta a todo el mundo en internet (¿Está usted seguro? Sepa que
  el administrador del sitio puede rechazarlas y eliminarlas).
 !endif
 </p><p>
 Si encuentra un error en la información anterior, por favor
 !href module=$module&cmd=reply&step=0 corríjala.
 </p><p>En caso contrario, para poder verificar la exactitud de sus contraseñas,
  escríbalas de nuevo.
</p>
 !exit
:step2

 ¡Bienvenido/a, $supervisor!<p>
 Ahora necesita una clave para terminar la operación de creación de
 su $name_classe bajo WIMS en el sitio $httpd_HTTP_HOST. </p><p>
 Esta clave acaba de ser enviada a su dirección de correo
 <span class="tt wims_address">$email</span>. Por favor, compruebe su buzón de correo electrónico (espere
 un poco si no llega), y lea el mensaje que se le ha enviado. Copie la clave del
 mensaje a continuación.
</p>
!exit
:step3

¡Bienvenido/a, $supervisor!<p>
 Su $name_classe $classname ya ha sido creada. ¡Felicidades, y que se divierta!</p><p>
 El número de participantes está limitado a $ilimit (incluido usted).
</p>
!exit
