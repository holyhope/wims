/*
	DynAPI Distribution
	TimerX Class by Raymond Irving (http://dyntools.shorturl.com)

	The DynAPI Distribution is distributed under the terms of the GNU LGPL license.

	requires: Dynlayer
*/

TimerX = {}; // used by dynapi.library

DynLayer.prototype.startTimer=function(interval) {
	if (this.tickTimer>0) this.stopTimer()
	this._timerInterval=interval||5
	this._timerTickCount=0
	this._timerStoped=false
	this._tickTimer=setTimeout(this+'.tickLoop()',this._timerInterval)
}
DynLayer.prototype.tickLoop=function() {
	if (this._timerStoped==true||this._timerStoped==null) return
	this._timerTickCount++;
	this.invokeEvent("timer")
	this._tickTimer=window.setTimeout(this+'.tickLoop()',this._timerInterval)
}
DynLayer.prototype.stopTimer=function() {
	this._timerStoped=true
	clearTimeout(this._tickTimer)
	status="stop"
}
DynLayer.prototype.setTimerInterval=function(interval) {
	this._timerInterval=interval||this._timerInterval
}
DynLayer.prototype.getTimerInterval=function() {
	return this._timerInterval
}
DynLayer.prototype.getTickCount=function() {
	return this._timerTickCount
}
DynLayer.prototype.resetTickCount=function() {
	this._timerTickCount=0
}



