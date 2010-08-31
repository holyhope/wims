
var special= [ '\\special{expandlines }', '\\special{imagefill }', '\\special{help }', '\\special{tabs2lines }', '\\special{rename }', '\\special{tooltip }' ];
function specialfun(instruction, version){
var special= [ '\\special{expandlines }', '\\special{imagefill }', '\\special{help }', '\\special{tabs2lines }', '\\special{rename }', '\\special{tooltip }' ];
function bd(instruction, version){
    switch(instruction)
	{
	case '\\special{expandlines }' :
chaine_aide='<code>\\special{expandlines}</code>'+
'Ecrit le paramètre dans un style <tt>pre</tt> sans évaluation. \n<p></p> \n'+
'<span class="wims_help_example">Exemple:</span> \n \n<pre>\\text{texte= \nfor a in \\B \n   a = a + 1 \nendfor \n} \n\\statement{ \\special{expandlines \\texte}} \n</pre>\n'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case '\\special{imagefill }' :
chaine_aide='<code>\\special{imagefill}</code>'+
' Met les champs des types de réponses  <tt>dragfill</tt> ou <tt>clickfill</tt> dans une grande image.  \n Doit être utiliser dans le <tt>statement</tt> d\'un exercice OEF.  \n <p></p> \n'+
' <span class="wims_help_example">Exemple</span> \n  \n <pre> \n\\special{imagefill \\imagedir/myphoto.jpg,450x350,40x40 \nreply 1,120x250 \nreply 3,300x50 \nreply 4,10x15 \n} \n</pre> \n Dans cet exemple, on affiche une grande image (<tt>\\imagedir/myphoto.jpg</tt>) dans l\'énoncé \n de type 450x350, avec 3 champs de réponse de type drag-and-drop de type 40x40. Les trois champs sont \n repsectiviement les réponses 1,3 and 4 (qui doivent être de type <tt>clickfill</tt> ou \n <tt>dragfill</tt>), aux posistions respectives 120x250, 300x50, 10x15 dans la grande image. \n  \n <p>  \n La grande image sera redimensionnée à la taille spécifiée. \n </p> \n <p> Il est possible d\'avoir des réponses multiples.  \n Ajouter un troisième paramètre entier à la taille : \n <tt>reply 1,120x250x4</tt> montrera un champ de longueur 4 ( x 120). \n </p>\n'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case '\\special{help }' :
chaine_aide='<code>\\special{help}</code>'+
'La methode spéciale <tt>help</tt> accepte deux paramètres. Le premier est un identificateur \n qui sera dans la variable <tt>\\help_subject</tt> à l\'intérieur de la commande <tt>\\help</tt> \n et le second est le texte du lien. \n  \nSi <tt>\\special{help}</tt> est mis dans l\'énoncé ou le feedback d\'un exercice,  \n l\'aide sera de type popup, contrairement à l\'aide usuelle. \n \nTout le contenu de l\'aide doit être mis dans le source de l\'exercice oef.  \nAucune facilité n\'est prévue pour l\'aide au niveau du module, car le principe \nest que l\'indépendance des fichiers oef n e doit pas être détruit par les aides. \nCependant, si vous avez plusieurs exercices partageant les mêmes textes d\'aide \nvous pouvez utiliser cpp. \n \n<p></p> \n'+
' <span class="wims_help_example">Exemple</span> \n  \n <pre> \n \\title{Deviner} \n \\statement{ Deviner un mot :   \n   \\special{help test1,Premier indice} \n } \n \\answer{1}{Singe} \n \\help{ \n   Voici l\'aide: help subject=\\help_subject \n   <p> \n   \\if{\\help_subject issametext or \\help_subject issametext none}{ \n     \\special{help test0,ici} \n   } \n   \\if{\\help_subject issametext test1}{ \n     La première lettre est <b>S</b>. Vous pouvez trouver un nouvel indice \n     \\special{help test2,ici} \n   } \n  \\if{\\help_subject issametext test2}{Voici le second indice.  \n    La deuxième lettre est <b>i</b> \n   } \n  \\if{\\help_subject issametext test0}{Voici \n    \\special{help test1,l\'aide 1}, \\special{help test2,l\'aide 2} \n   } \n } \n </pre> \n'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case '\\special{tabs2lines }' :
chaine_aide='<code>\\special{tabs2lines}</code>'+
'Convertit les tabulations en un passage à la ligne. \n<p></p> \n'+
'<span class="wims_help_example">Exemple</span> \n \n<pre> \n\\statement{  \n  \\special{tabs2lines \\texte	\\texte} \n} \n</pre> \n'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case '\\special{rename }' :
chaine_aide='<code>\\special{rename}</code>'+
' \nRenomme un fichier (image essentiellement).\n'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case '\\special{tooltip }' :
chaine_aide='<code>\\special{tooltip}</code>'+
'<script type="text/javascript" src="scripts/js/wz_tooltip.js"></script> \ncrée une aide popup (tooltip) : le premier paramètre est le texte du lien, \nle troisième paramètre est le texte apparaissant dans l\'aide popup.  \nle second paramètre est l\'option entre crochets:  \nEntre les crochets, vous pouvez mettre l\'option comme dans \nla documentation de wz_tooltip.js.  \nPar défaut : [FONTSIZE, \'12pt\', ABOVE, \'true\'] \nSi vous voulez ne charger qu\'une seule fois le javascript (une fois est suffisant pour une page \nhtml), ne mettez aucun paramètre.  Si vous ne voulez pas charger le javascript \ncar il a été déjà chargé dans la page html, ajoutez <tt>nojs</tt> \nau second paramètre \nVous pouvez configurer le style css du lien : class <tt> span.tooltip</tt>. \n \n \n'+
'<span class="wims_help_example">Exemple</span> \n \n<pre> \n\\special{tooltip passer la souris ici, ,le mot a 5 lettres} \n\\special{tooltip passer la souris ici,[DURATION, 4000, FONTSIZE, \'18pt\'], le mot a 5 lettres} \n\\special{tooltip passer la souris ici,[TITLE, \'Some Title\', PADDING, 9],un texte} \n\\special{tooltip } \n\\special{tooltip\\special{tooltip passer la souris ici,nojs [TITLE, \'Some Title\', PADDING, 9],un texte} \n</pre> \n \n'+
'' ; return chaine_aide;
	   break;
	////******************** 

	
	}
	}
}