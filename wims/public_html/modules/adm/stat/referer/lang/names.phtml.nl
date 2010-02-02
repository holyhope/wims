!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif

!set name_site=de website
!set name_stem=een pagina met adres
!set name_uniq=de pagina
!set names_site=websites
!set names_stem=site directory's
!set names_uniq=pagina's

!distribute items dagen,weken,maanden,jaren,to\
  into name_day,name_week,name_month,name_year,name_to
   
!distribute lines website naam\
  hoofd directory\
  compleet adres\
  De links kunnen worden gesorteerd op \
  van de webpagina, en het overzicht is beperkt tot de eerste\
  adressen. Zoek machine adressen kunnen \
  worden toegevoegd\
  uitgesloten van het overzicht\
  Optioneel: het overzicht kan worden beperkt tot websites/pagina's met daarin het woord\
 into name_site1,name_stem,name_uniq,name_listlink,name_limited,name_searchengine,\
 name_included,name_excluded,name_option

!set name_list1=!nosubst Overzicht van webpaginas $(names_$type) van waaruit onze site wordt bezocht,in de periode 

!set name_sum=!nosubst totaal over $laps dagen

!set name_list2=De eerste kolom laat het aantal bezoekers zien dat via een\
link $(name_$type) uit de tweede kolom ons bezocht.

!set name_visit1=bezoekers via links $totall
!set name_visit2=!nosubst Ten minste $auto bezoekers gaven geen referenties.\
Referentie pagina's vanuit $httpd_HTTP_HOST worden niet meegeteld.
 
!set title=Overzicht bezoekers via website
 
!set name_warning=Het overzicht van "bezoekers via website" is op deze server helaas uitgeschakeld.
   
 
!set name_choose=Periode overzicht van : 

:exit
:intro
In general, a web page who brings many visitors to us is also an interesting 
place for our other visitors. Therefore if you are
looking for web resources related to this server, a list of such pages is
what you need.
<p>
On the other hand, if you are the author of a page containing link(s) to us,
this list allows you to measure the efficiency of your link. It
is also our manner to thank you for the link.
<p>
Our backward link list is dynamically generated, according to the parameters
which you can choose in the following menu.