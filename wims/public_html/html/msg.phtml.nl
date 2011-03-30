
!if $wims_error=empty_data
Je het een onvolledig antwoord ingeleverd.<br>
Graag geheel ingevuld opsturen. 

 !exit
!endif

!if $wims_error=double_reply
Je hebt al eens een antwoord ingeleverd bij deze opgave.<br>
Dat antwoord is reeds geanalyseerd en verwerkt in je score.<br>
Herhaalde antwoorden worden genegeerd.
Gebruik nooit de "reload &amp; back" knop van je browser !
 !exit
!endif

!if $wims_error=no_ldap_parameter
De met een asterix gemarkeerde velden moeten worden ingevuld.
Raadpleeg desgewenst eerst de documentatie van uw <tt>ldap</tt> server. 
 !exit
!endif

!if $wims_error=no_ldap_parameter
 Vous devez remplir les champs marqués d'un astérisque. Consultez pour cela 
 le gestionnaire de votre annuaire ldap. 
 !exit
!endif

!if $wims_error=bad_class
  Je klas bestaat niet...
 !exit
!endif


!if $wims_error iswordof bad_day day_dontexist
 de datum is niet geldig.
!exit
!endif


!if $wims_error=not_supervisor
 Bewerking niet toegestaan
 !exit
!endif

!if $wims_error iswordof nouser bad_user bad_usercls
  Vreemd , maar ik geloof dat deze student niet bestaat ?!
!exit
!endif

!if $wims_error=insert_fail
 Door een fout in de software -maar meestal niet- kan ik Uw werk niet opnemen
in de database. Controleer even de data ! 
 !exit
!endif

!if bad_pass iswordof $wims_error
 Wachtwoord is niet goed: het mag alleen letters en cijfers bevatten, 
 en de lengte moet tussen de 4 en 16 lettertekens zijn.
 En het herhaald ingetypte wachtwoord moet natuurlijk wel gelijk zijn aan de eerste keer!
 Probeer het nog eens.
 !exit
!endif

!if bad_auth iswordof $wims_error
 Het inloggen is mislukt. Probeer opnieuw.
 !exit
!endif

!if bad_login=$wims_error
 Uw login-naam bevat niet toegestane karakters.
 <p>
 Gebruik een woord met alleen cijfers en letters , dus zonder accenten en spaties.
 !exit
!endif

Soort foutmelding&nbsp;: $wims_error $wims_error_parm.
