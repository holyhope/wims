!distribute item $wims_read_parm into input_type,jsx_reply,jsx_xsize,jsx_ysize,jsx_imgurl
!default showinfobox=false
!set input_cnt=!rows2lines $(replygood$i[;1])
!set input_cnt=!itemcnt $input_cnt
!set input_cnt=$[$input_cnt-1]

!set wims_bound=100
!set name_alert=La taille des requetes sur le serveur ne peut exceder $wims_bound points. Realiser le trace plus rapidement pour que la requete soit plus petite.
!set script=$script\
JXG.Options.point.showInfobox = $showinfobox;\
var brd = JXG.JSXGraph.initBoard('jsxbox$i', {axis:false, boundingbox: [0,0,$jsx_xsize,$jsx_ysize],showNavigation:false, showCopyright: false, grid:false });\
var urlImg ='$jsx_imgurl';\
var ima = brd.create('image',[urlImg,[0,$jsx_ysize],[$jsx_xsize,-$jsx_ysize]], {fixed: true, highlight: false});\
var jsxbox_free=[];\
var p=[];
  !if $input_type = points
    !set script=$script\
var coords;\
JXG.addEvent(document.getElementById('jsxbox$i'), 'mousedown', function (e) {\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd.getMousePosition(e),brd);\
p.push(brd.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,name:'',strokeColor:'black'}));\
c = [Math.round(p[p.length-1].X()),Math.round(p[p.length-1].Y())];\
jsxbox_free.push(c);\
/*alert(jsxbox_free);*/\
}, this);\
function efface() {\
brd.suspendUpdate();\
brd.removeObject(p[p.length-1]);\
p.splice(p.length-1,1);\
jsxbox_free.splice(p.length,1);\
/*alert(jsxbox_free);*/\
brd.unsuspendUpdate();\
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
    !set script=$script\
var pp=[];\
var re=0;\
JXG.addEvent(document.getElementById('jsxbox$i'), 'mousedown', function (e) {\
if (re<2){\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd.getMousePosition(e), brd);\
p[re] = brd.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',name:'',fixed:true,strokeColor:'black'});\
if(re==0){lo = brd.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',name:'',fixed:false,strokeColor:'black'});}\
lin = brd.create($trace,[p[0],lo], $ooo);\
var c = [Math.round(p[re].X()),Math.round(p[re].Y())];\
jsxbox_free.push(c);\
/*alert(jsxbox_free);*/\
if(re==1){brd.removeObject(lo);\
loui = brd.create($trace,[p[0],p[1]], $ooo);}\
re=re+1;\
JXG.addEvent(document.getElementById('jsxbox$i'),'mousemove', function (e) {\
if(re==1){\
var coor = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd.getMousePosition(e), brd);\
lo.moveTo(coor.usrCoords.slice(1));}\
},this);\
}\
},this);\
function efface() {\
brd.removeObject(p[0]);\
brd.removeObject(p[1]);\
brd.removeObject(loui);\
jsxbox_free.splice(p.lenght,2);\
return re=0;\
}
  !endif
  !if $input_type = rectangle
    !set ooo={straightFirst:false, straightLast:false}
    !set trace='line'
    !set script=$script\
var pp=[];\
var re=0;\
JXG.addEvent(document.getElementById('jsxbox$i'), 'mousedown', function (e) {\
if (re<2){\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd.getMousePosition(e), brd);\
p[re] = brd.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',name:'',fixed:true,strokeColor:'black'});\
if(re==0){pp = brd.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,name:'',strokeColor:'black'});\
li1 = brd.create('line',[[p[0].X(),p[0].Y()],[p[0].X(),function(){ return pp.Y();}]], $ooo );\
li2 = brd.create('line',[[p[0].X(),function(){ return pp.Y();}],[function(){ return pp.X();},function(){ return pp.Y();}]],$ooo);\
li3 = brd.create('line',[[function(){ return pp.X();},function(){ return pp.Y();}],[function(){ return pp.X();},p[0].Y()]],$ooo);\
li4 = brd.create('line',[[function(){ return pp.X();},p[0].Y()],[p[0].X(),p[0].Y()]],$ooo );}\
var c = [Math.round(p[re].X()),Math.round(p[re].Y())];\
jsxbox_free.push(c);\
/*alert(jsxbox_free);*/\
if(re==1){JXG.removeAllEvents (document.getElementById ('jsxbox$i'), 'mousemove', this);}\
re=re+1;\
JXG.addEvent(document.getElementById('jsxbox$i'),'mousemove', function (e) {\
if(re==1){\
var coor = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd.getMousePosition(e), brd);\
pp.moveTo(coor.usrCoords.slice(1));}\
},this);\
}\
}, this);\
function efface() {\
brd.removeObject(pp);\
brd.removeObject(p);\
brd.removeObject(li1);\
brd.removeObject(li2);\
brd.removeObject(li3);\
brd.removeObject(li4);\
jsxbox_free.splice(p.lenght,2);\
return re=0;\
}
  !endif
  !if $input_type = polygon
    !set script=$script\
var lu=[];\
var lo=[];\
var re=0;\
var jsss='';\
JXG.addEvent(document.getElementById('jsxbox$i'),'mousedown', function (e) {\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd.getMousePosition(e), brd);\
p[re] = brd.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,strokeColor:'black', name:''});\
var pp = brd.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,strokeColor:'black', name:'', Opacity:0.5});\
lo[re] = brd.create('segment',[p[re],pp],{Opacity:0.5});\
if(re>=1){\
louis = brd.create('segment',[p[re-1],p[re]]);\
lu[re] = brd.create('segment',[pp,p[0]],{Opacity:0.5});\
brd.removeObject(lo[re-1]);}\
brd.removeObject(lu[re-1]);\
var c = [Math.round(p[re].X()),Math.round(p[re].Y())];\
jsss= jsss+c+';';\
re=re+1;\
JXG.addEvent(document.getElementById('jsxbox$i'),'mousemove', function (z) {\
var coor = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd.getMousePosition(z), brd);\
pp.moveTo(coor.usrCoords.slice(1));\
},this);\
JXG.addEvent(document.getElementById('jsxbox$i'),'mouseleave', function (y) {\
JXG.removeAllEvents (document.getElementById ('jsxbox$i'), 'mousemove', this);\
brd.removeObject(lu[re]);\
brd.removeObject(lo[re]);\
luca = brd.create('segment',[p[re-1],p[0]]);\
brd.removeObject(pp);\
},this);\
}, this);\
function efface() {\
brd.removeObject(p);\
jsss='';\
/*alert(jsss);*/\
return re=0;\
}
   !endif

   !if $input_type = brokenline
