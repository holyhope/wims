!set lang_exists=yes

!set name_0=en preparación
!set name_1=abierto
!set name_2=cerrado
!set name_3=ocultado
!set name_publish=publicado
!set name_hide=ocultado
!set name_nominative=nominativo
!set name_anonymous=anónimo
!set name_trace=anónimo y trazado
!set name_choice=elección
!set name_data=datos
!set name_global=globales
!set name_detail=détailladas
!set name_help=Ayuda
!set name_yourchoice=Su elección&nbsp;:
!set title_data=Datos de los cuestionarios para hoja de calculo
!set title_nominative=registro
!set title_vote=Cuestionario
!set title_anonymous=Voto
!set name_choose=-- Elige
!set wims_name_vote=Lista de cuestionarios
!set name_result=Resultado del cuestionarioe&nbsp;
!set name_content=Contenido
!set name_creation= Creación de un cuestionario o registro.
!set name_edition=Edición de un cuestionario o registro.
!set name_remaining=plazas restantes
!set name_untitled=Sin título

!distribute lines  Su clase no tiene aún ninguna encuesta. \
 Pregunte a su profesor.\
 No hay ninguna encuesta activa.\
 No hay ninguna encuesta activa.\
Número de  votos\
into name_novote,name_novotecheck,name_noactivevote,name_class_vote,\
name_cnt_votes

!distribute line Esta es una encuesta anónima.\
   Este cuestionario es $name_trace.\
   Esta es una votación nominal.\
   Está cerrada.\
   respuestas\
   Ya ha votado.\
   Ya había hecho su elección, pero está a tiempo de cambiar de opinión.\
   Haga su elección\
   Detalle de los registros\
   Textos de los comentarios\
into name_thisvote_anomymous,name_thisvote_trace,name_thisvote_nominatif,\
   name_thisvote_closed,name_thisvote_answer,name_thisvote_already1,\
   name_thisvote_already2,name_give_your_choice,name_details,name_comments

!set name_whovote=Lista de los votantes

!set name_csv1=Ahí tienes el fichero que pueden cargar a distancia y abrir en su programa informático \
hoja de cálculo preferida&nbsp;

!set name_csv2=!nosubst Desean cargar a distancia los datos del cuestionario número $vote &nbsp;
!set name_format=formato


