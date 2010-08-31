//Fonctions specifiques "Netscape, Mozilla et consors..." :

function instruction() {
	var chaine = document.forms['replyform'].wims_deposit.value;
	//chaine[curseur-1]
	var curseur = Cursor_GetPos('wims_deposit_id');
	var n = chaine.length;

	var a = index + 5;
	if (n <= a) {
		//alert(chaine[n-1]);
		if (chaine[n - 1] == chaine[index + y]) {
			y++;
			instructionwims = instructionwims + chaine[curseur - 1];
			parcoursTab(instructionwims, k);
			//alert(instructionwims);
		}

	}
	else {
		clearInterval(chrono2);
		chrono2 = null;
		//alert(instructionwims);
		instructionwims = "";
		y = 0;
		anime();
	}

}

function change() {
	//var chaine=document.forms['replyform'].wims_deposit.value;
	//var mytool_array=chaine.split(" ");
	var chaine = document.getElementById("wims_deposit_id").value;
	//alert(chaine.value);
	var curseur = Cursor_GetPos('wims_deposit_id');

	var n = chaine.length;
	if (n > 0) {
		var i = n - 1;
		//alert(chaine[i]);
		if (chaine[curseur - 1] == "\\") {
			//alert(chaine[curseur-1]);
			index = i;
			k = i;
			clearInterval(chrono);
			chrono = null;
			anime2();
		}
		//alert(chaine[i]);
	}
}



function inser() {

	var selectedoption = document.getElementsByTagName("OPTION");
	var instruction = selectedoption[document.forms['formu'].sel.selectedIndex].innerHTML;
	var select = document.getElementById("select");
	var a = select.innerHTML;
	var mytool_array = a.split("<option>");
	var n = mytool_array.length;
	var n2 = instructionsss.length;
	var n3 = n2 + 1;
	//Si on  a la liste total des villes
	if (n == n3) {
		Cursor_AddTexte('wims_deposit_id', instruction);
		initlist();
	}
	else {
		var curseur = Cursor_GetPos('wims_deposit_id');
		//alert(curseur);
		var chaine = document.forms['replyform'].wims_deposit.value;
		var chaine2 = "";
		for (var i = 0; i < curseur - y; i++) {
			chaine2 = chaine2 + chaine[i];
		}
		var n = chaine.length;
		//alert(n);
		//alert(curseur);
		//alert(chaine2);
		if (n == curseur) {
			document.forms['replyform'].wims_deposit.value = chaine2 + instruction;

		}
		else {
			var chaine3 = "";
			for (var i = curseur; i < n; i++) {
				chaine3 = chaine3 + chaine[i];
			}
			document.forms['replyform'].wims_deposit.value = chaine2 + instruction + chaine3;
		}

		initlist();
	}
}