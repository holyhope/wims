!set wims_module_log=error: $error

<span class="wims_warning">$wims_name_Error</span>.

!if not_supervisor=$error
Helaas, deze handeling is alleen voor de supervisor van een klas bedoeld.
 !exit
!endif

!if not_superclass=$error
 Deze handeling kan alleen door de administrator van de digischool worden uitgevoerd.
 !exit
!endif

!if no_login iswordof $error
De opgestuurde data moeten wel een kolom bevatten met de
loginnaam van de student.
 !exit
!endif

!if bad_filename iswordof $error
Het opgestuurde bestand lijkt niet op "spreadsheet data in tekstformaat"
:csvformat

Bewaar spreadsheet data als een tekstformaat.
(dus komma_gescheiden of tab_gescheiden lijsten (met als extensie: *.csv *.tsv *.txt)
 voor dat ze naar deze server worden gestuurd.
 !exit
!endif

!if binary_upload iswordof $error
Uw spreadsheet data zijn in binair formaat en wordt uiteraard niet geaccepteerd.
 <p>
 !goto csvformat
!endif

!if no_manual iswordof $error
 U moet eerst een
 !href module=adm/class/grades handmatige
 &nbsp;cijfer kolom aanmaken, voordat deze gevuld kan worden met opgestuurde data.
 !exit
!endif

!if not_secure iswordof $error
Helaas, spreadsheet data upload/download zijn alleen beschikbaar vanaf
de zogenaamde "secure hosts".
Ga naar de configuratie pagina van Uw klas om deze instellingen te bekijken, en eventueel aan te passen.
 !exit
!endif

!if bad_user=$error
De student <span class="tt wims_login">$checkuser</span> komt niet voor in de database.
!exit
!endif

!if $error iswordof login_missing login_empty
!! login_missing: not find in the ldap for example : should be more precise ??
    Sommige login accounts konden niet gevonden worden.
 !exit
!endif

!if bad_exo=$error
Dat werkblad/document bestaat niet.
!exit
!endif

!if bad_op=$error
<span class="wims_warning">Ongeldige bewerking</span>.
Sluit dit venster.
!exit
!endif
!if too_big=$error
  The number of columns of the spreadsheet is too big (greater than $TOO_BIG).
  If you need the details of the exercices, you can do it sheet by sheet or
  exam by exam. The file to download does not give you all the informations you asked.
 !exit
!endif
!msg $error

