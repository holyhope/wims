!set lang_exists=yes

!set name_password_check=Password security check
!set name_listclass=klas,klas,klassen,klas,portaal

!default Cltype=$cltype
!if $Cltype iswordof 2 4
    !if $Cltype=2
	!set name_classe=$(name_listclass[$Cltype+1])
	!set name_sup=van de docent/administateur
	!else
	!set name_classe=$(name_listclass[$Cltype+1])
	!set name_sup=van de administrator
    !endif
    !set name_classes=de $name_classe
    !set name_classess=een $name_classe
    !set name_classesss=van de $name_classe
    !set name_classessss=De $name_classe
!else
    !set name_classe=$(name_listclass[$Cltype+1])
    !set name_classes=de $name_classe
    !set name_classess=een $name_classe
    !set name_classesss=van de $name_classe
    !set name_classessss=De $name_classe
    !set name_sup=van de docent
!endif

!distribute lines Doorgaan\
Herhaal deze procedure.\
Oprichten van een virtuele klas, groep klassen, school of instituut\
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
    !set noright=U hebt geen toestemming hiervoor.
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
Dit is een &eacute;&eacute;nmalige code, en is nergens anders voor te gebruiken !\
Code van $name_classe\
Externe authentificatie CAS (optioneel)\
 into name_help_date,name_help_limit,name_secure,name_optional,name_warning_code,name_code,name_cas

!set name_host=!nosubst Computers van waaruit management mag worden uitgevoerd in de klassen: $name_classe .\
Als hier niets wordt ingevuld, wordt bij elke handeling eerst een goedkeuringsemailtje verstuurd.\
Als hier <span class="tt wims_code_words">all</span> wordt ingevuld, zijn deze handelingen vanaf elke computer toegestaan.

!set name_cas_help=Bij gebruik van externe authentificatie niet het type CAS vergeten.

!set name_cpexempleintro=!nosubst U kunt een kopie van klas <span class="tt wims_code_words">$source_title</span> aanmaken
!set name_choosemode=U moet de kopieerfunctie die klasse te kiezen
!distribute item Integraal,Gedeeltelijk into name_btcpexemplemeth0,name_btcpexemplemeth1

!set name_cpexemplemeth0=De klas is gekopieerd.Het lesmateriaal is gedeactiveerd.
!set name_cpexemplemeth1=De toetsen zijn niet gekopieerd. Het lesmateriaal is gedeactiveerd.U kunt nu het materiaal naar eigen inzicht aanpassen.
!set name_cpexemplecomment=In ieder geval zijn de vervaldata gezet op de einddatum van de nieuwe klas.
!set name_research1=Er zijn veel virtuele klassen op deze site. Voer een sleutelwoord of de naam van de leraar in als zoekterm.
!set name_research2=Er ahv de zoekterm te veel klassen gevonden. Geef een betere zoekterm in.
!set name_searchclass=Zoek een klas
!set name_nofound=Er ahv de zoekterm geen klas gevonden.

!distribute items Open,Gesloten,Vrij,Kopieren,Klik op de te kopieren klas\
into name_free,name_protected,name_disallowed,name_cloning,name_clickclone

!set name_getcloningpwd=!nosubst U gaat een kopie van klas \
<span class="tt wims_code_words">$source_title</span> aanmaken. \
Voer het wachtwoord voor deze handeling in.
!set name_subclass=Sub klas van

!distribute lines Locatie (stad, land)\
Door het invullen gaat u ermee akkoord dat we aangegeven dat WIMS wordt gebruikt in uw stad (met geen andere referentie)\
 into name_location,name_location_help



