!distribute item $wims_read_parm into input_type,jsx_reply,jsx_xsize,jsx_ysize,jsx_imgurl,jsx_nb
!default showinfobox=false

!set wims_bound=200
!set name_alert=La taille des requetes sur le serveur ne peut exceder $wims_bound points. Realiser le tracé plus rapidement pour que la requete soit plus petite.
!set script$jsx_nb=$(script$jsx_nb)\
JXG.Options.point.showInfobox = $showinfobox;\
var brd$jsx_nb = init_jsx_brd$jsx_nb();\
function init_jsx_brd$jsx_nb() {\
  var jsx_brd = JXG.JSXGraph.initBoard('jsxbox$jsx_nb',\
                                          {axis:false,\
                                           boundingbox: [0, 0, $jsx_xsize, $jsx_ysize],\
                                           showNavigation: false,\
                                           showCopyright:  false,\
                                           grid: false });\
  jsx_brd.create('image',['$jsx_imgurl', [0,$jsx_ysize], [$jsx_xsize,-$jsx_ysize]], {fixed: true, highlight: false});\
  return jsx_brd;\
}\
/** UNCOMMENT THIS TO ENABLE DEBUG PRINT. ** var debug_field = document.getElementById("jsx_debug");\
function print_debug(chaine){debug_field.insertAdjacentHTML('beforeEnd', chaine+"\n");}*/\
var jsxbox_free$jsx_nb=[];\
var p$jsx_nb=[];\
// Niveau de zoom\
var zoom_level$jsx_nb = 1.0;\
// Agrandit la zone de travail\
function zoom_in_jsx$jsx_nb() {\
  zoom_level$jsx_nb = Math.min(zoom_level$jsx_nb + 0.1, 3.0);\
  var new_width = $jsx_xsize * zoom_level$jsx_nb;\
  var new_height = $jsx_ysize * zoom_level$jsx_nb;\
  brd$jsx_nb.resizeContainer(new_width, new_height);\
}\
// Réduit la zone de travail\
function zoom_out_jsx$jsx_nb() {\
  zoom_level$jsx_nb = Math.max(zoom_level$jsx_nb - 0.1, 0.5);\
  var new_width = $jsx_xsize * zoom_level$jsx_nb;\
  var new_height = $jsx_ysize * zoom_level$jsx_nb;\
  brd$jsx_nb.resizeContainer(new_width, new_height);\
}\
// Réinitialise la taille de la zone de travail\
function zoom_reset_jsx$jsx_nb() {\
  zoom_level$jsx_nb = 1.0;\
  brd$jsx_nb.resizeContainer($jsx_xsize,$jsx_ysize);\
}

!if $input_type iswordof points bound
  !set script$jsx_nb=$(script$jsx_nb)\
