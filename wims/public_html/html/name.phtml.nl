!!!!WARNING If you have to put "into" in the translation, write into$  ...

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
		Ga naar,\
		Vernieuwen,\
		Opslaan,\
		Ja,\
		Nee,\
		Download,\
		Sturen,\
		Details,\
		Laat zien,\
		Bewerken,\
		Attentie,\
		Gefeliciteerd,\
		of,\
		Uitleg,\
		Oefening,\
		Werkblad,\
		Account,\
		Inloggen,\
		Cijfers,\
		Mijn cijfers,\
		Proefwerk,\
		Browse,\
		Terug naar het menu,\
		Eind datum,\
 into wims_name_search,\
	wims_name_work,wims_name_resume,\
	wims_name_home,wims_name_intro,wims_name_help,wims_name_about,\
	wims_name_titleintro,\
	wims_name_back,wims_name_back2,\
	wims_name_manager,wims_name_author,wims_name_authors,\
	wims_name_translatedby,wims_name_exit,\
	wims_name_whelp,wims_name_reference,wims_name_forum,wims_name_forums,\
	wims_name_sheet,wims_name_tools,\
	wims_name_modify,wims_name_print,wims_name_import,\
	wims_name_printable,wims_name_renew,wims_name_testgo,\
	wims_name_refresh,wims_name_tosave,\
	wims_name_yes,wims_name_no,wims_name_download,wims_name_send,wims_name_detail,\
	wims_name_Show,wims_name_Edit,wims_name_warning,wims_name_Congratulations,wims_name_or,\
	wims_name_Explanations,wims_name_Exercise,wims_name_Sheet,wims_name_Account,wims_name_Enter,\
	wims_name_Score1,wims_name_myscore,wims_name_Examen,wims_name_browse,wims_name_menuback,\
	wims_name_expiration

!! **** Permalink Names ***
!distribute items deze module, deze oefening,\
	Installeer,op uw site,\
	Verberg deze opties,\
	Permanente link, embed,\
	knip en plak, deze link, deze code, of, in een email,\
	voor, enkel,\
	deze configuratie,\
    into wims_name_this_module, wims_name_this_exercice,\
    wims_name_display,wims_name_on_your_site,\
    wims_name_mask_this,\
    wims_name_permalink,wims_name_embeddable,\
    wims_name_copy_and_paste,wims_name_the_link,wims_name_the_code,wims_name_or,wims_name_in_a_mail,\
    wims_name_for,wims_name_only,\
    wims_name_this_config

!! the following sentences can be changed according to language if needed
!set wims_name_display1=!nosubst $wims_name_display $wims_name_this_module $wims_name_on_your_site
!set wims_name_display2=!nosubst $wims_name_copy_and_paste $wims_name_the_link $wims_name_on_your_site $wims_name_or $wims_name_in_a_mail
!set wims_name_display3=!nosubst $wims_name_copy_and_paste $wims_name_the_code $wims_name_on_your_site
!set wims_name_permalink1=!nosubst $wims_name_permalink $wims_name_for $wims_name_this_module

!! **** Module About Names ***
!distribute items Naam,\
	    Info over iconen,\
	    Module Informatie,\
	    Informatie over deze oefening,\
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
	    Zoektermen,\
	    Emailadres vertaler,\
	    Emailadres auteur,\
	    Onderwerp,\
	    Soort,\
	    Niveau(s),\
	    Scorings mechanisme<br><small>(oefening / ontspanning)</small>,\
	    Hulp software<br>vereist,\
	    Server tijd,\
	    Data module,\
	into wims_name_name,\
	wims_name_iconabout,\
        wims_name_module_infos,\
        wims_name_exo_infos,\
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
	wims_name_Copyright,wims_name_Keywords,\
	wims_name_tr_email,wims_name_auth_email,\
	wims_name_Domain,wims_name_Type,wims_name_Levels,\
	wims_name_Scoring,\
	wims_name_require,wims_name_server_time,wims_name_datamodule


