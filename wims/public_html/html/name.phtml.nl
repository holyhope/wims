!if $wims_name_home!=$empty
 !exit
!endif

!! **** Default Names ***
!distribute items Zoeken,\
		Werk,Terug naar het Werk,\
		WIMS Home,Intro/Config,Help,Wat is dit,\
		Introductie,\
		Sluit dit venster,Terug,\
		Website manager,Auteur van deze pagina,Auteurs van deze pagina's,\
		Vertaald door,Exit,\
		WIMS Help,Referentie,\
		Message board,Forums,\
		Werkblad,Hulpmiddelen,\
		Kopieer naar Modtool,\
		Print,\
		Importeer in uw eigen klas,\
		Printbare versie,\
		Opnieuw,\
		ga naar,\
		Refresh,\
		Save,\
		yes,\
		no,\
	into wims_name_search,\
	wims_name_work,wims_name_resume,\
	wims_name_home,wims_name_intro,wims_name_help,wims_name_about,\
	wims_name_titleintro,\
	wims_name_back,wims_name_back2,\
	wims_name_manager,wims_name_author,wims_name_authors,\
	wims_name_translatedby,wims_name_exit,\
	wims_name_whelp,wims_name_ref,wims_name_forum,wims_name_forums,\
	wims_name_sheet,wims_name_tools,\
	wims_name_modify,wims_name_print,wims_name_import,\
	wims_name_printable,wims_name_renew,wims_name_testgo,\
	wims_name_refresh,wims_name_tosave,\
	wims_name_yes,wims_name_no

!! **** Permalink Names *** 
!distribute items deze module, deze oefening,\
	Installeer,op uw site,\
	verberg deze opties,\
	Permanente link, Embeddable player,\
	knip en plak, deze link, deze code, of, in een email,\
	voor, enkel,\
	deze configuratie,\
	Naam\
    into wims_name_this_module, wims_name_this_exercice,\
    wims_name_display,wims_name_on_your_site,\
    wims_name_mask_this,\
    wims_name_permalink,wims_name_embeddable,\
    wims_name_copy_and_paste,wims_name_the_link,wims_name_the_code,wims_name_or,wims_name_in_a_mail,\
    wims_name_for,wims_name_only,\
    wims_name_this_config

!distribute items Naam,\
	Module Informatie,\
	Adres,\
	Link voor bookmark,\
	Omschrijving,\
	Versie,\
	Vereiste <br>WIMS versie,\
	Taal,\
	Schrijver,\
	Vertaler,\
	Dit is een module van,\
	WWW Interactive Multipurpose Server,\
	Copyright\
    into wims_name_name,\
    wims_name_module_infos,\
    wims_name_Address,\
    wims_name_Link_for_bookmark,\
    wims_name_Description,\
    wims_name_Version,\
    wims_name_Required_WIMS_version,\
    wims_name_Language,\
    wims_name_Author,\
    wims_name_Translator,\
    wims_name_This_is_a_module,\
    wims_name_WIMS_subtitle,\
    wims_name_Copyright
	


!! **** Class Relative Names ***
!if $wims_class!=$empty
 !distribute items Homepagina van je klas,Voeg $ toe aan het werkblad,\
		Schrijf naar je leraar,Uitloggen,\
		De antwoorden zijn reeds verwerkt en de cijfers berekend,\
		Je hebt het behalen van cijfers opgeschort,\
		Open score registration,Close score registration,\
		U bent de leraar van deze klas,\
		Bewaar de details van deze oefening,\
		Werkblad startpagina\
	into wims_name_class_home,wims_name_add,\
	wims_name_wsup,wims_name_visitor,\
	wims_name_scoreclose,\
	wims_name_scoresuspend,\
	wims_name_scorereopen,wims_name_scoreclose2,\
	wims_name_syou,\
	wims_name_exolog,\
	wims_name_sheetmanagement

 !set wims_name_score=!nosubst Je hebt voor deze opdracht $[$wims_homeref_got] punten gehaald uit maximaal\
	$[$wims_homeref_req] punten. <br>Gemiddelde score \
	$[$wims_homeref_mean]/10.
 !set wims_name_you=jij bent <b>$wims_firstname $wims_lastname</b>, en hoort bij
 !if _exam isin $session
  !distribute items Andere opgaven uit deze overhoring,\
	resterende tijd voor deze overhoring:,\
	zo gauw deze pagina is geladen\
	into wims_name_back,wims_name_examremain,wims_name_whenloaded
 !endif
 !if _check isin $session
  !let wims_page_name=Page
 !endif
 !set wims_name_sequence=!defof sequence_Title in wimshome/log/classes/$wims_class/seq/.def
 !default wims_name_sequence=Sequence
