!set wims_module_log=error: $error
<b>Erreur : </b>
!goto $error
!exit

:bad_class
 Etrange mais je trouve que votre classe n'est pas valide !!!
!exit

:toomanycomp
 Vous ne pouvez plus ajouter de compétences, la limite est de $maxcomp !
!exit

:nouser
 Etrange mais le participant ne semble pas exister !!!!
!exit
