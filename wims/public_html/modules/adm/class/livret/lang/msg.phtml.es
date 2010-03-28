!set wims_module_log=error: $error
<b>Erreur : </b>
!goto $error
!exit

:bad_class
 ¡Extraño pero encuentro que su clase no es válida!!!
!exit

:toomanycomp
 No pueden añadir más competencias, el límite es de $maxcomp !
!exit

:nouser
¡Extraño pero el participante no parece existir!!!!
!exit