!endif

!if adm/class isin $module
 !distribute line Docenten zone\
	Leerlingen zone\
	Demonstratie klassen\
	Inloggen voor docenten\
	Inloggen voor deelnemers\
	lagere school\
	middelbare school\
	universiteit\
	List of classes\
    List of classes and portals\
    Individual class\
    Superclasse\
    Portal\
	into wims_name_n_supervisor,wims_name_n_participant,wims_name_n_example,\
	wims_name_n_authsupervisor,wims_name_n_authparticipant,wims_name_n_E,wims_name_n_H,wims_name_n_U,\
	wims_name_classlist,wims_name_portal_list,\
	wims_name_create_class,wims_name_create_superclass,wims_name_create_portal
!endif

!if adm/new isin $module
  !distribute line nieuwe modules\
  verbeterde modules\
  laatste systeem veranderingen\
  RSS nieuwe modules\
  RSS verbeterde modules\
  into wims_name_mod_new,wims_name_mod_modif,wims_name_mod_sys,wims_name_rss_new,wims_name_rss_modif
!endif

!if $wims_user=$empty
  !distribute line Create a class\
  into wims_name_classcreate
!endif

!if adm/modtool isin $module or adm/createxo isin $module or $wims_user!=$empty
  !distribute line Test de module\
   Document manager\
   Inhoud module\
   Andere bestanden\
   Eigenschappen\
   Opslaan\
   Conroleer verschil\
   Publiceren\
   Nieuwe module\
   Lijst van modules\
   Binary bestanden\
   Backup van de module\
   Eigenschappen van account\
   Script tester\
   OEF Documentation \
   Script Library\
   Answer types\
   Doc technic\
   Terug naar de bestanden lijst\
   edfile Bewerken\
 into wims_name_test,wims_name_docgestion,wims_name_modcontent,wims_name_otherfiles,\
wims_name_properties,wims_name_modsave,wims_name_checkdiff,wims_name_publish,wims_name_createnew,\
wims_name_modlist,wims_name_binfile,wims_name_restore,\
wims_name_account_property,\
wims_name_scripttest,wims_name_docoef,wims_name_docslib,wims_name_docanswer,wims_name_doctec,\
wims_name_back3,wims_name_edfile,wims_name_change,wims_name_up,wims_name_erase

!distribute line Back to the exercise creation\
   Model list\
   Prepared models\
into wims_name_backcreatexo,wims_name_modellist,wims_name_model

!distribute line Test\
Modify the source\
Save in the development module\
Save into your class\
Save as a new exercise\
Send an image file\
Replace the old one\
Erase the exercise\
into wims_name_testexo,wims_name_exomodify,\
wims_name_putmodtool,wims_name_putclass,wims_name_newversion,\
wims_name_downloadbinary,wims_name_replace,wims_name_exoerase

!endif

!distribute line Nieuw document\
Nieuw werkblad\
Nieuwe overhoring\
Nieuwe klas\
Nieuwe enquete\
Nieuw oefening\
Oefeningen van deze klas\
into wims_name_add_doc,wims_name_add_sheet,wims_name_add_exam,wims_name_add_class,wims_name_add_vote,\
wims_name_add_exo,wims_name_classexo

!!! for documents

