!set wims_module_log=error: $error

!if no_subclass iswordof $error
    Bij de huidige instellingen heeft U niet de 
    rechten om subklassen op te richten.
  !set restart=no
 !exit
!endif

!if no_right iswordof $error
    U heeft niet de rechten om klassen op te richten op deze WIMS-server.<br>
    Neem
    !mailurl $wims_site_manager contact op met de site-manager\
    voor meer details over het oprichten van klassen
    op deze server.
 !set restart=no
 !exit
!endif

!if not_manager iswordof $error
    Helaas, maar alleen systeembeheerder (sitemanager) heeft de bevoegdheden
    om een portaal op te richten.
 !exit
!endif

!if getpass iswordof $error
 !if $sendmail!=$empty
  <font size="+1"><center>Het wachtwoord is verstuurd naar: $sendmail.</center></font>
  <p>
 !endif
 !if $regpass!=$empty
  Helaas, Uw wachtwoord is niet juist. Probeer het nog eens.
 !else
  !set cname=!item $cltype+1 of klassen,,een groep klassen,,\
  een portaal
  Het oprichten van $cname op deze server is beschermd met een wachtwoord.
  Vul hieronder het wachtwoord in.
 !endif
 <p>
 !form reply
  <input type="hidden" name="step" value="0">
  Het wachtwoord: <input size="16" name="regpass" type="password">
  <input type="submit" name="Envoyer" value="$wims_name_send">
 </form><p>
 Opmerking. Het wachtwoord voor het oprichten van klassen kan worden verkregen bij de 
 !mailurl $wims_site_manager systeembeheerder\
 van deze WIMS server.
    
 !if $regpassmail!=$empty and $sendmail=$empty
  !form reply
  Geef hier het emailadres waar het wachtwoord naar verstuurd moet worden:
  <input type="text" name="adresse1" value="$adresse1" size="20">
  <input type="hidden" name="step" value="0">
  !let nbaddr=!itemcnt $regpassmail
   !if $nbaddr=1
    <font size="+1">@$regpassmail</font>
    <input type="hidden" name="adresse2" value="$regpassmail">
   !else
    @
    !formselect adresse2 list $regpassmail
   !endif
   &nbsp;
  <input type="submit" value="Recevoir" name="Ontvangen">
    </form>
   !else
    !reset sendmail
   !endif
   !set restart=no
 !exit
!endif

!if getid iswordof $error
 !if $regpass$regid!=$empty
  Helaas, het wachtwoord was niet correct. Probeer nog een keer.
 !else
  Het oprichten van klassen op deze server wordt geregeld door een 
  wachtwoord beschermde aanmeldings procedure.
 !endif
 <p>
 !form reply
  <p><table border="0" cellspacing="5" summary="">
    <tr><td align="right">
    Geef de naam van uw account:</td><td><input size="20" name="regid"></td>
    </tr><tr><td align="right">
    en het bijhorende wachtwoord:</td><td><input size="16" name="regpass" type="password">
    <input type="submit" value="OK"></td>
    </tr></table>
 </form> <p>
 Opmerking: Schrijf naar de systeembeheerder of
 !mailurl $wims_site_manager sitemanager\
 voor een account
 als U klassen op deze server wilt oprichten.
  !set restart=no
 !exit
!endif

!if class_quota=$error
 U had het recht om $r_quota1 klassen op deze server te laten hosten.
 Het quotum is nu bereikt: er is geen plek meer voor nog een extra klas.
 !set restart=no
 !exit
!endif

!if bad_secure=$error
 Uw huidige ipadres staat niet in de door uzelf aangemaakte lijst (<tt>$secure</tt>)
 met veilige ipadressen.Dit is waarschijnlijk een typfoutje.
 <p>
 Lees aandachtig de onderstaande documentatie.
 Als het niet duidelijk is, vul hier dan niets of het woord <tt>all</tt> in.
 Bij dit laatste schakelt WIMS de controle op ipadressen voor uw klassen uit.
 <p>
 <hr>
 <p>
 !read help/hosts.phtml
 !reset secure
 !exit
!endif

!if has_empty=$error
  U hebt voor het oprichten van een klas niet alle vereiste informatie ingevuld.
  Graag aanvullen.
 !exit
!endif

!if too_short=$error
 Het veld ``$(name_$(error_subject))'' lijkt wat te kort.
 !exit
!endif

!if bad_date=$error
 De ingevulde einddatum is niet correct.
 !exit
!endif

!if anti_date=$error
 De verloopdatum van Uw klas ligt voor vandaag...uw klas is dus verlopen <b>voor</b> dat 
  "hij" is opgericht ;-) 
 !exit
!endif

!if bad_level=$error
 Een onjuiste niveau waarde.
 !exit
!endif

!if bad_email=$error
 Uw ingevulde email adres blijkt niet valide te zijn.
 <p>
 Denk eraan dat het oprichten van klassen op deze server alleen kan
 slagen bij een <b>echt werkend email adres<b>.
 !exit
!endif

!if existing=$error
 De klas $classname bestaat volgens mij al op deze server.
 !exit
!endif

!if pass_discord=$error
 Het tweede wachtwoord komt niet overeen met het eerste.<br>
 Probeer het nog eens.
 !exit
!endif

!if bad_pass=$error
 Uw $(name_$(error_subject)) bevat niet toegestane karakters. <p>
  Gebruik een woord met alleen cijfers en/of letters zonder accenten en zonder spaties.
 !exit
!endif

!if bad_code=$error
 U hebt niet de juiste toegangscode ingevuld.<br>
 Hebt U een correct werkend email adres ingevuld?<p>
 Dit voorval wordt opgenomen in de logfiles van deze server.
 !exit
!endif

!if define_fail=$error or abuse=$error
 De server was niet in staat deze nieuwe klas op te nemen in de database.<br>
 Dit moet een interne fout van de software zijn.
 <p>
 Gaarne dit voorval melden bij de
 !mailurl $wims_site_manager systeem beheerder\
Interne serverfout (oprichten van een klas)
 Alvast bedankt!
 !exit
!endif

!if duplicate=$error
 U probeert een bestaande klas opnieuw op te richten...<br>
 Hebt U op de <b>reload</b>-knop van uw browser geklikt?
 In elk geval: Uw klas $classname bestaat gewoon op deze server, 
 en deze poging wordt dus genegeerd.<p>
 !read adm/lang/links.phtml.$modu_lang
 !exit
!endif

