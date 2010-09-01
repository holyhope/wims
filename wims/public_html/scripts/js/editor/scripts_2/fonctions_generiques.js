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
			div_aide.innerHTML = "<strong>Aide contextuelle</strong> - tapez antislash suivi d'une lettre en minuscule!";
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
			div_aide.innerHTML = "<strong>Aide contextuelle</strong> - tapez antislash suivi d'une lettre en minuscule!";
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
		var image = "\\img{" + url + "}{alt='description manquante'}";
	}
	else {
		var image = "\\img{" + url + "}{alt='" + description + "'}";
	}
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
	
	switch(instructionsss)
	{
	case cities :
	var text = bd(instruction, version);
	break;
	case liste_func_latec :
	var text = bdlatec(instruction, version);
	break;
	case ifffff :
	var text = iffffffun(instruction, version);
	break;
	case special :
	var text = specialfun(instruction, version);
	break;
	case oef0 :
	var text = oef0fun(instruction, version);
	break;
	case oefparm1 :
	var text = oef1fun(instruction, version);
	break;
	case oefparm2 :
	var text = oef2fun(instruction, version);
	break;
	case oefparm4 :
	var text = oef4fun(instruction, version);
	break;
	case oefparm5 :
	var text = oef5fun(instruction, version);
	break;
	
	}

	if (text == "<img src='images/t1.gif'>" || text == "<img src='images/t2.gif'>" || text == "<img src='images/t3.gif'>" || text == "<img src='images/t4.gif'>" || text == "<img src='images/t5.gif'>") {
		div_aide.innerHTML = "<p><strong>" + instruction + " -instruction latex</strong></p><div>" + text + "</div>";
	}
	else {

		div_aide.innerHTML = "<p><strong>" + instruction + " -instruction wims</strong></p><div>" + text + "</div>";

	}

	//var mytool_array = text.split("\n");
	//var lignes = mytool_array.length;
	//if (lignes < 5) lignes = 0;
	//div_aide.style.marginBottom="44px";
	//div_aide.style.marginBottom = ""+lignes+"em";
	//if(text=="<img src='images/t1.gif'>") div_aide.style.marginBottom ="222px";
	//if(text=="<img src='images/t2.gif'>") div_aide.style.marginBottom ="200px";
	//if(text=="<img src='images/t3.gif'>") div_aide.style.marginBottom ="144px";
	//alert(text);
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

