!if $wims_module_log=$empty
 !set wims_module_log=error: $error
!endif

!if not_supervisor=$error
 Nee, alleen de supervisor heeft de rechten om het aanmeldings wachtwoord te veranderen 

 !exit
!endif

!if not_secure=$error
Helaas, alleen verbindingen met computers uit de lijst "secure-hosts" mogen de wachtwoorden wijzigen.<br>
Gebruik de
 !href module=adm/class/config klas configuratie pagina
 om de ip-adressen van deze "secure-hosts" de definieren. 

 !exit
!endif

!if bad_class=$error
Vreemd, maar ik zie nu dat Uw klas niet geldig is ?! 
 !exit
!endif

!if discord iswordof $error
    Wachtwoord verandering afgekeurd: 
    het nieuwe wachtwoord is twee keer verschillend ingevoerd.
 !exit
!endif

!if bad_pass=$error
Uw nieuwe wachtwoord bevat niet toegestane karakters. <p>
Gebruik gewoon letters en of cijfers zonder accenten en spaties als wachtwoord.
 
 !exit
!endif

!if bad_class_password iswordof $error
    Het oude klasse wachtwoord is niet correct!<p>
    Ben jij wel de supervisor van deze klas?
    !exit
!endif

!if bad_user iswordof $error
    Mislukt: er is hier in deze klas geen
     leerling genaamd <tt>$part</tt>.
    !exit
!endif

!if bad_user_password iswordof $error
    Het oude wachtwoord is niet correct!
    <p>
    De verandering van je wachtwoord is dus geweigerd!
    !exit
!endif

!if success iswordof $error
    Je wachtwoord is gewijzigd.
    !exit
!endif

!if fail iswordof $error
    Dit programma kon uw wachtwoord niet registreren.
    Dit moet een interne software fout zijn.
    Neem contact op met de systeembeheerder !
 !exit
!endif

!if too_long iswordof $error
    Fout : het nieuwe wachtwoord is veel te lang.
 !exit
!endif

!if too_short iswordof $error
    Fout : het nieuwe wachtwoord is veel te kort.
 !exit
!endif

!if nothing_to_do iswordof $error
    Ik heb niets veranderd, om dat het nieuwe wachtwoord gelijk is aan het oude.
 !exit
!endif
