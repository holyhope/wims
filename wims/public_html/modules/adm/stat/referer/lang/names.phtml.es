!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif
!set name_site=el sitio
!set name_stem=una página en la dirección
!set name_uniq=la página
!set names_site=sitios
!set names_stem=directorio de sitios
!set names_uniq=páginas

!distribute items día(s),semana(s),mes(es),año(s),el inicio\
  into name_day,name_week,name_month,name_year,name_begining
  
!distribute lines sitio\
  directorio base\
  dirección completa\
  Los enlaces se pueden listar por\
  de la página web, y la lista limitarse a las\
  direcciones primeras. Las direcciones de los motores de búsqueda pueden ser\
  incluidas o\
  excluidas de la lista\
  Opcionalmente, puede restringir la lista a los sitios/páginas que contengan el término\
 Facultativement, vous pouvez restreindre la liste aux sites/pages contenant un mot\
into name_site1,name_stem,name_uniq,name_listlink,name_limited,name_searchengine,\
 name_included,name_excluded,name_option
 
!set name_list1=!nosubst Lista de web $(names_$type) que dirigen a visitantes hacia nosotros, \
  en el periodo de
   
!set name_sum=!nosubst en total $laps días

!set name_list2=>La primera columna muestra el número de visitantes que siguieron\
un enlace en $(name_$type) de la segunda columna.
  
!set name_visit1=personas que nos han visitado a través de enlaces de
!set name_visit2=!nosubst Al menos $auto otras visitas no especificaron referencias a páginas\
 públicas. Las páginas que tienen como referencia $httpd_HTTP_HOST no se han contado.

!set title=Lista de enlaces inversos

!set name_warning=El registro de enlaces inversos (referers) de las cabeceras http no está \
activado en este sitio. No está disponible la lista de enlaces inversos. Lo sentimos.
 
!set name_choose=Periodo del listado: a partir de

:exit
:intro
En general una página web que nos envíe muchos invitados será un lugar
interesante para el resto de nuestros visitantes. Es lógico, si busca recursos
web relacionados con este servidor, lo que necesita es una lista de tales
páginas.
<p>
Por otro lado, si es usted el autor de una página con enlace(s) a nosotros,
esta lista le permitirá medir la eficacia de su vínculo. Es también nuestra
manera de agradecerle el enlace.
<p>
Nuestra lista de enlaces inversos se genera dinámicamente, según los parámetros que
puede elegir en el siguiente menú.