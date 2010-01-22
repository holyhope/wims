!goto $wims_read_parm

:pass

<center><h2>Aanmeldings wachtwoorden</h2></center>

Er zijn twee soorten wachtwoorden voor de aanmelding (registratie):
<p>
Het aanmeldings wachtwoord voor het <b>portaal</b> is voor docenten.<br>
Dit wachtwoord mag <tt><b>nooit</b></tt> worden verstrekt aan studenten.<br>
Omdat iedereen die zich aanmeld bij deze portaal wordt gezien als docent (met de bijhorende bevoegdheden).
<p>
Het aanmeldings wachtwoord voor een klas of voor een cursus is bedoeld voor studenten.<br>
Leeringen moeten zich aanmelden voor een bepaalde klas.
Een aanmelding in een bepaalde klas, maakt de student automatisch deelnemer voor het gehele instituut.
<p>
Alleen klassen en ook sommige cursussen vereisen een aanmeldings wachtwoord,
omdat andere zones (leerlniveau's, lesprogramma's) geen leerling automatisch accepteren.
<p>
U kunt ook een aanmeldings wachtwoord vastleggen (of veranderen) voor een compleet leerniveau.<br>
Dit wachtwoord wordt dan automatisch ook gebruikt als het "aanmeldings wachtwoord" voor alle cursussen en klassen onde dat leerniveau.
<p>
Laat het invulveld leeg wanneer U alleen enkele eigenschappen wilt veranderen (dus wanneer
U het wachtwoord niet wilt veranderen).




!exit
:passs

<center><h2>Supervisor wachtwoord</h2></center>

Dit wachtwoord is vereist voor docenten om supervisor bevoegdheden 
te krijgen op leerniveau, klas, lesprogramma of cursus.
De standaard instelling is het supervisor wachtwoord van de bovengeordende zone.
<p>
Laat het wachtwoord veld leeg 
als U nu het wachtwoord niet wilt veranderen.

!exit

:progopt

<center><h2>Opties voor een lesprogramma</h2></center>

Als een lesprogramma <em>verplicht</em> is, 
worden alle studenten in een klas automatisch geregistreerd bij deze cursus.
Dus alle cursussen zijn verplicht in alle corresponderende klassen.
<p>
Aan de andere kant, voor een <em>optioneel</em> 
lesprogramma , moeten de studenten
zichzelf aanmelden voor de cursussen. 
<p>
Als de automatische cursusinstallatie van het lesprogramma op "ja" staat, wordt
voor elke klas op dit leerniveau, de cursus aangemaakt.
Een cursus van dit lesprogramma wordt ook automatisch 
voor elke nieuw te maken klas op dit leerniveau aangemaakt. 
<p>
Wanneer de automatische cursusinstallatie van het lesprogramma op "nee" staat, moeten
de cursussen bij dit lesprogramma op dit leerniveau handmatig worden aangemaakt. 


!exit

:sechost
!reset wims_prefix
!set special_parm2=secure
!read wimshome/public_html/modules/adm/class/config.$lang/help/config.phtml

!exit

:structure

!read help/$lang/structure.phtml

!exit

:supervisor
<center><h2>De supervisor van een zone</h2></center>

Elke zone (leerniveau, klas, lesprogramma, cursus) van een institutionele structuur 
heeft een supervisor.
Dit is meestal een docent, die toegang heeft tot de management pagina van het instituut .  
<p>
De default instelling is dat de supervisor ook administrator rechten heeft voor alle onderliggende structuren.
<p>
Uiteraard, kunnen ook andere docenten (in het bezit van het supervisor wachtwoord) ook deze
management zone gebruiken voor configuratie en onderhoud.
Het verschil is dat de alleen "officiele" supervisor naam en emailadres wordt getoond aan alle 
deelgebieden van deze zone.

!exit
