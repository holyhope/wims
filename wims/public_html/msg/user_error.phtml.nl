Status: 450 WIMS User Error
Server: WIMS $wims_version (WWW Interactive Multipurpose Server)
Content-type: text/html; charset=iso-8859-1
Cache-Control: no-cache
Pragma: no-cache

<html><head>
<meta http-equiv=expires content="1 Jan 1990">
<meta HTTP-EQUIV="Pragma" CONTENT="no-cache">
<meta HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
!if exam_ isin $wims_user_error
<style type="text/css"><!--
body {text-align: justify;
padding-left: 3%; padding-right: 3%;}
--></style>
</head><body onload="window.resizeTo(500,200);window.moveTo(250,300);">
<h1 class="wims_center">FOUT</h1>
!goto examerr
!endif
</head><body>
!if threshold iswordof $wims_user_error
 <h1 class="wims_center">We zijn te druk</h1>
 <hr style="width:50%"/>
 Deze WIMS server <span style="color:blue">$httpd_HTTP_HOST</span> 
 is op dit moment belast door een zeer groot aantal aanvragen
 en neemt geen nieuwe opdrachten meer aan.<br />
 Kom later terug, of maak gebruik van een WIMS mirror site. 
 <p>We hopen U spoedig  weer van dienst te kunnen zijn. </p>
 !read mirror.phtml.en
 </body></html>
 !exit
!endif

!if overload iswordof $wims_user_error
 <h1 class="wims_center">SORRY</h1>
 Uw verzoek is geblokkeerd door deze WIMS server: maximum aantal verbindingen is bereikt.
 </body></html>
 !exit
!endif

!if ++++missing_ isin ++++$wims_user_error

 <h1 class="wims_center">Sorry</h1>
 <hr style="width:50%"/><p>
 WIMS heeft het software pakket
 !set miss=!upper $missing_software
 <span class="wims_warning">$miss</span>
 nodig om aan Uw verzoek te voldoen, helaas is dit pakket niet 
 beschikbaar (of niet zichtbaar voor WIMS) op deze server.
 </p>
 <p>
 U kunt een email sturen naar de
 <a href="mailto:$wims_site_manager?subject=$missing_software niet beschikbaar op WIMS">
 website beheerder</a> om deze te informeren over dit probleem, of een
 mirror site kiezen uit de onderstaande tabel.
 </p>
 <a href="wims.cgi">WIMS homepage</a>.
 !read mirror.phtml.en
 </body></html>
 !exit
!endif

!if trapped iswordof $wims_user_error
 <h1 class="wims_center">Stop!</h1><hr />
 Het materiaal op
 <a HREF="http://$httpd_HTTP_HOST">$httpd_HTTP_HOST</a>
 is niet geschikt voor het automatisch downloaden.
 De pagina's worden interactief gegenereerd en zijn ongeschikt voor offline gebruik.
 </body>
 </html>
 !exit 
!endif

<h1 class="wims_center">WIMS error</h1><hr />
<p>
Er is een fout geconstateerd in het verzoek aan deze WIMS server.
</p>

!if module_change iswordof $wims_user_error
 !if $wims_human_access=yes
 Voorkom het gebruik van de 'Terug' knop van de browser op deze Interactieve server.
  <p class="wimscenter">
  !set tit=!module title $module
  !default tit=$module
  !href module=$module $tit
  &nbsp;&nbsp;&nbsp;
  !href $ WIMS home
  !if $httpd_HTTP_REFERER!=$empty
   &nbsp;&nbsp;&nbsp;<a href="$httpd_HTTP_REFERER">Exit WIMS</a>
  !else
   </p>
   <small>Wilt U deze website gewoon willen verlaten, negeer dan deze mededelingen en
   ga door met het klikken van de `Terug' knop.</small>
  !endif
  !exit
 !endif
 U hebt een illegaal verzoek gedaan.
 Gebruik van een download robot om deze site te benaderen is verboden?
 :unblock
 !form new
 <input type="hidden" name="module" value="home" />
 <input type="hidden" name="deblockparm" value="$[randint(10000000)+1000000]" />
 Hebt U per ongeluk op de `Terug' knop van de browser geklikt,
 voer dan s.v.p. het woord "wims" hier:
 <input size="8" name="special_parm" /> en 
 <input type="submit" value="opsturen naar de server" />.
 </form>
 <p>
 Besef goed dat deze WIMS pagina's dynamisch worden gegenereerd en kunnen
 dus <b>alleen</b> online gebruikt worden, via een normale browser.
 Het is zinloos deze pagina's op te halen met een "download robot". 
 </p>

 !if robot_doubt iswordof $wims_user_error
  <small>Besef goed dat hackers voorgoed toegang tot deze
  site kunnen worden ontnomen !</small>
 !endif
 !exit
