!set wims_module_log=error: $error

!if error=nosupervisoremail
  Er is geen emailadres bekend voor uw account ! 
  Het is dus niet mogelijk om via dit programma emails te versturen.
 !exit
!endif

!if empty_msg=$error
 Het emailbericht is leeg !
 !exit
!endif

!if empty_user=$error
 Er zijn geen deelnemers geselecteerd. Kontroleer de filter instellingen.
 !exit
!endif

!if empty_mailuser=$error
 Geen van de deelnemers heeft een emailadres opgegeven.
 !exit
!endif

!if noclass=$error
 Vous n'êtes pas identifié dans une classe. Ne jouez pas avec la barre d'adresse du navigateur !
 !exit
!endif

!if notsupervisor=$error
 Vous n'êtes pas l'enseignant de cette classe. Ne jouez pas avec la barre d'adresse du navigateur !
 !exit
!endif

!msg $error
