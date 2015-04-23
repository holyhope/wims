!set lang_exists=yes

!set wims_name_sheetcheck=Bekijk dit Werkblad
!set wims_name_moduback=Terug naar de module

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
!set name_endallexo=!nosubst $addexo séries d'exercices ont été insérées avec succès dans la feuille <span class="wims_mod_title">$title</span>.
!set name_endallexo2=!nosubst Les $notadd ressources suivantes n'ont pas pu être insérées car elles existaient déjà : 


!set name_choose_exo=Wordt toegevoegd aan het werkblad als een nieuwe serie oefeningen
!set name_choose_helpexo=De ondersteunende oefeningen worden aangeboden als de score voor het werkblad lager is dan
!set name_choose_series=Klik op de serie oefeningen waarvoor ondersteuning moet worden aangeboden.
!set name_actualhelp=Ondersteuning bij dit onderwerp
!set name_series=Serie oefeningen
!set name_orderchange=Verander de volgorde van de oefeningen


!if $job=addallexo
!! il s'agit d'une copie de la partie intro du fichier oef/lang/names
 !distribute line Helaas, er is geen enkele oefening beschikbaar op dit moment. Kom later nog eens terug !\
 Deze module bevat op dit moment slechts een enkele oefening\
 Laat zien.\
 Kies de oefening&nbsp;\
 Oefeningen over\
 Een serie heeft\
 Moeilijkheidsgraad\
 Tijdslimiet\
 seconden\
 Het aantal items bij een meerkeuze vraag\
 Geef een uitgewerkte oplossing (mits aanwezig)\
 Simpel menu\
 Expert menu\
 Alleen oefeningen met in de titel het woord\
 oefeningen\
 Oefening configureren\
into name_noexercise,name_oneexercise,name_tryit,name_chooseexo,name_exercisescontaining,name_oneserie,\
name_levelseverity,name_chrono,name_secondes,name_qcmanswer,name_solutiongiven,\
name_simplifiedmenu,name_expertmenu,name_select,name_exercices,name_menu

 !set name_datamodule=Deze module heeft de data module <span class="tt">$module_data</span> nodig \
 om correct te functioneren.\
 Deze is niet ge&iuml;nstalleerd op deze server.\
 Vraag de systeembeheerder of deze alsnog ge&iuml;nstalleerd kan worden.

!set name_choice=nooit,alleen als de score niet maximaal is,altijd

!set name_choice_check=Altijd de goede oplossing bij een meerkeuze vraag laten zien,\
  Strafpunten bij een fout antwoord in een meerkeuze vraag.,\
  Laat het goede antwoord zien.,\
  Geef een tip (mits aanwezig).

!set name_aleaseries= Propose the exercises of the series in order.
!set name_remarkintro1=Nadat een eofenening is geselecteerd uit de lijst, \
klik op <span class="wims_button disabled">$wims_name_work</span>. \
De oefeningen worden willekeurig gekozen uit uw selectie. <br/>\
(of uit alle aanwezige oefeningen als er geen keuze lijst is aangegeven).

!!leave on one line
!set name_remarkintro3=Je kunt twee getallen aangeven in de tijdslimiet; een kleinere limiet gevolgd door een wat grotere. In dat geval is eerste getal de score  reductie, die loopt tot 0 als de tweede limiet bereikt is.

!endif
