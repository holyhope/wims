!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif

!set lang_fr=français
!set lang_en=English
!set lang_nl=Nederlands

!distribute lines Aanmelden bij het forum\
   Helaas, deze site bevat geen forums op dit moment. Probeer het later nog maar eens!\
   Aanmelding is beschermd door een wachtwoord.\
   Schrijf naar de eigenaar/houder\
   niet verplicht\
   Hallo\
   U hebt geen emailadres ingevuld.\
   Uw emailadres\
   Om de juistheid van Uw wachtwoord te kontroleren, graag nog een keer invullen:\
   Lijst van alle forums.\
into title,name_noforum,name_passw,name_write_owner,name_optional,name_hello,\
  name_email1,name_email2,name_email3,name_forumlist

!set name_obtain_passw=!nosubst <b>Opmerking</b>.\
  Het aanmeldings wachtwoord is verkrijgbaar bij de eigenaar ($supervisor) van dit forum.

!set name_inscription=!nosubst Om deel te nemen aan $forumname, vul dan de volgende informatievelden in
 
!set name_password1=Deze login naam gebruikt U later om in te loggen in het message board\
 Kies hiertoe een woord tussen de 4 en 16 karakters (cijfers en letters zonder accenten of spaties)

!set name_password2=Kies hiertoe een woord tussen de 4 en 16 karakters (cijfers en letters zonder accenten of spaties)
 
!set name_inscription2=!nosubst U bent zich nu aan het aanmelden voor $forumname,\
 met de login naam &nbsp;
 !exit

:welcome
 Welkom op $forumname.
  U bent nu een deelnemer aan dit forum, met de login naam
  ``<b><font color=green>$login</font></b>''. <p>
  U kunt nu
  !href module=adm/forum/forum&forum=$forum&type=authuser inloggen
  in het forum.
 
!exit
 
:code
 $forumname staat geen anonieme deelnemers toe.
  Uw emailadres wordt gebruikt voor Uw identiteit
  (om misbruik tegen te gaan)
  <p>
 Om het opgegeven emailadres te controleren,stuurt de server op dit moment
 een (eenmalige) code naar opgegeven emailadres.
 Haal deze mail nu op, en vul de code hieronder in:
!exit