!set name_admpasswd=Contraseña de administrador del sitio

!read authscript.phtml
<p>
!if $passone!=$empty
Al no haber definido una contraseña de administrador el servidor ha generado
 una contraseña de un solo uso para esta sesión. Podrá encontrarla en el fichero
 <span class="tt">$wims_home/$oncename</span> en la cuenta del servidor WIMS.
 Por favor lea el fichero y teclee su contenido en el campo anterior.
 </p><p>
 Si desea definir una contraseña permanente (lo que es cómodo pero menos
 seguro que las contraseñas de un solo uso) puede guardarla en un fichero de
 nombre <span class="tt">$wims_home/log/.wimspass</span>.
 ¡Pero <b>DEBE</b> hacer que sólo usted pueda leer ese fichero!
!else
 Ha definido una contraseña permanente de administrador del sitio. Por favor
 recuerde que también puede utilizar contraseñas de un solo uso, que son más
 seguras.
 </p><p>
 Para cambiar a contraseñas de un solo uso no tiene más que borrar el fichero
 <span class="tt">$wims_home/log/.wimspass</span> de la cuenta del servidor WIMS.
!endif

</p><p>
En cualquier caso por favor tenga MUCHÍSIMO cuidado cuando maneje la
contraseña de administrador del sitio. ¡Una intrusión como administrador del
sitio puede poner en peligro TODOS los datos de su servidor!
</p>
