!goto $wims_read_parm

:pass

<h2 class="wimscenter">Contraseña de inscripción</h2>
<p>
Hay dos tipos de contraseñas de inscripción:
</p><p>
La contraseña de inscripción en la plataforma permite crear cuentas
de profesores. Esta contraseña no debe dársele NUNCA a los alumnos, puesto
que todos los que se inscriben directamente en la plataforma son reconocidos
como profesores, con los derechos de los profesores.
</p><p>
La contraseña de inscripción de una clase o de un curso permite crear
cuentas de alumnos. Un alumno debe inscribirse en una clase dada en tanto 
que alumno, pero todas las inscripciones quedan registradas para todo el Centro.
</p><p>
Sólo las clases y ciertos cursos tienen necesidad de contraseña de
inscripción: en las otras zonas (nivel, programa) no está permitida
la inscripción de los alumnos.
</p><p>
Cuando quiera modificar las propiedades y no quiera cambiar la contraseña
no tiene más que dejar el campo en blanco.
</p>

!exit
:passs

<h2 class="wimscenter">Contraseña de profesor</h2>
<p>
Estas contraseñas permiten a los profesores acceder a la administración
de los niveles, clases, programas o cursos. Por defecto se instala la
contraseña de profesor de la zona superior.
</p><p>
Cuando modifique las propiedades y no quiera cambia la contraseña no tiene
más que dejar el campo en blanco.


!exit

:progopt


<h2 class="wimscenter">Opciones de un programa</h2>

Si un programa es <em>obligatorio</em>, todos los alumnos de una clase que
tengan un curso que dependa del programa están automáticamente
inscritos en dicho curso. Dicho de otra forma, todos los cursos del programa
son obligatorios para las clases correspondientes.
</p><p>
Por contra, para un programa <em>optativo</em>, los alumnos deben
inscribirse específicamente en sus cursos. Esto es útil cuando el programa
es opcional.
</p><p>
Si se encuentra en "sí" la instalación automática de los cursos del
programa, se creará un curso por cada clase del nivel, en el momento de
la creación del programa. Además, se creará automáticamente un curso
del programa cuando se cree una nueva clase en ese nivel.
</p><p>
Si la instalación automática de los cursos está puesta a "no", los
profesores de las clases deben crear manualmente los cursos correspondientes
al programa.
</p>

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


<h2 class="wimscenter">Profesor responsable de una zona</h2>
<p>
Cada zona (nivel, clase, programa, curso) de una estructura de centro educativo
debe tener un enseñante responsable. Los derechos de acceso a las páginas
de administración de la zona se rigen normalmente desde una cuenta de profesor.
</p><p>
Por defecto, el profesor responsable de la zona será el de la zona superior.
</p><p>
Si embargo cualquier otro enseñante del centro puede tener también acceso 
a la administración de la zona, si conoce la contraseña del profesor-responsable
de la misma. La única diferencia es que el nombre y la dirección de correo electrónico
que aparecerán en las páginas de los alumnos de la zona serán los del profesor
responsable "oficial".
</p>

!exit

:addcsvclass
<h2>Ajout de classes par importation d'un fichier.</h2>

<p>
Pour envoyer des données de votre tableur à la classe, sauvez les données
dans un fichier au format texte (txt, csv, ou tsv), puis envoyez le fichier
au serveur.
</p>
$table_header
<caption>Champs de données valables</caption>
$table_hdtr<th scope="col">Nom</th><th scope="col">Signification</th>
$table_tr<td class="tt wims_code_variable">cname</td><td>nom de la classe</td></tr>
$table_tr<td class="tt wims_code_variable">login</td><td>identifiant de l'enseignant controlant la classe (qui doit exister dans la classe avec les autorisations d'enseignant). Ecrire supervisor pour que la classe soit gérée par l'administrateur du portail.</td></tr>
$table_tr<td class="tt wims_code_variable">regpass</td><td>mot de passe d'inscription de la classe.</td></tr>
$table_tr<td class="tt wims_code_variable">secure</td><td>accès sécurisé de la classe (IP ou all).</td></tr>
$table_tr<td class="tt wims_code_variable">limit</td><td>nombre maximum d'élèves.</td></tr>

les colonnes regpass,secure,limit ne sont pas obligatoires. Elles seront fixées avec des valeurs par défauts si elles ne sont pas présentes.
$table_end
!exit
