!set lang_exists=yes
!if $wims_read_parm=$empty
 !exit
!endif

!goto $wims_read_parm

:file
<p>Ficheros disponibles en este documento:
 !for f in $flist
  !getfile doc/$f $f
  &nbsp;
 !next f
 </p>
 !form reply
 <input type="hidden" name="job2" value="erase" />
 Borrar un fichero:
 !formselect job2 list $flist
 <input type="submit" value="$wims_name_erase" />
 
!formend
 <p>
 Se puede acceder a los ficheros del documento usando la 
variable <span class="tt wims_code_variable">\filedir</span> en el documento. Por ejemplo
</p><p class="wimscenter">
 <span class="tt wims_address">&lt;a href="\filedir/$f1"&gt;$f1&lt;/a&gt;</span>
</p><p>
 proporciona un enlace al fichero <a href="$m_filedir/$f1">$f1</a>.
 También puede escribir
</p><p class="wimscenter">
 <span class="tt wims_address">&lt;img src="\filedir/myfile.jpg" alt="myfile"&gt;</span>
</p><p>
para incluir un fichero de imagen <span class="tt wims_fname">myfile.jpg</span> en la página.
 Los ficheros incorporados en el documento sólo serán accesibles
 a quienes estén autorizados a leer el documento.
</p>
Une nouvelle commande <span class="tt wims_code_words">\href{}{}</span> est en test. 
Pour obtenir un lien sur le fichier, il suffit alors d'écrire
<p class="wimscenter">
<span class="tt wims_code_words">\href{$f1}</span> ou <span class="tt wims_code_words">\href{$f1}{lien}</span>.
</p>
!exit

:readauth
Si es usted el autor del documento, recuerde por favor que necesita
 la autorización del
 !mailurl $wims_site_manager administrador del sitio\
Solicitud de apertura del documento WIMS $doc
 para hacer que el público pueda leer el documento.
 
!exit

:public

<b>Nota</b>. Necesita la aprobación del
 !mailurl $wims_site_manager administrador del sitio\
Ask to open WIMS document $doc
 para permitir que el público pueda acceder al documento.
 
!exit

:erase1

 Por razones de seguridad sólo los administradores del sitio pueden
 borrar documentos públicos.
 <p>
 Puede 
 !mailurl $wims_site_manager [wims] Pedir al administrador del sitio
 que borre este documento por usted.
 </p>
!exit

:erase2
<span class="wims_warning">ATENCIÓN!!</span> 
¡Una vez borrados los documentos no se pueden recuperar!
<p>
¿Está seguro de que quiere borrar el documento <span class="tt wims_fname">$tit</span>?
</p>

!exit


