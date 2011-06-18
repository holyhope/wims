!goto $wims_read_parm

:dellevel

<span class="wims_warning">AVISO</span>. ¡Esta operación es irreversible!
¡Y <span class="wims_warning">TODO</span>
lo que hay en este nivel será borrado <span class="wims_warning">DEFINITIVAMENTE</span>:
clases, programas, cursos, cuentas de alumnos, actividades, notas!
<p>
¿Está seguro de querer borrar este nivel?


!exit

:delclass

<span class="wims_warning">AVISO</span>. ¡Esta operación es irreversible!
¡Y <span class="wims_warning">TODO</span>
lo que hay en esta clase será borrado <span class="wims_warning">DEFINITIVAMENTE</span>: 
cursos, cuentas de alumnos, actividades, notas!
<p>
¿Está seguro de querer borrar esta clase?

!exit

:delprog
<span class="wims_warning">AVISO</span>. ¡Esta operación es irreversible!
¡Y <span class="wims_warning">TODO</span>
lo que hay en este programa será borrado <span class="wims_warning">DEFINITIVAMENTE</span>:
cursos, actividades, notas!
<p>
¿Está seguro de que quiere borrar este programa? 

!exit

:delcourse
<span class="wims_warning">AVISO</span>. ¡Esta operación es irreversible!
¡Y <span class="wims_warning">TODO</span>
lo que hay en este curso será borrado <span class="wims_warning">DEFINITIVAMENTE</span>:
cuentas de alumnos, actividades, notas!
<p>
¿Está seguro de querer borrar este curso?

!exit

:delteacher
<<span class="wims_warning">AVISO</span>. ¡Esta operación es irreversible!
<p>
¿Está usted seguro de que queire borrar la cuenta de profesor <tt>$del</tt>
($user_firstname $user_lastname)?

!exit

:deltest
<span class="wims_warning">AVISO</span>. ¡Esta operación es irreversible!
¡Y <span class="wims_warning">TODO</span>
lo que hay en esta zona de pruebas será borrado <span class="wims_warning">DEFINITIVAMENTE</span>!
<p>
¿Está seguro de que quiere borrar la zona de pruebas?

!exit

:progshare
Partage de ressources d'un autre programme

Votre programme va partager l'ensemble de ressources pédagogiques
(exercices, feuilles, examens, documents, questionnaires) avec le programme
<em>$other_description</em> du niveau <em>$other_level</em>. Cela signifie
que tout changement sur les ressources d'un des deux programmes se répercute
automatiquement dans l'autre programme.

<p><span class="wims_warning">$wims_name_warning</span>. Cette opération expérimentale va effacer les ressources
existantes dans votre programme et est <span class="wims_warning">IRREVERSIBLE</span>&nbsp;!
Vous ne pourrez pas arrêter le partage et les programmes partageant les
ressources ne doivent pas être effacés&nbsp;!

<p>
Êtes-vous sûr de vouloir continuer&nbsp;?

!exit