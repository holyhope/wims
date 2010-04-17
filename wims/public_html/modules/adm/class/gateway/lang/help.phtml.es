!goto $wims_read_parm

:pass

<center><h2>Contraseña de inscripción</h2></center>

Hay dos tipos de contraseñas de inscripción:
<p>
La contraseña de inscripción en la plataforma permite crear cuentas
de profesores. Esta contraseña no debe dársele NUNCA a los alumnos, puesto
que todos los que se inscriben directamente en la plataforma son reconocidos
como profesores, con los derechos de los profesores.
<p>
La contraseña de inscripción de una clase o de un curso permite crear
cuentas de alumnos. Un alumno debe inscribirse en una clase dada en tanto 
que alumno, pero todas las inscripciones quedan registradas para todo el Centro.
<p>
Sólo las clases y ciertos cursos tienen necesidad de contraseña de
inscripción: en las otras zonas (nivel, programa) no está permitida
la inscripción de los alumnos.
<p>
Cuando quiera modificar las propiedades y no quiera cambiar la contraseña
no tiene más que dejar el campo en blanco.


!exit
:passs

<center><h2>Contraseña de profesor</h2></center>

Estas contraseñas permiten a los profesores acceder a la administración
de los niveles, clases, programas o cursos. Por defecto se instala la
contraseña de profesor de la zona superior.
<p>
Cuando modifique las propiedades y no quiera cambia la contraseña no tiene
más que dejar el campo en blanco.


!exit

:progopt


<center><h2>Opciones de un programa</h2></center>

Si un programa es <em>obligatorio</em>, todos los alumnos de una clase que
tengan un curso que dependa del programa están automáticamente
inscritos en dicho curso. Dicho de otra forma, todos los cursos del programa
son obligatorios para las clases correspondientes.
<p>
Por contra, para un programa <em>optativo</em>, los alumnos deben
inscribirse específicamente en sus cursos. Esto es útil cuando el programa
es opcional.
<p>
Si se encuentra en "sí" la instalación automática de los cursos del
programa, se creará un curso por cada clase del nivel, en el momento de
la creación del programa. Además, se creará automáticamente un curso
del programa cuando se cree una nueva clase en ese nivel.
<p>
Si la instalación automática de los cursos está puesta a "no", los
profesores de las clases deben crear manualmente los cursos correspondientes
al programa.


!exit

:sechost
!reset wims_prefix
!set special_parm2=secure
!read wimshome/public_html/modules/adm/class/config/lang/help.$moduclass_lang/config.phtml

!exit

:structure

!read help/$moduclass_lang/structure.phtml

!exit

:supervisor


<center><h2>Profesor responsable de una zona</h2></center>

Cada zona (nivel, clase, programa, curso) de una estructura de centro educativo
debe tener un enseñante responsable. Los derechos de acceso a las páginas
de administración de la zona se rigen normalmente desde una cuenta de profesor.
<p>
Por defecto, el profesor responsable de la zona será el de la zona superior.
<p>
Si embargo cualquier otro enseñante del centro puede tener también acceso 
a la administración de la zona, si conoce la contraseña del profesor-responsable
de la misma. La única diferencia es que el nombre y la dirección de correo electrónico
que aparecerán en las páginas de los alumnos de la zona serán los del profesor
responsable "oficial".


!exit
