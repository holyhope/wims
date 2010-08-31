var oef0= [ 'real', 'complex', 'text', 'integer', 'rational', 'function', 'matrix' ];
function oef0fun(instruction, version){
    switch(instruction)
	{
	case 'real' :
chaine_aide='<code>\\real{x=random(-5..5)}</code>'+
'\\x est un nombre réel aléatoire entre -5 et 5'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'complex' :
chaine_aide='<code>\\complex{z=(1+2*i)^3}</code>'+
'\\z est le nombre complexe z=(1+2*i)^3'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'text' :
chaine_aide='<code>\\text{a=1 2  3}</code>'+
'\\a est le texte donné sans aucune transformation'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'integer' :
chaine_aide='<code>\\integer{n=3*exp(\\a)}</code>'+
'\\n est l\'entier le plus proche de 3*e<sup>\\a</sup> (il dépend de la valeur de \\a)'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'rational' :
chaine_aide='<code>\\rational{x=3*2/6}</code>'+
'\\x est un nombre réel aléatoire entre -5 et 5'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'function' :
chaine_aide='<code>\\function{f=2*x^2}</code>'+
'la fonction 2 x^2'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'matrix' :
chaine_aide='<code>\\matrix{m=1,2,3<br>4,5,6<br>7,8,9}</code>'+
'\\m est la matrice de 3 lignes et 3 colonnes.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	
	}
}