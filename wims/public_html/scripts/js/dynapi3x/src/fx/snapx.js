/*
    DynAPI Distribution
    SnapX Class by Leif Westerlind <warp-9.9 (at) usa (dot) net>

    The DynAPI Distribution is distributed under the terms of the GNU LGPL license.

    requires: Dynlayer
*/

var p = DynLayer.prototype;
p._SnapSetLocation = p.setLocation;
p.setLocation  = function(x,y){	
	if(Math.abs(x-this._snapLockX)>20) this._snapLockX=null;
	if(Math.abs(y-this._snapLockY)>20) this._snapLockY=null;
	this._SnapSetLocation(this._snapLockX||x,this._snapLockY||y);
	status=this.lockX
	if (this.isSnapEnabled) {
		var dirX = '', dirY = '';

		// get direction
		if (this._snapX != this.x){
			if (this._snapX < this.x){
				dirX="E";
			}
			else {
				dirX="W";
			}
		}
		if (this._snapY != this.y){
			if (this._snapY < this.y){
				dirY="S";
			}
			else {
				dirY="N";
			}
		}

		this._snapX = this.x;
		this._snapY = this.y;
		this._snapDirection = dirY + dirX;
		this._checkForSnap();	
	}
};
p.enableSnap = function (){
    this.isSnapEnabled = true;
    this.setSnapBoundary();
    this.setSnapBoundaryType();

    this._snapX = this.x;
    this._snapY = this.y;

/*    this.snapEvent ={
        onlocationchange : function(e) {
            var dirX = '', dirY = '', me = e.getSource();

            // get direction
            if (me._snapX != me.x){
                if (me._snapX < me.x){
                    dirX="E";
                }
                else {
                    dirX="W";
                }
            }
            if (me._snapY != me.y){
                if (me._snapY < me.y){
                    dirY="S";
                }
                else {
                    dirY="N";
                }
            }

            me._snapX = me.x;
            me._snapY = me.y;
            me._snapDirection = dirY + dirX;
            me._checkForSnap();
        }
    }
    this.addEventListener(this.snapEvent);
*/
};
p.disableSnap = function(){
    this.isSnapEnabled = false;
};
p.setSnapBoundaryType = function(snapBoundaryType){
    var def = 'outer';
    if (arguments.length == 0){
        this._snapBoundaryType = def;
    }
    else {
        this._snapBoundaryType = snapBoundaryType;
    }
};
p.getSnapBoundaryType = function(){
    return(this._snapBoundaryType);
};

DynLayer._snapBoundaryDefault = 25;
p.setSnapBoundaryDefault = function(b){
    DynLayer._snapBoundaryDefault = b;
}

p.getSnapBoundaryDefault = function(){
    return(DynLayer._snapBoundaryDefault);
}

