!!INDEX
!let module_author	=XIAO, Gang
!let module_address	=xiao@unice.fr
!let module_title	=Persoonlijke voorkeurs instellingen WIMS
!let module_description	=definieer de voorkeurs instellingen
!let module_version	=1.00
!let module_wims_version=0.13
!let module_language	=nl
!let module_copyright	=&copy; 1998 (<a href=COPYING>GNU GPL</a>)
!let module_category	=adm
!let module_level	=
!let module_domain	=adm
!let module_keywords	=wims
!!INDEXEND

<hr>
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

Deze pagina geeft toegang tot het fijnafstellen van een WIMS sessies.

<p>
Deze instellingen zijn:
<ul>
!if $wims_user=$empty
 <li>De taal.
  !set wims_language_cnt=!wordcnt $wims_site_languages
  !for l=1 to $wims_language_cnt
   !let la=!word $l of $wims_site_languages
   !href cmd=resume&phtml=useropts.phtml.$la&lang=$la <img src="gifs/$la.gif" alt="$la.gif" border=1>$(lang_name_$la)
   &nbsp;&nbsp;
  !next l
  </li>
!endif
!if $texalign = 2
<li>
    De WIMS server staat op dit moment voor u ingesteld op MathML.<br>
    !insmath x_{1,2} = \frac{-b \pm \sqrt{b^{2} - 4ac}}{2a}
    <br>
    !set zoom=!char 3 of useropts
    !let ts1=!eval $texsize-1
    !let ts2=!eval $texsize+1
    !if $ts1<1
	!let ts1=1
    !endif
    !if $ts2>9
	!let ts2=9
     !endif
    !href cmd=resume&useropts=$ts1$texalign$zoom <b>verkleinen</b>
    &nbsp;&nbsp;of&nbsp;&nbsp;
    !href cmd=resume&useropts=$ts2$texalign$zoom <b>vergroten</b>
    <br>
    !set zoom=0
    !href cmd=resume&useropts=$texsize$texalign$zoom <b>geen inzoomen</b>
    !set zoom=1
    &nbsp;&nbsp;of&nbsp;&nbsp;
    !href cmd=resume&useropts=$texsize$texalign$zoom <b>inzoomen</b>
    <br>
    Als bovenstaande formule niet correct is afgebeeld, gebruik dan
    !set arg=!nospace $texsize 1
   !href cmd=resume&useropts=$arg &nbsp;"wiskunde met gifs"&nbsp;
   in plaats van MathML.
</li>
!else
<li>
    De WIMS server staat op dit moment voor u afgesteld op "wiskunde met gifs".<br>
    Er kan ook gebruik worden gemaakt van 
    !set arg=!nospace $texsize 2
   !href cmd=resume&useropts=$arg MathML&nbsp;
   in plaats van "wiskunde met gifs".&nbsp;<br>
   !! no need to translate tooltip
   Geschikte <a onmouseover="return Tip('<ul><li>FireFox&nbsp;<a target=\'new\' href=\'http://www.mozilla-europe.org/$module_language/\'><img src=\'gifs/mathml/getFireFox.gif\' alt=\'get FireFox\'></a></li><li>Windows<ul><li>Internet Explorer : <a target=\'new\' href=\'http://www.dessci.com/en/products/mathplayer/\'><img src=\'gifs/mathml/dessci_logo.gif\' alt=\'dessci\'> DESSCI MathPlayer plugin</a><li>Opera : <a target=\'new\' href=\'http://xml-maiden.com/userjs/mathml/\'>UserJS MathML plugin</a></ul></li><li>Apple<ul><li></li></ul></li></ul>')">
   <font color="blue">browsers</font></a> voor MathML.
</li>
 <li>
 Hieronder kunnen deze gifplaatjes worden afgesteld.<br>
 De grootte van wiskundige symbolen en formules:<br>
 Gebruik de onderstaande regel voor de instellingen.
  <br>
  Griekse Letters $m_alpha,$m_pi. Wiskundige uitdrukkingen
  !let ins_align=center
  !set pw=2
  !insmath x_{1,2} = \frac{-b \pm \sqrt{b^{$pw} - 4ac}}{2a}
  <br>
  Een gemengd voorbeeld:
  <center>| $m_a + $m_b | $m_le $m_varepsilon + 123.45.</center>
  <p>
  U kunt het formaat van de de wiskundige symbolen
  !let ts1=!eval $texsize-1
  !let ts2=!eval $texsize+1
  !if $ts1<1
    !let ts1=1
  !endif
  !if $ts2>9
    !let ts2=9
  !endif
  !href cmd=resume&useropts=$ts1$texalign$useropt2 <b>verkleinen</b>
  of
  !href cmd=resume&useropts=$ts2$texalign$useropt2 <b>vergroten</b>
  teneinde ze redelijk te laten (in)passen by de tekst.
  Als de uitdrukking
  !insmath \frac{x+y}{x^$pw+y^2}
  te
  !if $texalign=1
  hoog is ten opzichte van de tekstregel,
   !href cmd=resume&useropts=$(texsize)0$useropt2 klik dan hier
   om de positie van het wiskunde symbool (plaatje) te verlagen.
  !else
  laag is ten opzichte van de tekstregel,
   !href cmd=resume&useropts=$(texsize)1$useropt2 klik dan hier
    om de positie van het wiskunde symbool (plaatje) te verhogen. 
  !endif
</li>
!endif
</ul>

!if $wims_user=$empty
Wanneer alles inorde is , voeg dan  
 <a href="$wims_ref_name?lang=$lang&+useropts=$texsize$texalign$useropt2"
 title="WIMS">deze link</a> toe aan uw bookmarks.
 Bij een volgend bezoek worden deze instellingen automatisch gebruikt.
!else
 Deze instellingen worden bewaard voor uw klas.
!endif
<script type="text/javascript" src="scripts/js/wz_tooltip.js"></script>
:end
!tail

