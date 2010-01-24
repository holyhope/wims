!goto $wims_read_parm
:file

<p>Aanwezige bestanden in dit document:
 !for f in $flist
  !getfile doc/$f $f
  &nbsp;
 !next f
 <p>
 !form reply
 <input type=hidden name=job2 value=erase>
 Verwijder een bastand:
 !formselect job2 list $flist
 <input type=submit value=OK>
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

 van deze server vragen om dit document <tt>$doc</tt> openbaar te maken.
