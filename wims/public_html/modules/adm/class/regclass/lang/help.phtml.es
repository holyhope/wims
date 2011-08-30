 !goto $wims_read_parm

:1
Una <font color=blue>agrupación de clases</font> permite a los
 profesores intercambiar o compartir materiales pedagógicos, y a los
 alumnos pasar de una clase a otra sin tener que volver a introducir la
 contraseña. Puede crear aquí su <font color=blue>página de entrada</font>.
 <p>
 Una <font color=blue>estructura de centro educativo</font> es un conjunto
 multinivel de clases virtuales, capaz de dar respuesta a las necesidades
 de un centro educativo al completo: bases de datos de alumnos y de
 profesores, diferentes niveles de enseñanza, programas, asignaturas y
 clases de alumnos, responsabilidades de los profesores, etc.
 Puede crear aquí su página inicial, llamada también
 <font color=blue>portal</font>.
 !exit
:2

  La creación
 !if $Cltype<2
   de una <font color="blue">clase</font>
   es una operación reservada a los <font color="blue">profesores</font>.
 !else
   !if $Cltype=2
    de una <font color="blue">página de entrada a una $name_classe</font>
   !else
    de una <font color="blue">$name_classe</font>
   !endif
   es una operación reservada a un <font color="blue">administrador</font>
  (que puede ser un profesor).
 !endif
 Necesitará una dirección de correo activa para poder hacerlo.
 Después de crear su  $name_classe,
 ha de asumir la responsabilidad de su mantenimiento. <p>
 Para crear su $name_classe, por favor, rellene la siguiente información.
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
  de nivel <b><font color=green>$name_level</font></b>,
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
 <p>
 Si encuentra un error en la información anterior, por favor
 !href module=$module&cmd=reply&step=0 corríjala.
 <p>En caso contrario, para poder verificar la exactitud de sus contraseñas,
  escríbalas de nuevo.
 !exit
:step2

 ¡Bienvenido/a, $supervisor!<p>
 Ahora necesita una clave para terminar la operación de creación de
 su $name_classe bajo WIMS en el sitio $httpd_HTTP_HOST. <p>
 Esta clave acaba de ser enviada a su dirección de correo
 <tt class="wims_address">$email</tt>. Por favor, compruebe su buzón de correo electrónico (espere
 un poco si no llega), y lea el mensaje que se le ha enviado. Copie la clave del
 mensaje a continuación.

!exit
:step3

¡Bienvenido/a, $supervisor!<p>
 Su $name_classe $classname ya ha sido creada. ¡Felicidades, y que se divierta!<p>
 El número de participantes está limitado a $ilimit (incluido usted).

!exit
