!set lang_exists=yes
!set classname=<b><font color=green>$wims_classname</font></b>\
 van <b><font color=green>$wims_institutionname</font></b>

!if $activetest<=0
!! !let wims_name_sheetadmin=Werkblad aanmaak pagina
 !set name_title=!nosubst Aanmaken van werkblad $sheet
!else
!! !let wims_name_sheetadmin=Werkblad beheer
 !set name_title=!nosubst Beheer van werkblad $sheet
!endif

!read adm/lang/date.phtml.$lang

!! ---------------------------------------------------------------------------------------------------
!! ancien fichier name du module exam.fr

!set wims_name_endexam=Be&euml;indig de proefwerk sessie
!set wims_name_scoreexam=Mijn cijfers

!set name_mainpage=Hoofdpagina van het proefwerk
!set name_dependency=Cijfer afhankelijkheden&nbsp;
!set name_Options=Opties
!set name_All=Alles
!set name_title=Aanmaken van een proefwerk

!!set name_expire=Laat het proefwerk nu verlopen

!set name_done=klaar

!distribute items Gewicht,Co&euml;fficient,Cijfer\
into name_weight,name_coeff,name_Score

!distribute lines Be&euml;indig deze proefwerksessie\
Terug naar het proefwerk\
Zo zien docenten dit proefwerk\
Zo zien studenten dit proefwerk\
Details van de score\
Dit proefwerk is leeg&nbsp;! Dit zal een foutje zijn van de docent.\
Inhoudsopgave van dit proefwerk&nbsp;\
Dit proefwerk is niet bereikbaar voor computers met uw IP adres.\
U mag dit proefwerk nog &eacute;&eacute;n keer maken.\
Dus het cijfer voor dit proefwerk kan niet meer worden verbeterd.\
Opgelet : dit is de laatste proefwerk poging.\
het aftellen begint en het aantal beschikbare proefwerk pogingen wordt met 1 verminderd.\
begin het aftellen .\
Vereist een goed cijfer bij de vorige opgaven\
Cijfer voor deze proefwerk sessie&nbsp;\
into wims_name_endexam,wims_name_backexam,wims_name_teacherview,name_presentation,\
name_scoreexam,name_empty,name_content,name_examclosed,name_exam1,name_exam5,\
name_lasttry,name_exam7,name_exam8,name_depend,name_scoreexam2

!set name_exam2=!nosubst Er zijn in't totaal $stries proefwerk pogingen beschikbaar.

!set name_exam3=!nosubst Deze proefwerk sessie is be&euml;indigd met $tried pogingen,
!set name_exam4=!nosubst Dit was proefwerk poging nummer $tried ,
!set name_exam6=!nosubst En er zijn nu nog $tryremain poging(en) beschikbaar.

!set name_exam9=!nosubst Dit proefwerk mag maximaal $sdure min. in beslag nemen.\
Wanneer een opgave wordt aangeklikt,
 
!set name_simulation=Dit proefwerk verloopt in simulatie mode. Het werkt precies zo als het echte proefwerk, \
alleen worden nu de cijfers -en andere data- natuurlijk niet opgeslagen.
  
!set wims_name_examremain=Resterende tijd voor dit proefwerk : $

!distribute lines bezig...\
U bent nog niet begonnen met dit proefwerk.\
Start dit proefwerk.\
Uw score wordt niet geregistreerd, omdat dit proefwerk in simulatie mode loopt.\
into name_pending,name_begin1,name_begin2,name_simulation2

!set name_timeleft=!nosubst De beschikbare tijd is verlopen! Je hebt de toegestane $sdure minuten verbruikt.
!set name_realscore=!nosubst De echte score voor deze proefwerk-sessie is $lastscore.
!set name_bestscore=!nosubst De score voor dit proefwerk is $lastscore. (En de beste score telt !)


!! ---------------------------
!! nouvelle partie 

!set statutname=$(wims_name_shstatus[1]),$wims_name_shstatus

!! -------------- title description for file examinfo.phtml
!let name_shinfo=!nosubst $wims_name_title,$wims_name_Status,\
Uitleg,\
Verloopdatum,,Cijfer registratie,voor alle klassen die aan het proefwerk meedoen :,Opmerkingen,Maximaal beschikbare tijd voor een proefwerk,Aantal pogingen per proefwerksessie

