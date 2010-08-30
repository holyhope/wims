!set wims_module_log=error: $error

<b>Fout</b>.

!if bad_auth iswordof $error
    Het inloggen is mislukt. Probeer opnieuw.
 !exit
!endif

!if bad_pass iswordof $error
 Wachtwoord is niet goed: het mag alleen letters en cijfers bevatten, 
 en de lengte moet tussen de 4 en 16 lettertekens zijn.
 En het herhaald ingetypte wachtwoord moet natuurlijk wel gelijk zijn aan de eerste keer! Probeer het nog eens.
 !exit
!endif

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

