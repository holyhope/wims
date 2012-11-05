!!INDEX
!let module_author=XIAO, Gang
!let module_address=xiao@unice.fr
!let module_title=Configuraci�n de preferencias para WIMS
!let module_description=define tus preferencias en WIMS
!let module_version=1.00
!let module_wims_version=0.13
!let module_language=es
!let module_copyright=&copy; 1998 (<a href="COPYING">GNU GPL</a>)
!let module_category=adm
!let module_level=
!let module_domain=adm
!let module_keywords=wims
!let module_translator=Juan Rafael Fern�ndez Garc�a
!let module_translator_address=juanrafael.fernandez@hispalinux.es
!!INDEXEND

!let tip='<ul><li>FireFox&nbsp;<a target=\'new\' href=\'http://www.mozilla-europe.org/$module_language/\'><img src=\'gifs/mathml/getFireFox.gif\' alt=\'get FireFox\'/></a></li><li>Windows<ul><li>Internet Explorer: <a target=\'new\' href=\'http://www.dessci.com/en/products/mathplayer/\'><img src=\'gifs/mathml/dessci_logo.gif\' alt=\'dessci\'/> DESSCI MathPlayer plugin</a><li>Opera: <a target=\'new\' href=\'http://xml-maiden.com/userjs/mathml/\'>UserJS MathML plugin</a></ul></li><li>Safari</li></ul>'


!let texsize=!char 1 of $useropts
!let texalign=!char 2 of $useropts
!let default=$[$wims_texbasesize-1]
!default texsize=$default
!let default=!char 1 of $default
!default texalign=$talign
!set arg=!nospace $texsize 1

!let useropt2=!char 3 to -1 of $useropts
!if $useropts!=$empty and $wims_realuser!=$empty
 !readproc adm/class/userdef classes,$wims_class,$wims_realuser
 !setdef !set user_opts=$useropts in $userdef
 !setdef wims_useropts=$useropts in wimshome/$wims_sesdir/var.stat
!endif

!set zoom=!char 3 of $useropts
    
!header
<script type="text/javascript" src="scripts/js/wz_tooltip.js"></script>
Esta p�gina le permite cambiar las preferencias de su sesi�n de trabajo
en WIMS.
<ul>
!if $wims_user=$empty
 <li>El lenguaje predeterminado.
  !set wims_language_cnt=!wordcnt $wims_site_languages
  !for l=1 to $wims_language_cnt
   !let la=!word $l of $wims_site_languages
   !href cmd=resume&phtml=useropts.phtml.$la&lang=$la <img src="gifs/$la.gif" alt="$la.gif" border="1" />$(lang_name_$la)
   &nbsp;&nbsp;
  !next l
  </li>
!endif

<li>
Mathematical formulas.

!if $texalign=2
  The server is currently set to MathML if you have a suitable browser. For example,
    <p class="wimscenter">
    !insmath x_{1,2} = \frac{-b \pm \sqrt{b^{2} - 4 a c}}{2a}
    </p>
    If the formula is not correctly displayed, you can use another
    <a onmouseover="return Tip($tip)"><span class="wims_emph">browser</span>
    </a> 
    or use the serveur with "math with images".
!set wims_ref_class=wims_button
<p class="wimscenter">
   !href cmd=resume&useropts=$arg Math with images
</p> 
</li><li>
    !let ts1=!eval $texsize-1
    !let ts2=!eval $texsize+1
    !if $ts1<1
      !let ts1=1
    !endif
    !if $ts2>9
      !let ts2=9
    !endif
    Set the size of mathematical formulas.
!set wims_ref_class=wims_button
    !href cmd=resume&useropts=$ts1$texalign <img src="gifs/doc/dgauche.gif" width="20px" />
    &nbsp;
!set wims_ref_class=wims_button
    !href cmd=resume&useropts=$default Default
    &nbsp;
!set wims_ref_class=wims_button
    !href cmd=resume&useropts=$ts2$texalign <img src="gifs/doc/ddroite.gif" width="20px"/>
 </li><li>
!set zoom=1
  Use zoom on formulas by mouse click.
!set wims_ref_class=wims_button
!href cmd=resume&useropts=$texsize$texalign$zoom $wims_name_yes
!set zoom=0 
   &nbsp;
!set wims_ref_class=wims_button
   !href cmd=resume&useropts=$texsize$texalign$zoom $wims_name_no
!else
    Currently, you use the server with "Math with images". If you have a suitable 
    <a onmouseover="return Tip($tip)"><span class="wims_emph">browser</span>, you may also use MathML.
<p class="wimscenter">
!set arg=!nospace $texsize 2
!set wims_ref_class=wims_button
!href cmd=resume&useropts=$arg MathML
</p>

</li><li>
Size of mathematical symbols and formulas. 
!let ts1=!eval $texsize-1
!let ts2=!eval $texsize+1
!if $ts1<1
    !let ts1=1
  !endif
!if $ts2>9
    !let ts2=9
!endif
!set wims_ref_class=wims_button
    !href cmd=resume&useropts=$ts1$texalign$useropt2 <img src="gifs/doc/dgauche.gif" width="20px" />
    &nbsp;
!set wims_ref_class=wims_button
    !href cmd=resume&useropts=$ts2$texalign$useropt2 <img src="gifs/doc/ddroite.gif" width="20px" />
  <p>
  Letras griegas $m_alpha, $m_pi. Expresiones matem�ticas 
  !let ins_align=middle
!! we need to force dynamic insertion
  !set pw=2
  !insmath x_{1,2} = \frac{-b \pm \sqrt{b^{$pw} - 4ac}}{2a}
  Una desigualdad
  </p><p class="wimscenter">| $m_a + $m_b | $m_le $m_varepsilon + 123.45.</p>
</li><li>
Position of the formulas. If the expression
  !insmath (x+y)/(x^$pw + y^2)
  es
  !if $texalign=1
   demasiado alta con respecto a la l�nea de texto,
   !href cmd=resume&useropts=$(texsize)0$useropt2 pulse aqu�
   para reducirla.
  !else
   demasiado baja con respecto a la l�nea de texto,
   !href cmd=resume&useropts=$(texsize)1$useropt2 pulse aqu�
   para agrandarla.
  !endif
!set zoom=$empty
!endif
</li>
</ul>

Cuando todo corresponda exactamente con lo que quiera, ponga
<a href="$wims_ref_name?lang=$lang&+useropts=$texsize$texalign$useropt2$zoom"
 title="WIMS">este enlace</a>
en sus Favoritos, para mantener estas preferencias para conexiones futuras.

:end
!tail