!! **** Class Relative Names ***
!if $wims_class!=$empty
 !distribute items Homepagina van je klas,Toevoegen aan werkblad,\
		Schrijf naar je docent,Uitloggen,\
		De antwoorden zijn reeds verwerkt en de cijfers berekend,\
		Je hebt het behalen van cijfers opgeschort,\
		Open cijfer registratie,Sluit cijfer registratie,\
		U bent docent van deze klas,\
		Bewaar de details van deze oefening,\
		Werkblad startpagina\
		Lesmateriaal in werkvolgorde,\
	into wims_name_class_home,wims_name_add,\
	wims_name_wsup,wims_name_visitor,\
	wims_name_scoreclose,\
	wims_name_scoresuspend,\
	wims_name_scorereopen,wims_name_scoreclose2,\
	wims_name_syou,\
	wims_name_exolog,\
	wims_name_sheetmanagement,\
	wims_name_add_sequence
 !set wims_name_chseries=!nosubst Sla de veranderingen aan de series oefeningen $(special_parm4[2]) uit werkblad $(special_parm4[1]) op. 
 !set wims_name_score=!nosubst Je hebt voor deze opdracht $[$wims_homeref_got] punten gehaald uit maximaal\
	$[$wims_homeref_req] punten. <br>Gemiddelde score \
	$[$wims_homeref_mean]/10.
 !set wims_name_you=jij bent <b>$wims_firstname $wims_lastname</b>, en hoort bij
 !if _exam isin $session
  !distribute items Andere opgaven uit deze overhoring,\
	resterende tijd voor deze overhoring&nbsp;:,\
	zo gauw deze pagina is geladen\
	into wims_name_back,wims_name_examremain,wims_name_whenloaded
 !endif
 !if _check isin $session
  !let wims_page_name=Pagina's
 !endif
 !set wims_name_sequence=!defof sequence_Title in wimshome/log/classes/$wims_class/seq/.def
 !default wims_name_sequence=Werkvolgorde
 !set wims_name_sequences=werkvolgorde
 
 !set wims_name_exceeded=Uw klas is groter dan de ingestelde limiet op deze server.<p>\
 Klasse management is hierdoor niet meer bereikbaar.\
 We adviseren dat u de website manager vraagt de limiet voor deze klas te verhogen.
 
 !set wims_name_reaching_limit=De grootte van deze klas nadert de ingestelde server limiet.\
 Als deze limiet is bereikt , wordt het klasse management geblokkeerd ! 
!endif

!if adm/class isin $module or adm/manage isin $module
 !distribute line Docenten \
	Studenten \
	Demonstratie klassen\
	Inloggen voor docenten\
	Inloggen voor studenten\
	lagere school\
	middelbare school\
	universiteit\
	klassen lijst\
    Lijst met klassen en/of instituten\
    Individuele klassen\
    Groep klassen\
    Instituut\
	into wims_name_n_supervisor,wims_name_n_participant,wims_name_n_example,\
	wims_name_n_authsupervisor,wims_name_n_authparticipant,wims_name_n_E,wims_name_n_H,wims_name_n_U,\
	wims_name_classlist,wims_name_portal_list,\
	wims_name_create_class,wims_name_create_superclass,wims_name_create_portal
!endif

!if adm/new isin $module
  !distribute line Nieuwe modules\
  Verbeterde modules\
  Laatste systeem veranderingen\
  RSS nieuwe modules\
  RSS verbeterde modules\
  into wims_name_mod_new,wims_name_mod_modif,wims_name_mod_sys,wims_name_rss_new,wims_name_rss_modif
!endif

!if $wims_user=$empty
  !distribute line Oprichten van een klas\
  into wims_name_classcreate
!endif

