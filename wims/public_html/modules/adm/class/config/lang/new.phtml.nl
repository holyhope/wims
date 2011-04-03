<p>
!if $backdays>7
 !if $backdays>100
    Van uw klas in meer dan 100 dagen geen backup gemaakt. 
 !else
    De laatste backup van uw klas was $backdays geleden.
 !endif
 !if backup iswordof $warn
  <p><span class="wims_warning">$wims_name_warning</span>.
  Het is de verantwoordelijkheid van de individuele docent een backup te maken van de virtuele ruimte.<br>
  Deze server computer zal -zonder contact met systeembeheer- <b>geen backups</b> van virtuele klassen aanmaken.
 !else
  <p>
  Bescherm Uw virtuele klassen tegen onvoorzien data verlies !
 !endif
 !href cmd=reply&job=arch Backup uw klassen 
 regelmatig
 <p>
!endif

!if creation iswordof $warn
 <p><b>WAARSCHUWING</b>.
 Uw virtuele klas is $creatdays oud: dit is te oud !
 <p>
 Het is dringend aan te bevelen een nieuwe klas op te richten aan het begin van 
 een schooljaar.
 !if $class_type notin 13
  <p>
  Hier kan een nieuwe virtuele klas oprichten, zonder dat er belangrijk lesmateriaal verloren gaat:
  <ol>
  <li>
  Maak een
  !href cmd=reply&job=arch backup
  </a> van de klas aan het einde van het schooljaar.
  </li><li>
  <a href="$wims_ref_name?lang=$lang&+module=adm/class/regclass">Maak</a>
  een nieuwe virtuele klas (of een groepje klassen, of een kompleet instituut)
  aan het begin van het schooljaar.
  </li><li>
  Installeer het lesmateriaal in de nieuwe klas, met de backupfile.<br>
  <small>(zonder de overbodige leerling accounts en scores)</small>
  </li></ol>
 !else
  <p>
  Maak een 
  !href cmd=reply&job=arch backup
  van alle lesmateriaal van uw huidige klas; hiermee kan een nieuwe klas worden gevuld.
 !endif
!endif

!if $warn=$empty
 !set job=list
 <p>
 !changeto list.phtml
!else
 <p><center>
  !href cmd=reply&job=list Doorgaan 
  met het klasse onderhoud.
 </center>
!endif


