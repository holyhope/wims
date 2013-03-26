jQuery.noConflict();

jQuery(function($) {
    
  /* Autocompletion des domaines dans Modtool 
      attention il faut remplir la variable "tags" pour afficher des mots clés
  */
     
     $(".autocomplete").autocomplete({
      source: function( request, response ) {
              
              var matcher = new RegExp( "^" + $.ui.autocomplete.escapeRegex( request.term ), "i" );
              response( $.grep( tags, function( item ){
                  return matcher.test( item );
              }) );
          }
    });
});