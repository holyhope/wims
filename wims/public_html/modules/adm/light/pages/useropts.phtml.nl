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
 <li>
 De grootte van wiskundige symbolen en formules. 
 Gebruik de onderstaande regel voor de instellingen.
  <p>
  Griekse Letters $m_alpha,$m_pi. Wiskundige uitdrukkingen
  !let ins_align=middle
  !instex $$x^3\sin(x)+{\sqrt{x^2+1}\over105}-123.45$$.
  een gemengd voorbeeld
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
  !href cmd=resume&useropts=$ts1$texalign$useropt2 verkleinen
  of
  !href cmd=resume&useropts=$ts2$texalign$useropt2 vergroten
  teneinde ze redelijk te laten (in)passen by de tekst.
  Als de uitdrukking
 
  !insmath (x+y)/(x^2+y^2)
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
</li></ul>

!if $wims_user=$empty
Wanneer alles inorde is , voeg dan  
 <a href="$wims_ref_name?lang=$lang&+useropts=$texsize$texalign$useropt2"
 title="WIMS">deze link</a> toe aan uw bookmarks.
 Bij een volgend bezoek worden deze instellingen automatisch gebruikt.
!else
 Deze instellingen worden bewaard voor uw klas.
!endif

:end
!tail

