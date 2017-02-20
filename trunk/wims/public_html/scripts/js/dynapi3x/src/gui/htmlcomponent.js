/*
	DynAPI Distribution
	HTMLComponent (HC) Class - These are insertable DynAPI components that simulates that their HTML counterparts
	Most HTMLComponents are design time only components, meaning you can only change their properties before they are inserted into the document or template.
	If you change the property of a design time only component after it has been inserted into the document or template you'll have to re-insert the component (or regenerate the template) for the new changes to be made visible. 
	HCs were specifically designed to work with TemplateManager, but can also be used to generate HMTL for other DynAPI widgets

	The DynAPI Distribution is distributed under the terms of the GNU LGPL license.
	
	Requires: DynElement
	
*/

function HTMLComponent(css){
	this.DynElement = DynElement;
	this.DynElement();
	this._class = css||'';
};
var p = dynapi.setPrototype('HTMLComponent','DynElement');
// color props 
p.backCol = '#FFFFFF';
p.foreCol = '#000000';
p._assignElm = p._remove = p._destroy = p._create = p._destroyAllChildren = dynapi.functions.Null;
p._createInserted = function(){
	this._assignElm();
};
p._inlineEvents = ' onclick="return htc._e(\'click\',this);" '
+' onmouseover="return htc._e(\'mouseover\',this);" '
+' onmousedown="return htc._e(\'mousedown\',this);" '
+' onmouseout="return htc._e(\'mouseout\',this);" '
+' onfocus="return htc._e(\'focus\',this);" '
+' onblur="return htc._e(\'blur\',this);" '
p._generateInlineEvents = function(htc){
	return this._inlineEvents.replace(/htc/g,htc.toString());
};
// event handler
p._e = function(evt,elm){
	this._cancelEvt = false;
	if(!this.elm) this._assignElm(elm);
	this.invokeEvent(evt);
	return !this._cancelEvt;
};
p.cancelEvent = function(){
	this._cancelEvt = true;
};
p.getInnerHTML = p._hEvt = dynapi.functions.Null;
p.getOuterHTML = function() {
	return this.getInnerHTML();
};
p.getElm = function(){
	if(!this.e) this._assignElm();
	return this.elm;
};
p.getCss = function(){
	if(!this.css) this._assignElm();
	return this.css;
};