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
!let module_copyright	=&copy; 2009 (<a href="COPYING">GNU GPL</a>)

!readproc adm/search_engine/names.$lang


!header

<div class="wims_content">
Deze interne zoekmachine maakt gebruik van zoektermen.<br />
!if $wims_class=$empty
Er kan ook gebruik worden gemaakt van de link <span class="wims_button disabled">$wims_name_browse</span> <br />
voor een overzicht van het beschikbare materiaal op deze server.
!endif
<h3>Zoekopdracht</h3>
Voer een zoekterm in en kies het type WIMS bronmateriaal waarin gezocht moet worden.<br />
<span class="small">(zoals bijvoorbeeld lesmodules, openbare werkbladen, interactieve documenten, online rekenmachines etc.)</span>
De voorkeurstaal van het gezochte materiaal kan ook worden ingevoerd.


<h5>Zoektermen</h5>
Afgezien van de gebruikelijke zoektermen kan ook bijvoorbeeld <br />
een woord als <span class="tt">levelH1</span> worden gebruikt om een lijst met materiaal te verkrijgen <br />
op middelbare school klas 1 niveau.<br />
De interne zoekmachine vergelijkt de zoekterm met de sleutelwoorden die de schrijvers van WIMS materiaal
als "keywords" voor hun werk hebben vastgesteld.
<br />
Bij het invoeren van meerdere termen, wordt een lijst met alle bronmateriaal getoond dat met beide termen is geassocieerd.

 
<h5>Materiaal</h5> 
De keuze <span class="tt">$C_A</span> zoekt in alle bronnen, behalve <span class="tt">$C_P</span> en  <span class="tt">$C_S</span><br />
De keuze <span class="tt">$C_X</span> zoekt in alle online oefeningen , zoals in <span class="tt">$C_O</span><br />
Bij de keuze <span class="tt">$C_P</span> moet er een zoekterm worden ingevoerd.

<h5>Default zoektaal</h5>
De interne zoekmachine zoekt naar materiaal in alle beschikbare talen.
Wanneer er in meerdere talen materiaal is gevonden voor de zoekopdracht,
worden de treffers getoond met in onderstaande prioriteiten volgorde: 
<ol>
<li>materiaal in de ingestelde zoektaal</li>
<li>materiaal in het engels</li>
<li>materiaal in een andere taal</li>
</ol>

<h5>Het adres van materiaal op de server</h5>
<p>
Wanneer het echte adres van WIMS lesmateriaal, zoals <span class="tt wims_address">E4/grammar/oeffonction.fr</span> bekend is
kan dit ook rechtstreeks in de zoekmachine worden ingevoerd.
</p>
</div>

!tail
