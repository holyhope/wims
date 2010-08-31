/*************************************************************************************************************/
/* FONCTIONS UTILS                                                                                                                                                            */
/*************************************************************************************************************/

/* GLOBAL VARS ******************************************************************************************************/

var tempVar= false;


/* EVENTS ******************************************************************************************************/

    function addEvent(obj, type, fn) {
        if (obj.addEventListener) {
            obj.addEventListener(type, fn, false);
        }
        else if (obj.attachEvent) {
            obj["e"+type+fn] = fn;
            obj[type+fn] = function() { obj["e"+type+fn]( window.event ); }
            obj.attachEvent("on"+type, obj[type+fn]);
        }
    }


/* DOM ******************************************************************************************************/

function navigateurEstIncompatible() {
	return (!document.getElementById || !document.createElement || !document.appendChild);
}

function getElementsByClassName(className, tag, elm) {
	var testClass = new RegExp("(^|\s)" + className + "(\s|$)");
	var tag = tag || "*";
	var elm = elm || document;
	var elements = (tag == "*" && elm.all)? elm.all : elm.getElementsByTagName(tag);
	var returnElements = [];
	var current;
	var length = elements.length;
	for(var i=0; i<length; i++){
		current = elements[i];
		if(testClass.test(current.className)){
			returnElements.push(current);
		}
	}
	return returnElements;
}

function getElementsByAttribute(oElm, strTagName, strAttributeName, strAttributeValue){
    var arrElements = (strTagName == "*" && document.all)? document.all : oElm.getElementsByTagName(strTagName);
    var arrReturnElements = new Array();
    var oAttributeValue = (typeof strAttributeValue != "undefined")? new RegExp("(^|\\s)" + strAttributeValue + "(\\s|$)") : null;
    var oCurrent;
    var oAttribute;
    for(var i=0; i<arrElements.length; i++){
        oCurrent = arrElements[i];
        oAttribute = oCurrent.getAttribute(strAttributeName);
        if(typeof oAttribute == "string" && oAttribute.length > 0){
            if(typeof strAttributeValue == "undefined" || (oAttributeValue && oAttributeValue.test(oAttribute))){
                arrReturnElements.push(oCurrent);
            }
        }
    }
    return arrReturnElements;
}

function chercherElementsDeFormulaire(obj) {
	result = new Array();
	searchTags = ['INPUT', 'TEXTAREA', 'OPTION'];
	for (i=0; i<searchTags.length; i++) {
		tags = obj.getElementsByTagName(searchTags[i]);
		for (j=0; j<tags.length; j++) {
			result.push(tags[j]);
		}
	}
	return result;
}

function insertAfter(parent, node, referenceNode) {
  parent.insertBefore(node, referenceNode.nextSibling);
}

function createImageLink(src, href, title, noPngFix) {
	img = document.createElement("img");
	img.setAttribute('src', src);
	img.setAttribute('border', '0');
	img.setAttribute('alt', title);
	img.setAttribute('noPngFix', noPngFix);
	a = document.createElement("a");
	a.onclick = function(){ eval(href); }
	//a.setAttribute('href', ''); // document.URL+'#'
	a.removeAttribute('href');
	a.setAttribute('title', title);
	a.style.cursor = "pointer";
	a.appendChild(img);
	return a;
}


function createSpacer() {
	spacer = document.createElement("div");
	spacer.setAttribute('class', '_spacer');
	return spacer;
}


/* FORMULAIRES  ******************************************************************************************************/

