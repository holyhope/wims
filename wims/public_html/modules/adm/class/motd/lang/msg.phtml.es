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
 Etrange, mais je ne trouve pas ce participant dans cette classe !
 !exit
!endif