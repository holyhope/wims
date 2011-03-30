!set wims_module_log=error: $error

!if not_supervisor=$error
Helaas, maar het maken of modificeren van een proefwerk
is voorbehouden aan de docent van een klas. 
 !exit
!endif

!if $error=no_sheet
De inhoud van een proefwerk kan alleen worden genomen
uit een <em>actief</em> of <em>verlopen</em> <b>werkblad</b>
 <p>
 Uw klas heeft echter geen werkbladen (actief of verlopen). <br>
 Dus eerst maakt U een werkblad van Uw oefeningen (oef of module)<br>
 onderaan een oefening/som staan de link <b>"toevoegen aan werkblad"</b><br>
 Daarna maakt U van deze actieve/verlopen werkbladen het echte proefwerk.
 !exit
!endif

!if bad_exam=$error
Uw proefwerk nummer is helaas niet geldig...een bug in de software? 
 !exit
!endif

!if $error=simuchange
    De status van dit proefwerk heeft U net veranderd.<br>Klik 
 !href cmd=reply&job=scorereg hier
 om deze simulatie correct af te sluiten.
 !exit                                                                                                                                     
!endif

!if already_registered=$error
Je cijfer staat al genoteerd.
 !exit
!endif

!if no_more_registration=$error
Dit proefwerk mocht je $stries keer maken.<br>
Jij mag het proefwerk dus niet meer overdoen.
 !exit
!endif

!if bad_source=$error
 Het item nummer $bad_source in de broncode, dat net is opgestuurd is helaas ongeldig
 !href cmd=reply&job=prep_putsource&source=$source Verbeter de broncode
 .
 !exit
!endif

!if no_title=$error
U wilt een proefwerk registreren zonder een naam ? 
niet verstandig. Fout of manipulatie ?
 !exit
!endif

!if prep_activate=$error
U wilt het proefwerk $exam activeren en dus beschikbaar stellen aan Uw leerlingen. <p>
Besef dat een proefwerk eenmaal geactiveerd niet meer kan worden veranderd.<br>
Wilt U doorgaan?
 <p><center>
 !href cmd=reply&job=activate $wims_name_yes; $(wims_name_actionlist[1])
 .&nbsp;&nbsp;
 !href cmd=resume $wims_name_no; $wims_name_giveup
 . </center>
 !exit
!endif

!if prep_erase=$error
Wil U werkelijk het proefwerk nummer $exam ($title) verwijderen?
 <p><center>
 !href cmd=reply&job=erase $wims_name_yes; $wims_name_erase
 .&nbsp;&nbsp;
 !href cmd=resume $wims_name_no; $wims_name_giveup
 . </center>
 !exit
!endif

!if prep_expire=$error
Dit proefwerk nummer $exam ($title) zou verlopen zijn op $expday
 !item $expmon of $months
 $expyear. wilt U het <b>nu</b> laten verlopen?
 <p><center>
 !href cmd=reply&job=expire $wims_name_yes; $(wims_name_actionlist[2])
 .&nbsp;&nbsp;
 !href cmd=resume $wims_name_no; $wims_name_giveup
 . </center>
 <p><b>Opmerking.</b> 
 Uw leerlingen kunnen niet doorgaan met het werken aan een verlopen proefwerk.<br>
Maar hun reeds behaalde cijfers voor dit proefwerk worden wel bewaard.
(en ook statistisch verwerkt, zodat deze resultaten altijd nog kunnen worden bekeken) 
 !exit
!endif

!if nodeactivate=$error
    Dit proefwerk kan niet worden gedeactiveerd omdat
  !if badstructure isin $deactivate
   de structuur van dit instituut dit niet toestaat.
  !else
   !if score isin $deactivate
    enkele studenten al zijn begonnen met dit proefwerk !
   !else
    het wordt gedeeld met een andere klas !
   !endif
  !endif
!endif

!if active_exam=$error
    Helaas, maar dit proefwerk is aktief en daardoor niet meer te veranderen.<br>
    We kunnen dus ook niets aan de opgenomen oefeningen meer wijzigen. 
 !exit
!endif 

!if $error=prep_noexercise
    De oefening $exo uit dit proefwerk is leeg. Probeer opnieuw.
  !exit
!endif

!msg $error