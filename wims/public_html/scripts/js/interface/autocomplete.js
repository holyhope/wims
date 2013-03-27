jQuery.noConflict();

jQuery(function($) {
    
  /* Autocompletion des domaines dans Modtool 
      attention il faut remplir la variable "tags" pour afficher des mots clés
  */
  
    function comma_split( val ) {
      return val.split( /,\s*/ );
    }
    function extractLast( term ) {
      return comma_split( term ).pop();
    }

    $(".multicomplete")
      // don't navigate away from the field on tab when selecting an item
      .bind( "keydown", function( event ) {
        if (event.keyCode === $.ui.keyCode.TAB &&  $( this ).data( "ui-autocomplete" ).menu.active ) {
          event.preventDefault();
        }
      })
      //Adds Autocompletion
      .autocomplete({
        focus: function() {
          // prevent value inserted on focus
          return false;
        },
        source: function( request, response ) {
          // delegate back to autocomplete, but extract the last term
          response( $.ui.autocomplete.filter(tags, extractLast( request.term ) ) );
        },
        select: function( event, ui ) {
          var terms = comma_split( this.value );
          // remove the current input
          terms.pop();
          // add the selected item
          terms.push( ui.item.value );
          // add placeholder to get the comma-and-space at the end
          terms.push("");
          this.value = terms.join(", ");
          return false;
        }
    });

    $(".autocomplete").autocomplete({
        source: function( request, response ) {
            var matcher = new RegExp( "^" + $.ui.autocomplete.escapeRegex( request.term ), "i" );
            response( $.grep( tags, function( item ){
                  return matcher.test( item );
            }) );
        }
    });
});