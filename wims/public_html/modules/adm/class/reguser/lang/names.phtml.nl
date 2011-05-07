!set lang_exists=yes

!set levelE=lagere school
!set levelH=middelbare school
!set levelU=universiteit

!set lang_fr=français
!set lang_en=english
!set lang_nl=nederlands
!set lang_es=español
!set lang_it=Italiano
!set lang_cn=ÖÐÎÄ
!set lang_ca=Català
!set lang_tw=¤¤¤å(Big5)

!if $cltype iswordof 2 4
   !if $cltype=2
    !set name_classe=een groep klassen
    !set name_sup=van docent/administrator
    !set name_classes= de $name_classe
    !set name_classess= een $name_classe
    !set name_classesss= van $name_classe
    !set name_classessss= De $name_classe
   !else
    !set name_classe=instituut
    !set name_sup=van administrateur
    !set name_classes= de $name_classe
    !set name_classess= een $name_classe
    !set name_classesss= van $name_classe
    !set name_classessss= De $name_classe
    !endif
 !else 
   !set name_classe=klas
   !set name_classes=de klas
   !set name_classess=een klas
   !set name_classesss= van de $name_classe
   !set name_classessss= De $name_classe
   !set name_sup=van docent
 !endif


!distribute lines het portaal\
  Het portaal\
  als <b>docent</b>\
  als <b>deelnemer</b>\
  Ben je een student, kun je jezelf aanmelden \
  bij je klas\
  is door een wachtwoord beschermd\
  aan het werk\
into name_portal,name_Portal,name_asateacher,name_asaparticipant,\
 name_inscription_student,name_inyourclass,name_isprotected,name_gotowork


!distribute lines beschikbare<br>plekken\
jaar\
open,besloten\
Aanmelden voor deelnemers by $name_classess\
alleen voor docenten\
Er zijn geen klassen beschikbaar voor jou. Probeer later nog eens !\
Kies een klas (klik op de naam)\
is beschermd door een wachtwoord en een directe aanmelding is alleen voorbehouden voor <b>docenten</b>.\
Klik op de naam van de student om deze over te zetten.\
Dit wordt gebruikt als naam om later in $classnam in te loggen.\
het wachtwoord moet tussen de 4 en 16 kararakter bevatten (cijfers of letters zonder accenten)\
Om het ingevoerde wachtwoord te controleren, voer het nog een keer in\
Er is geen geldig email adres opgegeven.\
Verplaats de activiteiten.\
Deze deelnemer kan ook nog activiteiten hebben in een andere klas.\
Schrijf naar de docent\
optioneel\
Type account\
Niet vergeten een bookmark van deze link te maken.\
Je kunt nu\
Dit wachtwoord is nodig voor het starten van de inschrijving\
kunt je dit wachtwoord bij je docent aanvragen.\
Hallo\
 into name_remainig, name_year,name_statut,name_title,name_reserved,name_warning1,name_inscription,\
name_warning_protected,name_clickname,name_warning_login,name_passwd_warning,name_passwd_exact,name_passwd_nonvalid,\
name_transfer1,name_otheractivities,name_write_adm,name_optional,name_accounttype,name_bookmark,name_youcan,\
name_writepasswd,name_obtainpasswd,name_hello

!set name_remark1=Bij alle open klassen kan men zich aanmelden zonder beperkingen.\
Bij besloten klassen is echter een wachtwoord vereist om deze aanmeldings procedure te starten.Dit wachtwoord kan worden verkregen bij de docent van de desbetreffende klas of school. 

!set name_access1=!nosubst Als de administrator ($supervisor) je toegang verleent,
!set name_access2=!nosubst Als de docent ($supervisor) je toegang verleent,
!set name_research=Geef een loginnaam of echte naam (of een gedeelte hiervan), om te zoeken naar een deelnemer in $name_classes 
!set name_nofound=!nosubst Er is geen deelnemer met <tt wims="wims_code_words">$search</tt> in echte naam of loginnaam gevonden.

!set name_student=!nosubst $firstn $lastn!
!set name_studentadded=De deelnemer $firstn $lastn is toegevoegd aan $name_classe.
!set name_welcome=!nosubst Je bent nu een geregistreerde deelnemer aan $classname, met loginnaam
!set name_newparticipant=!nosubst Vul het onderstaande formulier in over de nieuwe deelnemer aan $classname.
!set name_inscription2=!nosubst Vul het onderstaande formulier in om jezelf als deelnemer te registreren bij $classname .
!set name_inscription3=!nosubst Je bent bezig met de aanmelding bij $name_classesss $classname, met loginnaam &nbsp;

!set name_warning_direct=Directe aanmelding bij $name_classe is alleen bedoeld voor docenten.\
Ben je een leerling meld je dan aan bij 
  
  