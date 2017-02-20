/*
	DynAPI Distribution
	TemplateManager Class

	The DynAPI Distribution is distributed under the terms of the GNU LGPL license.
	
	Requires: DynLayer
*/


function Template(html,x,y,w,h,color,image){
	this.DynLayer = DynLayer;
	this.DynLayer(html||'',x,y,w,h,color,image);
	this._fields=[];
};
var p = dynapi.setPrototype('Template','DynLayer');
p._TemplateSetHTML = DynLayer.prototype.setHTML;
p._insertField = function(fld,value){
	var re = new RegExp('\\[@'+fld+'\\]');
	this.html = this.html.replace(re,value);
};
p._insertChild = function(c){
	if(!c._created) DynElement._flagPreCreate(c);
	var html=c.getOuterHTML();
	var re = new RegExp('\\[@'+c._tmplFld+'\\]');
	if(dynapi.ua.ns4||dynapi.ua.gecko) {
		// NS4 inline layers does not honor <td align="right">, they're always left align. To solve this a <table> must be used to wrap the ilayers. This will also ensure that <ilayers> behave like block elements in DOM
		// Mozilla will collapse table cells whenever the content of the layer changes. To solve this, wrap <div> within <table> and set <table> witdh to <div> width
		html='<table width="'+c.w+'" cellpadding="0" cellspacing="0" border="0"><tr><td>'+html+'</td></tr></table>'
	}
	this.html = this.html.replace(re,html);	
};
p.addChild = function(c,field){
	if (!c || !field) return dynapi.debug.print("Error: no object or field sent to [Template].addChild()");
	if (c.isChild) c.removeFromParent();
	c.isChild = true;
	c.parent = this;
	if (c._saveAnchor) {
		c.setAnchor(c._saveAnchor);
		c._saveAnchor = null;
		delete c._saveAnchor;
	}
	this[field]=c;
	c.isInline=true;
	c._tmplFld=field;
	c._noInlineValues=true;	
	if(c.isClass('DynLayer')) {
		c.setPosition('relative');
		// NS4 seems to create line breaks with inline layers that contains html
		if(dynapi.ua.ns4) c.enableBlackboard(); // this will force a <layer> arround the inline html
	}
	this.children[this.children.length] = c;
	return c;	
};
p.clearTemplate = function(){
	this.deleteAllChildren();
	this._TemplateSetHTML('&nbsp;');
};
// Template Object does not support enableBlackboard
p.enableBlackboard = dynapi.functions.Null;	
p.getInnerHTML=function() {	
	var s = '', fld = this._fields;
	var i,c,ch=this.children;
	// insert fields
	for(i in fld) this._insertField(i,fld[i]);
	// insert child layers/objects
	for (i=0;i<ch.length;i++) this._insertChild(ch[i]);	
	if (this.html!=null) {
		if(!dynapi.ua.ns4) s+=this.html;
		else {
			if (this.w==null) s += '<nobr>'+this.html+'</nobr>';
			else s+=this.html;
		}
	}
	return s;
};
// generate and display the changes made to the template 
p.generate = function(){
	if(!this._created) return;
	else {
		var h=this.getInnerHTML();
		var i,c,ch=this.children;
		this.html = null;
		this._TemplateSetHTML(h);		
		for (i=0;i<ch.length;i++) {
			c=ch[i];			
			if(c.isClass('DynLayer')) DynLayer._assignElement(c);
			if(!c._created) DynElement._flagCreate(c);
		}
	}
};
p.setHTML = function(html){
	this.html=html;
	if(this._created) this.generate();
};
p.getField = function(fld) {return this._fields[fld]};
p.setField = function(fld,value){
	this._fields[fld]=value;
};
