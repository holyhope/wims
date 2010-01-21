!goto $wims_read_parm

:pass

<center><h2>Aanmeldings wachtwoorden</h2></center>
Er zijn twee soorten wachtwoorden voor de aanmelding (registratie):
<p>
Het aanmeldings wachtwoord voor het <b>portaal</b> is voor docenten.<br>
Dit wachtwoord mag <tt><b>nooit</b></tt> worden verstrekt aan leerlingen.<br>
Omdat iedereen die zich aanmeld bij deze portaal wordt gezien als docent (met de bijhorende bevoegdheden).
<p>
Het aanmeldings wachtwoord voor een <b>klas</b> of voor een cursus is bedoeld voor studenten/leerlingen.<br>
Leeringen moeten zich aanmelden voor een bepaalde klas.
(maar een aanmelding in een bepaalde klas, geldt natuurlijk voor het gehele instituut.)
<p>
Alleen klassen en ook sommige cursussen vereisen een aanmeldings wachtwoord,
omdat andere zones (nivo, programma) geen leerling aanmeldings accepteren.
<p>
U kunt ook een aanmeldings wachtwoord vastleggen (of veranderen) voor een compleet "niveau".<br>
Dit wachtwoord wordt dan gebruikt als het "default aanmeldings wachtwoord" voor alle cursussen en klassen.
<p>
Laat het invulveld leeg wanneer U alleen enkele eigenschappen wilt veranderen (dus wanneer
U het wachtwoord niet wilt veranderen).




!exit
:passs

<center><h2>Supervisor wachtwoord</h2></center>

Dit wachtwoord is vereist om docenten toegang te geven tot het managen van een niveau, klas, programma of cursus.
De default instelling is het supervisor wachtwoord van de bovengeordende zone.
<p>
Laat het wachtwoord veld leeg als U nu het wachtwoord niet wilt veranderen.

!exit

:progopt

<center><h2>Opties voor een lesprogramma</h2></center>
Als een programma <em>verplicht</em> is, worden alle leerlingen in een klas die deze
kursus moeten volgen, automatisch geregistreerd bij deze kursus.
Dus alle cursussen zijn verplicht in alle corresponderende klassen.
<p>
Aan de andere kant, voor een <em>optioneel</em> programma , moeten de studenten
zichzelf aanmelden voor de kursussen. 
<p>
Als de automatische cursusinstallatie van het lesprogramma op "ja" staat, wordt
voor elke klas op dit niveau, de kursus aangemaakt.
Een kursus van dit lesprogramma wordt ook -automatisch- voor elke nieuwe klas op dit niveau aangemaakt. 
<p>
Wanneer de automatische cursusinstallatie van het lesprogramma op "nee" staat, moeten
de cursussen bij dit programma -op dit niveau- handmatig worden aangemaakt. 


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


<center><h2>
De supervisor van een zone
</h2></center>
Elke zone (niveau, klas, programma, cursus) van een institutionele structuur
(simpelweg: digitale school) heeft een supervisor.
Dit is meestal een docent, die het gehele managment van zo'n zone gaat bepalen.  
<p>
Uiteraard, kunnen ook andere docenten (in het bezit van het supervisor wachtwoord) deze
management zone gebruiken voor configuratie en onderhoud.
Het verschil is dat de alleen "officiele" supervisor_naam en emailadres wordt getoond aan alle 
deelgebieden van deze zone.

!exit
