!goto $wims_read_parm

:dellevel
<div class="wims_alert warning">
<span class="wims_warning">WAARSCHUWING</span>.
De gevolgen van deze handeling zijn onherroeplijk.
En <span class="wims_warning">ALLES</span> op dit leerniveau wordt
<span class="wims_warning">DEFINITIEF</span> verwijderd:
klassen, lesprogramma's, cursussen, studenten, activiteiten, opgeslagen toetsen en alle scores !
</div><p>
Dit leerniveau verwijderen ?
</p>
!exit

:delclass
<div class="wims_alert warning">
<span class="wims_warning">WAARSCHUWING</span>.
De gevolgen van deze handeling zijn onherroeplijk.
En <span class="wims_warning">ALLES</span> uit deze klas wordt
<span class="wims_warning">DEFINITIEF</span> verwijderd:
cursussen , studenten , activiteiten , opgeslagen toetsen en alle scores !
</div><p>
Deze klas verwijderen ?
</p>
!exit

:delprog

<div class="wims_alert warning">
<span class="wims_warning">WAARSCHUWING</span>.
De gevolgen van deze handeling zijn onherroeplijk.
En <span class="wims_warning">ALLES</span> uit dit lesprogramma wordt
<span class="wims_warning">DEFINITIEF</span> verwijderd:
cursussen , activiteiten , opgeslagen toetsen en alle scores !
</div><p>
Dit lesprogramma verwijderen ?
</p>
!exit

:delcourse
<div class="wims_alert warning">
<span class="wims_warning">WAARSCHUWING</span>.
De gevolgen van deze handeling zijn onherroeplijk.
En <span class="wims_warning">ALLES</span> uit deze cursus wordt
<span class="wims_warning">DEFINITIEF</span> verwijderd:
deelnemers, activiteiten, opgeslagen toetsen en alle scores !
</div><p>
Deze cursus verwijderen ?
</p>
!exit

:delteacher
<div class="wims_alert warning">
<span class="wims_warning">WAARSCHUWING</span>.
De gevolgen van deze handeling zijn onherroeplijk.
</div><p>
Moet het docenten account <span class="tt">$del</span> ($user_firstname
$user_lastname) worden verwijderd ?
</p>
!exit

:deltest
<div class="wims_alert warning">
<span class="wims_warning">WAARSCHUWING</span>.
De gevolgen van deze handeling zijn onherroeplijk.
En <span class="wims_warning">ALLES</span> uit deze testzone wordt
<span class="wims_warning">DEFINITIEF</span> verwijderd !
</div><p>
Deze testzone verwijderen ?
</p>
!exit

:progshare

<h3 class="wimscenter">Sharing resources of another program</h3>
<div class="wims_alert warning">
Dit lesprogramma gaat alle lesmateriaal delen
(oefeningen, werkbladen, examens, documenten, enquetes en alle andere voorzieningen) met lesprogramma
<em>$other_description</em> op niveau <em>$other_level</em>. 
Dit betekend dat alle veranderingen onmiddelijk en automaitsch worden geimplementeerd in <em>$other_description</em> 
</p><p> <span class="wims_warning">$wims_name_warning</span>. 
Deze experimentele operatie zal alle bestaande lesmateriaal kunnen wissen en is <span class="wims_warning">IRREVERSIBEL</span>! 
</p>
</div><p>
Doorgaan  ?
</p>
!exit
