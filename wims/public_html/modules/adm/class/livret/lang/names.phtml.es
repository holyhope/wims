!let lang_exists=yes
!set classname=<b><font color=green>$wims_classname</font></b>\
 de <b><font color=green>$wims_institutionname</font></b>

!set months=enero,febrero,marzo,abril,mayo,junio,julio,agosto,septiembre,octubre,noviembre,diciembre

!distribute items Competencia,\
competencia,\
Competencias,\
competencias,\
Nivel,\
Niveles,\
nivel,\
niveles,\
Todas,\
skills booklet,\
into name_Competence,name_competence,name_Competences,name_competences,name_n_Palier,name_n_Paliers,name_n_palier,name_n_paliers,name_All,name_livret

!set name_no_competence=No hay ninguna  $name_competence en este cuaderno !
!set name_noyetparticipant=Esta clase no tiene participante todavía.
!set name_info=Información sobre esta $name_competence&nbsp;
!set name_param_change=Ahí tienes los parámetros que puedes cambiar&nbsp;
!set name_color=Color de los fondos de las casillas en función del nivel de validación del  $name_n_palier &nbsp;
!set name_score_modify=Los resultados de los ejercicios de las hojas de trabajo siguientes se neutralizan para el cálculo de los niveles de adquisición de los $name_n_paliers &nbsp;
!set name_cocher=Por  favor seleccione  los ejercicios que desean utilizar para este $name_n_palier.
!set name_selectsheet=Indicar solamente los ejercicios de la hoja
!let name_nowork=No hay trabajo
!let name_listscoreoption=de la clase, del cuaderno
!let name_listscoreview=no visualización, entero, con un decimal, con dos decimales, con tres decimales, con cuatro decimales

 !distribute items Título de la $name_competence&nbsp;,\
Título del $name_n_palier&nbsp;,\
Número de $name_n_paliers&nbsp;,\
de la clase,\
Nota mínima para considerar el ejercicio como acervo,\
Paleta de color utilizada en el $name_n_paliers nivel,\
Muestra el resultado en $name_n_paliers nivel,\
Show skill booklet to participant,\
Show empty skill to participant,\
into name_title_comp,name_title_palier,name_cnt_palier,name_configtext2,name_configtext3,name_configtext4,name_configtext5,name_configtext6,name_configtext7

!!------------------------------- definición de los nombres de vínculos para wims_menu_items

!if $wims_user=supervisor
 !let tmp=!defof SE_list in wimshome/public_html/modules/home/names.$lang
!else
 !let tmp=!defof U_myscore in wimshome/public_html/modules/home/names.$lang
!endif

!distribute line Nueva competencia \
$tmp\
Cuaderno de la clase \
Cuaderno de $name_competences \
 into wims_name_add_competence,wims_name_go_userlist,wims_name_cls_livret,wims_name_livret

!if $job=addcomp
 !set name_job=!nosubst Añadir/modificar la $name_competence $comp
 !exit
!endif

!if $job=modpalier
  !set name_job=!nosubst Modificar el $name_n_palier $palier (<font color=green>$name_palier</font>) de la $name_competence $comp (<font color=green>$name_comp</font>).
  !exit
!endif

!if $job=user
  !set name_job=!nosubst <font color=green>$user_firstname $user_lastname</font>
!endif

!if $job=delpalier
 !let name_delpalier=!nosubst ¿Está seguro de querer suprimir el  $name_n_palier $palier ( $mem_palier ) de $name_competence $comp ( $mem_title ) del $name_livret ?
 !exit
!endif

!if $job=delcomp
 !let name_delcomp=!nosubst ¿Está seguro de querer suprimir el  $name_competence $comp ( $mem_title ) del $name_livret ?
 !exit
!endif

!if $job=save
 name_get=You can download the source file to get structure of your skill booklet \
  for example to restore it in an other class.
 name_put=Write the address of a skill booklet archive file on your computer. The skills of the file \
 will be add to those already in your skill booklet.
!endif