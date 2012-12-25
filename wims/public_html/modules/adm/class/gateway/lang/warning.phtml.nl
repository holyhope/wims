!goto $wims_read_parm

:dellevel
<p>
<span class="wims_warning">WAARSCHUWING</span>. 
De gevolgen van deze handeling zijn onherroeplijk.
En <span class="wims_warning">ALLES</span> op dit leerniveau wordt
<span class="wims_warning">DEFINITIEF</span> verwijderd: 
klassen, lesprogramma's, cursussen, studenten, activiteiten, opgeslagen toetsen en alle scores !
</p><p>
Dit leerniveau verwijderen ?
</p>
!exit

:delclass
<p>
<span class="wims_warning">WAARSCHUWING</span>. 
De gevolgen van deze handeling zijn onherroeplijk.
En <span class="wims_warning">ALLES</span> uit deze klas wordt 
<span class="wims_warning">DEFINITIEF</span> verwijderd:
cursussen , studenten , activiteiten , opgeslagen toetsen en alle scores !
</p><p>
Deze klas verwijderen ?
</p>
!exit

:delprog

<p>
<span class="wims_warning">WAARSCHUWING</span>. 
De gevolgen van deze handeling zijn onherroeplijk.
En <span class="wims_warning">ALLES</span> uit dit lesprogramma wordt 
<span class="wims_warning">DEFINITIEF</span> verwijderd:
cursussen , activiteiten , opgeslagen toetsen en alle scores !
</p><p>
Dit lesprogramma verwijderen ?
</p>
!exit

:delcourse
<p>
<span class="wims_warning">WAARSCHUWING</span>. 
De gevolgen van deze handeling zijn onherroeplijk.
En <span class="wims_warning">ALLES</span> uit deze cursus wordt 
<span class="wims_warning">DEFINITIEF</span> verwijderd:
deelnemers, activiteiten, opgeslagen toetsen en alle scores !
</p><p>
Deze cursus verwijderen ?
</p>
!exit

:delteacher
<p>
<span class="wims_warning">WAARSCHUWING</span>. 
De gevolgen van deze handeling zijn onherroeplijk.
</p><p>
Moet het docenten account <span class="tt">$del</span> ($user_firstname
$user_lastname) worden verwijderd ? 
</p>
!exit

:deltest
<p>
<span class="wims_warning">WAARSCHUWING</span>. 
De gevolgen van deze handeling zijn onherroeplijk.
En <span class="wims_warning">ALLES</span> uit deze testzone wordt 
<span class="wims_warning">DEFINITIEF</span> verwijderd !
</p><p>
Deze testzone verwijderen ?
</p>
!exit

:progshare

<h3 class="wimscenter">Sharing resources of another program</h3>
<p>
Your program is going to share all teaching resources
(exercises, sheets, exams, documents, votes) with the program
<em>$other_description</em> in level <em>$other_level</em>. This means that
any changes to the resources in one program will be automatically reflected
in all the other sharing programs. 
</p><p> <span class="wims_warning">$wims_name_warning</span>. This experimental operation will erase existing teaching
resources in your program, and is <span class="wims_warning">IRREVERSIBLE</span>! You cannot stop the
resource sharing, and resource-sharing programs should not be deleted!
</p><p>
Are you sure you want to continue? 
</p>
!exit