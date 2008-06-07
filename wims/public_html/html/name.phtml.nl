
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
		Kopieer naar Modtool\
	into wims_name_search,\
	wims_name_work,wims_name_resume,\
	wims_name_home,wims_name_intro,wims_name_help,wims_name_about,\
	wims_name_titleintro,\
	wims_name_back,wims_name_back2,\
	wims_name_manager,wims_name_author,wims_name_authors,\
	wims_name_translatedby,wims_name_exit,\
	wims_name_whelp,wims_name_ref,wims_name_forum,wims_name_forums,\
	wims_name_sheet,wims_name_tools,\
	wims_name_modify

!if $wims_class!=$empty
 !distribute items Homepagina van je klas,Voeg $ toe aan het werkblad,\
		Schrijf naar je leraar,Weg uit de klas,\
		De antwoorden zijn reeds verwerkt en de cijfers berekend,\
		Je hebt het behalen van cijfers opgeschort,\
		Jij bent de leraar van deze klas,\
		Bewaar de details van deze oefening\
	into wims_name_home,wims_name_add,\
	wims_name_wsup,wims_name_visitor,\
	wims_name_scoreclose,\
	wims_name_scoresuspend,\
	wims_name_syou,\
	wims_name_exolog
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



