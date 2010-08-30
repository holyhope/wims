 Hyperlinks naar uw $name_classe:<ul>
 <li>De link
  <a href="http://$httpd_HTTP_HOST$httpd_SCRIPT_NAME?lang=nl&module=adm/class/classes&type=authsupervisor&class=$code"
  >http://$httpd_HTTP_HOST$httpd_SCRIPT_NAME?lang=nl&module=adm/class/classes&type=authsupervisor&class=$code</a>
  wijst naar de hoofdpagina van Uw klas $name_classesss ( waar werkbladen,
   repetities, documenten  enz kunnen worden gemaakt). <p>
 <li>De link
  <a href="http://$httpd_HTTP_HOST$httpd_SCRIPT_NAME?lang=nl&module=adm/class/reguser&subclass=yes&class=$code"
  >http://$httpd_HTTP_HOST$httpd_SCRIPT_NAME?lang=nl&module=adm/class/reguser&class=$code</a>
    wijst naar de plek waar leerlingen zichzelf kunnen aanmelden bij Uw klas.<small>(of waar uzelf leerlingen kunt "aanmaken")</small>
   !if $Cltype>=2
    wanneer u klassen hebt aangemaakt van de $name_classe. 
   !endif
  !if $password!=$empty
  (Ze zullen wel het klasseswachtwoord nodig hebben voor de aanmeldingss-procedure)
  !endif
   !if $Cltype>=2
    <p>
  <li>De link
   <a href="http://$httpd_HTTP_HOST$httpd_SCRIPT_NAME?lang=fr&module=adm/class/reguser&class=$code"
  >http://$httpd_HTTP_HOST$httpd_SCRIPT_NAME?lang=fr&module=adm/class/reguser&class=$code</a>
  wijst naar de plek waar docenten zich kunnen aanmelden als leraar van $name_classe .(of waar U deze docenten kunt "aanmaken")
  !if $password!=$empty
    (Ze zullen wel het klassewachtwoord nodig hebben voor de aanmeldings-procedure)
   !endif
  !endif
  <p>
 <li>En de link
  <a href="http://$httpd_HTTP_HOST$httpd_SCRIPT_NAME?lang=nl&module=adm/class/classes&type=authparticipant&class=$code"
  >http://$httpd_HTTP_HOST$httpd_SCRIPT_NAME?lang=nl&module=adm/class/classes&type=authparticipant&class=$code</a>
  wijst geregistreerde leerlingen naar de hoofdpagina van hun klas $name_classesss .<br>
  Uw lesmateriaal staat daar voor hen ter beschikking
  <p>
 </ul>
 <p><b><font color=="red">Belangrijk.</font></b>
 Bookmark deze links voordat U dit venster sluit !!<br>
 Het is ook handig het klassenummer  <font color=green>$code</font> even te noteren.
