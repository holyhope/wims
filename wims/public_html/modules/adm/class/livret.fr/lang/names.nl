!let lang_exists=yes
!set classname=<b><font color=green>$wims_classname</font></b>\
 van <b><font color=green>$wims_institutionname</font></b>

!set months=Jan,Feb,Mar,Apr,Mei,Jun,Jul,Aug,Sept,Okt,Nov,Dec

!distribute items Bekwaamheid,\
bekwaamheid,\
Bekwaamheden,\
bekwaamheden,\
Prestiatieniveau,\
Prestatieniveaus,\
prestatieniveau,\
prestatieniveaus,\
Alle,\
into name_Competence,name_competence,name_Competences,name_competences,name_n_Palier,name_n_Paliers,name_n_palier,name_n_paliers,name_all

!set name_no_competence=Er staat geen enkele $name_competence vermeld in dit rapport !
!set name_noyetparticipant=Deze klas heeft geen studenten.
!set name_info=Informatie over deze $name_competence &nbsp;
!set name_param_change=Hier staan de instel-parameters waaruit u kunt kiezen&nbsp;
!set name_color=De kleur van de prestaties van $name_n_palier &nbsp;
!set name_score_modify=Cijfers voor oefeningen uit de volgende werkbladen, benodigd voor de berekening van de prestatieniveaus van $name_n_paliers &nbsp;
!set name_cocher=Controleer de gegevens die gebruikt moeten worden in het overzicht van $name_n_palier.
!set name_see=Toon alleen de werkblad oefeningen.


!distribute items Titel van de $name_comptence&nbsp;,\
Titel van $name_n_palier&nbsp;,\
Aantal $name_n_paliers&nbsp;,\
van de klas,\
minimale score voor dit onderdeel\
into name_title_comp,name_title_palier,name_cnt_palier,name_configtext2,name_configtext3

!! ----------------------------------------------   ajout pour la version 1.04
!let name_nowork=Geen werk
!distribute line Welke kleuren voor het $name_n_paliers niveau\
Laat het $name_n_paliers  niveau zien \
into name_configtext4,name_configtext5

!let name_listscoreoption=van de klas,van het raport boekje
!let name_listscoreview=niet laten zien,integer,op &eacute;&eacute;n decimaal,op twee decimalen,op drie decimalen,op vier decimalen

!!------------------------------- definition des noms de liens pour wims_menu_items

!if $wims_user=supervisor
 !let tmp=!defof SE_list in wimshome/public_html/modules/home/names.$lang
!else 
 !let tmp=!defof U_myscore in wimshome/public_html/modules/home/names.$lang
!endif

!distribute line Nieuwe vaardigheid\
$tmp\
Rapport van deze klas\
Rapport van $name_competences\
 into wims_name_add_competence,wims_name_go_userlist,wims_name_cls_livret,wims_name_livret

!if $job=addcomp
 !set name_job=!nosubst Toevoegen / bewerken van $name_competence $comp
 !exit
!endif

!if $job=modpalier
  !set name_job=!nosubst Verander de $name_n_palier $palier (<font color=green>$name_palier</font>) in de $name_competence $comp (<font color=green>$name_comp</font>).
  !exit
!endif

!if $job=user
  !set name_job=!nosubst <font color=green>$user_firstname $user_lastname</font>
!endif

