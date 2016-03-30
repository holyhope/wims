/********* search_engine.js  ************************************************************************
	scripts dedies au moteur de recherche de WIMS, declenchant l'autocompletion
****************************************************************************************************/

function start_multicomplete(){
	var search_category = $("#search_category").val();
	var search_lang = $("#search_lang").val();
	var fichier = "";

	if (search_category=="P")
		{fichier =  "./modules/tool/popup."+search_lang+"/dic/form.json";}
	else
		{fichier =  "./scripts/keywords/keywords."+search_lang+".json";}

	/*alert ("search_category = " + search_category + " \n fichier = " + fichier );*/

	$.getJSON( fichier, function(data) {
			console.log( "success" );
			set_multicomplete(data);
		})
		.fail(function( jqxhr, textStatus, error ) {
			var err = textStatus + ', ' + error;
			console.log( "Request JSON Failed: " + err);
			console.log( "Impossible de charger le fichier json " + fichier );
		})
		/*.always(function() { console.log( "complete" ); })*/
	;
}


jQuery(function($) {
	start_multicomplete();

	$("#search_category").change(function(){
		start_multicomplete();
	});
});
