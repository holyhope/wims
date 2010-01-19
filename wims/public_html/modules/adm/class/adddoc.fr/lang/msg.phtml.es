!set wims_module_log=error: $error

!if not_supervisor=$error
 Désolé, mais cette opération
 est réservée à l'enseignant enregistré d'une classe.
 !exit
!endif

!if bad_class=$error
 Etrange, mais je trouve que votre classe n'est pas valide!
 !exit
!endif

!if insert_fail=$error
 Le logiciel n'a pas pu insérer votre travail dans la classe. Veuillez
 vérifier vos données.
 !exit
!endif

!if already_exist=$error
 Le document que vous voulez insérer existe déjà dans votre classe.
 !exit
!endif
 
 
