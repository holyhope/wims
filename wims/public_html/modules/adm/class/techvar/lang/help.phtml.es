!if $wims_read_parm!=$empty
 !goto $wims_read_parm
!else
 Pas d'aide pour cette page.
 !exit
!endif

:listvar
Ce module permet de gérer les variables techniques :
<ul>
 <li> Création de variables techniques (limité à $MAXtechvar) ;</li>
 <li> Modification de la liste des valeurs possibles pour chaque variable technique ;</li>
 <li> Visualisation/Modification de la valeur des variables techniques pour chaque participant ;</li>
</ul>
<br/>
Il y a deux types de variables techniques : 
<ul>
 <li> Les variables techniques locales : ce sont celles que vous pouvez définir et modifier (leur nombre est limité à $MAXtechvar).</li>
 <li> Les variables techniques globales : ce sont celles de la structure (groupement de classe ou portail d'établissement) dans laquelle votre classe se trouve. Ces variables ne sont pas modifiables (elles le sont seulement par l'administrateur de la structure) mais vous pouvez les utiliser pour filtrer les élèves.</li>
</ul>

!exit