/*
INPUT:
	0 args: set snapBoundaryType to outer, set boundary to snapBoundaryDefault
	1 arg: if snapBoundaryType set boundary to default,
		if boundary set for all sides and snapBoundaryType inner & outer
	2 args: snapBoundaryType, boundary for all sides
	5 args: snapBoundaryType, t, r, b, l
*/
p.setSnapBoundary = function(){
	var a=arguments;
	var snapDefault = DynLayer._snapBoundaryDefault;
    if (a.length == 0){
        this.setSnapBoundaryType('both');
        this._snapBndTi = snapDefault;
        this._snapBndRi = snapDefault;
        this._snapBndBi = snapDefault;
        this._snapBndLi = snapDefault;
        this._snapBndTo = snapDefault;
        this._snapBndRo = snapDefault;
        this._snapBndBo = snapDefault;
        this._snapBndLo = snapDefault;
    }
    if (a.length == 1){
        if(a[0] == 'inner' || a[0] == 'outer' || a[0] == 'both'){
            this.setSnapBoundaryType(a[0]);
            this._snapBndTi = snapDefault;
            this._snapBndRi = snapDefault;
            this._snapBndBi = snapDefault;
            this._snapBndLi = snapDefault;
            this._snapBndTo = snapDefault;
            this._snapBndRo = snapDefault;
            this._snapBndBo = snapDefault;
            this._snapBndLo = snapDefault;
        }
        else {
            this.setSnapBoundaryType('both');
            this._snapBndTi = a[0];
            this._snapBndRi = a[0];
            this._snapBndBi = a[0];
            this._snapBndLi = a[0];
            this._snapBndTo = a[0];
            this._snapBndRo = a[0];
            this._snapBndBo = a[0];
            this._snapBndLo = a[0];
        }
    }
    else if (a.length == 2){
        var snapBoundaryType = arguments[0];

        if (snapBoundaryType == 'inner'){
            this.setSnapBoundaryType('inner');
            this._snapBndTi = a[1];
            this._snapBndRi = a[1];
            this._snapBndBi = a[1];
            this._snapBndLi = a[1];
        }
        else if (snapBoundaryType == 'outer'){
            this.setSnapBoundaryType('outer');
            this._snapBndTo = a[1];
            this._snapBndRo = a[1];
            this._snapBndBo = a[1];
            this._snapBndLo = a[1];
        }
        else if (snapBoundaryType == 'both' || snapBoundaryType == null){
            this.setSnapBoundaryType('both');
            this._snapBndTi = a[1];
            this._snapBndRi = a[1];
            this._snapBndBi = a[1];
            this._snapBndLi = a[1];
            this._snapBndTo = a[1];
            this._snapBndRo = a[1];
            this._snapBndBo = a[1];
            this._snapBndLo = a[1];
        }
    }
    else if (a.length == 5){
        if(a[0] == 'inner' || a[0] == 'outer' || a[0] == 'both'){
            this.setSnapBoundaryType(a[0]);
        }

        if (this._snapBoundaryType == 'inner'){
            this._snapBndTi = a[1];
            this._snapBndRi = a[2];
            this._snapBndBi = a[3];
            this._snapBndLi = a[4];
        }
        else if (this._snapBoundaryType == 'outer'){
            this._snapBndTo = a[1];
            this._snapBndRo = a[2];
            this._snapBndBo = a[3];
            this._snapBndLo = a[4];
        }
        else if (this._snapBoundaryType == 'both'){
            this._snapBndTi = a[1];
            this._snapBndRi = a[2];
            this._snapBndBi = a[3];
            this._snapBndLi = a[4];
            this._snapBndTo = a[1];
            this._snapBndRo = a[2];
            this._snapBndBo = a[3];
            this._snapBndLo = a[4];
        }
    }
    else {
        this.setSnapBoundaryType('both');
        this._snapBndTo = snapDefault;
        this._snapBndRo = snapDefault;
        this._snapBndBo = snapDefault;
        this._snapBndLo = snapDefault;
        this._snapBndTi = snapDefault;
        this._snapBndRi = snapDefault;
        this._snapBndBi = snapDefault;
        this._snapBndLi = snapDefault;
    }
};

p.getSnapBoundary = function(t){
    var To,Ro,Bo,Lo,Ti,Ri,Bi,Li,bndAry,X,Y,W,H;

    X = this.x;
    Y = this.y;
    W = this.w;
    H = this.h;

    Ti = Y + this._snapBndTi;
    Ri = X + W - this._snapBndRi;
    Bi = Y + H - this._snapBndBi;
    Li = X + this._snapBndLi;

    To = Y - this._snapBndTo;
    Ro = X + W + this._snapBndRo;
    Bo = Y + H + this._snapBndBo;
    Lo = X - this._snapBndLo;

    if (t==null) bndAry = [Ti,Ri,Bi,Li,To,Ro,Bo,Lo];
    else {
        if (t=='inner') bndAry = [Ti,Ri,Bi,Li];
        else if (t=='outer') bndAry = [To,Ro,Bo,Lo];
        else if (t=='both') bndAry = [Ti,Ri,Bi,Li,To,Ro,Bo,Lo];
    }
    return(bndAry);
};

