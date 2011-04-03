!if $special_parm!=$empty
 !changeto help/$module_language/$special_parm.phtml
!endif

!if $wims_user!=supervisor
 Lo sentimos, no hay ayuda para los participantes.
 !tail
 !exit
!endif

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

