!set lang_exists=yes

!if $wims_read_parm!=
 !goto $wims_read_parm
!endif

!set classname=$wims_classname - $wims_institutionname
 
!set months=Jan,Feb,Mar,Apr,Mei,Jun,Jul,Aug,Sept,Okt,Nov,Dec

!distribute line Gemiddelde van deze klas\
Gemiddelde\
Gemiddelde van alle positieve cijfers\
Totaal gemiddelde\
into name_classAverage,name_Average,name_posAverage,name_globalaverage

!set name_partdeleted=Verwijderde studenten
!set wims_name_reg_ex=Lijst van oefeningen
!set name_transfer=Breng zijn/haar activiteiten over uit andere klassen

!set name_thsheet=No,Titel,Vereist,Weging,Punten<br>verkregen,%,Kwaliteit,Moeilijkheidsgraad,Cijfer
!set name_minmax=min/gem/max van deze klas

!set name_manualscore=Handmatig ingevoerde cijfers
!set name_autoscore=Behaalde cijfers
!set name_manual_notes=globaal,docent,auto
!set name_examnote=Proefwerk cijfers

!set name_severitylevels=Moeilijkheidsgraad van Werkbladen
!set name_formula=No,Gewicht,niveau
!set name_sheetstatut=in bewerking,actief,verlopen,onzichtbaar

!distribute items Proefwerk,Werkblad,Oefening,Start,Cijfer,Sessie,Klaar,equiv.\
into name_Exam,name_Sheet,name_Exercise,name_Start,name_Score,name_Session,\
name_done,name_equiv

!set name_formula_comment=U kunt de moelijkheidsgraad en weging van de werkbladen vastleggen in de onderstaande tabel.\
De cijfers worden berekend met maximum = 
!set name_formula2=Cijfers berekenen met als maximum $scoremax
!set name_pickup=Kies een werkblad<br>om het gemiddelde cijfer per<br>werkblad te laten zien: 
!set name_warning=U opdracht voor de server is ongeldig en kan niet worden uitgevoerd.

!set name_click=Klik op de naam van een student om zijn/haar werk gedetailleerd te bestuderen. 
!set name_affi=kwaliteit,uitgevoerde opdrachten,cijfers
!set name_workdetail=Detail van het werk van
!set name_activesession=Deze student heeft een nog actieve proefwerk [exam] sessie

!distribute items Verbonden server,Resterende tijd,Proefwerk sessie,minuten\
into name_connecting,name_remaining_time,name_exam_session,name_minutes

!set name_noyetparticipant=Deze klas heeft nog geen studenten.

!if $manual>0
!set name_manual_explanation=<b>Uitleg.</b> In de kolom <tt>Gemiddelde</tt> , <tt>auto</tt> \
betekend het gemiddelde cijfer voor de server geregistreerde oefeningen en opdrachten in werkbladen,\
<tt>Docent</tt> betekend het gemiddelde cijfer over de handmatig ingevoerde scores door de docent/supervisor,\
en <tt>globaal</tt> wordt berekend aan de hand van de formule

!endif

!set name_title_showsheet=!nosubst details van werkblad $numshowsheet<br>$sh_title
!set name_percentagegot=Percentage van de verkregen punten
!set name_qualitygot=Kwaliteit berekend over een maximum van 10
!set name_percentagedone=Percentage van het afgeronde werk
!set name_post=Laat zien&nbsp;:
  
!if $job=userprop
  !distribute items Verander,Registratie nummer,Opmerkingen,Foto url, (technische) Variabelen,\
   Klasse wachtwoord,Geef het klasse wachtwoord\
   into name_change,name_regnum,name_comments,name_photourl,name_vars,\
  name_classpassword,name_enterpassword
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
  !set name_title_getraw=!nosubst Alle details van $lastname, $firstname <br>(in onbewerkte data)  
  !goto end
!endif

!set name_direct_score=ruwe cijfer lijst

!if $job=transfer
   !set name_title_transfer=Verplaatsen van activiteiten
   !distribute items Samenvoegen, Vervangen,Bekijken\
   into name_merge, name_replace,name_show
!set name_error1=<b>Error</b>. The participant has no registration in a corresponding\
 course in the current class to receive the transfer from
 !set name_error2=<b>Error</b> of class identification. Wrong manoeuvre or bug of the\
  software? 
 !set name_activities=!nosubst Detail of activities in $i (limited to 1000 lines).
 !set name_totransfer=Here are the other courses in which the participant has activities. \
   Click on an action to transfer them 

!endif

!if $job=recover
  !set name_empty=There is no deleted participant in this class.
  !set name_click=Click on a login name to recover the user.
!endif


!if $job=delprep
  !set name_delete=!nosubst Are you sure that you want to delete <b><em>$name_student1</em></b>\
     from your class?
!endif

!if $job=csv
  !distribute lines Here is the file\
    that you can download and open with your favorite spreadsheet program.\
    Participant informations changed\
    Added new participants\
    Addition of new participants ignored because there is no more available space.\
    Participant informations are not changed because grades are uploaded.\
    Server-computed scores (averages and worksheet/exam scores) are ignored in your data because they cannot be changed.\
    Ignored data about erased participants\
    The following login names do not exist in the class and cannot be added, because of unsufficient/incorrect information in the data\
    The following login names do not exist in the class and cannot be added (bad data, or no more space)\
    Manual grades are registered only for existing columns.\
    No change has been found in your spreadsheet data with respect to the class record.
    Check manual grades\
    To download class data for your spreadsheet, please specify\
    Format\
    Columns\
    To upload your spreadsheet data to the class, please specify\
    Data file\
    Accepted formats: .csv, .tsv, .txt\
  into name_file,name_download,name_infochanged,name_added,name_warning1,name_warning2,\
    name_warning3,name_warning4,name_nologin1,name_nologin2,name_manual1,name_data1,\
    name_check,name_data2,name_format,name_column,name_data3,name_data,name_format2
  
  !set name_deposit=!nosubst Spreadsheet file <tt>$wims_deposit</tt> successfully processed.
!endif

!set name_topten=!nosubst Top $class_topscores van deze clas
:end
!exit

:transfer
<b>Remarks</b>. <ol>
<li>"$name_merge" means putting together the activities in two courses.
<li>"$name_replace" means that the activities in the other cours will replace
that of this one. This will occur only if the former is not empty.
<li>Exam records and non-scoring activities are always merged.
<li>Registration of details of exercises or exams is not transfered.
<li>After the action ($name_merge ou $name_replace), the records of the participant
in the other course will be cleaned.
</ol>

