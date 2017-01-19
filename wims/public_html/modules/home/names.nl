N_manage = WIMS online onderhoud
wims_name_mirror = mirror websites
wims_name_Mirror = Mirror websites
wims_name_pref = Instellingen

N_within = onder andere
N_clear = wissen
N_go = ga naar
name_importfromtest=teaching materials from Test Zone.
N_at = bij
N_hide = Verbergen
name_allexampleclass=Alle openbare klassen

V_title = WWW Interactieve Multipurpose Server
V_cls = Virtuele klaslokalen
wims_name_n_participant = Studenten bereik
wims_name_n_supervisor = Docenten bereik
wims_name_mail = Schrijf naar de docent
wims_name_pref = Instellingen
wims_name_ref = Bezoekers
wims_name_stat = Serverstatistieken

CR_1 = Maak je eigen
CR_OEF = Simpele interactieve oefeningen
CR_Docs=Tutorials
CR_mod = Full-power modules
CR_sequence=U hebt gekozen om het lesmateriaal aan te bieden in een speciale volgorde.

E_comp = gecompileerd op
E_manager = Site manager:

RE_prev  = !nosubst Vorige resultaten
RE_next  = !nosubst Volgende resultaten
RE_found = !nosubst Gezocht en gevonden $Gotcnt $tt
RE_found2= De resultaten zijn op type activiteit gerangschikt.\
 Klik op de corresponderende link.
RE_warning_more= Er zijn meerdere zoekresultaten gevonden.\
(de limiet is $gotlim2 per soort activiteit).Het zoekresultaat kan verder worden beperkt\
door het toevoegen van andere zoektermen.

RE_nomatch = !nosubst Er is op deze server niets passends te vinden.
RE_pop = !nosubst Hier zijn de $gotcnt meest populaire $tt
RE_pop2 = !nosubst $gotcnt $tt op volgorde van populariteit\
(number $[$list_start+1] - $[$list_start+$gotcnt])
RE_try = Probeer
RE_noKeyword    = Er is geen zoekterm ingevuld.

U_greet = !nosubst Welkom, $wims_firstname $wims_lastname !

U_newmsg = Er zijn $$newmsgcnt nieuwe bericht(en) in het message board.
U_nosheet = Deze klas heeft (op dit moment)  nog geen werkbladen\
Probeer het later nog eens, als de docent wat werk heeft samengesteld.
U_assign = Hier staat het materiaal voor jullie klas
U_expired = verlopen
U_done = klaar
U_average = kwaliteit

U_examworking = Je bent nu met een overhoring voor een cijfer bezig.
U_examdouble = In dit geval mag je niet inloggen via deze netwerk verbinding (ip-adres)
U_examcont = Doorgaan met dit proefwerk.
wims_name_U_oclass = Andere klassen
wims_name_U_account = Mijn account
wims_name_coeff = weging

U_gotoclass1 = Ga naar een klas als leerling:
U_gotoclass3 = Ga naar een klas als supervisor:
U_gotoclass0 = Uw klassen :
U_gotoclass11 = $U_gotoclass1
U_gotoclass31 = $U_gotoclass3
U_gotoclass01 = U_gotoclass0

U_inscription1 = Meld je aan bij een klas:
U_inscription2 = Aanmelden in een andere klas.
U_clickhere = Klik hier
U_supervise = Klik hier om naar een andere klas te gaan als supervisor.
U_creatclass = Maak een nieuwe klas.
name_gotosupervise=Neem contact op met de server administrator om ook andere klassen als supervisor te bezoeken.

SU_greet = !nosubst Welkom, $wims_firstname $wims_lastname!<br/>\
Welkom op de Onderhouds pagina van uw klas.<br/>
SU_Bhome = Terug naar de supervisor pagina
SU_log = supervisor login
SU_exp1 = Deze klas is verlopen op:
SU_exp2 =

SU_nosheet = Uw klas heeft nog geen lesmateriaal ter beschikking.
SU_shlist = Lesmateriaal van de klas
wims_name_SU_Gateway = Structuur management
SU_Bprogram = Terug naar het lesprogramma
SU_nopartconnected=Er is op dit moment geen student ingelogd
SU_numpartconnected=!nosubst Er zijn op dit moment $wims_numpartconnected student(en) ingelogd
U_supconnected=Uw docent is ingelogd.

wims_name_SE_list = Leerlingen en cijfers (old)
wims_name_n_participant = Zo zien leerlingen deze pagina

wims_name_SE_mod = Bericht van de dag
wims_name_SE_config = Configuratie&amp;Onderhoud
wims_name_SE_secu = Security management

ADD_1 = Toevoegen:
ADD_doc = document
ADD_sheet = werkblad
ADD_exam = overhoring
ADD_exo = oefening
ADD_vote = enquete
ADD_class = klas
ADD_2 =
ADD_3 = Toevoegen:
ADD_cdt = Agenda

CL_Names = Niveaus ,Klassen ,Programma&rsquo;s ,Cursussen ,Interklas cursussen
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
!set name_dep3 = terug naar het werkblad.