!endif

!if robot_doubt iswordof $wims_user_error
We blokkeren de toegang tot deze website omdat er het verdacht bestaat 
dat een "download robot" gebruikt wordt om de webpagina's op te halen.

 !goto unblock
!endif

!if allow_violation iswordof $wims_user_error
 U hebt niet de toegangsrechten om de variabele ``$wims_error_data''
 te veranderen met de opdracht ``$cmd''.
  !goto end
!endif

!if bad_command iswordof $wims_user_error
  De opdrachtregel ``$cmd'' is niet toegestaan.
  <p>de toegestane commando's zijn: <pre>
  new, renew, reply, hint, config </pre>
  </p>
!endif

!if bad_host iswordof $wims_user_error
U hebt geprobeerd een sessie op te starten van af een andere computer.
Dit is niet toegestaan vanuit een virtuele klas.  
  <p>
  Helaas geven sommige Internet Service Providers een dynamisch hostadres,
  dat tijdens een verbinding kan veranderen...
  Mocht dit bij U het geval zijn, schrijf dan naar de docent met het verzoek
  de betreffende instellingen te wijzigen.
  </p>
  !goto end
!endif

!if need_https iswordof $wims_user_error
 Uw klas kan alleen via een <b>https</b> sessie worden bereikt.
 !set refname=!replace http:// by https:// in $wims_ref_name
 <a href="$refname?session=$wims_session&module=home&cmd=new">Probeer deze link</a>.
 !exit
!endif

!if bad_insnum iswordof $wims_user_error
 !if $cmd=getfile
 Het gezochte bestand bestaat niet
 !else
 De bestandsnaam is niet geldig.
  
 !endif
 !goto end
!endif

!if cmd_output_too_long iswordof $wims_user_error
Deze berekening heeft het ingestelde maximum ruim overtreden.<br />
Vermoedelijk een te gecompliceerde? berekening...
Vereenvoudig het verzoek.
  !goto end
!endif

!if double_click iswordof $wims_user_error
De server is nog steeds bezig met Uw <b>vorige opdracht</b>.  
<p>
Per ongeluk <b>dubbel geklikt ?</b>, wacht dan  
 <span class="wims_warning">$wims_cpu_limit seconden</span>
 tot de vorige opdracht is afgehandeld en 
 !href cmd=resume klik hier
 om terug te gaan naar het werk.
