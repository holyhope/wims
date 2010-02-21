
<center><h3>Browsen langs de naslagwerken en alle andere hulpmiddelen<br>
op deze server</h3></center>
<p>
De volgende hulpmiddelen staan op deze server ter beschikking. 


<ol class="wims_browse_type_list">
<li class="wims_browse_type_list">Naslagwerk:<br>
 The
 !if $wims_pedia_type=1 and $wims_pedia_address!=$empty
  <a href=$wims_pedia_address?module=adm/enc&cmd=new>Distributed Encyclopedia of Sciences</a>
  ($wims_pedia_address)
 !else
  !href module=adm/enc Distributed Encyclopedia of Sciences
 !endif
 bevat lijsten van de beste internet bronnen over elk onderwerp.


</li><li class="wims_browse_type_list">Online rekenmachines en functieplotters: onder andere, 
 <ul>
 <li class="wims_browse_type_list">
  !set cat=T
  !reset key
  !href $search_addr Alle beschikbare online tools
  op volgorde van populariteit
 </li><li class="wims_browse_type_list">
  Rekenmachines:
  !set cat=P
  !set key=number, complex, roots
  !href $search_addr simpele popup rekenmachine
  (simplify, breuken, conversies, factorisatie, complexe getallen, etc.) en
  diverse
  !set cat=T
  !set key=number, roots
  !href $search_addr specialistische calculators
  (integers, continued fraction, positive characteristics, etc.)
 </li><li class="wims_browse_type_list">
  Analysis
  !set key=analysis, calculus, functions
  !set cat=P
  !href $search_addr popup tools
  and
  !set cat=T
  !href $search_addr calculators
  voor alles wat je zou willen weten over rekeken en functies:
, afgeleide, integraal, limiet, minimum/maximum, wortels,rijen en reeksen,
  Fourier en Laplace transformaties, etc.
 </li><li class="wims_browse_type_list">
  !set cat=T
  !set key=linear algebra
  !href $search_addr Lineaire algebra calculators
  $ : lineaire systemen, matrices, determinant, vector ruimtes, etc.
 </li><li class="wims_browse_type_list">
  !set cat=T
  !set key=plotter
  Verschillende plotters:
  !href $search_addr sophisticated tools
  vaak met animaties en voorbeelden, of
  !set cat=P
  !href $search_addr snelle popup plotters
. Die zeer snel een kurve,oppervlakte rijen/reeksen kunnen printen

 </li><li class="wims_browse_type_list">
  !set cat=T
  !set key=statistics, data
  !href $search_addr Statistiek calculators
$ : gemiddelden en standaard afwijkingen, histogrammen, regressie, ...
 </li></ul>
 
</li><li class="wims_browse_type_list">Interactieve oefeningen: oefeningen op WIMS in zeer verschillende uitvoeringen ,
zoals bijvoorbeeld:
 <ul>
 <li class="wims_browse_type_list">
  !set cat=X
  !reset key
  !href $search_addr Alle beschikbare oefeningen
  op volgorde van popularteit.
  </li><li class="wims_browse_type_list">
  !set key=graphic choices
  !href $search_addr Grafische meerkeuze vragen
  van het type "klik op het goede plaatje"
    
 </li><li class="wims_browse_type_list">
  !set key=shoot
  !href $search_addr Schiet oefeningen
  Hier moet je een onzichtbaar punt proberen te raken/klikken, en wordt
  je beoordeeld op de precisie 
  </li><li class="wims_browse_type_list">
  !set key=draw
  !href $search_addr Teken oefeningen
  Hier moet je proberen de juiste curve tekenen met je muis. 
  
  </li><li class="wims_browse_type_list">
  !set key=coincidence
  !href $search_addr herken de curve oefeningen
  Er wordt je een curve getoond, je hebt meerdere kansen om de
  juiste vergelijking van deze curve te achterhalen
  </li><li class="wims_browse_type_list">
  !set key=deductio
  !href $search_addr Deductio oefeningen
  Oefeningen met interactieve bewijsvoering/logica 

  </li><li class="wims_browse_type_list">
  !set key=dialog
  !href $search_addr Dialoog oefeningen
  Hier kun je de server vragen stellen om een bepaald wiskundig probleem op te lossen
  Je wordt gestraft voor onzinnige vragen (...)
 
  </li><li class="wims_browse_type_list">
  !set key=scenario
  !href $search_addr Scenario oefeningen
  Er worden random en mogelijk ook foute redeneringen getoond, jij moet 
  uitvinden waar de crux zit
  
  </li><li class="wims_browse_type_list">
  !set cat=O
  !reset key
  !href $search_addr OEF oefeningen
  (Open Exercise Format)
  Dit is een verzameling  online ontwikkelde oefeningen.
  De vragen kunnen random zijn , de antwoorden  kunnen multiple choice, getallen
  functies ,text enz zijn.
   
  </li><li class="wims_browse_type_list">
  !set cat=X
  !set key=contrib
  !href $search_addr Diverse Oefeningen
  gedoneerd door diverse leraren en scholen

 </li></ul>
 Je kunt natuurlijk ook de oefeningen  
 !href module=$module&cmd=new&job=subject per onderwerp browsen
.
</li><li class="wims_browse_type_list">Mathematical recreations: 
 !set cat=R
 !reset key
 !href $search_addr gesorteerd naar populariteit.

</li></ol>
