
<center>
!form reply
Por favor introduzca la contraseña de administrador del sitio:<p>
<input size="24" type="password" name="auth">
<input type="submit" value="$wims_name_tosave">
</form></center>

!if $passone!=$empty
 Al no haber definido una contraseña de administrador el servidor ha generado
 una contraseña de un solo uso para esta sesión. Podrá encontrarla en el fichero
 <tt>$wims_home/$oncename</tt> en la cuenta del servidor WIMS. 
 Por favor lea el fichero y teclee su contenido en el campo anterior.
 <p>
 Si desea definir una contraseña permanente (lo que es cómodo pero menos
 seguro que las contraseñas de un solo uso) puede guardarla en un fichero de
 nombre <tt>$wims_home/log/.wimspass</tt>. 
 ¡Pero <b>DEBE</b> hacer que sólo usted pueda leer ese fichero!
!else
 Ha definido una contraseña permanente de administrador del sitio. Por favor
 recuerde que también puede utilizar contraseñas de un solo uso, que son más 
 seguras.
 <p>
 Para cambiar a contraseñas de un solo uso no tiene más que borrar el fichero
 <tt>$wims_home/log/.wimspass</tt> de la cuenta del servidor WIMS.
!endif

<p>
En cualquier caso por favor tenga MUCHÍSIMO cuidado cuando maneje la
contraseña de administrador del sitio. ¡Una intrusión como administrador del
sitio puede poner en peligro TODOS los datos de su servidor!

