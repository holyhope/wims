/*
	DynAPI Distribution
	Swiper Animation Extension - originally designed by Erik Arvidsson (http://web.eae.net)

	The DynAPI Distribution is distributed under the terms of the GNU LGPL license.
	
	requires: DynLayer
	
*/

Swiper = {}; // used by dynapi.library

DynLayer.prototype.swipeTo = function(dir, steps, ms) {

	this._swipeSteps = (steps!=null)? steps: 4;
	this._swipeMS = (ms!=null)? ms:25;
	this._swipeDir=dir;

	if (this.swipeTimer != null) window.clearTimeout(this.swipeTimer);
		
	if (!this._swipeCnt) {		// No animation yet!
		this._swipeOrgX  = this.getX();
		this._swipeOrgY  = this.getY();
		this._swipeOrgWidth = this.getWidth();
		this._swipeOrgHeight  = this.getHeight();
	}
	
	this._swipeCnt = this._swipeSteps;
	this.setClip([0,0,0,0]);
			
	window.setTimeout(this+"._swipe()", this._swipeMS);
};
DynLayer.prototype._swipe = function() {
	var steps	= this._swipeSteps;
	var x = this._swipeOrgX;
	var y = this._swipeOrgY;
	var w = this._swipeOrgWidth;
	var h = this._swipeOrgHeight;
	
	if (this._swipeCnt == 0) {
		this.setClip([0, w, h,0]);
		this.invokeEvent('swipefinish');
		return;
	}
	else {
		this._swipeCnt--;
		this.setVisible(true);
		switch (this._swipeDir) {
			case "bottom":		//down (see the numpad)
				this.setClip([h * this._swipeCnt / steps, w, h, 0]);
				this.setY(y - h * this._swipeCnt / steps);
				break;
			case "top":
				this.setClip([0, w, h * (steps - this._swipeCnt) / steps, 0]);
				this.setY(y + h * this._swipeCnt / steps);
				break;
			case "right":
				this.setClip([0, w, h,w * this._swipeCnt / steps]);
				this.setX(x - w * this._swipeCnt / steps);
				break;
			case "left":
				this.setClip([0, w * (steps - this._swipeCnt) / steps, h, 0]);
				this.setX(x + w * this._swipeCnt / steps);
				break;
			case "bottom-right":
				this.setClip([h * this._swipeCnt / steps, w, h, w * this._swipeCnt / steps]);
				this.setX(x - w * this._swipeCnt / steps);
				this.setY(y - h * this._swipeCnt / steps);
				break;
			case "bottom-left":
				this.setClip([h * this._swipeCnt / steps, w * (steps - this._swipeCnt) / steps, h, 0]);
				this.setX(x + w * this._swipeCnt / steps);
				this.setY(y - h * this._swipeCnt / steps);
				break;
			case "top-left":
				this.setClip([0, w * (steps - this._swipeCnt) / steps, h * (steps - this._swipeCnt) / steps, 0]);
				this.setX(x + w * this._swipeCnt / steps);
				this.setY(y + h * this._swipeCnt / steps);
				break;
			case "top-right":
				this.setClip([0, w, h * (steps - this._swipeCnt) / steps, w * this._swipeCnt / steps]);
				this.setX(x - w * this._swipeCnt / steps);
				this.setY(y + h * this._swipeCnt / steps);
		}		
		this.swipeTimer = window.setTimeout(this+"._swipe()", this._swipeMS);
	}
};

