!! to translate this help you just have to copy this file with correct extension (fr en de) and translate it !
!!

!let help_isread=yes
El cuaderno de competencias permite obtener una rejilla de lectura sintética del conjunto
del trabajo tenido en cuenta de los alumnos de la clase.
< br> El cuaderno consta como máximo de competencias (….) cada una de sus competencias
puede poseer varios grados (hasta….).
<p>
Para cada grado, el profesor puede definir la lista de las series de ejercicios de la clase
para los cuales el resultado va a producir en el cálculo del nivel de adquisición del grado.
< p>
El profesor de la clase puede decidir que se neutralizan algunas hojas virtuales para
el cálculo del nivel de adquisición de los grados del cuaderno de competencias
(eso permite conservar los datos pedagógicos de un año sobre el otro permitiendo
al mismo tiempo comenzar a validar algunas competencias).
<p>
El cálculo del nivel de adquisición se efectúa de la siguiente forma:

<center>
!insmath 10 \times \frac{\sum_{i=1}^{N} NM(x_{L[i;1],L[i;2]})}{\sum_{i=1}^{N} \delta_{L[i;1]}}
</center>
où
<ul>
 <li> <i>N</i> es el número de series de ejercicios que se producen en el grado.</li>
 <li> <i>L</i> es la lista de las series de ejercicios que se producen en el grado. Cada elemento de la lista contiene el número de hoja (escrito L[i;1]) y
 el número de la serie de ejercicios en la hoja (escrito)L[i;2]).</li>
 <li>
  !insmath X_{i,j}
  es la nota de calidad de la serie de ejercicios <i>j</i> de la hoja <i>i</i>.</li>
 <li>
  !insmath \delta_i
  vale 1 si la hoja <i> i</i> no está en la lista de las hojas desactivadas para el cálculo del nivel de adquisición de los grados y <I>0</i> si no. </li>
 <li> NM(a) vale <i> 1</i> si y <I><a /i> es superior a la nota mínima para considerar que se adquiere una serie y <I> 0</i> si no (fijar la nota mínima a <i>0</i> neutraliza esta opción.</li>
</ul>