var coords;\
JXG.addEvent(document.getElementById('jsxbox$jsx_nb'), 'mousedown', function (e) {\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$jsx_nb.getMousePosition(e),brd$jsx_nb);\
p$jsx_nb.push(brd$jsx_nb.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,name:'',strokeColor:'black'}));\
c = [Math.round(p$jsx_nb[p$jsx_nb.length-1].X()),Math.round(p$jsx_nb[p$jsx_nb.length-1].Y())];\
jsxbox_free$jsx_nb.push(c);\
/*alert(jsxbox_free$jsx_nb);*/\
}, this);\
function efface$jsx_nb() {\
brd$jsx_nb.suspendUpdate();\
brd$jsx_nb.removeObject(p$jsx_nb[p$jsx_nb.length-1]);\
p$jsx_nb.pop();\
jsxbox_free$jsx_nb.pop();\
/*alert(jsxbox_free$jsx_nb+';'+p$jsx_nb.length);*/\
brd$jsx_nb.unsuspendUpdate();\
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
  !set script$jsx_nb=$(script$jsx_nb)\
var pp=[];\
var re$jsx_nb=0;\
JXG.addEvent(document.getElementById('jsxbox$jsx_nb'), 'mousedown', function (e) {\
if (re$jsx_nb<2){\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$jsx_nb.getMousePosition(e), brd$jsx_nb);\
p$jsx_nb[re$jsx_nb] = brd$jsx_nb.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',name:'',fixed:true,strokeColor:'black'});\
if(re$jsx_nb==0){lo = brd$jsx_nb.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',name:'',fixed:false,strokeColor:'black'});}\
lin = brd$jsx_nb.create($trace,[p$jsx_nb[0],lo], $ooo);\
var c = [Math.round(p$jsx_nb[re$jsx_nb].X()),Math.round(p$jsx_nb[re$jsx_nb].Y())];\
jsxbox_free$jsx_nb.push(c);\
/*alert(jsxbox_free$jsx_nb);*/\
if(re$jsx_nb==1){brd$jsx_nb.removeObject(lo);\
loui$jsx_nb = brd$jsx_nb.create($trace,[p$jsx_nb[0],p$jsx_nb[1]], $ooo);}\
re$jsx_nb=re$jsx_nb+1;\
JXG.addEvent(document.getElementById('jsxbox$jsx_nb'),'mousemove', function (e) {\
if(re$jsx_nb==1){\
var coor = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$jsx_nb.getMousePosition(e), brd$jsx_nb);\
lo.moveTo(coor.usrCoords.slice(1));}\
},this);\
}\
},this);\
function efface$jsx_nb() {\
brd$jsx_nb.removeObject(p$jsx_nb[0]);\
brd$jsx_nb.removeObject(p$jsx_nb[1]);\
brd$jsx_nb.removeObject(loui$jsx_nb);\
jsxbox_free$jsx_nb.pop();\
jsxbox_free$jsx_nb.pop();\
/*alert(jsxbox_free$jsx_nb);*/\
return re$jsx_nb=0;\
}
!endif

!if $input_type = rectangle
  !set ooo={straightFirst:false, straightLast:false}
  !set trace='line'
  !set script$jsx_nb=$(script$jsx_nb)\
