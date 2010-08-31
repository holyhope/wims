var cities = [
	"\\answer{}{}{}", "\\author{}", "\\computeanswer{}", "\\condition{}{}", "\\conditions{}", "\\email{}", "\\embed{}", "\\feedback{}{}",
	"\\function{}", "\\help{}", "\\hint{}", "\\integer{}", "\\language{}", "\\matrix{}",
	"\\precision{}", "\\solution{}", "\\special{}", "\\statement{}",
	"\\steps{}"
	];
	


function bd(instruction, version){
	// les indices &agrave; partir de 19 correspondent aux instructions latex
	var index2="";
	switch(instruction)
	{
	//********************
	case "\\answer{}{}{}" :
		chaine_aide="La commande <code>\answer{texte}{\A}{type=un_type}{option=}{weight=}</code> ex&eacute;cute en g&eacute;n&eacute;ral les actions suivantes&nbsp;:"+
		"<ul><li> formatage de la pr&eacute;sentation html sous la forme sous laquelle la question va &ecirc;tre pos&eacute;e : zone de texte &agrave; &eacute;crire, &eacute;tiquettes &agrave; d&eacute;placer, zone &agrave; cliquer </li>"+
		"<li> r&eacute;cup&eacute;ration des donn&eacute;es transmises par l'utilisateur </li>"+
		"<li> analyse de la r&eacute;ponse en la comparant &agrave; la r&eacute;ponse donn&eacute;e par le d&eacute;veloppeur de mani&egrave;re diff&eacute;rente selon </li>"+
		"qu'il s'agit de nombres, de matrices, ou de tout autre format </li>"+
		"<li> renvoi d'une note </li>"+
		"<li> renvoi d'une variable <code>\\reply1</code> contenant des &eacute;l&eacute;ments de r&eacute;ponses qu'on peut r&eacute;utiliser dans un feedback.</li></ul>"+
		"Dans la premi&egrave;re accolade, on peut mettre du texte qui appara&icirc;t devant le champ r&eacute;serv&eacute; &agrave; la r&eacute;ponse. <br/>"+
		"La deuxi&egrave;me accolade permet de sp&eacute;cifier les &eacute;l&eacute;ments permettant de d&eacute;cider si la r&eacute;ponse est juste ou non. <br/>"+
		"Ces &eacute;l&eacute;ments vont d&eacute;pendre du type pr&eacute;cis&eacute; dans le troisi&egrave;me accolade.";
		return chaine_aide;
	break;
	//********************
	case "\\author{}" :
		chaine_aide="<code>\\author {...}</code> d&eacute;finit l'auteur de l'exercice\n"+
		"<div class='exemple'><div class='title'>Exemple :</div><code>\\author{Sophie Lemaire}</code></div>\n";
		return chaine_aide;
	break;
	//********************
	case "\\computeanswer{}" :
		chaine_aide="<code>\\computeanswer{a}</code><br/> Selon la valeur <code>yes</code> ou <code>no</code> donn&eacute;e &agrave; <code>a</code>, l'utilisateur pourra entrer une r&eacute;ponse num&eacute;rique en donnant une formule sans l'&eacute;valuer ou devra entrer un nombre.<br/>"+
		"La commande <code>\computeanswer{ no }</code> pr&eacute;cise que l'utilisateur doit lui-m&ecirc;me faire les calculs et entrer la valeur finale.<br/>"+
		" Si par contre, on met <code>\computeanswer{ yes }</code>, l'utilisateur peut entrer une formule comme <code>5*5</code>, laissant &agrave; l'ordinateur le soin de faire les calculs.";
		return chaine_aide;
		break;
	//********************	
	case "\\condition{}{}" :
		chaine_aide="<code>\\condition{commentaire}{conditions portant sur \\var}{option=}{weight=}</code><br/>"+
		"Dans la premi&egrave;re accolade, on peut mettre un texte qui sera affich&eacute; lors de l'analyse de la r&eacute;ponse.<br/>"+
		"Dans la seconde accolade, on met la liste des conditions que la r&eacute;ponse de l'utilisateur contenue dans <code>\\var</code> doit satisfaire pour &ecirc;tre consid&eacute;r&eacute;e comme bonne.";
		return chaine_aide;
		break;
	//********************
	case "\\conditions{}" :
		chaine_aide="On d&eacute;sire ici reposer la question si la r&eacute;ponse est fausse. Il faut analyser soi-m&ecirc;me la r&eacute;ponse &agrave; l'aide de\n"+
		"\condition et &eacute;ventuellement de \conditions.\n"+
		"<div class='exemple'><div class='title'>Exemple :</div> \n"+
		"Dans l'exemple ci-dessous, on demande le carr&eacute; d'un entier ; l'utilisateur a le droit &agrave; deux essais.<br/><pre>"+
		"<code>\\title{ Le carr&eacute; d'un entier avec 2 essais }\n"+
		"\\computeanswer{ no }\n"+
		"\\integer{ n = randint(-5..5) }\n"+
		"\\integer{ N = (\\n)^2 }\n"+
		
		"\\text{STEP = r1}\n"+
		"\\nextstep{\\STEP}\n"+
		"<strong>\\conditions{1}</strong>\n"+
		"\\statement{ Calculer le carr&eacute; de \\n.}\n\n"+
		"\\answer{ Carr&eacute; de \\n }{ \\var1 }{ type=numeric }\n"+
		"\\answer{ Carr&eacute; de \\n (2&egrave;me essai) }{ \\N }{ type=numeric }\n"+
		"<strong>\\condition{Votre premi&egrave;re r&eacute;ponse est-elle correcte ?}{\\var1 = \\N}</strong>\n"+
		"\\text{STEP=}\n"+
		"\\if{\\step = 2 and \\var1!=\\N}{\\text{STEP = r2}}\n"+
		"\\feedback{ \\reply1 < 0 }{ Le carr&eacute; d'un entier est toujours positif. }\n"+
		"\\feedback{\\var1!=\\N and \\reply2 = \\N}{Vous avez r&eacute;pondu correctement au 2&egrave;me essai.}\n"+
		"\\feedback{\\var1!=\\N and \\reply2!=\\N}{Vos deux r&eacute;ponses sont incorrectes.}</code></pre></div>";
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
	
	
	if(version=="fr"){

var a = [ 
"",
"",
"",
"",
"",

//EMAIL
"<code>\\email{...}</code> d&eacute;finit l'adresse &eacute;lectronique de l'auteur</div>",

//EMBED
"Pour inclure un champ de r&eacute;ponse dans l'&eacute;nonc&eacute;, on ajoute la commande <code>\\embed{}</code> &agrave; l'endroit de l'&eacute;nonc&eacute; o&ugrave; on veut que le champ de r&eacute;ponse apparaisse.<br/>"+
"<div class='exemple'><div class='title'>Exemple</div> Par exemple, on peut remplacer le statement dans le source de l'exercice '<a>Le carr&eacute; d'un entier</a>' (exemple de la fonction ??) par :<p>"+
"<code>\\statement{ Le carr&eacute; de \\n est : \\embed{reply1,5} }</code></p>"+
"Le deuxi&egrave;me param&egrave;tre de <code>\\embed{}</code>, ici <code>5</code>, pr&eacute;cise la longueur du champ de r&eacute;ponse.</div>", 

//FEEDBACK
"<code>\\feedback{...}{...}</code> pour faire afficher un message en fonction de la r&eacute;ponse de l'utilisateur",

//function
"<div class='exemple'><div class='title'>Exemple 1 :</div>"+
"la commande <code>\\function{f = +x-1+0}</code> prend la cha&icirc;ne de caract&egrave;res <code>+x-1+0</code>, enl&egrave;ve les espaces et le <code>+</code> inutiles puis renvoie la cha&icirc;ne de caract&egrave;res <code>x-1+0</code>."+
"</div><div class='exemple'><div class='title'>Exemple 2 :</div><pre><code>"+
"\\function{t = x+4}\n"+
"\\integer{a = -2}\n"+
"\\function{f = +1-\\a*\\t/(1-\\a)}</code></pre>"+
"La variable <code>\\f</code> contient la cha&icirc;ne de caract&egrave;res <code>1+2*x+4/(1+2)</code> ; <code>-2</code> a &eacute;t&eacute; simplifi&eacute; et <code>\\t</code> a &eacute;t&eacute; remplac&eacute; par la cha&icirc;ne de caract&egrave;res <code>t+4</code> telle quelle, ce qui donne un r&eacute;sultat diff&eacute;rent de <code>1+2*(x+4)/(1+2)</code>.</div>",

//HELP
"<code>\\help{...}</code> pour un texte qui appara&icirc;tra lorsque l'utilisateur clique sur un bouton 'Aide' de l'exercice.",

//HINT
"<code>\hint{...}</code> pour &eacute;crire une indication (ce qui appara&icirc;t lorsqu'on clique sur le lien 'Indications' de l'exercice.",

//INTEGER
"<code>\\integer{variable=valeur}</code> permet de définir une variable de type 'nombre entier'",

//LANGUAGE
"<div class='exemple'><span class='title'>Exemple :</span><code>\\language{fr}</code> définit la langue de l'exercice en fran&ccedil;ais</div>", 

//MATRIX
"<code>\\matrix{variable=valeur}</code> permet de définir une variable de type 'matrice'",

//precision
"<code>\\precision{n}</code> n est un entier positif qui pr&eacute;cise que la comparaison entre la r&eacute;ponse de l'utilisateur et la solution sera effectu&eacute;e avec une tol&eacute;rance de 1/n pour les r&eacute;ponses de type num&eacute;rique.<br/> Plus n sera grand et moins WIMS sera tolérant.",

//solution
"<code>\\solution{...}</code> pour afficher un message lorsque l'exercice est termin&eacute;.",

//SPECIAL
"On peut placer des champs de r&eacute;ponses de type <strong>dragfill</strong> ou <strong>clickfill</strong> directement sur une photo ou dans un dessin &agrave; l'aide de la commande <code>\\special{imagefill }</code>.<br/>"+
"Cette fonction est &agrave; mettre dans la commande <code>\\statement{ }</code>.<br/>"+
"<div class='exemple'><div class='title'>Exemple :</div>\n"+
"On d&eacute;sire un &eacute;nonc&eacute; contenant une image 'nom_photo.jpg' de taille 625x320 pixels, sur laquelle on positionne deux champs de r&eacute;ponses de taille 40x20 pixels.<br/>La premi&egrave;re &agrave; la position (100,200) en pixels et la deuxi&egrave;me &agrave; la position (200,50).<br/> L'utilisateur remplit les champs en choisissant parmi les &eacute;l&eacute;ments d'une liste appel&eacute;e ici <code>\\listechoix</code>.<br/> Les variables <code>\\bonchoix1</code> et <code>\\bonchoix2</code> d&eacute;signent les deux &eacute;l&eacute;ments de <code>\\listechoix</code> qui constituent la r&eacute;ponse correcte pour chacun des deux champs.<pre><code>"+
"\\statement{Compl&eacute;ter l'image : &lt;br&gt;\n"+
"\t <strong>\\special{imagefill \\imagedir/nom_photo.jpg,625x320,40x20</strong>\n"+
"\t reply1, 100x200\n"+
"\t reply2, 200x50\n"+
"}\n"+
"\\answer{}{\\bonchoix1; \\listechoix}{type=clickfill}\n"+
"\\answer{}{\\bonchoix2}{type=clickfill}</code></pre>"+
"<p><strong>Pour aller un peu plus loin : </strong> Pour faire la m&ecirc;me chose sur une figure construite avec la commande <code>\\text{dessin = draw(625,320 [...]instructions de dessin[...] )}</code>, "+
"il suffit de remplacer <code>\\imagedir/nom_photo.jpg</code> par <code>\\dessin</code> dans les lignes de code pr&eacute;c&eacute;dentes.</p></div>", 

//STATEMENT
"<code>\\statement{...}</code> pour &eacute;crire l'&eacute;nonc&eacute; (cette commande doit appara&icirc;tre une seule fois dans l'exercice)",

//STEPS
"Une seule des deux commandes <code>\\steps</code> ou <code>\\nextstep</code> peut &ecirc;tre utilis&eacute;e dans un exercice.<br/>"+
"<p>On utilise <code>\\steps</code> lorsque les questions qui vont &ecirc;tre pos&eacute;es pendant tout l'exercice sont fix&eacute;es avant l'apparition de l'&eacute;nonc&eacute;.</p>"+
"<p>On utilise <code>\\nextstep</code> au lieu de <code>\\steps</code> si on veut pouvoir poser des questions diff&eacute;rentes en fonction de la r&eacute;ponse de l'utilisateur &agrave; une &eacute;tape pr&eacute;c&eacute;dente.</p>"+
"La variable <code>\\step</code> est cr&eacute;&eacute;e automatiquement avec la valeur <code>1</code> d&egrave;s qu'une des commandes <code>\\steps</code> ou <code>\\nextstep</code> est ex&eacute;cut&eacute;e.<br/>"+
"Sa valeur augmente de 1 &agrave; chaque fois que l'utilisateur clique sur <em>'Envoyer votre r&eacute;ponse'</em>.<br/>"+
"En g&eacute;n&eacute;ral, on d&eacute;finit une variable de nom libre que l'on applique &agrave; <code>\\steps</code> ou <code>\\nexstep</code>. On l'appellera <code>\\STEP</code> dans nos exemples.<br/>"+
"Commen&ccedil;ons en donnant un exemple sch&eacute;matique montrant comment utiliser <code>\\steps</code>.\n"+
"<div class='exemple'><div class='title'>Exemple :</div>"+
"Dans un exercice &agrave; deux &eacute;tapes o&ugrave; l'on pose&nbsp;:<ul><li>deux questions &agrave; la premi&egrave;re &eacute;tape</li><li>et une question &agrave; la seconde &eacute;tape </li></ul><pre><code>"+
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
}
else{
var a = [
		"la version anglaise n'est pas disponible", 
		"la version anglaise n'est pas disponible", 
		"la version anglaise n'est pas disponible", 
		"la version anglaise n'est pas disponible", 
		"la version anglaise n'est pas disponible", 
		"la version anglaise n'est pas disponible", 
		"la version anglaise n'est pas disponible", 
		"la version anglaise n'est pas disponible", 
		"la version anglaise n'est pas disponible",
		"la version anglaise n'est pas disponible", 
		"la version anglaise n'est pas disponible", 
		"la version anglaise n'est pas disponible", 
		"la version anglaise n'est pas disponible", 
		"la version anglaise n'est pas disponible", 
		"la version anglaise n'est pas disponible", 
		"la version anglaise n'est pas disponible",
		"la version anglaise n'est pas disponible", 
		"la version anglaise n'est pas disponible", 
		"la version anglaise n'est pas disponible"
];

}
return a[index2];
}