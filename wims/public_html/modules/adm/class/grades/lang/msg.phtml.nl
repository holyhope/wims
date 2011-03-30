!set wims_module_log=error: $error

!if too_many_users=$error
 Uw klas heeft te veel leerlingen ($ucnt). 
 De cijfers kunnen alleen handmatig worden ingevoerd voor klassen met minder dan 
 $maxuser leerlingen. Sorry.
 !exit
!endif

!msg $error