!! ------- value for description of option
!set name_desc_title=!nosubst Maximaal $title_limit lettertekens
!set name_desc_desc=!nosubst Maximaal $desc_limit lettertekens; html tags en links zijn toegestaan

!!set name_desc_dependancy=Score drempels : dit betekent dat een deelnemer/leerling een bepaalde hoeveelheid punten <br>moet behalen voor dat de volgende som/opdracht uit het proefwerk bereikbaar wordt.<br>We noemen dit toets-type een "drempel toets".<br>Bijvoorbeeld:  <font color=blue><tt>1:50,2:30,3+4+5:60</tt></font> wil zeggen dat<br>de leerling minimaal 50% goed moet hebben van opdracht 1, 30% van opdracht 2 en opdracht 3,4,5 samen gemiddeld minimaal 60%.

!set name_desc_comment=Alleen zichtbaar voor docenten.
!set name_desc_duration=in minuten
!let name_mkexam=Proefwerk aanmaken
!let name_allowtype=open voor iedereen,in simulatiemode,gesloten voor iedereen,open voor de volgend ipadressen (en/of tijdstippen) :
!let name_shinfo_cutt=Openingstijden

!! définition des noms pour les liens dans le menubox (définis par wims_menu_items)
!distribute items Zo zien studenten deze pagina,\
Voeg een oefening toe,\
Voeg een serie oefeningen toe,\
into wims_name_participantview,wims_name_addexo,wims_name_addsexo


!! différents commentaires de la page de gestion
!distribute lines Algemene informatie&nbsp;\
Inhoudsopgave van dit proefwerk&nbsp;\
Dit proefwerk is leeg.\
into name_info,name_content,name_warning

!!De titel is\
!!Verande de serie oefeningen\
!!Vereiste punten aantal\
!!Gewicht\
!!Corrigeer de broncode\
!!De verloopdatum van dit werkblad moet gekozen worden voor de einddatum van de klas.\
!!Het verzoek wordt daarom genegeerd.\
!!,name_oldtitle,name_titlemodif,\
!!name_pointsasked,name_ofweight,name_correctsource,name_expiration1,name_expiration2

!! titre du tableau de contenu de l'examen (file examcontent.phtml)
!let name_extab=!nosubst No,$wims_name_title,Inhoud,$name_weight,$name_dependency,$wims_name_comment,$name_Options,$wims_name_action


!!if $job=student
!!  !set name_title=Werkblad nummer $sheet<br>$title (studenten presentatie)
!!  !set name_sheetempty=Dit werkblad is leeg ! Misschien een manipulatie faoutje van de docent ?
!!  !set name_assignedwork=Opdrachten in dit werkblad&nbsp;
!!  !set name_quality=!nosubst 0 uit $[$re] punten behaald , kwaliteit
!!endif

!!let name_intro_exo=Een oefening kan willekeurig worden gekozen uit de lijst van bestaande oefeningen uit de werkbladen.<br>Vink de werkbladen aan in de onderstaande lijst als kandidaten voor dit proefwerk. 



!set name_contenu=Kies de inhoud
!let name_cpsheet1=U kunt alle oefeningen van werkblad toevoegen aan het proefwerk. Elke oefening krijgt gewicht 1 en de titel van de oorspronkelijke oefening. Of geef hier generieke titel aan
!let name_cpsheet2=Sheet
!let name_cpsheet3=Generieke titel voor een oefening
!let name_cpsheet4=de oefeningen zijn genummerd

!set name_warning_nonfinished=Je hebt nog niet alle opgaven uit dit proefwerk gemaakt. Wanneer je \
  er nu mee stopt, wordt je cijfer bevroren en ben je dus een volle proefwerk poging kwijt.\
  Bij een eventuele volgende poging om dit proefwerk te maken, moet je wel weer alle\
  random (!) sommen opnieuw doen... <p>Weet je zeker dat je er mee wilt stoppen?

!let name_selectsheet=Laat alleen oefeningen zien uit werkblad


