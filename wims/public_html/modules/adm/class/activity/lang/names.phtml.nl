!set lang_exists=yes
!set name_title=Individuele activiteiten
!set name_noparticipant=Deze klas heeft geen deelnemers/leerlingen
!set name_lastconnexion=Laatste inlogsessie via ip-adres
!set name_total=tijdsduur
!set name_click=Klik op een naam voor details
!set name_nbsessions=Aantal sessies
!set name_exo=oefening
!set name_time=Tijd
!set name_cnt_exo=Aantal oefeningen

!set name_showsheet=Selecteer de werkbladen voor het activiteiten overzicht

!set name_ylabel=# ex.

!set name_expert0=Voor het selecteren van deelnemers zijn\
 meerdere methodes beschikbaar. Kies de gewenste methode.

!distribute items Expert menu,Lijst met loginnamen&nbsp;,Per selectie&nbsp;,\
Per student,dagen,Montrer les graphiques, Tous les participants\
into name_menu,name_loginlist,name_select,name_shiftpart,name_days,\
 name_graphics, name_allpart

!distribute lines Vous pourrez ensuite faire défiler les participants (méthode par défaut dans le cas où les graphiques sont demandés).\
Le nombre de participants sélectionnés est limité à $limitpart, seuls les $limitpart premiers seront affichés\
Dans le cas où les graphiques sont affichés, le nombre de participants affichés est limité à $limitpart\
Uniquement dans le cas où les graphiques ne sont pas demandés.\
dans le cas où les graphiques sont demandés\
into name_help1,name_help2,name_help3,name_help0,name_help00
