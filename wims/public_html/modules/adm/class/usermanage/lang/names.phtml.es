!set lang_exists=yes

!if $wims_read_parm!=
 !goto $wims_read_parm
!endif

!set name_studentloc=!nosubst $user_lastname $user_firstname
!set name_studentglo=!nosubst $wims_name_lastname $wims_name_firstname

!set name_click=Pulse sobre un nombre para ver los detalles de su trabajo
!set name_noyetparticipant=Esta clase no tiene ningún participante aún.
!set name_transfer=Transferir sus actividades desde otras clases
!set name_filter=Variables techniques

!if $job=regmanage
	!set name_all=Tous les participants
	!set name_reguser=Inscrire les participants
	!set name_unreguser=Supprimer l'inscription des participants
        !set name_display=Afficher
        !set name_techvardisplay=Sélection par variables techniques
	!set name_description=Utiliser les cases à cocher pour sélectionner les participants et les classes de votre choix puis appuyez sur l'un des deux boutons pour changer leurs droits d'accès.
!endif

!if $job iswordof userprop teacher userlist
  !distribute items Cambiar,Número de inscripción,Comentarios,URL de una fotografía,Variables (técnicas),\
  Contraseña de la clase,Introduzca la contraseña para la inscripción de participantes,\
  Login for external authentification,Inscription,Gestion,\
   Compulsory\
  into name_change,name_regnum,name_comments,name_photourl,name_vars,\
  name_classpassword,name_enterpassword,name_external_auth,name_inscript,name_gestion,\
  name_userprop_warning
  !exit
!endif

!if $job=transfer
   !set name_title_transfer=Transferencia de las actividades
   !distribute items Unir, Sustituir,Examinar\
   into name_merge, name_replace,name_show
 !set name_error1=El participante no está inscrito en ningún curso que corresponda\
     a la clase actual y que pueda recibir la transferencia desde
 !set name_error2=<b>Error</b> de identificador de las clases. \
    Falsa maniobra o error del programa informático ?
!set name_activities=!nosubst Detalle de las actividades en $i (limitado a 1000 líneas).
!set name_totransfer=Estos son los otros cursos en los que ha realizado actividades el participante.\
  Pulse sobre una acción para hacer la transferencia.
  !exit
!endif

!if $job=recover
  !set name_empty= No se ha dado de baja a ningún participante de esta clase.
  !set name_click=Pulse sobre un identificador de usuario (login) \
     para volver a incluir al participante en la clase.
  !exit
!endif

!if $job=delprep
  !set name_delete=!nosubst ¿Está seguro de que quiere dar de baja a  <b><em>$name_studentloc</em></b> de su clase?
  !exit
!endif


!exit

:transfer
<b>Notas</b>. <ol>
<li>"Unir" quiere decir unificar los conjuntos de actividades de los dos cursos.</li>
<li>"Sustituir" se refiere  a que las actividades del otro curso van a eliminar
completamente las de este. La sustitución no se realizará si el primero está vacío.</li>
<li>Las puntuaciones de los exámenes y las actividades no puntuadas siempre se unifican.</li>
<li>El registro de los detalles de los ejercicios o de los exámenes no se transfiere.</li>
<li>Después de la operación (de unir o sustituir), se borrarán los registros de las
actividades del participante en el otro curso.</li>
</ol>
!exit
