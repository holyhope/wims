!set lang_exists=yes
!!!set name_title=Actividades individuales globales
!set name_noparticipant=Esta clase no tiene participante todavía.
!set name_lastconnexion=Última conexión
!set name_total=tiempo total
!set name_click=Pulse un nombre para ver el detalle de su trabajo.
!set name_nbsessions=Numero de sesiones
!set name_exo=ejercicios
!set name_time=Tiempo
!set name_cnt_exo=Numero de ejercicios

!set name_showsheet=Seleccione las hojas de cuales desea ver la actividad.

!set name_ylabel=# ex.

!set name_expert0=Si desean seleccionar a algunos participantes, se proponen varios métodos. \
Marcan el método deseado.

!distribute items  Menu expert,Par liste de logins,Par sélection,\
  Par participant,days,Montrer les graphiques, Tous les participants\
into name_menu,name_loginlist,name_select,name_shiftpart,name_days,\
 name_graphics, name_allpart

!distribute lines Vous pourrez ensuite faire défiler les participants (méthode par défaut dans le cas où les graphiques sont demandés).\
Le nombre de participants sélectionnés est limité à $limitpart, seuls les $limitpart premiers seront affichés\
Dans le cas où les graphiques sont affichés, le nombre de participants affichés est limité à $limitpart\
Uniquement dans le cas où les graphiques ne sont pas demandés.\
dans le cas où les graphiques sont demandés\
into name_help1,name_help2,name_help3,name_help0,name_help00
