!goto $wims_read_parm
!exit

:allowtype
<center><b>Openingstijden van een proefwerk</b></center>
 U kunt openingstijden definieren voor dit proefwerk, door het toevoegen van woorden
 <tt class="wims_code_words">
&gt;yyyymmdd.hh:mm</tt>
 (openingstijd) en/of
 <tt class="wims_code_words">
&lt;yyyymmdd.hh:mm</tt>
 (sluitingstijd). 
 Deze tijden moeten worden aangegeven in de lokale tijd van deze SERVER,
 en moeten worden gescheiden door spaties.
 <br>
 Formaat van de tijden <tt>yyyymmdd.hh:mm</tt> (bij meerdere opties deze scheiden door spaties).
!exit

:dependency
<center><b>Score drempels</b></center>  
Score drempels dit wil zeggen dat een deelnemer/leerling een bepaalde hoeveelheid punten <br>
moet behalen voor dat de volgende som/opdracht uit het proefwerk bereikbaar wordt.<br>
We noemen dit toets-type een "drempel toets".<br>
Bijvoorbeeld:  <font color="blue"><tt>1:50,2:30,3+4+5:60</tt></font> wil zeggen dat<br>
de leerling minimaal 50% goed moet hebben van opdracht 1, 30% van opdracht 2 en opdracht 3,4,5 samen gemiddeld minimaal 60%.
!exit

:options
<center><b>Opties.</b></center>
Er is op dit moment slechts &eacute;&eacute;n optie beschikbaar :
<ul>                                                                                                                                
<li><em>autogen</em><br>
Alleen voor experts en voor het handmatig bijwerken van score resultaten.<br>
Autogen: betekent dat de oefening automatisch wordt uitgevoerd [automatische piloot...],<br>
zelfs als de gebruiker nergens op klikt.<br>
De gebruiker kan dit proefwerk dan raadplegen als de score registratie is afgelopen en de sessie reeds is afgesloten.  
!exit

:contenu
 <center><b>Inhoud van een proefwerk</b></center>
Een oefening kan willekeurig worden genomen uit de lijst van bestaande oefeningen uit de werkbladen.<br>
Vink de werkbladen aan in de onderstaande lijst als kandidaten voor dit proefwerk.
!exit