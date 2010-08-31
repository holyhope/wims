var hudPadding = 30;
var hudActif = false;

function DOM_HUD() {
	if (navigateurEstIncompatible()) return false;
	
	// ajout du div overlay à la fin du body
	var overlay = document.createElement("div");
	overlay.setAttribute('id', 'overlay');
	overlay.style.opacity = '0';
	document.body.insertBefore(overlay, document.body.childNodes[0]);

}

//  WIMS OVERLAY *************************************************************************************************************

function DOM_HUD_WIMS() {
	if (navigateurEstIncompatible()) return false;

        // Recherche des liens
	var liens, lien, sticky, reflet, icone = null;
	liens = getElementsByClassName('lien_externe_reload(.*)');
	for (i=0; i< liens.length; i++) { // boucle sur les liens
		lien = liens[i];
                if (lien.tagName.toLowerCase() == "a") {
                      lien.setAttribute('onclick', 'afficherOverlayWims();');
               }
	}
}

function afficherOverlayWims() {
	if (navigateurEstIncompatible()) return false;
        element = document.getElementById('hud_wims_actualiser');
        if (element) {
             hudCentrerElement(element);
             hudAfficherOverlay()
             element.style.display = 'block';
        }
}

function masquerOverlayWims() {
	//window.location.reload();
        window.location.href = window.location.href;
}


//  VIDEO INTRO OVERLAY *************************************************************************************************************

function afficherOverlayVideoIntro() {
	if (navigateurEstIncompatible()) return false;
        elementId = 'hud_video_intro';
        element = document.getElementById(elementId);
        if (element) {
             hudActif = true;
             hudCentrerElement(element);
             hudAfficherOverlay()
             setTimeout("hudAnimationOuverture(elementId)", 500);
        }
}

function masquerOverlayVideoIntro() {
        element = document.getElementById('hud_video_intro');
        if (element) {
                hudActif = false;
		hudAnimationFermeture(element.id);
        }
}
//  AJOUT DES ELEMENTS *************************************************************************************************************

function hudCreerElement(lElement, lTitre, lLangue, lFeedbackObject, lElementWidth) { // Ajout de la class hud_element aux nodes qui ont un id
	if (hudObjetEstValide(lElement)) {
		
		// ajout de la classe et stockage d'un object de feedback different de l'element (si fourni)
		addClassName(lElement, 'hud_element');
		lElement.hudFeedbackObject = lFeedbackObject;
		if (lElementWidth) { lElement.style.width = lElementWidth; }
                desactiverAutocomplete(lElement);
		
		// creation et ajout du titre
		h = document.createElement("h3");
		h.appendChild(document.createTextNode(lTitre));
		lElement.insertBefore(h, lElement.firstChild);
		
		// creation et ajout de la zone de boutons et du bouton annuler
		boutons = document.createElement("div");
		boutons.setAttribute('id', lElement.id+'_hud_boutons');
		boutons.className = 'hud_boutons';
		lElement.appendChild(boutons);
	}
}

function hudAjouterBouton(lType, lElement, lTitre, lName, lLangue, lImg, lAction, lAppend, lOnClick) { // Ajout d'un bouton (annuler, enregistrer...) + stockage des objets
	if (hudObjetEstValide(lElement)) {
		boutons = document.getElementById(lElement.id+'_hud_boutons');
		
                imgPath = 'images_css/boutons/'+lLangue+'/'+lImg;
                if (lType == 'IMAGE') {
                        bouton = createImageLink(imgPath, "hudBoutonsAction(this)", lTitre, lAppend);
                } else if (lType == 'SUBMIT') {
                        bouton = document.createElement("input");
                        bouton.setAttribute('type', 'image');
                        bouton.setAttribute('name', lName);
                        bouton.setAttribute('src', imgPath);
                        bouton.setAttribute('value', 'Valider');
                } else {
                        return null;
                }

		bouton.hudElement = lElement;
		bouton.hudAction  = lAction;
		bouton.hudAppend  = lAppend;
		if (lOnClick) { bouton.onclick = lOnClick; }
		if (lAppend) { boutons.appendChild(bouton); }
		return bouton;
	}
	return null;
}

function hudCreerBoutons(lElement, lInfosSubmit, lActionValider, lActionAnnuler, lLangue, lImg, lOnClick) { // Ajout des 2 boutons par défaut
	hudAjouterBouton('IMAGE',  lElement, lInfosSubmit['cancel'], '', lLangue, 'bouton_niveau4_annuler.png', lActionAnnuler, true, false);
	hudAjouterBouton('SUBMIT', lElement, lInfosSubmit['value'], lInfosSubmit['name'], lLangue, 'bouton_niveau4_'+lImg+'.png', lActionValider, true, lOnClick);
}

function hudCreerBoutonLancement(lElement, lTitre, lAction, lLangue, lImg, lNiveau) { // creation du bouton de lancement du HUD (false => pas inseré dans bloc boutons)
	return hudAjouterBouton('IMAGE', lElement, lTitre, '', lLangue, 'bouton_niveau'+lNiveau+'_'+lImg+'.png', lAction, false, false);
}

