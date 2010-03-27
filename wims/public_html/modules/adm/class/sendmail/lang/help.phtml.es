!if $special_parm!=$empty
 !goto $special_parm
!endif

:filter
Si definieron variables técnicas asociadas a los participantes
(por ejemplo su grupo), lo que puede hacerse
<ul>< li>
con ayuda de la conexión hoja de cálculo,
<li>
directamente en las propiedades de la cuenta de los estudiantes
<li> por medio de un cuestionario no anónimo
</ul>
(véase las documentaciones correspondientes), pueden filtrar
a los estudiantes relativamente a estas variables. Las condiciones en una misma línea
deben ser todas llenadas y en el caso de varias líneas, las condiciones al menos de una línea
deben cumplirse.
<p> por ejemplo ,
<pre>
grupo=1
grupo=3
</pre>
seleccionará los estudiantes que pertenecen al grupo 1 o al grupo 3.


:general
Pueden utilizar el método de selección y entrar al mismo tiempo nombres de logins.
El correo electrónico se envía al conjunto de los nombres seleccionados.
Si al mismo tiempo seleccionaron al filtro, el filtro se aplica a la lista
de los nombres seleccionados. Si no entran ninguna clave de acceso,
la lista de los logins utilizada es la lista de los participantes a la clase.

