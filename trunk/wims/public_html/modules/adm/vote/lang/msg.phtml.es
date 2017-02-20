!set wims_module_log=error: $error

<span class="wims_warning">$wims_name_Error</span>.
!if $error=badvariablename
 L'une, au moins, des variables techniques que vous utilisez n'existe pas ou n'est pas modifiable à ce niveau. Votre questionnaire ne fonctionnera pas correctement. 
 !exit
!endif

!if $error=notechvar
 Aucune variable technique définie dans cette classe. Pour utiliser ce modèle de questionnaire vous devez d'abord définir une variable technique dans la classe en utilisant le gestionnaire de variable technique.
 !exit
!endif

!if $error = not_user
 El sistema de encuestas sólo está disponible para las clases virtuales.
 !exit
!endif

!if $error = bad_vote
 La encuesta / votación que solicita no existe.
 !exit
!endif

!if $error = already_voted
 Ya ha votado. No puede volver a votar porque la encuesta es anónima.
 !exit
!endif

!if $error = too_many_votes
 Hay demasiadas encuestas / votaciones en su clase.
 ¿Por qué necesita tantas?
 !exit
!endif

!if $error = no_content
 No ha rellenado la encuesta / votación.
 !exit
!endif

!if $error = no_title
 Debe darle un título a su encuesta / votación.
 !exit
!endif

!if $error = bad_data
 Algunas de sus definiciones no son correctas. Por favor corríjalas.
 !exit
!endif

!if $error = no_vote
 Vous n'avez pas encore voté donc vous ne pouvez pas voir les résultats.
 !exit
!endif

!if $error = no_variable
   Vous n'avez pas donné de nom de variable ou il n'est pas valide.
   !exit
!endif

!if $error = bad_variable
   Le nom de variable que vous avez donné (<span class="tt wims_code_words">$namevar</span>) ne convient pas car il 
   est peut-être utilisé par le logiciel.
   !exit
!endif

!msg $error

