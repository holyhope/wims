!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif

!set lang_fr=français
!set lang_en=English
!set lang_nl=Nederlands
!set lang_es=español
!set lang_ca=Català
!set lang_cn=ÖÐÎÄ
!set lang_it=italiano
!set lang_si=slovensko

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
  Het aanmeldings wachtwoord is verkrijgbaar bij de houder ($supervisor) van dit forum.

!set name_inscription=!nosubst Voor deelname aan $forumname, eerst de volgende informatievelden invullen
 
!set name_password1=Deze loginnaam moet later worden gebruik om in te loggen\
 Kies hiertoe een woord tussen de 4 en 16 lettertekens (cijfers en letters zonder accenten of spaties)

!set name_password2=Kies hiertoe een woord tussen de 4 en 16 lettertekens (cijfers en letters zonder accenten of spaties)
 
!set name_inscription2=!nosubst U bent bezig zich aan te melden bij $forumname,\
 met loginnaam &nbsp;
 !exit

:welcome
 Welkom op $forumname.
  U bent nu een deelnemer aan dit forum, met de loginnaam
  ``<b><font color=green>$login</font></b>''. <p>
  U kunt nu
  !href module=adm/forum/forum&forum=$forum&type=authuser inloggen
  in het forum.
 
!exit
 
:code
 $forumname staat geen anonieme deelnemers toe.
  Het emailadres wordt gebruikt identitificatie
  (om misbruik tegen te gaan)
  <p>
 Om het opgegeven emailadres te controleren,stuurt de server op dit moment
 een (eenmalige) code naar opgegeven emailadres.
 Haal deze mail nu op, en vul de code hieronder in:
!exit
