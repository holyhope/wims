<p>Desde aquí puede configurar las restricciones a nivel de clase de los sitios
 a los que se les permita recibir calificaciones. Estas restricciones
 se aplicarán siempre independientemente de la configuración individual
 de las hojas.
</p>
 !read grestrictform.phtml
<p>
Puede introducir una o varias palabras en cada campo. El servidor
verificará cada palabra contra el nombre o el número IP de cada sitio que se conecte.
La regla correspondiente se aplicará cada vez. Una palabra definida aquí es
una subcadena de caracteres del nombre de la estación de trabajo o de su número IP.
</p>
<div class="wims_smallremark"><b>Sugerencia.</b> En el campo
<span class="wims_label">Sitios a los que se les permite recibir calificaciones</span>, puede imponer una
 restricción en el tiempo disponible para el registro de las notas añadiendo
 las palabras
 <span class="tt wims_code_words">
&gt;aaaammdd.hh:mm</span>
 (inicio) y/o
 <span class="tt wims_code_words">
&lt;aaaammdd.hh:mm</span>
 (fin). Las fechas y horas deben indicarse en tiempo local del SERVIDOR,
 y estas palabras deben estar separadas unas de otras por espacios.
  </div>
