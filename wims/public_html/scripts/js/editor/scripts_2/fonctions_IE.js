//Fonctions specifiques "Microsoft Internet Explorer" :
document.writeln("<style>div#textarea{width:95%;}</style>");

function instruction() {
	var chaine = document.forms['replyform'].wims_deposit.value;

	var n = chaine.length;
	if (n > 0) {
		var a = index + 5;
		if (n <= a) {
			//alert(chaine[n-1]);
			if (chaine[n - 1] == chaine[index + y]) {
				y++;
				instructionwims = instructionwims + chaine[n - 1];
				parcoursTab(instructionwims, k);
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
}

function change() {
	//var chaine=document.forms['replyform'].wims_deposit.value;
	//var mytool_array=chaine.split(" ");
	var chaine = document.getElementById("wims_deposit_id").value;
	//alert(chaine.value);
	var n = chaine.length;
	if (n > 0) {
		var i = n - 1;
		//alert(chaine[i]);
		if (chaine[i] == "\\") { //document.write("dfgdfgdsfgdsf");
			//alert("antislash detecté");
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
	var n2 = cities.length;
	var n3 = n2 + 1;
	//Si on  a la liste total des villes
	if (n == n3) {
		var chaine = document.forms['replyform'].wims_deposit.value;
		var chaine2 = chaine + "\n" + instruction;
		document.forms['replyform'].wims_deposit.value = chaine2;
		initlist();
	}
	else {
		var chaine = document.forms['replyform'].wims_deposit.value;
		var mytool_array = chaine.split("\n");
		var n = mytool_array.length;

		var b = "";
		for (var i = 0; i < n - 1; i++) {
			b = b + "" + mytool_array[i] + "\n";

		}
		var dernierligne = mytool_array[n - 1].split(" ");
		var n2 = dernierligne.length;
		//alert(n2);
		if (n2 == 1) {
			var chainefin = b + "" + instruction;
			document.forms['replyform'].wims_deposit.value = chainefin;
			initlist();
		}
		else {
			var dernierligne = mytool_array[n - 1].split(" ");
			var n3 = dernierligne.length;
			var c = "";
			for (var i = 0; i < n3 - 1; i++) {
				c = c + "" + dernierligne[i] + " ";

			}
			var chainefin = b + "" + c + "\n" + instruction;
			document.forms['replyform'].wims_deposit.value = chainefin;
			initlist();
		}
	}
}