!set lang_exists=yes
!set name_user=!nosubst $wims_firstname $wims_lastname.
!set monthnames=jan,feb,maart,apr,mei,juni,juli,aug,sept,okt,nov,dec
!set name_wroteon=schreef op
!set name_default=Forum 
!distribute item <i>onderwerp&nbsp;:</i> <b>,</b> into subj1,subj2
!distribute item <hr>,<hr> into body1,body2

!distribute line Lijst van berichten op datum\
Lijst van berichten op discussie volgorde\
Lees bericht\
Nieuw bericht\
Schrijf een reactie\
Bekijk het concept bericht\
Stuur een bericht\
Configuur dit forum\
Lijst van berichten op onderwerp\
into n_list,n_thread,n_read,n_compose,n_follow,n_preview,n_send,n_config,n_subjectlist

!set wims_name_compose=$n_compose
!set n_otherforums=Andere forums
!set n_welcome=Welkom
!set n_list_subject_month =Lijst van onderwerpen uit maand
!set n_email=email
!set n_list_month = Berichten van deze maand
!set n_most=het meest
!set n_old=recentste eerst,oudste eerst
!set n_new=Nieuw bericht
!set n_archives=Maandelijks Archief&nbsp;
!set n_following=volgende bericht
!set n_reverse=Draai de volgorde om
!set n_recent=Recenste bericht
!set n_erased=gewist
!set n_send=Stuur het bericht
!set n_edit=Terug naar "edit"
!set n_emptymsg=Uw bericht is leeg&nbsp;
!set n_listforum=Lijst van forums op deze server.
!set n_by=door
!set n_newfollow=Nieuwe reactie
!set n_subject=Onderwerp&nbsp;
!set n_content=Inhoud&nbsp;
!set n_preview=Bekijken
!set n_send0=Versturen
!set n_origin=Originele bericht
!set n_help=Help
!set n_mathhelp=om wiskundige formules te verwerken in het bericht.
!set n_yourname=Uw naam&nbsp;
!set n_cautious=<b>Attentie.</b>\
 Uw bericht wordt alleen verstuurd als U een geldig emailadres hebt opgegeven.
!set n_anonymous=Anonieme bezoeker.
!set n_emptyforum=Dit forum is leeg.
!set n_nomessage=Helaas, geen passend bericht gevonden.
!set n_erasedmsg=Bericht gewist
!set n_with=met
!set n_or=of
!set n_without=zonder
!set n_citation=citaat
!set n_source=Broncode
!set n_format=Geformateerd
!set n_erase=Wissen
!set n_follow_c=Reageer (citeer)
!set n_follow_nc=Reageer (zonder citaat)
!set n_add=Uw bericht is toegevoegd aan dit forum.
!set n_bydate=Op datum
!set n_bysubject=Op onderwerp
!set n_prec=Voorgaande
!set n_first=eerste reactie
!set n_allfollowing=alle reacties
!set n_statusask=Dit forum accepteerd geen anonieme berichten.<br>\
Het bewaakt wel uw ingevulde email adres, zodat er geen misbruik van kan worden gemaakt.<br>\
Om het opgegeven email adres te verifieren, wordt nu een code gestuurd naar dit adres.<br>\
Vul deze code hier in&nbsp;
!set n_warning=Een bericht is zojuist verstuurd naar het forum. Nier reageren op dit bericht.
!set n_forum=Forum
!set n_thread=De hele discussie
!if $job=compose and $c_prec!=$empty
 !set n_compose=Beantwoorden
!endif

!if $job notwordof read list config
 !set nextline=</b> <br>--- $(n_$job) ---
!endif

!set module_title=$module_title$nextline

!set name_prompt=Onbekende activiteit

!distribute line Hier kan het forum worden afgesteld.\
Wie mag deze berichten lezen&nbsp;\
  alle deelnemers, alleen ikzelf\
  iedereen,deelnemers,alleen ikzelf\
  Wie mag berichten schrijven&nbsp;\
  alle deelnemers,alle deelnemers met een geldig emailadres,alleen ikzelf\
  iedereen met een geldig emailadres,alle deelnemers,alle deelnemers met een geldig emailadres,alleen ikzelf\
into name_introconfig, name_whoread,name_prompt1,name_prompt2,name_whosend,name_prompt3,name_prompt4

