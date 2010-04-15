!set lang_exists=yes
!if $wims_read_parm=$empty
 !exit
!endif

!goto $wims_read_parm

:file

<p>Aanwezige bestanden in dit document:
 !for f in $flist
  !getfile doc/$f $f
  &nbsp;
 !next f
 <p>
 !form reply
 <input type=hidden name="job2" value=erase>
 Verwijder een bastand&nbsp;:
 !formselect job2 list $flist
 <input type=submit value="$wims_name_tosave">
 </form>
 <p>
 Bestanden kunnen worden opgeroepen in een document door de variabele
 <tt>\filedir</tt>. 
 Bijvoorbeeld,
<p><center>
 <tt>&lt;a&nbsp;href="\filedir/$"&gt;$f1&lt;/a&gt;</tt>
</center> <p>
 geeft de link naar het bestand <a href="$m_filedir/$f1">$f1</a>.
 Er kan ook worden geschreven:
<p><center>
 <tt>&lt;img src="\filedir/myfile.jpg" alt="myfile"&gt;</tt>
</center> <p>
om het plaatje <tt>myfile.jpg</tt> te verwerken in de pagina.
 <p>
Bestanden opgenomen in dit document zijn alleen beschikbaar voor mensen met "leesrechten" voor dit document

!exit

:readauth
Als schrijver van dit document moet u  toestemming aan de
 !mailurl $wims_site_manager systeem beheerder 

 van deze server vragen om dit document $doc openbaar te maken.
!exit

:erase1
 Alleen sitemanagers kunnen publieke documenten verwijderen.
 <p>
 Vraag
 !mailurl $wims_site_manager de sitemanager
 dit document te verwijderen.
!exit
 
:erase2
<font color=red><b>WAARSCHUWING</b>!!</font> Er is hier geen "undelete", 
dus weg is weg&nbsp;!
<p>
Weet u zeker dat het document<font color=red><b>$tit</b></font>&nbsp; moet worden verwijderd ?
!exit

:public
 <b>Opmerking</b>. U moet wel toestemming vragen aan de 
 !mailurl $wims_site_manager systeembeheerder/sitemanager\
 om dit WIMS 
 document $doc publiek te maken.
!exit

 