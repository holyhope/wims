!set wims_module_log=error: $error

!if no_pick=$error
 Por favor
 !href cmd=resume elija una hoja de trabajo
 antes de pulsar el botón ``insertar''.
 !exit
!endif

!if not_supervisor=$error
 Lo sentimos, pero la operación de modificar una hoja
 de trabajo está reservada al supervisor registrado
 de una clase.
 !exit
!endif

!if no_sheet=$error
 Su clase no tiene una hoja de trabajo no activa. Se debe insertar un trabajo
 en una hoja de trabajo no activa.
 !href module=adm/class/sheet&sheet=$[$sheettot+1] $wims_name_add_sheet
?
 !exit
!endif

!if bad_sheet=$error
 Número de hoja de trabajo erróneo.
 !exit
!endif

!if too_many_exos=$error
 La hoja de trabajo $picksheet ya contiene el máximo de elementos ($max_exo). 
 Elimine alguno antes de poder insertar más en ella.
 !exit
!endif

!if already_exist=$error
 El trabajo que quiere añadir ya existe en la hoja de trabajo $test.
 No debe referenciar el mismo ejercicio con los mismos parámetros 
 iniciales dos veces en la misma hoja de trabajo. <p>
 Por favor, cambie los parámetros del ejercicio antes de insertarlo en una 
 hoja de trabajo. <p>
 Si quiere que sus estudiantes repitan el trabajo de los ejercicios, 
 puede incrementar el número de puntos requeridos.
 !exit
!endif

!msg $error