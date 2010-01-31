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


:sheetpage

<center><b>Using a document block for worksheet presentation</b></center>

You may put the address of a document block
(such as <tt>c1/main</tt>) to be the presentation page of the work sheet.
The document itself need not be readable by participants.
<p>
Leave this field blank if you want to use the standard presentation page.
<p>
Links to individual exercises should be defined using the command
<tt>\exercise</tt>.
You can use the following pre-defined variables:<ul>
 <li><tt>\scorerequire</tt> Required points of each exercise
 <li><tt>\scoregot</tt> Participant's point achievements on each exercise
 <li><tt>\scoremean</tt> Participant's average score on each exercise
 <li><tt>\expiration</tt> Expiration date of the sheet, yyyymmdd
 <li><tt>\today</tt> Date of today, yyyymmdd

</ul>