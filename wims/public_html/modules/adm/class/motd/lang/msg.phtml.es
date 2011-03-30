!set wims_module_log=error: $error

!if not_supervisor=$error
 Lo sentimos, pero sólo tiene derecho a escribir el mensaje de una
 clase el supervisor registrado.
 !exit
!endif

!msg $error