!distribute item WIMS,Class,Docs,Up,Prev,Next,Hist.,Reload,\
	Interactive version,Printable version,\
	Back to doc,Help,About,\
	Bestand invoegen,\
	Back to the file list,\
	Hoofdpagina van dit document\
	into wims_name_doch_wims,wims_name_doch_class,wims_name_doch_docs,wims_name_doch_up,\
	wims_name_doch_prev,wims_name_doch_next,wims_name_doch_hist,wims_name_doch_reload,\
	wims_name_doch_interactive,wims_name_doch_printable,\
	wims_name_doch_back,wims_name_doch_help,wims_name_doch_about,\
	wims_name_doch_upload,wims_name_doch_filelist,wims_name_doch_main

!! for sequence et document

!distribute line Document\
hiden,visible\
Title\
Organize\
Insert in the class\
Create a new document\
Write on a try document\
Status\
into wims_name_doc,wims_name_status,wims_name_title,wims_name_reorder,wims_name_adddoc,\
wims_name_createdoc,wims_name_doctry,wims_name_Status 


 !distribute line Add a date\
   Add file\
   Add work\
   Configure\
  into wims_name_adddate,wims_name_addfile,wims_name_addtodo,wims_name_config


!set wims_name_supervisor=supervisor
!set wims_name_teacher=Leraren accounts
!set wims_name_addteacher=Nieuwe leraar
!set wims_name_modteacher=Leraar eigenschappen
!set wims_name_delteacher=Verwijder een leraar
!set wims_name_student=Leerlingen accounts
!set wims_name_addstudent=Nieuwe leerling
!set wims_name_modstudent=Leerling eigenschappen
!set wims_name_delstudent=Verwijder een leerling
!set wims_name_backstruct=Backup van de gehele structuur
!set wims_name_portal=portaal
!set wims_name_level=niveau
!set wims_name_class=klas
!set wims_name_program=programma
!set wims_name_course=cursus
!set wims_name_icourse=interklas cursus

!if config isin $module
 !distribute line Hoofdpagina klassen onderhoud\
 Instituut administratie\
 backup en herstel\
into wims_name_config, wims_name_struct,wims_name_save

!endif
!set wims_name_backgateway=Gestion of

!distribute line Add a course\
Add a interclass course\
Add a class\
Add a program\
Add a level\
login de gestion\
Zone change\
into wims_name_addcourse,wims_name_addicourse,wims_name_addclass,wims_name_addprog,wims_name_addlevel,\
wims_name_login,wims_name_chzone

!distribute line Statistiques d'activité\
Activités globales des participants\
Changer les niveaux de sévérité\
Notes manuellement attribuées\
spreadsheet data\
into wims_name_class_stat,wims_name_activity,wims_name_formula,wims_name_grades,\
wims_name_csv

!if adm/class/userlist isin $module
!distribute line Lijst van alle leerlingen \
Cijfers \
Sluit / be&euml;indig deze tentamen sessie\
details van het werk\
Schors deze student\
Ruwe gegevens\
verander het wachtwoord\
Verwerkte data\
Livret de compétences\
into wims_name_part_list,wims_name_scores,wims_name_partexamclose,wims_name_workdetail,\
wims_name_delprep,wims_name_rawdata,wims_name_passwd,wims_name_getraw,wims_name_livret
!endif

!if adm/manage isin $module
  !distribute line Other maintenance tasks\
  into wims_name_sitegestion
!endif

!if adm/class/livret isin $module
 !if $wims_user=supervisor
  !let tmp=Gestion des participants et notes
 !else 
  !let tmp=Mes notes
 !endif
 !distribute line Nouvelle compétence\
Configurer\
$tmp\
Livret de la classe\
  into wims_name_add_competence,wims_name_config,wims_name_go_userlist,wims_name_cls_livret
!endif

!distribute lines Modtool\
   Createxo\
   Quicktool\
   Latex2wims\
   into wims_name_modtool,wims_name_createxo,wims_name_quicktool,wims_name_latex2wims
   
