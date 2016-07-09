!set wims_module_log=error: $error

<span class="wims_warning">$wims_name_Error</span>.
!if $error=badvariablename
 L'une, au moins, des variables techniques que vous utilisez n'existe pas ou n'est pas modifiable à ce niveau. Votre questionnaire ne fonctionnera pas correctement. 
 !exit
!endif

!if $error=notechvar
 Er zijn geen technische variabelen gedefinieerd in deze klas. Stel eerst de benodigde technische variabelen vast voordat deze instelling kan worden gebruikt. 
 !exit
!endif

!if $error = not_user
Deze voorziening is alleen beschikbaar voor virtuele klassen.
 !exit
!endif

!if $error = bad_vote
 De verkiezing / enquete waar je om vroeg, bestaat niet.
 !exit
!endif

!if $error = already_voted
 Je hebt al eens een stem uitgebracht. 
 !exit
!endif

!if $error = too_many_votes
 Er zijn te veel enquetes in deze klas.
 <br />
 Waarom heeft u er zoveel nodig?
 !exit
!endif

!if $error = no_content
 U hebt de inhoud van het stemformulier / enquete formulier nog niet ingevuld.
 !exit
!endif

!if $error = no_title
  Geef de verkiezing / enquete eerst een naam.
 !exit
!endif

!if $error = bad_data
 Enkele van definities zijn ongeldig, graag corrigeren.
 !exit
!endif

!if $error = not_secure
 De gegevens zijn niet bereikbaar vanaf je netwerkadres.
!exit
!endif

!if $error = no_vote
    Je hebt nog geen stem uitgebracht en kunt daarom de resultaten niet bekijken.
 !exit
!endif

!if $error = no_variable
    Er is nog geen naam voor deze variabele bekend, of de opgegeven naam is niet geldig.
   !exit
!endif

!if $error = bad_variable
    De naam van variabele (<span class="tt wims_code_words">$namevar</span>) is niet goed gekozen:
    de naam kan al ingebruik zijn.
   !exit
!endif

!msg $error

