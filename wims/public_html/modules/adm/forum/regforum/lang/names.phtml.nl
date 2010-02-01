!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif

!set name_title=naam van het forum
!set name_description=omschrijving van het forum
!set name_supervisor=naam van de eigenaar
!set name_email=emailadres
!set name_password=aanmeldings wachtwoord van het forum
!set name_passsup=wachtwoord van de eigenaar

!set forumname=<b><font color=green>$title</font></b>

!set months=Jan,Feb,Maart,April,Mei,Juni,Juli,Aug,Sept,Okt,Nov,Dec

!distribute lines Oprichten van een forum\
  Herstart deze procedure.\
  Volledige naam van de eigenaar (U dus)\
  Dit forum kan alleen worden opgezet als er een werkend emailadres wordt invult.\
  Wachtwoord van de eigenaar\
  Kies het gebruikers wachtwoord voor het forum\
  tussen 4 en 16 lettertekens, cijfers of letters zonder accenten\
  Versturen\
  Hallo\
  Wachtwoord van de eigenaar\
  Wachtwoord voor deelnemers\
  Geheime code\
  lettertekens\
into title_title,name_restart,name_name_owner,name_warning1,name_choosepass1,name_choosepass2,\
  name_instruction,name_continue,name_hello,name_ownerpass,name_forumpass,name_code,\
  name_characters
  
!set name_name_forum=!nosubst Naam van het forum (maximaal $titlelim lettertekens)

!set name_help1=Dit wachtwoord geeft toegang tot configuratie van het forum,\
  U bent dus de enige die het wachtwoord mag kennen.

!set name_help2=Dit wachtwoord kunt U bekend maken aan alle deelnemers van dit forum.


!set name_warning= Wie een forum opricht op deze WIMS server, is ook verantwoordelijk voor het onderhoud ervan.
  <p>Om een eigen forum op te richten, vul dan het onderstaande formulier in.


!set name_warning2=<b>Opmarking</b> Deze code is &eacute;&eacute;nmalig. En kan hierna niet meer worden gebruikt !
 
!exit

:step1
U bent bezig met het oprichten van een forum $forumname op 
WIMS server
 $httpd_HTTP_HOST.
 <p>
 Is er iets niet correct is aan bovenstaande info dan svp
 !href module=$module&cmd=reply&step=0 corrigeren. 
 <p>Om de juistheid van de wachtwoorden te controleren, 
 graag hieronder nog een keer intypen:
 !exit
 
:step2
U hebt nu alleen nog de geheime code nodig om het oprichten van
 uw eigen forum op (WIMS $http_HTTP_HOST) af te kunnen ronden.
 <p>
 Deze code is net verstuurd naar het opgegeven email adres:
 ``<tt>$email</tt>''. 
  en kopieer de verstuurde code in het onderstaande veld
 !exit
 
 :step3
 Het forum $forumname is aangemaakt.
 Gefeliciteerd en veel plezier !<p>
 U kunt uw forum altijd
 !href module=adm/forum/forum hier bereiken
.
!exit