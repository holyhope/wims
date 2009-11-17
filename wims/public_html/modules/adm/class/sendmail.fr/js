<script type="text/javascript">
function moveSelections(selectLeft, selectRight, selectHidden, action) {
  var menuFrom; var menuTo;  var i ; 
    if (action == 'add') {
        menuFrom = selectLeft;
        menuTo = selectRight;
    }
    else {
        menuFrom = selectRight;
        menuTo = selectLeft;
    }
    // Don't do anything if nothing selected. Otherwise we throw javascript errors.
    if (menuFrom.selectedIndex == -1) {
        return;
    }

    // Add items to the 'TO' list.
    for (i=0; i < menuFrom.length; i++) {
        if (menuFrom.options[i].selected == true ) {
            menuTo.options[menuTo.length]= new Option(menuFrom.options[i].text, menuFrom.options[i].value);
        }
    }

    // Remove items from the 'FROM' list.
    for (i=(menuFrom.length - 1); i>=0; i--){
        if (menuFrom.options[i].selected == true ) {
            menuFrom.options[i] = null;
        }
    }

    // Set the appropriate items as 'selected in the hidden select.
    // These are the values that will actually be posted with the form.
    updateHidden(selectHidden, selectRight);
}

function updateHidden(h,r) {
    for (var i=0; i < h.length; i++) {
        h.options[i].selected = false;
    }

    for (i=0; i < r.length; i++) {
        h.options[h.length] = new Option(r.options[i].text, r.options[i].value);
        h.options[h.length-1].selected = true;
    }
}

function moveUp(l,h) {
    var indice = l.selectedIndex;
    if (indice < 0) {
        return;
    }
    if (indice > 0) {
        moveSwap(l, indice, indice-1);
        updateHidden(h, l);
    }
}

function moveDown(l,h) {
    var indice = l.selectedIndex;
    if (indice < 0) {
        return;
    }
    if (indice < l.options.length-1) {
        moveSwap(l, indice, indice+1);
        updateHidden(h, l);
    }
}

function moveSwap(l,i,j) {
    var valeur = l.options[i].value;
    var texte = l.options[i].text;
    l.options[i].value = l.options[j].value;
    l.options[i].text = l.options[j].text;
    l.options[j].value = valeur;
    l.options[j].text = texte;
    l.selectedIndex = j
}

/* end javascript for HTML_QuickForm_advmultiselect */
/* ]]> */

</script>
