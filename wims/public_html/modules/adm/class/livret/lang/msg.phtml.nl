!set wims_module_log=error: $error
<b>Fout : </b>
!goto $error
!exit

:bad_class
 Vreemd , maar ik zie hier dat je klas niet geldig is ?!
!exit

:toomanycomp
    Er kunnen geen nieuwe vaardigheden meer worden toegevoegd : de limiet is $maxcomp ! 
!exit

:nouser
    Vreemd , maar ik geloof dat deze student niet bestaat ?!
!exit