function hudCreerLancement(lElement, lTitre, lAction, lLangue, lImg, lNiveau, lId, lClass) { // creation du bouton de lancement du HUD et de son div
	bouton = hudCreerBoutonLancement(lElement, lTitre, lAction, lLangue, lImg, lNiveau);
	div = document.createElement("div");
	div.setAttribute('id', lId);
	div.setAttribute('class', 'hud_lancement');
	if (lClass) { addClassName(div, lClass); }
	div.appendChild(bouton);
	return div;
}


// ACTIONS *************************************************************************************************************

function hudBoutonsAction(obj) { // appelé par click sur un des boutons hud
	if (obj.hudAction) { obj.hudAction((obj.hudElement.hudFeedbackObject ? obj.hudElement.hudFeedbackObject : obj.hudElement)); } // appel du feedback avec element ou object feedback
	if (!obj.hudAppend) { // bouton lancement (pas dans le bloc des boutons)
             if (!hudActif) {
                hudActif = true;
		elementId = obj.hudElement.id;
		//hudAfficherOverlay();
		hudCentrerElement(obj.hudElement);
		setTimeout("hudAnimationOuverture(elementId)", 500);
                /*obj.hudElement.style.display = 'block';
                obj.hudElement.style.opacity = 1;
                obj.hudElement.style.zIndex   = 9999;
	        obj.hudElement.style.position = 'absolute';*/
            }
	} else {
                hudActif = false;
		hudAnimationFermeture(elementId);
	}
     return false;
}

// ANIMATION ********************************************************************************************************
var z=0;
function hudAnimationOuverture(obj) { // animation d'ouverture

if(z==1){
	element = document.getElementById(obj);
	element.style.display = 'block';
	//$(obj).effects({duration:1}).start({'opacity':[1,1]});
	//$(obj).effects({duration:1500, transition:Fx.Transitions.Elastic.easeOut}).start({'padding':[0,hudPadding], 'margin':[0,-hudPadding]});
        //setTimeout("hudFocus1erChamps(element)", 1501);
       hudFocus1erChamps(element);
	 }
	 z=1;
	   
	   
}

function hudFocus1erChamps(obj) {
       elementsForm = chercherElementsDeFormulaire(obj);
       if (elementsForm.length > 0) {
           if (elementsForm[0].type != 'image') { // AM : chercherElementsDeFormulaire renvoie d'abord les inputs => si pas d'input, renvoi le bouton submit => modifier en bouclant sur les champs et chercher autres que input
                elementsForm[0].blur();
                elementsForm[0].focus();
           }
      }
}

function hudAnimationFermeture(obj) { // animation de fermeture et masquage de l'overlay
	tempVar = obj;
	this._prepareIE("", "");
	//$(obj).effects({duration:200}).start({'opacity':[1,0]});
	str =       "document.getElementById(tempVar).style.display = 'none';";
	str = str + "document.getElementById(tempVar).style.position = 'relative';";
	str = str + "document.getElementById(tempVar).style.top = '';";
	str = str + "document.getElementById(tempVar).style.left = '';";
	str = str + "document.getElementById(tempVar).style.padding = '0';";
	str = str + "document.getElementById('overlay').style.display = 'none';";
	str = str + "tempVar=false;";
	setTimeout(str, 200);
	chrono=null;
	anime();

}


function hudCentrerElement(element) { // centrage d'un element
	element.style.position = 'absolute';
        element.style.zIndex   = 9999;
	tailleElement = getDimensions(element);
	x = positionDocVisible().x+(tailleDocVisible().width - tailleElement.width)/2;
	y = positionDocVisible().y+(tailleDocVisible().height - tailleElement.height)/3;
	x = (x >= positionDocVisible().x ? x : positionDocVisible().x);
	y = (y >= positionDocVisible().y ? y : positionDocVisible().y);
	element.style.left = x+'px';
        element.style.top  = y+'px';	
}
var k=0;
function hudAfficherOverlay() {

if(k==1){
	this._setOverlay();
	document.getElementById('overlay').style.opacity = '0.75';
	document.getElementById('overlay').style.display = 'block';
}
k=1;
}

// UTILS *************************************************************************************************************

function hudObjetEstValide(lElement) { // verification de l'id de l'element
	if (lElement) {
		return (lElement.id != null && lElement.id != "");
	}
	return false;
}

function _setOverlay() {
	if(navigator.appVersion.match(/\bMSIE\b/)) {
		this._prepareIE("100%", "hidden");
			//if (!navigator.appVersion.match(/\b7.0\b/)) window.scrollTo(0,0); // Disable scrolling on top for IE7
	}
}

function _prepareIE(height, overflow){
	var body = document.getElementsByTagName('body')[0];
	body.style.height = height;
	body.style.overflow = overflow;
	
	var html = document.getElementsByTagName('html')[0];
	html.style.height = height;
	html.style.overflow = overflow; 
}	
	

// LOAD *******************************************************************************************************

addEvent(window,'load', function() { DOM_HUD();} );
addEvent(window,'load', function() { DOM_HUD_WIMS();} );


addEvent(window,'load', function() { afficherOverlayVideoIntro();} );

