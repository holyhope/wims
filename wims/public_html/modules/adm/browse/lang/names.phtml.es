!set lang_exists=yes

!set name_A=todos
!set name_X=ejercicios
!set name_T=herramientas
!set name_R=matemáticas recreativas
!set name_L=referencias
!set name_S=hojas de ejercicios
!set name_P=herramientas emergentes

!if $job=subject
  !set title=Parcourir par sujet
  !set name_domain=Veuillez choisir l'un des domaines suivants.
  
  !set name_available=!nosubst Dans le domaine <i><font color=blue>$name</font></i>, les sujets suivants\
 sont disponibles.
 !set name_other=Autres domaines
!endif

!if $job=level
 !set title=Parcourir par niveau
 !distribute lines Année\
   Catégorie\
   Ecole primaire\
   Ecole secondaire\
   Université\
   3ème cycle\
   Recherche\
 into name_year,name_category,name_primary,name_secondary,name_university,name_graduate,,\
 name_research
  
!endif