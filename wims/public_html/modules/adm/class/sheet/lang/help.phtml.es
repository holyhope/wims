!if $wims_read_parm!=$empty
 !goto $wims_read_parm
!endif

:dependancies
<center><b>$(name_shtab[6])</b></center>
  quiere decir que
  un participante debe primero lograr puntos en otros ejercicios de la hoja,
  antes de poder trabajar en este. Por ejemplo,
  <tt class="wims_code_words">1:50,2:30,3+4+5:60</tt>
  significa que el participante debe tener un éxito del 50% en el ejercicio 1,
  30% en el ejercicio 2, y una media de éxito del 60% en los ejercicios
  3, 4 y 5.

!if $wims_read_parm!=$empty
 !exit
!endif

:allowtype

<center><b>Indicación sobre el registro de las notas.</b> </center>

 En el modo selectivo puede imponer una
 restricción en el tiempo en el que se grabarán las puntuaciones añadiendo las
 palabras
 <tt class="wims_code_words">
&gt;aaaammdd.hh:mm</tt>
 (inicio) y/o
 <tt class="wims_code_words">
&lt;aaaammdd.hh:mm</tt>
 (fin). Las fechas y horas deben estar indicadas en tiempo local del SERVIDOR
 y estas palabras deber ir separadas unas de otras por espacios.

!exit
