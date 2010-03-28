Status: 450 WIMS User Error
Server: WIMS $wims_version (WWW Interactive Multipurpose Server)
Content-type: text/html; charset=iso-8859-1
Cache-Control: no-cache
Pragma: no-cache

<HTML><HEAD>
<meta http-equiv=expires content="1 Jan 1990">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
!if exam_ isin $wims_user_error
<STYLE TYPE="text/css"><!--
body {text-align: justify;
padding-left: 3%; padding-right: 3%;}
--></STYLE>
</HEAD><BODY onload="window.resizeTo(500,200);window.moveTo(250,300);">
<H1 align=center>FOUT</H1>
!goto examerr
!endif
</HEAD><BODY>

!if threshold iswordof $wims_user_error
 <hr width=1>
 <H1 align=center>We zijn te druk</H1>
 <hr width=50%><p>
 Deze WIMS server <font color=blue>$httpd_HTTP_HOST</font> 
 is op dit moment belast door een zeer groot aantal aanvragen,
 en neemt geen nieuwe opdrachten meer aan.
 Kom later terug, of maak gebruik van een WIMS mirror site 
 <p>We hopen U spoedig  weer van dienst te kunnen zijn. 
 !read mirror.phtml.en
 </body></html>
 !exit
!endif

!if overload iswordof $wims_user_error
 <hr width=1>
 <H1 align=center>SORRY</H1>
 Uw verzoek is geblokkeerd door deze WIMS server: maximum aantal verbindingen is bereikt.
 </body></html>
 !exit
!endif

!if ++++missing_ isin ++++$wims_user_error
 <hr width=1>
 <H1 align=center>Sorry</H1>
 <hr width=50%><p>
 WIMS heeft het software pakket
 !set miss=!upper $missing_software
 <b><font color=red>$miss</font></b>
 nodig om aan Uw verzoek te voldoen, helaas is dit pakket niet 
 beschikbaar (of niet zichtbaar voor WIMS)  op deze server.
 <p>
 U kunt een email sturen naar de
 <a href="mailto:$wims_site_manager?subject=$missing_software niet beschikbaar op WIMS">
 website beheerder</a> om deze te informeren over dit probleem, of een
 mirror site kiezen uit de onderstaande tabel.
 <a href=wims.cgi>WIMS homepage</a>.
 !read mirror.phtml.en
 </body></html>
 !exit
!endif

!if trapped iswordof $wims_user_error
 <H1 align=center>Stop!</H1><hr>
 Het materiaal op
 <A HREF="http://$httpd_HTTP_HOST">$httpd_HTTP_HOST</a>
 is niet geschikt voor het automaitsch downloaden.
 De pagina's worden interactief gegenereerd, en zijn ongeschikt voor offline gebruik
 </body>
 </html>
 !exit 
!endif

<H1 align=center>WIMS error</H1><hr>

Er is een fout geconstateerd in Uw verzoek aan deze WIMS server.<p>

!if module_change iswordof $wims_user_error
 !if $wims_human_access=yes
 Voorkom het gebruik van de 'Terug' knop van Uw browser op deze Interactieve server.
  <p><center>
  !set tit=!module title $module
  !default tit=$module
  !href module=$module $tit
  &nbsp;&nbsp;&nbsp;
  !href $ WIMS home
  !if $httpd_HTTP_REFERER!=$empty
   &nbsp;&nbsp;&nbsp;<a href="$httpd_HTTP_REFERER">Exit WIMS</a>
  !else
   </center><p>
   <small>Mocht U deze website gewoon willen verlaten, negeer dan deze mededelingen en
   ga door met het klikken van de `Terug' knop.</small>
  !endif
  !exit
 !endif
 U hebt een illegaal verzoek gedaan.
 Gebruikt U soms een geautomatiseerd download programma om deze site te benaderen?
 :unblock
 !form new
 <input type=hidden name=module value="home">
 <input type=hidden name=deblockparm value="$[randint(10000000)+1000000]">
 Hebt U per ongeluk op de `Terug' knop van de browser geklikt,
 typ dan s.v.p. het woord "wims" hier:
 <input size=8 name=special_parm> en dan
 <input type=submit value="opsturen naar de server">.</form>
 <p>
 Besef goed dat deze WIMS pagina's dynamisch worden gegenereerd, en kunnen
 dus <b>alleen</b> online gebruikt worden, via een normale browser.
 Het is zinloos deze pagina's op te halen met een "download robot". 
 

 !if robot_doubt iswordof $wims_user_error
  <small>Besef goed dat hackers voorgoed toegang tot deze
  site wordt ontnomen !</small>
 !endif
 !exit
