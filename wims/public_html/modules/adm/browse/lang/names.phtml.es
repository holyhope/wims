!set lang_exists=yes

!set name_A=todos
!set name_X=ejercicios
!set name_T=herramientas
!set name_R=matemáticas recreativas
!set name_L=referencias
!set name_S=hojas de ejercicios
!set name_P=herramientas emergentes

!set name_M=module(s)

!set wims_name_credits=Credits

!if $job=subject
  !set title=Búsqueda por tema
  !set name_domain=Por favor, seleccione una de las siguientes áreas.

  !set name_available=!nosubst En la área <span class="wims_emph">$name</span>, los siguientes temas\
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
   Levels \
 into name_year,name_category,name_primary,name_secondary,name_university,name_graduate,\
 name_research,name_levels

!endif

!distribute lines Usted puede explorar el contenido de este sitio web siguiendo varios métodos.\
  Por área\
  Por nivel educativo\
  escuela primaria, secundaria y bachillerato, universidad, etc.\
  Por fecha\
  las últimas incorporaciones al servidor.\
  Et pouvez également utiliser les sélections faites pour vous.\
  Por tipo de recursos\
  herramientas gráficas y de cálculo, ejercicios, referencias, etc.\
  Una breve introducción\
  a alguna de las mejores actividades del servidor.\
  Correspondance indicative\
  avec les programmes de l'enseignement français\
  Fold / Unfold\
  By taxonomy\
  popular applications\
into name_h_browse,name_by_subject,name_by_level,name_by_level2,name_by_date,name_news,\
  name_selected,name_by_type,name_by_type2,name_introduction,name_thebest,name_french1,\
  name_french2,name_fold,name_by_taxo,name_best
