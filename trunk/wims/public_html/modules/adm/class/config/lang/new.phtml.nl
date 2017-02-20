
!if $backdays>7
 !if $backdays>100
    <p>Van uw klas in meer dan 100 dagen geen backup gemaakt.</p>
 !else
    <p>De laatste backup van uw klas was $backdays geleden.</p>
 !endif
 !if backup iswordof $warn
  <p><span class="wims_warning">$wims_name_warning</span>.
  Het is de verantwoordelijkheid van de individuele docent een backup te maken van de virtuele ruimte.<br />
  Deze server computer zal zonder expliciet contact met de systeembeheer <b>geen backups</b> van virtuele klassen aanmaken.
 !else
  <p>
  Bescherm Uw virtuele klassen tegen onvoorzien data verlies !
 !endif
 !href cmd=reply&job=arch Backup uw klassen
 regelmatig
 </p>
!endif

!if creation iswordof $warn
 <p><span class="wims_warning">WAARSCHUWING</span>.
 Uw virtuele klas is $creatdays oud: dit is te oud !
 </p><p>
 Het is dringend aan te bevelen een nieuwe klas op te richten aan het begin van
 een schooljaar.
 </p>
 !if $class_type notin 13
  <p>
  Hier kan een nieuwe virtuele klas oprichten, zonder dat er belangrijk lesmateriaal verloren gaat:
  </p><ol>
  <li>
  Maak een
  !href cmd=reply&job=arch backup
  van de klas aan het einde van het schooljaar.
  </li><li>
  <a href="$wims_ref_name?lang=$lang&+module=adm/class/regclass">Maak</a>
  een nieuwe virtuele klas (of een groepje klassen, of een kompleet instituut)
  aan het begin van het schooljaar.
  </li><li>
  Installeer het lesmateriaal in de nieuwe klas, met de backupfile.<br />
  <span class="small">(zonder de overbodige leerling accounts en scores)</span>
  </li></ol>
 !else
  <p>
  Maak een
  !href cmd=reply&job=arch backup
  van alle lesmateriaal van uw huidige klas; hiermee kan een nieuwe klas worden gevuld.
  </p>
 !endif
!endif
!exit
!if $warn=$empty
 !set job=list
 !changeto list.phtml
!else
  <div class="wimscenter">
  !href cmd=reply&job=list Doorgaan
  met het klasse onderhoud.
 </div>
!endif