!set script=$script\
var lo=[];\
var re=0;\
var jsss='';\
JXG.addEvent(document.getElementById('jsxbox$i'),'mousedown', function (e) {\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd.getMousePosition(e), brd);\
p[re] = brd.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,strokeColor:'black', name:''});\
var pp = brd.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,strokeColor:'black', name:'', Opacity:0.5});\
lo[re] = brd.create('segment',[p[re],pp],{Opacity:0.5});\
if(re>=1){\
louis = brd.create('segment',[p[re-1],p[re]]);\
brd.removeObject(lo[re-1]);}\
var c = [Math.round(p[re].X()),Math.round(p[re].Y())];\
jsss= jsss+c+';';\
re=re+1;\
JXG.addEvent(document.getElementById('jsxbox$i'),'mousemove', function (z) {\
var coor = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd.getMousePosition(z), brd);\
pp.moveTo(coor.usrCoords.slice(1));\
},this);\
JXG.addEvent(document.getElementById('jsxbox$i'),'mouseleave', function (y) {\
JXG.removeAllEvents (document.getElementById ('jsxbox$i'), 'mousemove', this);\
brd.removeObject(lo[re]);\
brd.removeObject(pp);\
},this);\
}, this);\
function efface() {\
brd.removeObject(p);\
jsss='';\
return re=0;\
}
   !endif
   !if $input_type = curve
!set script=$script\
var pp=[];\
var re=0;\
var ree=0;\
var rrr=0;\
var aa='';\
var tt=0;\
var jj=0;\
JXG.addEvent(document.getElementById('jsxbox$i'),'click', function (e) {\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd.getMousePosition(e), brd);\
p[re+tt] = brd.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,strokeColor:'black', name:''});\
c = [Math.round(p[re+tt].X()),Math.round(p[re+tt].Y())];\
aa=aa+c+',';\
re=re+1;\
JXG.addEvent(document.getElementById('jsxbox$i'),'mousemove', function (z) {\
var coor = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd.getMousePosition(z), brd);\
pp[rrr+jj] = brd.create('point', coor.usrCoords.slice(1),{face:'+',size:'1',Color:'blue',name:''});\
d = [Math.round(pp[rrr+jj].X()),Math.round(pp[rrr+jj].Y())];\
aa=aa+d+',';\
/*brd.create('segment',[p[0],pp[0]],{Color:'blue'});*/\
if(rrr>0){brd.create('segment',[pp[rrr-1+jj],pp[rrr+jj]],{Color:'yellow'});}\
rrr=rrr+1;\
if(rrr>$wims_bound || jj+rrr>$wims_bound){JXG.removeAllEvents (document.getElementById ('jsxbox$i'), 'mousemove', this);\
alert('$name_alert');\
efface();}\
},this);\
if(re%2==0){JXG.removeAllEvents (document.getElementById ('jsxbox$i'), 'mousemove', this);\
aa=aa.substr(0,aa.length-1);\
aa=aa+';';\
tt=tt+re;\
jj=jj+rrr;\
/*alert('re='+re+'tt='+tt);\
alert(aa);*/\
re=0;\
rrr=0;}\
}, this);\
function efface() {\
brd.removeObject(p);\
brd.removeObject(pp);\
JXG.removeAllEvents (document.getElementById ('jsxbox$i'), 'mousemove', this);\
aa='';\
re=0;\
rrr=0;\
jj=0;\
}
   !endif

!readproc slib/geo2D/jsxgraph jsxbox$i,$jsx_xsize x $jsx_ysize,$script

$slib_out
<script type="text/javascript">
/*<![CDATA[*/
!if $input_type iswordof points
  var capture = function() {document.getElementById('$jsx_reply').value='free='+jsxbox_free +'';}
!endif
!if $input_type iswordof line sline segment vector rectangle
  var capture = function() {if(re==2){document.getElementById('$jsx_reply').value='free='+jsxbox_free +'';}}
!endif
!if $input_type iswordof circle
  var capture = function() {
        document.getElementById('$jsx_reply').value='free=' + [Math.round(p[0].X()),Math.round(p[0].Y()),Math.round(p[0].Dist(p[1]))] +'';}
!endif
!if $input_type iswordof polygon brokenline 
var capture = function() {
    document.getElementById('$jsx_reply').value='free=' + jsss +'';}
!endif
!if $input_type iswordof curve
  var capture = function(){
    document.getElementById('$jsx_reply').value='free=' + aa;
  }
!endif
/*]]>*/
</script>
