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

<center><b>Indication sur l'enregistrement des notes.</b> </center>

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

