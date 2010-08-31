function include(fileName){
	document.write("<script type='text/javascript' src='"+fileName+"'></script>" );
}

var version = "fr";

var liste = "-";
var compter = 0;
var index = null;
var k = null;
var y = 0;
var instructionwims = "";
var chrono = null;
var chrono2 = null;

Nom_Browser = navigator.appName;
Version_Browser = navigator.appVersion;
switch (Nom_Browser) {

case "Netscape":
	include('scripts_2/fonctions_Mozilla.js');
	break;
case "Microsoft Internet Explorer":
	include('scripts_2/fonctions_IE.js');
	break;
}