var oefparm4= [ 'pari', 'maxima', 'yacas', 'wims', 'draw', 'slib' ];
function oef4fun(instruction, version){
    switch(instruction)
	{
	case 'pari' :
chaine_aide='<code>pari(factor(2^101-1))</code>'+
'appel de  PARI/GP: ici pour factoriser un entier (utiliser en général de préférence avec \\text{})'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'maxima' :
chaine_aide='<code>maxima(integrate(x^2+1,x);)</code>'+
'appel de Maxima: ici pour intégrer une fonction'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'yacas' :
chaine_aide='<code>yacas(Taylor(x,0,10) cos(x^2+x+1))</code>'+
'appel de Yacas: ici pour calculer un développement de Taylor'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'wims' :
chaine_aide='<code>wims(sort items \\list) wims(listintersect \\list1 and \\list2)</code>'+
'utilisation de commandes wims (deux exemples : la première utilise la commande wims !sort pour ordonner les items de la liste \\list, la seconde utilise la commande wims !listintersect pour obtenir les items communs des listes \\list1 et \\list2)'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'draw' :
chaine_aide='<code>draw(pixel_size_x,pixel_size_y<br>draw_source)</code>'+
'dessiner, le source est le même que pour la commande \\draw, la première ligne étant formée de la taille de l\'image en pixels. La sortie est l\'adresse URL de l\'image.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'slib' :
chaine_aide='<code>slib(matrix/invertible 3,5)</code>'+
'bibliothèque de scripts, par exemple, ici une matrice inversible  3x3 dont les coefficients sont inférieurs à  5.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	
	}
}