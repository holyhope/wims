!set lang_exists=yes

!if $wims_read_parm!=
 !goto $wims_read_parm
!endif

!set name_donchoose=Geselecteerd
!set name_studentloc=!nosubst $user_lastname $user_firstname
!set name_studentglo=!nosubst $wims_name_lastname $wims_name_firstname

!distribute line Gemiddelde van deze klas\
Gemiddelde\
Gemiddelde van alle positieve cijfers\
Totaal gemiddelde\
Groep gemiddelde\
into name_classAverage,name_Average,name_posAverage,name_globalaverage,\
name_groupAverage

!set name_partdeleted=Verwijderde studenten
!set wims_name_reg_ex=Lijst van oefeningen
!!set name_transfer=Breng zijn/haar activiteiten over uit andere klassen

!!!set name_thsheet=No,Titel,Vereist,Weging,Punten<br />verkregen, % , Kwaliteit , Moeilijkheidsgraad , Cijfer ,\
 Hoogste cijfers, Aantal pogingen, Laatste resultaat, Vereiste niveau
!set name_minmax=min/gem/max van deze klas

!set name_manualscore=Handmatig ingevoerde cijfers
!set name_autoscore=Behaalde cijfers
!set name_manual_notes=globaal,docent,auto
!set name_examnote=Proefwerkcijfers

!set name_severitylevels=Moeilijkheidsgraad van Werkbladen
!set name_formula=No,Gewicht,niveau
!set name_sheetstatut=in bewerking,actief,verlopen,onzichtbaar

!distribute items Proefwerk,Werkblad,Oefening,Start,Cijfer,Sessie,\
 Klaar,equiv.,Tijdsduur\
into name_Exam,name_Sheet,name_Exercise,name_Start,name_Score,name_Session,\
name_done,name_equiv,name_Duration

!set name_formula_comment=U kunt de moeiljkheidsgraad en weging van de werkbladen vastleggen in de onderstaande tabel.\
De cijfers worden berekend met maximum =
!set name_formula2=!nosubst Cijfers berekenen met als maximum $scoremax
!set name_pickup=Kies een werkblad<br />om het gemiddelde cijfer per<br />werkblad te laten zien:
!set name_warning=U verzoek is ongeldig en kan niet worden uitgevoerd.

!set name_click=Klik op de naam van een student om zijn/haar werk gedetailleerd te bestuderen
!set name_affi=&nbsp;kwaliteit&nbsp;,&nbsp;afgerond werk&nbsp;,&nbsp;cijfers&nbsp;,&nbsp;gemiddelde van de hoogste scores&nbsp;
!set name_workdetail=Detail van het werk van
!set name_activesession=Deze student heeft een nog actieve proefwerk sessie

!distribute items Netwerkadres,Resterende tijd,Proefwerk sessie,minuten\
into name_connecting,name_remaining_time,name_exam_session,name_minutes

!set name_noyetparticipant=Deze klas heeft nog geen studenten.

!set name_warning_no_sequence=U hebt de werkvolgorde geconfigureerd , maar nog niets aangegeven.Dus er kunnen ook geen cijfers worden getoond.

!if $manual>0
!set name_manual_explanation=<b>Uitleg.</b> In de kolom <span class="tt">Gemiddelde</span> , <span class="tt">auto</span> \
betekend het gemiddelde cijfer voor de server geregistreerde oefeningen en opdrachten in werkbladen,\
<span class="tt">docent</span> betekend het gemiddelde cijfer over de handmatig ingevoerde scores door de docent/supervisor,\
en <span class="tt">globaal</span> wordt berekend aan de hand van de formule

!endif

!set name_title_showsheet=!nosubst details van werkblad $numshowsheet<br />$sh_title
!set name_percentagegot=Percentage van de verkregen punten
!set name_qualitygot=Kwaliteit berekend over een maximum van 10
!set name_percentagedone=Percentage van het afgeronde werk
!set name_percentagebest=Gemiddelde van de beste scores

!set name_post=laat zien&nbsp;:
!set name_Post=Laat zien&nbsp;:

!set name_sheetdetail=Klik op een kolom kop \
voor een overzicht \
van alle oefeningen met het corresponderende werkblad.

!if $job iswordof userprop teacher
  !distribute items Verander,Registratie nummer,Opmerkingen,Foto url, (technische) Variabelen,\
   Klasse wachtwoord,Geef het klasse wachtwoord,\
   Login bij externe authentificatie,Inschrijving,Beheer,\
   Verplicht\
   into name_change,name_regnum,name_comments,name_photourl,name_vars,\
  name_classpassword,name_enterpassword,name_external_auth,name_inscript,name_gestion,\
  name_userprop_warning
  !goto end
!endif

!if $job=examcheck
 !set name_title_examcheck=!nosubst Proefwerk details van $name_studentloc
 !set name_no_exampart=Deze student heeft nog geen volledig proefwerk gemaakt.
 !set name_no_exampart=Hier staan alle proefwerk sessies van deze student.\
 Klik op een oefening om de inhoud te bekijken.
 !goto end
!endif
!if $job=getraw
  !set name_title_getraw=!nosubst Alle details van $name_studentloc<br />(in onbewerkte data)
  !goto end
!endif

!set name_direct_score=ruwe cijferlijst

!if $job=csv
  !distribute lines Hier is het bestand\
    dat kan worden geopend met een spreadsheet programma.\
    Student informatie is aangepast\
    Nieuwe studenten toegevoegd\
    Het toevoegen van nieuwe studenten is mislukt : er is geen geheugenruimte meer beschikbaar.\
    Student informatie is niet aangepast omdat de cijfers zijn geupload.\
    Server berekende cijfers (de gemiddelden en werkblad/proefwerk scores) zijn niet aangepast : deze kunnen niet worden veranderd.\
    Niet aangepaste gegevens over verwijderde studenten \
    De volgende loginnamen zijn niet toegevoeg omdat de login te kort is\
    De volgende loginnamen zijn niet aangepast in verband met onvolledige of incorrecte data\
    De volgende loginnamen zijn niet aanwezig in deze klas en kunnen niet wordn toegevoegd (incorrecte data of te weinig ruimte)\
    Handmatig ingevoerde cijfers zijn alleen opgenomen voor bestaande kolommen.\
    Er zijn geen verschillen gevonden tussen uw spreadsheet data en de klasses gegevens\
    Kontroleer handmatig de gegevens\
    Om klasse gegevens te downloaden voor gebruik in een spreadsheet programma ,specificeer \
    Formaat\
    Kolommen\
    Om klasse gegevens in spreadsheet formaat te uploaden naar de klas, specificeer \
    Data bestand\
    Geaccepteerde formaten\
  into name_file,name_download,name_infochanged,name_added,name_warning1,name_warning2,\
  name_warning3,name_warning4,name_badlogin,name_nologin1,name_nologin2,name_manual1,name_data1,\
    name_check,name_data2,name_format,name_column,name_data3,name_data,name_format2

  !set name_deposit=!nosubst Spreadsheet bestand <span class="tt">$wims_deposit</span> met succes verwerkt.
  !set name_indicateur=Indicatie
  !set name_techvar=Andere zoekterm
  !set name_regvar=Registration variables
  !set name_all=Alles
  !set name_allscore=Alle scores
!endif

!set name_topten=!nosubst Top $class_topscores van deze klas
:end
!exit

