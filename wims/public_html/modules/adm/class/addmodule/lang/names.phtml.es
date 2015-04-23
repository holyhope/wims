!set lang_exists=yes

!set wims_name_sheetcheck=Compruebe la hoja de trabajo
!set wims_name_moduback=Vuelta al módulo

!set name_choose=Elija la hoja en la cual quiere insertar el elemento de trabajo&nbsp;
!set name_title=Insertar en una hoja de trabajo

!set name_insert=Quiere insertar el elemento de trabajo
!set name_parm= con los parámetros de inicialización
!set name_modifytitle=También puede modificar el título y el texto de la descripción.

!set name_required=Número de puntos que los participantes deben obtener&nbsp;
!set name_repeat=cada respuesta correcta en el ejercicio da 10 puntos; ponga \
 más de 10 puntos aquí si quiere que el participante repita el ejercicio.

!set name_weight=Peso de los puntos obtenidos en este trabajo
!set name_weight_hint=para el cálculo de la media
!set name_end=!nosubst  El recurso <span class="wims_mod_title">$title</span> se ha añadido con éxito a la hoja de trabajo
!set name_endallexo=!nosubst $addexo séries d'exercices ont été insérées avec succès dans la feuille <span class="wims_mod_title">$title</span>.
!set name_endallexo2=!nosubst Les $notadd ressources suivantes n'ont pas pu être insérées car elles existaient déjà : 

!set name_choose_exo=Cette ressource sera insérée comme une nouvelle série d'exercices de la feuille.
!set name_choose_helpexo=Cette ressource sera insérée comme une aide pour l'une des séries d'exercices de la feuille lorsque la note est inférieure à
!set name_choose_series=Cliquez sur le nom de la séries d'exercices à laquelle vous souhaitez ajouter l'aide
!set name_actualhelp=Aide actuelle
!set name_series=Séries d'exercices
!set name_orderchange=Changer l'ordre des exercices

!if $job=addallexo
!! il s'agit d'une copie de la partie intro du fichier oef/lang/names

!distribute line  Lo sentimos, este módulo no tiene ejercicios disponibles por ahora. ¡Vuelva más tarde!\
Este módulo contiene en estos momentos solamente un ejercicio\
 Pruébelo.\
 Elija los ejercicios&nbsp;\
 Ejercicios que contienen\
 Una serie tendrá;\
 Nivel de severidad\
 Tiempo límite\
 segundos\
 Número de ítems mostrados en los ejercicios de opciones múltiples&nbsp;\
 Dar una solución (si está disponible)&nbsp;\
 Configuración simplificada\
 Configuración experta\
 Seleccionar títulos que contengan el término\
 ejercicios\
 Set-up\
into name_noexercise,name_oneexercise,name_tryit,name_chooseexo,name_exercisescontaining,name_oneserie,\
name_levelseverity,name_chrono,name_secondes,name_qcmanswer,name_solutiongiven,\
name_simplifiedmenu,name_expertmenu,name_select,name_exercices,name_menu

 !set name_datamodule=Este módulo necesita el módulo de datos <span class="tt">$module_data</span> \
  que no está instalado en este servidor. Si desean utilizarlo, \
  pidan  al gestor del lugar instalarlo.

!set name_choice=nunca,si la nota no es máxima,siempre

!set name_choice_check=Siempre añadir una respuesta correcta en los ejercicios con opciones múltiples,\
  Penalización por respuestas incorrectas en los ejercicios de opciones múltiples.,\
  Mostrar la respuesta correcta.,\
  Permitir las pistas (cuando existan).

!set name_aleaseries= Propose the exercises of the series in order.
!set name_remarkintro1=After having selected an exercise from the list,\
click on <span class="wims_button disabled">$wims_name_work</span>. Los ejercicios se tomarán aleatoriamente de la lista generada \
por sus opciones. Si su elección está vacía, se utilizarán todos los ejercicios disponibles.

!!leave on one line
!set name_remarkintro3=Puede poner dos números en el campo del límite de tiempo, un número seguido de otro más grande. En este caso, el primer límite señala el momento de comenzar la reducción de la calificación, hasta llegar a 0 cuando se alcance el segundo límite.


!endif
