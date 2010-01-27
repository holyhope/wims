!goto $wims_read_parm
 
:1
<ul>
<li>
 Een indiviuele klas is bedoeld voor een enkele docent en zijn/haar leerlingen. 
</li>
<li>
 Een gemeenschappelijke ingang voor een groepje klasses [een soort digi-school]<br>
 geeft leerlingen de mogelijkheid om zonder wachtwoorden over te stappen naar <br>
 andere klassen [andere vakken of cursussen].<br>
 Voor docenten is er de mogelijkheid om lesmateriaal te delen en samen<br>
 met collega&rsquo;s lesmateriaal te ontwikkelen.<br>
 Ook kan een docent meerdere klassen beheren.
</li>
<li>
 Een instituut is een groep multi-level klassen.<br>
 Op verschillende niveaus kunnen dwarsverbanden worden gecreerd tussen cursussen,<br>
 lesprogramma's ,lesmateriaal, docenten en studenten.<br>
 Op alle leerniveaus kunnen meerdere gemeenschappelijke ingangen worden gemaakt.<br>
 [voor verschillende vakken, cursussen examentraining  etc.]<br>
 Dit alles kan centraal worden beheerd.
</li>
</ul>    
!exit
:2
 
Het oprichten van
!if $Cltype<2
    een klas is voorbehouden aan een docent.
!else
    <font color="blue">$name_classe</font>
     is voorbehouden aan de administrator.
!endif
<br>
<small>
    Voor deze handeling is een werkend emailadres noodzakelijk.<br>
    Nadat uw klas $name_classe is opgericht, bent U verantwoordelijk voor het onderhoud ervan.
</small>
<p>
Voor het oprichten de onderstaande vragen beantwoorden :
!exit
 
:step1
Hallo , $supervisor! <p>
U bent begonnen met het oprichten van
!if $Cltype<2
 een
!else
 een
!endif
$name_classe $classname op de WIMS server van $httpd_HTTP_HOST,
!if $Cltype iswordof 0 1
 !let tmp=!positionof item $ilevel in $levelid
 op leerniveau ``<b><font color=green>$(leveldesc[$tmp])</font></b>'',
!endif
en met de verloopdatum $exp_day/$exp_month/$exp_year .
Het maximum toegestane aantal  studenten in $classname is $ilimit . 
Het aanmelden van nieuwe leerlingen 
!if $pword!=$empty
 is beveiligd door het wachtwoord $name_classesss.
!else
 vrij. 
<small> weet U wel zeker dat deze site dat toestaat ?</small> 
!endif
<p>
U kunt deze instellingen nog steeds
!href module=$module&cmd=reply&step=0 corrigeren.
<p>
Als laatste controle: voer nog &eacute;&eacute;n keer het wachtwoord in:
!exit

:step2
 
Welkom , $supervisor ! 
<p>
Om de aanmeldings procedure van $name_classe op de WIMS site $httpd_HTTP_HOSTte voltooien, 
vul daarvoor hier de code in die zojuist naar het opgegeven emailadres ``<tt>$email</tt>'' is gestuurd.

!exit

:step3

Hallo , $supervisor!<p>
Uw $name_classe $classname is aangemaakt. Gefeliciteerd en veel plezier !<p>
Het aantal deelnemers is beperkt tot $ilimit participants.

!exit
