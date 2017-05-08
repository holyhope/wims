!set lang_exists=yes

!set name_A=todos
!set name_X=ejercicios
!set name_T=herramientas
!set name_R=matemáticas recreativas
!set name_L=referencias
!set name_S=hojas de ejercicios
!set name_P=herramientas rápidas

!set name_M=módulo(s)

!set wims_name_credits=Créditos

!if $job=subject
  !set title=Búsqueda por tema
  !set name_domain=Por favor, seleccione una de las siguientes áreas.
  !set job_desc=Cada módulo educativo tiene asociadas unas palabras clava. \
   Encontrareis debajo todas estas palabras clave, organizadas en árbol. \
<br class="spacer"/>\
Sin embargo, las cifras no tienen en cuenta las subramas. \
Cada punto indica el número de módulos a los que se asigna la palabra clave correspondiente.

  !set name_available=!nosubst En el área <span class="wims_emph">$name</span>, los siguientes temas\
 están disponibles.
 !set wims_name_other=Otras áreas
!endif

!if $job=taxo
  !set title=Búsqueda por taxonomía
  !set job_desc=Una parte de los módulos de WIMS se han clasificado en algunas taxonomías \
   clásicas, las pueden encontrar a continuación.\
  <br class="spacer" />\
  Aquí, los números que aparecen representan el número de\
   módulos contenidos en las subramas.
!endif

!if $job=level
 !set title=Búsqueda por nivel
 !distribute lines Año\
   Categoría \
   Escuela primaria \
   Secundaria y Bachillerato\
   Universidad\
   3er ciclo\
   Investigación \
   Niveles \
 into name_year,name_category,name_primary,name_secondary,name_university,name_graduate,\
 name_research,name_levels

!endif

!distribute lines Usted puede explorar el contenido de este sitio web siguiendo varios métodos.\
  Por tema\
  Por nivel educativo\
  escuela primaria, secundaria y bachillerato, universidad, etc.\
  Por fecha\
  las últimas incorporaciones al servidor.\
  Y puede también utilizar las selecciones hechas para usted.\
  Por tipo de recursos\
  herramientas gráficas y de cálculo, ejercicios, referencias, etc.\
  Una breve introducción\
  a alguna de las mejores actividades del servidor.\
  Correspondencia indicativa\
  con los programas de la educación francesa\
  Reducir/Ampliar\
  Por taxonomía\
  aplicaciones populares\
into name_h_browse,name_by_subject,name_by_level,name_by_level2,name_by_date,name_news,\
  name_selected,name_by_type,name_by_type2,name_introduction,name_thebest,name_french1,\
  name_french2,name_fold,name_by_taxo,name_best
