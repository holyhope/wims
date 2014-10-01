!set wims_module_log=error: $error

!if no_pick=$error
Kies eerst een
 !href cmd=resume werkblad
 voor U op de <span class="wims_button disabled">$wims_name_Insert</span> drukt...
 !exit
!endif

!if not_supervisor=$error
Helaas, maar het veranderen van een werkblad is alleen toegestaan voor docenten van een klas.

 !exit
!endif

!if no_sheet=$error
Uw klas heeft -nog- geen werkbladen in voorbereiding .<br />
Lesmateriaal of oefeningen kun men alleen toevoegen aan een nog <b>niet geactiveerd werkblad</b>.

 !href module=adm/class/sheet&sheet=$[$sheettot+1] Maak een nieuw Werkblad
?
 !exit
!endif

!if bad_sheet=$error
 Werkbladnummer is incorrect.
 !exit
!endif

!if too_many_exos=$error
Het werkblad $picksheet heeft het maximum van $max_exos items reeds bereikt
Verwijder eerst enkele items alvorens verder te gaan met dit werkblad.
 !exit
!endif

!if already_exist=$error
Het werk dat U wilt toevoegen bestaat reeds in het werkblad $test .<br />
U kunt beter niet een zelfde oefening meerdere keren onder dezelfde
parameters in een werkblad opnemen. <br />
Verander eerst enkele parameters van de oefening voordat U verder gaat. <br />
Of wilt U soms dat leerlingen deze sommen vaker maken?...verhoog dan gewoon het vereiste
punten aantal voor deze sommen.
!exit
!endif

!if $error=bad_exo
    Er kan geen serie oefeningen worden gevonden die voldoet aan deze informatie.
 !exit
!endif

!if $error=not_exo
    De module kan niet worden toegevoegd aan het werkblad: het is geen module met oefeningen!
 !exit
!endif

!msg $error
