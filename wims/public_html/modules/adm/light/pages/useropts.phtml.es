!!INDEX
!let module_translator=Juan Rafael Fernández García
!let module_translator_address=juanrafael.fernandez@hispalinux.es
!let module_title=Configuración de preferencias para WIMS
!let module_description=define tus preferencias en WIMS
!let module_language=es
!!INDEXEND

!let tip='<ul><li>FireFox&nbsp;<a target=\'new\' href=\'http://www.mozilla-europe.org/$module_language/\'><img src=\'gifs/mathml/getFireFox.gif\' alt=\'get FireFox\'/></a></li><li>Google Chrome&nbsp;<a target=\'new\' href=\'https://chrome.google.com/webstore/detail/mathjax-for-chrome/elbbpgnifnallkilnkofjcgjeallfcfa\'> MathJax Extension </a><li>Windows<ul><li>Internet Explorer: <a target=\'new\' href=\'http://www.dessci.com/en/products/mathplayer/\'><img src=\'gifs/mathml/dessci_logo.gif\' alt=\'dessci\'/> DESSCI MathPlayer plugin</a><li>Opera: <a target=\'new\' href=\'http://xml-maiden.com/userjs/mathml/\'>UserJS MathML plugin</a></ul></li><li>Safari</li></ul>'

!read proc/useropts.proc

!header
<script type="text/javascript" src="scripts/js/wz_tooltip.js"></script>
<p>Esta página le permite cambiar las preferencias de su sesión de trabajo
  en WIMS.</p>

<div id="widget_useropts">
  <ul>
    <li><a href="#formula">Mathematical formulas</a></li>
    !if $wims_user=$empty
      <li><a href="#language_selector">El lenguaje predeterminado</a></li>
    !endif
    <li><a href="#accessibility">Accessibility</a></li>
  </ul>

  <div id="language_selector">
    <h2>
      El lenguaje predeterminado
    </h2>
    <p>
      !read themes/_widgets/language_selector.phtml
    </p>
  </div>

  <div id="formula">
    <h2>
     Mathematical formulas
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
          !href cmd=resume&useropts=$ts1$texalign$zoom$font <img src="gifs/doc/dgauche.gif" alt="gauche" style="width:1em" />
          !set wims_ref_class=wims_button
          !href cmd=resume&useropts=$default Default
          !set wims_ref_class=wims_button
          !href cmd=resume&useropts=$ts2$texalign$zoom$font <img src="gifs/doc/ddroite.gif" alt="droite" style="width:1em" />
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
       !href cmd=resume&useropts=$ts1$texalign$zoom$font <img src="gifs/doc/dgauche.gif" style="width:1em" />
       !set wims_ref_class=wims_button
       !href cmd=resume&useropts=$ts2$texalign$zoom$font <img src="gifs/doc/ddroite.gif" style="width:1em" />
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
  </div>

  <div id="accessibility">
    <h2>Accessibility</h2>

    <p>Vous pouvez régler l'espacement des lettres et des mots
        !set wims_ref_class=wims_button
        !href cmd=resume&useropts=$(texsize)$texalign$(zoom)0 Normal

        !set wims_ref_class=wims_button
        !href cmd=resume&useropts=$(texsize)$texalign$(zoom)1 Espacé
    </p><p>
    Le mode espacé est particulierement adapté dans le cas d'un lecteur dyslexique.</p>

    <br class="spacer" />
  </div>

</div>
!if $jquery_defined=yes
  !read adm/tabscript useropts
!endif

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

!tail
