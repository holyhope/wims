!set wims_module_log=error: $error

!if too_many_users=$error
 Su clase tiene demasiados participantes ($ucnt).
 Las puntuaciones se pueden introducir manualmente
 sólo para clases con un máximo de $maxuser participantes. 
 Lo sentimos.
 !exit
!endif

!msg $error

