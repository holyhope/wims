!set wims_module_log=error: $error

!if badoldvaluesnb=$error
 Het aantal waarden voor deze oude technische variabele zijn te groot om te worden hersteld.
 !exit
!endif

!if not_supervisor=$error
 Helaas, alleen een docent of supervisor mag deze handeling verrichten.
 !exit
!endif

!if nameforbidden=$error
 Helaas, de naam van een technische variabele mag niet die van een werkblad, examen, enquete,  getal etc zijn.
 !exit
!endif

!if bad_class=$error
 U bent niet aangemeld bij een klas.
 !exit
!endif

!if toomanytechvar=$error
 Het maximum toegestane aantal technische variabelen hier is reeds overschreden.  
 !exit
!endif

!if badnamelen=$error
 De naam van de technische variabele is niet correct : teveel of te weinig karacters (maximaal $MAXcharname ). 
 !exit
!endif

!if namealreadyuse=$error
 Deze naam is reeds in gebruikt. Kies ene andere naam voor deze technische variabele !
 !exit
!endif

!if badvaluenb=$error
 De lijst met mogelijke waarden mag niet leeg zijn en maximaal $MAXnbvalue waarden bevatten. 
 !exit
!endif

!if badtechvarnumber=$error
 Een probleem met interpreteren van de tecghnische variabele. Niet prutsen met de adresbalk van je browser !
 !exit
!endif

!if valuedisappear=$error
 Voor nu moet de lijst met nieuwe waarden ook nog de oude waarden bevatten. 
 (de interface is werk-in-uitvoering op dit moment!)
 !exit
!endif

!if nolocalvartech=$error
 Deze technische variabele is niet modificeerbaar voor die leerling.
 !exit
!endif

!if nooldvar=$error
 Er zijn geen oude technische variabelen gedetecteerd in deze structuur.
 !exit
!endif

!if $error=oldvar_nouser
De oude technische variabele is niet gedefineerd voor een leerling is deze klas.
Misschien hoor deze variabele bij een andere klas of groep.
Het aanmaken is mislukt.
!exit
!endif

!if $error=oldvar_badvar
De oude variabele die je probeert om te zetten bestaat niet. Niet prutsen met de adres-balk van je browser ! 
!exit
!endif

!if $error=witholdvar
Er zijn oude technische variabelen gevonde, Misschien moeten deze eerst worden omgezet mbv  <i> $wims_name_oldvar </i> voordat er nieuwe variabelen worden aangemaakt ? 
 !exit
!endif

!msg $error
