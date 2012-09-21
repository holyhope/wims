!set lang_exists=yes

!set name_A=todos
!set name_X=ejercicios
!set name_T=herramientas
!set name_R=matemáticas recreativas
!set name_L=referencias
!set name_S=hojas de ejercicios
!set name_P=herramientas emergentes

!if $job=subject
  !set title=Búsqueda por tema
  !set name_domain=Por favor, seleccione una de las siguientes áreas.

  !set name_available=!nosubst En la área <i><font color=blue>$name</font></i>, los siguientes temas\
 están disponibles.
 !set wims_name_other=Otras áreas
!endif

!if $job=level
 !set title=Búsqueda por nivel
 !distribute lines Año\
   Categoría \
   Escuela primaria \
   Secondaria\
   Universidad\
   3er ciclo\
   Investigación \
 into name_year,name_category,name_primary,name_secondary,name_university,name_graduate,,\
 name_research

!endif