function sauvegarderValeursElementsForm(obj) {
	elementsForm = chercherElementsDeFormulaire(obj);
	
	for (i=0; i<elementsForm.length; i++) { // boucle sur les elements pour sauvegarder leur valeur
		elementForm		= elementsForm[i];
		elementTagName	= elementForm.tagName.toLowerCase();
		elementType		= elementForm.type;	
		
		if (elementType == 'textarea' || elementType == 'text') { // textarea ou text  => on prend la "value"
			elementForm.valueDepart = elementForm.value;
		} else if (elementType == 'checkbox' || elementType == 'radio') { // checkbox ou radio  => on prend la "checked"
			elementForm.valueDepart = elementForm.checked;
		} else if (elementTagName == "option") { // option (tagName car pas de type) => on prend la "selected"
			elementForm.valueDepart = elementForm.selected;
		}
	}
}

 function restaurerValeursElementsForm(obj) {
	elementsForm = chercherElementsDeFormulaire(obj);
	
	for (i=0; i<elementsForm.length; i++) { // boucle sur les elements pour restaurer leur valeur
		elementForm		= elementsForm[i];
		elementTagName	= elementForm.tagName.toLowerCase();
		elementType		= elementForm.type;	
		
		if (elementType == 'textarea' || elementType == 'text') { // textarea ou text  => on prend la "value"
			elementForm.value = elementForm.valueDepart;
		} else if (elementType == 'checkbox' || elementType == 'radio') { // checkbox ou radio  => on prend la "checked"
			elementForm.checked = elementForm.valueDepart;
		} else if (elementTagName == "option") { // option (tagName car pas de type) => on prend la "selected"
			elementForm.selected = elementForm.valueDepart;
			if (elementForm.selected && elementForm.parentNode.type == "select-one") { // bug refresh de la liste safari
				elementForm.parentNode.selectedIndex = elementForm.index;
			}
		}
	}
}

function desactiverAutocomplete(obj) {
	var inputElements = obj.getElementsByTagName("input");
	for (var i=0; i<inputElements.length; i++) {
                 if (inputElements[i].type == "text" || inputElements[i].type == "password") {
                         inputElements[i].setAttribute("autocomplete","off");
                 }
	}
}

/* CSS ******************************************************************************************************/

function getDimensions(element) {
    element = $(element);
    var display = getDisplay(element);
    if (display != 'none' && display != null) // Safari bug
		return {width: element.offsetWidth, height: element.offsetHeight};
    var els = element.style;
    var originalVisibility = els.visibility;
    var originalPosition = els.position;
    var originalDisplay = els.display;
    els.visibility = 'hidden';
    els.position = 'absolute';
    els.display = 'block';
    var originalWidth = element.clientWidth;
    var originalHeight = element.clientHeight;
    els.display = originalDisplay;
    els.position = originalPosition;
    els.visibility = originalVisibility;
    return {width: originalWidth, height: originalHeight};
  }
  
function getDisplay(element) {
	element = $(element);
	var value = element.style['display'];
	if (!value) {
		if (navigator.appVersion.indexOf("MSIE")!=-1) { // IE
			value = element.currentStyle.display;
		} else {
			var css = document.defaultView.getComputedStyle(element, null);
			value = css ? css['display'] : null;
		}
	}
	return value;
}

function tailleDoc() {
	var test1 = document.body.scrollHeight;
	var test2 = document.body.offsetHeight
	if (test1 > test2) { // all but Explorer Mac
		return {width: document.body.scrollWidth, height: document.body.scrollHeight};
	} else { // Explorer Mac; would also work in Explorer 6 Strict, Mozilla and Safari
		return {width: document.body.offsetWidth, height: document.body.offsetHeight};
	}
}

function tailleDocVisible() {
	if (self.innerHeight) { // all except Explorer
		return {width: self.innerWidth, height: self.innerHeight};
	} else if (document.documentElement && document.documentElement.clientHeight) { // Explorer 6 Strict Mode
		return {width: document.documentElement.clientWidth, height: document.documentElement.clientHeight};
	} else if (document.body) { // other Explorers
		return {width: document.body.clientWidth, height: document.body.clientHeight};
	}
}

function positionDocVisible() {
	if (self.pageYOffset) { // all except Explorer
		return {x: self.pageXOffset, y: self.pageYOffset};
	} else if (document.documentElement && document.documentElement.scrollTop) { // Explorer 6 Strict
		return {x: document.documentElement.scrollLeft, y: document.documentElement.scrollTop};
	} else if (document.body) { // all other Explorers
		return {x: document.body.scrollLeft, y: document.body.scrollTop};
	}
}

