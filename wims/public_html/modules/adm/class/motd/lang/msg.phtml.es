!set wims_module_log=error: $error

!if not_supervisor=$error
 Lo sentimos, pero sólo tiene derecho a escribir el mensaje de una
 clase el supervisor registrado.
 !exit
!endif

!if bad_class=$error
 ¡Qué extraño, detecto que su clase no es válida!
 !exit
!endif

!if bad_user=$error
 ¡Extraño, no encuentro a este participante en esta clase!
 !exit
!endif
