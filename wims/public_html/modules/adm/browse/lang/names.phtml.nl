!set lang_exists=yes

!set name_A=allemaal
!set name_X=oefeningen
!set name_T=hulpmiddelen
!set name_R=ontspanning
!set name_L=referenties
!set name_S=werkbladen
!set name_P=popup hulpmiddelen

!if $job=subject
  !set title=Browsen per onderwerp
  !set name_domain= Kies een van de volgende onderwerpen. 
  
  !set name_available=!nosubst Op domein  <span class="wims_emph">$name</span>, \
  zijn de volgende onderwerpen aanwezig
 !set wims_name_other= Andere domeinen
!endif

!if $job=level
 !set title=Browsen op leerniveau
 !distribute lines jaar\
   Categorie\
   Lagere school\
   Middelbare school\
   Universiteit\
   Promovendus\
   Research\
 into name_year,name_category,name_primary,name_secondary,name_university,name_graduate,,\
 name_research
  
!endif

!distribute lines Je kunt de inhoud van deze website op diverse manieren benaderen:\
  Onderwerp\
  Moeilijkheids graad\
  lagere school, middelbare school, universiteit, etc.\
  Datum\
  laatste nieuwtjes op deze server\
  Et vous pouvez également utiliser les sélections faites pour vous.\
  Soort \
  references, computational en plotting tools, oefeningen, enz.\
  populairste toepassing\
  \
  Correspondance indicative\
  avec les programmes de l'enseignement français\
into name_h_browse,name_by_subject,name_by_level,name_by_level2,name_by_date,name_news,\
  name_selected,name_by_type,name_by_type2,name_introduction,name_thebest,name_french1,\
  name_french2
