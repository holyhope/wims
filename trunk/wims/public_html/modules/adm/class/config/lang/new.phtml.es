
!if $backdays>7
 !if $backdays>100
  <p>Su clase no se salvaguardó desde más de 100 días.</p>
 !else
  <p>Última protección de su clase: hace $backdays días.</p>
 !endif
 !if backup iswordof $warn
  <p><span class="wims_warning">$wims_name_warning</span>.
  <br />
  ¡Es la responsabilidad de los profesores de salvaguardar sus recursos pedagógicos!
No cuentan nunca con la protección del servidor para recuperar su trabajo perdido.
Además, las clases virtuales que no son   salvaguardadas regularmente se considerarán
por el programa informático como siendo inactivas y sin importancia,
y pueden borrarse a cada momento para dejar lugar a los otros.

 !else
  <p> ¡Protegen se contra los incidentes del servidor!
 !endif
 !href cmd=reply&job=arch Salvaguarde la clase regularmente.
 </p>
!endif

!if creation iswordof $warn
 <p><span class="wims_warning">$wims_name_warning</span>. ¡Su clase virtual es demasiado vieja! Ya tiene $creatdays días.
 </p><p>
 Se recomienda vivamente reconstruir una nueva estructura de clase virtual
a principios de cada nuevo año escolar. Seguir utilizando una vieja clase virtual
durante años conducirá inexorablemente a un desbordamiento de los ficheros
de registro y la cuota de espacio disco, lo que corre el riesgo de bloquear
el acceso a su clase en un momento crucial.
 </p>
 !if $class_type notin 13
  <p>
  Ahí tienes cómo reconstruir su clase virtual sin rehacer sus recursos pedagógicos.
  </p>
  <ol>
  <li>
  !href cmd=reply&job=arch Salvaguardar su clase al fin del año escolar.
  </li><li>
  <a href="$wims_ref_name?lang=$lang&module=adm/class/regclass">Crear</a>
una nueva clase virtual (o grupo de clase o pórtico de
establecimiento) a principios del año escolar siguiente.
</li><li> restaurar los recursos pedagógicos (ejercicios, hojas, exámenes,
documentos) que salvaguardaron en la nueva clase.
(Sin restaurar las cuentas de alumnos y las actividades que son caducas.
)
  </li></ol>
 !else
  <p>
  Por favor informa al administrador del grupo de clases a cual
su clase pertenece.
  </p><p>
  Pueden
  !href cmd=reply&job=arch salvaguardar
  los recursos pedagógicos de su clase actual luego restaurarlos
en la nueva.
  </p>
 !endif
!endif
!exit
!if $warn=$empty
 !set job=list
 !changeto list.phtml
!else
  <div class="wimscenter">
  !href cmd=reply&job=list Seguir con el mantenimiento de la clase.
 </div>
!endif


