
!set classname=<b><font color=green>$wims_classname</font></b>\
 van <b><font color=green>$wims_institutionname</font></b>

!read adm/lang/date.phtml.$lang

!set statutname=!defof SU_Uprep,SU_Uprep,SU_Ac,SU_Ex,SU_Hi in wimshome/public_html/modules/home/names.$lang
!set statutaction=Activeren,Berlopen,Deactiveren,Verbergen,Tonen,$wims_name_erase
!set seriesaction=$wims_name_change,$wims_name_erase,$wims_name_up

!! définition des noms pour les liens dans le menubox (définis par wims_menu_items)
!distribute items Broncode toevoegen,\
		Zo zien studenten deze pagina,\
		Broncode van het werkblad \
into wims_name_putsource,wims_name_participantview,wims_name_sheetsource

!let name_shtab=No,$wims_name_title,$wims_name_Description,Punten,Weging,Afhankelijkheden,$wims_name_comment,$wims_name_action,Parameters

!if $activetest<=0
 !let wims_name_sheetadmin=Werkblad aanmaakpagina
 !set name_title=!nosubst Aanmaken van werkblad $sheet
!else
 !let wims_name_sheetadmin=Werkblad management
 !set name_title=!nosubst Management van werkblad $sheet
!endif

!let name_shinfo=!nosubst $wims_name_title <small>(maximaal $title_limit karakters)</small>,$wims_name_Status,\
Omschrijving <br><small>(maximaal $desc_limit karakters; html tags en links zijn toegestaan)</small>,\
Einddatum,Presentatie pagina,Cijfer registratie,voor alle klassen die dit werkblad delen :,Opmerkingen <small>(Alleen zichtbaar voor de docenten)</small>
!let name_allowtype=open voor iedereen, gesloten voor iedereen, alleen open voor de volgende adressen (en/of tijdstippen) :
!let name_mksheet=Maak een werkblad

!distribute lines Algemene informatie&nbsp;\
Inhoud van dit werkblad&nbsp;\
Dit werkblad heeft nog geen inhoud.\
De oorspronkelijke titel is\
Gewijzigde reeks oefeningen\
Vereiste punten aantal\
Punten\
Corrigeer de broncode\
De uiterste datum van het werkblad moet vóór de vervaldatum van deze klas zijn\
Uw date worden dus genegeerd\
into name_info,name_content,name_warning,name_oldtitle,name_titlemodif,\
name_pointsasked,name_ofweight,name_correctsource,name_expiration1,name_expiration2

!set name_text1=Om oefening (of hulpmiddelen etc) aan een werkblad toe te voegen, moet\
eerst de betreffende module worden geslecteerd (zie hieronder) ; stel de oefening op de intropagina naar eigen wens \
af met de daarvoor bestemde instelparameters. \
Start de oefening en klik vervolgens op de link <font color=blue><tt>voeg toe aan werkblad</tt></font> onderaan de pagina.\
Voor het selecteren van oefening zijn de volgende opties beschikbaar

!set name_text2=Geef een zoekopdracht
!set name_text3=Zoek naar een oefening met
!set name_text4=Zoek een oefening uit uw eigen account

!if $job=student
  !set name_title=Werkblad nummer $sheet<br>$title (Presentatie voor studenten)
  !set name_sheetempty=Dit werkblad is leeg. Waarschijnlijk een foutje van de je docent.
  !set name_assignedwork=Opdrachten in dit werkblad&nbsp;
  !set name_quality=0 uit $[$re] punten behaald, kwaliteit
!endif

!set name_desc_dependancy=een student moet eerst de gewenst score hebben behaald voordat de volgende opdracht mag worden gedaan.[drempel] <br>Bijvoorbeeld:<font color=blue><tt>1:50,2:30,3+4+5:60</tt></font> betekend: de student moet 50% van de opdracht 1 goed hebben,30% van opdracht 2 en een gemiddelde score van 60% over de opdrachtwn 3,4 en 5</small>           

!set name_desc_comment=Alleen zichtbaar voor docenten.
!set name_getsource=Hier staat de broncode van dit werkblad.U kunt deze kopieren (tussen de twee regels met "****") en hergebruiken voor een ander werkblad.                                                                                                      
