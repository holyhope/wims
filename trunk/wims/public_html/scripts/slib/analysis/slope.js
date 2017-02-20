slib_script=var $brd = JXG.JSXGraph.initBoard('$jxgbox', {axis:true, boundingbox:[-4,4,4,-4],showCopyright:false});\
  JXG.JSXGraph.freeBoard($brd);\
var xinit$slib_number = parseFloat('$slib_xinit');\
var yinit$slib_number = parseFloat('$slib_yinit');\
var xmin$slib_number = parseFloat('$slib_xmin');\
var xmax$slib_number = parseFloat('$slib_xmax');\
var xsep$slib_number = parseFloat('$slib_xsep');\
var ymin$slib_number = parseFloat('$slib_ymin');\
var ymax$slib_number = parseFloat('$slib_ymax');\
var ysep$slib_number = parseFloat('$slib_ysep');\
var seglength$slib_number = parseFloat('$slib_seglength');\
var N = 10; var P$slib_number;\
  $brd = JXG.JSXGraph.initBoard('$jxgbox', {axis:true, boundingbox:[xmin$slib_number,ymax$slib_number,xmax$slib_number,ymin$slib_number]});\
    /*CURSOR*/\
  var txt1 = $brd.jc.snippet('$slib_f1',true,'x,y');\
  var txt2 = $brd.jc.snippet('$slib_f2',true,'x,y');\
/*  $brd.update();*/\
  $brd.suspendUpdate();\
  var f1_$slib_number = function (x, yy){ return [txt1(yy[0], yy[1])];}\
  var f2_$slib_number = function (x, yy){ return [txt2(yy[0], yy[1])];}\
  var f_$slib_number  = function (t, yy){ return [txt1(yy[0], yy[1]), txt2(yy[0], yy[1])]}\
  slopefield(f1_$slib_number,f2_$slib_number,xmin$slib_number,xmax$slib_number,xsep$slib_number,ymin$slib_number,ymax$slib_number,ysep$slib_number,seglength$slib_number);\
\
   var P$slib_number = $brd.create('point',[xinit$slib_number,yinit$slib_number], {name:'(x_0,y_0)'});\
   plotFunction$slib_number();\
\
  $brd.unsuspendUpdate();\
\
function slopefield(f1,f2,xmin,xmax,xsep,ymin,ymax,ysep,seglength) {\
   var xval, yval;\
   var xnum = Math.ceil((xmax-xmin)/xsep);\
   var ynum = Math.ceil((ymax-ymin)/ysep);\
   var echelle=(ymax-ymin)/(xmax-xmin);\
   for (var i=0;i<=xnum;i++) {\
     xval = xmin + i*xsep;\
     for (var j=0;j<=ynum;j++) {\
       yval = ymin + j*ysep;\
       var f1val=echelle*f1(0,[xval,yval])[0];\
       var f2val=f2(0,[xval,yval])[0];\
       var norm=Math.sqrt(f1val*f1val+ f2val*f2val);\
       $brd.create('arrow',[\
       [xval-0.5*seglength*f1val/norm, yval-0.5*seglength*f2val/norm],\
       [xval+0.5*seglength*f1val/norm, yval+0.5*seglength*f2val/norm]\
       ],\
       {strokeWidth:1, dash:0, fixed:true, strokeColor:'$(slib_color[1])'});\
     };\
   };\
};\
function solutiondata$slib_number() {\
   return JXG.Math.Numerics.rungeKutta('heun', [P$slib_number.X(),P$slib_number.Y()], [P$slib_number.X(), P$slib_number.Y()+N], 500, f_$slib_number);\
};\
\
function plotFunction$slib_number() {\
    var g$slib_number = $brd.create('curve', [[0],[0]], {strokeColor:'$(slib_color[2])', strokeWidth:'2px'});\
    g$slib_number.updateDataArray = function() {\
        var data = solutiondata$slib_number();\
        var h = N/200;\
        this.dataX = [];\
        this.dataY = [];\
        for(var i=0; i<data.length; i++) {\
            this.dataX[i] = data[i][0];\
            this.dataY[i] = data[i][1];\
        }\
    };\
};\
