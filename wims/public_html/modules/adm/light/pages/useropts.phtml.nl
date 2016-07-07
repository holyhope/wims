!!INDEX
!let module_translator=
!let module_translator_address=
!let module_title=Setup your preferences for WIMS
!let module_description=define preferences for wims
!let module_language=nl
!!INDEXEND

!let tip='<ul><li>FireFox&nbsp;<a target=\'new\' href=\'http://www.mozilla-europe.org/$module_language/\'><img src=\'gifs/mathml/getFireFox.gif\' alt=\'get FireFox\'/></a></li><li>Google Chrome&nbsp;<a target=\'new\' href=\'https://chrome.google.com/webstore/detail/mathjax-for-chrome/elbbpgnifnallkilnkofjcgjeallfcfa\'> MathJax Extension </a><li>Windows<ul><li>Internet Explorer: <a target=\'new\' href=\'http://www.dessci.com/en/products/mathplayer/\'><img src=\'gifs/mathml/dessci_logo.gif\' alt=\'dessci\'/> DESSCI MathPlayer plugin</a><li>Opera: <a target=\'new\' href=\'http://xml-maiden.com/userjs/mathml/\'>UserJS MathML plugin</a></ul></li><li>Safari</li></ul>'

!read proc/useropts.proc

!header
<script type="text/javascript" src="scripts/js/wz_tooltip.js"></script>
<p>Op deze pagina kan het uiterlijk van de WIMS sessie worden aangepast.</p>

<div id="widget_useropts">
  <ul>
    <li><a href="#formula">Wiskundige formules</a></li>
    !if $wims_user=$empty
      <li><a href="#language_selector">De taal</a></li>
    !endif
    <!--li><a href="#accessibility">Accessibility</a></li-->
  </ul>

  !if $wims_user=$empty
  <div id="language_selector">
    <h2>De taal</h2>
    !read themes/_widgets/language_selector.phtml
  </div>
  !endif

  <div id="formula">
    <h2>Wiskundige formules:</h2>

    !if $texalign=2
      De server staat afgesteld op <b>MathML</b>.
      <p class="wimscenter">
        !insmath x_{1,2} = \frac{-b \pm \sqrt{b^{2} - 4 a c}}{2a}
      </p>
      Als de bovenstaande formule niet correct is afgebeeld, kan er gebruik worden gemaakt van een andere
      <a onmouseover="return Tip($tip)"><span class="wims_emph">browser</span></a>
      of gebruik de server in de afstelling "wiskunde met plaatjes".

      <p class="wimscenter">
        !set wims_ref_class=wims_button
        !href cmd=resume&useropts=$arg Gebruik Wiskunde met plaatjes
      </p>

      !let ts1=!eval $texsize-1
      !let ts2=!eval $texsize+1
      !if $ts1<1
        !let ts1=1
      !endif
      !if $ts2>9
        !let ts2=9
      !endif
      Stel de grootte van de formules af.
      !set wims_ref_class=wims_button
      !href cmd=resume&useropts=$ts1$texalign <img src="gifs/doc/dgauche.gif" width="20px" />

      &nbsp;
      !set wims_ref_class=wims_button
      !href cmd=resume&useropts=$default Standaard

      &nbsp;
      !set wims_ref_class=wims_button
      !href cmd=resume&useropts=$ts2$texalign <img src="gifs/doc/ddroite.gif" width="20px" />
      <br/>
      !set zoom=1
      Gebruik ook inzoomen per muisklik.
      !set wims_ref_class=wims_button
      !href cmd=resume&useropts=$texsize$texalign$zoom $wims_name_yes
      !set zoom=0
      &nbsp;
      !set wims_ref_class=wims_button
      !href cmd=resume&useropts=$texsize$texalign$zoom $wims_name_no
    !else
      De server staat afgesteld op "Wiskunde met plaatjes".
      Bij gebruik van een geschikte
      <a onmouseover="return Tip($tip)"><font color="blue">browser</font></a>, kan de server ook MathML leveren.
      <p class="wimscenter">
        !set arg=!nospace $texsize 2
        !set wims_ref_class=wims_button
        !href cmd=resume&useropts=$arg Gebruik MathML
      </p>

      <hr/>Grootte van wiskundige symbolen en formules.
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
        Griekse Letters $m_alpha, $m_pi. Wiskundige uitdrukking
        !let ins_align=middle
        !! we need to force dynamic insertion
        !set pw=2
        !insmath x_{1,2} = \frac{-b \pm \sqrt{b^{$pw} - 4ac}}{2a}
        <br />
        Gemengde formule
      </p>
      <p class="wimscenter">| $m_a + $m_b | $m_le $m_varepsilon + 123.45.</p>

      <hr/>
      Positie van de formules. Als de uitdrukking
      !insmath (x+y)/(x^$pw + y^2)
      te
      !if $texalign=1
        hoog staat tov de tekst
        !href cmd=resume&useropts=$(texsize)0$useropt2 klik hier
        om het plaatje te verlagen.
      !else
        te laag staat tov de tekst
        !href cmd=resume&useropts=$(texsize)1$useropt2 klik hier
        om het plaatje te verhogen
      !endif
      !set zoom=$empty
    !endif
  </div>

</div>
!if $jquery_defined=yes
  !read adm/tabscript useropts
!endif

<p>
  !if $wims_user=$empty
    Als alles correct is afgesteld, maak dan van
    <a href="$wims_ref_name?lang=$lang&+useropts=$texsize$texalign$useropt2$zoom"
       title="WIMS">deze link</a>
    een bookmark , zodat ook bij een volgend bezoek aan deze server deze instellingen worden gebruikt.
  !else
    Deze instellingen worden bewaard voor toekomstige inlogsessies in deze klas.
  !endif
</p>

!tail
