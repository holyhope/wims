//-------------------------------------------------------------
//  Nom Document : GFCURSOR.JS
//  Auteur       : G.Ferraz
//  Objet        : Gestion du curseur dans TEXTAERA et INPUT...
//  Création     : 18.09.2006
//-------------------------------------------------------------
//  Mise à Jour  : 20.11.2006
//  Objet        : Vilain BUG avec le retour chariot sous IE (*)
//-------------------------------------------------------------
//-(*)------------------
function Get_NbrCR(txt_){
  var NbrCR = 0;
  var Pos = txt_.indexOf("\r\n");
  while( Pos > -1){
    Pos = txt_.indexOf("\r\n", Pos+2);
    NbrCR ++;
  }
  return( NbrCR);
}
//----------------------------------
function Cursor_SetPos( where_, pos_){
  //-- Recup l'Objet
  var Obj = document.getElementById( where_);
  if( Obj){
    Obj.focus();
    if( typeof Obj.selectionStart != "undefined"){
      Obj.setSelectionRange( pos_, pos_);
    }
    else{ // IE and consort
      var Chaine = Obj.createTextRange();
      Chaine.moveStart('character', pos_);
      //-- Deplace le curseur
      Chaine.collapse();
      Chaine.select();
    }
    //-- Retour valeur Reelle placee
    return( Cursor_GetPos( where_, pos_));
  }
}
//----------------------------------
function Cursor_GetPos( where_, pos_){
  //-- Recup l'Objet
  var Obj= document.getElementById(where_);
  if( Obj){
    //-- Focus sur Objet
    Obj.focus();
    if(typeof Obj.selectionStart != "undefined")
      return Obj.selectionStart;
    else{ // IE and consort
      var szMark = "~~";
      var Chaine = Obj.value;
      //-- Cree un double et insert la Mark ou est le curseur
      var szTmp = document.selection.createRange();
      szTmp.text = szMark;
      //-- Recup. la position du curseur
      var PosDeb = Obj.value.search(szMark);
      //-(*)- Supprime les retours Chariot
      var szAvant  = Chaine.substring( 0 , PosDeb);
      PosDeb -= Get_NbrCR( szAvant);
      //-- Restaure valeur initiale
      Obj.value = Chaine;
      Chaine = Obj.createTextRange();
      //-- Deplace le Debut de la chaine
      Chaine.moveStart('character', PosDeb);
      //-- Deplace le curseur
      Chaine.collapse();
      Chaine.select();
      return( PosDeb);
    }
  }
}
//------------------------------------
function Cursor_AddTexte(where_, txt_){
  //-- Recup l'Objet
  var Obj = document.getElementById( where_);
  if( Obj){
    //-- Focus sur Objet
    Obj.focus();
    if( typeof Obj.selectionStart != "undefined"){
      //-- Position du curseur
      var PosDeb  = Obj.selectionStart;
      var PosFin  = Obj.selectionEnd;
      //-- Recup. des Chaines
      var Chaine  = Obj.value;
      var szAvant = Chaine.substring( 0 , PosDeb);
      var szApres = Chaine.substring( PosFin, Obj.textLength );
      //-- Recup. texte selectionne
      var szSelect = Chaine.substring( PosDeb, PosFin);
      //-- Insertion du texte
      Obj.value = szAvant + txt_ + szApres;
      //-- Replace le curseur
      Obj.setSelectionRange(  szAvant.length + txt_.length, szAvant.length + txt_.length );
      //-- Replace le Focus
      Obj.focus();
    }
    else{ // IE and consort
      //-- Recup. de la selection
      var szSelect = document.selection.createRange().text;
      //-- Si du Texte est selectionne on le remplace
      if( szSelect.length > 0){
        var Chaine = document.selection.createRange();
        Chaine.text = txt_ ;
        Chaine.collapse();
        Chaine.select();
      }
      else{
        var Chaine = Obj.value;
        var szMark ="~~";
        //-- Cree un double et insert la Mark ou est le curseur
        var szTmp = document.selection.createRange().duplicate();
        szTmp.text = szMark;
        //-- Recup. la position du curseur
        var PosDeb = Obj.value.search(szMark);
        //-- Recup. des Chaines
        var szAvant = Chaine.substring( 0 , PosDeb);
        var szApres = Chaine.substring( PosDeb, Obj.textLength );
        //-- Insertion du texte
        Obj.value = szAvant + txt_ + szSelect + szApres;
        //-- Repositionne le curseur
        PosDeb += txt_.length;
        //-(*)- Supprime les retours Chariot
        PosDeb -= Get_NbrCR( szAvant);
        //-- Recup de la Chaine
        Chaine = Obj.createTextRange();
        //-- Deplace le Debut de la chaine
        Chaine.moveStart('character', PosDeb);
        //-- Deplace le curseur
        Chaine.collapse();
        Chaine.select();
      }
    }
  }
}
//-- EOF ------------------------------------------------------