!endif

!if robot_doubt iswordof $wims_user_error
We blokkeren de toegang to deze website voor U, omdat er het verdacht bestaat 
dat U een "download robot" gebruikt op deze pagina's op te halen.

 !goto unblock
!endif

!if allow_violation iswordof $wims_user_error
 U hebt niet de toegangsrechten om de variabele  ``$wims_error_data''
 te veranderen met de opdracht ``$cmd''.
  !goto end
!endif

!if bad_command iswordof $wims_user_error
  De opdrachtregel ``$cmd'' is niet toegestaan.
  <p>de toegestane commando's zijn: <pre>
  new, renew, reply, hint, config </pre>
!endif

!if bad_host iswordof $wims_user_error
U hebt geprobeerd een sessie op te starten van af een andere computer.
Dit is niet toegestaan in Uw virtuele klas.  
  <p>
  Helaas geven sommige Internet Service Providers een dynamisch hostadres,
  dat tijdens een verbindging kan veranderen...
  Mocht dit bij U het geval zijn, schrijf dan naar uw supervisor met het verzoek
  de betreffende instellingen te wijzigen  
  !goto end
!endif

!if need_https iswordof $wims_user_error
 Uw klas kan alleen via een <b>https</b> sessie worden bereikt.
 !set refname=!replace http:// by https:// in $wims_ref_name
 <a href="$refname?session=$wims_session&module=home&cmd=new">Probeer dit</a>.
 !exit
!endif

!if bad_insnum iswordof $wims_user_error
 !if $cmd=getfile
 Het gezochte bestand bestaat niet
 !else
 De bestandsnaam voor dit dynamisch bestand is niet geldig.
  
 !endif
 !goto end
!endif

!if cmd_output_too_long iswordof $wims_user_error
Het resultaat van de door U verzocht berekening heeft het ingestelde maximum
ruim overtreden.<br>
U hebt vermoedelijk om een te gecompliceerde? berekening verzocht.
Vereenvoudig Uw verzoek, s.v.p.
 
  !goto end
!endif

