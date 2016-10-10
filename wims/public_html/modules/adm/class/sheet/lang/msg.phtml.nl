!set wims_module_log=error: $error

!if not_supervisor=$error
 Helaas, maar het maken en/of veranderen van een werkblad is voorbehouden aan de supervisor van een klas
 !exit
!endif

!if bad_series=$error
 Vreemd, ik kan geen serie oefeningen vinden om te veranderen !
 !exit
!endif

!if bad_source=$error
 Het item nummer $bad_source in de  zojuist ingevoerde code is ongeldig.
 !href cmd=reply&job=prep_putsource&source=$source Verbeter deze code
 .
 !exit
!endif

!if active_sheet=$error
    Dit werkblad is aktief. De inhoud ervan kan niet meer worden veranderd.
!exit
!endif

!if bad_sheet=$error
Uw werkblad nummer is niet geldig. Een bug in de software?
 !exit
!endif

!if bad_maxsheet=$error
 Het maximum aantal werkbladen is ingesteld op $max_sheets. Er kan geen nieuw werkblad meer worden aangemaakt.
 !exit
!endif

!if no_title=$error
    U wilt een werkblad registreren zonder titel, dat is niet handig...foutje of misbruik?
 !exit
!endif

!if $error=not_secure
Deze operatie mag alleen worden uitgevoerd van af een veilig ip-adres.
 !if $sec=$empty
  Verboden toegang.
  U hebt geen veilige ip-adressen gedefinieerd. De sitemanager kan dit regelen.
 !else
  Verboden toegang.
 !endif
 !exit
!endif

!if $error=sharing_sheet
    Deze werkbladen worden gedeeld met een andere klas !
 !if $wims_ismanager<2
    U zult de oprichter van dit instituut moeten vragen het werkblad te deactiveren.
  !exit
 !endif
 U loopt het risico dat er hierdoor in andere klassen ongeldige werkbladen of toetsen ontstaan.
 <p>
  Doorgaan met deze procedure?
</p><div class="wimscenter">
 !href cmd=reply&job=deactivate&confirm=yes $wims_name_yes; $(wims_name_actionlist[3])
 .&nbsp;&nbsp;
 !href cmd=resume $wims_name_no; $wims_name_giveup
 . </div>
 <b>Het is verstanding om collega's eerst een backup te laten maken van hun klassen.</b>
 !exit
!endif

!if $error=sheet_in_exam
    Het is onmogelijk dit werkblad te deactiveren: er zijn proefwerken aangemeekt op basis van dit werkblad.
 !exit
!endif

!if $error=non_empty_activities
 U wilt het werblad $sheet deactiveren, maar er zijn al studenten mee aan het werk geweest.

 !if share iswordof $confirmed
     En dit werkblad wordt ook gedeeld mat andere klassen.
     Onmogelijk nu te deactiveren.
  !exit
 !endif
 Alle behaalde cijfers voor dit werblad worden verwijderd, indien U het deactiveerd.
 Doorgaan ?
  <div class="wimscenter">
 !href cmd=reply&job=deactivate&confirm=yes $wims_name_yes; $(wims_name_actionlist[3])
 .&nbsp;&nbsp;
 !href cmd=resume $wims_name_no; $wims_name_giveup
 . </div>
 Lijst van deelnemers die aan dit werblad heben gewerkt:
 <p>
 <span class="tt">$worktest</span>
 </p>
 <b>Opmerking</b>.
 Deze handeling moet eigenlijk niet worden uitgevoerd in een actieve klas !.
 En is bedoeld voor "test klassen"
 !exit
!endif

!if prep_activate=$error
U wilt het werkblad $sheet laten activeren, zodat Uw leerlingen hiermee kunnen werken.
Onthoud dat een eenmaal geactiveerd werkblad, niet meer kan worden veranderd !

!if $test_expire!=$empty
  <div class="wims_warning">
   De einddatum van het werkblad is verlopen; het wordt nu gezet op de vervaldatum van uw klas.
  </div>
 !endif
 Wilt U doorgaan?
  <div class="wimscenter">
 !href cmd=reply&job=activate $wims_name_yes; $(wims_name_actionlist[1])
 .&nbsp;&nbsp;
 !href cmd=resume $wims_name_no; $wims_name_giveup
 .</div>
 !exit
!endif

!if prep_erase=$error
Weet U zeker dat U het werkblad nummer $sheet ($title) wilt verwijderen?
  <div class="wimscenter">
 !set wims_ref_class=wims_button wims_warning
 !href cmd=reply&job=erase $wims_name_yes; $wims_name_erase
 !set wims_ref_class=wims_button
 !href cmd=resume $wims_name_no ; $wims_name_giveup
</div>
 !exit
!endif

!if prep_expire=$error
Dit werkblad nummer $sheet ($title) was normaal verlopen op $expday
 !item $expmon of $months
 $expyear.
 U wilt het <b>nu</b> laten verlopen?

  <div class="wimscenter">
 !href cmd=reply&job=expire $wims_name_yes ; $(wims_name_actionlist[2])
 .&nbsp;&nbsp;
 !href cmd=resume $wims_name_no ; $wims_name_giveup
 . </div><b>Opmerking.</b>
 Uw studenten kunnen niet doorgaan met werken aan een verlopen werkblad.
 Maar hun reeds behaalde cijfers worden uiteraard bewaard (en worden dus ook
 verwerkt in de statistieken) en U kunt ze altijd later nog bestuderen.
 !exit
!endif

!if prep_putsource=$error
Hebt U een broncode van een reeds eerder gemaakt werkblad, kan deze
in het onderstaande venster worden ingevoerd. Daarna klikken op "Sturen".
Uiteraard kan ook met "knippen &amp; plakken" worden gewerkt.

 !set wims_menu_items=!append line sheetadmin,1,cmd=resume \
to $wims_menu_items

 !form reply
 <input type="hidden" name="job" value="putsource" /><p class="wimscenter">
 <textarea cols="55" rows="10" name="source">$source</textarea>
 </p>
 <p class="wimscenter"><input type="submit" value="$wims_name_send" />
 </p>
!formend
 <span class="wims_warning">$wims_name_warning</span>.
 Voer geen "corrupte code" handmatig in ; het risico
 bestaat dat het werkblad onbruikbaar wordt.

 !exit
!endif

!if prep_modify=$error
 !set cnt=!recordcnt wimshome/log/classes/$wims_class/sheets/.sheet$sheet
 !if $modif>$cnt or $modif<1
 Uw verzoek is niet toegestaan.
 !else
  !set exo=!record $modif of wimshome/log/classes/$wims_class/sheets/.sheet$sheet
  !changeto exomodify.phtml $exo
 !endif
 !exit
!endif

!if $error=toolate
!read adm/lang/date.phtml.$moduclass_lang $class_expiration
 <p>$name_expiration1 ($l_date_out). $name_expiration2 </p>
 !set wims_ref_class=wims_button
 !href cmd=resume $wims_name_back2
 ($wims_name_sheetmanagement)
 !exit
!endif

!if $error=srcnoexo
 Dit werkblad bevat geen enkele oefening en is daardoor leeg...<br />
 !href cmd=resume terug naar de werkblad aanmaak pagina
 !exit
!endif

!msg $error
