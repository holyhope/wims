!distribute item $wims_read_parm into input_type,jsx_reply,jsx_xsize,jsx_ysize,jsx_imgurl
!default showinfobox=false

!set wims_bound=100
!set name_alert=La taille des requetes sur le serveur ne peut exceder $wims_bound points. Realiser le trace plus rapidement pour que la requete soit plus petite.
!set script$i=$(script$i)\
JXG.Options.point.showInfobox = $showinfobox;\
var brd$i = JXG.JSXGraph.initBoard('jsxbox$i', {axis:false, boundingbox: [0,0,$jsx_xsize,$jsx_ysize],showNavigation:false, showCopyright: false, grid:false });\
var urlImg ='$jsx_imgurl';\
var ima = brd$i.create('image',[urlImg,[0,$jsx_ysize],[$jsx_xsize,-$jsx_ysize]], {fixed: true, highlight: false});\
var jsxbox_free$i=[];\
var p$i=[];
  !if $input_type = points
    !set script$i=$(script$i)\
var coords;\
JXG.addEvent(document.getElementById('jsxbox$i'), 'mousedown', function (e) {\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$i.getMousePosition(e),brd$i);\
p$i.push(brd$i.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,name:'',strokeColor:'black'}));\
c = [Math.round(p$i[p$i.length-1].X()),Math.round(p$i[p$i.length-1].Y())];\
jsxbox_free$i.push(c);\
/*alert(jsxbox_free$i);*/\
}, this);\
function efface$i() {\
brd$i.suspendUpdate();\
brd$i.removeObject(p$i[p$i.length-1]);\
p$i.pop();\
jsxbox_free$i.pop();\
/*alert(jsxbox_free$i+';'+p$i.length);*/\
brd$i.unsuspendUpdate();\
}
  !endif
   
  !if $input_type iswordof line sline segment vector circle
    !if $input_type iswordof line sline segment vector
      !set trace='line'
      !default ooo={straightFirst:true}
      !if $input_type issametext sline
        !set ooo={straightFirst:false}
      !endif
      !if $input_type issametext segment
        !set ooo={straightFirst:false, straightLast:false}
      !endif
      !if $input_type issametext vector
        !set ooo={straightFirst:false, straightLast:false,lastArrow:true}
      !endif
    !endif
    !if $input_type issametext circle
      !set trace='circle'
      !set ooo={}
    !endif
    !set script$i=$(script$i)\
var pp=[];\
var re$i=0;\
JXG.addEvent(document.getElementById('jsxbox$i'), 'mousedown', function (e) {\
if (re$i<2){\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$i.getMousePosition(e), brd$i);\
p$i[re$i] = brd$i.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',name:'',fixed:true,strokeColor:'black'});\
if(re$i==0){lo = brd$i.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',name:'',fixed:false,strokeColor:'black'});}\
lin = brd$i.create($trace,[p$i[0],lo], $ooo);\
var c = [Math.round(p$i[re$i].X()),Math.round(p$i[re$i].Y())];\
jsxbox_free$i.push(c);\
/*alert(jsxbox_free$i);*/\
if(re$i==1){brd$i.removeObject(lo);\
loui$i = brd$i.create($trace,[p$i[0],p$i[1]], $ooo);}\
re$i=re$i+1;\
JXG.addEvent(document.getElementById('jsxbox$i'),'mousemove', function (e) {\
if(re$i==1){\
var coor = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$i.getMousePosition(e), brd$i);\
lo.moveTo(coor.usrCoords.slice(1));}\
},this);\
}\
},this);\
function efface$i() {\
brd$i.removeObject(p$i[0]);\
brd$i.removeObject(p$i[1]);\
brd$i.removeObject(loui$i);\
jsxbox_free$i.pop();\
jsxbox_free$i.pop();\
/*alert(jsxbox_free$i);*/\
return re$i=0;\
}
  !endif
  !if $input_type = rectangle
    !set ooo={straightFirst:false, straightLast:false}
    !set trace='line'
    !set script$i=$(script$i)\
