!set wims_module_log=error: $error

!if not_supervisor=$error
 Helaas, 
 alleen een geregistreerde supervisor van een klas kan deze pagina aanroepen 
 !exit
!endif

!if bad_class=$error
 Vreemd, ik zie nu dat Uw klas niet geldig is!
 !exit
!endif

!if too_many_users=$error
 Uw klas heeft te veel leerlingen ($ucnt). 
 De cijfers kunnen alleen handmatig worden ingevoerd voor klassen met minder dan 
 $maxuser leerlingen. Sorry.
 !exit
!endif

!msg $error

