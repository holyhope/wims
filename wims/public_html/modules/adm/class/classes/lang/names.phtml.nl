!set lang_exists=yes
!if $class_type iswordof 2 4
   !if $class_type=2
    !set name_classe=groep klassen
    !set name_sup=administrator
    !set name_classes= de $name_classe
    !set name_classesss= van de $name_classe
    !set name_classessss= De $name_classe
   !else
    !set name_classe=instituut
    !set name_sup=administrator
    !set name_classes= het $name_classe
    !set name_classesss= van het $name_classe
    !set name_classessss= Het $name_classe
   !endif
   !set name_classess= een $name_classe
 !else
   !set name_classe=klas
   !set name_classes=de $name_classe
   !set name_classess=een $name_classe
   !set name_classesss= van de $name_classe
   !set name_classessss= De $name_classe
   !set name_sup=docent
 !endif
 !if $splevel iswordof 1 2 3
   !set sousclasses=!item $splevel of klas,cursus
   !set Name_level= !item $splevel of Niveau,Klas,Cursus
   !set Name_levels= !item $splevel of Niveaus,Klassen,Cursussen
   !set sousclasses_else=!item $splevel of &bnsp;of een klas,&nbsp;of een cursus
   !set name_level_else= !item $splevel of een niveau,een klas,een cursus
 !else
   !set sousclasses=sub-klassen
   !set sousclasses_else=een klas of een instituut
 !endif

!set CL_Name=Niveau,Klas,Programma,Cursus,Cursus,Portaal,Test Zone
!set Name_program=Programma
!set name_program=programma
!set name_portalandgroup=Instituten en groepen klassen
!set name_independantclass=Onafhankelijke klassen

!distribute items Aanmelden,Anoniem,openbaar,besloten,Jaar,\
Nieuwe deelnemer,aanmelden,Inloggen,Up\
into name_register,name_anonymous,name_open,name_protected,name_year,\
name_new_participant,name_registered,name_connexion,name_up

!distribute line U heeft geen account in een andere klas.\
Zoek mijn klassen\
Geen andere klassen aanwezig.\
Geen klas gevonden.\
U kunt direct overstappen naar&nbsp;\
into name_noaccount,name_searchclass,name_noavailable,name_nofound,name_direct

!let classification=Lagere school,Middelbare school,Lyceum,Universiteit,Anders

!set name_text1=Kies uit de tabel uw klas\
<p>Nog niet aangemeld? klik dan op <tt>$name_register</tt>\
 (als de status heet <tt>$name_protected</tt> , is er een wachtwoord vereist voor de aanmeldings procedure.\
 Dit wachtwoord is verkrijgbaar bij de docent of administrator.)\
<p>Klik op <tt>$wims_name_Enter</tt> om in te loggen. 

!set name_text2=Om over te stappen naar  $name_level_else $sousclasses_else, kies \
uit de onderstaande tabel.
!set name_text3=Of kies $name_level_else $sousclasses_else uit de onderstaande tabel.

!set name_language=Er is geen nederlandstalige klas aanwezig op deze server.\
Wilt u een klas in een andere taal ?
!set name_language2=Op deze server zijn geen enkele nederlandstalige klassen  geinstalleerd.

!set name_warning=<b>Fout</b>. Je probeert in te loggen in een klas die niet bestaat. \
  Probeer het nog eens een keer...

!set name_enter=!nosubst Om in de klas <b><font color="green">$class_description</font></b> van\
<b><font color="green">$class_institution</font></b> als een\
geregistreerde deelnemer te komen, vul dan hier je login naam en wachtwoord in.

!set name_entersup=!nosubst Om in $name_classes <b><font color="green">$class_description</font></b> van\
<b><font color="green">$class_institution</font></b> als de\
<em>$name_sup</em> in te loggen, voer hier het $name_sup wachtwoord in.
 
 !set name_research1= Er zijn zeer veel virtuele klassen geinstalleerd op deze server. \
   Om Uw klas te vinden, voer een zoekterm in.
 
!set name_research2= Er zijn te veel klassen gevonden met uw zoekterm. Geef een duidelijkere zoekterm.

!set name_supervisor_text= Klik op de klas (of school of instituut) van Uw keuze.<br>\
     <small> Als U op <tt>$name_enter</tt> klikt, bent U reeds aangemeld als docent of supervisor.<br>\
     Klik op <tt>$name_register</tt> als U docent wilt worden in een school of instituut.<br>\
     Deze aanmelding is dus <b>alleen</b> voor <tt>docenten</tt>.

!if $type=example
   !set name_example1=Er zijn geen openbare klassen geinstalleerd op deze server.
   !set name_example2=Er zijn geen nederlandstalige klassen geinstalleerd op deze server, \
   maar er zijn wel $clcnt engelstalige klassen.
   !set name_example3=!nosubst Er zijn $clcnt nederlandstalige openbare demonstratie klassen geinstalleerd.
   !set name_example4=U kunt ook een eigen klas maken om te zien hoe een docenten account er echt uitziet
   !set name_instruction=<ul>\
<li>Klik op <tt class="d">$name_anonymous</tt> om in te loggen anls anonieme student (deelnemer).\
<li><p>Klik op <tt class="d">$name_registered</tt> op in te loggen als reeds geregistreerde student.\
(Je moet jezelf natuurlijk dan wel eerder hebben aangemeld; wat niet wil zeggen\
dat registreren in "demonstratie klaslokalen" een blijvende registratie is. Op gezette tijden\
  verwijdert de server deze "bezoekers accounts")\
<li><p>Klik op <tt class="d">$name_register</tt> voor het aanmelden in een openbare klas.\
</ul>

  !set name_sheet_example=U kunt ook de gebruikte werkbladen importeren [en modificeren] in uw eigen klas.
!endif
 