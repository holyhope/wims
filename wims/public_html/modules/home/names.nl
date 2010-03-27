
N_manage	=	WIMS online onderhoud
N_best		=het beste van
N_new		=nieuwste
N_New		=Nieuwste
N_mirror	=mirror websites
N_Mirror	=Mirror websites
N_forum		=forums
N_Forum		=Forums
N_pref		=instellingen
N_Pref		=Instellingen
N_help		=help
N_Help		=Help
N_within	=onder andere
N_clear		=wissen
N_go		=ga naar
N_at		=bij
N_or		=of
N_import	=import
N_Mboard	=Forum
N_hide		=Verbergen

#S_tip		=<b>TIP</b>. Searching for empty string in some categories\
#gives you the list of most popular resources.

V_title		=WWW Interactieve Multipurpose Server
V_cls		=Virtuele klaslokalen
V_stu		=Studenten bereik
V_sup		=Docenten bereik
V_ex		=Demonstratie klassen
V_Quit		=Weg uit de klas
V_Wsup		=Schrijf naar de docent
V_Chpref	=Verander de voorkeurs instellingen 
V_Chpass	=Verander het wachtwoord
V_sh		=Werkblad
V_shs       	=Werkbladen
V_exam		=proefwerk

CR_1		=Maak je eigen
CR_OEF		=Simpele interactieve oefeningen
CR_mod		=Full-power modules

E_doc		=Technische  documentatie
E_src		=Download
E_ref		=Backward links
E_stat		=Gebruiks statistieken
E_comp		=gecompileerd op
E_manager	=Site manager:
E_faq      	=FAQ
E_dochelp  	=Help documenten

RE_found	=!nosubst Gezocht en gevonden $gotcnt $tt
RE_nomatch	=!nosubst Er is op deze server niets passends te vinden.
RE_pop		=!nosubst Hier zijn de $gotcnt meest populaire $tt
RE_pop2		=!nosubst $gotcnt $tt op volgorde van populariteit\
(number $[$list_start+1] - $[$list_start+$gotcnt])
RE_try		=Probeer

U_greet		=!nosubst Hallo, $wims_firstname $wims_lastname !

U_newmsg	=Er zijn $$newmsgcnt nieuwe bericht(en) in het message board.
U_nosheet	=Deze klas heeft (op dit moment)  nog geen werkbladen\
Probeer het later nog eens, als de docent wat werk heeft samengesteld.
U_assign	=Hier staat het materiaal voor jullie klas
U_expired	=verlopen
U_done		=klaar
U_average	=kwaliteit
U_cdt           =Agenda
U_Doc		=Document
U_Sheet		=Werkblad
U_Exam		=Overhoring
U_Vote		=Enquete
U_myscore	=Mijn cijfers
U_examworking	=<b><font color=red>Attentie.</font></b>Je bent nu met een overhoring voor een cijfer bezig.
U_examdouble	=In dit geval mag je niet inloggen via deze netwerk-verbinding (ip-adres)
U_examcont	=Doorgaan met dit proefwerk.
U_oclass	=Andere klassen
U_Back		=Terug
U_account	=Mijn account
U_teacher	=Docent
U_Docstatus 	=niet lezen en niet schrijven,alleen lezen,lezen en schrijven
U_weight    	=weging

U_gotoclass1	=Ga naar een klas als leerling:
U_gotoclass3	=Ga naar een klas als supervisor:
U_gotoclass	=Je klassen :

U_inscription1	=Meld je aan bij een klas:
U_inscription2	=Aanmelden in een andere klas.
U_clickhere	=Klik hier
U_supervise	=om naar een andere klas te gaan als supervisor.
U_creatclass	=Maak een nieuwe klas.


SU_greet	=!nosubst Hallo, $wims_firstname $wims_lastname!<br>\
Welkom op de Onderhouds pagina van uw klas.<br>
SU_Bhome	=Terug naar de supervisor pagina
SU_log		=supervisor login
SU_exp1		=Deze klas is verlopen op:  
SU_exp2		=
SU_Uprep	=Nog niet klaar voor gebruik
SU_Ac		=Actief
SU_Ex		=Verlopen
SU_Hi		=Verlopen+Onzichtbaar
SU_nosheet	=Uw klas heeft nog geen lesmateriaal ter beschikking.
SU_Crone        =Maken.
SU_shlist	=Lesmateriaal van de klas
SU_shno		=Nummer
SU_shti		=Titel
SU_shst		=Status
SU_Howsh	=Hoe voeg ik lesmateriaal toe aan een werkblad? 
SU_classexo	=Oefenmateriaal van de klas (<small>dus uw eigen wims-modules</small>)
SU_Gateway	=Structuur management
SU_Bprogram	=Terug naar het lesprogramma

SE_list		=Leerlingen en cijfers 
SE_part		=Zo zien leerlingen deze pagina
SE_mod		=Bericht van de dag
SE_config	=Configuratie/Onderhoud
SE_secu		=Security management

ADD_1		=Toevoegen:
ADD_doc		=document
ADD_sheet	=werkblad
ADD_exam	=overhoring
ADD_exo		=oefening
ADD_vote	=enquete
ADD_class	=klas
ADD_2		=
ADD_3		=Toevoegen:
ADD_cdt         =Agenda

CL_Names	=Niveaus ,Klassen ,Programma's ,Cursussen ,Interklas cursussen
CL_Name =niveau,klas,programma,cursus,interklas cursus
CL_Test		=Test zone
CL_otherNames=Andere $(CL_Names[2]),$(CL_Names[3]),$(CL_Names[4]) van de klas

ER_expression	=<b>Waarschuwing.</b> <br>\
Zoek je een wiskundige uitdrukking? Dat is op deze plek niet echt logisch.

!if $wims_supertype=4
 U_oclass       =Verwissel van zone
!else
 U_oclass       =Andere klassen
!endif

!set name_deps=Je cijfers voor deze oefeningen moeten verbeterd worden
!set name_dep=Je cijfer voor deze oefening moet verbeterd worden
!set name_dep2=voor dat je deze oefening mag proberen.
!set name_dep3=terug naar werkblad.
