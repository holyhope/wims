
!set classname=<b><font color=green>$wims_classname</font></b>\
 de <b><font color=green>$wims_institutionname</font></b>

!set months=enero,febrero,marzo,abril,mayo,junio,julio,agosto,septiembre,octubre,noviembre,diciembre

!set wims_name_endexam=Terminar esta sesi�n de examen
!set wims_name_scoreexam=Mi puntuaci�n

!set wims_name_mainpage=P�gina principal del examen
!set name_dependency=Dependencias de las puntuaciones&nbsp;
!set name_Options=Opciones
!set name_All=Todas
!set name_title=Preparaci�n del examen
!set name_expire=Darlo por expirado ahora mismo
!set name_done=hecho

!distribute items poids,Coeficiente,Puntuaci�n\
into name_weight,name_coeff,name_Score

!distribute lines Terminar esta sesi�n de examen\
Volver a trabajar en el examen\
Punto de vista del profesor sobre el examen\
Presentaci�n a los participantes\
Detalle de la puntuaci�n actual\
�Este examen est� vac�o! No se le ha asignado nada. Posiblemente un error de manipulaci�n de su supervisor.Contenido del examen\
Contenido del examen\
Actualmente, este examen est� cerrado a su conexi�n.\
Solo puede realizar una vez este examen.\
por lo tanto no puede mejorar su puntuaci�n.\
Es su �ltimo intento disponible. �Preste atenci�n!\
la cuenta atr�s comenzar�, y se incrementar� en 1 el n�mero de intentos.\
la cuenta atr�s comenzar�.\
Requiere el �xito sobre otros ejercicios\
Puntuaci�n de esta sesi�n del examen\
into wims_name_endexam,wims_name_backexam,wims_name_teacherview,name_presentation,\
name_scoreexam,name_empty,name_content,name_examclosed,name_exam1,name_exam5,\
name_lasttry,name_exam7,name_exam8,name_depend,name_scoreexam2

!set name_exam2=!nosubst Puede registrar hasta $stries puntuaciones en este examen.

!set name_exam3=!nosubst Ya ha terminado su sesi�n de examen con $tried ensayos,
!set name_exam4=!nosubst Ya lo ha intentado $tried veces,
!set name_exam6=!nosubst Y todav�a puede hacer $tryremain nuevos intentos.

!set name_exam9=!nosubst Tiene $sdure minutos para trabajar en el examen.\
     Cuando pulse en un ejercicio de los anteriores,

!set name_simulation=Este examen est� en modo simulaci�n. Funciona exactamente igual \
que el examen verdadero pero no se puede guardar la puntuaci�n y el intento no se tendr� en cuenta.

!set wims_name_examremain=Tiempo restante de examen: $

!distribute lines pendiente\
 Todav�a no ha comenzado a trabajar en este examen.\
 Comenzar a trabajar.\
 La puntuaci�n actual no se tomar� en cuenta, porque el examen est� en modo simulaci�n.\
into name_pending,name_begin1,name_begin2,name_simulation2

!set name_timeleft=!nosubst �Se acab� el tiempo! Ya ha usado los $sdure minutos permitidos para este examen.
!set name_realscore=!nosubst Su puntuaci�n real para esta hoja de examen es $lastscore
!set name_bestscore =!nosubst Su mejor puntuaci�n para este examen es $lastscore (la mejor puntuaci�n es la que se tomar� en cuenta).
