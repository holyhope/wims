!!INDEX
!let module_translator=Juan Rafael Fernández García
!let module_translator_address=juanrafael.fernandez@hispalinux.es
!let module_title=Configuración de preferencias para WIMS
!let module_description=define tus preferencias en WIMS
!let module_language=es
!!INDEXEND

!let tip=<ul><li><strong>FireFox</strong> nativamente soporta MathML sin extensión</li><li><strong>Safari</strong> nativamente soporta MathML sin extensión</li><li><strong>Google Chrome</strong> necesita <a target="new" href="https://chrome.google.com/webstore/detail/mathjax-for-chrome/elbbpgnifnallkilnkofjcgjeallfcfa">MathJax Extension </a></li><li><strong>Internet Explorer</strong> necesita <a target="new" href="http://www.dessci.com/en/products/mathplayer/">DESSCI MathPlayer plugin</a></li><li><strong>Opera</strong> necesita <a target="new" href="http://xml-maiden.com/userjs/mathml/">UserJS MathML plugin</a></li></ul>

!read proc/useropts.proc

!header

<p>Esta página le permite cambiar las preferencias de su sesión de trabajo en WIMS.</p>

<div id="widget_useropts">
  <ul>
    <li><a href="#formula">Fórmulas matemáticas</a></li>
    !if $wims_user=$empty
      <li><a href="#language_selector">Lengua predeterminada</a></li>
    !endif
    <li><a href="#accessibility">Accesibilidad</a></li>
  </ul>

  !if $wims_user=$empty
  <div id="language_selector">
    <h2>Lengua predeterminada</h2>
    <p>
      Escoja la lengua predeterminada:
      !read themes/_widgets/language_selector.phtml
    </p>
  </div>
  !endif

  <div id="formula">
    <h2>Fórmulas matemáticas</h2>
    <p>
       El servidor permite dos modos de visualización de fórmulas: el Modo imagen, o la utilización de MathML (si el navegador lo soporta).</p>
!!      <p>
      !if $texalign=2
        <p>Actualmente, las fórmulas se muestran en modo MathML.</p>
      !endif
    Algunos ejemplos:
    <ul>
      <li>
        Letras griegas:
        <pre>
         !insmath alpha != pi
        </pre>
      </li>
      <li>
        Expresión matemática
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
        Si los ejemplos no se muestran correctamente, puede utilizar otro
        navegador o utilizar el servidor en "Modo imagen".
      </p>
        <h3>Modo de visualización</h3>
        <p>
         Ahora está en modo MathML
          !set wims_ref_class=wims_button
          !href cmd=resume&useropts=$(arg)0$font Pasar a modo imagen
        </p>
        <h3 id="formula_options">Opción de modo MathML:</h3>
          <p>El modo MathML permite un zoom con un click del ratón sobre las fórmulas.</p>
          !set wims_ref_class=wims_button
          !if $useropts=$texsize$(texalign)0$font
            El zoom está <span class="disabled">desactivado</span>.
            !href cmd=resume&useropts=$texsize$(texalign)1$font#formula_options activar
            <span class="wims_button disabled">desactivar</span>
          !else
            El zoom está <span class="oef_indgood success">activado</span>.
            <span class="wims_button disabled">activar</span>
            !href cmd=resume&useropts=$texsize$(texalign)0$font#formula_options desactivar
          !endif
        <h3>Navegadores compatibles MathML</h3>
        $tip

    !else
      <p>
        Ahora el servidor está configurado en <strong>Modo imagen</strong>.<br/> 
        Con un navegador compatible puede utilizar MathML.
      </p>
      <h3>Modo de visualización</h3>
      <p>
        Ahora está en modo Imagen
        !set arg=!nospace $texsize 2
        !set wims_ref_class=wims_button
        !href cmd=resume&useropts=$(arg)0$font Pasar a modo MathML
      </p>
      <h3>Opciones del modo imagen</h3>
      <ul><li>
          Medida de los símbolos y expresiones matemáticas .
         !let ts1=!eval $texsize-1
         !let ts2=!eval $texsize+1
         !if $ts1<1
           !let ts1=1
         !endif
         !if $ts2>9
          !let ts2=9
         !endif
         !set wims_ref_class=wims_button
         !href cmd=resume&useropts=$ts1$texalign$zoom$font#formula <img src="gifs/doc/dgauche.gif" style="width:1em" />
         !set wims_ref_class=wims_button
         !href cmd=resume&useropts=$[$wims_texbasesize-1]$texalign$zoom$font#formula Normal
         !set wims_ref_class=wims_button
         !href cmd=resume&useropts=$ts2$texalign$zoom$font#formula <img src="gifs/doc/ddroite.gif" style="width:1em" />
      </li><li>
          Posición de las expresiones matemáticas. Si la expresión
          !insmath (x+y)/(x^$pw + y^2)
          está
          !if $texalign=1
           demasiado alta respecto a la linea de texto,
           !set wims_ref_class=wims_button
           !href cmd=resume&useropts=$(texsize)0$zoom$font haga clic aquí para bajarla.
          !else
           demasiado baja respecto a la linea de texto,
           !set wims_ref_class=wims_button
           !href cmd=resume&useropts=$(texsize)1$zoom$font haga clic aquí para subirla.
      !endif
    </li>
    </ul>
    !endif
  </div>

  <div id="accessibility">
    <h2>Accesibilidad</h2>

    <p>Puede ajustar el espaciado entre letras y palabras
         !if $useropts=$(texsize)$texalign$(zoom)1
            !set secondary1=wims_button disabled
            !set secondary2=wims_button
          !else
            !set secondary2=wims_button disabled
            !set secondary1=wims_button
          !endif
        !set wims_ref_class=$secondary2
        !href cmd=resume&useropts=$(texsize)$texalign$(zoom)0 Normal

        !set wims_ref_class=$secondary1
        !href cmd=resume&useropts=$(texsize)$texalign$(zoom)1 Lector disléxico
    </p>
    <p>El modo espaciado es especialmente adecuado en el caso de un lector disléxico.</p>
  </div>

</div>
!if $jquery_defined=yes
  !read adm/tabscript useropts
!endif

<p class="spacer">
  !if $wims_user=$empty
   Cuando todo corresponda exactamente con lo que quiera, ponga
    !set wims_ref_class=wims_button
   <a href="$wims_ref_name?lang=$lang&+useropts=$texsize$texalign$zoom$font" title="WIMS">
   este enlace</a>
   en sus Favoritos, para mantener estas preferencias para conexiones futuras.
  !else
   Las preferencias se mantendrán en las conexiones futuras a esta clase.
  !endif
</p>

!tail
