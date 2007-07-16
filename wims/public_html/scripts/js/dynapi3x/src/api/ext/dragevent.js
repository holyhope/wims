/*
   DynAPI Distribution
   DragEvent Class

   The DynAPI Distribution is distributed under the terms of the GNU LGPL license.
*/

// DragEvent object
function DragEvent(type,src) {
	this.MouseEvent = MouseEvent;
	this.MouseEvent();
	this.DynEvent()
	this.isDragging = false;
}
var p = dynapi.setPrototype('DragEvent','MouseEvent');
p.getX=function() {return this.x};
p.getY=function() {return this.y};
p.getPageX=function() {return this.pageX};
p.getPageY=function() {return this.pageY};
p.cancelDrag=function() {this.isDragging=false};

//DragEvent.dragPlay=0;

DragEvent.dragevent = new DragEvent();

DragEvent.lyrListener = {
	onmousedown : function(e) {
		DragEvent.startDrag(e);
		//e.preventDefault();
	}
};

DragEvent.startDrag = function(e,dlyr) {
	var origdlyr = dlyr;
	if (!dlyr) dlyr = e.getSource();
	
	if (dynapi.ua.dom) {
		dlyr.elm.ondragstart = function() { return false; }
		dlyr.elm.onselectstart = function() { return false; }
	}
	
	// Initialize dragEvent object
	var de=DragEvent.dragevent;
	//de.bubble = true;
	de.src = dlyr;
	de.origin = (origdlyr)? e.origin : dlyr;
	de.x = e.getPageX()-dlyr.getPageX();
	de.y = e.getPageY()-dlyr.getPageY();
	de.pageX = e.getPageX();
	de.pageY = e.getPageY();
	de.parentPageX = dlyr.parent.getPageX();
	de.parentPageY = dlyr.parent.getPageY();

	de.isDragging = true;

	e.preventDefault();
	e.preventBubble();

	//dlyr._dyndoc.addEventListener(DragEvent.docListener);
	
	dlyr.invokeEvent("dragstart",de);
}