var pp=[];\
var re$jsx_nb=0;\
JXG.addEvent(document.getElementById('jsxbox$jsx_nb'), 'mousedown', function (e) {\
if (re$jsx_nb<2){\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$jsx_nb.getMousePosition(e), brd$jsx_nb);\
p$jsx_nb[re$jsx_nb] = brd$jsx_nb.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',name:'',fixed:true,strokeColor:'black'});\
if(re$jsx_nb==0){pp = brd$jsx_nb.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,name:'',strokeColor:'black'});\
 li1 = brd$jsx_nb.create('line',[[p$jsx_nb[0].X(),p$jsx_nb[0].Y()],[p$jsx_nb[0].X(),function(){ return pp.Y();}]], $ooo );\
 li2 = brd$jsx_nb.create('line',[[p$jsx_nb[0].X(),function(){ return pp.Y();}],[function(){ return pp.X();},function(){ return pp.Y();}]],$ooo);\
 li3 = brd$jsx_nb.create('line',[[function(){ return pp.X();},function(){ return pp.Y();}],[function(){ return pp.X();},p$jsx_nb[0].Y()]],$ooo);\
 li4 = brd$jsx_nb.create('line',[[function(){ return pp.X();},p$jsx_nb[0].Y()],[p$jsx_nb[0].X(),p$jsx_nb[0].Y()]],$ooo );}\
var c = [Math.round(p$jsx_nb[re$jsx_nb].X()),Math.round(p$jsx_nb[re$jsx_nb].Y())];\
jsxbox_free$jsx_nb.push(c);\
/*alert(jsxbox_free$jsx_nb);*/\
if(re$jsx_nb==1){JXG.removeAllEvents (document.getElementById ('jsxbox$jsx_nb'), 'mousemove', this);}\
re$jsx_nb=re$jsx_nb+1;\
JXG.addEvent(document.getElementById('jsxbox$jsx_nb'),'mousemove', function (e) {\
if(re$jsx_nb==1){\
var coor = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$jsx_nb.getMousePosition(e), brd$jsx_nb);\
pp.moveTo(coor.usrCoords.slice(1));}\
},this);\
}\
}, this);\
function efface$jsx_nb() {\
brd$jsx_nb.removeObject(pp);\
brd$jsx_nb.removeObject(p$jsx_nb);\
brd$jsx_nb.removeObject(li1);\
brd$jsx_nb.removeObject(li2);\
brd$jsx_nb.removeObject(li3);\
brd$jsx_nb.removeObject(li4);\
jsxbox_free$jsx_nb.pop();\
jsxbox_free$jsx_nb.pop();\
return re$jsx_nb=0;\
}
!endif

!if $input_type = polygon
  !set script$jsx_nb=$(script$jsx_nb)\
var lu=[];\
var lo=[];\
var re$jsx_nb=0;\
var jsss$jsx_nb='';\
JXG.addEvent(document.getElementById('jsxbox$jsx_nb'),'mousedown', function (e) {\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$jsx_nb.getMousePosition(e), brd$jsx_nb);\
p$jsx_nb[re$jsx_nb] = brd$jsx_nb.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,strokeColor:'black', name:''});\
var pp = brd$jsx_nb.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,strokeColor:'black', name:'', Opacity:0.5});\
lo[re$jsx_nb] = brd$jsx_nb.create('segment',[p$jsx_nb[re$jsx_nb],pp],{Opacity:0.5});\
if(re$jsx_nb>=1){\
louis$jsx_nb = brd$jsx_nb.create('segment',[p$jsx_nb[re$jsx_nb-1],p$jsx_nb[re$jsx_nb]]);\
lu[re$jsx_nb] = brd$jsx_nb.create('segment',[pp,p$jsx_nb[0]],{Opacity:0.5});\
brd$jsx_nb.removeObject(lo[re$jsx_nb-1]);}\
brd$jsx_nb.removeObject(lu[re$jsx_nb-1]);\
var c = [Math.round(p$jsx_nb[re$jsx_nb].X()),Math.round(p$jsx_nb[re$jsx_nb].Y())];\
jsss$jsx_nb= jsss$jsx_nb+c+';';\
re$jsx_nb=re$jsx_nb+1;\
JXG.addEvent(document.getElementById('jsxbox$jsx_nb'),'mousemove', function (z) {\
var coor = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$jsx_nb.getMousePosition(z), brd$jsx_nb);\
pp.moveTo(coor.usrCoords.slice(1));\
},this);\
JXG.addEvent(document.getElementById('jsxbox$jsx_nb'),'mouseleave', function (y) {\
JXG.removeAllEvents (document.getElementById ('jsxbox$jsx_nb'), 'mousemove', this);\
brd$jsx_nb.removeObject(lu[re$jsx_nb]);\
brd$jsx_nb.removeObject(lo[re$jsx_nb]);\
luca = brd$jsx_nb.create('segment',[p$jsx_nb[re$jsx_nb-1],p$jsx_nb[0]]);\
brd$jsx_nb.removeObject(pp);\
},this);\
}, this);\
function efface$jsx_nb() {\
brd$jsx_nb.removeObject(p$jsx_nb);\
jsss$jsx_nb='';\
/*alert(jsss$jsx_nb);*/\
return re$jsx_nb=0;\
}
!endif

!! Broken Line
!if $input_type = brokenline
  !set script$jsx_nb=$(script$jsx_nb)\