var pp=[];\
var re$i=0;\
JXG.addEvent(document.getElementById('jsxbox$i'), 'mousedown', function (e) {\
if (re$i<2){\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$i.getMousePosition(e), brd$i);\
p$i[re$i] = brd$i.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',name:'',fixed:true,strokeColor:'black'});\
if(re$i==0){pp = brd$i.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,name:'',strokeColor:'black'});\
 li1 = brd$i.create('line',[[p$i[0].X(),p$i[0].Y()],[p$i[0].X(),function(){ return pp.Y();}]], $ooo );\
 li2 = brd$i.create('line',[[p$i[0].X(),function(){ return pp.Y();}],[function(){ return pp.X();},function(){ return pp.Y();}]],$ooo);\
 li3 = brd$i.create('line',[[function(){ return pp.X();},function(){ return pp.Y();}],[function(){ return pp.X();},p$i[0].Y()]],$ooo);\
 li4 = brd$i.create('line',[[function(){ return pp.X();},p$i[0].Y()],[p$i[0].X(),p$i[0].Y()]],$ooo );}\
var c = [Math.round(p$i[re$i].X()),Math.round(p$i[re$i].Y())];\
jsxbox_free$i.push(c);\
/*alert(jsxbox_free$i);*/\
if(re$i==1){JXG.removeAllEvents (document.getElementById ('jsxbox$i'), 'mousemove', this);}\
re$i=re$i+1;\
JXG.addEvent(document.getElementById('jsxbox$i'),'mousemove', function (e) {\
if(re$i==1){\
var coor = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$i.getMousePosition(e), brd$i);\
pp.moveTo(coor.usrCoords.slice(1));}\
},this);\
}\
}, this);\
function efface$i() {\
brd$i.removeObject(pp);\
brd$i.removeObject(p$i);\
brd$i.removeObject(li1);\
brd$i.removeObject(li2);\
brd$i.removeObject(li3);\
brd$i.removeObject(li4);\
jsxbox_free$i.pop();\
jsxbox_free$i.pop();\
return re$i=0;\
}
  !endif
  !if $input_type = polygon
    !set script$i=$(script$i)\
var lu=[];\
var lo=[];\
var re$i=0;\
var jsss$i='';\
JXG.addEvent(document.getElementById('jsxbox$i'),'mousedown', function (e) {\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$i.getMousePosition(e), brd$i);\
p$i[re$i] = brd$i.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,strokeColor:'black', name:''});\
var pp = brd$i.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,strokeColor:'black', name:'', Opacity:0.5});\
lo[re$i] = brd$i.create('segment',[p$i[re$i],pp],{Opacity:0.5});\
if(re$i>=1){\
louis$i = brd$i.create('segment',[p$i[re$i-1],p$i[re$i]]);\
lu[re$i] = brd$i.create('segment',[pp,p$i[0]],{Opacity:0.5});\
brd$i.removeObject(lo[re$i-1]);}\
brd$i.removeObject(lu[re$i-1]);\
var c = [Math.round(p$i[re$i].X()),Math.round(p$i[re$i].Y())];\
jsss$i= jsss$i+c+';';\
re$i=re$i+1;\
JXG.addEvent(document.getElementById('jsxbox$i'),'mousemove', function (z) {\
var coor = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$i.getMousePosition(z), brd$i);\
pp.moveTo(coor.usrCoords.slice(1));\
},this);\
JXG.addEvent(document.getElementById('jsxbox$i'),'mouseleave', function (y) {\
JXG.removeAllEvents (document.getElementById ('jsxbox$i'), 'mousemove', this);\
brd$i.removeObject(lu[re$i]);\
brd$i.removeObject(lo[re$i]);\
luca = brd$i.create('segment',[p$i[re$i-1],p$i[0]]);\
brd$i.removeObject(pp);\
},this);\
}, this);\
function efface$i() {\
brd$i.removeObject(p$i);\
jsss$i='';\
/*alert(jsss$i);*/\
return re$i=0;\
}
   !endif

   !if $input_type = brokenline
