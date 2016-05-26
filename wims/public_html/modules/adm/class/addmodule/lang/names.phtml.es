!set lang_exists=yes

!set wims_name_sheetcheck=Compruebe la hoja de trabajo
!!set wims_name_moduback=Vuelta al módulo

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
!set name_endallexo=!nosubst une série d'exercices a été insérée avec succès dans la feuille <span class="wims_mod_title">$title</span>.
!set name_endallexos=!nosubst $addexo séries d'exercices ont été insérées avec succès dans la feuille <span class="wims_mod_title">$title</span>.
!set name_endallexo2s=!nosubst Les $notadd ressources suivantes n'ont pas pu être insérées car elles existaient déjà :
!set name_endallexo2=!nosubst La ressource suivante n'a pas pu être insérée car elle existait déjà :

!set name_choose_exo=Cette ressource sera insérée comme une nouvelle série d'exercices de la feuille.
!set name_choose_helpexo=Cette ressource sera insérée comme une aide pour l'une des séries d'exercices de la feuille lorsque la note est inférieure à
!set name_choose_series=Cliquez sur le nom de la séries d'exercices à laquelle vous souhaitez ajouter l'aide
!set name_actualhelp=Aide actuelle
!set name_series=Séries d'exercices
!set name_orderchange=Changer l'ordre des exercices

!if $job=addallexo
  !read oef/es/intronames
!endif