p._checkForSnap = function(){
    switch (this._snapBoundaryType) {
        case 'outer' :
            this._checkForSnapOuter();
            break;
        case 'inner' :
            this._checkForSnapInner();
            break;
        case 'both' :
            this._checkForSnapInner();
            this._checkForSnapOuter();
            break;
        default:
            return(false);
    }
};

p.getSnapDirection = function (){
    return(this._snapDirection);
};

p._checkForSnapInner = function(){
    if (!this.parent.children.length>0) return(false);
    if (!this.isSnapEnabled==true) return(false);

    var ch,chX1,chY1,chX2,chY2,chBX1,chBY1,chBX2,chBY2
    var sX1,sY1,sX2,sY2,chBndAry;
    var C1,C2a,C2b,C3,C4a,C4b,C5,C6a,C6b,C7,C8a,C8b,sDir;

    sX1 = this.x;
    sY1 = this.y;
    sW  = this.w;
    sH  = this.h;
    sX2 = sX1 + sW;
    sY2 = sY1 + sH;
    sDir = this.getSnapDirection();

    for (var i in this.parent.children){
        ch = this.parent.children[i];
        if (ch != this && ch.isSnapEnabled == true){
            chX1 = ch.x;
            chY1 = ch.y;
            chX2 = chX1 + ch.w;
            chY2 = chY1 + ch.h;
            chBndAry = ch.getSnapBoundary('inner');
            chBiX1 = chBndAry[3];
            chBiY1 = chBndAry[0];
            chBiX2 = chBndAry[1];
            chBiY2 = chBndAry[2];

            // inner top-left corner, source top-left, move N, NW, W
            C1  = (sX1 <= chBiX1 && sX1 >  chX1   && sY1 <= chBiY1 && sY1 > chY1   && (sDir == 'N' || sDir == 'NW' || sDir == 'W'));

            // inner top-middle side, source top-left, move NE, N, NW
            C2a = (sX1 >  chBiX1 && sX1 <  chBiX2 && sY1 <= chBiY1 && sY1 > chY1   && (sDir == 'NE' || sDir == 'N' || sDir == 'NW'));

            // inner top-middle side, source top-right, move NE, N, NW
            C2b = (sX2 >  chBiX1 && sX2 <  chBiX2 && sY1 <= chBiY1 && sY1 > chY1   && (sDir == 'NE' || sDir == 'N' || sDir == 'NW'));

            // inner top-right corner, source top-right, move E, NE, N
            C3  = (sX2 >= chBiX2 && sX2 <  chX2   && sY1 <= chBiY1 && sY1 > chY1   && (sDir == 'E' || sDir == 'NE' || sDir == 'N'));

            // inner right-middle side, source top-right, move SE, E, NE
            C4a = (sX2 >= chBiX2 && sX2 <  chX2   && sY1 >  chBiY1 && sY1 < chBiY2 && (sDir == 'SE' || sDir == 'E' || sDir == 'NE'));

            // inner right-middle side, source bottom-right, move SE, E, NE
            C4b = (sX2 >= chBiX2 && sX2 <  chX2   && sY2 >  chBiY1 && sY2 < chBiY2 && (sDir == 'SE' || sDir == 'E' || sDir == 'NE'));

            // inner bottom-right corner, source lower-right, move dir E, SE, S
            C5  = (sX2 >= chBiX2 && sX2 <  chX2   && sY2 >= chBiY2 && sY2 < chY2   && (sDir == 'E' || sDir == 'SE' || sDir == 'S'));

            // inner bottom-middle side, source lower-left, move SW, S, SE
            C6a = (sX1 >  chBiX1 && sX1 <  chBiX2 && sY2 >= chBiY2 && sY2 < chY2   && (sDir == 'SW' || sDir == 'S' || sDir == 'SE'));

            // inner bottom-middle side, source lower-right, move SW, S, SE
            C6b = (sX2 >  chBiX1 && sX2 <  chBiX2 && sY2 >= chBiY2 && sY2 < chY2   && (sDir == 'SW' || sDir == 'S' || sDir == 'SE'));

            // inner bottom-left corner, source lower-left, move W, SW, S
            C7  = (sX1 <= chBiX1 && sX1 >  chX1   && sY2 >= chBiY2 && sY2 < chY2   && (sDir == 'W' || sDir == 'SW' || sDir == 'S'));

            // inner left-middle side, source top-left, move NW, W, SW
            C8a = (sX1 <= chBiX1 && sX1 >  chX1   && sY1 >  chBiY1 && sY1 < chBiY2 && (sDir == 'NW' || sDir == 'W' || sDir == 'SW'));

            // inner left-middle side, source bottom-left, move NW, W, SW
            C8b = (sX1 <= chBiX1 && sX1 >  chX1   && sY2 >  chBiY1 && sY2 < chBiY2 && (sDir == 'NW' || sDir == 'W' || sDir == 'SW'));

            if (C1){
                this._SnapSetLocation(chX1, chY1);
            }
            else if (C3){
                this._SnapSetLocation(chX2-sW, chY1);
            }
            else if (C5){
                this._SnapSetLocation(chX2-sW, chY2-sH);
            }
            else if (C7){
                this._SnapSetLocation(chX1, chY2-sH);
            }
            else if (C2a || C2b){
                this._SnapSetLocation(sX1, chY1);
            }
            else if (C4a || C4b){
                this._SnapSetLocation(chX2-sW, sY1);
            }
            else if (C6a || C6b){
                this._SnapSetLocation(sX1, chY2-sH);
            }
            else if (C8a || C8b){
                this._SnapSetLocation(chX1 , sY1);
            }

            if (C1 || C2a || C2b || C3 || C4a || C4b ||
                 C5 || C6a || C6b || C7 || C8a || C8b){
                this._snapObject=ch
                this.invokeEvent("snap");
                ch._snapObject=this
                ch.invokeEvent("snap");
            }
        }
    }
    return(false);
};

