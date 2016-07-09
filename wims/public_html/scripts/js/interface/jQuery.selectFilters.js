/*
jQuery.selectFilters.js

  A jQuery extension adding "filterByText" and "selectByText" functions to <select> tags.

By LESSAN VAEZI | Published: 2011/07/11
  http://www.lessanvaezi.com/filter-select-list-options/

Modified by Obado on 2016/03/03, adding automatic selection (selectByText function)
  nb : You can use both "filterByText" and "selectByText" on a same <select>.
*/

/***
    filterByText By LESSAN VAEZI
------------
A jQuery extension method to filter the elements of a select list (option tags).
It binds to a textbox, and as you type in the textbox the select list gets filtered
to match what you are typing.

You can play around with it on jsbin: http://jsbin.com/egogeh/edit

------------
Parameters:
###########
 * textbox
This could be a jQuery selector, a jQuery object, or a DOM object.

 * selectSingleMatch (optional)
  - if you set it to "single", when the filtered list includes only one item, that item will be automatically selected.
  - if you set it to "multiple", all itels item will be automatically selected.
 * preventReturn (optional - default = 'true')
  - if you set it to "true", form will not be submitted when user press "return" from textarea.
------------
For example:
############
$(function() {
  $('#select').filterByText($('#textbox'), 'single');
});

*/

jQuery.fn.filterByText = function(textbox, selectMatches, preventReturn) {
  preventReturn = typeof preventReturn !== 'undefined' ? preventReturn : true;
  if (preventReturn) {
      /* prevent user from sending form by pressing "return". */
      $(textbox).keydown(function(event){
          if(event.keyCode == 13) {
            event.preventDefault();
            return false;
          }
      });
  }

  return this.each(function() {
    var select = this;
    var options = [];
    $(select).find('option').each(function() {
      options.push({value: $(this).val(), text: $(this).text()});
    });
    $(select).data('options', options);

    $(textbox).bind('change keyup', function() {
      var options = $(select).empty().scrollTop(0).data('options');
      var search = $.trim($(this).val());
      /*if (search == "")
        selected_state = false;
      else
        selected_state = true;*/
      var regex = new RegExp(search,'gi');

      $.each(options, function(i) {
        var option = options[i];
        if(option.text.match(regex) !== null) {
          $(select).append(
             $('<option>').text(option.text).val(option.value)
             //.prop('selected', true)
          );
        }
      });
      if (selectMatches == "single" && $(select).children().length === 1) {
        $(select).children().get(0).prop('selected', true);
      }
      else if (selectMatches == "multiple" && search !== "") {
        $(select).children().prop('selected', true);
      }
    });
  });
};


/***
    selectByText
jQuery.fn.selectByText by Obado
------------
A jQuery extension method to automatically select the elements of a select list (option tags).
It binds to a textbox, and as you type in the textbox the select list gets selected
to match what you are typing.

------------
Parameters:
###########
 * textbox
This could be a jQuery selector, a jQuery object, or a DOM object.

 * preventReturn (optional - default = false)
  - if you set it to "true", form will not be submitted when user press "return" from textarea.

------------
For example:
############
$(function() {
  $('#select').selectByText($('#textbox'));
});

*/

jQuery.fn.selectByText = function(textbox, preventReturn) {

  preventReturn = typeof preventReturn !== 'undefined' ? preventReturn : false;
  if (preventReturn) {
      /* prevent user from sending form by pressing "return". */
      $(textbox).keydown(function(event){
          if(event.keyCode == 13) {
            event.preventDefault();
            return false;
          }
      });
  }

  return this.each(function() {
    var select = this;
    var options = [];
    $(select).find('option').each(function() {
      options.push({value: $(this).val(), text: $(this).text(), object:$(this)});
      //$(this).prop('selected', false);
    });
    //$(select).data('options', options);

    $(textbox).bind('change keyup', function() {
      //var options = $(select).empty().scrollTop(0).data('options');
      var search = $.trim($(this).val());
      /*if (search == "")
        selected_state = false;
      else
        selected_state = true;*/
      $(select).find('option').each(function() {
          $(this).prop('selected', false);
      });
      var regex = new RegExp(search,'gi');
      if (search !== "")
      {
        $.each(options, function(i) {
          var option = options[i];
          if(option.text.match(regex) !== null) {
            /*$(select).append(
               $('<option>').text(option.text).val(option.value)
               //.prop('selected', true)
            );*/
            option.object.prop('selected', true);
          }
        });
      }
    });
  });
};