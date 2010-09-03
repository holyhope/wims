var cities = [
	"\\answer{}{}{}", "\\author{}", "\\computeanswer{}", "\\condition{}{}", "\\conditions{}", "\\email{}", "\\embed{}", "\\feedback{}{}",
	"\\function{}", "\\help{}", "\\hint{}", "\\integer{}", "\\language{}", "\\matrix{}",
	"\\precision{}", "\\solution{}", "\\special{}", "\\statement{}",
	"\\steps{}"
	];
	


function bd(instruction, version){
	// les indices &agrave; partir de 19 correspondent aux instructions latex
	var chaine_aide="";
	switch(instruction)
	{
	//********************
	case "\\answer{}{}{}" :
		chaine_aide=names["not_available"];

	break;
	//********************
	case "\\author{}" :
		chaine_aide="<code>\\author {...}</code> " +
		"<div class='exemple'><div class='title'>Example :</div><code>\\author{Sophie Lemaire}</code></div>\n";

	break;
	//********************
	case "\\computeanswer{}" :
		chaine_aide=names["not_available"];
		break;
	//********************	
	case "\\condition{}{}" :
		chaine_aide=names["not_available"];
		break;
	//********************
	case "\\conditions{}" :
		chaine_aide=names["not_available"];
		break;
	//********************
	case "\\email{}" :
		chaine_aide=names["not_available"];
		break;
	//********************
	case "\\embed{}" :
		chaine_aide=names["not_available"];
		break;
	case "\\feedback{}{}" :
		chaine_aide=names["not_available"];
		break;
	case "\\function{}" :
		chaine_aide=names["not_available"];
		break;
	case "\\help{}" :
		chaine_aide=names["not_available"];
		break;
	case "\\hint{}" :
		chaine_aide=names["not_available"];
		break;
	case "\\integer{}" :
		chaine_aide=names["not_available"];
		break;
	case "\\language{}" :
		chaine_aide=names["not_available"];
		break;
	case "\\matrix{}" :
		chaine_aide=names["not_available"];
		break;
	case "\\precision{}" :
		chaine_aide=names["not_available"];
		break;
	case "\\solution{}" :
		chaine_aide=names["not_available"];
		break;
	case "\\special{}" :
		chaine_aide=names["not_available"];
		break;
	case "\\statement{}" :
		chaine_aide=names["not_available"];
		break;
	case "\\steps{}" :
		chaine_aide=names["not_available"];
		break;
	default :
		chaine_aide=names["not_available"];
	}


	return chaine_aide;
}