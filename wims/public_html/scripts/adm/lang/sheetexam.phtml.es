!! definici�n de los nombres para los v�nculos en el menubox (definidos por wims_menu_items)
!distribute items Vista de los participantes,\
		A�adir un ejercicio,\
		A�adir una serie de ejercicios,\
into wims_name_participantview,wims_name_addexo,wims_name_addsexo
!distribute items A�adir un ejercicio,\
		A�adir una serie de ejercicios,\
into wims_name_addexo,wims_name_addsexo


!set wims_name_chseries=!nosubst Enregistrer les modifications sur la s�rie d'exercices $(special_parm4[2]) feuille $(special_parm4[1])

!set name_desc_title=!nosubst limitado a  $title_limit caracteres
!set name_desc_desc=!nosubst limitado a $desc_limit caracteres; se admiten los tags y v�nculos HTML

!let name_shinfo=!nosubst $wims_name_title,$wims_name_Status,\
Texto de explicaci�n, \
Fecha de expiraci�n, Registro de las notas, para todas las clases compartiendo : , Comentario, Duraci�n de un examen, N�mero de pruebas por sesi�n

!let name_allowtype=abierto para todos, abierto para simulaci�n, cerrado para todos, abierto para siguientes puestos (y/o horas):
!if exam notin $module
 !let name_allowtype=$(name_allowtype[1]),$(name_allowtype[3]),$(name_allowtype[4])
!endif

!set name_desc_comment=Visible solamente por el profesor.
!let name_selectsheet=Indicar solamente los ejercicios de la hoja

!if $job=student
  !set name_title=Hoja de trabajo n�mero $sheet<br>$title (presentaci�n para los participantes)
  !set name_assignedwork=Tareas asignadas en esta hoja&nbsp;
  !set name_quality=0 de $[$re] puntos obtenidos, calidad
!endif

!set name_sheetempty=�La hoja est� vac�a! No se le ha asignado nada todav�a. Posiblemente se trata de un error de su profesor.

!!set name_desc_dependancy=Un participante debe en primer lugar adquirir puntos en otros ejercicios de la hoja, antes de poder trabajar sobre �ste. Por ejemplo,  <font color=blue><tt>1:50,2: 30,3+4+5: 60</tt></font> significa que el participante debe tener un �xito del  50% sobre el ejercicio 1, 30% sobre el ejercicio 2, y una media de �xito del 60% sobre los ejercicios 3, 4, 5.

!set name_deps=Tiene que mejorar sus puntuaciones en los ejercicios
!set name_dep=Tiene que mejorar su puntuaci�n en el ejercicio
!set name_dep2= antes de recibir puntuaciones en este.

!distribute items poids,Coeficiente\
into name_weight,name_coeff

!set name_dependency=Dependencias de las puntuaciones&nbsp;
