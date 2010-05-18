!set wims_module_log=error: $error

!if no_pick=$error
Kies eerst een  
 !href cmd=resume werkblad 
 voor U op de <tt class="c">toevoegen</tt> drukt...
 !exit
!endif

!if not_supervisor=$error
Helaas, maar het veranderen van een werkblad is alleen toegestaan voor docenten van een klas.
 
 !exit
!endif

!if bad_class=$error
Vreemd, maar uw klas staat hier niet (meer?) geregistreerd !

 !exit
!endif

!if no_sheet=$error
Uw klas heeft -nog- geen werkbladen in voorbereiding .<br> 
Lesmateriaal of oefeningen kun men alleen toevoegen aan een nog <b>niet geactiveerd werkblad</b>.
 
 !href module=adm/class/sheet&sheet=$[$sheettot+1] Maak een nieuw Werkblad
?
 !exit
!endif
!if bad_sheet=$error
 Werkbladnummer is incorrect.
 !exit
!endif

!if insert_fail=$error
Door een fout in de software -maar meestal niet- kan ik Uw werk niet opnemen
in de database. Controleer even de data ! 
 !exit
!endif

!if too_many_exos=$error
Het werkblad $picksheet heeft het maximum van $max_exo items reeds bereikt
Verwijder eerst enkele items alvorens verder te gaan met dit werkblad.
 !exit
!endif

!if already_exist=$error
Het werk dat U wilt toevoegen bestaat reeds in het werkblad $test .<br>
U kunt beter niet een zelfde oefening meerdere keren onder dezelfde
parameters in een werkblad opnemen. <p>
Verander eerst enkele parameters van de oefening voordat U verder gaat. <p>
Of wilt U soms dat leerlingen deze sommen vaker maken?...verhoog dan gewoon het vereiste
punten aantal voor deze sommen. 
!exit
!endif