p._checkForSnapOuter = function(){
    if (! this.parent.children.length > 0) return(false);
    if (! this.isSnapEnabled == true) return(false);

    var ch,chX1,chY1,chX2,chY2,chBX1,chBY1,chBX2,chBY2,sX1,sY1,sX2,sY2,chBndAry,C1,C2a,C2b,C3,C4a,C4b,C5,C6a,C6b,C7,C8a,C8b,sDir;

    sX1 = this.x;
    sY1 = this.y;
    sW  = this.w;
    sH  = this.h;
    sX2 = sX1 + sW;
    sY2 = sY1 + sH;
    sDir = this.getSnapDirection();

    for (var i in this.parent.children){
        ch = this.parent.children[i];
        if (ch != this && ch.isSnapEnabled == true){
            chX1 = ch.x;
            chY1 = ch.y;
            chX2 = chX1 + ch.w;
            chY2 = chY1 + ch.h;
            chBndAry = ch.getSnapBoundary('outer');
            chBoX1 = chBndAry[3];
            chBoY1 = chBndAry[0];
            chBoX2 = chBndAry[1];
            chBoY2 = chBndAry[2];

            // outer top-left corner, source lower-right, move dir E, SE, S
            C1  = (sX2 >= chBoX1 && sX2 <  chX1 && sY2 >= chBoY1 && sY2 <  chY1 && (sDir == 'E' || sDir == 'SE' || sDir == 'S'));

            // outer top-middle side, source lower-left, move SW, S, SE
            C2a = (sX1 >= chX1   && sX1 <= chX2 && sY2 >= chBoY1 && sY2 <  chY1 && (sDir == 'SW' || sDir == 'S' || sDir == 'SE'));

            // outer top-middle side, source lower-right, move SW, S, SE
            C2b = (sX2 >= chX1   && sX2 <= chX2 && sY2 >= chBoY1 && sY2 <  chY1 && (sDir == 'SW' || sDir == 'S' || sDir == 'SE'));

            // outer top-right corner, source lower-left, move W, SW, S
            C3  = (sX1 <= chBoX2 && sX1 >  chX2 && sY2 >= chBoY1 && sY2 <  chY1 && (sDir == 'W' || sDir == 'SW' || sDir == 'S'));

            // outer right-middle side, source top-left, move NW, W, SW
            C4a = (sX1 <= chBoX2 && sX1 >  chX2 && sY1 >= chY1   && sY1 <= chY2 && (sDir == 'NW' || sDir == 'W' || sDir == 'SW'));

            // outer right-middle side, source bottom-left, move NW, W, SW
            C4b = (sX1 <= chBoX2 && sX1 >  chX2 && sY2 >= chY1   && sY2 <= chY2 && (sDir == 'NW' || sDir == 'W' || sDir == 'SW'));

            // outer bottom-right corner, source top-left, move N, NW, W
            C5  = (sX1 <= chBoX2 && sX1 >  chX2 && sY1 <= chBoY2 && sY1 >  chY2 && (sDir == 'N' || sDir == 'NW' || sDir == 'W'));

            // outer bottom-middle side, source top-left, move NE, N, NW
            C6a = (sX1 >= chX1   && sX1 <= chX2 && sY1 <= chBoY2 && sY1 >  chY2 && (sDir == 'NE' || sDir == 'N' || sDir == 'NW'));

            // outer bottom-middle side, source top-right, move NE, N, NW
            C6b = (sX2 >= chX1   && sX2 <= chX2 && sY1 <= chBoY2 && sY1 >  chY2 && (sDir == 'NE' || sDir == 'N' || sDir == 'NW'));

            // outer bottom-left corner, source top-right, move E, NE, N
            C7  = (sX2 >= chBoX1 && sX2 <  chX1 && sY1 <= chBoY2 && sY1 >  chY2 && (sDir == 'E' || sDir == 'NE' || sDir == 'N'));

            // outer left-middle side, source top-right, move SE, E, NE
            C8a = (sX2 >= chBoX1 && sX2 <  chX1 && sY1 >= chY1  && sY1  <= chY2 && (sDir == 'SE' || sDir == 'E' || sDir == 'NE'));

            // outer left-middle side, source bottom-right, move SE, E, NE
            C8b = (sX2 >= chBoX1 && sX2 <  chX1 && sY2 >= chY1  && sY2  <= chY2 && (sDir == 'SE' || sDir == 'E' || sDir == 'NE'));

            if (C1){
                this._SnapSetLocation(chX1-sW, chY1-sH);
            }
            else if (C3){
                this._SnapSetLocation(chX2, chY1-sH);
            }
            else if (C5){
                this._SnapSetLocation(chX2, chY2);
            }
            else if (C7){
                this._SnapSetLocation(chX1-sW, chY2);
            }
            else if (C2a || C2b){
                if(!this._snapLockY) this._snapLockY=chY1-sH;
                this._SnapSetLocation(sX1 , this._snapLockY);
            }
            else if (C4a || C4b){
                if(!this._snapLockX) this._snapLockX=chX2;
                this._SnapSetLocation(this._snapLockX, sY1);
            }
            else if (C6a || C6b){
                if(!this._snapLockY) this._snapLockY=chY2;
                this._SnapSetLocation(sX1 , this._snapLockY);
            }
            else if (C8a || C8b){
                if(!this._snapLockX) this._snapLockX=chX1-sW;
                this._SnapSetLocation(chX1-sW , sY1);
            }

            if (C1 || C2a || C2b || C3 || C4a || C4b ||
                 C5 || C6a || C6b || C7 || C8a || C8b){
                this._snapObject=ch
                this.invokeEvent("snap");
                ch._snapObject=this
                ch.invokeEvent("snap");
            }
        }
    }

    return false;
};
p.enableStickySnap = function(){
    this._stickySnap = true;
};
p.disableStickySnap = function(){
    this._stickySnap = false;
};
p.setStickySnap = function(){
    if (arguments.length == 0){
        this._stickySnapBorder == this._snapBoundaryDefault;
    }
    else if (arguments[0] === true){
        this._stickySnap = true;
    }
    else if (arguments[0] === false){
        this._stickySnap = false;
    } else {

    }
}


