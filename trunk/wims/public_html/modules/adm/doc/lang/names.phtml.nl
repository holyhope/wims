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
 </p>
 !form reply
 <input type="hidden" name="job2" value="erase" />
 Verwijder een bestand&nbsp;:
 !formselect job2 list $flist
 <input type="submit" value="$wims_name_erase" />
 
!formend
 <p>
 Bestanden kunnen worden opgeroepen in een document door de variabele
 <span class="tt wims_code_variable">\filedir</span>. 
 Bijvoorbeeld,
</p><p class="wimscenter">
 <span class="tt wims_address">&lt;a href="\filedir/$f1"&gt;$f1&lt;/a&gt;</span>
</p><p>
 geeft de link naar het bestand <a href="$m_filedir/$f1">$f1</a>.
 Er kan ook worden geschreven:
</p><p class="wimscenter">
 <span class="tt wims_address">&lt;img src="\filedir/myfile.jpg" alt="myfile"&gt;</span>
</p>
om het plaatje <span class="tt wims_fname">myfile.jpg</span> te verwerken in de pagina.
De bestanden zijn alleen beschikbaar voor dit document.

</p><p>

Een nieuw commando <span class="tt wims_code_words">\href{}{}</span> is ge&iuml;ntroduceerd. 
Om een link naar een bestand aan te maken, is de onderstaande syntax afdoende:
</p>
<p class="wimscenter">
<span class="tt wims_code_words">\href{$f1}</span> of <span class="tt wims_code_words">\href{$f1}{lien}</span>.
</p>
!exit

:readauth
Er moet toestemming van de
 !mailurl $wims_site_manager systeem beheerder 
 van deze server zijn om document $doc openbaar te maken.
!exit

:erase1
 Alleen sitemanagers kunnen publieke documenten verwijderen.
 <p>
 Vraag
 !mailurl $wims_site_manager de sitemanager
 dit document te verwijderen.
 </p>
!exit

:erase2
<span class="wims_warning">WAARSCHUWING !!</span> Er is hier geen "undelete", 
dus weg is weg&nbsp;!
<p>
Weet u zeker dat het document<span class="tt wims_fname">$tit</span>&nbsp; moet worden verwijderd ?
</p>
!exit

:public
 <b>Opmerking</b>. U moet wel toestemming vragen aan de 
 !mailurl $wims_site_manager systeembeheerder/sitemanager\
 om dit WIMS 
 document $doc publiek te maken.
!exit
