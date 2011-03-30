
!set wims_module_error=error: $error

<b>$wims_name_Error</b>.

!if bad_sheet iswordof $error
 Nombre de hoja de trabajo inválido.
 !exit
!endif

!if too_many_print iswordof $error
 Ha pedido demasiadas versiones impresas.
 !href cmd=reply&job=read $wims_name_back2
 !exit
!endif

