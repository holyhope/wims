!set lang_exists=yes

!set wims_name_sheetcheck=Bekijk dit Werkblad
!!set wims_name_moduback=Terug naar de module

!set name_choose= Kies het werkblad waarin deze oefening moet worden opgenomen
!set name_title=Voeg een oefening toe aan een Werkblad

!set name_insert=Deze oefening toevoegen
!set name_parm=met "init parameters"
!set name_modifytitle=Er kan nu ook de titel en de omschrijving van het werkblad worden veranderd.

!set name_required=Het aantal punten dat minimaal wordt vereist voor deze opdracht
!set name_repeat=elk 100% correct antwoord levert 10 punten op: dus als er meer dan\
  10 punten wordt gevraagd moet de leerling deze opdracht meerdere keren doen.

!set name_weight=Het gewicht van de punten
!set name_weight_hint=deze weging wordt gebruikt voor de berekening van het gemiddelde
!set name_end=!nosubst De oefening <span class="wims_mod_title">$title</span> is succesvol opgenomen in het werkblad
!set name_endallexo=!nosubst een serie oefeningen is met succes opgenomen in werkblad <span class="wims_mod_title">$title</span>.
!set name_endallexos=!nosubst $addexo serie oefeningen zijn met succes opgenomen in werkblad <span class="wims_mod_title">$title</span>.
!set name_endallexo2s=!nosubst De volgende $notadd oefeningen zijn niet opgenomen, omdat deze reeds bestaan:
!set name_endallexo2=!nosubst De volgende oefening kon niet worden opgenomen, omdat deze reeds bestaat:
!set name_choose_exo=Wordt toegevoegd aan het werkblad als een nieuwe serie oefeningen
!set name_choose_helpexo=De ondersteunende oefeningen worden aangeboden als de score voor het werkblad lager is dan
!set name_choose_series=Klik op de serie oefeningen waarvoor ondersteuning moet worden aangeboden.
!set name_actualhelp=Ondersteuning bij dit onderwerp
!set name_series=Serie oefeningen
!set name_orderchange=Verander de volgorde van de oefeningen


!if $job=addallexo
  !read oef/nl/intronames
!endif
