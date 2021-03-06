!set wims_module_log=error: $error

!if $error iswordof already_exist baddocnumber not_supervisor insert_fail max_doc toomuchsheet noexo
  !goto $error
!else
 !msg $error
 !exit
!endif


:already_exist
 El documento que desea insertar ya existe en la clase.
!exit

:baddocnumber
 Les informations que vous avez saisies ne correspondent pas à un document enregistré de la classe.
!exit

:not_supervisor
Seul l'administrateur de la classe peut mener cette action.
!exit

:insert_fail
vous essayez d'insérer un module non autorisé.
!exit

:maxdoc
Le nombre de documents est limité à $max_doc.
!exit

:toomuchsheet
Le nombre de feuilles est limité à $max_sheets. Vous ne pouvez donc plus en créer.
!exit

:noexo
Ce document ne contient aucun exercice.
!exit
