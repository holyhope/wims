
!read adm/title.phtml 3\
\
Binaire Bestanden voor oefeningen 

!if $quota=yes
 <b>Fout</b>.<br>
 Er is helaat voor Uw klas niet genoeg ruimte meer 
 beschikbaar op de harde schijf.
 <p>
 !goto sendend
!endif

!set wims_form_method=file
 U kunt diverse bestandstypes opsturen (plaatjes , mp3 ,pdf, ...)

!form reply
Het bestand voor deze oefening:
<input type=file name=wims_deposit>
<input type=submit value=OK>
</form>

:sendend

!if $imglist=$empty
    Deze oefening bevat geen binaire bestanden.
!else
    Hier staat de lijst van verwerkte bestanden.
 <p><center><table border=2>
 <th>Bestandsnaam<th>thumbnail<th>-
 !for i in $imglist
  <tr><td valign=middle align=center>$i
  <td valign=middle align=center>
  <img src="$wims_ref_name?cmd=getfile&+session=$wims_session&+special_parm=oefimg/$i" alt=""
   height=40 width=50>
  <td valign=middle align=center>
  !href cmd=reply&delfile=$i  $wims_name_erase
 !next i
 $table_end <p>
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
  <center><pre>
  !if $test_=1
 &lt;img src="\imagedir/$example"&gt;
 !else
   &lt;a href="\imagedir/$example"&gt;$example&lt;/a&gt;.  
 !endif
  </pre></center>
  Voor bestanden van het type plaatje, kan geschreven worden
  <tt>&lt;img src="\imagedir/$eximage"&gt;</tt>, maar ook
  <tt>\img{\imagedir/$eximage}</tt> of
 <tt>\img{\imagedir/$eximage}{html options}</tt>. Het voordeel van deze laatste methode is dat de naam van het bestand verborgen is.
 Dit gaat wel ten koste van de snelheid; en moet alleen worden gebruikt indien strict noodzakelijk.
<p>Voor alle andere bestandstypes, kan met html worden geschreven :
<tt>&lt;a href="\imagedir/file.pdf"&gt;file.pdf&lt;/a&gt;</tt> ...
!endif

!set wims_menu_items=!append line \
testexo,1,cmd=resume&level=3&realtest=yes&retest=again\
backcreatexo,1,cmd=reply&level=3\
to $wims_menu_items

