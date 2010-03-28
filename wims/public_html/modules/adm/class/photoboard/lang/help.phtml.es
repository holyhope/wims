!if $special_parm!=$empty
 !goto $special_parm
!endif

Si definieron variables técnicas asociadas a los participantes
(por ejemplo su grupo), lo que puede hacerse
<ul>< li>
con ayuda de la conexión hoja de cálculo,
<li>
directamente en las propiedades de la cuenta de los estudiantes
<li> por medio de un cuestionario no anónimo
</ul>
(véase las documentaciones correspondientes), pueden filtrar
a los estudiantes relativamente a estas variables.Escriba en una misma línea,
y separadas por espacios, las condiciones que deben cumplirse al mismo tiempo.
El trombinoscopio se formará por las fotografías de los participantes
que satisfarán al menos una de las líneas de condiciones.

<p> por ejemplo ,
<pre>
grupo=1 lengua=2
grupo=3
</pre>
seleccionará los participantes que pertenecen al grupo 1 y cuya lengua es 2
 o quiénes que pertenecen al grupo 3.

Pueden también poner una lista de logins (identificador).


