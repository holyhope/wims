var oefparm3= [ 'evalue', 'solve', 'simplify', 'diff', 'int', 'int', 'det', 'sin tg tan sec (1/sin) cot cotan cotan ctg csc (1/cos)', 'sh sinh tanh tanh th ch cosh coth cotanh ', 'Argch acosh argch Argsh asinh argsh Argth atanh argth', 'sqrt', 'binomial', 'ceil', 'floor', 'rint round', 'e E', 'erf', 'erfc', 'EULER Euler euler', 'exp', 'factorial', 'Inf', 'gcd', 'lcm', 'max', 'min', 'lg log10', 'lgamma', 'ln log', 'log2 mylog2', 'pow', 'sgn sign', 'PI Pi pi' ];
function bd(instruction, version){
    switch(instruction)
	{
	case 'evalue' :
chaine_aide='<code>evalue(x^2+sin(y),x=3,y=4)</code>'+
'évaluation de la fonction x^2+sin(y) en x=3, y=4'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'solve' :
chaine_aide='<code>solve(x^3-3*x+1,x=0..1)</code>'+
'la racine simple de x^3-3x+1 entre 0 et 1'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'simplify' :
chaine_aide='<code>simplify(x^5*y^3*x^2/y)</code>'+
'expression simplifiée : x<sup>7</sup>y<sup>2</sup>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'diff' :
chaine_aide='<code>diff(sin(x)+cos(y),x)</code>'+
'la dérivée de sin(x)+cos(y) par rapport à x'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'int' :
chaine_aide='<code>int(x^2+3*x+1,x)</code>'+
'primitive de x^2+3*x+1, le terme constant étant indéterminé'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'int' :
chaine_aide='<code>int(t^2+3*t+1,t=0..1)</code>'+
'l\'intégrale numérique de x^2+3*x+1, entre 0 et 1'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'det' :
chaine_aide='<code>det(\\mat)</code>'+
'le déterminant de la matrice \\mat'+
'' ; return chaine_aide;
	   break;
	////******************** 

case 'binomial' :
chaine_aide='\\integer{a=binomial(9,3)}'+
'' ; return chaine_aide;
	   break;
	////******************** 

	'<code>le coefficient binomial (pour des coefficients inférieurs à 10^7 sinon</code>'+
'utiliser la fonction de pari \\text{a=pari(binomial(50,10))}'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'ceil' :
chaine_aide='<code>\\real{a=ceil(3.4)}</code>'+
'le plus petit entier supérieur'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'floor' :
chaine_aide='<code>\\real{a=floor(3.4)}</code>'+
'le plus grand entier inférieur'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'rint round' :
chaine_aide='<code>\\real{a=rint(3.4)}</code>'+
'closest integer'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'e E' :
chaine_aide='<code>\\real{a=e^2}</code>'+
'constante mathématique $m_e'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'erf' :
chaine_aide=case 'erfc' :
chaine_aide=case 'EULER Euler euler' :
chaine_aide=case 'exp' :
chaine_aide=case 'factorial' :
chaine_aide='<code>\\integer{a=factorial(4)}</code>'+
'factorielle'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'Inf' :
chaine_aide='<code>\\real{a=Inf + 3}</code>'+
'l\'infini'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'gcd' :
chaine_aide='<code>\\integer{a=gcd(4,6)}</code>'+
'pgcd de deux entiers'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lcm' :
chaine_aide='<code>\\integer{a=lcm(4,6)}</code>'+
'ppcm de deux entiers'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'max' :
chaine_aide='<code>\\real{a=max(4,6)}</code>'+
'maximum de deux nombres'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'min' :
chaine_aide='<code>\\real{a=gcd(4,6)}</code>'+
'minimum de deux nombres'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lg log10' :
chaine_aide='<code>\\real{a=log10(10^4)}</code>'+
'log en base 10'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lgamma' :
chaine_aide='<code>\\real{a=lgamma(e^(24))}</code>'+
'log de la fonction Gamma'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'ln log' :
chaine_aide='<code>\\real{a=ln(e^4)}</code>'+
'log népérien'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'log2 mylog2' :
chaine_aide='<code>\\real{a=log2(2^4)}</code>'+
'log en base 2'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'pow' :
chaine_aide='<code>\\real{a=pow(3,0.6)}</code>'+
'puissance, équivalent à  3^0.6'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'sgn sign' :
chaine_aide='<code>\\integer{a=sign(-4)}</code>'+
'signe de la valeur'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'PI Pi pi' :
chaine_aide='<code>\\real{a=sin(Pi)}</code>'+
'constante mathématique $m_pi'+
'' ; return chaine_aide;
	   break;
	////******************** 

	
	}
}