function permuterAffichageDivs(lIdBlocAfficher, lIdBlocMasquer) {
      tempBlocAfficher = document.getElementById(lIdBlocAfficher);
      tempBlocMasquer = document.getElementById(lIdBlocMasquer);
      if (tempBlocAfficher && tempBlocMasquer) {
            tempBlocAfficher.style.display = 'block';
            tempBlocMasquer.style.display = 'none';
      }
}

/* AJAX ******************************************************************************************************/

function lancerRequeteAjax(url, http_vars, method, selector, obj) {
	req = false;
    if(window.XMLHttpRequest && !(window.ActiveXObject)) {
    	try {
			req = new XMLHttpRequest();
        } catch(e) {
			req = false;
        }
    } else if(window.ActiveXObject) {
       	try {
        	req = new ActiveXObject("Msxml2.XMLHTTP");
      	} catch(e) {
        	try {
          		req = new ActiveXObject("Microsoft.XMLHTTP");
        	} catch(e) {
          		req = false;
        	}
		}
    }
	if(req) {
		if (method.toUpperCase() == "GET") {
			url = url+"?"+	http_vars;
			http_vars = "";
		}
		req.onreadystatechange = function() { 
			processReponseAjax(req, selector, obj);
		}
		req.open(method, url, true);
		req.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
		req.send(http_vars);
	}
	return req;
}

function processReponseAjax(req, selector, obj) {
    if (req.readyState == 4) {
		selector.call("", req.responseText, obj, (req.status != 200));
    }
}
  

/* CORRECTION TRANSPARENCE PNG DANS IE6 ******************************************************************************************/

function correctPNG() // correctly handle PNG transparency in Win IE 5.5 & 6.
{
   var arVersion = navigator.appVersion.split("MSIE")
   var version = parseFloat(arVersion[1])
   if ((version >= 5.5) && (document.body.filters)) 
   {
      for(var i=0; i<document.images.length; i++)
      {
         var img = document.images[i]
         var imgName = img.src.toUpperCase()
         if (imgName.substring(imgName.length-3, imgName.length) == "PNG" && !img.getAttribute('noPngFix')) {
            var imgID = (img.id) ? "id='" + img.id + "' " : ""
            var imgClass = (img.className) ? "class='" + img.className + "' " : ""
            var imgTitle = (img.title) ? "title='" + img.title + "' " : "title='" + img.alt + "' "
            var imgStyle = "display:inline-block;" + img.style.cssText 
            if (img.align == "left") imgStyle = "float:left;" + imgStyle
            if (img.align == "right") imgStyle = "float:right;" + imgStyle
            if (img.parentElement.href) imgStyle = "cursor:hand;" + imgStyle
            var strNewHTML = "<span " + imgID + imgClass + imgTitle
            + " style=\"" + "width:" + img.width + "px; height:" + img.height + "px;" + imgStyle + ";"
            + "filter:progid:DXImageTransform.Microsoft.AlphaImageLoader"
            + "(src=\'" + img.src + "\', sizingMethod='scale');\"></span>" 
            img.outerHTML = strNewHTML
            i = i-1
         }
      }
   }    
}

/* RECUPERATION PARAMETRES GET *****************************************************************************************/

function getURLParam(strParamName){
  var strReturn = "";
  var strHref = window.location.href;
  if ( strHref.indexOf("?") > -1 ){
    var strQueryString = strHref.substr(strHref.indexOf("?")).toLowerCase();
    var aQueryString = strQueryString.split("&");
    for ( var iParam = 0; iParam < aQueryString.length; iParam++ ){
      if (aQueryString[iParam].indexOf(strParamName.toLowerCase() + "=") > -1 ){
        var aParam = aQueryString[iParam].split("=");
        strReturn = aParam[1];
        break;
      }
    }
  }
  return unescape(strReturn);
}

