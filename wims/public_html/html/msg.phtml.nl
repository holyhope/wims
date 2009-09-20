
!if $wims_error=empty_data
Je het een onvolledig antwoord ingeleverd.<br>
Graag geheel ingevuld opsturen. 

 !exit
!endif

!if $wims_error=double_reply
Je hebt al eens een antwoord ingeleverd bij deze opgave.<br>
Dat antwoord is reeds geanalyseerd en verwerkt in je score.<br>
Herhaalde antwoorden worden genegeerd.
<small> gebruik nooit de "reload" knop van je browser om antwoorden in te leveren!</small> 
 !exit
!endif

!if $wims_error=no_ldap_parameter
De met een asterix gemarkeerde velden moeten worden ingevuld.
Raadpleeg desgewenst eerst de documentatie van uw <tt>ldap</tt> server. 
 !exit
!endif

Soort foutmelding: $wims_error $wims_error_parm.