!if adm/modtool isin $module or adm/createxo isin $module or $wims_user!=$empty or $module!=
  !distribute line Test de module\
   Document manager\
   Inhoud module\
   Andere bestanden\
   Eigenschappen\
   Opslaan\
   Verschillen\
   Publiceren\
   Nieuwe module\
   Lijst van modules\
   Bestanden\
   Backup van de module\
   Eigenschappen van account\
   Script tester\
   OEF Documentatie \
   Script bibiliotheek\
   Mogelijke antwoord modellen\
   Doc technisch\
   Terug naar de bestanden lijst\
   Bewerken het bestand\
   Veranderen\
   Terug\
   Wissen\
   Aktie\
   Hiervoor moet je webbrowser Java ondersteunen.\
   Datum\
   Toevoegen\
   Verwijderen\
   Broncode\
 into wims_name_test,wims_name_docgestion,wims_name_modcontent,wims_name_otherfiles,\
wims_name_properties,wims_name_modsave,wims_name_checkdiff,wims_name_publish,wims_name_createnew,\
wims_name_modlist,wims_name_binfile,wims_name_restore,\
wims_name_account_property,\
wims_name_scripttest,wims_name_docoef,wims_name_docslib,wims_name_docanswer,wims_name_doctec,\
wims_name_back3,wims_name_edfile,wims_name_change,wims_name_up,wims_name_erase,wims_name_action,\
wims_name_nojava,wims_name_date,wims_name_add0,wims_name_delete,wims_name_source

!distribute line Terug naar Createxo\
   Lijst met voorbeelden\
   Uitgewerkte voorbeelden\
into wims_name_backcreatexo,wims_name_modellist,wims_name_model

!distribute line Test de oefening\
Terug naar confia2qcm\
Terug naar createqcm\
Verander de broncode\
Bewaar deze testmodule\
Bewaar in uw klas\
Bewaar als een nieuwe oefening\
Stuur een plaatje\
Vervang de bestaande\
Verwijder de oefening\
into wims_name_testexo,wims_name_backconfia2qcm,wims_name_backcreateqcm,wims_name_exomodify,\
wims_name_putmodtool,wims_name_putclass,wims_name_newversion,\
wims_name_downloadbinary,wims_name_replace,wims_name_exoerase

!endif

!distribute line Nieuw document\
Nieuw werkblad\
Nieuwe proefwerk\
Nieuwe klas\
Nieuwe enquete\
Nieuw oefening\
Oefeningen van deze klas\
into wims_name_add_doc,wims_name_add_sheet,wims_name_add_exam,wims_name_add_class,wims_name_add_vote,\
wims_name_add_exo,wims_name_classexo

!!! for documents en particulier..

!distribute item WIMS,Klas,Docs,Up,Vorige,Volgende,Hist.,Vernieuwen,\
	Interactieve versie,Printbare versie,\
	Terug naar doc,Help,Info,\
	Bestand opsturen,\
	Terug naar de bestanden lijst,\
	Hoofdpagina van dit document\
	into wims_name_doch_wims,wims_name_doch_class,wims_name_doch_docs,wims_name_doch_up,\
	wims_name_doch_prev,wims_name_doch_next,wims_name_doch_hist,wims_name_doch_reload,\
	wims_name_doch_interactive,wims_name_doch_printable,\
	wims_name_doch_back,wims_name_doch_help,wims_name_doch_about,\
	wims_name_doch_upload,wims_name_doch_filelist,wims_name_doch_main

!! for sequence et document

!distribute line Document\
Onzichtbaar,Zichtbaar\
Titel\
Reorganiseren\
Toevoegen aan klas\
Maak een nieuw document\
Bewerk een document\
Status\
Toevoegen\
into wims_name_doc,wims_name_status,wims_name_title,wims_name_reorder,wims_name_adddoc,\
wims_name_createdoc,wims_name_doctry,wims_name_Status,wims_name_Insert

 !distribute line Een datum toegvoegen\
   Een bestand toevoegen\
   Bewerk de ToDo lijst\
   Configureren\
   Annulereren\
   Agenda\
  into wims_name_adddate,wims_name_addfile,wims_name_addtodo,wims_name_config,wims_name_giveup,\
  wims_name_cdt

