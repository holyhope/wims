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
	if (chrono2 == null) chrono2 = setInterval("instruction()", 15);
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
	
	var text="";
	
    switch(instructionsss)
	{
	case oefcommand :
		text = oefcommandfun(instruction);
		break;
	case latex :
		text = latexfun(instruction);
		break;
	case iff :
		text = ifffun(instruction);
		break;
	case special :
		text = specialfun(instruction);
		break;
	case oefparm0 :
		text = oefparm0fun(instruction);
		break;
	case oefparm1 :
		text = oefparm1fun(instruction);
		break;
	case oefparm2 :
		text = oefparm2fun(instruction);
		break;
	case oefparm3 :
		text = oefparm3fun(instruction);
		break;
	case oefparm4 :
		text = oefparm4fun(instruction);
		break;
	case oefparm5 :
		text = oefparm5fun(instruction);
		break;
	case slib :
		text = slibfun(instruction);
		break;
	
	}
	div_aide.innerHTML = "<h3 style='display:inline-block;margin-top:0;'>" + instruction + "</h3><div class='description'>" + text + "</div>";
	
}

function funcname() {
switch(instructionsss)
	{
	case oefcommand :
		titre_bd= oefcommandname;
		break;
	case latex :
		titre_bd= latexname;
		break;
	case iff :
		titre_bd= iffname;
		break;
	case special :
		titre_bd= specialname;
		break;
	case oefparm0 :
		titre_bd=oefparm0name;
		break;
	case oefparm1 :
		titre_bd=oefparm1name;
		break;
	case oefparm2 :
		titre_bd=oefparm2name;
		break;
	case oefparm3 :
		titre_bd=oefparm3name;
		break;
	case oefparm4 :
		titre_bd=oefparm4name;
		break;
	case oefparm5 :
		titre_bd=oefparm5name;
        break;
	case slib :
		titre_bd= slibname;
		break;
	
	}
}
//enregistrer() :
function enregistrer() {
	var chaine = document.forms['replyform'].wims_deposit.value;
	alert(chaine);
}

//initlist() :
instructionsss=oefcommand;
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
	funcname();
	var n2 = instructionsss.length;
	var liste = "";
	for (var i = 0; i < n2; i++) {
		liste = liste + "<option>" + instructionsss[i] + "</option>";
	}
	formselect.innerHTML = "<form name='formu' onClick='afficheaide();'><select ondblclick='inser()' id='select' name='sel' size='10'>" + liste + "</select><br><input type='button' value='"+names["insert_selection"]+"' onclick='inser()' /></form>";
    document.getElementById("name_list_instruction").innerHTML = titre_bd ; 
}

function changerListeInstruction() {
	afficherHud('hud_video_intro');
}

function changerListeInstruction2(nomdutabo) {
	instructionsss=nomdutabo;
	hudAnimationFermeture('hud_video_intro');
	initlist();
}