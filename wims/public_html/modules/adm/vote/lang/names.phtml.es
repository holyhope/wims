!set lang_exists=yes

!set name_introtext_group=Saisir l'effectif de chaque groupe ainsi qu'un commentaire (éventuel).
!set name_cardinal=Effectif

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
!set name_question=Question
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
!set name_showresult=show result
!set name_nowritable=Questionnaire actif, il est impossible de modifier son contenu. En voici le source :
!set name_novotant=Aucun vote
!set name_notenough=Pas assez de votants pour publier la liste
!set name_showlist=Résultats par question
!set name_showglobal=Résultats globaux
!set name_showlistbystudent=Résultats par votants
!set name_showstudentbyitem=Liste par choix

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
   name_thisvote_already2,name_give_your_choice,name_details,\
   name_comments,name_textarea

!set name_textarea_limit=!nosubst limité à $limit_textarea caractères
!set name_whovote=Lista de los votantes
!set name_whodontvote=List of those who have not voted

!set name_csv1=Ahí tienes el fichero que pueden cargar a distancia y abrir en su programa informático \
hoja de cálculo preferida&nbsp;

!set name_csv2=!nosubst Desean cargar a distancia los datos del cuestionario número $vote &nbsp;
!set name_format=formato

!set name_option=Options
!set name_value=Values

!! guided mode

!set name_optionclosed=closed, will be opened only when other options will be full

!distribute lines How many sessions?\
How many groups?\
at most\
uservar name\
Default host IP \
can be changed in the following page\
Introductory text \
e.g. general instructions for the students\
Num.Stud.\
Date of session\
Beg. time of session\
End time of session\
Host IP\
Extra info\
Inscription cancellation\
into name_howmany,name_howmanygroups,name_atmost,name_namevar,name_textconnip,\
  name_textconnip2, name_introtext,name_introtext2,name_numstud,name_sessiondate,\
  name_begintime,name_endtime,name_connip,name_extra,\
  name_cancellation

!set name_numsess=!nosubst $numsess sessions are available.
!set name_session_select=!nosubst Select date and time of the $numsess available sessions\

!set name_describesource=!nosubst Here you can see the source code of the vote. Check the data and click on <span class="wims_button disabled">$wims_name_tosave</span>.

!if $vote_mode!=free
 !readproc adm/lang/sheetexam.phtml.$lang
!endif

!set name_yourvariable=!nosubst Le nom de la variable correspondant à ce questionnaire \
  que vous avez choisi est <span class="tt wims_code_variable">$namevar</span>
!set name_accessvar_instr=!nosubst <strong>Utilisation dans un examen ou dans une feuille</strong>: \
dans une feuille ou un examen actif, dans <span class="tt wims_code_words">$(name_shinfo[6])</span>, sélectionnez \
 <span class="tt wims_code_words">$(name_allowtype[3])</span> et écrivez \
<span class="tt wims_code_variable">\$namevar</span> (y compris <span class="tt wims_code_variable">\</span>).

!set name_group_instr=!nosubst <strong>Utilisation dans la classe</strong>: vous pouvez filtrer \
les participants selon cette variable pour certaines activités de la classe.

!set name_group_help= permet de sélectionner les participants \
selon les groupes (mail et trombinoscope pour l'instant).

!set name_accessvar_help=permet d'individualiser l'accès des participants \
à une feuille ou à un examen.

!distribute items Free Mode ,Access to sheets or exams,Constitution of groups,Groups into name_free,name_accessvar, name_group,name_group1

!set name_model=Model
!set name_nextstep=Next Step

!set name_getsource=This is the source code. The code written between the \
  two rows of `*'; can be copied into$ an empty vote (use the clipboard) to create a\
  new vote with the same content.
