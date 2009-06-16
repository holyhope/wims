!if $wims_name_home!=$empty
 !exit
!endif

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
	wims_name_printable,wims_name_renew

!if $wims_class!=$empty
 !distribute items Homepagina van je klas,Voeg $ toe aan het werkblad,\
		Schrijf naar je leraar,Weg uit de klas,\
		De antwoorden zijn reeds verwerkt en de cijfers berekend,\
		Je hebt het behalen van cijfers opgeschort,\
		Jij bent de leraar van deze klas,\
		Bewaar de details van deze oefening,\
		Werkblad Startpagina\
	into wims_name_home,wims_name_add,\
	wims_name_wsup,wims_name_visitor,\
	wims_name_scoreclose,\
	wims_name_scoresuspend,\
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
	into wims_name_n_supervisor,wims_name_n_participant,wims_name_n_example,\
	wims_name_n_authsupervisor,wims_name_n_authparticipant,wims_name_n_E,wims_name_n_H,wims_name_n_U
!endif

!if adm/new isin $module
  !distribute line nieuwe modules\
  verbeterde modules\
  laatste systeem veranderingen\
  RSS\
  into wims_name_mod_new,wims_name_mod_modif,wims_name_mod_sys,wims_name_rss
!endif

!if $wims_user=$empty
  !distribute line Create a class\
  into wims_name_classcreate
!endif

!if adm/modtool isin $module
  !distribute line Test the module\
   Document manager\
   Module content\
   Other files\
   Properties\
   Save\
   Check diff\
   Publish it\
   New Module\
   List of modules\
   Binary files\
   Backup the module\
   Modtool\
   Createxo\
   Quicktool\
   Latex2wims\
   Account properties\
 into wims_name_test,wims_name_docgestion,wims_name_modcontent,wims_name_otherfiles,\
wims_name_properties,wims_name_modsave,wims_name_checkdiff,wims_name_publish,wims_name_createnew,\
wims_name_modlist,wims_name_binfile,wims_name_restore,wims_name_modtool,\
wims_name_createxo,wims_name_quicktool,wims_name_latex2wims,wims_name_account_property
!endif

!distribute line New document\
New  sheet\
New exam\
New class\
New vote\
New exercise\
Class exercises\
into wims_name_add_doc,wims_name_add_sheet,wims_name_add_exam,wims_name_add_class,wims_name_add_vote,\
wims_name_add_exo,wims_name_classexo
