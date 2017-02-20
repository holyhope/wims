/*
	DynAPI Distribution
	HTMLContainer Class

	The DynAPI Distribution is distributed under the terms of the GNU LGPL license.
	
	Requires: HTMLComponent
*/

function HTMLContainer(css,html,w,h){
	this.HTMLComponent = HTMLComponent;
	this.HTMLComponent(css);	
	
	this.w=w; this.h=h;
	this.html=html||'';
};
var p = dynapi.setPrototype('HTMLContainer','HTMLComponent');
p._ns4IPad='<img src="'+dynapi.library.path+'ext/images/pixel.gif" width="0" height="0">';
p._assignElm = function(elm){
	if(!this.parent) return;
	else if(!this.parent._created) return;
	var id=this.id+'HTC';
	var doc=this.parent.doc;
	if(elm) elm;	
	else if(dynapi.ua.ie) elm=doc.all[id];
	else if(dynapi.ua.dom) elm=doc.getElementById(id);
	else if(dynapi.ua.ns4) {
		this._ns4ielm=doc.layers[id];
		elm =this._ns4ielm.document.layers[id+'L'];
		this._ns4ielm.clip.width=elm.document.width;
		this._ns4ielm.clip.height=elm.document.height;
	}
	if(!elm) return;
	this.elm = elm;
	this.css = (dynapi.ua.ns4)? elm:elm.style;
	this.doc = elm.document;
};
p.getInnerHTML = function(){
	var h,html = this.html;
	if(dynapi.ua.ns4) {
		if(this.w==null) html='<nobr>'+html+'</nobr>';
		h='\n<ilayer visibility="inherit" id="'+this.id+'HTC" '
		+((this.w)? ' width="'+this.w+'"':'')
		+((this.h)? ' height="'+this.h+'"':'')
		+'><layer id="'+this.id+'HTCL">'+this._ns4IPad+html+'</layer></ilayer>';
		/* NS4 iLayer seems to be having a problem when you're trying to update the content of the layer 
		so a layer was used to support document.write() method after page load.
		I've also noticed that at times <layer> will not display a <table> it's nested inside another table. 
		for example <table><tr><td><ilayer><layer><table><tr><td>Content</td></tr></table></layer></ilayer></td></tr></table>
		the _ns4IPad will keep things in tact. *sigh* - NS4!!!! */
	}
	else {
		h='<div class="'+this._class+'" id="'+this.id+'HTC" style="'
		+((this.w)? ' width:'+this.w+'px;':'')
		+((this.h)? ' height:'+this.h+'px;':'')
		+'">'+html+'</div>';		
	}
	return h;
};
p.setHTML = function(html){
	if(this.html==html) return;
	this.html=html
	if(this.getElm()){
		if(dynapi.ua.ie) this.elm.innerHTML=html; // ok?
		else if(dynapi.ua.dom) {
			var elm = this.elm;
			elm.innerHTML = html;		
			var sTmp=(this.w==null)? '<nobr>'+this.html+'</nobr>':this.html;
			while (elm.hasChildNodes()) elm.removeChild(elm.firstChild);
			var r=elm.ownerDocument.createRange();
			r.selectNodeContents(elm);
			r.collapse(true);
			var df=r.createContextualFragment(sTmp);
			elm.appendChild(df);
		}else {
			var doc=this.doc;
			if(this.w==null) html='<nobr>'+html+'</nobr>';
			doc.open(); doc.write(this._ns4IPad+html); doc.close();
			this._ns4ielm.clip.width=doc.width;
			this._ns4ielm.clip.height=doc.height;
		}
	}
};