/*
	DynAPI Distribution
	HTMLHyperLink Class

	The DynAPI Distribution is distributed under the terms of the GNU LGPL license.
	
	Requires: HTMLComponent
*/

function HTMLHyperLink(css,text,url,title){
	this.HTMLComponent = HTMLComponent;
	this.HTMLComponent(css);
	
	this.url=url;
	this._text=text;
	this._title=title;
};
var p = dynapi.setPrototype('HTMLHyperLink','HTMLComponent');
p._assignElm = function(elm){
	if(!this.parent) return;
	else if(!this.parent._created) return;
	var doc=this.parent.doc;
	if(elm) elm;
	else if(dynapi.ua.ie) elm=doc.all[this.id];
	else if(dynapi.ua.dom) elm=doc.getElementById(this.id);
	else {
		for(i=0;i<doc.links.length;i++){
			elm=doc.links[i];
			if(elm.name==this.id) break;
			elm=null;
		}
	};
	if(!elm) return;
	this.elm = elm;
	this.css = (dynapi.ua.ns4)? elm:elm.style;
	this.doc = this.parent.doc; //??
};
p.getInnerHTML = function(){
	var evt = this._generateInlineEvents(this);
	var url=this.url||'javascript:;';
	return [
		'<a class="',this._class,'" id="',this.id,'" name="',this.id,'" href="',url,'" ',
		evt,' title="',this._title,'">',this._text,'</a>'
	].join('');
};
p.setText = function(t) {
	var elm = this.getElm();
	if(elm){
		if(dynapi.ua.ns4) elm.text = t; // not supported in ns4?
		else elm.innerHTML=t;
	}
};
p.getURL = function(){
	var url='',elm = this.getElm();
	if(elm) url=elm.href;
	return url;
};
p.setURL = function(url){
	url=(url!=null)? url:'javascript:;';
	var elm = this.getElm();
	if(elm) elm.href=url;	
};