// Segment temporaire\
var temp_seg;\
// Curseur\
var currentPoint;\
var re$jsx_nb=0;\
var jsss$jsx_nb='';\
var jsxbox$jsx_nb = document.getElementById('jsxbox$jsx_nb');\
var tracing=false;\
if (JXG.isTouchDevice()){\
  // Empeche le navigateur de scroller lors d'un touchmove\
  function preventBehavior(e) {e.preventDefault();};\
  jsxbox$jsx_nb.addEventListener("touchmove", preventBehavior, false);\
}\
else {\
  JXG.addEvent(jsxbox$jsx_nb,'mouseleave', termine$jsx_nb, this);\
}\
brd$jsx_nb.on('down', function (pointer_pos) {\
  startTrace$jsx_nb(pointer_pos);\
});\
brd$jsx_nb.on('up', function (pointer_pos) {\
  if(tracing){\
    // "0" give position of the first finger (on touch devices).\
    var coor = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$jsx_nb.getMousePosition(pointer_pos, 0), brd$jsx_nb);\
    var sliced_coor = coor.usrCoords.slice(1)\
    // Déplace le curseur (ce qui modifie le segment)\
    currentPoint.moveTo(sliced_coor);\
    currentPoint.size(8);\
    // ajoute un nouveau point noir\
    p$jsx_nb[re$jsx_nb-1] = brd$jsx_nb.create('point', sliced_coor, {face:'+', size:'8', fixed:true, strokeColor:'black', name:'', Opacity:0.5});\
    if(re$jsx_nb>1){\
      // trace un segment définitif entre le precedent point et le nouveau\
      louis$jsx_nb = brd$jsx_nb.create('segment',[p$jsx_nb[re$jsx_nb-2],p$jsx_nb[re$jsx_nb-1]]);\
      // retire le segment temporaire\
      brd$jsx_nb.removeObject(temp_seg);\
    }\
    // trace un segment temporaire entre le nouveau point et le curseur\
    temp_seg = brd$jsx_nb.create('segment', [p$jsx_nb[re$jsx_nb-1], currentPoint], {strokeColor:'magenta', Opacity:0.5});\
    var c = [Math.round(p$jsx_nb[re$jsx_nb-1].X()),Math.round(p$jsx_nb[re$jsx_nb-1].Y())];\
    jsss$jsx_nb= jsss$jsx_nb+c+';';\
  }\
  tracing=false;\
});\
brd$jsx_nb.on('move', function (pointer_pos) {\
  if(re$jsx_nb>0){\
    // Deplace le curseur (ce qui modifie le segment)\
    var coor = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$jsx_nb.getMousePosition(pointer_pos, 0), brd$jsx_nb);\
    var sliced_coor = coor.usrCoords.slice(1);\
    currentPoint.moveTo(coor.usrCoords.slice(1));\
  }\
});\
function startTrace$jsx_nb(pointer_pos) {\
  if(!tracing){\
    var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$jsx_nb.getMousePosition(pointer_pos, 0), brd$jsx_nb);\
    var sliced_coords = coords.usrCoords.slice(1);\
    if(re$jsx_nb==0){\
      // Crée un curseur\
      currentPoint = brd$jsx_nb.create('point', sliced_coords, {face:'+', size:'64',fixed:true,strokeColor:'red', name:'', Opacity:0.5});\
    }\
    else{\
      // Déplace le curseur et le rend plus gros (plus visible sous les doigts sur les interfaces tactiles)\
      currentPoint.size(64);\
      currentPoint.moveTo(sliced_coords);\
    }\
    tracing=true;\
    re$jsx_nb=re$jsx_nb+1;\
  }\
}\
function termine$jsx_nb() {\
  // Lorsque la souris sort du champ, on arrete le dessin.\
  brd$jsx_nb.removeObject(temp_seg);\
  if(tracing){currentPoint.moveTo([0, 0]);}\
  tracing=false;\
}\
function efface$jsx_nb() {\
  brd$jsx_nb.clearTraces();\
  brd$jsx_nb = init_jsx_brd$jsx_nb();\
  jsss$jsx_nb='';\
  re$jsx_nb=0;\
  tracing=false;\
}

!endif

!if $input_type = curve
  !set script$jsx_nb=$(script$jsx_nb)\