</p>
<p>
 Mocht U deze website gewoon willen verlaten, negeer dan deze mededelingen en
   ga door met het klikken van de `Terug' knop.
</p>
 !exit
!endif

!if invalid_char_in_query_string iswordof $wims_user_error
  De substitutie ``$wims_error_data'' in de opdracht regel is illegaal.
  !goto end
!endif

!if name_conflict iswordof $wims_user_error
  ``$wims_error_data'' is een gereserveerde naam van WIMS.
  !goto end
!endif

!if no_command iswordof $wims_user_error
  Er is geen opdracht...
  !goto end
!endif

!if no_insnum iswordof $wims_user_error
 !if $cmd=getfile
 Een file aangevraagd zonder passende filenaam ?
 !else
 Een "dynamische invoeging" verzocht zonder een passend nummer ?
 !endif
 !goto end
!endif

!if no_module_name iswordof $wims_user_error
U hebt een nieuwe sessie aangevraagd zonder module naam...vermoedelijk een foutieve link naar een module ?
  !goto end
!endif

!if no_session iswordof $wims_user_error
Het sessienummer is niet aanwezig.  
  !goto end
!endif

!if parm_too_long iswordof $wims_user_error
Uw opdracht regel is veel te groot...niet toegestaan.
  !goto end
!endif

!if string_too_long iswordof $wims_user_error
De definitie van deze variabele valt buiten het toegestane maximum.
  !goto end
!endif

!if too_many_variables iswordof $wims_user_error
Het aantal parameters is groter dan de toegestane limiet.
  !goto end
!endif

!if unmatched_parentheses iswordof $wims_user_error
 We hebben een missend haakje ontdekt :
 U kunt deze fout hier herstellen:
  !form $cmd
  $(name$bad_parentheses) =
  !for i in module,special_parm,worksheet
   !if $($i)!=$empty
    !set value=!translate " to $ $ in $($i)
    <input type="hidden" name="$i" value="$value" />
   !endif
  !next i
  !for i=0 to $user_var_no-1
   !if $i!=$bad_parentheses
    !set value=!translate " to $ $ in $(value$i)
    <input type="hidden" name="$(name$i)" value="$value" />
   !endif
  !next i
  !set value=!translate " to $ $ in $(value$bad_parentheses)
  !set len=!charcnt $value
  !set n=!linecnt $value
  !if $n<=1
   !if $len<55
    !set len=$[$len+3]
   !else
    !set len=59
   !endif
   <input size="$len" name="$(name$bad_parentheses)" value="$value" />
  !else
   !if $n>10
    !set n=10
   !endif
   <p>
   <textarea rows="$n" cols="50" name="$(name$bad_parentheses)">$value</textarea>
   </p>
  !endif
  en vervolgens
  <input type="submit" value="verstuur de gecorrigeerde text" />
  </form><p><hr/><div class="wimscenter">
  !href cmd=resume Laat maar zitten
, or
  !href $ wims home
.</div>
  !exit
!endif
  
!if wrong_module iswordof $wims_user_error
 !set tmp=!translate "!/<>;': to $         $ in $module
 <p>De verzochte module <code>$tmp</code> bestaat niet op deze WIMS site.
 <br /><small><em>kontroleer regelmatig of de links op uw web-pagina / ELO nog up-to-date zijn.</em></small></p>
  !goto end
!endif

!if wrong_session iswordof $wims_user_error
  
Het sessienummer ``$session'' is niet (of niet langer) geldig.
  <a href="wims.cgi">Maak een nieuwe sessie</a>.
  !goto end
!endif  

!if rafale iswordof $wims_user_error
Niet spelen met de oefeningen !
 <p>
 Je kan beter even nadenken en proberen een oplossing te vinden voor 
 deze oefening...in plaats van keer op keer een nieuwe variant aan te vragen.
 </p>
 !href cmd=resume Vergeet het laatste verzoek
.
 !if $wims_user!=$empty and $wims_user!=supervisor
  <p><span class="wims_warning">ATTENTIE</span>! 
  Deze gebruikersfout niet herhalen ! 
  Dit kan aanleiding geven tot zeer slechte scoreresultaten...zelfs als de cijferregistratie gesloten is.
  </p>
 !endif
 !goto end2
!endif

:examerr

!if exam_dep iswordof $wims_user_error
Deze oefening is alleen beschikbaar wanneer je met goed gevolg 

  !if , isin $dep_list
   de opdrachten  $dep_list.
  !else
   de opdracht $dep_list.
  !endif
  hebt afgerond.
  !goto examend
!endif

!if bad_exam iswordof $wims_user_error
Je hebt een illegaal verzoek gedaan binnen een examen sessie.  
  !goto examend
!endif

!if exam_exo_finished iswordof $wims_user_error
Je hebt deze oefening reeds afgerond met een $wims_exo_lastscore als resultaat. 
 Je kunt dit niet nog eens overdoen: dit is een examen (...)
 
  !goto examend
!endif

!if expired_exam iswordof $wims_user_error
Je hebt geen tijd meer over om het examen af te maken.
  :examend
  !set pses=!translate _ to , in $wims_session
  !set pses=!item 1 of $pses
  !set pser=!randint 1,999
  !set wims_opener=window.opener.location='$wims_ref_name?session=$pses.$pser&cmd=reply&job=student';
  <p class="wimscenter">
  <a href=# "window.close();$wims_opener">Sluit dit venster</a>.
  </p>
  !exit
!endif

!if exam_closed iswordof $wims_user_error
Dit "examen" is op dit moment niet meer bereikbaar vanuit je ipadres.<br />
Log opnieuw in en start een nieuw "examen" <br />
Eventueel even navragen bij je docent.
 !goto examend
!endif

!if bad_ident iswordof $wims_user_error
Uw verzoek geeft een "gebruikers identificatie" fout.
Probeer je andermans sessie te benaderen?  
 <p>
 s.v.p.
 <a href="wims.cgi?special_parm=ignorecookie&special_parm2=$[randint(10^8)]">maak een nieuwe sessie</a>.
 </p>
 </body></html>
 !exit
!endif

!if no_access iswordof $wims_user_error
  Door het toegangsbeleid op deze site kan het verzoek niet worden behandeld.<br />
  Onze excuses.
  !goto end
!endif  

!if class_closed iswordof $wims_user_error
  Sorry.
  <p>
  Je docent heeft de virtuele klas is eventjes gesloten.<br />
  Kom later terug, of vraag aan je docent de klas weer te openen...
  </p>
  <div class="wimscenter">
  !href cmd=close&module=home WIMS
  </div>
  </body></html>
  !exit
!endif  

:end
<p>Wanneer je dit bericht ziet na het volgen van een link op een andere
pagina, dan is vermoedelijk deze link corrupt.
In dat geval, gaarne informeer de auteur van deze pagina's.  
Je kan natuurlijk ook de
<a href="mailto:$wims_site_manager?subject=wims.cgi">site manager</a> een email sturen
met een gedetailleerde beschrijving van het geconstateerde ongemak.
</p>

:end2
<hr/><div class="wimscenter">
!href module=home&cmd=new WIMS start pagina
</div>

</body></html>

