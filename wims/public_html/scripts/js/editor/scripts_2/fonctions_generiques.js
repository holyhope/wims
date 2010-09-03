//Ensemble de Fonctions génériques :

// Actuliste : 
function actuliste(liste, indice) {
	var mytool_array = liste.split("-");
	var n2 = mytool_array.length;
	var liste2 = "";
	for (var i = 0; i < n2; i++) {
		liste2 = liste2 + "<OPTION>" + mytool_array[i] + "</OPTION>";
	}
	document.forms['formu'].sel.innerHTML = liste2;
	//var chaine=document.form.wims_deposit.value;
	//var n=chaine.length;
}

// parcoursTab : 
function parcoursTab(instructionwims, indice) {
	if (instructionwims != "\\") {
		//var mytool_array=instructionwims.split("\\");
		//var instructionwims=mytool_array[1];
		//alert(instructionwims);
		var a = "^\\" + instructionwims + "";
		var n2 = instructionsss.length;
		for (var i = 0; i < n2; i++) {
			var instruction = instructionsss[i];
			var MonReg = new RegExp(a);
			if (MonReg.test(instruction)) {
				liste = liste + instruction + "-";
			}
		}
		compter++;
		if (liste == "-") {
			var div_aide = document.getElementById("aide");
			div_aide.innerHTML = "<h3>"+names["contextual_help"]+"</h3> - "+names["contextual_help_desc"];
			initlist();
		}
		else {
			actuliste(liste, indice);
		}
		liste = "-";
		if (compter == 4) {
			compter = 0;
			liste = "-";
			var div_aide = document.getElementById("aide");
			div_aide.innerHTML = "<h3>"+names["contextual_help"]+"</h3> - "+names["contextual_help_desc"];
		}
	}
}

//anime :
function anime() {
	initlist();
	//if (chrono == null) chrono = setInterval("change()", 10);
}

//anime2 :
function anime2() {
	if (chrono2 == null) chrono2 = setInterval("instruction()", 10);
}

//image :
function image() {
	var url = document.getElementById("url").value;
	var description = document.getElementById("description").value;
	hudAnimationFermeture('hud_video_intro');
	if (description == "") {
		description=names["image_alt"];
	}
    var image = "\\img{" + url + "}{alt='" + description + "'}";
	Cursor_AddTexte('wims_deposit_id', image);
}

//afficheaide :
function afficheaide(langue) {

	var div_aide = document.getElementById("aide");
	var selectedoption = document.getElementsByTagName("OPTION");
	var instruction = selectedoption[document.forms['formu'].sel.selectedIndex].innerHTML;

	//alert(instruction);
	if (langue == "undefined") langue = version;
	if (langue == "eng") version = "eng";
	if (langue == "fr") version = "fr";
	
	var titre_bd="";
	var text="";
	
	switch(instructionsss)
	{
	case cities :
		text = bd(instruction, version);
		titre_bd= names["wims_instruction"];
		break;
	case liste_func_latec :
		text = bdlatec(instruction, version);
		titre_bd= names["latex_instruction"];
		break;
	case ifffff :
		text = iffffffun(instruction, version);
		titre_bd= names["if_instruction"];
		break;
	case special :
		text = specialfun(instruction, version);
		titre_bd= names["special_instruction"];
		break;
	case oef0 :
		text = oef0fun(instruction, version);
		titre_bd= names["oef0_instruction"];
		break;
	case oefparm1 :
		text = oef1fun(instruction, version);
		titre_bd= names["oef1_instruction"];
		break;
	case oefparm2 :
		text = oef2fun(instruction, version);
		titre_bd= names["oef2_instruction"];
		break;
	case oefparm4 :
		text = oef4fun(instruction, version);
		titre_bd= names["oef4_instruction"];
		break;
	case oefparm5 :
		text = oef5fun(instruction, version);
		titre_bd= names["oef5_instruction"];
		break;
	
	}


	div_aide.innerHTML = "<h3 style='display:inline-block;margin-top:0;'>" + instruction + "</h3> - <span class='subtitle'>" + titre_bd + "</span><div class='description'>" + text + "</div>";
	
}

//enregistrer() :
function enregistrer() {
	var chaine = document.forms['replyform'].wims_deposit.value;
	alert(chaine);
}

//initlist() :
instructionsss=cities;
function initlist() {
//alert('initlist');
	liste = "-";
	compter = 0;
	index = null;
	k = null;
	y = 0;
	instructionwims = "";

	//ie error    alert(document.forms['replyform'].wims_deposit.value;);
	var formselect = document.getElementById("divoptions");

	var n2 = instructionsss.length;
	var liste = "";
	for (var i = 0; i < n2; i++) {
		liste = liste + "<OPTION>" + instructionsss[i] + "</OPTION>";
	}
	formselect.innerHTML = "<FORM NAME='formu' onClick='afficheaide();'><SELECT ondblclick='inser()' id='select' NAME='sel' SIZE='10'>" + liste + "</SELECT><br><input type='button' value='"+names["insert_selection"]+"' onclick='inser()' /></FORM>";

}

function changerListeInstruction() {
	afficherHud('hud_video_intro');
}

function changerListeInstruction2(nomdutabo) {
	instructionsss=nomdutabo;
	hudAnimationFermeture('hud_video_intro');
	initlist();
}