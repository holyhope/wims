!set wims_module_log=error: $error

<b>Error</b>.

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
 <p>
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

!msg $error

