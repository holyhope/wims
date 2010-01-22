!set lang_exists=yes
!set classname=$wims_classname - $wims_institutionname

!!!set months=january,february,march,april,may,june,july,august,september,october,november,december

!if $job=adddate
  !set cdt_subtitle=Modificatie datum
  !goto common
!endif

!if $job=addtodo
  !set cdt_subtitle=Voeg huiswerk toe
  !goto common
!endif

!if $job=logfile
  !set cdt_subtitle=Log file
  !set name_text=Lijst met ipadressen ingelogd op de klas agenda
  !goto common
!endif

!if $job=config
  !set cdt_subtitle=Aanmelden
  !set name_link=De linknaam op de homepage
  !set name_intro=Hier zijn de instelparameters
  !set name_see=Bekijk 
  !set name_see2=de log file van de agenda.
  !goto common
!endif

!if $job=file
  !set name_erasedfile=!nosubst Het bestand <b>$erase</b> is verwijderd.
  !set name_depos=Een bestand toevoegen
  !set name_available=Beschikbare bestanden
  !set name_erase=Verwijder een bestand
  !set name_nodeposit=Er kan geen bestand meer worden toegevoegd omdat de ingestelde maximum \
  hardeschijfruimte voor deze klas is bereikt.
  !set name_explanation1=!nosubst Deze bestanden kunnen worden ingebonden door de variabele\
  <tt>\filedir</tt>. \
  Bijvoorbeeld:\
  <p><center>\
  <tt>&lt;a href="\filedir/$f1"&gt;$f1&lt;/a&gt;</tt>\
  </center> <p>\
  geeft een link naar het bestand \
  <a href="$m_filedir/$f1">$f1</a>.\
  En mag ook gedefinieerd worden als
 
 !set name_explanation2=!nosubst om een plaatje  
 <tt>myfile.jpg</tt> \
 toe te voegen. <p>De bestanden zijn alleen bereikbaar voor leerlingen van deze klas.
 
 !set name_availablespace=Totaal beschikbare hardeschijfruimte,Onbenutte hardeschijfruimte
 
  !goto common
!endif


!if $job=helplink
  !set name_Add=Klik op de link om een item toe te voegen.
  !set name_exam=Proefwerken;
  !goto common
!endif

:common
!distribute line Werk\
Nog te doen \
tussen\
en\
Voeg een proefwerk toe\
voor\
Werk te doen\
Werk\
Aantal zichtbare datums \
Werk nog te doen voor \
Werk\
Sessie\
karakters\
Geen informatie\
Geen informatie voor deze dag\
Geen informatie voor deze periode\
Dag\
Disciplines\
In klas\
Gegeven\
Er is geen werk opgegeven voor\
into name_done,name_todo,name_between,name_and,name_addexam,name_for,name_worktodo,\
name_work,name_nb_date,name_todo2,name_workdone,name_session,\
name_character,name_noinfo1,name_noinfo2,name_noinfo3,\
name_Day,name_discipline,name_inclass,name_giventhe,name_nowork

!set name_workfor=$name_work $name_for

!set name_warning1=Als er geen tweede datum is opgegeven wordt alles gebaseerd op de eerst opgegeven datum.

!set name_date=!nosubst $jyear/$jmonth/$jday
!set name_date2=!nosubst $jyear2/$jmonth2/$jday2
