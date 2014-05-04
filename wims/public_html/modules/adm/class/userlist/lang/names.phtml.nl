!set lang_exists=yes

!if $wims_read_parm!=
 !goto $wims_read_parm
!endif

!distribute line Gemiddelde van deze klas\
Gemiddelde\
Gemiddelde van alle positieve cijfers\
Totaal gemiddelde\
into name_classAverage,name_Average,name_posAverage,name_globalaverage

!set name_partdeleted=Verwijderde studenten
!set wims_name_reg_ex=Lijst van oefeningen
!set name_transfer=Breng zijn/haar activiteiten over uit andere klassen

!!!set name_thsheet=No,Titel,Vereist,Weging,Punten<br />verkregen,%,Kwaliteit,Moeilijkheidsgraad,Cijfer,\
 Best scores,Number of tries,Last result, Acquired level
!set name_minmax=min/gem/max van deze klas

!set name_manualscore=Handmatig ingevoerde cijfers
!set name_autoscore=Behaalde cijfers
!set name_manual_notes=globaal,docent,auto
!set name_examnote=Proefwerkcijfers

!set name_severitylevels=Moeilijkheidsgraad van Werkbladen
!set name_formula=No,Gewicht,niveau
!set name_sheetstatut=in bewerking,actief,verlopen,onzichtbaar

!distribute items Proefwerk,Werkblad,Oefening,Start,Cijfer,Sessie,Klaar,equiv.\
into name_Exam,name_Sheet,name_Exercise,name_Start,name_Score,name_Session,\
name_done,name_equiv

!set name_formula_comment=U kunt de moeiljkheidsgraad en weging van de werkbladen vastleggen in de onderstaande tabel.\
De cijfers worden berekend met maximum =
!set name_formula2=!nosubst Cijfers berekenen met als maximum $scoremax
!set name_pickup=Kies een werkblad<br />om het gemiddelde cijfer per<br />werkblad te laten zien:
!set name_warning=U verzoek is ongeldig en kan niet worden uitgevoerd.

!set name_click=Klik op de naam van een student om zijn/haar werk gedetailleerd te bestuderen
!set name_filter=or filter according to a technical variable (student properties)
!set name_affi=kwaliteit,uitgevoerde opdrachten,cijfers,la moyenne des meilleures notes requises
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
 !set name_title_examcheck=!nosubst Proefwerk details van $user_lastname, $user_firstname
 !set name_no_exampart=Deze student heeft nog geen volledig proefwerk gemaakt.
 !set name_no_exampart=Hier staan alle proefwerk sessies van deze student.\
 Klik op een oefening om de inhoud te bekijken.
 !goto end
!endif
!if $job=getraw
  !set name_title_getraw=!nosubst Alle details van $lastname, $firstname <br />(in onbewerkte data)
  !goto end
!endif

!set name_direct_score=ruwe cijfer lijst

!if $job=transfer
   !set name_title_transfer=Verplaatsen van activiteiten
   !distribute items Samenvoegen, Vervangen,Bekijken\
   into name_merge, name_replace,name_show
!set name_error1=Deze student is niet geregistreerd bij de andere cursus en\
kan dus niet worden overgezet van
 !set name_error2=<b>Fout</b> in de klas identificatie. Verkeerde handeling of een software fout?
 !set name_activities=!nosubst Details van de aktiviteiten in $i (beperkt tot 1000 regels).
 !set name_totransfer=Hier staan de andere cursussen waarin deze student werk heeft uitgevoerd.\
 Klik om het werk over te hevelen

!endif

!if $job=recover
  !set name_empty=Er is geen verwijderde student in deze klas.
  !set name_click=Klik op de loginnaam om het account te herstellen.
!endif

!if $job=delprep
  !set name_delete=!nosubst Zeker weten de <b><em>$name_student1</em></b>\
     uit deze klas verwijderd moet worden ?
!endif
!if $job=csv
  !distribute lines Hier is het bestand\
    dat kan worden geopend met een spreadsheet programma.\
    Student informatie is aangepast\
    Nieuwe studenten toegevoegd\
    Het toevoegen van nieuwe studenten is mislukt : er is geenv geheugenruimte meer beschikbaar.\
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
!endif

!set name_topten=!nosubst Top $class_topscores van deze klas
:end
!exit

:transfer
<b>Opmerkingen</b>. <ol>
<li>"$name_merge" wil zeggen : het samenvoegen van de activiteiten van twee cursussen.</li>
<li>"$name_replace" wil zeggen : de activiteiten in de andere cursus gaan de activiteiten
in deze cursus vervangen.</li>
<li>Proefwerk cijfers en alle niet_scorende activiteiten worden altijd samengevoegd.</li>
<li>De verbatim opgeslagen proefwerk &amp; oefeningen worden niet overgezet.</li>
<li>Na de handeling ($name_merge of $name_replace), worden deze gegevens van de
student in de andere cursus gewist.</li>
</ol>

