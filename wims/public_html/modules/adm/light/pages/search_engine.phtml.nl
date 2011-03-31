!!INDEX
!! Erase the above line to hide your page from wims search engine.
!! Line starting with double exclamations are comment lines.
!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!
!! Indexing definitions. You should modify them according to your case.
!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

!! Put every definition in ONE LINE!!
!let module_author	=
!let module_address	=
!let module_title	=Zoek machine
!let module_description	=
!let module_language	=$lang

!!Your copyright policy.
!!Your page will be included in wims distribution if the word `GNU'
!! appears in the following definition.
!let module_copyright	=&copy; 2009 (<a href=COPYING>GNU GPL</a>)

!readproc adm/search_engine/names.$lang


!header

Deze interne zoekmachine maakt gebruik van zoektermen.<br>
Er kan ook gebruik worden gemaakt van de link <span class="wims_button disabled">$wims_name_browse</span> <br>
voor een overzicht van het beschikbare materiaal op deze server.
<p>
<h3>Zoekopdracht</h3>
Voer een zoekterm in en kies het type WIMS bronmateriaal waarin gezocht moet worden.<br>
<small>(zoals bijvoorbeeld lesmodules, openbare werkbladen, interactieve documenten, online rekenmachines etc.)</small>
De voorkeurstaal van het gezochte materiaal kan ook worden ingevoerd.
</p>
<p>
<h5>Zoektermen</h5>
Afgezien van de gebruikelijke zoektermen kan ook bijvoorbeeld <br>
een woord als <tt>levelH1</tt> worden gebruikt om een lijst met materiaal te verkrijgen <br>
op middelbare school klas 1 niveau.<br>
De interne zoekmachine vergelijkt de zoekterm met de sleutelwoorden die de schrijvers van WIMS materiaal
als "keywords" voor hun werk hebben vastgesteld.
<br>
Bij het invoeren van meerdere termen, wordt een lijst met alle bronmateriaal getoond dat met beide termen is geassocieerd.
</p>
<p> 
<h5>Materiaal</h5> 
De keuze <tt>$C_A</tt> zoekt in alle bronnen, behalve <tt>$C_P</tt> en  <tt>$C_S</tt><br>
De keuze <tt>$C_X</tt> zoekt in alle online oefeningen , zoals in <tt>$C_O</tt><br>
Bij de keuze <tt>$C_P</tt> moet er een zoekterm worden ingevoerd.
</p>
<p>
<h5>Default zoektaal</h5>
De interne zoekmachine zoekt naar materiaal in alle beschikbare talen.
Wanneer er in meerdere talen materiaal is gevonden voor de zoekopdracht,
worden de treffers getoond met in onderstaande prioriteiten volgorde: 
<ol>
<li>materiaal in de ingestelde zoektaal
<li>materiaal in het engels
<li>materiaal in een andere taal
</ol>
</p>
!tail
