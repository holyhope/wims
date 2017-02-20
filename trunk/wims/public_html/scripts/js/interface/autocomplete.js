
/********* Autocomplete.js  ************************************************************************
    Autocompletion d'un champ texte
    ajoutez la classe "multicomplete" ou "autocomplete" au choix sur l'input, selon que vous
    souhaitez autoriser un ou plusieurs mot-cles.
    Puis lancez set_multicomplete, ou set_autocomplete avec la liste des mots cles en parametre
****************************************************************************************************/

/** String function to replace accented latin letters by their normal ones, using RegExp.
    based on js-replace-diacritics "https://github.com/yvg/js-replace-diacritics" **/
String.prototype.deAccent = function(){
    var accent = [
        /[\300-\306]/g, /[\340-\346]/g, // A, a
        /[\310-\313]/g, /[\350-\353]/g, // E, e
        /[\314-\317]/g, /[\354-\357]/g, // I, i
        /[\322-\330]/g, /[\362-\370]/g, // O, o
        /[\331-\334]/g, /[\371-\374]/g, // U, u
        /[\321]/g, /[\361]/g, // N, n
        /[\307]/g, /[\347]/g, // C, c
    ];
    var noaccent = ['A','a',
                    'E','e',
                    'I','i',
                    'O','o',
                    'U','u',
                    'N','n',
                    'C','c'];

    var str = this;
    for(var i = 0; i < accent.length; i++){
        str = str.replace(accent[i], noaccent[i]);
    }

    return str;
};


function comma_split( val ) {
  return val.split( /,\s*/ );
}

function extractLast( term ) {
  return comma_split( term ).pop();
}

function set_multicomplete(tags){
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
        keyword = extractLast( request.term ).deAccent();
        //alert(keyword);
        response( $.ui.autocomplete.filter(tags, keyword ) );
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
}

function set_autocomplete(tags){
    $(".autocomplete").autocomplete({
        source: function( request, response ) {
            var matcher = new RegExp( "^" + $.ui.autocomplete.escapeRegex( request.term ), "i" );
            response( $.grep( tags, function( item ){
                  return matcher.test( item );
            }) );
        }
    });
}
