!set wims_module_log=error: $error

!if not_supervisor=$error
 Désolé, mais seul l'enseignant peut utiliser cette fonctionnalité.
 !exit
!endif

!if nameforbidden=$error
 Désolé, les variables techniques ne peuvent pas porter des noms du type exam, sheet, vote, manual suivis d'un numéro.
 !exit
!endif

!if bad_class=$error
 Vous n'êtes pas connecté à une classe.
 !exit
!endif

!if toomanytechvar=$error
 Vous avez déjà atteint le nombre maximum de variables techniques autorisé. 
 !exit
!endif

!if badnamelen=$error
 Le nom de variable technique proposé n'est pas de la bonne longueur : trop de caractères ou pas assez (limitation à $MAXcharname caractères). 
 !exit
!endif

!if namealreadyuse=$error
 Le nom de variable technique proposé est déjà utilisé. Choisissez en un autre !
 !exit
!endif

!if badvaluenb=$error
 La liste des valeurs possibles doit être non vide et contenir au plus $MAXnbvalue éléments. 
 !exit
!endif

!if badtechvarnumber=$error
 Problème d'identification de la variable technique. Ne jouez pas avec la barre d'adresse du navigateur !
 !exit
!endif

!if valuedisappear=$error
 Pour l'instant la liste des nouvelles valeurs doit au moins contenir les anciennes valeurs. 
 (Interface en cours d'amélioration : soyez patient !)
 !exit
!endif

!if nolocalvartech=$error
 Il n'y a pas de variable technique modifiable pour cet élève.
 !exit
!endif

!if nooldvar=$error
 Il n'y a pas d'ancienne variable technique détectée dans cette structure.
 !exit
!endif

!if $error=oldvar_nouser
 L'ancienne variable technique que vous souhaitez créer n'est définie pour aucun élève de votre classe. Probablement que cette variable appartient à une autre classe du groupement. La création n'a pas eu lieu.
!exit
!endif

!if $error=oldvar_badvar
 L'ancienne variable que vous essayer de transférer ne correspond à aucune ancienne variable transférable. Ne jouez pas avec la barre d'adresse du navigateur !
!exit
!endif

!if $error=witholdvar
 D'anciennes variables techniques sont détectées. Peut-être devriez-vous les récupérer, en utilisant le lien <i>$wims_name_oldvar</i>, avant de créer de nouvelles variables ?
 !exit
!endif

!msg $error
