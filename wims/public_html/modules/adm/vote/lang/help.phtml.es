!if $special_parm!=$empty
 !changeto help/$module_language/$special_parm.phtml
!endif

!if $wims_user!=supervisor
 Lo sentimos, no hay ayuda para los participantes.
 !tail
 !exit
!endif

!if $wims_read_parm=$empty
El contenido de una encuesta puede ser un texto html, reforzado con los mismos
elementos que los mensajes de los foros. Además se pueden utilizar las siguientes
órdenes: <dl>
<p><dt><tt class="wims_code_variable">\menu{Sí,No}</tt>
	<dd>Elección mediante un menú.

<p><dt><tt class="wims_code_variable">\list{A,B,C,D}</tt>
	<dd>Elección mediante botones en una lista vertical.

<p><dt><tt class="wims_code_variable">\radio{muy mal, bastante mal, bastante bien, muy bien}</tt>
	<dd>Una elección con botones horizontales. 

<p><dt><tt class="wims_code_variable">\uservar{vname,val0,val1,...}</tt>
	<d>Grabar la elección inmediatamente precedente en una variable
	individual para el participante, de nombre <tt>vname</tt>. Esta
	variable tendrá el valor <tt>val0</tt> por defecto, <tt>val1</tt> si
	el participante había escogido la primera opción, etc. <p>
	Esta variable puede posteriormente utilizarse para definir accesos
	individualizados a las hojas de trabajo o a los exámenes, poniendo
	la palabra <tt>\vname</tt> entre las restricciones de la hoja o examen.

</dl>

Una encuesta puede contener hasta 64 campos de elección.
!tail
!exit
!endif

!if generalinfo iswordof $wims_read_parm
<ul>
 <li><b>$wims_name_title</b> : le titre du questionnaire.</li>
 <li><b>$wims_name_Type</b> : 
  <ul>
   <li><b>$name_anonymous</b> : questionnaire anonyme, personne ne connaît les réponses apportées 
   (il est impossible de connaître sa propre réponse une fois qu'on a voté)</li>
   <li><b>$name_trace</b> : questionnaire anonyme répondant aux mêmes critères que précédemment. 
   Cependant il est possible de connaître les réponses effectuées par un participant 
   sans pour autant pouvoir identifier ce participant.</li>
   <li><b>$name_nominative</b> : les réponses de chaque participants peuvent être 
   consultées (il n'est pas possible d'utiliser des zones de réponses 
   libres dans ce type de questionnaire).</li>
  </ul>
 </li>
 <li><b>$wims_name_Status</b> : l'un des statuts ci-dessous :
     <ul>
      <li><b>$name_0</b> : le questionnaire est modifiable, les participants ne peuvent pas le voir.</li>
      <li><b>$name_1</b> : le questionnaire n'est plus modifiable, les participants 
      peuvent répondre au questionnaire.</li>
      <li><b>$name_2</b> : le questionnaire n'est plus modifiable, les participants 
      ne peuvent plus répondre au questionnaire.</li>
      <li><b>$name_3</b> : le questionnaire n'est plus modifiable, les participants 
      ne voient plus le questionnaire.</li>
     </ul>
 </li>
 <li><b>$name_result</b> : si les résultats sont $(name_publish)s, les participants peuvent les consulter 
 (une fois qu'ils ont voté). Dans le cas contraire, seul l'enseignant de la classe accède aux résultats.</li>
 <li><b>$name_whovote</b> : si la liste des votants est $name_publish2, alors l'enseignant
 et les participants peuvent la consulter (à condition qu'il y ait un nombre suffisant de votants).
 Dans le cas contraire, personne ne peut savoir qui a voté !</li>
</ul> 
!tail
!exit
!endif
!tail

