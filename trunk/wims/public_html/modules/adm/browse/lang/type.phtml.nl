!read adm/title.phtml 3\
Browsen langs de naslagwerken en alle andere hulpmiddelen\
op deze server


De volgende hulpmiddelen staan op deze server ter beschikking. 


<ol class="wims_browse_type_list">
<li>Online rekenmachines en functieplotters: onder andere, 
 <ul class="wims_browse_type_list"">
 <li>
  !set cat=T
  !reset key
  !href $search_addr Alle beschikbare online tools
  op volgorde van populariteit
 </li><li>
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
 </li><li>
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
 </li><li>
  !set cat=T
  !set key=linear algebra
  !href $search_addr Lineaire algebra calculators
  $ : lineaire systemen, matrices, determinant, vector ruimtes, etc.
 </li><li>
  !set cat=T
  !set key=plotter
  Verschillende plotters:
  !href $search_addr sophisticated tools
  vaak met animaties en voorbeelden, of
  !set cat=P
  !href $search_addr snelle popup plotters
. Die zeer snel een kurve,oppervlakte rijen/reeksen kunnen printen

 </li><li>
  !set cat=T
  !set key=statistics, data
  !href $search_addr Statistiek calculators
$ : gemiddelden en standaard afwijkingen, histogrammen, regressie, ...
 </li></ul>
 
</li><li>Interactieve oefeningen: oefeningen op WIMS in zeer verschillende uitvoeringen ,
zoals bijvoorbeeld:
 <ul>
 <li>
  !set cat=X
  !reset key
  !href $search_addr Alle beschikbare oefeningen
  op volgorde van popularteit.
  </li><li>
  !set key=graphic choices
  !href $search_addr Grafische meerkeuze vragen
  van het type "klik op het goede plaatje"
    
 </li><li>
  !set key=shoot
  !href $search_addr Schiet oefeningen
  Hier moet je een onzichtbaar punt proberen te raken/klikken, en wordt
  je beoordeeld op de precisie 
  </li><li>
  !set key=draw
  !href $search_addr Teken oefeningen
  Hier moet je proberen de juiste curve tekenen met je muis. 
  
  </li><li>
  !set key=coincidence
  !href $search_addr herken de curve oefeningen
  Er wordt je een curve getoond, je hebt meerdere kansen om de
  juiste vergelijking van deze curve te achterhalen
  </li><li>
  !set key=deductio
  !href $search_addr Deductio oefeningen
  Oefeningen met interactieve bewijsvoering/logica 

  </li><li>
  !set key=dialog
  !href $search_addr Dialoog oefeningen
  Hier kun je de server vragen stellen om een bepaald wiskundig probleem op te lossen
  Je wordt gestraft voor onzinnige vragen (...)
 
  </li><li>
  !set key=scenario
  !href $search_addr Scenario oefeningen
  Er worden random en mogelijk ook foute redeneringen getoond, jij moet 
  uitvinden waar de crux zit
  
  </li><li>
  !set cat=O
  !reset key
  !href $search_addr OEF oefeningen
  (Open Exercise Format)
  Dit is een verzameling  online ontwikkelde oefeningen.
  De vragen kunnen random zijn , de antwoorden  kunnen multiple choice, getallen
  functies ,text enz zijn.
   
  </li><li>
  !set cat=X
  !set key=contrib
  !href $search_addr Diverse Oefeningen
  gedoneerd door diverse leraren en scholen

 </li></ul>
 Je kunt natuurlijk ook de oefeningen  
 !href module=$module&cmd=new&job=subject per onderwerp browsen
.
</li><li>Mathematical recreations: 
 !set cat=R
 !reset key
 !href $search_addr gesorteerd naar populariteit.

</li></ol>
