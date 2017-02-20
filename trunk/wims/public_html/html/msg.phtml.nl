
!if empty_data iswordof $wims_error
Je het een onvolledig antwoord ingeleverd.<br />
Graag geheel ingevuld opsturen. 

 !exit
!endif

!if double_reply iswordof $wims_error
Je hebt al eens een antwoord ingeleverd bij deze opgave.<br />
Dat antwoord is reeds geanalyseerd en verwerkt in je score.<br />
Herhaalde antwoorden worden genegeerd.<br />
Gebruik nooit de "back" knop van je browser !
 !exit
!endif

!if bad_data iswordof $wims_error
    De opgestuurde data / antwoorden kon ik niet verwerken (een "tiep" foutje ?)
 !exit
!endif

!if no_ldap_parameter iswordof $wims_error
De met een asterix gemarkeerde velden moeten worden ingevuld.<br />
Raadpleeg desgewenst eerst de documentatie van uw <span class="tt">ldap</span> server. 
 !exit
!endif

!if bad_class iswordof $wims_error
  Je klas bestaat niet...
 !exit
!endif

!if bad_day iswordof $wims_error or day_dontexist iswordof $wims_error
 de datum is niet geldig.
!exit
!endif


!if not_supervisor iswordof $wims_error
 Bewerking niet toegestaan
 !exit
!endif

!if nouser iswordof $wims_error or bad_user iswordof $wims_error \
  or bad_usercls iswordof $wims_error
  Vreemd , maar ik geloof dat deze student niet bestaat ?!
!exit
!endif

!if insert_fail iswordof $wims_error
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
 Gebruik een woord met alleen cijfers en letters, dus zonder accenten en spaties.
 !exit
!endif

Soort foutmelding&nbsp;: $wims_error $wims_error_parm.
