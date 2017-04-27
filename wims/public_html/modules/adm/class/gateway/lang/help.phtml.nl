!goto $wims_read_parm

:pass

<h2 class="wimscenter">Aanmeldings wachtwoorden</h2>
<p>
Er zijn twee soorten wachtwoorden voor de aanmelding (registratie):
</p><p>
Het aanmeldings wachtwoord voor het <b>portaal</b> is voor docenten.<br />
Dit wachtwoord mag <tt><b>nooit</b></tt> worden verstrekt aan studenten.<br />
Omdat iedereen die zich aanmeld bij deze portaal wordt gezien als docent (met de bijhorende bevoegdheden).
</p><p>
Het aanmeldings wachtwoord voor een klas of voor een cursus is bedoeld voor studenten.<br />
Leeringen moeten zich aanmelden voor een bepaalde klas.
Een aanmelding in een bepaalde klas, maakt de student automatisch deelnemer voor het gehele instituut.
</p><p>
Alleen klassen en ook sommige cursussen vereisen een aanmeldings wachtwoord,
omdat andere zones (leerlniveau's, lesprogramma's) geen leerling automatisch accepteren.
</p><p>
U kunt ook een aanmeldings wachtwoord vastleggen (of veranderen) voor een compleet leerniveau.<br />
Dit wachtwoord wordt dan automatisch ook gebruikt als het "aanmeldings wachtwoord" voor alle cursussen en klassen onde dat leerniveau.
</p><p>
Laat het invulveld leeg wanneer U alleen enkele eigenschappen wilt veranderen (dus wanneer
U het wachtwoord niet wilt veranderen).
</p>

!exit
:passs

<h2 class="wimscenter">Supervisor wachtwoord</h2>
<p>
Dit wachtwoord is vereist voor docenten om supervisor bevoegdheden 
te krijgen op leerniveau, klas, lesprogramma of cursus.
De standaard instelling is het supervisor wachtwoord van de bovengeordende zone.
</p><p>
Laat het wachtwoord veld leeg 
als U nu het wachtwoord niet wilt veranderen.
</p>
!exit

:progopt

<h2 class="wimscenter">Opties voor een lesprogramma</h2>
<p>
Als een lesprogramma <em>verplicht</em> is, 
worden alle studenten in een klas automatisch geregistreerd bij deze cursus.
Dus alle cursussen zijn verplicht in alle corresponderende klassen.
</p><p>
Aan de andere kant, voor een <em>optioneel</em> 
lesprogramma , moeten de studenten
zichzelf aanmelden voor de cursussen. 
</p><p>
Als de automatische cursusinstallatie van het lesprogramma op "ja" staat, wordt
voor elke klas op dit leerniveau, de cursus aangemaakt.
Een cursus van dit lesprogramma wordt ook automatisch 
voor elke nieuw te maken klas op dit leerniveau aangemaakt. 
</p><p>
Wanneer de automatische cursusinstallatie van het lesprogramma op "nee" staat, moeten
de cursussen bij dit lesprogramma op dit leerniveau handmatig worden aangemaakt. 
</p>

!exit

:sechost
!reset wims_prefix
!set special_parm2=secure
!read wimshome/public_html/modules/adm/class/config/lang/help.$moduclass_lang/config.phtml

!exit

:structure

!read help/$moduclass_lang/structure.phtml

!exit

:supervisor
<h2 class="wimscenter">De supervisor van een zone</h2>
<p>
Elke zone (leerniveau, klas, lesprogramma, cursus) van een institutionele structuur 
heeft een supervisor.
Dit is meestal een docent, die toegang heeft tot de management pagina van het instituut .  
</p><p>
De default instelling is dat de supervisor ook administrator rechten heeft voor alle onderliggende structuren.
</p><p>
Uiteraard, kunnen ook andere docenten (in het bezit van het supervisor wachtwoord) ook deze
management zone gebruiken voor configuratie en onderhoud.
Het verschil is dat de alleen "officiele" supervisor naam en emailadres wordt getoond aan alle 
deelgebieden van deze zone.
</p>
!exit

:addcsvclass
<h2>Het toevoegen van klassen door een bestand te importeren.</h2>

<p>
Om klassen te importeren via een spreadsheet, bewaar de klasse data in een spreadsheet text formaat (txt, csv, or tsv), 
en stuur dit bestand naar de server.
</p>
$table_header
<caption>geldige data</caption>
$table_hdtr<th scope="col">naam</th><th scope="col">betekenis</th></tr>
$table_tr<td class="tt wims_code_variable">cname</td><td>naam van de klas</td></tr>
$table_tr<td class="tt wims_code_variable">login</td><td>login naam van de docent.</td></tr>
$table_tr<td class="tt wims_code_variable">regpass</td><td>klasse wachtwoord (voor aanmeling leerlingen)</td></tr>
$table_tr<td class="tt wims_code_variable">secure</td><td>een IP adress of woord "all".</td></tr>
$table_tr<td class="tt wims_code_variable">limit</td><td>maximaal aantal leerlingen.</td></tr>

De kolommen "regpass", "secure", "limit" zijn niet verplicht.
Indien afwezig worden de standaard instellingen van het instituut gebruikt
$table_end
!exit
