var oefparm1= [ 'random', 'randint', 'randitem', 'random', 'shuffle', 'shuffle', 'randomitem', 'randitem', 'randomrow' ];
function oef1fun(instruction, version){
    switch(instruction)
	{
	case 'random' :
chaine_aide='<code>random(-5..5)</code>'+
'un nombre au hasard entre -5 et 5.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'randint' :
chaine_aide='<code>randint(-5..5)</code>'+
'un entier au hasard entre  -5 et 5 (bornes comprises).'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'randitem' :
chaine_aide='<code>randitem(+,-)</code>'+
'un signe aléatoire: + ou -'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'random' :
chaine_aide='<code>random(1,2,3,a,b,c)</code>'+
'un item au hasard parmi {1,2,3,a,b,c}'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'shuffle' :
chaine_aide='<code>shuffle(6)</code>'+
'une liste de 6 entiers 1,2,...,6, dans un ordre aléatoire.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'shuffle' :
chaine_aide='<code>shuffle(a,b,c,d,e)</code>'+
'la liste des lettres {a,b,c,d,e}, dans un ordre aléatoire.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'randomitem' :
chaine_aide='<code>randomitem(\\list)</code>'+
'un item au hasard de la liste  \\list (items séparés par des virgules).'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'randitem' :
chaine_aide='<code>randitem(\\list)</code>'+
'un item au hasard de la liste  \\list (items séparés par des virgules).'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'randomrow' :
chaine_aide='<code>randomrow(\\mat)</code>'+
'une ligne au hasard de la matrice  \\mat.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	
	}
}