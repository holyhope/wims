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
Een webpagina met links naar ons systeem is mogelijk ook een interessante plek
voor WIMS gebruikers.
De lijst met "bezoekers via website" geeft daarover enige informatie.
<p>
Anderzijds als u linkst naar WIMS plaatst op uw eigen webpagina's is het
handig te weten of er ook daadwerkelijk gebruik van wordt gemaakt.
En het is onze manier om te bedanken voor het plaatsen van een link naar WIMS.
<p>
De lijst met "bezoekers via website" wordt speciaal aangemaakt aan de hand van de
instelparameters, welke gekozen kunnen worden in het volgende menu.
