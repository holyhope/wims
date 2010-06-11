!set lang_exists=yes

!distribute items day(s),week(s),month(s),year(s),Requests,Sessions,Visiting sites,\
  Number,total,average<br>per jour,average<br>per week,average<br>per month,average<br>per année,\
  average<br>per site,Weekly<br>average,Type of the plot,Daily,the beginning\
into name_day,name_week,name_month,name_year,name_Requests,name_Sessions,name_Visitors,\
   name_cnt,name_total,name_avgday,name_avgweek,name_avgmonth,name_avgyear,\
   name_avgsite,name_avghebdo,name_plot,name_byday

!set name_requests=!lowercase $name_Requests
!set name_sessions=!lowercase $name_Sessions
!set name_visitors=!lowercase $name_Visitors

!distribute lines Choose a period for usage statistics: since\
  Show per module details\
  Show the statistics\
  Per module details\
  Number of visits\
  from\
  to\
  Date of<br>installation\
  Sub-total\
into name_choose,name_details,name_showstat,wims_name_statdetail,name_number_visits,name_from,\
  name_to,name_installed,name_subtotal
!set title=Usage statistics
!set name_sum=!nosubst sum over $laps days

!set name_prompt=total<br>requests,requests<br>per site,total<br>sites
!set name_explanations=<ul>\
<li>The request number counts only requests for pages.\
 Requests for modules under development are not counted.\
<li>The number of visiting sites is counted on a daily basis.\
<li>The number of (daily) visitors is between the site number and \
 the session number.\
</ul>

!set name_warning=The usage accounting is not active on this site. No statistics is available. Sorry.
 
!set name_numberclass=!nosubst There are $classcnt portals and individual classes on this server, with\
  $usercnt total user accounts.
  
  
!set format1=%m%d
!set format2=%m%d
!set format3=%m%y
