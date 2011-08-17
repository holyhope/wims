!! définition des noms pour les liens dans le menubox (définis par wims_menu_items)
!distribute items Broncode toevoegen,\
		Zo zien studenten deze pagina,\
		Broncode van het werkblad \
into wims_name_putsource,wims_name_participantview,wims_name_sheetsource

!distribute items Voeg een oefening toe,\
Voeg een serie oefeningen toe,\
into wims_name_addexo,wims_name_addsexo

!set name_desc_title=!nosubst Maximaal $title_limit lettertekens
!set name_desc_desc=!nosubst Maximaal $desc_limit lettertekens; html tags en links zijn toegestaan

!let name_shinfo=!nosubst $wims_name_title,$wims_name_Status,\
Uitleg,\
Verloopdatum,Presentatie pagina,Cijfer registratie,voor alle klassen die aan het proefwerk meedoen :,Opmerkingen,Maximaal beschikbare tijd voor een proefwerk,Aantal pogingen per proefwerksessie

!let name_allowtype=open voor iedereen,in simulatiemode,gesloten voor iedereen,open voor de volgend ipadressen (en/of tijdstippen) :
!if exam notin $module
 !let name_allowtype=$(name_allowtype[1]),$(name_allowtype[3]),$(name_allowtype[4])
!endif

!set name_desc_comment=Alleen zichtbaar voor docenten.
!let name_selectsheet=Laat alleen oefeningen zien uit werkblad

!if $job=student
  !set name_title=Werkblad nummer $sheet<br>$title (Presentatie voor studenten)
  !set name_assignedwork=Opdrachten in dit werkblad&nbsp;
  !set name_quality=0 uit $[$re] punten behaald, kwaliteit
!endif

!set name_sheetempty=Het werkblad is leeg! Dit is waarschijnlijk een fout.

!set name_deps=Je cijfers voor deze oefeningen moeten verbeterd worden
!set name_dep=Je cijfer voor deze oefening moet verbeterd worden
!set name_dep2=voor dat je deze oefening mag proberen.

!distribute items Gewicht,Co&euml;fficient\
into name_weight,name_coeff

!set name_dependency=Cijfer afhankelijkheden&nbsp;
