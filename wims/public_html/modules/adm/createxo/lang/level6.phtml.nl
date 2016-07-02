
!read adm/title.phtml 3\
\
Binaire Bestanden voor oefeningen 

!if $quota=yes
 <span class="wims_warning">$wims_name_Error</span>.
 Er is helaas voor niet genoeg ruimte meer beschikbaar.
 <p></p>
 !goto sendend
!endif

!set wims_form_method=file
 U kunt diverse bestandstypes opsturen (plaatjes , mp3, pdf, ...)

!form reply
Het bestand voor deze oefening:
<input type="file" name="wims_deposit" />
<input type="submit" value="$wims_name_tosave" />

!formend

:sendend

!if $imglist=$empty
    Deze oefening bevat geen binaire bestanden.
!else
    Hier staat de lijst van verwerkte bestanden.
 <table class="wimsborder wimscenter">
 <tr><th>Bestandsnaam</th><th>thumbnail</th><th>-</th></tr>
 !for i in $imglist
  <tr><td>$i</td>
  <td>
  <img src="$wims_ref_name?cmd=getfile&+session=$wims_session&+special_parm=oefimg/$i" alt=""
   height="40px" width="50px" alt="" /></td>
  <td>
  !set wims_ref_class=wims_button
  !href cmd=reply&delfile=$i  $wims_name_erase
  </td>
 !next i
</tr>
 $table_end 

 !if $imgfname!=
   !set example=$imgfname
 !else
  !set example=!item 1 of $imglist
 !endif
 $wims_deposit $imgfname
 Deze bestanden zijn aan te roepen in een oefening via de
 interne parameter \imagedir.
 !set example1=!lowercase $example
 !if .gif isin $example1 or .jpg isin $example1 or .png isin $example1
   !set test_=1
 !endif
 !if $test_=1
   !set eximage=$example
 !else
   !set eximage=file.jpg
 !endif
 Bij voorbeeld, kan geschreven worden
  <pre class="wimscenter">
  !if $test_=1
 &lt;img src="\imagedir/$example"/&gt;
 !else
   &lt;a href="\imagedir/$example"&gt;$example&lt;/a&gt;.  
 !endif
  </pre>
  Voor bestanden van het type plaatje, kan geschreven worden
  <span class="tt">&lt;img src="\imagedir/$eximage"/&gt;</span>, maar ook
  <span class="tt">\img{\imagedir/$eximage}</span> of
 <span class="tt">\img{\imagedir/$eximage}{html options}</span>. Het voordeel van deze laatste methode is dat de naam van het bestand verborgen is.
 Dit gaat wel ten koste van de snelheid; en moet alleen worden gebruikt indien strict noodzakelijk.
<p>Voor alle andere bestandstypes, kan met html worden geschreven :
<span class="tt">&lt;a href="\imagedir/file.pdf"&gt;file.pdf&lt;/a&gt;</span> ...
</p>
!endif
<p class="wims_warning">
Bewaar de bestanden voor de oefening, zodat ze niet verloren gaan.
</p>
!set wims_menu_items=!append line \
testexo,1,cmd=resume&level=3&realtest=yes&retest=again\
backcreatexo,1,cmd=reply&level=3\
to $wims_menu_items
