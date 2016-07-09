!if $wims_read_parm!=$empty
 !goto $wims_read_parm
!else
 Geen help-pagina aanwezig.
 !exit
!endif

:listvar
Met deeze module kunnen techniosche variabelen worden gedeklareerd:
<ul>
 <li> aanmaken  van technische variabelen (maximaal $MAXtechvar) ;</li>
 <li> varanderen van de lijst met waarden voor deze variabelen ;</li>
 <li> inzien en veranderen van de technische variabelen voor elke deelnemer;</li>
</ul>
Les variables techniques peuvent être utilisées pour faire certaines actions sur un groupe d'élèves de la classe (par exemple, pour limiter de manière sélective la durée d'ouverture de feuilles d'exercices ou d'examens, envoyer un message qu'à un groupe d'élèves ou faire apparaître un groupe d'élèves dans le tableau des résultats ...).
<br/>

Er zijn een tweetal types technische variabelen :
<ul>
 <li> Lokale variabelen : deze kan een docent aanmaken en veranderen (maixmumaal aantal $MAXtechvar).</li>
 <li> Globale variabelen : deze variabelen horen de hele school of instituut waar uw klas onderdeel van is. Deze variabelen zijn alleen veranderbaar door de supervisor van de school of instituut.Als docent kun u deze globale variabelen wel gebruiken (om te filteren etc)</li>
</ul>
<h3> Création d'une variable technique locale</h3>
Utilisez le menu <span class="tt wims_code_words">$name_addvar</span> afin de définir le nom et les valeurs possibles pour cette variable. 
<h3> Définition ou modification de la valeur d'une variable technique locale d'un élève</h3>
Pour définir ou modifier la valeur d'une variable technique locale d'un élève, il suffit de cliquer sur le lien <span class="tt wims_code_words">Liste des participants</span> à partir de la page <span class="tt wims_code_words">Gestion des variables techniques, </span> puis de cliquer sur le nom de l'élève dans la liste qui s'affichera. 
<br/>
Il est aussi possible d'entrer les valeurs d'une variable technique pour tous les participants à l'aide d'un fichier tableur  (voir l'aide de la page <span class="tt wims_code_words">Liaison tableur</span> pour connaitre le format du fichier tableur).  

!exit

