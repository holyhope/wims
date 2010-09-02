var oefparm5= [ 'reply', 'choice', 'step', 'sc_score', 'help_subject' ];
function oef5fun(instruction, version){
    switch(instruction)
	{
	case 'reply' :
chaine_aide='<code>reply1 reply2 ...</code>'+
'variable contenant la réponse de l\'élève à la question de type <tt>reply</tt> numéro 1'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'choice' :
chaine_aide='<code>choice1 choice2 ...</code>'+
'variable contenant la réponse de l\'élève à la question de type <tt>choice</tt> numéro 1'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'step' :
chaine_aide='<code>step</code>'+
'variable donnant le numéro de l\'étape (dans le cas où une commande de type <tt>\\steps</tt> ou <tt>\\nextstep</tt> a été introduite).'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'sc_score' :
chaine_aide='<code>sc_score1 sc_score2 ...</code>'+
'variable entre 0 et 1 indiquant si la réponse à la question est juste ou non (peut avoir des valeurs entre 0 et 1 pour certains types de réponses).'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'help_subject' :
chaine_aide='<code>help_subject</code>'+
'variable contenant l\'identificateur de l\'aide introduite par la méthode spéciale <tt>help</tt>.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	
	}
}