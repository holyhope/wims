!set lang_exists=yes

!set levelid=E1,E2,E3,E4,E5,E6,H1,H2,H3,H4,H5,H6,U1,U2,U3,U4,U5,G,R
!set leveldesc=Lagere school klas 1,Lagere school klas 2,Lagere school klas 3,Lagere school klas 4,Lagere school klas 5,Lagere school klas 6,Middelbare school klas 1,Middelbare school klas 2,Middelbare school klas 3,Middelbare school klas 4,Middelbare school klas 5,Middelbare school klas 6,Universiteit jaar 1,Universiteit jaar 2,Universiteit jaar 3,Universiteit jaar 4,Universiteit jaar 5,Graduate,Research

!set nblevel=19
!! !itemcnt $levelid


!if $Cltype iswordof 2 4
    !if $Cltype=2
	!set name_classe=klassen
	!set name_sup=van de docent/administateur
	!else
	!set name_classe=portaal
	!set name_sup=van de administateur
    !endif
    !set name_classes=de $name_classe
    !set name_classess=een $name_classe
    !set name_classesss=van de $name_classe
    !set name_classessss=De $name_classe
!else
    !set name_classe=klas
    !set name_classes=de $name_classe
    !set name_classess=een $name_classe
    !set name_classesss=van de $name_classe
    !set name_classessss=De $name_classe
    !set name_sup=van de docent
!endif

!distribute lines Doorgaan\
Herhaal deze procedure.\
Oprichten van een virtuele klas, groep klassen, school of  instituut\
Naam van het instituut\
maximaal\
minimaal\
uitsluitend voor experts\
lettertekens\
Terug naar het begin van de aanmelding.\
Kies hier het soort virtuele_ruimte dat U wilt aanmaken\
4 karakters en 16 karakters, cijfers en of letters zonder accenten\
 into name_continue,name_again,title,name_Name_portal,name_atmost,name_atleast,name_expert,\
 name_characters,name_comeback,name_choose,name_warningpass
   
!if $regpolicy=file
    !set noright=U bent hiertoe niet bevoegd.
 !else
    !set noright=alleen de sitemanager is hiertoe bevoegd.
 !endif
 
!set name_regpolicy=!nosubst Het oprichten van $name_classesss zal niet lukken \
als er geen -op dit moment- geldig emailadres wordt ingevoerd.
   
!set name_help1=Met dit wachtwoord kunt u inloggen als $name_sup van $name_classe .\
Zorg ervoor dat u de enige bent die dit wachtwoord kent.

!set name_help2=Het klassewachtwoord $name_classesss wordt gebruikt door studenten om\
de aanmeldings procedure te kunnen starten. Het is dus de bedoeling dat dit wachtwoord wordt gecommuniceerd met \
uw studenten.
  
!set name_help3=Het wachtwoord $name_classesss wordt gebruikt voor docenten om\
zichzelf te registreren; dit wachtwoord moet dus niet voor studenten worden gebruikt.

!distribute lines Dit is de datum waarop er automatisch een backup archief van de klas wordt gemaakt.\
Limiet voor het aantal deelnemers aan uw $name_classe\
Beveiligde toegang\
Optioneel\
Optionele beveiling.<br>Een lijst met ip-adressen van waaruit de administratie voor uw $name_classe kan worden afgehandeld.<br>(alleen computers met deze ip-adressen krijgen administratieve toegang)\
Dit is een &eacute;&eacute;nmalige code, en is nergens anders voor te gebruiken !\
Code van $name_classe\
 into name_help_date,name_help_limit,name_secure,name_optional,name_host,name_warning_code,name_code

!exit
