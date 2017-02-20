!if $special_parm!=$empty
 !goto $special_parm
!endif

:general
<p>
De filter-regels kunnen gelijktijdig worden gebruikt met het selecteren van loginnamen.
De email wordt verstuurd naar geselecteerde deelnemers.
Het filter wordt dan toegepast op deze lijst deelnemers.
Wordt er geen gebruik gemaakt van loginnamen,
 dan wordt de lijst met loginnamen uit de klas gebruikt.
</p>

:filter
!read help/nl/filter.phtml
