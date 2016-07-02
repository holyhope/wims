!set lang_exists=yes

!set name_remark_numstud=Vous pouvez saisir 0 dans la deuxième colonne pour indiquer qu'il n'y a pas de limite.
!set name_introtext_group=Saisir l'effectif de chaque groupe ainsi qu'un commentaire (éventuel).
!set name_cardinal=Effectif

!set name_0=in bewerking
!set name_1=open
!set name_2=gesloten
!set name_3=onzichtbaar
!set name_publish=publiceren
!set name_publish2=publiceren
!set name_hide=verbergen
!set name_hide2=verborgen
!set name_nominative=op naam gesteld [niet anoniem]
!set name_anonymous=anoniem
!set name_trace=anoniem en traceerbaar
!set name_choice=Keuze
!set name_question=Vraag
!set name_data=gegevens
!set name_global=globaal
!set name_detail=gedetailleerd
!set name_yourchoice=Uw keuze&nbsp;:
!set title_data=Gegevens vragenlijsten voor spreadsheet
!set title_nominative=Enquete
!set title_vote=Enquete
!set title_anonymous=Anonieme enquete
!set name_choose= -- Kies --
!set wims_name_vote=Enquete of verkiezingslijsten
!set name_result=Resultaat van de enquete&nbsp;
!set name_content=Inhoud
!set name_creation=Maken van een enquete of verkiezing.
!set name_edition=Bewerken van een enquete of verkiezing.
!set name_remaining=rest
!set name_untitled=geen titel
!set name_showresult=laat resultaat zien
!set name_nowritable=Een actieve enquete kan niet worden veranderd. Hier is de broncode:
!set name_novotant=Geen stem uitgebracht
!set name_notenough=Nog niet genoeg stemmen uitgebracht
!set name_showlist=Resultaten per vraag
!set name_showglobal=Globale resutaten
!set name_showlistbystudent=Resultaten per deelnemer
!set name_showstudentbyitem=Lijst met keuzes

!distribute lines  Jouw klas heeft geen voorziening voor een verkiezing of enquete.\
Neem hierover contact op met je docent.\
Er is geen actieve verkiezing of enquete in je klas.\
Hier staan de verkiezingen/enquetes van jouw klas.\
Aantal stemmen\
into name_novote,name_novotecheck,name_noactivevote,name_class_vote,\
name_cnt_votes

!distribute line Dit is een anonieme verkiezing/enquete.\
Deze enquete is $name_trace.\
Deze enquete is $name_nominative.\
Is gesloten.\
reacties\
Je hebt al gestemd.\
Je voorkeur staat genoteerd; maar je kunt je nog bedenken\
Maak je keuze&nbsp;\
Details\
Opmerkingen\
Gebruik het forum voor uitgebreider commentaar.\
into name_thisvote_anomymous,name_thisvote_trace,name_thisvote_nominatif,\
   name_thisvote_closed,name_thisvote_answer,name_thisvote_already1,\
   name_thisvote_already2,name_give_your_choice,name_details,\
   name_comments,name_textarea

!set name_textarea_limit=!nosubst beperkte to $limit_textarea lettertekens
!set name_whovote=Lijst met stemmers
!set name_whodontvote=Lijst met niet stemmers

!set name_csv1=Hier is het bestand. Het kan geopend worden met een spreadsheet\
programma naar keuze.

!set name_csv2=!nosubst U wilt de gegevens downloaden uit de vragenlijst nummer $vote&nbsp;
!set name_format=formaat

!set name_option=Options
!set name_value=Waarden

!! guided mode

!set name_optionclosed=gesloten, wordt geopend als alle andere opties zijn ingevuld

!distribute lines Hoeveel sessies ?\
Hoeveel groepen?\
maximaal\
uservar naam\
Default host IP \
kan worden veranderd op de volgende pagina\
Introductie tekst \
dwz introductie tekst voor de student\
aantal<br />studenten\
Datum<br />sessie\
Begin tijd<br />sessie\
Eind tijd<br />sessie\
Host IP\
Extra info\
Afmelding inschrijving\
into name_howmany,name_howmanygroups,name_atmost,name_namevar,name_textconnip,\
  name_textconnip2, name_introtext,name_introtext2,name_numstud,name_sessiondate,\
  name_begintime,name_endtime,name_connip,name_extra,\
  name_cancellation

!set name_numsess=!nosubst $numsess toets sessies zijn beschikbaar.
!set name_session_select=!nosubst Selecteer datum en tijd van de $numsess beschikbare toets sessies

!set name_describesource=!nosubst Hier staat de brontekst. Controleer de gegevens en klik op <span class="wims_button disabled">$wims_name_tosave</span>.

!if $vote_mode!=free
 !readproc adm/lang/sheetexam.phtml.$lang
!endif

!set name_yourvariable=!nosubst De naam van de variabele voor de instellingen \
die u hebt gekozen is <span class="tt wims_code_variable">$namevar</span>
!set name_accessvar_instr=!nosubst <strong>Voor gebruik in een werkblad of toets</strong>: \
in een actief werkblad of toets, <span class="tt wims_code_words">$(name_shinfo[6])</span>, selecteer \
 <span class="tt wims_code_words">$(name_allowtype[4])</span>.

!set name_group_instr=!nosubst <strong>Voor gebruik in een klas</strong>: U kunt de deelnemers \
op basis van deze variabele voor een aantal activiteiten in de klas filteren
!set name_group_help=kan worden gebruikt om deelnemers per groep (bijv. e-mail en foto gallery ) te selecteren.

!set name_accessvar_help=kan worden gebruikt om werkbladen of toetsen voor een selectieve groep studenten klaar te zetten.

!distribute items Vrije Mode ,Toegang tot werkbladen en toetsen,Samenstelling van de groep,Groepen into name_free,name_accessvar, name_group,name_group1

!set name_model=Model
!set name_nextstep=Volgende stap

!set name_getsource=Dit is de bron code. De tekst tussen de twee rijen `*' \
kan worden gekopieerd (clipboard) in een lege 'stemming' met dezelfde inhoud.
