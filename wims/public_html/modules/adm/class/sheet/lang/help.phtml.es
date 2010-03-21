!goto $wims_read_parm
!exit

:dependancies

<center><b>$(name_shtab[6])</b></center>
  quiere decir que
  un participante debe primero lograr puntos en otros ejercicios de la hoja,
  antes de poder trabajar en este. Por ejemplo,
  <font color=blue><tt>1:50,2:30,3+4+5:60</tt></font>
  significa que el participante debe tener un éxito del 50% en el ejercicio 1,
  30% en el ejercicio 2, y una media de éxito del 60% en los ejercicios
  3, 4 y 5.

!exit

:allowtype

<center><b>Indicación sobre el registro de las notas.</b> </center>

 En el modo selectivo puede imponer una
 restricción en el tiempo en el que se grabarán las puntuaciones añadiendo las
 palabras
 <font color=blue><b>
 <tt>&gt;aaaammdd.hh:mm</tt></b></font>
 (inicio) y/o
 <font color=blue><b>
 <tt>&lt;aaaammdd.hh:mm</tt></b></font>
 (fin). Las fechas y horas deben estar indicadas en tiempo local del SERVIDOR
 y estas palabras deber ir separadas unas de otras por espacios.

!exit
:sheetpage

<center><b>Utilizar un bloque de documento para la presentación de una hoja de trabajo</b></center>

Pueden poner la dirección de un bloque de documento (como< tt> c1/main< /tt>)
para la página de presentación de una hoja de trabajo.
El propio documento no tiene necesidad de ser legible de los participantes.
<p>
Dejar este campo vacio si desean utilizar la página de presentación normal.
<p>
Los vínculos a los ejercicios individuales deben ser definidos por el pedido
<tt> \ exercise< /tt>.
Pueden utilizar las variables siguientes predefinidas: <ul>
<li>< tt> \ scorerequire</tt> Puntos requeridos por cada ejercicio
<Li>< tt> \ scoregot</tt> Trabajo del participante por cada ejercicio
<Li>< tt> \ scoremean</tt> Resultado medio del participante por cada ejercicio
<Li>< tt> \ expiration</tt> fecha de expiración de la hoja, aaaammdd
<Li>< tt> Fecha del día, aaaammdd

</ul>
