!!INDEX
!let module_author=XIAO, Gang
!let module_address=xiao@unice.fr
!let module_title=Setup your preferences for WIMS
!let module_description=define preferences for wims
!let module_version=1.00
!let module_wims_version=0.13
!let module_language=nl
!let module_copyright=&copy; 1998 (<a href="COPYING">GNU GPL</a>)
!let module_category=adm
!let module_level=
!let module_domain=adm
!let module_keywords=wims
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
Op deze pagina kan het uiterlijk van de WIMS sessie worden aangepast.
<ul>
!if $wims_user=$empty
 <li>De taal :
  !set wims_language_cnt=!wordcnt $wims_site_languages
  !for l=1 to $wims_language_cnt
   !let la=!word $l of $wims_site_languages
   !href cmd=resume&phtml=useropts.phtml.$la&lang=$la <img src="gifs/$la.gif" alt="$la.gif" />$(lang_name_$la)
   &nbsp;&nbsp;
  !next l
  </li>
!endif

<li>
Wiskundige formules:<br/>

!if $texalign=2
    De server staat afgesteld op <b>MathML</b>.
    <p class="wimscenter">
    !insmath x_{1,2} = \frac{-b \pm \sqrt{b^{2} - 4 a c}}{2a}
    </p>
    Als de bovenstaande formule niet correct is afgebeeld, kan er gebruik worden gemaakt van een andere
    <a onmouseover="return Tip($tip)"><span class="wims_emph">browser</span>
    </a> 
    of gebruik de server in de afstelling "wiskunde met plaatjes".
!set wims_ref_class=wims_button
<p class="wimscenter">
   !href cmd=resume&useropts=$arg Gebruik Wiskunde met plaatjes
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
    Stel de grootte van de formules af.
!set wims_ref_class=wims_button
    !href cmd=resume&useropts=$ts1$texalign <img src="gifs/doc/dgauche.gif" width="20px"/>
    &nbsp;
!set wims_ref_class=wims_button
    !href cmd=resume&useropts=$default Standaard
    &nbsp;
!set wims_ref_class=wims_button
    !href cmd=resume&useropts=$ts2$texalign <img src="gifs/doc/ddroite.gif" width="20px"/>
 </li><li>
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

</li><li>
Grootte van wiskundige symbolen en formules.
!let ts1=!eval $texsize-1
!let ts2=!eval $texsize+1
!if $ts1<1
    !let ts1=1
  !endif
!if $ts2>9
    !let ts2=9
!endif
!set wims_ref_class=wims_button
    !href cmd=resume&useropts=$ts1$texalign$useropt2 <img src="gifs/doc/dgauche.gif" width="20px"/>
    &nbsp;
!set wims_ref_class=wims_button
    !href cmd=resume&useropts=$ts2$texalign$useropt2 <img src="gifs/doc/ddroite.gif" width="20px"/>
  <p>
  Griekse Letters $m_alpha, $m_pi. Wiskundige uitdrukking 
  !let ins_align=middle
!! we need to force dynamic insertion
  !set pw=2
  !insmath x_{1,2} = \frac{-b \pm \sqrt{b^{$pw} - 4ac}}{2a}
  <br/>
  Gemengde formule
  </p><p class="wimscenter">| $m_a + $m_b | $m_le $m_varepsilon + 123.45.</p>
</li><li>
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
</li>
</ul>

!if $wims_user=$empty
Als alles correct is afgesteld, maak dan van 
 <a href="$wims_ref_name?lang=$lang&+useropts=$texsize$texalign$useropt2$zoom"
 title="WIMS">deze link</a>
  een bookmark , zodat ook bij een volgend bezoek aan deze server deze instellingen worden gebruikt.
!else
    Deze instellingen worden bewaard voor toekomstige inlogsessies in deze klas.
!endif

:end
!tail