DragEvent.docListener = {
	onmousemove : function(e) {
		//var x = e.getPageX();
		//var y = e.getPageY();
		//dynapi.debug.status('drag move '+e.x+' '+e.y);
		
		var de = DragEvent.dragevent;
		if (de && de.isDragging) {
			
			
			var lyr = de.src;
			if (!lyr) return;
		
			// DS: what is this?
			// Detect if we should start the drag
			/*if(DragEvent.dragPlay==0 || (Math.abs(de.pageX-e.getPageX())-DragEvent.dragPlay>0) || (Math.abs(de.pageY-e.getPageY())-DragEvent.dragPlay>0)) {
				de.isDragging=true;
				de.src.invokeEvent("dragstart",de);
				e.setBubble(de.bubble);
			}
			*/
			/*else if (!de.dragEnabled) {
				// This allows 'cancelDrag' method to fire the mouseUp as if had been released by the user
				lyr.invokeEvent("mouseup");
				return;
			}*/
		
			// Properties
			de.type="dragmove";
			de.pageX=e.getPageX();
			de.pageY=e.getPageY();
		
			/*if (DragEvent.stopAtDocumentEdge) {
				if (de.pageX<0) de.pageX = 0;
				if (de.pageY<0) de.pageY = 0;
				if (de.pageX>DynAPI.document.w) de.pageX = DynAPI.document.w;
				if (de.pageY>DynAPI.document.h) de.pageY = DynAPI.document.h;
			}*/
			
			var x=de.pageX-de.parentPageX-de.x;
			var y=de.pageY-de.parentPageY-de.y;
		
			// Respect boundary, if any
			if (lyr._dragBoundary) {
				var dB = lyr._dragBoundary;
				var t = dB.top;
				var r = dB.right;
				var b = dB.bottom;
				var l = dB.left
				if (x<l) x = l;
				else if (x>lyr.parent.w-lyr.w-r) x = lyr.parent.w-lyr.w-r;
				if (y<t) y = t;
				else if (y>lyr.parent.h-lyr.h-b) y = lyr.parent.h-lyr.h-b;
			}
			else if (lyr._dragBoundaryA) {
				var dB = lyr._dragBoundaryA;
				var b=dB[2];
				var r=dB[1];
				var l=dB[3];
				var t=dB[0];
				var w=lyr.w;
				var h=lyr.h;
				if (x<l) x=l;
				else if (x+w>r) x=r-w;
				if (y<t) y=t;
				else if (y+h>b) y=b-h;
			}
			// Move dragged layer
			lyr.setLocation(x,y);
			lyr.invokeEvent("dragmove",de);
			
			if (lyr._dragStealth==false && lyr.parent.DragOver) {
				lyr.parent.DragOver(lyr);
			}
			
			e.preventDefault();
			e.preventBubble();
		}
	},
	onmouseup : function(e) {
		// Get, if any, the currently drag in process and the layer. If none, return
		var de=DragEvent.dragevent;
		//de.bubble = true;
		if (!de) return;
		var lyr=de.src;
		if (!lyr) return;
	
		if (!de.isDragging) {
	    	de.type="dragend";
    		de.src=null;
    		//e.setBubble(true);
			return;
		}
		if (dynapi.ua.ie) lyr.doc.body.onselectstart = null;
	
		// Avoid click for the dragged layer ( with MouseEvent addition )
		if (dynapi.ua.def) dynapi.wasDragging=true;
		if (lyr.parent.DragDrop) lyr.parent.DragDrop(lyr); 
		// Properties for the event
		de.type="dragend";
		de.isDragging=false;
		lyr.invokeEvent("dragend",de);
	
		// Clean drag stuff
		de.src=null;
		//e.preventDefault();
		e.preventBubble();
		
		//lyr._dyndoc.removeEventListener(DragEvent.docListener);
	}
};
DragEvent.stopAtDocumentEdge = true;
DragEvent.setDragBoundary=function(lyr,t,r,b,l) {
	if (!lyr) {dynapi.debug.print("Error: no object passed to DragEvent.setDragBoundary()"); return;}
	var a=arguments;
	if (a.length==0) return;
	if (a.length==1) {
		lyr._dragBoundary = {left:0,right:0,top:0,bottom:0};
	}
	if (a.length==2) {
		lyr._dragBoundary = arguments[1];
	}
	else if (a.length==5) lyr._dragBoundaryA = [t,r,b,l];
};
DragEvent.enableDragEvents=function() {
	for (var i=0;i<arguments.length;i++) {
		var lyr=arguments[i];
		if (!lyr) {dynapi.debug.print("Error: no object passed to DragEvent.enableDragEvents()"); return;}
		if (lyr.isClass('DynLayer')) lyr.addEventListener(DragEvent.lyrListener);
	}
	dynapi.document.addEventListener(DragEvent.docListener);
	dynapi.document.captureMouseEvents();
};
DragEvent.disableDragEvents=function() {
	for (var i=0;i<arguments.length;i++) {
		var lyr=arguments[i];
		lyr.removeEventListener(DragEvent.lyrListener);
	}
};

DynLayer.setDragMode = function(b,boundry){
	if(!self.DragEvent) return false;
	if(boundry)DragEvent.setDragBoundary(this,boundry);
	if (b) DragEvent.enableDragEvents(this);
	else DragEvent.disableDragEvents(this);
	return true;	
};
DynLayer.prototype.setDragOverStealthMode = function(b){
	this._dragStealth=(b)? true:false;
};
// Enable ondrop event
DynElement.prototype.DragDrop=function(s){ 
	if (!this.children.length>0) return false;
	var ch,chX,sX,sY;
	for (var i in this.children) { 
		ch=this.children[i]; 
		if(ch._hasDragEvents){
			chX=ch.getPageX();
			chY=ch.getPageY(); 
			sX=s.getPageX();
			sY=s.getPageY(); 
			if (chX<sX && chX+ch.w>sX+s.w && chY<sY && chY+ch.h>sY+s.h) { 
				if (ch.DragDrop(s)) return true; 
				ch.invokeEvent("drop"); 
				return true; 
			}
		}
	}
	return false; 
};

// Enable ondragover event
DynElement.prototype.DragOver=function(s){ 
	if (!this.children.length>0) return false;
	var ch,chX,sX,sY;
	for (var i in this.children) { 
		ch=this.children[i];
		if(ch._hasDragEvents){
			chX=ch.getPageX();
			chY=ch.getPageY(); 
			sX=s.getPageX();
			sY=s.getPageY(); 
			if (chX<sX && chX+ch.w>sX+s.w && chY<sY && chY+ch.h>sY+s.h) { 
				if (ch.DragDrop(s)) return true; 
				ch._isDragOver=true;
				ch.invokeEvent("dragover"); 			
				return true; 
			}else if (ch._isDragOver) {
				ch._isDragOver=false;
				ch.invokeEvent("dragout"); 			
			}
		}
	}
	return false; 
};