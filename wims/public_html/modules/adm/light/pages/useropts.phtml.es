!!INDEX
!let module_author=XIAO, Gang
!let module_address=xiao@unice.fr
!let module_title=Configuración de preferencias para WIMS
!let module_description=define tus preferencias en WIMS
!let module_version=1.00
!let module_wims_version=0.13
!let module_language=es
!let module_copyright=&copy; 1998 (<a href="COPYING">GNU GPL</a>)
!let module_category=adm
!let module_level=
!let module_domain=adm
!let module_keywords=wims
!let module_translator=Juan Rafael Fernández García
!let module_translator_address=juanrafael.fernandez@hispalinux.es
!!INDEXEND

!let tip='<ul><li>FireFox&nbsp;<a target=\'new\' href=\'http://www.mozilla-europe.org/$module_language/\'><img src=\'gifs/mathml/getFireFox.gif\' alt=\'get FireFox\'/></a></li><li>Windows<ul><li>Internet Explorer: <a target=\'new\' href=\'http://www.dessci.com/en/products/mathplayer/\'><img src=\'gifs/mathml/dessci_logo.gif\' alt=\'dessci\'/> DESSCI MathPlayer plugin</a><li>Opera: <a target=\'new\' href=\'http://xml-maiden.com/userjs/mathml/\'>UserJS MathML plugin</a></ul></li><li>Safari</li></ul>'


!let texsize=!char 1 of $useropts
!let texalign=!char 2 of $useropts
!let default=$[$wims_texbasesize-1]
!default texsize=$default
!let default=!char 1 of $default
!default texalign=$talign
!set zoom=!char 3 of $useropts
!set font=!char 4 of $useropts
!default zoom=0
!default font=0
!set arg=!nospace $texsize 1

!let useropt2=!char 3 to -1 of $useropts
!if $useropts!=$empty and $wims_realuser!=$empty
 !readproc adm/class/userdef classes,$wims_class,$wims_realuser
 !setdef !set user_opts=$useropts in $userdef
 !setdef wims_useropts=$useropts in wimshome/$wims_sesdir/var.stat
!endif

    
!header
<script type="text/javascript" src="scripts/js/wz_tooltip.js"></script>
Esta página le permite cambiar las preferencias de su sesión de trabajo
en WIMS.

!if $wims_user=$empty
 <h2>
  El lenguaje predeterminado.
 </h2>
  <p>
  !set wims_language_cnt=!wordcnt $wims_site_languages
  !for l=1 to $wims_language_cnt
   !let la=!word $l of $wims_site_languages
   !href cmd=resume&phtml=useropts.phtml.$la&lang=$la <img src="gifs/$la.gif" alt="$la.gif" style="height:1.1em;" />$(lang_name_$la)
   &nbsp;&nbsp;
  !next l
  </p>

!endif

<h2>
 Mathematical formulas.
</h2>
<p>
Le serveur permet 2 modes d'affichage des formules : le mode image, ou l'utilisation de MathML (à condition que votre navigateur le supporte).</p>
    Voici quelques exemples : 
    <ul>
      <li>
       Letras griegas. 
          <pre>
           !insmath alpha != pi
          </pre>
      </li>
      <li>
       Expresiones matemáticas 
       !let ins_align=middle
    !! we need to force dynamic insertion
       !set pw=2
       <pre>
        !insmath x_{1,2} = \frac{-b \pm \sqrt{b^{$pw} - 4a c}}{2a}
       </pre>
      </li>
      <li>
       Una desigualdad: 
        <pre>
         !insmath | a + b | <= epsilon + 123.45
        </pre>
      </li>
    </ul>

!if $texalign=2
  <p>
  The server is currently set to MathML if you have a suitable browser. 
    If the formula is not correctly displayed, you can use another
    <a onmouseover="return Tip($tip)" class="wims_emph" style="cursor:help;">
    browser
    </a> 
    or use the serveur with "math with images".
    </p>
    <ul>
     <li>
     Modifier le mode d'affichage : 
      !set wims_ref_class=wims_button
      !href cmd=resume&useropts=$(arg)0$font Math with images
      
      !set arg=!nospace $texsize 2
      !set wims_ref_class=wims_button
      !href cmd=resume&useropts=$(arg)0$font MathML

     </li>
     <li>
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
      !href cmd=resume&useropts=$ts1$texalign$zoom$font <img src="gifs/doc/dgauche.gif" alt="gauche" style="width:1em"/>
      !set wims_ref_class=wims_button
      !href cmd=resume&useropts=$default Default
      !set wims_ref_class=wims_button
      !href cmd=resume&useropts=$ts2$texalign$zoom$font <img src="gifs/doc/ddroite.gif" alt="droite" style="width:1em"/>
     </li><li>
      Use zoom on formulas by mouse click.
      !set wims_ref_class=wims_button
      !href cmd=resume&useropts=$texsize$(texalign)1$font $wims_name_yes
      &nbsp;
      !set wims_ref_class=wims_button
      !href cmd=resume&useropts=$texsize$(texalign)0$font $wims_name_no
!else
 <p>
    Currently, you use the server with "Math with images". If you have a suitable 
    <a onmouseover="return Tip($tip)" class="wims_emph" style="cursor:help;">
    browser
    </a>, 
    you may also use MathML.
 </p>

 <ul>
  <li>Modifier le mode d'affichage : 
   !set wims_ref_class=wims_button
   !href cmd=resume&useropts=$(arg)0$font Mode image

   !set arg=!nospace $texsize 2
   !set wims_ref_class=wims_button
   !href cmd=resume&useropts=$(arg)0$font MathML
  </li>

  <li>
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
   !href cmd=resume&useropts=$ts1$texalign$zoom$font <img src="gifs/doc/dgauche.gif" style="width:1em"/>
   !set wims_ref_class=wims_button
   !href cmd=resume&useropts=$ts2$texalign$zoom$font <img src="gifs/doc/ddroite.gif" style="width:1em"/>
</li><li>
Position of the formulas. If the expression
  !insmath (x+y)/(x^$pw + y^2)
  es
  !if $texalign=1
   demasiado alta con respecto a la línea de texto,
   !href cmd=resume&useropts=$(texsize)0$zoom$font pulse aquí
   para reducirla.
  !else
   demasiado baja con respecto a la línea de texto,
   !href cmd=resume&useropts=$(texsize)1$zoom$font pulse aquí
   para agrandarla.
  !endif
!endif
</li>
</ul>

<h2>Accessibilité</h2>

<p>Vous pouvez régler l'espacement des lettres et des mots 
    !set wims_ref_class=wims_button
    !href cmd=resume&useropts=$(texsize)$texalign$(zoom)0 Normal
    
    !set wims_ref_class=wims_button
    !href cmd=resume&useropts=$(texsize)$texalign$(zoom)1 Espacé
</p><p>
Le mode espacé est particulierement adapté dans le cas d'un lecteur dyslexique.</p>

<br class="spacer"/>
<p>
!if $wims_user=$empty
Cuando todo corresponda exactamente con lo que quiera, ponga
  !set wims_ref_class=wims_button
 <a href="$wims_ref_name?lang=$lang&+useropts=$texsize$texalign$zoom$font" title="WIMS">
 este enlace
 </a>
en sus Favoritos, para mantener estas preferencias para conexiones futuras.
!else
 Your preferences will be preserved in your future logins in this class.
!endif
</p>

:end
!tail
