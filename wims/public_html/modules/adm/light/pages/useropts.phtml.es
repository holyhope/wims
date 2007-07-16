!!INDEX
!let module_author	=XIAO, Gang
!let module_address	=xiao@unice.fr
!let module_title	=Configuración de preferencias para WIMS
!let module_description	=define tus preferencias en WIMS
!let module_version	=1.00
!let module_wims_version=0.13
!let module_language	=es
!let module_copyright	=&copy; 1998 (<a href=COPYING>GNU GPL</a>)
!let module_category	=adm
!let module_level	=
!let module_domain	=adm
!let module_keywords	=wims
!let module_translator	=Juan Rafael Fernández García
!let module_translator_address=juanrafael.fernandez@hispalinux.es
!!INDEXEND

!let texsize=!char 1 of $useropts
!let texalign=!char 2 of $useropts
!default texsize=$[$wims_texbasesize-1]
!default texalign=$talign
!let useropt2=!char 3 to -1 of $useropts
!if $useropts!=$empty and $wims_realuser!=$empty
 !readproc adm/class/userdef classes,$wims_class,$wims_realuser
 !setdef !set user_opts=$useropts in $userdef
 !setdef wims_useropts=$useropts in wimshome/$wims_sesdir/var.stat
!endif

!header

Esta página le permite cambiar las preferencias de su sesión de trabajo
en WIMS.
<p>
Estas preferencias son:
<ul>
 <li>El lenguaje predeterminado.
  !for l=1 to $wims_language_cnt
   !let la=!word $l of $wims_site_languages
   !href cmd=resume&phtml=useropts.phtml.$la&lang=$la <img src=gifs/$la.gif border=1>$(lang_name_$la)
   &nbsp;&nbsp;
  !next l
 <p><li>El tamaño de los símbolos matemáticos y las fórmulas. Use la siguiente
  línea para comparar los tamaños de los símbolos y los textos.
  <p>
  Letras griegas $m_alpha,$m_pi. Expresiones matemáticas 
  !let ins_align=middle
  !instex $$x^3\sin(x)+{\sqrt{x^2+1}\over105}-123.45$$.
  Una desigualdad
  <center>| $m_a + $m_b | $m_le $m_varepsilon + 123.45.</center>
  <p>
  Puede
  !let ts1=!eval $texsize-1
  !let ts2=!eval $texsize+1
  !if $ts1<1
    !let ts1=1
  !endif
  !if $ts2>9
    !let ts2=9
  !endif
  !href cmd=resume&useropts=$ts1$texalign$useropt2 decrementar
  o
  !href cmd=resume&useropts=$ts2$texalign$useropt2 incrementar
  el tamaño de los símbolos matemáticos, para hacerlos corresponder al texto.
  Si la expresión
  !insmath (x+y)/(x^2+y^2)
  es
  !if $texalign=1
   demasiado alta con respecto a la línea de texto,
   !href cmd=resume&useropts=$(texsize)0$useropt2 pulse aquí
   para reducirla.
  !else
   demasiado baja con respecto a la línea de texto,
   !href cmd=resume&useropts=$(texsize)1$useropt2 pulse aquí
   para agrandarla.
  !endif
</ul>

Cuando todo corresponda exactamente con lo que quiera, ponga
<a href="$wims_ref_name?lang=$lang&useropts=$texsize$texalign$useropt2"
 title="WIMS">este enlace</a>
en sus Favoritos, para mantener estas preferencias para conexiones futuras.

:end
!tail

