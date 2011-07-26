!set wims_module_log=error: $error

<b>$wims_name_Error</b>.

!if not_supervisor=$error
Helaas, deze handeling is alleen voor de supervisor van een klas bedoeld. 
 !exit
!endif

!if not_superclass=$error
 Deze handeling kan alleen door de administrator van de digischool worden uitgevoerd.
 !exit
!endif

!if bad_classpass=$error
Helaas, U hebt niet het juiste wachtwoord ingevuld.
U kunt dus de gegevens niet wijzigen. 
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
 U moetr eerst een 
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
De student <tt class="wims_login">$checkuser</tt> komt niet voor in de database.
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

!msg $error

