!set wims_module_log=error: $error

<span class="wims_warning">$wims_name_Error</span>.

!if empty_data iswordof $error
 !distribute items $wims_name_title,$wims_name_Description,$wims_name_Type into tmp_title, tmp_description, tmp_category

 Vul het definitieveld
 <span class="tt wims_warning">$(tmp_$(empty_data)</span>
 van uw module in.
 !exit
!endif

!if bad_fname iswordof $error
 Ongeschikte bestandsnaam. Kies een andere naam voor dit bestand.
 !exit
!endif

!if binary_file iswordof $error
 Binaire bestanden zijn hier niet toegestaan.
 !exit
!endif

!if illegal_filedesc iswordof $error
    U kunt niets anders dan een omschrijving in de "<span class="tt wims_fname">filedesc</span>
    vermelden.
 !exit
!endif

!if badoriginal iswordof $error
 Deze module kan niet worden gekopieerd.
 !exit
!endif

!if clash iswordof $error
 De module bestaat reeds.
 !exit
!endif

!if badtarget iswordof $error
 Het adres van de module is niet goed: te lang,te kort, inkompleet
  of niet toegestane lettertekens
  <ul>
  !if incorrect_t1 iswordof $error
   <li>incorrecte zone</li>
  !endif
  !if incorrect_t2 iswordof $error
   <li>incorrecte categorie</li>
  !endif
  !if incorrect_t3 iswordof $error
   <li>incorrecte naam</li>
  !endif
  !if incorrect_t4 iswordof $error
   <li>incorrecte taal</li>
  !endif
  !if incorrect_tlen iswordof $error
   <li>adres te lang of te kort</li>
  !endif
 </ul>
 !exit
!endif

!if symlink iswordof $error
 De module code kan niet worden gekopieerd, omdat deze
 symbolische links bevat.
 !exit
!endif

!msg $error
