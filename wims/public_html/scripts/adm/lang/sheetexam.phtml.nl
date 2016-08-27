!! définition des noms pour les liens dans le menubox (définis par wims_menu_items)
!distribute items Broncode toevoegen,\
Broncode van het werkblad \
into wims_name_putsource,wims_name_sheetsource

!distribute items Voeg een oefening toe,\
Voeg een serie oefeningen toe,\
into wims_name_addexo,wims_name_addsexo

!set name_desc_title=!nosubst Maximaal $title_limit lettertekens
!set name_desc_desc=!nosubst Maximaal $desc_limit lettertekens; html tags en hyperlinks zijn toegestaan

!let name_shinfo=!nosubst $wims_name_title,$wims_name_Status,\
Uitleg,\
Verloopdatum,Presentatie pagina,Cijfer registratie,voor alle klassen die aan het proefwerk deelnemen :,Opmerkingen,Maximaal beschikbare tijd voor een proefwerk,Aantal pogingen per proefwerksessie

!let name_allowtype=open voor iedereen,in simulatiemode,gesloten voor iedereen,open voor de volgende ip-adressen (en/of tijdstippen) :,volgens technische variabelen

!if exam notin $module
 !let name_allowtype=$(name_allowtype[1,3,4,5])
!endif
!set name_desc_allowtechvar=Kies de technische variabele
!set name_desctableval=Filterinstellings tabel voor de technische variabelen
!set name_value=Waarde
!set name_filtre=Filter
!set name_EMPTY=Leeg

!set name_desc_comment=Alleen zichtbaar voor docenten.
!let name_selectsheet=Laat alleen oefeningen zien uit werkblad

!if $job=student
  !set name_title=Werkblad nummer $sheet<br/>$title (Presentatie voor studenten)
  !set name_assignedwork=Opdrachten in dit werkblad&nbsp;
  !set name_quality=0 uit $[$re] punten behaald, kwaliteit
!endif

!set name_sheetempty=Het werkblad is leeg! Dit is waarschijnlijk een fout.

!set name_deps=Je cijfers voor deze oefeningen moeten verbeterd worden
!set name_dep=Je cijfer voor deze oefening moet verbeterd worden
!set name_dep2=voordat je deze oefening mag proberen.

!distribute items Gewicht,Co&euml;fficient,Score\
into name_weight,name_coeff,name_Score

!set name_dependency=Cijfer afhankelijkheden&nbsp;