!set script$i=$(script$i)\
var lo=[];\
var re$i=0;\
var jsss$i='';\
JXG.addEvent(document.getElementById('jsxbox$i'),'mousedown', function (e) {\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$i.getMousePosition(e), brd$i);\
p$i[re$i] = brd$i.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,strokeColor:'black', name:''});\
var pp = brd$i.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,strokeColor:'black', name:'', Opacity:0.5});\
lo[re$i] = brd$i.create('segment',[p$i[re$i],pp],{Opacity:0.5});\
if(re$i>=1){\
louis$i = brd$i.create('segment',[p$i[re$i-1],p$i[re$i]]);\
brd$i.removeObject(lo[re$i-1]);}\
var c = [Math.round(p$i[re$i].X()),Math.round(p$i[re$i].Y())];\
jsss$i= jsss$i+c+';';\
re$i=re$i+1;\
JXG.addEvent(document.getElementById('jsxbox$i'),'mousemove', function (z) {\
var coor = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$i.getMousePosition(z), brd$i);\
pp.moveTo(coor.usrCoords.slice(1));\
},this);\
JXG.addEvent(document.getElementById('jsxbox$i'),'mouseleave', function (y) {\
JXG.removeAllEvents (document.getElementById ('jsxbox$i'), 'mousemove', this);\
brd$i.removeObject(lo[re$i]);\
brd$i.removeObject(pp);\
},this);\
}, this);\
function efface$i() {\
brd$i.removeObject(p$i);\
jsss$i='';\
return re$i=0;\
}
   !endif
   !if $input_type = curve
!set script$i=$(script$i)\
var pp=[];\
var re$i=0;\
var ree=0;\
var rrr$i=0;\
var aa$i='';\
var tt=0;\
var jj$i=0;\
JXG.addEvent(document.getElementById('jsxbox$i'),'click', function (e) {\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$i.getMousePosition(e), brd$i);\
p$i[re$i+tt] = brd$i.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,strokeColor:'black', name:''});\
c = [Math.round(p$i[re$i+tt].X()),Math.round(p$i[re$i+tt].Y())];\
aa$i=aa$i+c+',';\
re$i=re$i+1;\
JXG.addEvent(document.getElementById('jsxbox$i'),'mousemove', function (z) {\
var coor = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$i.getMousePosition(z), brd$i);\
pp[rrr$i+jj$i] = brd$i.create('point', coor.usrCoords.slice(1),{face:'+',size:'1',Color:'blue',name:''});\
d = [Math.round(pp[rrr$i+jj$i].X()),Math.round(pp[rrr$i+jj$i].Y())];\
aa$i=aa$i+d+',';\
/*brd$i.create('segment',[p$i[0],pp[0]],{Color:'red'});*/\
if(rrr$i>0){brd$i.create('segment',[pp[rrr$i-1+jj$i],pp[rrr$i+jj$i]],{Color:'yellow'});}\
rrr$i=rrr$i+1;\
if(rrr$i>$wims_bound || jj$i+rrr$i>$wims_bound){JXG.removeAllEvents (document.getElementById ('jsxbox$i'), 'mousemove', this);\
alert('$name_alert');\
efface$i();}\
},this);\
if(re$i%2==0){JXG.removeAllEvents (document.getElementById ('jsxbox$i'), 'mousemove', this);\
aa$i=aa$i.substr(0,aa$i.length-1);\
aa$i=aa$i+';';\
tt=tt+re$i;\
jj$i=jj$i+rrr$i;\
/*alert('re$i='+re$i+'tt='+tt);\
alert(aa$i);*/\
re$i=0;\
rrr$i=0;}\
}, this);\
function efface$i() {\
brd$i.removeObject(p$i);\
brd$i.removeObject(pp);\
JXG.removeAllEvents (document.getElementById ('jsxbox$i'), 'mousemove', this);\
aa$i='';\
re$i=0;\
rrr$i=0;\
jj$i=0;\
}
   !endif

!readproc slib/geo2D/jsxgraph jsxbox$i,$jsx_xsize x $jsx_ysize,$(script$i)

$slib_out
<script type="text/javascript">
/*<![CDATA[*/
!if $input_type iswordof points
  var capture$i = function() {document.getElementById('$jsx_reply').value='free='+jsxbox_free$i +'';}
!endif
!if $input_type iswordof line sline segment vector rectangle
  var capture$i = function() {if(re$i==2){document.getElementById('$jsx_reply').value='free='+jsxbox_free$i +'';}}
!endif
!if $input_type iswordof circle
  var capture$i = function() {
        document.getElementById('$jsx_reply').value='free=' + [Math.round(p$i[0].X()),Math.round(p$i[0].Y()),Math.round(p$i[0].Dist(p$i[1]))] +'';}
!endif
!if $input_type iswordof polygon brokenline 
var capture$i = function() {
    document.getElementById('$jsx_reply').value='free=' + jsss$i +'';}
!endif
!if $input_type iswordof curve
  var capture$i = function(){
    document.getElementById('$jsx_reply').value='free=' + aa$i;
  }
!endif
/*]]>*/
</script>