!set wims_name_supervisor=administrator
!set wims_name_Supervisor=Administrator
!set wims_name_namestudent=Student
!set wims_name_nameteacher=Docent
!set wims_name_teacher=Docenten accounts
!set wims_name_addteacher=Nieuwe docent
!set wims_name_addparticipant=Voeg een deelnemer toe
!set wims_name_modteacher=Docent eigenschappen
!set wims_name_delteacher=Verwijder een docent
!set wims_name_student=Studenten accounts
!set wims_name_addstudent=Nieuwe student
!set wims_name_modstudent=Studenten eigenschappen
!set wims_name_delstudent=Verwijder een student
!set wims_name_group=Institiuut
!set wims_name_portal=Instituut
!set wims_name_level=Leerniveau
!set wims_name_class=Klas
!set wims_name_program=Programma
!set wims_name_course=Cursus
!set wims_name_icourse=Interklas cursus
!set wims_name_backstruct=Backup van de gehele structuur

!if config isin $module
 !distribute line Hoofdpagina klassen onderhoud\
 Instituut administratie\
 Backup en herstel\
into wims_name_config, wims_name_struct,wims_name_save

!endif

!set wims_name_backgateway=Beheer van

!distribute line Een cursus toevoegen\
Een interklas cursus toevoegen\
Een klas toevoegen\
Een programma toevoegen\
Een studieniveau toevoegen\
Inloggen beheerder \
Verander van zone\
into wims_name_addcourse,wims_name_addicourse,wims_name_addclass,wims_name_addprog,wims_name_addlevel,\
wims_name_login,wims_name_chzone

!distribute line Statistisch overzicht van de activiteiten\
Globale activiteiten van de deelnemers\
Verander de moeilijkheidsgraad\
Handmatig ingevoerde cijfers\
Spreadsheet data\
into wims_name_class_stat,wims_name_activity,wims_name_formula,wims_name_grades,\
wims_name_csv

!if adm/class isin $module or reguser isin $module or $wims_class!=$empty
!distribute line Lijst van alle studenten \
Cijfers\
Beeindig deze proefwerk sessie\
Details van het werk\
Schors deze student\
Ruwe gegevens\
Verander het wachtwoord\
Verwerkte data\
Overzicht vaardigheden \
into wims_name_part_list,wims_name_scores,wims_name_partexamclose,wims_name_workdetail,\
wims_name_delprep,wims_name_rawdata,wims_name_passwd,wims_name_getraw,wims_name_livret
!endif

!if adm/manage isin $module
  !distribute line Ander onderhoud\
  into wims_name_sitegestion
!endif

!if $wims_user=supervisor
 !distribute line Terug naar de supervisor pagina\
 into wims_name_backteacher
!endif

!distribute lines Modtool\
   Createxo\
   Quicktool\
   Latex2wims\
   into wims_name_modtool,wims_name_createxo,wims_name_quicktool,wims_name_latex2wims

!distribute line activeer de html-editor\
deactiveer de html-editor\
Let op: veranderingen worden niet opgeslagen als deze optie tijdens het schrijven wordt veranderd\
into wims_name_active, wims_name_desactive,wims_name_speck_warning

!distribute items Achternaam,Voornaam,Wachtwoord,email,Loginnaam,Herhaal het wachtwoord,Opmerkingen\
into wims_name_lastname, wims_name_firstname,wims_name_Password,wims_name_email,\
wims_name_Login,wims_name_repeat_pass,wims_name_comment

!distribute line Foto album\
Verstuur email\
into wims_name_photoboard,wims_name_sendmail

!distribute items Docent,Administrator,Student\
into wims_name_nameteacher,wims_name_Supervisor,wims_name_namestudent
