
!read adm/title.phtml 3\
\
Ficheros de imagen para el ejercicio

!if $quota=yes
 <span class="wims_warning">$wims_name_Error</span>. No puede añadir más ficheros a su clase porque su contendido
 ha igualado o superado el espacio de disco autorizado.
 Lo sentimos.
 <p>
 !goto sendend
!endif

!set wims_form_method=file
 Vous pouvez charger différents types de fichiers (image, mp3, pdf, ...).
 
!form reply
Fichero de imagen que se va a enviar en el ejercicio:
<input type="file" name="wims_deposit"/>
<input type="submit" value="$wims_name_tosave"/>

!formend

:sendend

!if $imglist=$empty
 Este ejercicio no tiene aún ningún fichero de imagen.
!else
 Lista de ficheros de imagen del ejercicio:
 <table class="wimsborder wimscenter">
 <tr><th>Nombre del fichero</th><th>Vista</th><th>-</th></tr>
 !for i in $imglist
  <tr><td>$i</td>
  <td>
  <img src="$wims_ref_name?cmd=getfile&+session=$wims_session&+special_parm=oefimg/$i" alt=""
   height="40px" width="50px" alt=""/></td>
  <td>
  !set wims_ref_class=wims_button
  !href cmd=reply&delfile=$i  $wims_name_erase
  </td>
 !next i
 </tr>
 $table_end 

 !if $imgfname!=
   !set example=$imgfname
 !else
  !set example=!item 1 of $imglist
 !endif
 <p>
 Se puede acceder a estos ficheros de imagen en el enunciado del ejercicio
 mediante el parámetro interno \imagedir. Por ejemplo puede escribir
 </p>
 <pre class="wimscenter">
 &lt;img src=\imagedir/$example/&gt;
 </pre>
 Puede también escribir simplemente <span class="tt">\img{\imagedir/$example}</span>, o
 <span class="tt">\img{\imagedir/$example}{opciones html}</span>. La ventaja de este segundo método
 es que los estudiantes no verán el nombre del fichero. A causa de su coste
 en consumo de recursos, no utilice este método más que cuando sea necesario.
!endif
<p class="wims_warning">
Sauvez l'exercice pour que les fichiers ajoutés le soient de manière
permanente.
</p>
!set wims_menu_items=!append line \
testexo,1,cmd=resume&level=3&realtest=yes&retest=again\
backcreatexo,1,cmd=reply&level=3\
to $wims_menu_items
