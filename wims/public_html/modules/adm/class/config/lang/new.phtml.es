<p>
!if $backdays>7
 !if $backdays>100
  Su clase no se salvaguardó desde más de 100 días.
 !else
  Última protección de su clase: hace $backdays días.
 !endif
 !if backup iswordof $warn
  <p><font color="red"><b>$wims_name_warning</b></font>
  ¡Es la responsabilidad de los profesores de salvaguardar sus recursos pedagógicos!
No cuentan nunca con la protección del servidor para recuperar su trabajo perdido.
Además, las clases virtuales que no son   salvaguardadas regularmente se considerarán
por el programa informático como siendo inactivas y sin importancia,
y pueden borrarse a cada momento para dejar lugar a los otros.

 !else
  <p> ¡Protegen se contra los incidentes del servidor!
 !endif
 !href cmd=reply&job=arch Salvaguarde la clase regularmente.
 <p>
!endif

!if creation iswordof $warn
 <p><b>$wims_name_warning</b>. ¡Su clase virtual es demasiado vieja! Ya tiene $creatdays días.
 <p>
 Se recomienda vivamente reconstruir una nueva estructura de clase virtual
a principios de cada nuevo año escolar. Seguir utilizando una vieja clase virtual
durante años conducirá inexorablemente a un desbordamiento de los ficheros
de registro y la cuota de espacio disco, lo que corre el riesgo de bloquear
el acceso a su clase en un momento crucial.

 !if $class_type notin 13
  <p>
  Ahí tienes cómo reconstruir su clase virtual sin rehacer sus recursos pedagógicos.
  <ol>
  <li><p>
  !href cmd=reply&job=arch Salvaguardar su clase al fin del año escolar.
  <li><p>
  <a href="$wims_ref_name?lang=$lang&module=adm/class/regclass">Crear</a>
una nueva clase virtual (o grupo de clase o pórtico de
establecimiento) a principios del año escolar siguiente.
<li><p> restaurar los recursos pedagógicos (ejercicios, hojas, exámenes,
documentos) que salvaguardaron en la nueva clase.
(Sin restaurar las cuentas de alumnos y las actividades que son caducas.
)
  </ol>
 !else
  <p>
  Por favor informa al administrador del grupo de clases a cual
su clase pertenece.
  <p>
  Pueden
  !href cmd=reply&job=arch salvaguardar
  los recursos pedagógicos de su clase actual luego restaurarlos
en la nueva.
 !endif
!endif

!if $warn=$empty
 !set job=list
 <p>
 !changeto list.phtml
!else
 <p><center>
  !href cmd=reply&job=list Seguir con el mantenimiento de la clase.
 </center>
!endif


