	{
Nom_Browser = navigator.appName;

Version_Browser = navigator.appVersion;
 switch(Nom_Browser)
    {
    case "Netscape" :
var version="fr";	
	
	var cities = [
	"\\answer{}{}{}", "\\author{}", "\\computeanswer{}", "\\condition{}{}", "\\conditions{}", "\\email{}", "\\embed{}", "\\feedback{}{}",
	"\\function{}", "\\help{}", "\\hint{}", "\\integer{}", "\\language{}", "\\matrix{}",
	"\\precision{}", "\\solution{}", "\\special{}", "\\statement{}",
	"\\steps{}","\\alpha","\\beta","\\gamma","\\delta", "\\epsilon", "\\varepsilon", "\\zeta", "\\eta", "\\Gamma",
	"\\Delta","\\Theta","\\theta","\\vartheta","\\kappa", "\\lambda", "\\mu", "\\nu", "\\xi", "\\pi",
	"\\varpi","\\rho","\\varrho","\\sigma","\\varsigma", "\\Sigma", "\\Upsilon", "\\Phi", "\\tau", "\\upsilon",
	"\\phi","\\varphi","\\chi","\\psi","\\omega", "\\Psi", "\\Upsilon", "\\Phi", "\\Omega",
	
	"\\pm","\\mp","\\times","\\div","\\ast", "\\star", "\\circ", "\\bullet", "\\cdot",
	"\\cap","\\cup","\\uplus","\\sqcap","\\sqcup", "\\vee", "\\wedge", "\\setminus", "\\wr",
	"\\diamond","\\bigtriangleup","\\bigtriangledown","\\triangleleft","\\triangleright", "\\lhd$^b$", "\\rhd$^b$", "\\unlhd$^b$", "\\unrhd$^b$",
	"\\oplus","\\ominus","\\otimes","\\oslash","\\odot", "\\bigcirc", "\\dagger", "\\ddagger", "\\amalg",
	
	"\\widetilde{abc}","\\overleftarrow{abc}","\\overline{abc}","\\overbrace{abc}","\\sqrt{abc}", "\\widehat{abc}", 
	"\\overrightarrow{abc}", "\\underline{abc}", "\\sqrt[n]{abc}", "\\frac{abc}{xyz}",
	
	"\\hat{a}", "\\check{a}", "\\acute{a}", "\\grave{a}", "\\bar{a}", "\\vec{a}", "\\dot{a}", "\\ddot{a}",
	
	"\\rmoustache", "\\arrowvert", "\\lmoustache", "\\Arrowvert", "\\Arrowvert", "\\bracevert", "\\lgroup"
	];




var liste="-";
var compter=0;

function actuliste(liste, indice){
var mytool_array=liste.split("-");
var n2=mytool_array.length;
var liste2="";
for(var i=0; i<n2; i++){
liste2=liste2+"<OPTION>"+mytool_array[i]+"</OPTION>";
}
document.formu.sel.innerHTML=liste2;
//var chaine=document.replyform.wims_deposit.value;
//var n=chaine.length;

}

function parcoursTab(instructionwims, indice){
	if(instructionwims!="\\"){
	//var mytool_array=instructionwims.split("\\");
	//var instructionwims=mytool_array[1];
	//alert(instructionwims);
	var a="^\\"+instructionwims+"";
		var n2=cities.length;
		for(var i=0; i<n2; i++){
		var instruction=cities[i];
		var MonReg = new RegExp(a);
			if(MonReg.test(instruction)){
			liste=liste+instruction+"-";
			}
		}
	compter++;
	if(liste=="-"){
	var div=document.getElementById("aide");
	aide.innerHTML="<strong>Aide contextuelle</strong> - tapez antislash suivi d'une lettre en miniscule!";
	initlist();
	}
	else{
	actuliste(liste, indice);
	}
	liste="-";
	if(compter==4){
		compter=0;
		liste="-";
		var div=document.getElementById("aide");
	aide.innerHTML="<strong>Aide contextuelle</strong> - tapez antislash suivi d'une lettre en miniscule!";
	}
	}
}

	
	index=null;
	k=null;
	y=0;
	var instructionwims="";
	var chrono=null;
	var chrono2=null;
	
function instruction(){
		var chaine=document.replyform.wims_deposit.value;
		 //chaine[curseur-1]
		 var curseur=Cursor_GetPos('wims_deposit_id');
		 var n=chaine.length;

			 var a=index+5;
				if(n<=a){
				//alert(chaine[n-1]);
					
					if(chaine[n-1]==chaine[index+y]){
					y++;
					instructionwims=instructionwims+chaine[curseur-1];
					parcoursTab(instructionwims, k);
					//alert(instructionwims);
					}
				
				}
				else{
				clearInterval(chrono2);
				chrono2=null;
				//alert(instructionwims);
				instructionwims="";
				y=0;
				anime();
				}
					
			 
		}
		function anime2() {
		
		
		if(chrono2==null){
		 chrono2=setInterval("instruction()",20);
		 
		 }
		}
		function change() {
		 //var chaine=document.replyform.wims_deposit.value;
		 //var mytool_array=chaine.split(" ");
		  var chaine=document.getElementById("wims_deposit_id").value;
//alert(chaine.value);
var curseur=Cursor_GetPos('wims_deposit_id');

		 var n=chaine.length;
			 if(n>0){ 
			 var i = n-1;
				//alert(chaine[i]);
				if(chaine[curseur-1]=="\\"){
				//alert(chaine[curseur-1]);
				index=i;
				k=i;
				clearInterval(chrono);
				chrono=null;
				anime2();
				}
				//alert(chaine[i]);
				
			 }
		}

		function anime() {
		initlist();
		if(chrono==null)
		 chrono=setInterval("change()",10);
		}
 function initlist() {
 liste="-";
 compter=0;
index=null;
	k=null;
	y=0;
	 instructionwims="";
	 
	 

	 //ie error    alert(document.replyform.wims_deposit.value;);
	 var formselect=document.getElementById("divoptions");
	var n2=cities.length;
	var liste="";
	var liste2="";
	for(var i=0; i<n2; i++){
		
		liste=liste+"<OPTION>"+cities[i]+"</OPTION>";
	}
	formselect.innerHTML="<FORM NAME='formu' onClick='afficheaide();'><SELECT ondblclick='inser()' id='select' NAME='sel' SIZE='10'>"+liste+"</SELECT><br><input type='button' value='insérer la sélection'"+ 
	"onclick='inser()' /></FORM>";
	//alert(formselect.innerHTML);
 }
 function afficheaide(langue){
 
 var div=document.getElementById("aide");
  var selectedoption=document.getElementsByTagName("OPTION");
   var instruction=selectedoption[document.formu.sel.selectedIndex].innerHTML;

//alert(instruction);
if(langue=="undefined") langue=version;
if(langue=="eng") version="eng";
if(langue=="fr") version="fr";
	var text=bd(instruction, version);
	
	if(text=="<img src='/js/enev/styles/t1.gif'>" || text=="<img src='/js/enev/styles/t2.gif'>" || text=="<img src='/js/enev/styles/t3.gif'>" || text=="<img src='/js/enev/styles/t4.gif'>" || text=="<img src='/js/enev/styles/t5.gif'>"){
	aide.innerHTML="<p><strong>"+instruction+" -instruction latex</strong></p><div><pre>"+text+"</pre></div>";
	}
	else{
	
aide.innerHTML="<p><strong>"+instruction+" -instruction wims</strong></p><div><pre>"+text+"</pre></div>";

	}

var mytool_array=text.split("\n");
var lignes=mytool_array.length;
if(lignes<5) lignes=0;
//aide.style.marginBottom="44px";

aide.style.marginBottom = ""+lignes+"em";
if(text=="<img src='/js/enev/styles/t1.gif'>") aide.style.marginBottom ="222px";
if(text=="<img src='/js/enev/styles/t2.gif'>") aide.style.marginBottom ="200px";
if(text=="<img src='/js/enev/styles/t3.gif'>") aide.style.marginBottom ="144px";
//alert(text);
 }
 
 function inser(){
 
 var selectedoption=document.getElementsByTagName("OPTION");
 var instruction=selectedoption[document.formu.sel.selectedIndex].innerHTML;
 var select=document.getElementById("select");
 var a=select.innerHTML;
 var mytool_array=a.split("<option>");
 var n=mytool_array.length;
 var n2=cities.length;
 var n3=n2+1;
 //Si on  a la liste total des villes
	 if(n==n3){
	Cursor_AddTexte('wims_deposit_id', instruction);
	 initlist();
	 }
	 else{
	 var curseur=Cursor_GetPos('wims_deposit_id');
	 //alert(curseur);
	 var chaine=document.replyform.wims_deposit.value;
	 var chaine2="";
	 for(var i=0; i<curseur-y; i++){
	 chaine2=chaine2+chaine[i];
	 }
	 var n=chaine.length;
	 //alert(n);
	 //alert(curseur);
	 //alert(chaine2);
	 if(n==curseur){
	 document.replyform.wims_deposit.value=chaine2+instruction;
	 
	 }
	 else{
	 var chaine3="";
	 for(var i=curseur; i<n; i++){
	 chaine3=chaine3+chaine[i];
	 }
	 document.replyform.wims_deposit.value=chaine2+instruction+chaine3;
	 }
	 
	 
		initlist();
	 }
 }
 function enregistrer(){
 var chaine=document.replyform.wims_deposit.value;
 alert(chaine);
 
 }
 

        break;
    case "Microsoft Internet Explorer" :
document.writeln("<style>div#textarea{width:95%;}</style>");
		
var version="fr";	
	
		var cities = [
	"\\answer{}{}{}", "\\author{}", "\\computeanswer{}", "\\condition{}{}", "\\conditions{}", "\\email{}", "\\embed{}", "\\feedback{}{}",
	"\\function{}", "\\help{}", "\\hint{}", "\\integer{}", "\\language{}", "\\matrix{}",
	"\\precision{}", "\\solution{}", "\\special{}", "\\statement{}",
	"\\steps{}","\\alpha","\\beta","\\gamma","\\delta", "\\epsilon", "\\varepsilon", "\\zeta", "\\eta", "\\Gamma",
	"\\Delta","\\Theta","\\theta","\\vartheta","\\kappa", "\\lambda", "\\mu", "\\nu", "\\xi", "\\pi",
	"\\varpi","\\rho","\\varrho","\\sigma","\\varsigma", "\\Sigma", "\\Upsilon", "\\Phi", "\\tau", "\\upsilon",
	"\\phi","\\varphi","\\chi","\\psi","\\omega", "\\Psi", "\\Upsilon", "\\Phi", "\\Omega",
	
	"\\pm","\\mp","\\times","\\div","\\ast", "\\star", "\\circ", "\\bullet", "\\cdot",
	"\\cap","\\cup","\\uplus","\\sqcap","\\sqcup", "\\vee", "\\wedge", "\\setminus", "\\wr",
	"\\diamond","\\bigtriangleup","\\bigtriangledown","\\triangleleft","\\triangleright", "\\lhd$^b$", "\\rhd$^b$", "\\unlhd$^b$", "\\unrhd$^b$",
	"\\oplus","\\ominus","\\otimes","\\oslash","\\odot", "\\bigcirc", "\\dagger", "\\ddagger", "\\amalg",
	
	"\\widetilde{abc}","\\overleftarrow{abc}","\\overline{abc}","\\overbrace{abc}","\\sqrt{abc}", "\\widehat{abc}", 
	"\\overrightarrow{abc}", "\\underline{abc}", "\\sqrt[n]{abc}", "\\frac{abc}{xyz}",
	
	"\\hat{a}", "\\check{a}", "\\acute{a}", "\\grave{a}", "\\bar{a}", "\\vec{a}", "\\dot{a}", "\\ddot{a}",
	
	"\\rmoustache", "\\arrowvert", "\\lmoustache", "\\Arrowvert", "\\Arrowvert", "\\bracevert", "\\lgroup"
	];





var liste="-";
var compter=0;

function actuliste(liste, indice){
var mytool_array=liste.split("-");
var n2=mytool_array.length;
var liste2="";
for(var i=0; i<n2; i++){
liste2=liste2+"<OPTION>"+mytool_array[i]+"</OPTION>";
}
document.formu.sel.innerHTML=liste2;
//var chaine=document.form.wims_deposit.value;
//var n=chaine.length;

}

function parcoursTab(instructionwims, indice){
	if(instructionwims!="\\"){
	//var mytool_array=instructionwims.split("\\");
	//var instructionwims=mytool_array[1];
	//alert(instructionwims);
	var a="^\\"+instructionwims+"";
		var n2=cities.length;
		for(var i=0; i<n2; i++){
		var instruction=cities[i];
		var MonReg = new RegExp(a);
			if(MonReg.test(instruction)){
			liste=liste+instruction+"-";
			}
		}
	compter++;
	if(liste=="-"){
	var div=document.getElementById("aide");
	aide.innerHTML="<strong>Aide contextuelle</strong> - tapez antislash suivi d'une lettre en miniscule!";
	initlist();
	}
	else{
	actuliste(liste, indice);
	}
	liste="-";
	if(compter==4){
		compter=0;
		liste="-";
		var div=document.getElementById("aide");
	aide.innerHTML="<strong>Aide contextuelle</strong> - tapez antislash suivi d'une lettre en miniscule!";
	}
	}
}

	
	index=null;
	k=null;
	y=0;
	var instructionwims="";
	var chrono=null;
	var chrono2=null;
		function instruction(){
		var chaine=document.replyform.wims_deposit.value;
		 
		 var n=chaine.length;
			 if(n>0){
			 var a=index+5;
				if(n<=a){
				//alert(chaine[n-1]);
				if(chaine[n-1]==chaine[index+y]){
					y++;
					instructionwims=instructionwims+chaine[n-1];
					parcoursTab(instructionwims, k);
				}
				}
				else{
				clearInterval(chrono2);
				chrono2=null;
				//alert(instructionwims);
				instructionwims="";
				y=0;
				anime();
				}
					
			 }
		}
		function anime2() {

		if(chrono2==null)
		 chrono2=setInterval("instruction()",10);
		}
		function change() {
		 //var chaine=document.replyform.wims_deposit.value;
		 //var mytool_array=chaine.split(" ");
		  var chaine=document.getElementById("wims_deposit_id").value;
//alert(chaine.value);
		 var n=chaine.length;
			 if(n>0){ 
			 var i = n-1;
				//alert(chaine[i]);
				if(chaine[i]=="\\"){				//document.write("dfgdfgdsfgdsf");

				//alert("antislash detecté");
				index=i;
				k=i;
				clearInterval(chrono);
				chrono=null;
				anime2();
				}
				//alert(chaine[i]);
				
			 }
		}

		function anime() {
		initlist();
		if(chrono==null)
		 chrono=setInterval("change()",10);
		}
		
 function initlist() {
 liste="-";
 compter=0;
index=null;
	k=null;
	y=0;
	 instructionwims="";
	 
	 

	 //ie error    alert(document.replyform.wims_deposit.value;);
	 var formselect=document.getElementById("divoptions");
	var n2=cities.length;
	var liste="";
	for(var i=0; i<n2; i++){
	liste=liste+"<OPTION>"+cities[i]+"</OPTION>";
	}
	formselect.innerHTML="<FORM NAME='formu' onClick='afficheaide();'><SELECT ondblclick='inser()' id='select' NAME='sel' SIZE='10'>"+liste+"</SELECT><br><input type='button' value='insérer la sélection'"+ 
	"onclick='inser()' /></FORM>";
	//alert(formselect.innerHTML);
 }
 function afficheaide(langue){
 
 var div=document.getElementById("aide");
  var selectedoption=document.getElementsByTagName("OPTION");
   var instruction=selectedoption[document.formu.sel.selectedIndex].innerHTML;

//alert(instruction);
if(langue=="undefined") langue=version;
if(langue=="eng") version="eng";
if(langue=="fr") version="fr";
	var text=bd(instruction, version);
	if(text=="<img src='/js/enev/styles/t1.gif'>" || text=="<img src='/js/enev/styles/t2.gif'>" || text=="<img src='/js/enev/styles/t3.gif'>" || text=="<img src='/js/enev/styles/t4.gif'>" || text=="<img src='/js/enev/styles/t5.gif'>"){
	aide.innerHTML="<p><strong>"+instruction+" -instruction latex</strong></p><div><pre>"+text+"</pre></div>";
	}
	else{
	
aide.innerHTML="<p><strong>"+instruction+" -instruction wims</strong></p><div><pre>"+text+"</pre></div>";

	}
//alert(text);
var mytool_array=text.split("\n");
var lignes=mytool_array.length;
if(lignes<5) lignes=0;
//aide.style.marginBottom="44px";

aide.style.marginBottom = ""+lignes+"em";
if(text=="<img src='/js/enev/styles/t1.gif'>") aide.style.marginBottom ="222px";
if(text=="<img src='/js/enev/styles/t2.gif'>") aide.style.marginBottom ="200px";
if(text=="<img src='/js/enev/styles/t3.gif'>") aide.style.marginBottom ="111px";
 }
 function inser(){
 var selectedoption=document.getElementsByTagName("OPTION");
 var instruction=selectedoption[document.formu.sel.selectedIndex].innerHTML;
 var select=document.getElementById("select");
 var a=select.innerHTML;
 var mytool_array=a.split("<option>");
 var n=mytool_array.length;
 var n2=cities.length;
 var n3=n2+1;
 //Si on  a la liste total des villes
	 if(n==n3){
	 var chaine=document.replyform.wims_deposit.value;
	 var chaine2=chaine+"\n"+instruction;
	 document.replyform.wims_deposit.value=chaine2;
	 initlist();
	 }
	 else{
	 var chaine=document.replyform.wims_deposit.value;
	 var mytool_array=chaine.split("\n");
	 var n=mytool_array.length;
	 
	 var b="";
		for(var i=0; i<n-1; i++){
		b=b+""+mytool_array[i]+"\n";
	 
		}
		var dernierligne=mytool_array[n-1].split(" ");
		var n2=dernierligne.length;
		//alert(n2);
		if(n2==1){
		var chainefin=b+""+instruction;
		document.replyform.wims_deposit.value=chainefin;
		initlist();
		}
		else{
		var dernierligne=mytool_array[n-1].split(" ");
		var n3=dernierligne.length;
		var c="";
		for(var i=0; i<n3-1; i++){
		c=c+""+dernierligne[i]+" ";
	 
		}
		var chainefin=b+""+c+"\n"+instruction;
		document.replyform.wims_deposit.value=chainefin;
		initlist();
		}
	 }
 }
 function enregistrer(){
 var chaine=document.replyform.wims_deposit.value;
 alert(chaine);
 
 }

        break;
   
	}
}
function image(){
var url=document.getElementById("url").value;
var description=document.getElementById("description").value;
hudAnimationFermeture('hud_video_intro');
if(description==""){ var image="\\img{"+url+"}{alt='description manquante'}";}
else{
var image="\\img{"+url+"}{alt='"+description+"'}";
}
Cursor_AddTexte('wims_deposit_id', image);
}