!if double_click iswordof $wims_user_error
De server is nog steeds bezig met Uw <b>vorige opdracht</b>.  
<p>
Hebt U per ongeluk <b>dubbel geklikt ?</b>, wacht dan  
 <font color=red><b>$wims_cpu_limit seconden</b></font>
 tot de vorige opdracht is afgehandeld, en dan
 !href cmd=resume klik hier
 om terug te gaan naar uw werk.
 <p>
 Mocht U deze website gewoon willen verlaten, negeer dan deze mededelingen en
   ga door met het klikken van de `Terug' knop.
  
 !exit
!endif

!if invalid_char_in_query_string iswordof $wims_user_error
  De substitutie ``$wims_error_data'' in de opdracht regel is illegaal.
  !goto end
!endif

!if name_conflict iswordof $wims_user_error
  ``$wims_error_data'' is een  gereserveerde naam van WIMS.
  !goto end
!endif

!if no_command iswordof $wims_user_error
  Er is geen opdracht...
  !goto end
!endif

!if no_insnum iswordof $wims_user_error
 !if $cmd=getfile
 U hebt een file aangevraag zonder passende filenaam.
 !else
 U hebt een "dynamische invoeging" verzocht zonder een passend nummer hiervoor.
  
 !endif
 !goto end
!endif

!if no_module_name iswordof $wims_user_error
U hebt een nieuwe sessie aangevraagd zonder module naam.  
  !goto end
!endif

!if no_session iswordof $wims_user_error
Het sessienummer is niet aanwezig.  
  !goto end
!endif

!if parm_too_long iswordof $wims_user_error
Uw opdracht regel is veel te groot...<br>
Dit is -om beveiligings redenen- niet toegestaan.
  !goto end
!endif

!if string_too_long iswordof $wims_user_error
De definitie van deze variabele val buiten het toegestane maximum.
  !goto end
!endif

!if too_many_variables iswordof $wims_user_error
Het aantal parameters is groter dan het op deze WIMS site toegestane limiet
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
    <input type=hidden name=$i value="$value">
   !endif
  !next i
  !for i=0 to $user_var_no-1
   !if $i!=$bad_parentheses
    !set value=!translate " to $ $ in $(value$i)
    <input type=hidden name=$(name$i) value="$value">
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
   <input size=$len name=$(name$bad_parentheses) value="$value"><p>
  !else
   !if $n>10
    !set n=10
   !endif
   <textarea rows=$n cols=50 name=$(name$bad_parentheses)>$value</textarea>
   <p>
  !endif
  en vervolgens
  <input type=submit value="verstuur de gecorrigeerde text.">
  </form><p><hr><p><center>
  !href cmd=resume Laat maar zitten
, or
  !href $ wims home
.</center>
  !exit
!endif
  
!if wrong_module iswordof $wims_user_error
 De verzochte module ``$module'' bestaat niet op deze WIMS site.
 <br><small><em>kontroleer regelmatig of de links op uw web-pagina / ELO nog up-to-date zijn.</em></small>
  !goto end
!endif

!if wrong_session iswordof $wims_user_error
  
Het sessienummer ``$session'' is niet (of niet langer) geldig.
  <a href="wims.cgi">Maak een nieuwe Sessie</a>.
  !goto end
!endif  

!if rafale iswordof $wims_user_error
Niet spelen met de oefeningen !
 <p>
 Je kan beter even nadenken en proberen een oplossing te vinden voor 
 deze oefening...in plaats van keer op keer een nieuwe variant aan te vragen.
 
 !href cmd=resume Vergeet het laatste verzoek
.
 !goto end2
!endif

:examerr

!if exam_dep iswordof $wims_user_error
Deze oefening is alleen beschikbaar wanneer je met goed gevolg hebt 

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
 Je kunt dit niet nog eens overdoen: dit is een examen ...
 
  !goto examend
!endif

!if expired_exam iswordof $wims_user_error
Je hebt geen tijd meer over om het examen af te maken.
  :examend
  <p><center>
  <a href=# onclick=window.close();>Sluit dit venster</a>.
  </center><p>
  !exit
!endif

!if exam_closed iswordof $wims_user_error
Dit "examen" is op dit moment niet meer bereikbaar voor Uw ipadres.<br>
Log opnieuw in, en start een nieuw "examen" <br>
Doe eventueel even navraag bij je docent.
 !goto examend
!endif

!if bad_ident iswordof $wims_user_error
Uw verzoek geeft een "gebruikers identificatie" fout.
Probeer je een andermans sessie te benaderen?  
 <p>
 s.v.p.
 <a href=wims.cgi?special_parm=ignorecookie&special_parm2=$[randint(10^8)]>maak een nieuwe sessie</a>.
 </body></html>
 !exit
!endif

!if no_access iswordof $wims_user_error
  Door het toegangsbeleid op deze site kan uw verzoek niet worden behandeld.<br>
  Onze excuses.
  !goto end
!endif
     
!if class_closed iswordof $wims_user_error
  Sorry.
  <p>
  Je docent heeft deze virtuele klas is eventjes gesloten.<br>
  Kom later terug, of vraag aan je docent de klas weer te openen...
  <p><center>
  !href cmd=close&module=home WIMS
  </center>
  </body></html>
  !exit
!endif  

:end
<p>Wanneer je dit bericht ziet na het volgen van een link op een andere
pagina, dan is vermoedelijk deze link corrupt.
In dat geval, gaarne informeer de auteur van deze pagina's.  
Je kan natuurlijk ook de
<a href="mailto:$wims_site_manager?subject=wims.cgi">site manager</a> een email sturen
met een gedetailleerde beschrijving van het geconstateerde ongemak

:end2
<hr><p>
<center>
!href module=home&cmd=new WIMS start pagina
</center>

</body></html>

