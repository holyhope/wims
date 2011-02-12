!! This file contains error messages. It will be processed
!! whenever the variable `error' is not empty.

!set errorhead=<b>$wims_name_Error</b>.

!if prohibited = $error
  $errorhead Your message contains prohibited words. For example, you
  can not put some javascript in the message. Attention, this error 
  is registered by the server.
  !exit
!endif

!if forum_not_exist = $error
 $errorhead Dat forum bestaat hier niet (meer).
 !set fatal=yes
 !exit
!endif

!if no_read_right = $error
 $errorhead Je hebt geen toegang tot dit forum.
 !set fatal=yes
 !exit
!endif

!if no_subject = $error
 $errorhead Voer het onderwerp van een bericht in.
 !exit
!endif

!if translation_fail = $error
 $errorhead De software heeft helaas een interne fout , en kan het bericht niet verwerken.
 !if $wims_exec_error!=$empty
  <p>
  De fout : <tt>$wims_exec_error</tt>
 !endif
 !exit
!endif

!if open_tag = $error
 <b>$wims_name_warning</b>.
 Uw bericht bevat een niet afgesloten html-tag.<br>
 Graag controleren en verbeteren.
  <p>
 Uw bericht wordt getoond als een html-pagina, dus als U bijvoorbeeld wiskundige ongelijkheden gebruikt, geef dan een spatie achter het `&lt;' teken, 
 of gebruik de TeX manier om de wiskunde te noteren (dus gebruik \( en \) ).
 !exit
!endif

!if bad_message = $error
 $errorhead Het bericht dat U wilt lezen bestaat niet in dit forum.
 !exit
!endif

!if erased_message = $error
 $errorhead Dat bericht is verwijderd uit dit forum.
 !exit
!endif

!if $error=no_send_right
 $errorhead U mag geen bericht naar dit forum te versturen.
 <p>
 !href cmd=reply&job=list&mlist=.newlist Lijst van berichten.
 !exit
!endif

!if $error=email_required
 $errorhead U moet een werkend emailadres invullen om een bericht te kunnen opsturen.
 <br>
 <b>$wims_name_warning</b>. De server zal het opgegeven adres kontroleren.
 !set job=compose
 !exit
!endif

!if $error=bad_email
 $errorhead U hebt geen geldig emailadres ingevuld.Graag corrigeren 

 !set job=compose
 !exit
!endif

!if $error=bad_sendcode
 $errorhead Het bericht kan niet worden opgenomen in het forum, omdat de
 geheime code niet correct is ingevuld.
 <p>
Kontroleer het opgegeven emailadres, klik op de "versturen knop" en haal dan
per email de <b>nieuwe</b> geheime code op. 
 !set job=compose
 !exit
!endif

!if $error=not_owner
 $errorhead Alleen de eigenaar van dit forum mag het configureren
 <p>
 !set job=list
 !exit
!endif

!if auth_failure = $error
 $errorhead  Aanmelden is mislukt!. <p>
 !set fatal=yes
 !exit
!endif

!msg $error

