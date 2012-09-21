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
  
  !set name_available=!nosubst Op domein  <i><font color=blue>$name</font></i>, \
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