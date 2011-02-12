
!read adm/title.phtml 3\
\
Ficheros de imagen para el ejercicio

!if $quota=yes
 <b>Error</b>. No puede añadir más ficheros a su clase porque su contendido
 ha igualado o superado el espacio de disco autorizado.
 Lo sentimos.
 <p>
 !goto sendend
!endif

!set wims_form_method=file
 Vous pouvez charger différents types de fichiers chargés (image, mp3, pdf, ...).
 
!form reply
Fichero de imagen que se va a enviar en el ejercicio:
<input type="file" name="wims_deposit">
<input type="submit" value="$wims_name_tosave">
</form>

:sendend

!if $imglist=$empty
 Este ejercicio no tiene aún ningún fichero de imagen.
!else
 Lista de ficheros de imagen del ejercicio:
 <p><center><table border="2">
 <th>Nombre del fichero</th><th>Vista</th><th>-</th>
 !for i in $imglist
  <tr><td valign="middle" align="center">$i</td>
  <td valign="middle" align="center">
  <img src="$wims_ref_name?cmd=getfile&+session=$wims_session&+special_parm=oefimg/$i" alt=""
   height="40" width="50"></td>
  <td valign="middle" align="center">
  !set wims_ref_class=wims_button
  !href cmd=reply&delfile=$i  $wims_name_erase
  </td>
 !next i
 $table_end <p>
 !set example=!item 1 of $imglist
 Se puede acceder a estos ficheros de imagen en el enunciado del ejercicio
 mediante el parámetro interno \imagedir. Por ejemplo puede escribir
 <center><pre>
 &lt;img src=\imagedir/$example&gt;
 </pre></center>
 Puede también escribir simplemente <tt>\img{\imagedir/$example}</tt>, o
 <tt>\img{\imagedir/$example}{opciones html}</tt>. La ventaja de este segundo método
 es que los estudiantes no verán el nombre del fichero. A causa de su coste
 en consumo de recursos, no utilice este método más que cuando sea necesario.
!endif

Sauvez l'exercice pour que les fichiers ajoutés le soient de manière
permanente.

!set wims_menu_items=!append line \
testexo,1,cmd=resume&level=3&realtest=yes&retest=again\
backcreatexo,1,cmd=reply&level=3\
to $wims_menu_items
