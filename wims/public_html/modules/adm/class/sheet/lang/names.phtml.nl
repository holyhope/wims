!let lang_exists=yes

!read adm/lang/date.phtml.$moduclass_lang
!read adm/lang/sheetexam.phtml.$lang

!set statutname=$(wims_name_shstatus[1]),$wims_name_shstatus
!set seriesaction=!nosubst $wims_name_change,$wims_name_erase,$wims_name_up
!set name_duplicateok=Werkbladen zijn correct gedupliceerd.

!set name_name=Naam
!set name_ltvalue=Waarde(s)

!let name_shtab=!nosubst No,$wims_name_title,$wims_name_Description,Punten,Weging,Afhankelijkheden,$wims_name_comment,$wims_name_action,Parameters,$wims_name_feedbackexo
!set name_qnum=Nb ex. in series

!if $activetest<=0
 !let wims_name_sheetadmin=Werkblad aanmaakpagina
 !set name_title=!nosubst Aanmaken van werkblad $sheet
 !set name_order=Volgorde van de oefeningen
!else
 !let wims_name_sheetadmin=Werkblad management
 !set name_title=!nosubst Management van werkblad $sheet
!endif
!let name_mksheet=Maak een werkblad

!distribute lines Algemene informatie&nbsp;\
Inhoud van dit werkblad&nbsp;\
Dit werkblad heeft nog geen inhoud.\
De oorspronkelijke titel is\
Gewijzigde reeks oefeningen\
Vereiste punten aantal\
Corrigeer de broncode\
De uiterste datum van het werkblad moet v��r de vervaldatum van deze klas zijn\
Deze data worden dus genegeerd\
into name_info,name_content,name_warning,name_oldtitle,name_prep_modify,\
name_pointsasked,name_correctsource,name_expiration1,name_expiration2

!set name_text1=Om oefening (of hulpmiddelen etc) aan een werkblad toe te voegen, moet\
eerst de betreffende module worden geslecteerd (zie hieronder) ; stel de oefening op de intropagina naar eigen wens \
af met de daarvoor bestemde instel-parameters. \
Start de oefening en klik vervolgens op de link <span class="wims_emph">voeg toe aan werkblad</span> onderaan de pagina.\
Voor het selecteren oefeningen op WIMS zijn de volgende opties beschikbaar:

!set name_text2=Geef een zoekopdracht
!set name_text3=Zoek naar een oefening met
!set name_text4=Zoek een oefening uit uw eigen account
!set name_texttaxo=Zoek een geclassificeerde oefening
!set name_textsubject=Zoek een oefening op een kernwoord

!set name_getsource=Hier staat de broncode van dit werkblad. U kunt deze kopieren (knippen &amp; plakken ... tussen de twee regels met "****") en hergebruiken voor een ander werkblad.

!! be careful define variable below only if module help/teacher/program work in your lang. Keep , at the same place.
!! !set name_helpprog=Vous aider de cette, correspondance indicative, entre les programmes de l'enseignement fran�ais et les exercices Wims
!set name_helpprog=$empty

