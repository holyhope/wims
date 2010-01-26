!set lang_exists=yes
!set classname=<b><font color=green>$wims_classname</font></b>\
 de <b><font color=green>$wims_institutionname</font></b>

!if $activetest<=0
 !let wims_name_sheetadmin=Page de préparation
 !set name_title=!nosubst Préparation de l'examen $sheet
!else
 !let wims_name_sheetadmin=Page de gestion
 !set name_title=!nosubst Gestion de l'examen $sheet
!endif

!read adm/lang/date.phtml.$lang

!! ---------------------------------------------------------------------------------------------------
!! ancien fichier name du module exam.fr

!set wims_name_endexam=Be&euml;indig de proefwerk sessie
!set wims_name_scoreexam=Mijn cijfers

!set wims_name_mainpage=Hoofdpagina van het proefwerk
!set name_dependency=Cijfer afhankelijkheden&nbsp;
!set name_Options=Opties
!set name_All=Alles
!set name_title=Aanmaken van een proefwerk
!set name_expire=Laat het proefwerk nu verlopen
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
U mag dit proefwerk nog &eacute;&eactue;n keer maken.\
Dus het cijfer voor dit proefwerk kan niet meer worden verbeterd.\
Opgelet : dit is de laatste proefwerk poging.\
het aftellen begint en het aantal beschikbare proefwerk pogingen wordt met 1 verminderd.\
begin het aftellen .\
Vereist een goed cijfer bij de vorige opgaven\
Cijfer voor deze proefwerk sessie&nbsp;\
into wims_name_endexam,wims_name_backexam,name_teacherview,name_presentation,\
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
!set name_bestscore =!nosubst De score voor dit proefwerk is $lastscore. (En de beste score telt !)

!! ---------------------------
!! nouvelle partie 

!set statutname=!defof SU_Uprep,SU_Uprep,SU_Ac,SU_Ex,SU_Hi in wimshome/public_html/modules/home/names.$lang
!set statutaction=Activer,Expirer,Désactiver,Cacher,Montrer,$wims_name_erase

!! -------------- title description for file examinfo.phtml
!let name_shinfo=!nosubst $wims_name_title,$wims_name_Status,\
Texte d'explication,\
Date d'expiration,,Enregistrement des notes,pour toutes les classes partageant l'examen :,Commentaire,Durée d'une session d'examen,Nombre d'essais par session

!! ------- value for description of option
!set name_desc_title=!nosubst limité à $title_limit caractères
!set name_desc_desc=!nosubst limité à $desc_limit caractères; les tags et liens html sont admis
!set name_desc_dependancy=Un participant doit d'abord acquérir des points dans d'autres exercices de la feuille, avant de pouvoir travailler sur celui-ci. Par exemple, <font color=blue><tt>1:50,2:30,3+4+5:60</tt></font> signifie que le participant doit avoir un succès de 50% sur l'exercice 1, 30% sur l'exercice 2, et une moyenne de succès de 60% sur les exercices 3, 4, 5.</small>
!set name_desc_comment=Visible seulement par l'enseignant.
!set name_desc_duration=en minutes
!let name_mkexam=Créer l'examen
!let name_allowtype=ouvert pour tous,ouvert pour simulation,fermé pour tous,ouvert pour postes (et/ou heures) suivants :
!let name_shinfo_cutt=Heures de coupure

!! définition des noms pour les liens dans le menubox (définis par wims_menu_items)
!distribute items Vue des participants,\
		Ajouter un exercice,\
		Ajouter une série d'exercices,\
into wims_name_participantview,wims_name_addexo,wims_name_addsexo


!! différents commentaires de la page de gestion
!distribute lines Informations générales&nbsp;\
Contenu de l'examen&nbsp;\
Cet examen n'a pas encore de contenu.\
Le titre d'origine est\
Modification de série d'exercices\
Nombre de points demandés\
Poids\
Corriger le source\
La date d'expiration de la feuille doit être antérieure à la date d'expiration de la classe\
Votre requête est donc ignorée.\
into name_info,name_content,name_warning,name_oldtitle,name_titlemodif,\
name_pointsasked,name_ofweight,name_correctsource,name_expiration1,name_expiration2

!! titre du tableau de contenu de l'examen (file examcontent.phtml)
!let name_extab=!nosubst No,$wims_name_title,Contenu,$name_weight,$name_dependency,$wims_name_comment,$name_Options,$wims_name_action


!if $job=student
  !set name_title=Feuille de travail numéro $sheet<br>$title (Présentation pour participants)
  !set name_sheetempty=Cette feuille est vide! Peut-être une erreur de manipulation de votre enseignant.
  !set name_assignedwork=Devoirs dans cette feuille&nbsp;
  !set name_quality=!nosubst 0 des $[$re] points obtenus, qualité
!endif

!let name_intro_exo=Cet exercice peut être pris (aléatoirement) dans une liste d'exercices\
existants dans des feuilles de travail. Veuillez marquer parmi les exercices des\
feuilles de la liste suivante ceux que vous voulez prendre pour cet exercice d'examen.
!set name_contenu=Choix du contenu
