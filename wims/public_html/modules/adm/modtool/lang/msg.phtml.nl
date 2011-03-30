!set wims_module_log=error: $error

<b>$wims_name_Error</b>.

!if empty_data iswordof $error
 Vul het definitieveld 
 <b><em><font color="red">$(name_$empty_data)</font></em></b>
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
    U kunt niets anders dan een omschrijving in de "filedesc"  
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
 !exit
!endif

!if symlink iswordof $error
 De module code kan niet worden gekopieerd, omdat deze 
 symbolische links bevat.
 !exit
!endif

!msg $error

