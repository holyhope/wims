!goto $wims_read_parm

:dellevel

<div class="wims_alert warning"><span class="wims_warning">AVISO</span>. �Esta operaci�n es irreversible!
�Y <span class="wims_warning">TODO</span>
lo que hay en este nivel ser� borrado <span class="wims_warning">DEFINITIVAMENTE</span>:
clases, programas, cursos, cuentas de alumnos, actividades, notas!
</div><p>
�Est� seguro de querer borrar este nivel?
</p>

!exit

:delclass

<div class="wims_alert warning"><span class="wims_warning">AVISO</span>. �Esta operaci�n es irreversible!
�Y <span class="wims_warning">TODO</span>
lo que hay en esta clase ser� borrado <span class="wims_warning">DEFINITIVAMENTE</span>:
cursos, cuentas de alumnos, actividades, notas!
</div><p>
�Est� seguro de querer borrar esta clase?
</p>
!exit

:delprog
<div class="wims_alert warning"><span class="wims_warning">AVISO</span>. �Esta operaci�n es irreversible!
�Y <span class="wims_warning">TODO</span>
lo que hay en este programa ser� borrado <span class="wims_warning">DEFINITIVAMENTE</span>:
cursos, actividades, notas!
</div><p>
�Est� seguro de que quiere borrar este programa?
</p>
!exit

:delcourse
<div class="wims_alert warning"><span class="wims_warning">AVISO</span>. �Esta operaci�n es irreversible!
�Y <span class="wims_warning">TODO</span>
lo que hay en este curso ser� borrado <span class="wims_warning">DEFINITIVAMENTE</span>:
cuentas de alumnos, actividades, notas!
</div><p>
�Est� seguro de querer borrar este curso?
</p>
!exit

:delteacher
<div class="wims_alert warning">
<span class="wims_warning">AVISO</span>. �Esta operaci�n es irreversible!
</div><p>
�Est� usted seguro de que queire borrar la cuenta de profesor <span class="tt">$del</span>
($user_firstname $user_lastname)?
</p>
!exit

:deltest
<div class="wims_alert warning">
<span class="wims_warning">AVISO</span>. �Esta operaci�n es irreversible!
�Y <span class="wims_warning">TODO</span>
lo que hay en esta zona de pruebas ser� borrado <span class="wims_warning">DEFINITIVAMENTE</span>!
<div class="wims_alert warning"><p>
�Est� seguro de que quiere borrar la zona de pruebas?
</p>
!exit

:progshare
Partage de ressources d'un autre programme

Votre programme va partager l'ensemble de ressources p�dagogiques
(exercices, feuilles, examens, documents, questionnaires) avec le programme
<em>$other_description</em> du niveau <em>$other_level</em>. Cela signifie
que tout changement sur les ressources d'un des deux programmes se r�percute
automatiquement dans l'autre programme.

<div class="wims_alert warning"><span class="wims_warning">$wims_name_warning</span>. Cette op�ration exp�rimentale va effacer les ressources
existantes dans votre programme et est <span class="wims_warning">IRREVERSIBLE</span>&nbsp;!
Vous ne pourrez pas arr�ter le partage et les programmes partageant les
ressources ne doivent pas �tre effac�s&nbsp;!
</div><p>
�tes-vous s�r de vouloir continuer&nbsp;?
</p>
!exit
