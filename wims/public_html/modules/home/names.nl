N_manage = WIMS online onderhoud
wims_name_mod_new = Nieuwste
wims_name_mirror = mirror websites
wims_name_Mirror = Mirror websites
wims_name_pref = Instellingen

N_within = onder andere
N_clear = wissen
N_go = ga naar
N_at = bij
N_hide = Verbergen

V_title = WWW Interactieve Multipurpose Server
V_cls = Virtuele klaslokalen
wims_name_n_participant = Studenten bereik
wims_name_n_supervisor = Docenten bereik
wims_name_mail = Schrijf naar de docent
wims_name_pref = Verander de voorkeurs instellingen 
wims_name_ref = Backward links
wims_name_stat = Gebruiks statistieken

CR_1 = Maak je eigen
CR_OEF = Simpele interactieve oefeningen
CR_mod = Full-power modules

E_comp = gecompileerd op
E_manager = Site manager:
wims_name_faq = FAQ
E_dochelp = Help documenten

RE_found = !nosubst Gezocht en gevonden $gotcnt $tt
RE_nomatch = !nosubst Er is op deze server niets passends te vinden.
RE_pop = !nosubst Hier zijn de $gotcnt meest populaire $tt
RE_pop2 = !nosubst $gotcnt $tt op volgorde van populariteit\
(number $[$list_start+1] - $[$list_start+$gotcnt])
RE_try = Probeer

U_greet = !nosubst Hallo, $wims_firstname $wims_lastname !

U_newmsg = Er zijn $$newmsgcnt nieuwe bericht(en) in het message board.
U_nosheet = Deze klas heeft (op dit moment)  nog geen werkbladen\
Probeer het later nog eens, als de docent wat werk heeft samengesteld.
U_assign = Hier staat het materiaal voor jullie klas
U_expired = verlopen
U_done = klaar
U_average = kwaliteit

U_examworking = <b><font color = red>Attentie.</font></b>Je bent nu met een overhoring voor een cijfer bezig.
U_examdouble = In dit geval mag je niet inloggen via deze netwerk-verbinding (ip-adres)
U_examcont = Doorgaan met dit proefwerk.
wims_name_U_oclass = Andere klassen

wims_name_U_account = Mijn account

wims_name_coeff = weging

U_gotoclass1 = Ga naar een klas als leerling:
U_gotoclass3 = Ga naar een klas als supervisor:
U_gotoclass = Je klassen :

U_inscription1 = Meld je aan bij een klas:
U_inscription2 = Aanmelden in een andere klas.
U_clickhere = Klik hier
U_supervise = om naar een andere klas te gaan als supervisor.
U_creatclass = Maak een nieuwe klas.


SU_greet = !nosubst Hallo, $wims_firstname $wims_lastname!<br>\
Welkom op de Onderhouds pagina van uw klas.<br>
SU_Bhome = Terug naar de supervisor pagina
SU_log = supervisor login
SU_exp1 = Deze klas is verlopen op:  
SU_exp2 = 

SU_nosheet = Uw klas heeft nog geen lesmateriaal ter beschikking.
SU_shlist = Lesmateriaal van de klas
SU_Gateway = Structuur management
SU_Bprogram = Terug naar het lesprogramma

wims_name_SE_list = Leerlingen en cijfers 
wims_name_SE_part = Zo zien leerlingen deze pagina
wims_name_SE_mod = Bericht van de dag
wims_name_SE_config = Configuratie/Onderhoud
wims_name_SE_secu = Security management

ADD_1 = Toevoegen:
ADD_doc = document
ADD_sheet = werkblad
ADD_exam = overhoring
ADD_exo = oefening
ADD_vote = enquete
ADD_class = klas
ADD_2 = ADD_3 = Toevoegen:
ADD_cdt = Agenda

CL_Names = Niveaus ,Klassen ,Programma's ,Cursussen ,Interklas cursussen
CL_Name = niveau,klas,programma,cursus,interklas cursus
CL_Test = Test zone
CL_otherNames = Andere $(CL_Names[2]),$(CL_Names[3]),$(CL_Names[4]) van de klas

!if $wims_supertype = 4
 wims_name_U_oclass = Verwissel van zone
!else
 wims_name_U_oclass = Andere klassen
!endif

!set name_deps = Je cijfers voor deze oefeningen moeten verbeterd worden
!set name_dep = Je cijfer voor deze oefening moet verbeterd worden
!set name_dep2 = voor dat je deze oefening mag proberen.
!set name_dep3 = terug naar werkblad.