var pp=[];\
var re$jsx_nb=0;\
var ree=0;\
var rrr$jsx_nb=0;\
var aa$jsx_nb='';\
var tt=0;\
var jj$jsx_nb=0;\
JXG.addEvent(document.getElementById('jsxbox$jsx_nb'),'click', function (e) {\
var coords = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$jsx_nb.getMousePosition(e), brd$jsx_nb);\
p$jsx_nb[re$jsx_nb+tt] = brd$jsx_nb.create('point', coords.usrCoords.slice(1),{face:'+', size:'8',fixed:true,strokeColor:'black', name:''});\
c = [Math.round(p$jsx_nb[re$jsx_nb+tt].X()),Math.round(p$jsx_nb[re$jsx_nb+tt].Y())];\
aa$jsx_nb=aa$jsx_nb+c+',';\
re$jsx_nb=re$jsx_nb+1;\
JXG.addEvent(document.getElementById('jsxbox$jsx_nb'),'mousemove', function (z) {\
var coor = new JXG.Coords(JXG.COORDS_BY_SCREEN, brd$jsx_nb.getMousePosition(z), brd$jsx_nb);\
pp[rrr$jsx_nb+jj$jsx_nb] = brd$jsx_nb.create('point', coor.usrCoords.slice(1),{face:'+',size:'1',Color:'blue',name:''});\
d = [Math.round(pp[rrr$jsx_nb+jj$jsx_nb].X()),Math.round(pp[rrr$jsx_nb+jj$jsx_nb].Y())];\
aa$jsx_nb=aa$jsx_nb+d+',';\
/*brd$jsx_nb.create('segment',[p$jsx_nb[0],pp[0]],{Color:'red'});*/\
if(rrr$jsx_nb>0){brd$jsx_nb.create('segment',[pp[rrr$jsx_nb-1+jj$jsx_nb],pp[rrr$jsx_nb+jj$jsx_nb]],{Color:'yellow'});}\
rrr$jsx_nb=rrr$jsx_nb+1;\
if(rrr$jsx_nb>$wims_bound || jj$jsx_nb+rrr$jsx_nb>$wims_bound){JXG.removeAllEvents (document.getElementById ('jsxbox$jsx_nb'), 'mousemove', this);\
alert('$name_alert');\
efface$jsx_nb();}\
},this);\
if(re$jsx_nb%2==0){JXG.removeAllEvents (document.getElementById ('jsxbox$jsx_nb'), 'mousemove', this);\
aa$jsx_nb=aa$jsx_nb.substr(0,aa$jsx_nb.length-1);\
aa$jsx_nb=aa$jsx_nb+';';\
tt=tt+re$jsx_nb;\
jj$jsx_nb=jj$jsx_nb+rrr$jsx_nb;\
/*alert('re$jsx_nb='+re$jsx_nb+'tt='+tt);\
alert(aa$jsx_nb);*/\
re$jsx_nb=0;\
rrr$jsx_nb=0;}\
}, this);\
function efface$jsx_nb() {\
brd$jsx_nb.removeObject(p$jsx_nb);\
brd$jsx_nb.removeObject(pp);\
JXG.removeAllEvents (document.getElementById ('jsxbox$jsx_nb'), 'mousemove', this);\
aa$jsx_nb='';\
re$jsx_nb=0;\
rrr$jsx_nb=0;\
jj$jsx_nb=0;\
}
!endif

!readproc slib/geo2D/jsxgraph jsxbox$jsx_nb,$jsx_xsize x $jsx_ysize,$(script$jsx_nb)

$slib_out
<script type="text/javascript">
/*<![CDATA[*/
!if $input_type iswordof points bound
  var capture$jsx_nb = function()
    {document.getElementById('$jsx_reply').value='free='+jsxbox_free$jsx_nb +'';}
!endif
!if $input_type iswordof line sline segment vector rectangle
  var capture$jsx_nb = function()
    {if(re$jsx_nb==2){document.getElementById('$jsx_reply').value='free='+jsxbox_free$jsx_nb +'';}}
!endif
!if $input_type iswordof circle
  var capture$jsx_nb = function() {
    document.getElementById('$jsx_reply').value='free=' + [Math.round(p$jsx_nb[0].X()),
                                                           Math.round(p$jsx_nb[0].Y()),
                                                           Math.round(p$jsx_nb[0].Dist(p$jsx_nb[1]))] +'';
  }
!endif
!if $input_type iswordof polygon brokenline
  var capture$jsx_nb = function()
    {document.getElementById('$jsx_reply').value='free=' + jsss$jsx_nb +'';}
!endif
!if $input_type iswordof curve
  var capture$jsx_nb = function()
    {document.getElementById('$jsx_reply').value='free=' + aa$jsx_nb;}
!endif
/*]]>*/
</script>
