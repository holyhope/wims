!set lang_exists=yes

!distribute items día(s),semana(s),mes(es),año(s),Peticiones de página,Sesiones,Sitios,\
  Número,total,media<br>diaria,media<br>por semana,media<br>por mes,media<br>por año,\
  media<br>por sitio,Media<br>semanal,Tipo de gráfica,al día,el comienzo\
into name_day,name_week,name_month,name_year,name_Requests,name_Sessions,name_Visitors,\
   name_cnt,name_total,name_avgday,name_avgweek,name_avgmonth,name_avgyear,\
   name_avgsite,name_avghebdo,name_plot,name_byday,name_beginning

!set name_requests=!lowercase $name_Requests
!set name_sessions=!lowercase $name_Sessions
!set name_visitors=!lowercase $name_Visitors

!distribute lines Elija un período para las estadísticas: a partir de \
  Mostrar también los detalles por módulos.\
  Mostrar las estadísticas\
  Detalles por módulos\
  Número de visitas desde\
  el\
  al\
  Fecha de<br>instalación\
  Sous-total\
into name_choose,name_details,name_showstat,wims_name_statdetail,name_number_visits,name_from,\
  name_to,name_installed,name_subtotal
!set title=Estadísticas de visitas
!set name_sum=!nosubst en total $laps días

!set name_prompt= peticiones<br>totales,peticiones<br>por sitio,sitios<br>totales
!set name_explanations=<ul>\
<li>El número de peticiones contabiliza únicamente peticiones de páginas.\
 Las solicitudes de módulos en desarrollo no se han contabilizado.</li>\
<li>El número de sitios visitantes cuenta una visita por día.</li>\
<li>El número de visitantes aparece entre el número de sitios y el\
    número de sesiones.</li>\
</ul>
!set name_warning=El seguimiento de visitas no está activado en este sitio. No hay estadísticas disponibles. Lo sentimos. <p>
 
 
!set name_numberclass=!nosubst  Hay $classcnt portales y clases individuales en este servidor, con\
  $usercnt cuentas de usuario en total.
  

!set format1=%d%m
!set format2=%d%m
!set format3=%m%y