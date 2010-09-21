var oefcommandname='Commandes OEF';
var oefcommand = [
	"\\answer{}{}{}", "\\author{}", "\\computeanswer{}", "\\condition{}{}", "\\conditions{}", "\\email{}", "\\embed{}", "\\feedback{}{}",
	"\\function{}", "\\help{}", "\\hint{}", "\\integer{}", "\\language{}", "\\matrix{}",
	"\\precision{}", "\\solution{}", "\\special{}", "\\statement{}",
	"\\steps{}"
	];
	


function oefcommandfun(instruction){
	var index2="";
	switch(instruction)
	{
	//********************
	case "\\answer{}{}{}" :
		chaine_aide="La commande <code>\answer{texte}{\A}{type=un_type}{option=}{weight=}</code> exécute en général les actions suivantes&nbsp;:"+
		"<ul><li> formatage de la présentation html sous la forme sous laquelle la question va être posée : zone de texte à écrire, étiquettes à déplacer, zone à cliquer </li>"+
		"<li> récupération des données transmises par l'utilisateur </li>"+
		"<li> analyse de la réponse en la comparant à la réponse donnée par le développeur de manière différente selon </li>"+
		"qu'il s'agit de nombres, de matrices, ou de tout autre format </li>"+
		"<li> renvoi d'une note </li>"+
		"<li> renvoi d'une variable <code>\\reply1</code> contenant des éléments de réponses qu'on peut réutiliser dans un feedback.</li></ul>"+
		"Dans la première accolade, on peut mettre du texte qui apparaît devant le champ réservé à la réponse. <br/>"+
		"La deuxième accolade permet de spécifier les éléments permettant de décider si la réponse est juste ou non. <br/>"+
		"Ces éléments vont dépendre du type précisé dans le troisième accolade.";
		return chaine_aide;
	break;
	//********************
	case "\\author{}" :
		chaine_aide="<code>\\author {...}</code> définit l'auteur de l'exercice\n"+
		"<div class='exemple'><div class='title'>Exemple :</div><code>\\author{Sophie Lemaire}</code></div>\n";
		return chaine_aide;
	break;
	//********************
	case "\\computeanswer{}" :
		chaine_aide="<code>\\computeanswer{a}</code><br/> Selon la valeur <code>yes</code> ou <code>no</code> donnée à <code>a</code>, l'utilisateur pourra entrer une réponse numérique en donnant une formule sans l'évaluer ou devra entrer un nombre.<br/>"+
		"La commande <code>\computeanswer{ no }</code> précise que l'utilisateur doit lui-même faire les calculs et entrer la valeur finale.<br/>"+
		" Si par contre, on met <code>\computeanswer{ yes }</code>, l'utilisateur peut entrer une formule comme <code>5*5</code>, laissant à l'ordinateur le soin de faire les calculs.";
		return chaine_aide;
		break;
	//********************	
	case "\\condition{}{}" :
		chaine_aide="<code>\\condition{commentaire}{conditions portant sur \\var}{option=}{weight=}</code><br/>"+
		"Dans la première accolade, on peut mettre un texte qui sera affiché lors de l'analyse de la réponse.<br/>"+
		"Dans la seconde accolade, on met la liste des conditions que la réponse de l'utilisateur contenue dans <code>\\var</code> doit satisfaire pour être considérée comme bonne.";
		return chaine_aide;
		break;
	//********************
	case "\\conditions{}" :
		chaine_aide="On désire ici reposer la question si la réponse est fausse. Il faut analyser soi-même la réponse à l'aide de\n"+
		"\condition et éventuellement de \conditions.\n"+
		"<div class='exemple'><div class='title'>Exemple :</div> \n"+
		"Dans l'exemple ci-dessous, on demande le carré d'un entier ; l'utilisateur a le droit à deux essais.<br/><pre>"+
		"<code>\\title{ Le carré d'un entier avec 2 essais }\n"+
		"\\computeanswer{ no }\n"+
		"\\integer{ n = randint(-5..5) }\n"+
		"\\integer{ N = (\\n)^2 }\n"+
		
		"\\text{STEP = r1}\n"+
		"\\nextstep{\\STEP}\n"+
		"<strong>\\conditions{1}</strong>\n"+
		"\\statement{ Calculer le carré de \\n.}\n\n"+
		"\\answer{ Carré de \\n }{ \\var1 }{ type=numeric }\n"+
		"\\answer{ Carré de \\n (2ème essai) }{ \\N }{ type=numeric }\n"+
		"<strong>\\condition{Votre première réponse est-elle correcte ?}{\\var1 = \\N}</strong>\n"+
		"\\text{STEP=}\n"+
		"\\if{\\step = 2 and \\var1!=\\N}{\\text{STEP = r2}}\n"+
		"\\feedback{ \\reply1 < 0 }{ Le carré d'un entier est toujours positif. }\n"+
		"\\feedback{\\var1!=\\N and \\reply2 = \\N}{Vous avez répondu correctement au 2ème essai.}\n"+
		"\\feedback{\\var1!=\\N and \\reply2!=\\N}{Vos deux réponses sont incorrectes.}</code></pre></div>";
		return chaine_aide;
		break;
	//********************
	case "\\email{}" :
	index2=5;
	break;
	//********************
	case "\\embed{}" :
	index2=6;
	break;
	case "\\feedback{}{}" :
	index2=7;
	break;
	case "\\function{}" :
	index2=8;
	break;
	case "\\help{}" :
	index2=9;
	break;
	case "\\hint{}" :
	index2=10;
	break;
	case "\\integer{}" :
	index2=11;
	break;
	case "\\language{}" :
	index2=12;
	break;
	case "\\matrix{}" :
	index2=13;
	break;
	case "\\precision{}" :
	index2=14;
	break;
	case "\\solution{}" :
	index2=15;
	break;
	case "\\special{}" :
	index2=16;
	break;
	case "\\statement{}" :
	index2=17;
	break;
	case "\\steps{}" :
	index2=18; 
	 break;
	default :
	index2=13;
	}
	
	
var a = [ 
"",
"",
"",
"",
"",

//EMAIL
"<code>\\email{...}</code> définit l'adresse électronique de l'auteur</div>",

//EMBED
"Pour inclure un champ de réponse dans l'énoncé, on ajoute la commande <code>\\embed{}</code> à l'endroit de l'énoncé o&ugrave; on veut que le champ de réponse apparaisse.<br/>"+
"<div class='exemple'><div class='title'>Exemple</div> Par exemple, on peut remplacer le statement dans le source de l'exercice '<a>Le carré d'un entier</a>' (exemple de la fonction ??) par :<p>"+
"<code>\\statement{ Le carré de \\n est : \\embed{reply1,5} }</code></p>"+
"Le deuxième paramètre de <code>\\embed{}</code>, ici <code>5</code>, précise la longueur du champ de réponse.</div>", 

//FEEDBACK
"<code>\\feedback{...}{...}</code> pour faire afficher un message en fonction de la réponse de l'utilisateur",

//function
"<div class='exemple'><div class='title'>Exemple 1 :</div>"+
"la commande <code>\\function{f = +x-1+0}</code> prend la chaîne de caractères <code>+x-1+0</code>, enlève les espaces et le <code>+</code> inutiles puis renvoie la chaîne de caractères <code>x-1+0</code>."+
"</div><div class='exemple'><div class='title'>Exemple 2 :</div><pre><code>"+
"\\function{t = x+4}\n"+
"\\integer{a = -2}\n"+
"\\function{f = +1-\\a*\\t/(1-\\a)}</code></pre>"+
"La variable <code>\\f</code> contient la chaîne de caractères <code>1+2*x+4/(1+2)</code> ; <code>-2</code> a été simplifié et <code>\\t</code> a été remplacé par la chaîne de caractères <code>t+4</code> telle quelle, ce qui donne un résultat différent de <code>1+2*(x+4)/(1+2)</code>.</div>",

//HELP
"<code>\\help{...}</code> pour un texte qui apparaîtra lorsque l'utilisateur clique sur un bouton 'Aide' de l'exercice.",

//HINT
"<code>\hint{...}</code> pour écrire une indication (ce qui apparaît lorsqu'on clique sur le lien 'Indications' de l'exercice.",

//INTEGER
"<code>\\integer{variable=valeur}</code> permet de définir une variable de type 'nombre entier'",

//LANGUAGE
"<div class='exemple'><span class='title'>Exemple :</span><code>\\language{fr}</code> définit la langue de l'exercice en fran&ccedil;ais</div>", 

//MATRIX
"<code>\\matrix{variable=valeur}</code> permet de définir une variable de type 'matrice'",

//precision
"<code>\\precision{n}</code> n est un entier positif qui précise que la comparaison entre la réponse de l'utilisateur et la solution sera effectuée avec une tolérance de 1/n pour les réponses de type numérique.<br/> Plus n sera grand et moins WIMS sera tolérant.",

//solution
"<code>\\solution{...}</code> pour afficher un message lorsque l'exercice est terminé.",

//SPECIAL
"On peut placer des champs de réponses de type <strong>dragfill</strong> ou <strong>clickfill</strong> directement sur une photo ou dans un dessin à l'aide de la commande <code>\\special{imagefill }</code>.<br/>"+
"Cette fonction est à mettre dans la commande <code>\\statement{ }</code>.<br/>"+
"<div class='exemple'><div class='title'>Exemple :</div>\n"+
"On désire un énoncé contenant une image 'nom_photo.jpg' de taille 625x320 pixels, sur laquelle on positionne deux champs de réponses de taille 40x20 pixels.<br/>La première à la position (100,200) en pixels et la deuxième à la position (200,50).<br/> L'utilisateur remplit les champs en choisissant parmi les éléments d'une liste appelée ici <code>\\listechoix</code>.<br/> Les variables <code>\\bonchoix1</code> et <code>\\bonchoix2</code> désignent les deux éléments de <code>\\listechoix</code> qui constituent la réponse correcte pour chacun des deux champs.<pre><code>"+
"\\statement{Compléter l'image : &lt;br&gt;\n"+
"\t <strong>\\special{imagefill \\imagedir/nom_photo.jpg,625x320,40x20</strong>\n"+
"\t reply1, 100x200\n"+
"\t reply2, 200x50\n"+
"}\n"+
"\\answer{}{\\bonchoix1; \\listechoix}{type=clickfill}\n"+
"\\answer{}{\\bonchoix2}{type=clickfill}</code></pre>"+
"<p><strong>Pour aller un peu plus loin : </strong> Pour faire la même chose sur une figure construite avec la commande <code>\\text{dessin = draw(625,320 [...]instructions de dessin[...] )}</code>, "+
"il suffit de remplacer <code>\\imagedir/nom_photo.jpg</code> par <code>\\dessin</code> dans les lignes de code précédentes.</p></div>", 

//STATEMENT
"<code>\\statement{...}</code> pour écrire l'énoncé (cette commande doit apparaître une seule fois dans l'exercice)",

//STEPS
"Une seule des deux commandes <code>\\steps</code> ou <code>\\nextstep</code> peut être utilisée dans un exercice.<br/>"+
"<p>On utilise <code>\\steps</code> lorsque les questions qui vont être posées pendant tout l'exercice sont fixées avant l'apparition de l'énoncé.</p>"+
"<p>On utilise <code>\\nextstep</code> au lieu de <code>\\steps</code> si on veut pouvoir poser des questions différentes en fonction de la réponse de l'utilisateur à une étape précédente.</p>"+
"La variable <code>\\step</code> est créée automatiquement avec la valeur <code>1</code> dès qu'une des commandes <code>\\steps</code> ou <code>\\nextstep</code> est exécutée.<br/>"+
"Sa valeur augmente de 1 à chaque fois que l'utilisateur clique sur <em>'Envoyer votre réponse'</em>.<br/>"+
"En général, on définit une variable de nom libre que l'on applique à <code>\\steps</code> ou <code>\\nexstep</code>. On l'appellera <code>\\STEP</code> dans nos exemples.<br/>"+
"Commen&ccedil;ons en donnant un exemple schématique montrant comment utiliser <code>\\steps</code>.\n"+
"<div class='exemple'><div class='title'>Exemple :</div>"+
"Dans un exercice à deux étapes o&ugrave; l'on pose&nbsp;:<ul><li>deux questions à la première étape</li><li>et une question à la seconde étape </li></ul><pre><code>"+
"\\text{STEP = r1, r2r3}\n"+
"\\steps{\\STEP}\n"+
"\\statement{\n"+
"\t \\if{\\step = 1 }{question 1 : \\embed{r1}, question 2 : \\embed{r2}}\n"+
"\t \\if{\\step = 2}{question 3 : \\embed{r3}}\n"+
"}\n"+
"\\answer{}{\\a}{type=...}\n"+
"\\answer{}{\\b}{type=...}\n"+
"\\answer{}{\\c}{type=...}</code></pre></div>\n"
];

return a[index2];
}