#include "canvasdraw.h"

/* not used ?? */
/*
char *data2js_array(int data[],int len);
char *xy2js_array(int xy[],int len);
*/
void add_js_multidraw(FILE *js_include_file,int canvas_root_id,char *draw_types,char *button_style){
/*

just for the javascript switches():
point = 0	points =1
circle = 2 	circles = 3
line =4 	lines = 5
segment = 6 	segments = 7
arrow = 8 	arrows = 9
triangle = 10 	triangles = 11
polygon = 12
text = 13
rect = 14
rects =15
poly = 16
polys = 17
paralelogram = 18
28/6/2015:
the next js-code block (parsing/scanning the multidraw objects array) is -for now- generic, 
e.g. not responsive to the actual draw_types used.

TODO: examine/parse the *draw_Types and make the js-code accordingly (e.g. specific and not generic)
*/

fprintf(js_include_file,"\n<!-- begin multidraw  -->\n\
var canvas_userdraw = create_canvas%d(999,xsize,ysize);\
var context_userdraw = canvas_userdraw.getContext(\"2d\");\
var click_cnt = 0;\
if(wims_status != \"done\"){\
 canvas_div.addEventListener('mousedown',user_draw,false);\
 canvas_div.addEventListener('mousemove',user_drag,false);\
 canvas_div.addEventListener('touchstart'  , function(e) { e.preventDefault(); user_draw(e.changedTouches[0]);},false);\
 canvas_div.addEventListener( 'touchmove'  , function(e) { e.preventDefault(); user_drag(e.changedTouches[0]);},false);\
};\
clear_draw_area%d = function(type,name){\
 if(confirm(\"delete \"+multilabel[name]+\" ? \")){\
  switch(type){\
   case 0: context_points.clearRect(0,0,xsize,ysize);points_x = [];points_y = [];break;\
   case 1: points_x.pop();points_y.pop();draw_points();break;\
   case 2: context_circles.clearRect(0,0,xsize,ysize);circles_x = [];circles_y = []; multi_radius = [];break;\
   case 3: circles_x.pop();circles_y.pop(); multi_radius.pop();draw_circles();break;\
   case 4: context_lines.clearRect(0,0,xsize,ysize);lines_x = [];lines_y = [];break;\
   case 5: lines_x.pop();lines_y.pop();lines_x.pop();lines_y.pop();draw_lines();break;\
   case 6: context_segments.clearRect(0,0,xsize,ysize);segments_x = [];segments_y = [];break;\
   case 7: segments_x.pop();segments_y.pop();segments_x.pop();segments_y.pop();draw_segments();break;\
   case 8: context_arrows.clearRect(0,0,xsize,ysize);arrows_x = [];arrows_y = [];break;\
   case 9: arrows_x.pop();arrows_y.pop();arrows_x.pop();arrows_y.pop();draw_arrows();break;\
   case 10:context_triangles.clearRect(0,0,xsize,ysize); triangles_x = [];triangles_y = [];break;\
   case 11:for(var p=0;p<3;p++){triangles_x.pop();triangles_y.pop();};draw_triangles();break;\
   case 12:context_closedpoly.clearRect(0,0,xsize,ysize);closedpoly_x = [];closedpoly_y = [];break;\
   case 13:context_text.clearRect(0,0,xsize,ysize);text_x.pop();text_y.pop();text_abc.pop();draw_text();break;\
   case 14:context_rects.clearRect(0,0,xsize,ysize);rects_x = [];rects_y = [];break;\
   case 15:rects_x.pop();rects_y.pop();rects_x.pop();rects_y.pop();draw_rects();break;\
   case 16:context_polys.clearRect(0,0,xsize,ysize); polys_x = [];polys_y = [];break;\
   case 17:for(var p=0;p<polynum;p++){polys_x.pop();polys_y.pop();};draw_polys();break;\
   case 18:context_parallelogram.clearRect(0,0,xsize,ysize); parallelogram_x = [];parallelogram_y = [];break;\
   case 19:for(var p = 0; p < 4;p++){ parallelogram_x.pop();parallelogram_y.pop();};draw_parallelogram();break;\
   default:break;\
  };\
 };\
};\
function user_draw(evt){\
 var canvas_rect = canvas_userdraw.getBoundingClientRect();\
 var y = evt.clientY - canvas_rect.top;\
 var x = evt.clientX - canvas_rect.left;\
 switch(userdraw_primitive){\
  case 0: points(x,y,0,0);break;\
  case 1: points(x,y,0,1);break;\
  case 2: circles(x,y,0,0);break;\
  case 3: circles(x,y,0,1);break;\
  case 4: lines(x,y,0,0);break;\
  case 5: lines(x,y,0,1);break;\
  case 6: segments(x,y,0,0);break;\
  case 7: segments(x,y,0,1);break;\
  case 8: arrows(x,y,0,0);break;\
  case 9: arrows(x,y,0,1);break;\
  case 10: triangles(x,y,0,0);break;\
  case 11: triangles(x,y,0,1);break;\
  case 12: closedpoly(x,y,0,0);break;\
  case 13: text(x,y,0,1);break;\
  case 14: rects(x,y,0,0);break;\
  case 15: rects(x,y,0,1);break;\
  case 16: polys(x,y,0,0);break;\
  case 17: polys(x,y,0,1);break;\
  case 18: parallelogram(x,y,0,0);break;\
  case 19: parallelogram(x,y,0,1);break;\
  default:break;\
 };\
};\
function user_drag(evt){\
 var canvas_rect = canvas_userdraw.getBoundingClientRect();\
 var y = evt.clientY - canvas_rect.top;\
 var x = evt.clientX - canvas_rect.left;\
 switch(userdraw_primitive){\
  case 0: break;\
  case 1: break;\
  case 2: circles(x,y,1,0);break;\
  case 3: circles(x,y,1,1);break;\
  case 4: lines(x,y,1,0);break;\
  case 5: lines(x,y,1,1);break;\
  case 6: segments(x,y,1,0);break;\
  case 7: segments(x,y,1,1);break;\
  case 8: arrows(x,y,1,0);break;\
  case 9: arrows(x,y,1,1);break;\
  case 10: triangles(x,y,1,0);break;\
  case 11: triangles(x,y,1,1);break;\
  case 12: closedpoly(x,y,1,0);break;\
  case 13: break;\
  case 14: rects(x,y,1,0);break;\
  case 15: rects(x,y,1,1);break;\
  case 16: polys(x,y,1,0);break;\
  case 17: polys(x,y,1,1);break;\
  case 18: parallelogram(x,y,1,0);break;\
  case 19: parallelogram(x,y,1,1);break;\
  default:break;\
 };\
};\
var draw_things = [\"%s\"];\
var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
var inner_html=\"\";\
var button_style = \"%s\";\
var id_x;\
var id_y;\
var id_r;\
if( typeof(multilabel[multilabel.length - 1 ]) === 'undefined' ){multilabel[multilabel.length - 1] = 'stop drawing';};\
for(var p = 0;p < draw_things.length;p++){\
 var desc;\
 id_r = 0;\
 if( multistrokeopacity[p] > 1 ){ multistrokeopacity[p] = (0.0039215*multistrokeopacity[p]).toFixed(2); };\
 if( multifillopacity[p] > 1 ){ multifillopacity[p] =  (0.0039215*multifillopacity[p]).toFixed(2); };\
 if( draw_things[p] == 'point' || draw_things[p] == 'points' ){\
  var canvas_points = create_canvas%d(1000,xsize,ysize);\
  var context_points = canvas_points.getContext(\"2d\");\
  context_points.strokeStyle = \"rgba(\"+multistrokecolors[p]+\",\"+multistrokeopacity[p]+\")\";\
  context_points.fillStyle = context_points.strokeStyle;\
  context_points.lineWidth = multilinewidth[p];\
  if(multilinewidth[p]%%2 == 1){ context_points.translate(0.5,0.5);};\
  var points_x = new Array();var points_y = new Array();\
  var points_snap = multisnaptogrid[p];\
  if(draw_things[p] == 'point' ){desc = 0;}else{desc = 1;};\
  id_x = 'input_points_x';id_y = 'input_points_y';\
 }\
 else\
 {\
  if( draw_things[p] == 'circle' || draw_things[p] == 'circles' ){\
   var canvas_circles = create_canvas%d(1001,xsize,ysize);\
   var context_circles = canvas_circles.getContext(\"2d\");\
   context_circles.lineWidth = multilinewidth[p];\
   if(multilinewidth[p]%%2 == 1){ context_circles.translate(0.5,0.5);};\
   context_circles.strokeStyle = \"rgba(\"+multistrokecolors[p]+\",\"+multistrokeopacity[p]+\")\";\
   if(multifill[p] == '1' ){ context_circles.fillStyle = \"rgba(\"+multifillcolors[p]+\",\"+multifillopacity[p]+\")\";}else{context_circles.fillStyle = \"rgba( 255,255,255,0)\"; };\
   if(multidash[p] == '1' ){ if( context_circles.setLineDash ){context_circles.setLineDash([2,4]);}else{if(context_circles.mozDash){context_circles.mozDash = [2,4]};};};\
   var circles_x = new Array();var circles_y = new Array();var multi_radius = new Array();\
   var circles_snap = multisnaptogrid[p];\
   if( draw_things[p] == 'circle' ){desc = 2;}else{desc = 3;};\
   id_x = 'input_circles_x';id_y = 'input_circles_y';id_r = 'input_circles_r';\
  }\
  else\
  {\
   if( draw_things[p] == 'line' || draw_things[p] == 'lines' ){\
    var canvas_lines = create_canvas%d(1002,xsize,ysize);\
    var context_lines = canvas_lines.getContext(\"2d\");\
    context_lines.lineWidth = multilinewidth[p];\
    if(multilinewidth[p]%%2 == 1){ context_lines.translate(0.5,0.5);};\
    context_lines.strokeStyle = \"rgba(\"+multistrokecolors[p]+\",\"+multistrokeopacity[p]+\")\";\
    if(multidash[p] == '1' ){ if( context_lines.setLineDash ){context_lines.setLineDash([2,4]);}else{if(context_lines.mozDash){context_lines.mozDash = [2,4]};};};\
    var lines_x = new Array();var lines_y = new Array();\
    var lines_snap = multisnaptogrid[p];\
    if(draw_things[p] == 'line' ){desc = 4;}else{desc = 5;};\
    id_x = 'input_lines_x';id_y = 'input_lines_y';\
   }\
   else\
   {\
    if( draw_things[p] == 'segment' || draw_things[p] == 'segments' ){\
     var canvas_segments = create_canvas%d(1003,xsize,ysize);\
     var context_segments = canvas_segments.getContext(\"2d\");\
     context_segments.lineWidth = multilinewidth[p];\
     if(multilinewidth[p]%%2 == 1){ context_segments.translate(0.5,0.5);};\
     context_segments.strokeStyle = \"rgba(\"+multistrokecolors[p]+\",\"+multistrokeopacity[p]+\")\";\
     if(multidash[p] == '1' ){ if( context_segments.setLineDash ){context_segments.setLineDash([2,4]);}else{if(context_segments.mozDash){context_segments.mozDash = [2,4]};};};\
     var segments_x = new Array();var segments_y = new Array();\
     var segments_snap = multisnaptogrid[p];\
     if( draw_things[p] == 'segment' ){desc = 6;}else{ desc = 7;};\
     id_x = 'input_segments_x';id_y = 'input_segments_y';\
    }\
    else\
    {\
     if( draw_things[p] == 'arrow' || draw_things[p] == 'arrows' ){\
      var canvas_arrows = create_canvas%d(1004,xsize,ysize);\
      var context_arrows =  canvas_arrows.getContext(\"2d\");\
      context_arrows.lineWidth = multilinewidth[p];\
      if(multilinewidth[p]%%2 == 1){ context_arrows.translate(0.5,0.5);};\
      context_arrows.lineCap = \"round\";\
      context_arrows.strokeStyle = \"rgba(\"+multistrokecolors[p]+\",\"+multistrokeopacity[p]+\")\";\
      context_arrows.fillStyle = context_arrows.strokeStyle;\
      if(multidash[p] == '1' ){ if( context_arrows.setLineDash ){context_arrows.setLineDash([2,4]);}else{if(context_arrows.mozDash){context_arrows.mozDash = [2,4]};};};\
      var arrows_x = new Array();var arrows_y = new Array();\
      var arrows_snap = multisnaptogrid[p];\
      if( draw_things[p] == 'arrow' ){desc = 8;}else{desc = 9;};\
      id_x = 'input_arrows_x';id_y = 'input_arrows_y';\
     }\
     else\
     {\
      if( draw_things[p] == 'rect' || draw_things[p] == 'rects' ){\
       var canvas_rects = create_canvas%d(1008,xsize,ysize);\
       var context_rects = canvas_rects.getContext(\"2d\");\
       context_rects.lineWidth = multilinewidth[p];\
       if(multilinewidth[p]%%2 == 1){ context_rects.translate(0.5,0.5);};\
       context_rects.strokeStyle = \"rgba(\"+multistrokecolors[p]+\",\"+multistrokeopacity[p]+\")\";\
       if(multidash[p] == '1' ){ if( context_rects.setlineDash ){context_rects.setlineDash([2,4]);}else{if(context_rects.mozDash){context_rects.mozDash = [2,4]};};};\
       if(multifill[p] == '1' ){ context_rects.fillStyle = \"rgba(\"+multifillcolors[p]+\",\"+multifillopacity[p]+\")\";}else{context_rects.fillStyle = \"rgba( 255,255,255,0)\"; };\
       var rects_x = new Array();var rects_y = new Array();\
       var rects_snap = multisnaptogrid[p];\
       if(draw_things[p] == 'rect' ){desc = 14;}else{desc = 15;};\
       id_x = 'input_rects_x';id_y = 'input_rects_y';\
      }\
      else\
      {\
       if( draw_things[p] == 'closedpoly'){\
        var canvas_closedpoly = create_canvas%d(1006,xsize,ysize);\
        var context_closedpoly =  canvas_closedpoly.getContext(\"2d\");\
        context_closedpoly.lineCap = \"round\";\
        context_closedpoly.lineWidth = multilinewidth[p];\
        if(multilinewidth[p]%%2 == 1){ context_closedpoly.translate(0.5,0.5);};\
        context_closedpoly.lineCap = \"round\";\
        context_closedpoly.strokeStyle = \"rgba(\"+multistrokecolors[p]+\",\"+multistrokeopacity[p]+\")\";\
        if(multifill[p] == '1' ){ context_closedpoly.fillStyle = \"rgba(\"+multifillcolors[p]+\",\"+multifillopacity[p]+\")\";}else{context_closedpoly.fillStyle = \"rgba( 255,255,255,0)\"; };\
        if(multidash[p] == '1' ){ if( context_closedpoly.setLineDash ){context_closedpoly.setLineDash([2,4]);}else{if(context_closedpoly.mozDash){context_closedpoly.mozDash = [2,4]};};};\
        var closedpoly_x = new Array();var closedpoly_y = new Array();\
        var closedpoly_snap = multisnaptogrid[p];\
        desc = 12;\
        id_x = 'input_closedpoly_x';id_y = 'input_closedpoly_y';\
       }\
       else\
       {\
        if( draw_things[p] == 'triangle' || draw_things[p] == 'triangles' ){\
         var canvas_triangles = create_canvas%d(1005,xsize,ysize);\
         var context_triangles = canvas_triangles.getContext(\"2d\");\
         context_triangles.lineCap = \"round\";\
         context_triangles.lineWidth = multilinewidth[p];\
         if(multilinewidth[p]%%2 == 1){ context_triangles.translate(0.5,0.5);};\
         context_triangles.strokeStyle = \"rgba(\"+multistrokecolors[p]+\",\"+multistrokeopacity[p]+\")\";\
         if(multifill[p] == '1' ){ context_triangles.fillStyle = \"rgba(\"+multifillcolors[p]+\",\"+multifillopacity[p]+\")\";}else{context_triangles.fillStyle = \"rgba( 255,255,255,0)\"; };\
         if(multidash[p] == '1' ){ if( context_triangles.setLineDash ){context_triangles.setLineDash([2,4]);}else{if(context_triangles.mozDash){context_triangles.mozDash = [2,4]};};};\
         var triangles_x = new Array();var triangles_y = new Array();\
         var triangles_snap = multisnaptogrid[p];\
         if( draw_things[p] == 'triangle'){desc = 10;};\
         if( draw_things[p] == 'triangles'){desc = 11;};\
         id_x = 'input_triangles_x';id_y = 'input_triangles_y';id_r = 'input_triangles_r';\
        }\
        else\
        {\
         if( draw_things[p].indexOf('para') != -1 ){\
          var canvas_parallelogram = create_canvas%d(1010,xsize,ysize);\
          var context_parallelogram = canvas_parallelogram.getContext(\"2d\");\
          context_parallelogram.lineCap = \"round\";\
          context_parallelogram.lineWidth = multilinewidth[p];\
          if(multilinewidth[p]%%2 == 1){ context_parallelogram.translate(0.5,0.5);};\
          context_parallelogram.strokeStyle = \"rgba(\"+multistrokecolors[p]+\",\"+multistrokeopacity[p]+\")\";\
          if(multifill[p] == '1' ){ context_parallelogram.fillStyle = \"rgba(\"+multifillcolors[p]+\",\"+multifillopacity[p]+\")\";}else{context_parallelogram.fillStyle = \"rgba( 255,255,255,0)\"; };\
          if(multidash[p] == '1' ){ if( context_parallelogram.setLineDash ){context_parallelogram.setLineDash([2,4]);}else{if(context_parallelogram.mozDash){context_parallelogram.mozDash = [2,4]};};};\
          var parallelogram_x = new Array();var parallelogram_y = new Array();\
          var parallelogram_snap = multisnaptogrid[p];\
          if( draw_things[p] == 'parallelogram'){multiuserinput[p] =  0;desc = 18;};\
          if( draw_things[p] == 'parallelograms'){multiuserinput[p] =  0;desc = 19;};\
          id_x = 'input_parallelogram_x';id_y = 'input_parallelogram_y';id_r = 'input_parallelogram_r';\
         }\
         else\
         {\
          if( draw_things[p].indexOf('poly') != -1 ){\
           var canvas_polys = create_canvas%d(1009,xsize,ysize);\
           var context_polys = canvas_polys.getContext(\"2d\");\
           context_polys.lineCap = \"round\";\
           context_polys.lineWidth = multilinewidth[p];\
           if(multilinewidth[p]%%2 == 1){ context_polys.translate(0.5,0.5);};\
           context_polys.strokeStyle = \"rgba(\"+multistrokecolors[p]+\",\"+multistrokeopacity[p]+\")\";\
           if(multifill[p] == '1' ){ context_polys.fillStyle = \"rgba(\"+multifillcolors[p]+\",\"+multifillopacity[p]+\")\";}else{context_polys.fillStyle = \"rgba( 255,255,255,0)\"; };\
           if(multidash[p] == '1' ){ if( context_polys.setLineDash ){context_polys.setLineDash([2,4]);}else{if(context_polys.mozDash){context_polys.mozDash = [2,4]};};};\
           var polys_x = new Array();var polys_y = new Array();\
           var polys_snap = multisnaptogrid[p];\
           if( draw_things[p].indexOf('polys') != -1){desc = 17;}else{desc = 16;}\
           multiuserinput[p] = 0;\
           id_x = 'input_polys_x';id_y = 'input_polys_y';id_r = 'input_polys_r';\
          }\
          else\
          {\
           if( draw_things[p] == 'text' ){\
            var canvas_text = create_canvas%d(1007,xsize,ysize);\
            var context_text = canvas_text.getContext(\"2d\");\
            context_text.font = multifont_family;\
            context_text.fillStyle = \"rgba(\"+multifont_color+\",\"+multistrokeopacity[p]+\")\";\
            var text_snap = multisnaptogrid[p];\
            var text_x = new Array;var text_y = new Array; var text_abc = new Array();\
            multiuserinput[p] = 1;\
            id_x = 'input_text_x';id_y = 'input_text_y';id_r = 'input_text_r';\
            desc = 13;\
           };\
          };\
         };\
        };\
       };\
      };\
     };\
    };\
   };\
  };\
 };\
 inner_html+=\"<tr style='background-color:rgba(\"+multistrokecolors[p]+\",0.4)'><td><input type='button' id='canvasdraw_\"+draw_things[p]+\"' style=\"+button_style+\" onclick='javascript:userdraw_primitive=\"+desc+\";click_cnt = 0;' value='\"+multilabel[p]+\"' /></td><td><input type='button' style='\"+button_style+\"' onclick='javascript:clear_draw_area%d(\"+desc+\",\"+p+\");' value='delete' /></td>\";\
 if(multiuserinput[p] == '1'){ \
  if(desc == 0 || desc == 1 ){\
   inner_html+=\"<td><b>(</b><input type='text' size='5' value='' id='\"+id_x+\"' style='\"+button_style+\"' /><b>:</b> <input type='text' size='5' value='' id='\"+id_y+\"' style='\"+button_style+\"' /> <b>)</b></td>\";\
  }\
  else\
  {\
   if(desc == 2 || desc == 3){\
    inner_html+=\"<td><b>M&nbsp;:&nbsp;(<input type='text' size='5' value='' id='\"+id_x+\"' style='\"+button_style+\"' /> : <input type='text' size='5' value='' id='\"+id_y+\"' style='\"+button_style+\"' />)&nbsp;&nbsp;R</b>&nbsp;:&nbsp;<input type='text' size='3' value='' id='\"+id_r+\"' style='\"+button_style+\"' /></b></td>\";\
   }\
   else\
   {\
    if(desc >3 && desc <10 || desc == 14 || desc == 15){\
     inner_html+=\"<td><b>(</b><input type='text' size='5' value='x1 : y1' id='\"+id_x+\"' style='\"+button_style+\";text-align:center;' /><b>) --- (</b> <input type='text' size='5' value='x2 : y2' id='\"+id_y+\"' style='\"+button_style+\";text-align:center;' /> <b>)</b></td>\";\
    }\
    else\
    {\
     if( desc == 10 || desc == 11){\
      inner_html+=\"<td><b>(<input type='text' size='5' value='x1 : y1' id='\"+id_x+\"' style='\"+button_style+\"' />) -- (<input type='text' size='5' value='x2 : y2' id='\"+id_y+\"' style='\"+button_style+\"' />) -- (<input type='text' size='5' value='x3 : y3' id='\"+id_r+\"' style='\"+button_style+\"' />)</b></td>\";\
     }\
     else\
     {\
      if( desc == 12 || desc == 16 || desc == 17 || desc == 18 || desc == 19){\
       inner_html+=\"<td><b>(<input type='text' size='8' value='x1,x2...x_n' id='\"+id_x+\"' style='\"+button_style+\"' /> ---- <input type='text' size='8' value='y1,y2...y_n' id='\"+id_y+\"' style='\"+button_style+\"' />)</b></td>\";\
      }\
      else\
      {\
       if( desc == 13 ){\
        inner_html+=\"<td><b>(<input type='text' size='4' value='x' id='\"+id_x+\"' style='\"+button_style+\"' /> - <input type='text' size='4' value='y' id='\"+id_y+\"' style='\"+button_style+\"' />)</b><input type='text' size='4' value='' id='\"+id_r+\"' style='\"+button_style+\"' /></td>\";\
       };\
      };\
     };\
    };\
   };\
  };\
  inner_html+=\"<td><input type='button' id='canvasdraw_ok_button'  style='\"+button_style+\"' onclick='javascript:update_draw_area%d(\"+desc+\",\"+id_x+\",\"+id_y+\",\"+id_r+\")' value='OK'/ ></td></tr>\";\
 }\
 else\
 {\
  inner_html+\"<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td></tr>\";\
 };\
};\
if( wims_status != 'done' ){\
 tooltip_div.innerHTML = \"<table style=''>\"+inner_html+\"<tr><td>&nbsp;</td><td><input type='button' id='canvasdraw_stop_drawing' style='\"+button_style+\"' value='\"+multilabel[multilabel.length - 1]+\"' onclick='javascript:userdraw_primitive=null;' /></td><td>&nbsp;</td></tr></table>\";\
};\
function x_snap_check(x,snap){\
 if( snap == 1 || snap == 2 ){\
  return snap_to_x(x);\
 };\
 return x;\
};\
function y_snap_check(y,snap){\
 if( snap == 1 || snap == 3 ){\
  return snap_to_y(y);\
 };\
 return y;\
};\
function coord_split(coord){if(coord.indexOf(':') > 0 ){return coord.split(':');}else{if(coord.indexOf(';') > 0 ){return coord.split(';');}else{if(coord.indexOf(',') > 0 ){return coord.split(',');}else{alert(coord+'--> X : Y ');return;};};};};\
function scale_xy(type,xy){var tmp_xmin = xmin;var tmp_xmax = xmax;var tmp_ymin = ymin;var tmp_ymax = ymax;xmin=zoom_xy[0];xmax=zoom_xy[1];ymin=zoom_xy[2];ymax=zoom_xy[3];if(type == 1 ){for(var p=0;p<xy.length;p++){xy[p] = px2x(xy[p]);};}else{for(var p=0;p<xy.length;p++){xy[p] = px2y(xy[p]);};};xmin = tmp_xmin;ymin = tmp_ymin;xmax = tmp_xmax;ymax = tmp_ymax;if(type == 1){for(var p=0;p<xy.length;p++){xy[p] = x2px(xy[p]);}}else{for(var p=0;p<xy.length;p++){xy[p] = y2px(xy[p]);};};return xy;};\
function scale_multi_radius(r){for(var p = 0 ; p < r.length;p++ ){r[p] = zoom_xy[0]/xmin*r[p];};return r;};\
redraw_all%d = function(){\
if( points_x && points_x.length > 0 ){points_x = scale_xy(1,points_x);points_y = scale_xy(1,points_y);draw_points();};\
if( circles_x && circles_x.length > 0 ){circles_x = scale_xy(1,circles_x);circles_y = scale_xy(1,circles_y);multi_radius = scale_multi_radius(multi_radius);draw_circles();};\n\
if( segments_x && segments_x.length > 0 ){segments_x = scale_xy(1,segments_x);segments_y = scale_xy(1,segments_y);draw_segments();};\
if( arrows_x && arrows_x.length > 0 ){arrows_x = scale_xy(1,arrows_x);arrows_y = scale_xy(2,arrows_y);draw_arrows();};\
if( lines_x && lines_x.length > 0 ){lines_x = scale_xy(1,lines_x);lines_y = scale_xy(2,lines_y);draw_lines();};\
if( triangles_x && triangles_x.length > 0 ){triangles_x = scale_xy(1,triangles_x);triangles_y = scale_xy(2,triangles_y);draw_triangles();};\
if( rects_x && rects_x.length > 0 ){rects_x = scale_xy(1,rects_x);rects_y = scale_xy(2,rects_y);draw_rects();};\
if( closedpoly_x && closedpoly_x.length > 0 ){closedpoly_x = scale_xy(1,closedpoly_x);closedpoly_y = scale_xy(2,closedpoly_y);draw_closedpoly();};\
if( text_x && text_x.length > 0 ){text_x = scale_xy(1,text_x);text_y = scale_xy(2,text_y);draw_text();};\
if( polys_x && polys_x.length > 0 ){polys_x = scale_xy(1,polys_x);polys_y = scale_xy(2,polys_y);draw_polys();};\
if( parallelogram_x && parallelogram_x.length > 0 ){parallelogram_x = scale_xy(1,parallelogram_x);parallelogram_y = scale_xy(2,parallelogram_y);draw_parallelogram();};\
return;\
};\
update_draw_area%d = function(desc,id_x,id_y,id_r){\
 var x1,x2,x3,y1,y2,y3,r,A,B;\
 x1 = document.getElementById(id_x.id).value;\
 y1 = document.getElementById(id_y.id).value;\
 if(desc > 3 && desc < 12 || desc == 14 || desc == 15){\
  A = coord_split(x1);B = coord_split(y1);\
  if(A.length != 2 || B.length != 2){alert(' X : Y ');return;};\
  x1 = x2px(safe_eval(A[0]));y1 = y2px(safe_eval(A[1]));\
  x2 = x2px(safe_eval(B[0]));y2 = y2px(safe_eval(B[1]));\
  if(desc == 10 || desc == 11 ){\
   r = document.getElementById(id_r.id).value;\
   A = coord_split(r);\
   x3 = x2px(safe_eval(A[0]));y3 = y2px(safe_eval(A[1]));\
  };\
 }\
 else\
 {\
  if( desc < 4 ){\
   x1 = x2px(safe_eval(x1));y1 = y2px( safe_eval(y1));\
  };\
 };\
 switch(desc){\
  case 0: points(x1,y1,0,0);break;\
  case 1: points(x1,y1,0,1);break;\
  case 2: r = scale_x_radius(safe_eval(document.getElementById(id_r.id).value));multi_radius[0] = r;circles_x[0] = x1;circles_y[0] = y1;draw_circles();break;\
  case 3: r = scale_x_radius(safe_eval(document.getElementById(id_r.id).value));multi_radius.push(r);circles_x.push(x1);circles_y.push(y1);draw_circles();break;\
  case 4: lines_x[0] = x1;lines_x[1] = x2;lines_y[0] = y1;lines_y[1] = y2;calc_lines();draw_lines();break;\
  case 5: lines_x.push(x1);lines_x.push(x2);lines_y.push(y1);lines_y.push(y2);calc_lines();draw_lines();break;\
  case 6: segments_x[0] = x1;segments_x[1] = x2;segments_y[0] = y1;segments_y[1] = y2;draw_segments();break;\
  case 7: segments_x.push(x1);segments_x.push(x2);segments_y.push(y1);segments_y.push(y2);draw_segments();break;\
  case 8: arrows_x[0] = x1;arrows_x[1] = x2;arrows_y[0] = y1;arrows_y[1] = y2;draw_arrows();break;\
  case 9: arrows_x.push(x1);arrows_x.push(x2);arrows_y.push(y1);arrows_y.push(y2);draw_arrows();break;\
  case 10: triangles_x[0] = x1;triangles_x[1] = x2;triangles_x[2] = x3;triangles_y[0] = y1;triangles_y[1] = y2;triangles_y[2] = y3;draw_triangles();break;\
  case 11: triangles_x.push(x1);triangles_x.push(x2);triangles_x.push(x3);triangles_y.push(y1);triangles_y.push(y2);triangles_y.push(y3);draw_triangles();break;\
  case 12:\
  A = coord_split(x1);B = coord_split(y1);\
  var plus_len = A.length;if( plus_len != B.length){alert('mismatch between the number of x-values and  y-values');return;};\
  for(var p = 0 ; p < plus_len ; p++){\
   x1 = x2px(safe_eval(A[p]));\
   y1 = y2px(safe_eval(B[p]));\
   closedpoly_x.push(x1);\
   closedpoly_y.push(y1);\
  };\
   x1 = x2px(safe_eval(A[0]));\
   y1 = y2px(safe_eval(B[0]));\
   closedpoly_x.push(x1);\
   closedpoly_y.push(y1);\
  draw_closedpoly();break;\
  case 13:text_abc.push( document.getElementById(id_r.id).value);text(x2px(safe_eval(x1)),y2px(safe_eval(y1)),0,1);draw_text();break;\
  case 14: rects_x[0] = x1;rects_x[1] = x2;rects_y[0] = y1;rects_y[1] = y2;draw_rects();break;\
  case 15: rects_x.push(x1);rects_x.push(x2);rects_y.push(y1);rects_y.push(y2);draw_rects();break;\
  case 16: polys_x[0] = x1;polys_x[1] = x2;polys_x[2] = x3;polys_y[0] = y1;polys_y[1] = y2;polys_y[2] = y3;draw_polys();break;\
  case 17: polys_x.push(x1);polys_x.push(x2);polys_x.push(x3);polys_y.push(y1);polys_y.push(y2);polys_y.push(y3);draw_polys();break;\
  case 18: parallelogram_x[0] = x1;parallelogram_x[1] = x2;parallelogram_x[2] = x3;parallelogram_y[0] = y1;parallelogram_y[1] = y2;parallelogram_y[2] = y3;draw_parallelogram();break;\
  case 19: parallelogram_x.push(x1);parallelogram_x.push(x2);parallelogram_x.push(x3);parallelogram_y.push(y1);parallelogram_y.push(y2);parallelogram_y.push(y3);draw_parallelogram();break;\
  default:break;\
 };\
};\
 <!-- end multidraw -->\n",canvas_root_id,canvas_root_id,draw_types,canvas_root_id,button_style,
 canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,
 canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id );
 
/* 
 now add specific draw functions according to draw_types 
 these will be somewhat simpler and less fancy-full than for the 'single object' userdraw command...
 the 'switch function' in the mouselisteners will probably eat more CPU...so the rest needs to be faster:
 we don't want to imitate these horribly slow js-libraries like JSXgraph

28/6/2015
TODO: add a selection of the 'generic js-code' from above into these C-code selector parts !
*/
 if( strstr(draw_types,"text") != 0){
  fprintf(js_include_file,"function text(x,y,event_which,num){\
   if(event_which == 1){ return; };\
   if( num == 0 ){\
    text_x[0] = x_snap_check(x,text_snap);\
     text_y[0] = y_snap_check(y,text_snap);\
   }else{\
    text_x.push(x_snap_check(x,text_snap));\
    text_y.push(y_snap_check(y,text_snap));\
   };\
   text_abc.push(document.getElementById('input_text_r').value);\
   draw_text();\
  };\
  function draw_text(){\
   context_text.clearRect(0,0,xsize,ysize);\
   for(var p = 0 ; p < text_x.length ; p++ ){\
    context_text.fillText(text_abc[p],text_x[p],text_y[p]);\
   };\
  };");
 }

 if( strstr(draw_types,"point") != 0){
  fprintf(js_include_file,"function points(x,y,event_which,num){\
   if(event_which == 1){ return; };\
   if( num == 0 ){\
     points_x[0] = x_snap_check(x,points_snap);\
     points_y[0] = y_snap_check(y,points_snap);\
   }else{\
    points_x.push(x_snap_check(x,points_snap));\
    points_y.push(y_snap_check(y,points_snap));\
   };\
   draw_points();\
  };\
  function draw_points(){\
   var radius = 2*(context_points.lineWidth);\
   context_points.clearRect(0,0,xsize,ysize);\
   for(var p = 0 ; p < points_x.length ; p++ ){\
    context_points.beginPath();\
    context_points.arc(points_x[p],points_y[p],radius,0,2*Math.PI,false);\
    context_points.closePath();\
    context_points.fill();\
   };\
  };");
 }
 if( strstr(draw_types,"circle") != 0){
  fprintf(js_include_file,"function circles(x,y,event_which,num){\
   var last = circles_x.length - 1;\
   var xc = circles_x[last];\
   var yc = circles_y[last];\
   if(event_which == 0){\
    circles_x.push(x_snap_check(x,circles_snap));circles_y.push(y_snap_check(y,circles_snap));multi_radius.push(4);\
    click_cnt++;\
   }\
   else\
   {\
    if( click_cnt == 1 ){\
     multi_radius[last] = parseInt(Math.sqrt( (x - xc)*(x - xc) + (y - yc)*(y - yc) ));\
    };\
   };\
   if( click_cnt == 2 ){\
    click_cnt = 0;\
    circles_x.pop();circles_y.pop();multi_radius.pop();\
    if( num == 0 ){\
     last = circles_x.length - 1;xc = circles_x[last];yc = circles_y[last];var r = multi_radius[last];\
     circles_x = new Array();circles_y = new Array();multi_radius = new Array();\
     circles_x[0] = x_snap_check(xc,circles_snap);circles_y[0] = y_snap_check(yc,circles_snap);multi_radius[0] = r;\
    }\
   };\
   draw_circles();\
 };\
 function draw_circles(){\
   context_circles.clearRect(0,0,xsize,ysize);\
   for(var p = 0 ; p < circles_x.length ; p++ ){\
    context_circles.beginPath();\
    context_circles.arc(circles_x[p],circles_y[p],multi_radius[p],0,2*Math.PI,false);\
    context_circles.closePath();\
    context_circles.fill();\
    context_circles.stroke();\
   };\
   return;\
 };"); 
 }

 if( strstr(draw_types,"segment") != 0){
  fprintf(js_include_file,"function segments(x,y,event_which,num){\
   var last = segments_x.length - 1;\
   if(event_which == 0){\
    if(num == 0){\
     segments_x[0] = x_snap_check(x,segments_snap);segments_y[0] = y_snap_check(y,segments_snap);\
    }\
    else\
    {\
     segments_x.push(x_snap_check(x,segments_snap));segments_y.push(y_snap_check(y,segments_snap));\
    };\
    click_cnt++;\
   }\
   else\
   {\
    if( click_cnt == 1 ){\
     segments_x.push(x_snap_check(x,segments_snap));segments_y.push(y_snap_check(y,segments_snap));\
     draw_segments();\
     segments_x.pop();segments_y.pop();\
    };\
   };\
   if( click_cnt == 2 ){\
    segments_x[last+num] = x_snap_check(x,segments_snap);segments_y[last+num] = y_snap_check(y,segments_snap);\
    click_cnt = 0;\
    draw_segments();\
   };\
  };\
  function draw_segments(){\
   var len = segments_x.length;\
   if( len%%2 == 0 ){\
    context_segments.clearRect(0,0,xsize,ysize);\
    for(var p = 0 ; p < len ; p = p+2 ){\
     context_segments.beginPath();\
     context_segments.moveTo(segments_x[p],segments_y[p]);\
     context_segments.lineTo(segments_x[p+1],segments_y[p+1]);\
     context_segments.closePath();\
     context_segments.stroke();\
    };\
   };\
   return;\
  };");
 }
 if( strstr(draw_types,"arrow") != 0){
  fprintf(js_include_file,"function arrows(x,y,event_which,num){\
   var last = arrows_x.length - 1;\
   if(event_which == 0){\
    if(num == 0){\
     arrows_x[0] =  x_snap_check(x,arrows_snap);arrows_y[0] = y_snap_check(y,arrows_snap);\
    }\
    else\
    {\
     arrows_x.push(x_snap_check(x,arrows_snap));arrows_y.push(y_snap_check(y,arrows_snap));\
    };\
    click_cnt++;\
   }\
   else\
   {\
    if( click_cnt == 1 ){\
     arrows_x.push(x_snap_check(x,arrows_snap));arrows_y.push(y_snap_check(y,arrows_snap));\
     draw_arrows();\
     arrows_x.pop();arrows_y.pop();\
    };\
   };\
   if( click_cnt == 2 ){\
    arrows_x[last+num] = x_snap_check(x,arrows_snap);arrows_y[last+num] = y_snap_check(y,arrows_snap);\
    click_cnt = 0;\
    draw_arrows();\
   };\
  };\
  function draw_arrows(){\
   var len = arrows_x.length;\
   var x1,y1,x2,y2,dx,dy,h;\
   if( len%%2 == 0 ){\
    context_arrows.clearRect(0,0,xsize,ysize);\
    for(var p = 0 ; p < len ; p = p+2 ){\
     context_arrows.save();\
     x1 = arrows_x[p];y1 = arrows_y[p];x2 = arrows_x[p+1];y2 = arrows_y[p+1];dx = x2 - x1;dy = y2 - y1;\
     h = Math.sqrt(dx*dx+dy*dy);\
     context_arrows.beginPath();\
     context_arrows.moveTo(x1,y1);\
     context_arrows.lineTo(x2,y2);\
     context_arrows.closePath();\
     context_arrows.stroke();\
     context_arrows.translate(x2,y2);\
     context_arrows.rotate(Math.atan2(dy,dx));\
     context_arrows.beginPath();\
     context_arrows.moveTo(0,0);\
     context_arrows.lineTo(-1*arrow_head,-0.5*arrow_head);\
     context_arrows.lineTo(-1*arrow_head, 0.5*arrow_head);\
     context_arrows.closePath();\
     context_arrows.fill();\
     context_arrows.stroke();\
     context_arrows.restore();\
    };\
   };\
  return;\
 };");
 }

 
 if( strstr(draw_types,"line") != 0){
  fprintf(js_include_file,"function calc_lines(){\
   var marge = 2;var len = lines_x.length;\
   var x = lines_x;var y = lines_y;\
   lines_x = new Array(len);\
   lines_y = new Array(len);\
   var pp;\
   for(var p = 0 ; p< len ;p = p+2){\
    pp = p+1;\
    if(x[p] < x[pp]+marge && x[p] > x[pp]-marge){\
     lines_x[p] = x[p];lines_x[pp] = x[pp];\
     lines_y[p] = 0;lines_y[pp] = ysize;\
    }\
    else\
    {\
     if(y[p] < y[pp]+marge && y[p] > y[pp]-marge){\
      lines_x[p] = 0;lines_x[pp] = xsize;\
      lines_y[p] = y[p];lines_y[pp] = y[pp];\
     }\
     else\
     {\
      lines_x[p] = 0;lines_x[pp] = xsize;\
      lines_y[p] = y[p] - (x[p])*(y[pp] - y[p])/(x[pp] - x[p]);\
      lines_y[pp] = y[p] + (xsize - x[p])*(y[pp] - y[p])/(x[pp] - x[p]);\
     };\
    };\
   };\
   return;\
  }\
  function lines(x,y,event_which,num){\
   if(event_which == 0){\
    if( num == 0 && click_cnt == 0 ){lines_x = [];lines_y = [];};\
    lines_x.push(x_snap_check(x,lines_snap));lines_y.push(y_snap_check(y,lines_snap));\
    click_cnt++;\
   }\
   else\
   {\
    if( click_cnt == 1 ){\
     lines_x.push(x_snap_check(x,lines_snap));lines_y.push(y_snap_check(y,lines_snap));\
     draw_lines();\
     lines_x.pop();lines_y.pop();\
    };\
   };\
   if( click_cnt == 2 ){\
    click_cnt = 0;\
    calc_lines();\
    draw_lines();\
   };\
  };\
  function draw_lines(){\
   var len = lines_x.length;\
   if( len %%2 == 0 ){\
    context_lines.clearRect(0,0,xsize,ysize);\
    for(var p = 0 ; p < len ; p = p+2 ){\
     context_lines.beginPath();\
     context_lines.moveTo(lines_x[p],lines_y[p]);\
     context_lines.lineTo(lines_x[p+1],lines_y[p+1]);\
     context_lines.closePath();\
     context_lines.stroke();\
    };\
   };\
   return;\
  };");
 }

 if( strstr(draw_types,"rect") != 0){
  fprintf(js_include_file,"\
  function rects(x,y,event_which,num){\
   if(event_which == 0){\
    if( num == 0 && click_cnt == 0 ){rects_x = [];rects_y = [];};\
    rects_x.push(x_snap_check(x,rects_snap));rects_y.push(y_snap_check(y,rects_snap));\
    click_cnt++;\
   }\
   else\
   {\
    if( click_cnt == 1 ){\
     rects_x.push(x_snap_check(x,rects_snap));rects_y.push(y_snap_check(y,rects_snap));\
     draw_rects();\
     rects_x.pop();rects_y.pop();\
    };\
   };\
   if( click_cnt == 2 ){\
    click_cnt = 0;\
    draw_rects();\
   };\
  };\
  function draw_rects(){\
   var len = rects_x.length;\
   if( len %%2 == 0 ){\
    context_rects.clearRect(0,0,xsize,ysize);\
    for(var p = 0 ; p < len ; p = p+2 ){\
     context_rects.beginPath();\
     context_rects.rect(rects_x[p],rects_y[p],rects_x[p+1]-rects_x[p],rects_y[p+1]-rects_y[p]);\
     context_rects.closePath();\
     context_rects.fill();\
     context_rects.stroke();\
    };\
   };\
   return;\
  };");
 }

 if( strstr(draw_types,"closedpoly") != 0 ){
  fprintf(js_include_file,"\
  function check_closed(x1,y1,X,Y){\
   var marge=10;\
   var len = X.length-1;\
   for(var p = 0 ; p < len ; p++){\
    if(x1 < X[p] + marge && x1 > X[p] - marge ){\
     if(y1 < Y[p] + marge && y1 > Y[p] - marge ){\
      return 1;\
     };\
    };\
   };\
   return 0;\
  };\
  function closedpoly(x,y,event_which,num){\
   if(event_which == 0){\
    if(click_cnt == 0){\
     closedpoly_x = [];closedpoly_y = [];\
     closedpoly_x[0] = x_snap_check(x,closedpoly_snap);closedpoly_y[0] = y_snap_check(y,closedpoly_snap);\
    }\
    else\
    {\
     closedpoly_x.push(x_snap_check(x,closedpoly_snap));closedpoly_y.push(y_snap_check(y,closedpoly_snap));\
    };\
    click_cnt++;\
    if( click_cnt > 2 ){\
     if( check_closed(x,y,closedpoly_x,closedpoly_y) == 1){\
      draw_closedpoly();\
      click_cnt = 0;\
     };\
    }\
   }\
   else\
   {\
    if( click_cnt > 0 ){\
     closedpoly_x.push(x_snap_check(x,closedpoly_snap));closedpoly_y.push(y_snap_check(y,closedpoly_snap));\
     draw_closedpoly();\
     closedpoly_x.pop();closedpoly_y.pop();\
    };\
   };\
  };\
  function draw_closedpoly(){\
   var len = closedpoly_x.length;\
   context_closedpoly.clearRect(0,0,xsize,ysize);\
   var p = 0;\
   context_closedpoly.beginPath();\
   context_closedpoly.moveTo(closedpoly_x[0],closedpoly_y[0]);\
   for(var p = 1 ; p < len ; p++){\
    context_closedpoly.lineTo(closedpoly_x[p],closedpoly_y[p]);\
   };\
   context_closedpoly.lineTo(closedpoly_x[0],closedpoly_y[0]);\
   context_closedpoly.closePath();\
   context_closedpoly.fill();\
   context_closedpoly.stroke();\
   return;\
  };");
 }
/* the next : just one type allowed triangel;.poly[3-9],parallelogram */
 if( strstr(draw_types,"triangle") != 0 ){
   fprintf(js_include_file,"\
   function triangles(x,y,event_which,num){\
    var last = triangles_x.length - 1;\
    if(event_which == 0){\
     if(num == 0 && click_cnt == 0){\
      triangles_x = [];triangles_y = [];\
      triangles_x[0] = x_snap_check(x,triangles_snap);triangles_y[0] = y_snap_check(y,triangles_snap);\
     }\
     else\
     {\
      triangles_x.push(x_snap_check(x,triangles_snap));triangles_y.push(y_snap_check(y,triangles_snap));\
     };\
     click_cnt++;\
    }\
    else\
    {\
     if( click_cnt < 3 ){\
      triangles_x.push(x_snap_check(x,triangles_snap));triangles_y.push(y_snap_check(y,triangles_snap));\
      draw_triangles();\
      triangles_x.pop();triangles_y.pop();\
     };\
    };\
    if( click_cnt == 3 ){\
     triangles_x.pop();triangles_y.pop();\
     triangles_x.push(x_snap_check(x,triangles_snap));triangles_y.push(y_snap_check(y,triangles_snap));\
     click_cnt = 0;\
     draw_triangles();\
    };\
   };\
   function draw_triangles(){\
    var len = triangles_x.length - 1;\
    context_triangles.clearRect(0,0,xsize,ysize);\
    for(var p = 0 ; p < len ; p = p+3){\
     context_triangles.beginPath();\
     context_triangles.moveTo(triangles_x[p],triangles_y[p]);\
     for( var m = p+1 ;m < p+3 ; m++){\
      context_triangles.lineTo(triangles_x[m],triangles_y[m]);\
     };\
     context_triangles.lineTo(triangles_x[p],triangles_y[p]);\
     context_triangles.closePath();\
     context_triangles.fill();\
     context_triangles.stroke();\
    };\
    return;\
   };");
 }
   /* need to rethink the parallelogram !!! 26/6/2015 */
 if(strstr( draw_types,"parallelogram") != 0){
  fprintf(js_include_file,"\
    function parallelogram(x,y,event_which,num){\
     var l2 = parallelogram_x.length;\
     var l1 = l2 - 1;\
     var l0 = l2 - 2;\
    if(event_which == 0){\
     if(click_cnt == 0){\
      if(num == 0){parallelogram_x = [];parallelogram_y = [];};\
      parallelogram_x.push(x_snap_check(x,parallelogram_snap));parallelogram_y.push(y_snap_check(y,parallelogram_snap));\
     }\
     else\
     {\
      parallelogram_x.push(x_snap_check(x,parallelogram_snap));parallelogram_y.push(y_snap_check(y,parallelogram_snap));\
      if(click_cnt == 2){\
       parallelogram_x.push(x_snap_check(parallelogram_x[l2]-parallelogram_x[l1] + parallelogram_x[l0]));\
       parallelogram_y.push(y_snap_check(parallelogram_y[l2]-parallelogram_y[l1] + parallelogram_y[l0]));\
      };\
     };\
     click_cnt++;\
    }\
    else\
    {\
     if(click_cnt == 1){\
      parallelogram_x.push(x_snap_check(parallelogram_x[l1]));\
      parallelogram_y.push(y_snap_check(parallelogram_y[l1]));\
      parallelogram_x.push(x_snap_check(x,parallelogram_snap));\
      parallelogram_y.push(y_snap_check(y,parallelogram_snap));\
      draw_parallelogram();\
      parallelogram_x.pop();parallelogram_y.pop();\
      parallelogram_x.pop();parallelogram_y.pop();\
     }\
     else\
     {\
      if(click_cnt > 1 && click_cnt < 3){\
       parallelogram_x.push(x_snap_check(x,parallelogram_snap));parallelogram_y.push(y_snap_check(y,parallelogram_snap));\
       parallelogram_x.push(x_snap_check(parallelogram_x[l2]-parallelogram_x[l1] + parallelogram_x[l0]));\
       parallelogram_y.push(y_snap_check(parallelogram_y[l2]-parallelogram_y[l1] + parallelogram_y[l0]));\
       draw_parallelogram();\
       parallelogram_x.pop();parallelogram_y.pop();\
       parallelogram_x.pop();parallelogram_y.pop();\
      };\
     };\
    };\
    if( click_cnt == 3 ){\
     parallelogram_x.pop();parallelogram_y.pop();\
     parallelogram_x.push(x_snap_check(parallelogram_x[l2]-parallelogram_x[l1] + parallelogram_x[l0]));\
     parallelogram_y.push(y_snap_check(parallelogram_y[l2]-parallelogram_y[l1] + parallelogram_y[l0]));\
     parallelogram_x.push(x_snap_check(x,parallelogram_snap));parallelogram_y.push(y_snap_check(y,parallelogram_snap));\
     parallelogram_x.pop();parallelogram_y.pop();\
     click_cnt = 0;\
     draw_parallelogram();\
    };\
   };\
   function draw_parallelogram(){\
    var len = parallelogram_x.length-1;\
    context_parallelogram.clearRect(0,0,xsize,ysize);\
    for(var p = 0 ; p < len ; p = p+4){\
     context_parallelogram.beginPath();\
     context_parallelogram.moveTo(parallelogram_x[p],parallelogram_y[p]);\
     for( var m = p+1 ;m < p+4 ; m++){\
      context_parallelogram.lineTo(parallelogram_x[m],parallelogram_y[m]);\
     };\
     context_parallelogram.lineTo(parallelogram_x[p],parallelogram_y[p]);\
     context_parallelogram.closePath();\
     context_parallelogram.fill();\
     context_parallelogram.stroke();\
    };\
    return;\
   };");
  }
  
  if( strstr( draw_types,("poly")) != 0 ){
   char *p = draw_types; int polynum=-1;
   while( *p ){ if( isdigit(*p) ){ polynum = atoi(p);break; } else { p++;} }
   if(polynum != -1 ){
    fprintf(js_include_file,"var polynum = %d;\
    function polys(x,y,event_which,num){\
     var last = polys_x.length - 1;\
     if(event_which == 0){\
      if(num == 0 && click_cnt == 0){\
       polys_x = [];polys_y = [];\
       polys_x[0] = x_snap_check(x,polys_snap);polys_y[0] = y_snap_check(y,polys_snap);\
      }\
      else\
      {\
       polys_x.push(x_snap_check(x,polys_snap));polys_y.push(y_snap_check(y,polys_snap));\
      };\
      click_cnt++;\
     }\
     else\
     {\
      if( click_cnt < polynum ){\
       polys_x.push(x_snap_check(x,polys_snap));polys_y.push(y_snap_check(y,polys_snap));\
       draw_polys();\
       polys_x.pop();polys_y.pop();\
      };\
     };\
     if( click_cnt == polynum ){\
      polys_x.pop();polys_y.pop();\
      polys_x.push(x_snap_check(x,polys_snap));polys_y.push(y_snap_check(y,polys_snap));\
      click_cnt = 0;\
      draw_polys();\
     };\
    };\
    function draw_polys(){\
     var len = polys_x.length - 1;\
     context_polys.clearRect(0,0,xsize,ysize);\
     for(var p = 0 ; p < len ; p = p+polynum){\
      context_polys.beginPath();\
      context_polys.moveTo(polys_x[p],polys_y[p]);\
      for( var m = p+1 ;m < p+polynum ; m++){\
       context_polys.lineTo(polys_x[m],polys_y[m]);\
      };\
      context_polys.lineTo(polys_x[p],polys_y[p]);\
      context_polys.closePath();\
      context_polys.fill();\
      context_polys.stroke();\
     };\
     return;\
    };",polynum);
   }
  }
} /* end 'void add_js_multidraw()' */

void add_js_circles(FILE *js_include_file,int num,char *draw_type,int line_width, int radius ,char *stroke_color,double stroke_opacity,int use_filled,char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on final canvas -->\n\
var num = %d;\
userdraw_radius[0] = %d;\
var line_width = %d;\
var stroke_color = \"%s\";\
var stroke_opacity = %f;\
var use_filled = %d;\
var fill_color = \"%s\";\
var fill_opacity = %f;\
var use_dashed = %d;\
var dashtype1 = %d;\
var dashtype0 = %d;\
var click_cnt = 0;\
var x0,y0,x1,y1;\
var mouse;\
function user_draw(evt){\
 mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 x0 = mouse.x;\
 y0 = mouse.y;\
 if(y0 < ysize + 1){\
  if( use_snap_to_points != 0 ){\
   var xy = new Array(2);\
   if( use_snap_to_points == 1 ){\
    xy = snap_to_points(x0,y0);\
   }\
   else\
   {\
    xy = snap_to_fun(x0,y0);\
   };\
   x0 = xy[0];y0 = xy[1];\
  }\
  else\
  {\
   if( x_use_snap_to_grid == 1 ){\
    x0 = snap_to_x(x0);\
   };\
   if( y_use_snap_to_grid == 1 ){\
    y0 = snap_to_y(y0);\
   };\
  };\
  if(evt.which == 1 || evt.identifier == 0){\
   if( click_cnt == 0 ){\
    userdraw_x[xy_cnt] = x0;\
    userdraw_y[xy_cnt] = y0;\
    userdraw_radius[xy_cnt] = line_width;\
    click_cnt = 1;\
    draw_circles(context_userdraw,userdraw_x,userdraw_y,userdraw_radius,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);\
   }\
   else\
   {\
    click_cnt = 0;\
    if( num != 1 ){ xy_cnt++; }\
   }\
  }\
  else\
  {\
    canvas_remove(x0,y0);\
  }\
 }\
};\
function user_drag(evt){\
 if( click_cnt == 1 ){\
  mouse = dragstuff.getMouse(evt,canvas_userdraw);\
  x1 = mouse.x;\
  y1 = mouse.y;\
  if( use_snap_to_points != 0 ){\
   var xy = new Array(2);\
   if( use_snap_to_points == 1 ){\
    xy = snap_to_points(x1,y1);\
   }\
   else\
   {\
    xy = snap_to_fun(x1,y1);\
   };\
   x1 = xy[0];y1 = xy[1];\
  }\
  else\
  {\
   if( x_use_snap_to_grid == 1 ){\
     x1 = snap_to_x(x1);\
   };\
   if( y_use_snap_to_grid == 1 ){\
    y1 = snap_to_y(y1);\
   };\
  };\
  userdraw_radius[xy_cnt] = parseInt(Math.sqrt( (x1-x0)*(x1-x0) + (y1-y0)*(y1-y0) ));\
  userdraw_x[xy_cnt] = x0;\
  userdraw_y[xy_cnt] = y0;\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_circles(context_userdraw,userdraw_x,userdraw_y,userdraw_radius,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);\
 };\
};\
function canvas_remove(x,y){\
 var marge = 10*line_width;\
 var diff1;var diff2;\
 for(var p = 0;p < userdraw_x.length ; p++){\
  diff1 = (x-userdraw_x[p])*(x - userdraw_x[p]) + (y - userdraw_y[p])*(y - userdraw_y[p]) - userdraw_radius[p]*userdraw_radius[p];\
  diff2 = (x-userdraw_x[p])*(x - userdraw_x[p]) + (y - userdraw_y[p])*(y - userdraw_y[p]) - (userdraw_radius[p] - marge)*(userdraw_radius[p] - marge);\
  if( diff1 < 0 && diff2 > 0 ){\
   if(confirm(\"remove circle ?\")){\
    if( num == 1 ){ userdraw_x = [];userdraw_y = []; userdraw_radius = [];xy_cnt = 0;context_userdraw.clearRect(0,0,xsize,ysize); return;}\
    else\
    {\
     userdraw_x.splice(p,1);\
     userdraw_y.splice(p,1);\
     userdraw_radius.splice(p,1);\
     xy_cnt--;\
     context_userdraw = null;context_userdraw = canvas_userdraw.getContext(\"2d\");context_userdraw.clearRect(0,0,xsize,ysize);\
     draw_circles(context_userdraw,userdraw_x,userdraw_y,userdraw_radius,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);\
    };\
   };\
   return;\
  }\
 }\
};",draw_type,num,radius,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);
}


/*  function draw_circles(ctx,x_points,y_points,radius,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);*/
void add_js_points(FILE *js_include_file,int num,char *draw_type,int line_width, int radius ,char *stroke_color,double stroke_opacity,int use_filled,char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on final canvas -->\n\
var num = %d;\
userdraw_radius[0] = %d;\
var line_width = %d;\
var stroke_color = \"%s\";\
var stroke_opacity = %f;\
var use_filled = %d;\
var fill_color = \"%s\";\
var fill_opacity = %f;\
var use_dashed = %d;\
var dashtype1 = %d;\
var dashtype0 = %d;\
var x0,y0,x1,y1;\
var canvas_rect;\
function user_draw(evt){\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 x0 = mouse.x;\
 y0 = mouse.y;\
 if( use_snap_to_points != 0 ){\
  var xy = new Array(2);\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x0,y0);\
  }\
  else\
  {\
   xy = snap_to_fun(x0,y0);\
  };\
  x0 = xy[0];y0 = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
   x0 = snap_to_x(x0);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y0 = snap_to_y(y0);\
  };\
 };\
 if(evt.which == 1 || evt.identifier == 0){\
  userdraw_x[xy_cnt] = x0;\
  userdraw_y[xy_cnt] = y0;\
  userdraw_radius[xy_cnt] = line_width;\
  if( num != 1 ){ xy_cnt++; }else{context_userdraw.clearRect(0,0,xsize,ysize);};\
  draw_circles(context_userdraw,userdraw_x,userdraw_y,userdraw_radius,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);\
 }\
 else\
 {\
  canvas_remove(x0,y0);\
 };\
};\
function user_drag(evt){ return;};\
function canvas_remove(x,y){\
 var marge = 4*line_width;\
 for(var p = 0;p < userdraw_x.length ; p++){\
  if(userdraw_x[p] < x + marge && userdraw_x[p] > x - marge ){\
   if(userdraw_y[p] < y + marge && userdraw_y[p] > y - marge ){\
    userdraw_x.splice(p,1);userdraw_y.splice(p,1);\
    context_userdraw = null;context_userdraw = canvas_userdraw.getContext(\"2d\");context_userdraw.clearRect(0,0,xsize,ysize);\
    draw_circles(context_userdraw,userdraw_x,userdraw_y,userdraw_radius,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);\
    xy_cnt--;\
    return;\
   };\
  };\
 };\
};",draw_type,num,radius,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);
}

void add_js_inputs(FILE *js_include_file,int canvas_root_id,int num,int input_cnt,char *input_style,int line_width){
fprintf(js_include_file,"\n<!-- user draw inputfields -->\n\
var canvas_rect;\
var input_cnt = %d;\
var start_input_cnt = input_cnt;\
function user_drag(evt){return;}\
function user_draw(evt){\
 canvas_rect = canvas_userdraw.getBoundingClientRect();\
 var x = evt.clientX - canvas_rect.left;\
 var y = evt.clientY - canvas_rect.top;\
 if( use_snap_to_points != 0 ){\
  var xy = new Array(2);\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x,y);\
  }\
  else\
  {\
   xy = snap_to_fun(x,y);\
  };\
  x = xy[0];y = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
 };\
 var num = %d;var inputs;\
 if(evt.which == 1){\
  var inputs;var xi;var yi;var wi;var hi;\
  var found = 0;\
  if( start_input_cnt < input_cnt){\
   for(var p = start_input_cnt ; p < input_cnt ; p++ ){\
    inputs = document.getElementById(\"canvas_input\"+p);\
    xi = findPosX(inputs) - canvas_rect.left;\
    yi = findPosY(inputs) - canvas_rect.top;\
    wi = 4 + inputs.clientWidth;\
    hi = 4 + inputs.clientHeight;\
    if( x > xi - wi && x < xi + wi && y > yi - hi && y < yi + hi ){\
     found = 1;\
    };\
   };\
  };\
  if( found == 0 ){\
   if( num == 1 ){\
    inputs = document.getElementById(\"canvas_input\"+start_input_cnt);\
    try{canvas_div.removeChild(inputs);}catch(e){};\
    input_cnt = 0;\
   };\
   userdraw_x.push(x);userdraw_y.push(y);\
   draw_inputs(%d,input_cnt,x,y,%d,1,\"%s\",\"?\");\
   input_cnt++;\
  };\
 }\
 else\
 {\
  for(var p = start_input_cnt ; p < input_cnt; p++){\
   inputs = document.getElementById(\"canvas_input\"+p);\
   try{canvas_div.removeChild(inputs);}catch(e){};\
  };\
  userdraw_x = [];userdraw_y = [];\
  input_cnt = start_input_cnt;\
 };\
};",input_cnt,num,canvas_root_id,line_width,input_style);
}

void add_zoom_buttons(FILE *js_include_file,int canvas_root_id,char *stroke_color,double stroke_opacity){
fprintf(js_include_file,"\n<!-- draw zoom buttons -->\n\
var draw_zoom_buttons = function(){\
 var obj;var canvas_type =%d;\
 if( document.getElementById(\"wims_canvas%d\"+canvas_type) ){\
  obj = document.getElementById(\"wims_canvas%d\"+canvas_type);\
 }\
 else\
 {\
  obj = create_canvas%d(canvas_type,xsize,ysize);\
 };\
 var ctx = obj.getContext(\"2d\");\
 ctx.font =\"18px Ariel\";\
 ctx.textAlign = \"right\";\
 ctx.fillStyle=\"rgba(%s,%f)\";\
 ctx.fillText(\"+\",xsize,ysize);\
 ctx.fillText(\"\\u2212\",xsize - 15,ysize);\
 ctx.fillText(\"\\u2192\",xsize - 30,ysize-2);\
 ctx.fillText(\"\\u2190\",xsize - 45,ysize-2);\
 ctx.fillText(\"\\u2191\",xsize - 60,ysize-2);\
 ctx.fillText(\"\\u2193\",xsize - 75,ysize-2);\
 ctx.fillText(\"\\u00D7\",xsize - 90,ysize-2);\
 ctx.stroke();\
};\ndraw_zoom_buttons();",BG_CANVAS,canvas_root_id,canvas_root_id,canvas_root_id,stroke_color,stroke_opacity);
}

void add_js_crosshairs(FILE *js_include_file,int num,char *draw_type,int line_width, int crosshair_size ,char *stroke_color,double stroke_opacity){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on currect active canvas -->\n\
var num = %d;\
var crosshair_size = %d;\
var line_width = %d;\
var stroke_color = \"%s\";\
var stroke_opacity = %f;\
context_userdraw.lineWidth = line_width;\
context_userdraw.strokeStyle=\"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
function user_drag(evt){return;}\
function user_draw(evt){\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 var x = mouse.x;\
 var y = mouse.y;\
 if( use_snap_to_points != 0 ){\
  var xy = new Array(2);\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x,y);\
  }\
  else\
  {\
   xy = snap_to_fun(x,y);\
  };\
  x = xy[0];y = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
 };\
 var x1,y1,x2,y2;\
 if(evt.which == 1 || evt.identifier == 0 ){\
   userdraw_x[xy_cnt] = x;\
   userdraw_y[xy_cnt] = y;\
   x1 = x - crosshair_size;\
   x2 = x + crosshair_size;\
   y1 = y - crosshair_size;\
   y2 = y + crosshair_size;\
   if( num != 1 ){ xy_cnt++;\
    for(var p = 0; p < xy_cnt - 1 ;p++){\
     if(x1 < userdraw_x[p] && x2 > userdraw_x[p]){\
      if(y1 < userdraw_y[p] && y2 > userdraw_y[p]){\
       canvas_remove(x,y);\
       context_userdraw = null;context_userdraw = canvas_userdraw.getContext(\"2d\");\
      }\
     }\
    }\
   };\
   context_userdraw.beginPath();\
   context_userdraw.moveTo(x1,y1);\
   context_userdraw.lineTo(x2,y2);\
   context_userdraw.closePath();\
   context_userdraw.stroke();\
   context_userdraw.beginPath();\
   context_userdraw.moveTo(x2,y1);\
   context_userdraw.lineTo(x1,y2);\
   context_userdraw.closePath();\
   context_userdraw.stroke();\
   context_userdraw.clearRect(0,0,xsize,ysize);\
   draw_crosshairs(context_userdraw,userdraw_x,userdraw_y,line_width,crosshair_size,stroke_color,stroke_opacity,0,0,0,[0,0]);\
 }\
 else\
 {\
 canvas_remove(x,y);\
 }\
}\
function canvas_remove(x,y){\
 var marge = 2*crosshair_size;\
 for(var p = 0;p < userdraw_x.length ; p++){\
  if(userdraw_x[p] < x + marge && userdraw_x[p] > x - marge ){\
   if(userdraw_y[p] < y + marge && userdraw_y[p] > y - marge ){\
    userdraw_x.splice(p,1);userdraw_y.splice(p,1);\
    context_userdraw = null;context_userdraw = canvas_userdraw.getContext(\"2d\");context_userdraw.clearRect(0,0,xsize,ysize);\
    xy_cnt--;\
    draw_crosshairs(context_userdraw,userdraw_x,userdraw_y,line_width,crosshair_size,stroke_color,stroke_opacity,0,0,0,[0,0]);\
    return;\
   }\
  }\
 }\
};",draw_type,num,crosshair_size,line_width,stroke_color,stroke_opacity);
}

void add_js_rect(FILE *js_include_file,int num,int roundrect,char *draw_type,int line_width,char *stroke_color,double stroke_opacity,int use_filled,char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on currect active canvas -->\n\
var roundrect = %d;\
var line_width = %d;\
var stroke_color = \"%s\";\
var stroke_opacity = %f;\
var use_filled = %d;\
var fill_color = \"%s\";\
var fill_opacity = %f;\
var use_dashed = %d;\
var dashtype0 = %d;\
var dashtype1 = %d;\
var num = %d;\
var use_rotate = 0;\
var angle = 0;\
var closed_path = 1;\
var clickcnt = 0;\
xy_cnt = 0;\
var x0,y0,x1,y1;\
var marge = 10*line_width;\
function user_draw(evt){\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 x0 = mouse.x;\
 y0 = mouse.y;\
 if( use_snap_to_points != 0 ){\
  var xy = new Array(2);\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x0,y0);\
  }\
  else\
  {\
   xy = snap_to_fun(x0,y0);\
  };\
  x0 = xy[0];y0 = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
   x0 = snap_to_x(x0);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y0 = snap_to_y(y0);\
  };\
 };\
 if( evt.which == 1 || evt.identifier == 0 ){\
  if(clickcnt == 0 ){\
   clickcnt = 1;\
   userdraw_x[xy_cnt] = x0;userdraw_y[xy_cnt] = y0;xy_cnt++;\
  }\
  else\
  {\
   clickcnt = 0;\
   if(roundrect == 0 ){\
    draw_rects(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,0,[1,0,0,1,0,0]);\
   }\
   else\
   {\
    draw_roundrects(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,0,[1,0,0,1,0,0]);\
   }\
   if( num != 1 ){ xy_cnt++; }else{xy_cnt--;}\
  }\
 }\
 else\
 {\
  canvas_remove(x0,y0);\
 };\
};\
function user_drag(evt){\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 x1 = mouse.x;\
 y1 = mouse.y;\
 if( clickcnt == 1 ){\
  var xy = new Array(2);\
  if( use_snap_to_points != 0 ){\
   if( use_snap_to_points == 1 ){\
    xy = snap_to_points(x1,y1);\
   }\
   else\
   {\
    xy = snap_to_fun(x1,y1);\
   };\
   x1 = xy[0];y1 = xy[1];\
  }\
  else\
  {\
   if( x_use_snap_to_grid == 1 ){\
    x1 = snap_to_x(x1);\
   };\
   if( y_use_snap_to_grid == 1 ){\
   y1 = snap_to_y(y1);\
   };\
  };\
  userdraw_x[xy_cnt] = x1;\
  userdraw_y[xy_cnt] = y1;\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  if( roundrect == 0 ){\
   draw_rects(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,0,[1,0,0,1,0,0]);\
  }\
  else\
  {\
   draw_roundrects(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,0,[1,0,0,1,0,0]);\
  };\
 };\
};\
function canvas_remove(x,y){\
 for(var p = 0;p < userdraw_x.length ; p++){\
  if(userdraw_x[p] < x + marge && userdraw_x[p] > x - marge ){\
   if(userdraw_y[p] < y + marge && userdraw_y[p] > y - marge ){\
    if( confirm(\"remove rectangle ?\" )){\
     if( p%%2 == 0 ){\
      userdraw_x.splice(p,2);userdraw_y.splice(p,2);\
     }\
     else\
     {\
      userdraw_x.splice(p-1,2);userdraw_y.splice(p-1,2);\
     }\
     xy_cnt = xy_cnt - 2;\
     context_userdraw.clearRect(0,0,xsize,ysize);\
     if(xy_cnt < 2){xy_cnt = 0;click_cnt = 0;userdraw_x = [];userdraw_y = [];return;};\
     if( roundrect == 0 ){\
      draw_rects(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,0,[1,0,0,1,0,0]);\
     }\
     else\
     {\
      draw_roundrects(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,0,[1,0,0,1,0,0]);\
     }\
     return;\
    };\
   };\
  };\
 };\
};",draw_type,roundrect,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,num);
}

void add_js_poly(FILE *js_include_file,int num,char *draw_type,int line_width,char *stroke_color,double stroke_opacity,int use_filled,char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on currect active canvas -->\n\
var num = %d;\
var line_width = %d;\
var stroke_color = \"%s\";\
var stroke_opacity = %f;\
var use_filled = %d;\
var fill_color = \"%s\";\
var fill_opacity = %f;\
var use_dashed = %d;\
var dashtype0 = %d;\
var dashtype1 = %d;\
var use_rotate = 0;\
var angle = 0;\
var use_translate = 0;\
var vector=[0,0];\
var closed_path = 1;\
var done = 1;\
var x,y;\
var marge = 10*line_width;\
var canvas_rect;\
function user_draw(evt){\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 x = mouse.x;\
 y = mouse.y;\
 var xy = new Array(2);\
 if( use_snap_to_points != 0 ){\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x,y);\
  }\
  else\
  {\
   xy = snap_to_fun(x,y);\
  };\
  x = xy[0];y = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
 };\
 if( evt.which == 1 || evt.identifier == 0 ){\
  if( num == -1 && xy_cnt > 2 ){\
   if( x - marge < userdraw_x[0] && x + marge > userdraw_x[0]){\
    if( y - marge < userdraw_y[0] && y + marge > userdraw_y[0]){\
     userdraw_x.splice(xy_cnt,1);userdraw_y.splice(xy_cnt,1);\
     draw_paths(context_userdraw,userdraw_x,userdraw_y,line_width,closed_path,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,0,[1,0,0,1,0,0]);\
     done = 1;return;\
    };\
   };\
  }\
  else\
  {\
   if( xy_cnt == num - 1){\
    draw_paths(context_userdraw,userdraw_x,userdraw_y,line_width,closed_path,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,0,[1,0,0,1,0,0]);\
    done = 1;return;\
   };\
  };\
  done = 0;\
  userdraw_x[xy_cnt] = x;userdraw_y[xy_cnt] = y;xy_cnt++;\
  user_drag(evt);\
 }\
 else\
 {\
  canvas_remove(x,y);\
  return;\
 }\
};\
function user_drag(evt){\
 if( done == 0 ){\
  var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
  x = mouse.x;\
  y = mouse.y;\
  if( use_snap_to_points != 0 ){\
   var xy = new Array(2);\
   if( use_snap_to_points == 1 ){\
    xy = snap_to_points(x,y);\
   }\
   else\
   {\
    xy = snap_to_fun(x,y);\
   };\
   x = xy[0];y = xy[1];\
  }\
  else\
  {\
   if( x_use_snap_to_grid == 1 ){\
    x = snap_to_x(x);\
   };\
   if( y_use_snap_to_grid == 1 ){\
    y = snap_to_y(y);\
   };\
  };\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  userdraw_x[xy_cnt] = x;userdraw_y[xy_cnt] = y;\
  draw_paths(context_userdraw,userdraw_x,userdraw_y,line_width,closed_path,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,0,[1,0,0,1,0,0]);\
 }\
}\
function canvas_remove(x,y){\
 for(var p = 0;p < userdraw_x.length ; p++){\
  if(userdraw_x[p] < x + marge && userdraw_x[p] > x - marge ){\
   if(userdraw_y[p] < y + marge && userdraw_y[p] > y - marge ){\
    if( confirm(\"remove polygone ?\" )){\
     context_userdraw = null;context_userdraw = canvas_userdraw.getContext(\"2d\");context_userdraw.clearRect(0,0,xsize,ysize);\
     xy_cnt = 0;userdraw_x = [];userdraw_y = [];done = 1;\
    }\
    return;\
   }\
  }\
 }\
};",draw_type,num,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);
}

/*
  canvas_rect = canvas_userdraw.getBoundingClientRect();\
  var x = evt.clientX - canvas_rect.left;\
  var y = evt.clientY - canvas_rect.top;\
*/
void add_js_polyline(FILE *js_include_file,char *draw_type,int line_width, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on final canvas -->\n\
var cnt = 0;\
var line_width = %d;\
var stroke_color = \"%s\";\
var stroke_opacity = %f;\
var use_dashed = %d;\
var dashtype0 = %d;\
var dashtype1 = %d;\
var x,y;\
function user_draw(evt){\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 x = mouse.x;\
 y = mouse.y;\
 var lu = userdraw_x.length;\
 if( use_snap_to_points != 0 ){\
  var xy = new Array(2);\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x,y);\
  }\
  else\
  {\
   xy = snap_to_fun(x,y);\
  };\
  x = xy[0];y = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
 };\
 if( evt.which == 1 || evt.identifier == 0 ){\
  userdraw_x[lu] = x;userdraw_y[lu] = y;\
  if( cnt == 0 ){\
   user_drag(evt);\
   cnt = 1;\
  }\
  else\
  {\
    cnt = 0;\
    draw_polyline(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
  }\
 }\
 else\
 {\
  canvas_remove(x,y);\
 }\
};\
function user_drag(evt){\
 if( cnt == 0){\
  var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
  x = mouse.x;\
  y = mouse.y;\
  if( use_snap_to_points != 0 ){\
   var xy = new Array(2);\
   if( use_snap_to_points == 1 ){\
    xy = snap_to_points(x,y);\
   }\
   else\
   {\
    xy = snap_to_fun(x,y);\
   };\
   x = xy[0];y = xy[1];\
  }\
  else\
  {\
   if( x_use_snap_to_grid == 1 ){\
    x = snap_to_x(x);\
   };\
   if( y_use_snap_to_grid == 1 ){\
    y = snap_to_y(y);\
   };\
  };\
  var lu = userdraw_x.length;\
  if( lu > 0 ){\
   userdraw_x[lu - 1] = x; userdraw_y[lu - 1] = y;\
   draw_polyline(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
  };\
 }\
};\
function canvas_remove(x,y){\
 if( confirm(\"remove line ?\" )){\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  userdraw_x = [];userdraw_y = [];cnt = 1;\
  xy_cnt=0;\
  return;\
 }\
};",draw_type,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);
}

void add_js_segments(FILE *js_include_file,int num,char *draw_type,int line_width, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on final canvas -->\n\
var num = %d;\
var line_width = %d;\
var stroke_color = \"%s\";\
var stroke_opacity = %f;\
var use_dashed = %d;\
var dashtype0 = %d;\
var dashtype1 = %d;\
var x0,y0;\
function user_draw(evt){\
 var lu = userdraw_x.length;\
 if( lu != 0 && lu%%2 == 0){\
  draw_segments(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
 }\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 var x = mouse.x;\
 var y = mouse.y;\
 if( use_snap_to_points != 0 ){\
  var xy = new Array(2);\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x,y);\
  }\
  else\
  {\
   xy = snap_to_fun(x,y);\
  };\
  x = xy[0];y = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
 };\
 if( evt.which == 1 || evt.identifier == 0){\
  if( lu%%2 == 0){\
   x0 = x;y0 = y;\
   if(num == 1){ userdraw_x = [];userdraw_y = [];userdraw_x[0] = x0;userdraw_y[0] = y0;} else {userdraw_x[lu] = x0;userdraw_y[lu] = y0;};\
   draw_circles(context_userdraw,[x0],[y0],[line_width],line_width,stroke_color,stroke_opacity,1,stroke_color,stroke_opacity,0,1,1);\
   user_drag(evt);\
  }\
  else\
  {\
   if( num == 1 ){ userdraw_x[1] = x;userdraw_y[1] = y;} else {userdraw_x[lu] = x;userdraw_y[lu] = y;};\
   draw_segments(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
  }\
 }\
 else\
 {\
  canvas_remove(x,y);\
 }\
};\
function user_drag(evt){\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 var x = mouse.x;\
 var y = mouse.y;\
 var lu = userdraw_x.length;\
 if( use_snap_to_points != 0 ){\
  var xy = new Array(2);\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x,y);\
  }\
  else\
  {\
   xy = snap_to_fun(x,y);\
  };\
  x = xy[0];y = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
 };\
 if( lu%%2 != 0 ){\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_circles(context_userdraw,[x0],[y0],[line_width],line_width,stroke_color,stroke_opacity,1,stroke_color,stroke_opacity,0,1,1);\
  draw_circles(context_userdraw,[x],[y],[line_width],line_width,stroke_color,stroke_opacity,1,stroke_color,stroke_opacity,0,1,1);\
  draw_segments(context_userdraw,[x0,x],[y0,y],line_width,stroke_color,stroke_opacity);\
  if( lu > 0){\
   draw_segments(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
  }\
 }\
};\
function canvas_remove(x,y){\
 var marge = 10*line_width;\
 for(var p = 0;p < userdraw_x.length ; p++){\
  if(userdraw_x[p] < x + marge && userdraw_x[p] > x - marge ){\
   if(userdraw_y[p] < y + marge && userdraw_y[p] > y - marge ){\
    if( confirm(\"remove line ?\" )){\
     context_userdraw = null;context_userdraw = canvas_userdraw.getContext(\"2d\");context_userdraw.clearRect(0,0,xsize,ysize);\
     if( p%%2 == 0 ){\
      userdraw_x.splice(p,2);userdraw_y.splice(p,2);\
     }\
     else\
     {\
      userdraw_x.splice(p-1,2);userdraw_y.splice(p-1,2);\
     }\
     if(userdraw_x.length < 2){ userdraw_x = [];userdraw_y = [];return;};\
     xy_cnt = xy_cnt - 2;\
     draw_segments(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
    }\
    return;\
   }\
  }\
 }\
};",draw_type,num,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);
}

void add_js_demilines(FILE *js_include_file,int num,char *draw_type,int line_width, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on final canvas -->\n\
var num = %d;\
var line_width = %d;\
var stroke_color = \"%s\";\
var stroke_opacity = %f;\
var use_dashed = %d;\
var dashtype0 = %d;\
var dashtype1 = %d;\
var x0,y0;\
function user_draw(evt){\
 var lu = userdraw_x.length;\
 if( lu != 0 && lu%%2 == 0){\
  draw_demilines(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
 }\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 var x = mouse.x;\
 var y = mouse.y;\
 if( use_snap_to_points != 0 ){\
  var xy = new Array(2);\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x,y);\
  }\
  else\
  {\
   xy = snap_to_fun(x,y);\
  };\
  x = xy[0];y = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
 };\
 if( evt.which == 1 || evt.identifier == 0 ){\
  if( lu%%2 == 0){\
   x0 = x;y0 = y;\
   if(num == 1){ userdraw_x = [];userdraw_y = [];userdraw_x[0] = x0;userdraw_y[0] = y0;} else {userdraw_x[lu] = x0;userdraw_y[lu] = y0;}\
   draw_circles(context_userdraw,[x0],[y0],[line_width],line_width,stroke_color,stroke_opacity,1,stroke_color,stroke_opacity,0,1,1);\
   user_drag(evt);\
  }\
  else\
  {\
   if( num == 1 ){ userdraw_x[1] = x;userdraw_y[1] = y;} else {userdraw_x[lu] = x;userdraw_y[lu] = y;};\
   draw_demilines(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
  }\
 }\
 else\
 {\
  canvas_remove(x,y);\
 }\
};\
function user_drag(evt){\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 var x = mouse.x;\
 var y = mouse.y;\
 var lu = userdraw_x.length;\
 if( use_snap_to_points != 0 ){\
  var xy = new Array(2);\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x,y);\
  }\
  else\
  {\
   xy = snap_to_fun(x,y);\
  };\
  x = xy[0];y = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
 };\
 if( lu%%2 != 0 ){\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_circles(context_userdraw,[x0],[y0],[line_width],line_width,stroke_color,stroke_opacity,1,stroke_color,stroke_opacity,0,1,1);\
  draw_circles(context_userdraw,[x],[y],[line_width],line_width,stroke_color,stroke_opacity,1,stroke_color,stroke_opacity,0,1,1);\
  draw_demilines(context_userdraw,[x0,x],[y0,y],line_width,stroke_color,stroke_opacity);\
  if( lu > 0){\
   draw_demilines(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
  }\
 }\
};\
function canvas_remove(x,y){\
 var marge = 10*line_width;\
 for(var p = 0;p < userdraw_x.length ; p++){\
  if(userdraw_x[p] < x + marge && userdraw_x[p] > x - marge ){\
   if(userdraw_y[p] < y + marge && userdraw_y[p] > y - marge ){\
    if( confirm(\"remove line ?\" )){\
     context_userdraw = null;context_userdraw = canvas_userdraw.getContext(\"2d\");context_userdraw.clearRect(0,0,xsize,ysize);\
     if( p%%2 == 0 ){\
      userdraw_x.splice(p,2);userdraw_y.splice(p,2);\
     }\
     else\
     {\
      userdraw_x.splice(p-1,2);userdraw_y.splice(p-1,2);\
     }\
     xy_cnt = xy_cnt - 2;\
     if(userdraw_x.length < 2){ userdraw_x = [];userdraw_y = [];return;};\
     draw_demilines(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
    }\
    return;\
   }\
  }\
 }\
};",draw_type,num,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);
}


/*
num=1 single horizontal line
num=2 multiple horizontal lines
num=3 single vertical line
num=4 multiple vertical lines
*/
void add_js_hlines(FILE *js_include_file,int num,char *draw_type,int line_width, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on final canvas -->\n\
var num = %d;\
var line_width = %d;\
var stroke_color = \"%s\";\
var stroke_opacity = %f;\
var use_dashed = %d;\
var dashtype0 = %d;\
var dashtype1 = %d;\
var x0,y0;\
function user_draw(evt){\
 if( evt.which == 1 || evt.identifier == 0){\
  var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
  var x = mouse.x;\
  var y = mouse.y;\
  if( use_snap_to_points != 0 ){\
   var xy = new Array(2);\
   if( use_snap_to_points == 1 ){\
    xy = snap_to_points(x,y);\
   }\
   else\
   {\
    xy = snap_to_fun(x,y);\
   };\
   x = xy[0];y = xy[1];\
  }\
  else\
  {\
   if( x_use_snap_to_grid == 1 ){\
    x = snap_to_x(x);\
   };\
   if( y_use_snap_to_grid == 1 ){\
    y = snap_to_y(y);\
   };\
  };\
  var lu = userdraw_x.length;\
  switch(num){\
   case 1: userdraw_x[0] = x;userdraw_x[1] = xmax;userdraw_y[0] = y; userdraw_y[1] = y;break;\
   case 2: userdraw_x[lu] = x;userdraw_x[lu+1] = xmax;userdraw_y[lu] = y;userdraw_y[lu+1] = y;break;\
   case 3: userdraw_x[0] = x;userdraw_x[1] = x;userdraw_y[0] = y; userdraw_y[1] = ymax;break;\
   case 4: userdraw_x[lu] = x;userdraw_x[lu+1] = x;userdraw_y[lu] = y;userdraw_y[lu+1] = ymax;break;\
  };\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_lines(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
 }\
 else\
 {\
  userdraw_x = [];userdraw_y = [];context_userdraw.clearRect(0,0,xsize,ysize);return;\
 };\
};\
function user_drag(evt){ return evt; };",draw_type,num,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);
}



void add_js_lines(FILE *js_include_file,int num,char *draw_type,int line_width, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on final canvas -->\n\
var num = %d;\
var line_width = %d;\
var stroke_color = \"%s\";\
var stroke_opacity = %f;\
var use_dashed = %d;\
var dashtype0 = %d;\
var dashtype1 = %d;\
var x0,y0;\
function user_draw(evt){\
 var lu = userdraw_x.length;\
 if( lu != 0 && lu%%2 == 0){\
  draw_lines(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
 }\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 var x = mouse.x;\
 var y = mouse.y;\
 if( use_snap_to_points != 0 ){\
  var xy = new Array(2);\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x,y);\
  }\
  else\
  {\
   xy = snap_to_fun(x,y);\
  };\
  x = xy[0];y = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
 };\
 if( evt.which == 1 || evt.identifier == 0 ){\
  if( lu%%2 == 0){\
   x0 = x;y0 = y;\
   if(num == 1){ userdraw_x = [];userdraw_y = [];userdraw_x[0] = x0;userdraw_y[0] = y0;} else {userdraw_x[lu] = x0;userdraw_y[lu] = y0;}\
   draw_circles(context_userdraw,[x0],[y0],[line_width],line_width,stroke_color,stroke_opacity,1,stroke_color,stroke_opacity,0,1,1);\
   user_drag(evt);\
  }\
  else\
  {\
   if( num == 1 ){ userdraw_x[1] = x;userdraw_y[1] = y;} else {userdraw_x[lu] = x;userdraw_y[lu] = y;};\
   draw_lines(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
  };\
 }\
 else\
 {\
  canvas_remove(x,y);\
 };\
};\
function user_drag(evt){\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 var x = mouse.x;\
 var y = mouse.y;\
 var lu = userdraw_x.length;\
 if( use_snap_to_points != 0 ){\
  var xy = new Array(2);\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x,y);\
  }\
  else\
  {\
   xy = snap_to_fun(x,y);\
  };\
  x = xy[0];y = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
 };\
 if( lu%%2 != 0 ){\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_circles(context_userdraw,[x0],[y0],[line_width],line_width,stroke_color,stroke_opacity,1,stroke_color,stroke_opacity,0,1,1);\
  draw_circles(context_userdraw,[x],[y],[line_width],line_width,stroke_color,stroke_opacity,1,stroke_color,stroke_opacity,0,1,1);\
  draw_lines(context_userdraw,[x0,x],[y0,y],line_width,stroke_color,stroke_opacity);\
  if( lu > 0){\
   draw_lines(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
  }\
 }\
};\
function canvas_remove(x,y){\
 var marge = 10*line_width;\
 for(var p = 0;p < userdraw_x.length ; p++){\
  if(userdraw_x[p] < x + marge && userdraw_x[p] > x - marge ){\
   if(userdraw_y[p] < y + marge && userdraw_y[p] > y - marge ){\
    if( confirm(\"remove line ?\" )){\
     context_userdraw = null;context_userdraw = canvas_userdraw.getContext(\"2d\");context_userdraw.clearRect(0,0,xsize,ysize);\
     if( p%%2 == 0 ){\
      userdraw_x.splice(p,2);userdraw_y.splice(p,2);\
     }\
     else\
     {\
      userdraw_x.splice(p-1,2);userdraw_y.splice(p-1,2);\
     }\
     xy_cnt--;\
     if(userdraw_x.length < 2){ userdraw_x = [];userdraw_y = [];return;};\
     draw_lines(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
    }\
    return;\
   }\
  }\
 }\
};",draw_type,num,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);
}


void add_js_arrows(FILE *js_include_file,int num,char *draw_type,int line_width,int type, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1,int arrow_head){
/*
constants in draw_arrows() ... for this moment: ;var use_rotate = 0;var angle = 0;var use_translate = 0 ;var vector = [0,0];\
*/
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on final canvas -->\n\
var num = %d;\
var line_width = %d;\
var stroke_color = \"%s\";\
var stroke_opacity = %f;\
var use_dashed = %d;\
var dashtype0 = %d;\
var dashtype1 = %d;\
var arrow_head = %d;\
var x0,y0;\
var type = %d;\
var use_rotate = 0;var angle = 0;var use_translate = 0 ;var vector = [0,0];\
function user_draw(evt){\
 var lu = userdraw_x.length;\
 if( lu != 0 && lu%%2 == 0){\
  draw_arrows(context_userdraw,userdraw_x,userdraw_y,arrow_head,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,type,use_rotate,angle,0,[1,0,0,1,0,0]);\
 }\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 var x = mouse.x;\
 var y = mouse.y;\
 if( use_snap_to_points != 0 ){\
  var xy = new Array(2);\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x,y);\
  }\
  else\
  {\
   xy = snap_to_fun(x,y);\
  };\
  x = xy[0];y = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
 };\
 if( evt.which == 1 || evt.identifier == 0 ){\
  if( lu%%2 == 0){\
   x0 = x;y0 = y;\
   if(num == 1){ userdraw_x = [];userdraw_y = [];userdraw_x[0] = x0;userdraw_y[0] = y0;} else {userdraw_x[lu] = x0;userdraw_y[lu] = y0;}\
   user_drag(evt);\
  }\
  else\
  {\
   if( num == 1 ){ userdraw_x[1] = x;userdraw_y[1] = y;} else {userdraw_x[lu] = x;userdraw_y[lu] = y;};\
   draw_arrows(context_userdraw,userdraw_x,userdraw_y,arrow_head,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,type,use_rotate,angle,0,[1,0,0,1,0,0]);\
  };\
 }\
 else\
 {\
  canvas_remove(x,y);\
 };\
};\
function user_drag(evt){\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 var x = mouse.x;\
 var y = mouse.y;\
 var lu = userdraw_x.length;\
 if( use_snap_to_points != 0 ){\
  var xy = new Array(2);\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x,y);\
  }\
  else\
  {\
   xy = snap_to_fun(x,y);\
  };\
  x = xy[0];y = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
 };\
 if( lu%%2 != 0 ){\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_arrows(context_userdraw,[x0,x],[y0,y],arrow_head,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,type,use_rotate,angle,0,[1,0,0,1,0,0]);\
  if( lu > 0){\
    draw_arrows(context_userdraw,userdraw_x,userdraw_y,arrow_head,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,type,use_rotate,angle,0,[1,0,0,1,0,0]);\
  }\
 }\
};\
function canvas_remove(x,y){\
 var marge = 10*line_width;\
 for(var p = 0;p < userdraw_x.length ; p++){\
  if(userdraw_x[p] < x + marge && userdraw_x[p] > x - marge ){\
   if(userdraw_y[p] < y + marge && userdraw_y[p] > y - marge ){\
    if( confirm(\"remove line ?\" )){\
     context_userdraw = null;context_userdraw = canvas_userdraw.getContext(\"2d\");context_userdraw.clearRect(0,0,xsize,ysize);\
     if( p%%2 == 0 ){\
      userdraw_x.splice(p,2);userdraw_y.splice(p,2);\
     }\
     else\
     {\
      userdraw_x.splice(p-1,2);userdraw_y.splice(p-1,2);\
     }\
     xy_cnt = xy_cnt - 2;\
     if(userdraw_x.length < 2){ userdraw_x = [];userdraw_y = [];return;};\
     draw_arrows(context_userdraw,userdraw_x,userdraw_y,arrow_head,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,type,use_rotate,angle,0,[1,0,0,1,0,0],type,use_rotate,angle,0,[1,0,0,1,0,0]);\
    }\
    return;\
   }\
  }\
 }\
};",draw_type,num,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,arrow_head,type);

}

void add_js_paths(FILE *js_include_file,int num,char *draw_type,int line_width, int closed_path,char *stroke_color,double stroke_opacity,int use_filled, char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on final canvas -->\n\
var path_cnt = 0;\
var temp_x = [];\
var temp_y = [];\
var num = %d;\
xy_cnt=0;\
var line_width = %d;\
var stroke_color = \"%s\";\
var stroke_opacity = %f;\
var fill_color = \"%s\";\
var fill_opacity = %f;\
var use_filled = %d;\
var use_dashed = %d;\
var dashtype0 = %d;\
var dashtype1 = %d;\
var closed_path = 0;\
var click_cnt=0;\
function user_draw(evt){\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 var x = mouse.x;\
 var y = mouse.y;\
 if( use_snap_to_points != 0 ){\
  var xy = new Array(2);\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x,y);\
  }\
  else\
  {\
   xy = snap_to_fun(x,y);\
  };\
  x = xy[0];y = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
 };\
 if(evt.which == 1 || evt.identifier == 0){\
  if( click_cnt == 0 ){\
   click_cnt = 1;\
   user_drag(evt);\
  }\
  else\
  {\
   userdraw_x[path_cnt] = new Array();\
   userdraw_y[path_cnt] = new Array();\
   userdraw_x[path_cnt] = temp_x;\
   userdraw_y[path_cnt] = temp_y;\
   path_cnt++;\
   temp_x = [];\
   temp_y = [];\
   click_cnt = 0;\
   xy_cnt = 0;\
  };\
 }\
 else\
 {\
   canvas_remove(x,y);\
 };\
 context_userdraw.clearRect(0,0,xsize,ysize);\
 for(var p=0; p < path_cnt; p++){\
  if(userdraw_x[p] != null){\
   draw_paths(context_userdraw,userdraw_x[p],userdraw_y[p],line_width,0,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);\
  };\
 };\
};\
function user_drag(evt){\
 if(click_cnt == 1 ){\
  var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
  temp_x[xy_cnt] = mouse.x;\
  temp_y[xy_cnt] = mouse.y;\
  if( x_use_snap_to_grid == 1 ){\
   temp_x[xy_cnt] = snap_to_x(temp_x[xy_cnt]);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   temp_y[xy_cnt] = snap_to_y(temp_y[xy_cnt]);\
  };\
  xy_cnt++;\
  draw_paths(context_userdraw,temp_x,temp_y,line_width,0,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);\
 };\
};\
function canvas_remove(x,y){\
 var marge = 4*line_width;\
 var tmpx = [];\
 var tmpy = [];\
 for(var i = 0 ; i < path_cnt; i++){\
  tmpx = userdraw_x[i];\
  if(tmpx != null){\
   tmpy = userdraw_y[i];\
   for(var p = 0;p<tmpx.length;p++){\
    if( x + marge > tmpx[p] &&  x - marge < tmpx[p] ){\
     if( y + marge > tmpy[p] &&  y - marge < tmpy[p] ){\
      if(confirm(\"Remove this drawing ?\")){\
       userdraw_x[i] = null;\
       userdraw_y[i] = null;\
       xy_cnt = 0;click_cnt = 0;\
       return;\
      };\
     };\
    };\
   };\
  };\
 };\
};",draw_type,num,line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_filled,use_dashed,dashtype0,dashtype1);
}

void add_js_popup(int canvas_root_id,int xsize,int ysize,char *getfile_cmd){
fprintf(stdout,"\n<!-- begin command popup %d -->\n\
<script type=\"text/javascript\">\n\
if( wims_status != 'done'){\n\
 var popup = window.open('','','toolbar=no,scrollbars=yes,menubar=no,location=no,resizable=yes,top=4,left=4,status=no, width = %dpx, height = %dpx');\n\
 var popupHTML =\"<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN' 'http://www.w3.org/TR/html4/loose.dtd'>\\n<html><head></head>\\n<body><div style='width:%dpx;height:%dpx;position:relative' id='canvas_div%d'></div><div id='tooltip_placeholder_div%d' style='display:block;position:relative;margin-left:auto;margin-right:auto;margin-bottom:4px;'><span id='tooltip_placeholder%d' style='display:none;'></span></div></body></html>\";\n\
 popup.document.write(popupHTML);\n\
 var s0 = popup.document.createElement(\"script\");\n\
 s0.text=\"var wims_status = window.opener.wims_status; var use_dragdrop_reply = window.opener.use_dragdrop_reply;window.opener.canvas_scripts.push('%d');\";\n\
 popup.document.getElementsByTagName(\"HEAD\")[0].appendChild(s0);\n\
 var s1 = popup.document.createElement(\"script\");\n\
 s1.type = \"text/javascript\";\n\
 s1.src = \"%s\"\n\
 popup.document.getElementsByTagName(\"HEAD\")[0].appendChild(s1);\n\
 popup.document.close();\n\
 }else{\n\
 var canvas_div = document.getElementById('canvas_div%d');\n\
 canvas_div.style.display='block';\n\
 };\n\
 \n</script>\n\
 <!-- end command popup %d -->\n",
canvas_root_id,
xsize+40,ysize+40,
xsize,ysize,
canvas_root_id,
canvas_root_id,
canvas_root_id,
canvas_root_id,
getfile_cmd,
canvas_root_id,
canvas_root_id);
}

void add_js_tooltip(int canvas_root_id,char *tooltip_text,char *bgcolor,int xsize,int ysize){
fprintf(stdout,"\n<!-- begin command intooltip %d -->\n\
<script type=\"text/javascript\">\n\
var xsize = %d;\
var ysize = %d;\
var tooltip%d_obj_x = 0;\
var tooltip%d_obj_y = 0;\
var tooltip%d_flipflop = 0;\
var tooltip%d_obj = document.getElementById(\"canvas_div%d\");\
tooltip%d_obj.style.display=\"none\";\
tooltip%d_obj.style.position=\"absolute\";\
var tooltip%d_link = document.createElement(\"a\");\
tooltip%d_link.addEventListener(\"mousemove\",tooltip%d_drag,false);\
tooltip%d_link.setAttribute(\"onclick\",\"tooltip%d_show()\");\
tooltip%d_link.innerHTML  = \"%s\";\
var tooltip_placeholder = document.getElementById(\"tooltip_placeholder%d\");\
tooltip_placeholder.style.display=\"block\";\
tooltip_placeholder.style.position=\"absolute\";\
tooltip_placeholder.style.backgroundColor=\"%s\";\
tooltip_placeholder.appendChild(tooltip%d_link);\
function tooltip%d_drag(action){\
 if(!action){ action = event; }\
 if(action.clientX){\
  tooltip%d_obj.style.left = (tooltip%d_mouseX(action) + 10) +\"px\";\
  var ytop = tooltip%d_mouseY(action);\
  if(ytop + ysize < window.innerHeight){\
   tooltip%d_obj.style.top = (ytop - 10) +\"px\";\
  }\
  else\
  {\
   tooltip%d_obj.style.top = parseInt(ytop - 0.8*ysize) +\"px\";\
  }\
 }\
 else\
 {\
  return null;\
 }\
}\
function tooltip%d_mouseX(action){\
 if(action.pageX){\
  return action.pageX;\
 }\
 else\
 {\
  if(action.clientX){\
   return action.clientX + (document.documentElement.scrollLeft ? document.documentElement.scrollLeft : document.body.scrollLeft);\
  }\
  else\
  {\
   return null;\
  }\
 }\
}\
function tooltip%d_mouseY(action){\
 if(action.pageY){\
  return action.pageY;\
 }\
 else\
 {\
  if(action.clientY){\
   return action.clientY + (document.documentElement.scrollTop ? document.documentElement.scrollTop :document.body.scrollTop);\
  }\
  else\
  {\
   return null;\
  }\
 }\
}\
function tooltip%d_show(){\
 if(tooltip%d_flipflop == 0){\
  tooltip%d_obj.style.display = \"block\";\
  tooltip%d_flipflop = 1;\
 }\
 else\
 {\
  tooltip%d_flipflop = 0;\
  tooltip%d_obj.style.display = \"none\";\
 }\
};\n</script>\n<!-- end command intooltip %d -->\n",canvas_root_id,xsize,ysize,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,tooltip_text,canvas_root_id,bgcolor,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id);

}

void add_js_arc(FILE *js_include_file,int canvas_root_id,int num,int line_width,char *stroke_color,double stroke_opacity,char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1){
fprintf(js_include_file,"\n<!-- begin userdraw \"arc\" on final canvas -->\n\
var canvas_rect;\
function user_draw(evt){\
 var num = %d;\
 var x,xc,x1,x2,y,yc,y1,y2;var lu = userdraw_x.length;\
 if( num == 1 && lu == 3 ){ userdraw_x = [];userdraw_y = [];userdraw_radius = [];};\
 if(evt.which == 1 || evt.identifier == 0 ){\
  var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
  x = mouse.x;\
  y = mouse.y;\
  if( use_snap_to_points != 0 ){\
   var xy = new Array(2);\
   if( use_snap_to_points == 1 ){\
    xy = snap_to_points(x,y);\
   }\
   else\
   {\
    xy = snap_to_fun(x,y);\
   };\
   x = xy[0];y = xy[1];\
  }\
  else\
  {\
   if( x_use_snap_to_grid == 1 ){x = snap_to_x(x);};\
   if( y_use_snap_to_grid == 1 ){y = snap_to_y(y);};\
  };\
  if(num == 1 && lu == 3){userdraw_x = [];userdraw_y = [];userdraw_radius = [];};\
  lu = userdraw_x.push(x);userdraw_y.push(y);\
  if( lu != 0 && lu%%3 == 0){\
   context_userdraw.clearRect(0,0,xsize,ysize);\
   userdraw_radius = [];\
   for(var p = 0 ; p < lu; p = p + 3){\
     xc = userdraw_x[p];\
     yc = userdraw_y[p];\
     x1 = userdraw_x[p+1];\
     x2 = userdraw_x[p+2];\
     y1 = userdraw_y[p+1];\
     y2 = userdraw_y[p+2];\
     draw_userarc(context_userdraw,xc,yc,x1,y1,x2,y2,%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d);\
   };\
  };\
 }\
 else\
 {\
  if( confirm(\"remove drawing ?\") ){\
   context_userdraw.clearRect(0,0,xsize,ysize);userdraw_x = [];userdraw_y = [];userdraw_radius = [];return;\
  };\
 };\
};\
function user_drag(evt){ \
 var lu = userdraw_x.length;\
 if( (lu+1)%%3 == 0) {\
  var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
  var x2 = mouse.x;\
  var y2 = mouse.y;\
  var xc = userdraw_x[lu-2];\
  var yc = userdraw_y[lu-2];\
  var x1 = userdraw_x[lu-1];\
  var y1 = userdraw_y[lu-1];\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_userarc(context_userdraw,xc,yc,x1,y1,x2,y2,1,\"255,0,0\",0.6,\"255,255,0\",0.4,0,2,2);\
 };\
 return;\
};\
var draw_userarc = function(ctx,xc,yc,x1,y1,x2,y2,line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1){\
 ctx.save();\
 if( use_dashed == 1){if(ctx.setLineDash){ctx.setLineDash([dashtype0,dashtype1]);}else{if(ctx.mozDash){ ctx.mozDash = [dashtype0,dashtype1];};};};\
 ctx.lineWidth = line_width;\
 ctx.strokeStyle =  \"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 ctx.fillStyle = \"rgba(\"+fill_color+\",\"+fill_opacity+\")\";\
 var alpha = find_angle(xc,yc,x2,y2);\
 if( %d == 1 ){userdraw_radius[0] = alpha;ctx.clearRect(0,0,xsize,ysize);}else{userdraw_radius.push(alpha);};\
 var r = Math.sqrt(Math.pow(xc-x2,2)+Math.pow(yc-y2,2));\
 var start = find_angle(xc,yc,x1,y1);\
 ctx.translate(xc,yc);\
 ctx.rotate(start);\
 ctx.beginPath();\
 ctx.arc(0,0,r,0,alpha,false);\
 ctx.lineTo(0,0);\
 ctx.closePath();\
 ctx.fill();\
 ctx.stroke();\
 ctx.restore();\
};",num,line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,num);
}

void add_js_text(FILE *js_include_file,int canvas_root_id,int font_size,char *font_family,char *font_color,double stroke_opacity){
fprintf(js_include_file,"\n<!-- begin command userdraw text -->\n\
canvas_div.addEventListener(\"keydown\",function(e){ e.preventDefault();user_text(e);},false);\
context_userdraw = canvas_userdraw.getContext(\"2d\");\
var font_color = \"%s\";\
var font_opacity = %f;\
var mask_opacity = 0.5*font_opacity;\
var font_size = %d;\
var font_family = \"%s\";\
context_userdraw.fillStyle = \"rgba(\"+font_color+\",\"+font_opacity+\")\";\
context_userdraw.font = font_family;\
context_userdraw.save();\
var tmp_font_size = parseInt(context_userdraw.measureText(\"m\").width);\
if( font_size > tmp_font_size ){context_userdraw.font = font_size+\"px Ariel\";};\
var userdraw_text = new Array();\
var temp_userdraw_txt=\"\";\
var x_txt = 0;\
var y_txt = 0;\
function user_draw(evt){\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 x_txt = mouse.x;\
 y_txt = mouse.y;\
 if( use_snap_to_points != 0 ){\
  var xy = new Array(2);\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x_txt,y_txt);\
  }\
  else\
  {\
   xy = snap_to_fun(x_txt,y_txt);\
  };\
  x_txt = xy[0];y_txt = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
   x_txt = snap_to_x(x_txt);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y_txt = snap_to_y(y_txt);\
  };\
 };\
 return;\
};\
function user_drag(evt){return;};\
function redraw_all_user_text(){\
 var len = userdraw_x.length;\
 context_userdraw.clearRect(0,0,xsize,ysize);\
 for(var p = 0 ; p < len ; p++){\
  context_userdraw.fillText(userdraw_text[p],userdraw_x[p],userdraw_y[p]);\
 };\
};\
function user_text(evt){\
 var kc = evt.keyCode;\
 if( kc== 8 || kc == 27 || kc == 46 ){\
  var len = userdraw_x.length;\
  for( var p=0 ; p < len ; p++){\
   var tmp = userdraw_text[p];\
   var w = context_userdraw.measureText(tmp).width;\
   if( y_txt <= userdraw_y[p] && y_txt > userdraw_y[p] - font_size){\
    if( x_txt < userdraw_x[p] + w && x_txt > userdraw_x[p] ){\
     if (confirm(\"delete : \"+tmp+\"?\")){\
      userdraw_text.splice(p,1);\
      userdraw_x.splice(p,1);\
      userdraw_y.splice(p,1);\
      temp_userdraw_txt = \"\";\
      redraw_all_user_text();\
      return;\
     };\
    };\
   };\
  };\
 }\
 else\
 {\
  if( kc < 126 && kc > 40 ){\
   temp_userdraw_txt=temp_userdraw_txt+String.fromCharCode(kc);\
   context_userdraw.save();\
   context_userdraw.fillStyle = \"rgba(\"+font_color+\",\"+mask_opacity+\")\";\
   context_userdraw.fillText(temp_userdraw_txt,x_txt,y_txt);\
   context_userdraw.restore();\
  }\
  else\
  {\
   if(kc == 13 ){\
    w = context_userdraw.measureText(temp_userdraw_txt).width;\
    if(w < 1){ return;};\
    userdraw_x.push(x_txt);\
    userdraw_y.push(y_txt);\
    userdraw_text.push(temp_userdraw_txt);\
    redraw_all_user_text();\
    temp_userdraw_txt=\"\";\
    return;\
   };\
  };\
 };\
};",font_color,stroke_opacity,font_size,font_family);

}

/*

type = 0 : x-values only [command mousex]
type = 1 : y-values only [command mousey]
type = 2 : (x:y) 	 [command mouse]
type = 3 : degree	 [command mouse_degree]
type = 4 : radian
type = 5 : radius

  var mouse = dragstuff.getMouse(evt,canvas_div);\
  var x = evt.clientX - mouse_canvas_rect.left;\
  var y = evt.clientY - mouse_canvas_rect.top;\

*/
void add_js_mouse(FILE *js_include_file,int canvas_cnt,int canvas_root_id,int precision,char *stroke_color,int font_size,double stroke_opacity,int type){
fprintf(js_include_file,"\n<!-- begin command mouse on mouse canvas -->\n\
function use_mouse_coordinates(){\
 var display_type = %d;\
 var canvas_type = %d;\
 var mouse_canvas = create_canvas%d(canvas_type,xsize,ysize);\
 var mouse_context = mouse_canvas.getContext(\"2d\");\
 mouse_canvas.addEventListener(\"mousemove\",show_coordinate%d,false);\
 mouse_canvas.addEventListener(\"touchmove\", function(e){ e.preventDefault();show_coordinate%d(e.changedTouches[0]);},false);\
 var prec = Math.log(%d)/(Math.log(10));\
 function show_coordinate%d(evt){\
  var mouse = dragstuff.getMouse(evt,mouse_canvas);\
  var x = mouse.x;\
  var y = mouse.y;\
  var m_data = \"\";\
  switch(display_type){\
   case 0: m_data = \" \"+(px2x(x)).toFixed(prec)+\" \"+unit_x;break;\
   case 1: m_data = \" \"+(px2y(y)).toFixed(prec)+\" \"+unit_y;break;\
   case 2: m_data = \"(\"+(px2x(x)).toFixed(prec)+\":\"+(px2y(y)).toFixed(prec)+\")\";break;\
   case 3: if(userdraw_radius[0]){ m_data = \" \"+( ( userdraw_radius[0])/(Math.PI/180) ).toFixed(prec)+\" \\u00B0 \";};break;\
   case 4: if(userdraw_radius[0]){ m_data = \" \"+(userdraw_radius[0]).toFixed(prec)+\" rad \";};break;\
   case 5: if( userdraw_x.length > 0 ){ m_data = \" R = \"+((xmax - xmin)*(distance(x,y,userdraw_x[l-1],userdraw_y[l-1]))/xsize).toFixed(prec)+\" \"+unit_x;};break;\
   default:break;\
  };\
  var s = parseInt(0.8*%d*(m_data.toString()).length);\
  mouse_context.font = \"%dpx Ariel\";\
  mouse_context.fillStyle = \"rgba(%s,%f)\";\
  mouse_context.clearRect(0,0,s,1.2*%d);\
  mouse_context.fillText(m_data,0,%d);\
 };\
};",type,MOUSE_CANVAS,canvas_root_id,canvas_root_id,canvas_root_id,precision,canvas_root_id,font_size,font_size,stroke_color,stroke_opacity,font_size,font_size);
}
/* to avoid easy js-code injection...but is it a real problem ? */
void add_safe_eval(FILE *js_include_file){
fprintf(js_include_file," \nfunction safe_eval(exp){\
 exp = exp.replace(/pi/g,'3.14159');\
 if(exp.indexOf('^') != -1){\
  exp = exp.replace(/[a-zA-Z]/g,' ');\
  exp = exp.replace(/\\*10\\^-/g,'e-');\
  exp = exp.replace(/\\*10\\^/g,'e+');\
  exp = exp.replace(/10\\^-/g,'1e-');exp = exp.replace(/10\\^/g,'1e+');\
  exp = eval(exp);\
  if(isNaN(exp)){alert(\"invalid input\\ntry just a real number \\ne.g. no calculations...\");return null;}\
  return exp;\
 };\
 var reg = /(?:[a-z$_][a-z0-9$_]*)|(?:[;={}\\[\\]\"'!&<>^\\\\?:])/ig;\
 var valid = true;\
 exp = exp.replace(reg,function($0){\
  if(Math.hasOwnProperty($0)){\
   return \"Math.\"+$0;\
  }\
  else\
  {\
   valid = false;\
  }\
 }\
 );\
 if( !valid ){\
  alert(\"hmmm \"+exp+\" ?\"); exp = null;\
 }\
 else\
 {\
  try{ exp = eval(exp); } catch(e){alert(\"Invalid arithmetic expression\"); exp = null;};\
 };\
 return exp;\
};");
}

/*
add display of slider value in mouse context
use_slider_display = 1 : x/y -values
use_slider_display = 10 : x-values only
use_slider_display = 11 : y-values only

use_slider_display = 2 : angle in degrees
use_slider_display = 3 : angle in radians
*/
void add_slider_display(FILE *js_include_file,int canvas_root_id,int precision,int font_size,char *font_color,double stroke_opacity){
fprintf(js_include_file,"<!-- begin add_slider_display -->\n\
function show_slider_value(value,use_slider_display){\
 var current_canvas = create_canvas%d(%d,xsize,ysize);\
 var current_context = current_canvas.getContext(\"2d\");\
 current_context.clearRect(0,0,xsize,ysize);\
 var prec = Math.log(%d)/(Math.log(10));\
 var string;\
 switch(use_slider_display){\
  case 1: string = \" \"+value[0].toFixed(prec)+\" \"+unit_x+\":\"+value[1].toFixed(prec)+\" \"+unit_y; break;\
  case 10: string = \" \"+value[0].toFixed(prec)+\" \"+unit_x; break;\
  case 11: string = \" \"+value[1].toFixed(prec)+\" \"+unit_y; break;\
  case 2: value[1] = value[1]*180/Math.PI;string = \" \"+value[1].toFixed(prec)+\"\\u00B0\";break;\
  case 3: string = \" \"+value[1].toFixed(prec)+\" rad\";break;\
  default: string = \" \";break;\
 };\
 var s = parseInt(1.2*%d*(string).length);\
 current_context.font = \"%dpx Ariel\";\
 current_context.strokeStyle = \"rgba(%s,%.2f)\";\
 current_context.clearRect(0,0,s,1.2*%d);\
 current_context.fillText(string,0,%d);\
};\n",canvas_root_id,MOUSE_CANVAS,precision,font_size,font_size,font_color,stroke_opacity,font_size,font_size);
}
/*
add slider
return value is array : value[0] is the actual value between value_1 and value_2

 var x_px = evt.clientX\
*/
void add_slider(FILE *js_include_file,int canvas_root_id,double v1,double v2,int width,int height,int type,char *label,int slider_cnt,char *stroke_color,char *fill_color,int line_width,double opacity,char *font_family,char *font_color,int use_slider_display){
fprintf(js_include_file,"\n<!-- begin add_slider no. %d -->\n\
function add_slider_%d(){\
 if( wims_status == \"done\" ){return;};\
 var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
 var slider_type = %d;\
 var span = document.createElement(\"span\");\
 span.setAttribute(\"style\",\"font:%s;color:%s\");\
 var title = document.createTextNode(\" %s \");\
 var br = document.createElement(\"br\");\
 span.appendChild(title);\
 span.appendChild(br);\
 tooltip_div.appendChild(span);\
 var slider_fillcolor = \"%s\";\
 var slider_strokecolor = \"%s\";\
 var slider_linewidth = \"%d\";\
 var slider_canvas = document.createElement(\"canvas\");\
 slider_canvas.id = \"slider_canvas%d\";\
 tooltip_div.appendChild(slider_canvas);\
 br = document.createElement(\"br\");\
 tooltip_div.appendChild(br);\
 var slider_width = %d;\
 var slider_height = %d;\
 var slider_center = %d;\
 var slider_radius = 2*slider_linewidth;\
 var slider_opacity = %f;\
 slider_canvas.width = slider_width;\
 slider_canvas.height = slider_height;\
 var slider_ctx = slider_canvas.getContext(\"2d\");\
 slider_ctx.font = \"%s\";\
 slider_ctx.strokeStyle = \"rgba(\"+slider_strokecolor+\",\"+slider_opacity+\")\";\
 slider_ctx.fillStyle = \"rgba(\"+slider_fillcolor+\",\"+slider_opacity+\")\";\
 slider_ctx.lineWidth = slider_linewidth;\
 slider_ctx.beginPath();\
 slider_ctx.arc(10,slider_center,slider_radius,0,2*Math.PI,false);\
 slider_ctx.moveTo(10,slider_center);\
 slider_ctx.lineTo(slider_width-10,slider_center);\
 slider_ctx.rect(0,0,slider_width,slider_height);\
 slider_ctx.closePath();\
 slider_ctx.fill();\
 slider_ctx.stroke();\
 slider_canvas.addEventListener(\"mousemove\",slider_%d,false);\
 slider_canvas.addEventListener(\"touchmove\", function(e){ e.preventDefault();slider_%d(e.changedTouches[0]);},false);\
function slider_%d(evt){\
 var value_1 = %f;\
 var value_2 = %f;\
 var canvas_rect = (slider_canvas).getBoundingClientRect();\
 slider_ctx.clearRect(0,0,slider_width,slider_height);\
 var x_px = evt.clientX - canvas_rect.left;\
 var x;var y;\
 if( slider_type == 1 ){\
  x = x_px*(value_2 - value_1)/slider_width + value_1;\
  y = 0;\
 }else{\
  y = x_px*(value_2 - value_1)/slider_width + value_1;\
  x = 0;\
 };\
 slider_ctx.beginPath();\
 slider_ctx.arc(x_px,slider_center,slider_radius,0,2*Math.PI,false);\
 slider_ctx.moveTo(10,slider_center);\
 slider_ctx.lineTo(slider_width-10,slider_center);\
 slider_ctx.rect(0,0,slider_width,slider_height);\
 slider_ctx.closePath();\
 slider_ctx.fill();\
 slider_ctx.stroke();\
 dragstuff.Slide( [x,y] , %d );\
 if(%d != 0 ){show_slider_value([x,y],%d);};\
 return;\
 };\
};\
add_slider_%d();\n",slider_cnt,slider_cnt,canvas_root_id,type,font_family,font_color,label,fill_color,stroke_color,line_width,slider_cnt,width,height,(int)(0.5*height),opacity,font_family,slider_cnt,slider_cnt,slider_cnt,v1,v2,slider_cnt,use_slider_display,use_slider_display,slider_cnt);
}


/*
add xyslider
 return value is array : value[0] is the actual x-value between value_1 and value_2, value[1] is y-value between value_1 and value_2
*/
void add_xyslider(FILE *js_include_file, int canvas_root_id,double v1,double v2,int width,int height,int type,char *label,int slider_cnt,char *stroke_color,char *fill_color,int line_width,double opacity,char *font_family,char *font_color,int use_slider_display){
fprintf(js_include_file,"\n<!-- begin add_slider no. %d -->\n\
function add_slider_%d(){\
 if( wims_status == \"done\" ){return;};\
 var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
 var slider_type = %d;\
 var span = document.createElement(\"span\");\
 span.setAttribute(\"style\",\"font:%s;color:%s\");\
 var title = document.createTextNode(\" %s \");\
 var br = document.createElement(\"br\");\
 span.appendChild(title);\
 span.appendChild(br);\
 tooltip_div.appendChild(span);\
 var slider_fillcolor = \"%s\";\
 var slider_click = 0;\
 var slider_strokecolor = \"%s\";\
 var slider_linewidth = \"%d\";\
 var slider_canvas = document.createElement(\"canvas\");\
 slider_canvas.id = \"slider_canvas%d\";\
 tooltip_div.appendChild(slider_canvas);\
 br = document.createElement(\"br\");\
 tooltip_div.appendChild(br);\
 var slider_width = %d;\
 var slider_height = %d;\
 var slider_center = %d;\
 var slider_radius = 4*slider_linewidth;\
 var slider_opacity = %f;\
 slider_canvas.width = slider_width;\
 slider_canvas.height = slider_height;\
 var slider_ctx = slider_canvas.getContext(\"2d\");\
 slider_ctx.font = \"%s\";\
 slider_ctx.strokeStyle = \"rgba(\"+slider_strokecolor+\",\"+slider_opacity+\")\";\
 slider_ctx.fillStyle = \"rgba(\"+slider_fillcolor+\",\"+slider_opacity+\")\";\
 slider_ctx.lineWidth = slider_linewidth;\
 slider_ctx.beginPath();\
 slider_ctx.arc(10,slider_center,slider_radius,0,2*Math.PI,false);\
 slider_ctx.fill();\
 slider_ctx.closePath();\
 slider_ctx.rect(0,0,slider_width,slider_height);\
 slider_ctx.stroke();\
 slider_canvas.addEventListener(\"mousemove\",sliderdrag_%d,false);\
 slider_canvas.addEventListener(\"mousedown\",sliderclick_%d,false);\
 slider_canvas.addEventListener(\"touchmove\",function(e){ e.preventDefault();sliderdrag_%d(e.changedTouches[0]);},false);\
 slider_canvas.addEventListener(\"touchstart\", function(e){ e.preventDefault();sliderclick_%d(e.changedTouches[0]);},false);\
 var canvas_rect = (slider_canvas).getBoundingClientRect();\
function sliderdrag_%d(evt){\
 if(slider_click == 1){\
  var value_1 = %f;\
  var value_2 = %f;\
  var canvas_rect = (slider_canvas).getBoundingClientRect();\
  slider_ctx.clearRect(0,0,slider_width,slider_height);\
  var x_px = evt.clientX - canvas_rect.left;\
  var y_px = evt.clientY - canvas_rect.top;\
  slider_ctx.clearRect(0,0,slider_width,slider_height);\
  var x = x_px*(value_2 - value_1)/slider_width + value_1;\
  var y = y_px*(value_2 - value_1)/slider_height + value_1;\
  x = parseFloat(eval(slider_function%d.x));\
  y = parseFloat(eval(slider_function%d.y));\
  slider_ctx.beginPath();\
  slider_ctx.arc(x_px,y_px,slider_radius,0,2*Math.PI,false);\
  slider_ctx.fill();\
  slider_ctx.rect(0,0,slider_width,slider_height);\
  slider_ctx.closePath();\
  slider_ctx.stroke();\
  dragstuff.Slide( [x,y] , %d );\
  if(%d != 0 ){show_slider_value([x,y],%d);}\
 };\
};\
function sliderclick_%d(evt){\
  if(slider_click == 1){slider_click = 0;}else{slider_click = 1;};\
};\
};\n\
add_slider_%d();",slider_cnt,slider_cnt,canvas_root_id,type,font_family,font_color,label,fill_color,stroke_color,line_width,canvas_root_id,width,height,(int)(0.5*height),opacity,font_family,slider_cnt,slider_cnt,slider_cnt,slider_cnt,slider_cnt,v1,v2,slider_cnt,slider_cnt,slider_cnt,use_slider_display,slider_cnt,slider_cnt,slider_cnt);
}


/*
adds inputfield for x-value: returns the js-calculated y-value after click on 'OK' button
draws a non-configurable crosshair on this calculated location
*/
void add_calc_y(FILE *js_include_file,int canvas_root_id,char *jsmath,int font_size,char *input_style){
fprintf(js_include_file,"\n<!-- begin add_calc_y -->\n\
use_jsmath=1;\
function add_calc_y(){\
 if( wims_status == \"done\" ){return;};\
 var fun = to_js_math(\"%s\");if(fun == null){return;};\
 function eval_jsmath(x){return parseFloat(eval(fun));};\
 var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
 var calc_div = document.createElement('div');\
 calc_div.id = \"calc_div\";\
 tooltip_div.appendChild(calc_div);\
 var label_x = \"x\";var label_y = \"y\";\
 if( typeof(xaxislabel) !== 'undefined' ){label_x = xaxislabel;}\
 if( typeof(yaxislabel) !== 'undefined' ){label_y = yaxislabel;}\
 calc_div.innerHTML=\"<br /><span style='font-style:italic;font-size:%dpx'>\"+label_x+\" : <input type='text' size='4' value='' id='calc_input_x' style='%s' />&nbsp;\"+ label_y+\" : <input type='text' size='5' value='' id='calc_output_y' style='%s' readonly /><input id='calc_button' type='button' value='OK' onclick=''  style='color:red;background-color:lightblue;' /></span> \";\
 var calc_button = document.getElementById(\"calc_button\");\
 calc_button.addEventListener(\"mousedown\",show_it,false);\
 calc_button.addEventListener(\"touchstart\", function(e){ e.preventDefault();show_it(e.changedTouches[0]);},false);\
 function show_it(){\
  var x_value=document.getElementById(\"calc_input_x\").value;\
  var y_value = eval_jsmath(x_value);\
  document.getElementById(\"calc_output_y\").value = y_value;\
  if(isNaN(y_value)){return;};\
  var canvas = create_canvas%d(123,xsize,ysize);\
  var ctx = canvas.getContext(\"2d\");\
  draw_crosshairs(ctx,[x2px(x_value)],[y2px(y_value)],1,5,\"#000000\",1,0,0,0,[0,0]);return;\
 };\
};\
;add_calc_y();",jsmath,canvas_root_id,font_size,input_style,input_style,canvas_root_id);
}
/*
 x-value of the mouse will be used to calculate via javascript the corresponding y-value using the verbatim js-math function
 a configurable crosshair and vertical/horizontal crosshair lines will be drawn
 function is called "use_mouse_coordinates() and thus can not be combined with command 'mouse'
*/
void add_trace_js_mouse(FILE *js_include_file,int canvas_cnt,int canvas_root_id,char *stroke_color,char *jsmath,int font_size,double stroke_opacity,int line_width,int crosshair_size,char *input_style){
fprintf(js_include_file,"\n<!-- begin command add_trace_jsmath  trace_canvas -->\n\
use_jsmath=1;\
function use_trace_jsmath(){\
if( wims_status == \"done\" ){return;};\
 var label_x = \"x\";var label_y = \"y\";\
 if( typeof(xaxislabel) !== 'undefined' ){label_x = xaxislabel;}\
 if( typeof(yaxislabel) !== 'undefined' ){label_y = yaxislabel;}\
 var trace_canvas = create_canvas%d(%d,xsize,ysize);\
 var trace_context = trace_canvas.getContext(\"2d\");\
 var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
 var trace_div = document.createElement('div');\
 trace_div.id = \"trace_div\";\
 tooltip_div.appendChild(trace_div);\
 trace_div.innerHTML = \"<br /><span style='font-style:italic;font-size:%dpx'>\"+label_x+\" : <input type='text' size='4' value='' id='trace_input_x' style='%s' />\"+label_y+\" : <input type='text' size='5' value='' id='trace_input_y' style='%s' readonly /></span> \";\
 canvas_div.addEventListener(\"mousemove\",trace,false);\
 canvas_div.addEventListener(\"touchmove\",function(e){ e.preventDefault();trace(e.changedTouches[0]);},false);\
 var fun = to_js_math(\"%s\");if(fun == null){return;};\
 function eval_jsmath(x){return parseFloat(eval(fun));};\
 function trace(evt){\
  var mouse = dragstuff.getMouse(evt,trace_canvas);\
  var x_px = mouse.x;\
  var x = px2x(x_px);\
  var y = eval_jsmath(x);\
  if(isNaN(y)){return;};\
  var y_px = y2px(y);\
  trace_context.clearRect(0,0,xsize,ysize);\
  draw_crosshairs(trace_context,[x_px],[y_px],%d,%d,\"%s\",%f,0,0,0,[0,0]);\
  document.getElementById(\"trace_input_x\").value = x;\
  document.getElementById(\"trace_input_y\").value = y;\
 };\
 return;\
};use_trace_jsmath();",canvas_root_id,canvas_cnt,canvas_root_id,font_size,input_style,input_style,jsmath,line_width,crosshair_size,stroke_color,stroke_opacity);
}

/*
add a table with 2 textarea's labeled 'x' 'y' ( or 'xlabel' 'ylabel' if defined)
add two buttons: OK and NOK (OK draws; NOK will delete last item pair from userdraw_x / userdraw_y array's
*/
void add_textarea_xy(FILE *js_include_file, int canvas_root_id, char *input_style){
fprintf(js_include_file,"\n<!-- begin add_textarea_xy -->\n\
function add_textarea_xy(){\
if( wims_status == \"done\" ){return;};\
var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
var textarea_div = document.createElement('div');\
textarea_div.id = \"textarea_div\";\
tooltip_div.appendChild(textarea_div);\
var label_x = \"x\";var label_y = \"y\";\
if( typeof(xaxislabel) !== 'undefined' ){label_x = xaxislabel;}\
if( typeof(yaxislabel) !== 'undefined' ){label_y = yaxislabel;}\
textarea_div.innerHTML=\"\
<table style=\'border:1px solid black;background-color:#ffffa0\' >\
<tr>\
 <td><input id='textarea_ok_button' type='button' value='OK' onclick='' style='color:red;background-color:lightblue;'/></td>\
 <td><input id='textarea_nok_button' type='button' value='NOK' onclick='' style='color:blue;background-color:red;'/></td>\
</tr>\
<tr>\
 <td><em>\"+label_x+\"</em></td>\
 <td><em>\"+label_y+\"</em></td>\
</tr>\
<tr>\
 <td><textarea rows='5' cols='2' id='userinput_x' style='%s' ></textarea></td>\
 <td><textarea rows='5' cols='2' id='userinput_y' style='%s' ></textarea></td>\
</tr>\
</table>\";\
var textarea_ok_button = document.getElementById(\"textarea_ok_button\");\
var textarea_nok_button = document.getElementById(\"textarea_nok_button\");\
textarea_ok_button.addEventListener(\"mousedown\",function(e){user_redraw(1);return;},false);\
textarea_nok_button.addEventListener(\"mousedown\",function(e){user_redraw(-1);return;},false);\
return;\
};add_textarea_xy();",canvas_root_id,input_style,input_style);
}

/*

*/
void add_setlimits(FILE *js_include_file, int canvas_root_id,int font_size,char *input_style){
fprintf(js_include_file,"\n<!-- begin add_setlimits -->\n\
use_pan_and_zoom = 1;\
function use_setlimits(){\
if( wims_status == \"done\" ){return;};\
var label_x = \"x\";var label_y = \"y\";\
if( typeof(xaxislabel) !== 'undefined' ){label_x = xaxislabel;}\
if( typeof(yaxislabel) !== 'undefined' ){label_y = yaxislabel;}\
var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
var setlim_div = document.createElement('div');\
setlim_div.id = \"setlim_div\";\
tooltip_div.appendChild(setlim_div);\
setlim_div.innerHTML=\"<br /><span style='font-style:italic;font-size:%dpx'>\"+label_x+\"min = <input type='text' size='4' value='\"+xmin+\"' id='userinput_xmin' style='%s' /> \"+label_x+\"max = <input type='text' size='4' value='\"+xmax+\"' id='userinput_xmax' style='%s' /><br />\"+label_y+\"min = <input type='text' size='4' value='\"+ymin+\"' id='userinput_ymin' style='%s' /> \"+label_y+\"max = <input type='text' size='4' value='\"+ymax+\"' id='userinput_ymax' style='%s' /><br /><input id='set_limits' type='button' value='OK' onclick='' style='color:red;background-color:lightblue;' />\";\
var setlimit_button = document.getElementById(\"set_limits\");\
function set_limits(e){\
xmin = safe_eval(document.getElementById('userinput_xmin').value);\
xmax = safe_eval(document.getElementById('userinput_xmax').value);\
ymin = safe_eval(document.getElementById('userinput_ymin').value);\
ymax = safe_eval(document.getElementById('userinput_ymax').value);\
if(xmin > xmax || ymin > ymax){alert(\"your limits are not correct...\");return;}\
try{start_canvas%d(1234)}catch(e){};try{dragstuff.Zoom(xmin,xmax,ymin,ymax)}catch(e){};return;};\
setlimit_button.addEventListener(\"mousedown\",function(e){set_limits();},false);\
};use_setlimits();",canvas_root_id,font_size,input_style,input_style,input_style,input_style,canvas_root_id);
}


void add_rawmath(FILE *js_include_file){
fprintf(js_include_file,"\n<!-- begin add_rawmath() -->\n\
function rawmath(i){\
 i=i.toLowerCase();\
 i=i.replace(/\\ /g,\"\");i=i.replace(/\\*\\*/g,\"^\");\
 if(i.indexOf(\"e+\")!=-1){i=i.replace(\"e+\",\"*10^\");};\
 if(i.indexOf(\"e-\")!=-1){i=i.replace(\"e-\",\"*10^-\");};\
 i=i.replace(/\\*\\*/g,\"*\");\
 if(i.charAt(0)==\"*\"){i=i.substring(1,i.length);};\
 var fun=[\"asin\",\"acos\",\"atan\",\"sin\",\"cos\",\"tan\",\"log\",\"ln\",\"pi\",\"e\",\"x\",\"y\"];\
 var cons=[\"pi\",\"e\",\"0\",\"1\",\"2\",\"3\",\"4\",\"5\",\"6\",\"7\",\"8\",\"9\"];\
 var cntl = 0;var cntr = 0;\
 var len = i.length;\
 for( var p = 0;p < len; p++){\
  if(i.charAt(p) == '('){cntl++;}\
  if(i.charAt(p) == ')'){cntr++;}\
 };\
 if(cntl != cntr){alert(\"unmatched parenthesis !!\");return null;};\
 for(var p = 0; p < 12 ; p++){\
  for(var d = 0; d < 12 ; d++){\
   while(i.indexOf(cons[d]+\"\"+fun[p])!=-1){\
    i = i.replace(cons[d]+\"\"+fun[p],cons[d]+\"*\"+fun[p]);\
   };\
   while(i.indexOf(fun[p]+\"\"+cons[d])!=-1){\
    i = i.replace(fun[p]+\"\"+cons[d],fun[p]+\"*\"+cons[d]);\
   };\
  };\
 };\
 if(i.indexOf(\"(\")!=-1){\
  for(var p = 0;p < 12; p++){\
   if(i.indexOf(cons[p]+\"(\")!=-1){\
    i = i.replace(cons[p]+\"(\",cons[p]+\"*(\");\
   };\
   if(i.indexOf(\")\"+cons[p])!=-1){\
    i = i.replace(\")\"+cons[p],\")*\"+cons[p]);\
   };\
  };\
  i = i.replace(/\\)\\(/g,\")*(\");\
 };\
 return i;\
}\n");
}
void add_input_jsfunction(FILE *js_include_file, int canvas_root_id,char *input_style,char *input_label,int input_cnt,char *stroke_color,float stroke_opacity,int line_width,int use_dashed,int dashtype0,int dashtype1,int font_size){
fprintf(js_include_file,"\n<!-- begin add_input_jsfunction -->\n\
function clear_jsfunction(canvas_plot_id,input_field){\
 try{\
  var canvas_plot = document.getElementById(\"wims_canvas%d\"+canvas_plot_id);\
  var canvas_plot_ctx = canvas_plot.getContext(\"2d\");\
  if( confirm(\"clear function plot?\") ){\
   canvas_plot_ctx.clearRect(0,0,xsize,ysize);\
   document.getElementById(input_field).value = \"\";\
  };\
  return;\
 }catch(e){alert(e+\"nothing to remove...\");};\
 return;\
};\
function add_input_jsfunction(input_cnt,input_style,input_label,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1){\
 var canvas_plot_id = %d+input_cnt;\
 var input_field = \"canvas_input\"+input_cnt;\
 var update_button_id = \"update_button\"+input_cnt;\
 var delete_button_id = \"delete_button\"+input_cnt;\
 if( wims_status == \"done\" ){return;};\
 var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
 var input_jsfunction_div = document.createElement('div');\
 input_jsfunction_div.id = \"input_jsfunction_div\"+input_cnt;\
 tooltip_div.appendChild(input_jsfunction_div);\
 input_jsfunction_div.innerHTML=\"<br /><br /><span style='font-style:italic;font-size:%dpx;color:rgb(\"+stroke_color+\")'><b>\"+input_label+\" <input type='text' size='16' value='' id='\"+input_field+\"' style='\"+input_style+\"' /></b><input id='\"+update_button_id+\"' type='button' value='OK' onclick='' style='color:red;background-color:lightblue;'/><input id='\"+delete_button_id+\"' type='button' value='NOK' onclick='' style='color:blue;background-color:red;'/></span> \";\
 var update_button = document.getElementById(update_button_id);\
 var delete_button = document.getElementById(delete_button_id);\
 update_button.addEventListener(\"mousedown\",function(e){jsplot(canvas_plot_id,[rawmath(document.getElementById(input_field).value)],[line_width],[stroke_color],[stroke_opacity],[use_dashed],dashtype0,dashtype1);return;},false);\
 delete_button.addEventListener(\"mousedown\",function(e){clear_jsfunction(canvas_plot_id,input_field);return;},false);\
};\
add_input_jsfunction(%d,\"%s\",\"%s\",%d,\"%s\",%.2f,%d,%d,%d);\n",canvas_root_id,USERDRAW_JSPLOT,canvas_root_id,font_size,input_cnt,input_style,input_label,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);
}


/*
adds 2 inputfields (x:y) and 'ok' | 'nok' button
these are used for user drawing with inputfields...
*/

void add_input_xy(FILE *js_include_file, int canvas_root_id,int font_size,char *input_style){
fprintf(js_include_file,"\n<!-- begin add_input_xy -->\n\
function add_input_xy(){\
if( wims_status == \"done\" ){return;};\
var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
var input_xy_div = document.createElement('div');\
input_xy_div.id = \"input_xy_div\";\
tooltip_div.appendChild(input_xy_div);\
var label_x = \"x\";var label_y = \"y\";\
input_xy_div.innerHTML=\"<br /><span style='font-style:italic;font-size:%dpx'><b>( <input type='text' size='5' value='' id='userinput_x' style='%s' /> : <input type='text' size='5' value='' id='userinput_y' style='%s' /> )</b><input id='update_button' type='button' value='OK' onclick=''  style='color:red;background-color:lightblue;'/><input id='delete_button' type='button' value='NOK' onclick='' style='color:blue;background-color:red;'/></span> \";\
var update_button = document.getElementById(\"update_button\");\
var delete_button = document.getElementById(\"delete_button\");\
update_button.addEventListener(\"mousedown\",function(e){user_redraw(1);return;},false);\
delete_button.addEventListener(\"mousedown\",function(e){user_redraw(-1);return;},false);\
};add_input_xy();",canvas_root_id,font_size,input_style,input_style);
}

/* adds 4 inputfields (x1:y1) --- (x2:y2) and 'ok' + 'nok' button */
void add_input_x1y1x2y2(FILE *js_include_file, int canvas_root_id,int font_size,char *input_style){
fprintf(js_include_file,"\n<!-- begin add_input_x1y1x2y2 -->\n\
function add_input_x1y1x2y2(){\
if( wims_status == \"done\" ){return;};\
var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
var input_x1y1x2y2_div = document.createElement('div');\
input_x1y1x2y2_div.id = \"input_x1y1x2y2_div\";\
tooltip_div.appendChild(input_x1y1x2y2_div);\
input_x1y1x2y2_div.innerHTML=\"<br /><span style='font-size:%dpx'><b>( <input type='text' size='5' value='' id='userinput_x1' style='%s' /> : <input type='text' size='5' value='' id='userinput_y1' style='%s' /> ) ----- ( <input type='text' size='5' value='' id='userinput_x2' style='%s' /> : <input type='text' size='5' value='' id='userinput_y2' style='%s'/> )</b><input id='update_button' type='button' value='OK' onclick='' style='color:red;background-color:lightblue;'/><input id='delete_button' type='button' value='NOK' onclick='' style='color:blue;background-color:red;' /></span> \";\
var update_button = document.getElementById(\"update_button\");\
var delete_button = document.getElementById(\"delete_button\");\
update_button.addEventListener(\"mousedown\",function(e){user_redraw(1);return;},false);\
delete_button.addEventListener(\"mousedown\",function(e){user_redraw(-1);return;},false);\
};add_input_x1y1x2y2();",canvas_root_id,font_size,input_style,input_style,input_style,input_style);
}

/* adds 3 inputfields Center (x:y) Radius r and 'ok'+'nok' buttons */
void add_input_xyr(FILE *js_include_file, int canvas_root_id,int font_size,char *input_style){
fprintf(js_include_file,"\n<!-- begin add_input_xyr -->\n\
function add_input_xyr(){\
if( wims_status == \"done\" ){return;};\
var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
var input_xyr_div = document.createElement('div');\
input_xyr_div.id = \"input_xyr_div\";\
tooltip_div.appendChild(input_xyr_div);\
input_xyr_div.innerHTML=\"<br /><span style='font-style:italic;font-size:%dpx'><b>Center : ( <input type='text' size='5' value='' id='userinput_x' style='%s' /> : <input type='text' size='5' value='' id='userinput_y' style='%s' /> ) Radius : <input type='text' size='5' value='' id='userinput_r' style='%s' /></b><input id='update_button' type='button' value='OK' onclick='' style='color:red;background-color:lightblue;'/><input id='delete_button' type='button' value='NOK' onclick='' style='color:blue;background-color:red;'/></span> \";\
var update_button = document.getElementById(\"update_button\");\
var delete_button = document.getElementById(\"delete_button\");\
update_button.addEventListener(\"mousedown\",function(e){user_redraw(1);return;},false);\
delete_button.addEventListener(\"mousedown\",function(e){user_redraw(-1);return;},false);\
};add_input_xyr();",canvas_root_id,font_size,input_style,input_style,input_style);
}

/* THESE JS-FUNCTIONS COULD BE MADE LESS COPY & PASTE "PROGRAMMING" */

/* draw circle(s) / point(s) via 3 inputfields */
void add_input_circle(FILE *js_include_file,int type,int num){
/*
type = 0 : a point ...radius is fixed
type = 1 : a circle ... read inputfield userinput_r
num = 1 : a single point / circle
num = 2 : multiple points / circles
*/
fprintf(js_include_file,"\n<!-- begin add_input_circle -->\n\
function user_redraw(t){\
 var type = %d;\
 var num = %d;\
 var lu = userdraw_x.length;\
 if( t == -1 && lu > 0){\
  userdraw_x.splice(lu-1,1);\
  userdraw_y.splice(lu-1,1);\
  if(type == 1){\
    userdraw_radius.splice(lu-1,1);\
  };\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_circles(context_userdraw,userdraw_x,userdraw_y,userdraw_radius,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);\
  return;\
 };\
 var add_x = safe_eval( document.getElementById(\"userinput_x\").value );\
 var add_y = safe_eval( document.getElementById(\"userinput_y\").value );\
 if( add_x != null && add_y != null ){\
  if( type == 2 ){\
   var add_r = safe_eval( document.getElementById(\"userinput_r\").value );if( add_r == null ){alert(\"illegal radius input \");return;}\
   if( num == 1 ){\
    userdraw_radius[0] = parseInt(Math.abs(xsize*(add_r)/(xmax - xmin)));\
   }\
   else\
   {\
    userdraw_radius[lu] = parseInt(Math.abs(xsize*(add_r)/(xmax - xmin)));\
   };\
  }\
  else\
  {\
    userdraw_radius[lu] = userdraw_radius[0];\
  };\
  if( num == 1 ){\
  userdraw_x[0] = x2px(add_x);\
  userdraw_y[0] = y2px(add_y);\
  }\
  else\
  {\
    userdraw_x[lu] = x2px(add_x);\
    userdraw_y[lu] = y2px(add_y);\
    xy_cnt++;\
  };\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_circles(context_userdraw,userdraw_x,userdraw_y,userdraw_radius,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);\
 };\
 return;\
};",type,num);
}
/* draw crosshairs via inputfields x/y */
void add_input_crosshair(FILE *js_include_file,int num){
fprintf(js_include_file,"\n<!-- begin add_input_crosshair -->\n\
function user_redraw(t){\
 var lu = userdraw_x.length;\
 if( t == -1 && lu > 0){\
  userdraw_x.splice(lu-1,1);\
  userdraw_y.splice(lu-1,1);\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_crosshairs(context_userdraw,userdraw_x,userdraw_y,line_width,crosshair_size,stroke_color,stroke_opacity,0,0,0,[0,0]);\
  return;\
 };\
 var add_x = safe_eval( document.getElementById(\"userinput_x\").value );\
 var add_y = safe_eval( document.getElementById(\"userinput_y\").value );\
 if( add_x != null && add_y != null ){\
  if( %d == 1 ){\
   userdraw_x[0] = x2px(add_x);\
   userdraw_y[0] = y2px(add_y);\
  }\
  else\
  {\
    userdraw_x[lu] = x2px(add_x);\
    userdraw_y[lu] = y2px(add_y);\
    xy_cnt++;\
  };\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_crosshairs(context_userdraw,userdraw_x,userdraw_y,line_width,crosshair_size,stroke_color,stroke_opacity,0,0,0,[0,0]);\
 };\
 return;\
};",num);
}

/* draw arrows via inputfields x/y */
void add_input_arrow(FILE *js_include_file,int num){
fprintf(js_include_file,"\n<!-- begin add_input_arrow -->\n\
function user_redraw(t){\
 var lu = userdraw_x.length;\
 if( t == -1 && lu > 1 ){\
  userdraw_x.splice(lu-2,2);\
  userdraw_y.splice(lu-2,2);\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_arrows(context_userdraw,userdraw_x,userdraw_y,arrow_head,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,type,use_rotate,angle,0,[1,0,0,1,0,0]);\
  return;\
 };\
 var add_x1 = safe_eval( document.getElementById(\"userinput_x1\").value );\
 var add_y1 = safe_eval( document.getElementById(\"userinput_y1\").value );\
 var add_x2 = safe_eval( document.getElementById(\"userinput_x2\").value );\
 var add_y2 = safe_eval( document.getElementById(\"userinput_y2\").value );\
 if( add_x1 != null && add_y1 != null && add_x2 != null && add_y2 != null ){\
  if( %d == 2 ){\
    var s = userdraw_x.length;\
    userdraw_x[lu] = x2px(add_x1);\
    userdraw_y[lu] = y2px(add_y1);\
    userdraw_x[lu+1] = x2px(add_x2);\
    userdraw_y[lu+1] = y2px(add_y2);\
  }\
  else\
  {\
   userdraw_x[0] = x2px(add_x1);\
   userdraw_y[0] = y2px(add_y1);\
   userdraw_x[1] = x2px(add_x2);\
   userdraw_y[1] = y2px(add_y2);\
  };\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_arrows(context_userdraw,userdraw_x,userdraw_y,arrow_head,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,type,use_rotate,angle,0,[1,0,0,1,0,0]);\
 };\
 return;\
};",num);
}

/* draw line via inputfields x/y */
void add_input_line(FILE *js_include_file,int num){
fprintf(js_include_file,"\n<!-- begin line via inputfields  -->\n\
function user_redraw(t){\
 var lu = userdraw_x.length;\
 if( t == -1 && lu > 1){\
  userdraw_x.splice(lu-2,2);\
  userdraw_y.splice(lu-2,2);\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_lines(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,1,0,0);\
  return;\
 };\
 var add_x1 = safe_eval( document.getElementById(\"userinput_x1\").value );\
 var add_y1 = safe_eval( document.getElementById(\"userinput_y1\").value );\
 var add_x2 = safe_eval( document.getElementById(\"userinput_x2\").value );\
 var add_y2 = safe_eval( document.getElementById(\"userinput_y2\").value );\
 if( add_x1 != null && add_y1 != null && add_x2 != null && add_y2 != null ){\
  if( %d == 2 ){\
    userdraw_x[lu] = x2px(add_x1);\
    userdraw_y[lu] = y2px(add_y1);\
    userdraw_x[lu+1] = x2px(add_x2);\
    userdraw_y[lu+1] = y2px(add_y2);\
  }\
  else\
  {\
   userdraw_x[0] = x2px(add_x1);\
   userdraw_y[0] = y2px(add_y1);\
   userdraw_x[1] = x2px(add_x2);\
   userdraw_y[1] = y2px(add_y2);\
  };\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_lines(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,1,0,0);\
 };\
 return;\
};",num);
}


/* draw polyline via inputfields x/y */
void add_input_polyline(FILE *js_include_file){
fprintf(js_include_file,"\n<!-- begin polyline_segment via inputfields -->\n\
function user_redraw(t){\
 var lu = userdraw_x.length;\
 cnt = 1;\
 if( t == -1 && lu > 0){\
  userdraw_x.splice(lu-1,1);\
  userdraw_y.splice(lu-1,1);\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_polyline(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
  return;\
 };\
 var add_x = safe_eval( document.getElementById(\"userinput_x\").value );\
 var add_y = safe_eval( document.getElementById(\"userinput_y\").value );\
 if(add_x != null && add_y != null ){\
  userdraw_x.push(x2px(add_x));\
  userdraw_y.push(y2px(add_y));\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_polyline(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
 };\
 return;\
};");
}
/* draw segment(s) via inputfields x/y */
void add_input_segment(FILE *js_include_file,int num){
fprintf(js_include_file,"\n<!-- begin add_input_segment -->\n\
function user_redraw(t){\
 var lu = userdraw_x.length;\
 if( t == -1 && lu > 1){\
  userdraw_x.splice(lu-2,2);\
  userdraw_y.splice(lu-2,2);\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_segments(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
  return;\
 };\
 var add_x1 = safe_eval( document.getElementById(\"userinput_x1\").value );\
 var add_y1 = safe_eval( document.getElementById(\"userinput_y1\").value );\
 var add_x2 = safe_eval( document.getElementById(\"userinput_x2\").value );\
 var add_y2 = safe_eval( document.getElementById(\"userinput_y2\").value );\
 if( add_x1 != null && add_y1 != null && add_x2 != null && add_y2 != null ){\
  if( %d == 2 ){\
    var s = userdraw_x.length;\
    userdraw_x[s] = x2px(add_x1);\
    userdraw_y[s] = y2px(add_y1);\
    userdraw_x[s+1] = x2px(add_x2);\
    userdraw_y[s+1] = y2px(add_y2);\
  }\
  else\
  {\
   userdraw_x[0] = x2px(add_x1);\
   userdraw_y[0] = y2px(add_y1);\
   userdraw_x[1] = x2px(add_x2);\
   userdraw_y[1] = y2px(add_y2);\
  };\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_segments(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
 };\
 return;\
};",num);
}

/* draw demilines(s) via inputfields x/y */
void add_input_demiline(FILE *js_include_file,int num){
fprintf(js_include_file,"\n<!-- begin add_input_segment -->\n\
function user_redraw(t){\
 var lu = userdraw_x.length;\
 if( t == -1 && lu > 1){\
  userdraw_x.splice(lu-2,2);\
  userdraw_y.splice(lu-2,2);\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_demilines(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
  return;\
 };\
 var add_x1 = safe_eval( document.getElementById(\"userinput_x1\").value );\
 var add_y1 = safe_eval( document.getElementById(\"userinput_y1\").value );\
 var add_x2 = safe_eval( document.getElementById(\"userinput_x2\").value );\
 var add_y2 = safe_eval( document.getElementById(\"userinput_y2\").value );\
 if( add_x1 != null && add_y1 != null && add_x2 != null && add_y2 != null ){\
  if( %d == 2 ){\
    var s = userdraw_x.length;\
    userdraw_x[s] = x2px(add_x1);\
    userdraw_y[s] = y2px(add_y1);\
    userdraw_x[s+1] = x2px(add_x2);\
    userdraw_y[s+1] = y2px(add_y2);\
  }\
  else\
  {\
   userdraw_x[0] = x2px(add_x1);\
   userdraw_y[0] = y2px(add_y1);\
   userdraw_x[1] = x2px(add_x2);\
   userdraw_y[1] = y2px(add_y2);\
  };\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_demilines(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
 };\
 return;\
};",num);
}

/* draw polygon via 2 textarea's x/y : split into lines ! */
void add_textarea_polygon(FILE *js_include_file){
fprintf(js_include_file,"\n<!-- begin polygon via 2 textareas x / y -->\n\
function user_redraw(t){\
 var lu = userdraw_x.length;\
 if( t == -1 && lu > 0){\
  if( lu < 3 ){\
   userdraw_x = [];\
   userdraw_y = [];\
  }\
  else\
  {\
  userdraw_x.splice(lu-1,1);\
  userdraw_y.splice(lu-1,1);\
  };\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_paths(context_userdraw,userdraw_x,userdraw_y,line_width,closed_path,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,use_rotate,angle,0,[1,0,0,1,0,0]);\
  cnt = 1; return;\
 };\
 var add_x_values = (document.getElementById(\"userinput_x\").value).split('\\n');\
 var add_y_values = (document.getElementById(\"userinput_y\").value).split('\\n');\
 var lx = add_x_values.length;\
 var ly = add_y_values.length;\
 if( lx != ly){ if(lx > ly){alert(\'x/y mismatch\\ntoo few y-values\');return}else{alert(\'x/y mismatch\\ntoo many y-values\');return}};\
 var add_x;var add_y;\
 for(var p = 0 ; p < lx ; p++){\
  add_x = safe_eval( add_x_values[p] );\
  add_y = safe_eval( add_y_values[p] );\
  if( add_x == null || add_y == null ){return;};\
  userdraw_x[lu+p] = x2px(add_x);\
  userdraw_y[lu+p] = y2px(add_y);\
  if(p>100){alert(\"hmmmm\");return;};\
 };\
 draw_paths(context_userdraw,userdraw_x,userdraw_y,line_width,closed_path,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,use_rotate,angle,0,[1,0,0,1,0,0]);\
 cnt = 1;\
 return;\
};");
}

void add_jsplot(FILE *js_include_file,int canvas_root_id){
fprintf(js_include_file,"\n<!-- begin jsplot() -->\n\
var jsplot = function(canvas_type,funs,linewidth,color,opacity,use_dashed,dashtype0,dashtype1){\
 var obj = create_canvas%d(canvas_type,xsize,ysize);\
 var ctx = obj.getContext(\"2d\");\
 ctx.clearRect(0,0,xsize,ysize);\
 var len = funs.length;\
 function eval_jsmath(x,func){return parseFloat(eval(func));};\
 if( typeof(multilinewidth) !== 'undefined' && multilinewidth != null ){ linewidth = multilinewidth;};\
 if( typeof(multistrokecolors) !== 'undefined' && multistrokecolors != null){ color = multistrokecolors;};\
 if( typeof(multistrokeopacity) !== 'undefined' && multistrokeopacity != null ){ opacity = multistrokeopacity;};\
 if( typeof(multidash) !== 'undefined' && multidash != null ){use_dashed = multidash;};\
 for(var i = 0 ; i < len; i++){\
  var fun = to_js_math(funs[i]);\
  if(fun == null){alert(\"Syntax Error...\\nAttention : try use very precise notation !\\nlike :\\n6*(0.25)^(1.23)\\n1/(sin(5*x))\\n(3*x+4)/(x^(2*pi)) \");return;};\
  try{ parseFloat( eval_jsmath( px2x(0),fun ) );}catch(e){alert(\"\\nSyntax Error...\\nAttention : try use very precise notation !\\nlike :\\n6*(0.25)^(1.23)\\n1/(sin(5*x))\\n(3*x+4)/(x^(2*pi))\");return;};\
  ctx.lineWidth = linewidth[i];\
  ctx.strokeStyle=\"rgba(\"+color[i]+\",\"+opacity[i]+\")\";\
  if(use_dashed[i] == \"1\"){if(ctx.setLineDash){ctx.setLineDash([dashtype0,dashtype1]);}else{ctx.mozDash =[dashtype0,dashtype1];}};\
  var y1;var x1;var y2;var x2;\
  ctx.beginPath();\
  for(var p = 0 ; p<xsize;p++){\
   x1 = px2x(p);\
   y1 = y2px(parseFloat(eval_jsmath(x1,fun)));\
   x2 = px2x(p+1);\
   y2 = y2px(parseFloat(eval_jsmath(x2,fun)));\
   if(Math.abs(y2-y1) < ysize ){\
    ctx.moveTo(p,y1);\
    ctx.lineTo(p+1,y2);\
   };\
  };\
  ctx.closePath();\
  ctx.stroke();\
 };\
};",canvas_root_id);
}

void add_to_js_math(FILE *js_include_file){
fprintf(js_include_file,"\n<!-- begin to_js_math() -->\n\
var to_js_math = function(math_fun){\
 if(math_fun == null){return;};\
 var infun=[\"sqrt\",\"^\",\"asin\",\"acos\",\"atan\",\"log\",\"pi\",\"abs\",\"sin\",\"cos\",\"tan\",\"e\"];\
 var outfun=[\"Math.sqrt\",\"Math.pow\",\"Math.asin\",\"Math.acos\",\"Math.atan\",\"Math.log\",\"(3.14159265358979)\",\"Math.abs\",\"Math.sin\",\"Math.cos\",\"Math.tan\",\"(2.718281828459045)\"];\
 var len = infun.length;var in_fun;var In_Fun;var out_fun;var w_cnt;\
 for(var p=0 ; p < len ; p++){\
  in_fun = infun[p];In_Fun = in_fun.toUpperCase();out_fun = outfun[p];w_cnt=0;\
  if(math_fun.indexOf(in_fun) != -1){\
   if(in_fun == \"^\"){\
    var tab = [];var small_trick = \"___small_trick___\";\
    while (math_fun.indexOf(\"(\") != -1){\
     math_fun = math_fun.replace(/(\\([^\\(\\)]*\\))/g, function(m, t){tab.push(t);return (small_trick + (tab.length - 1));});\
     w_cnt++;if(w_cnt>1000){alert(\"hmmm \"+math_fun+\" ?\\nUse command plot for more complex math functions...\");return null;};\
    };\
    tab.push(math_fun);w_cnt = 0;math_fun = small_trick + (tab.length - 1);\
    while (math_fun.indexOf(small_trick) != -1){\
     math_fun = math_fun.replace(new RegExp(small_trick + \"(\\\\d+)\", \"g\"), function(m, d){return tab[d].replace(/(\\w*)\\^(\\w*)/g, out_fun+\"($1,$2)\");});\
     w_cnt++;if(w_cnt>1000){alert(\"hmmm \"+math_fun+\" ?\\nUse command plot for more complex math functions...\");return null;};\
    };\
   }\
   else\
   {\
    while( math_fun.indexOf(in_fun) != -1 ){\
     math_fun = math_fun.replace(in_fun,out_fun);\
     math_fun = math_fun.replace(in_fun,In_Fun);\
     w_cnt++;if(w_cnt>1000){alert(\"hmmm \"+math_fun+\" ?\\nUse command plot for more complex math functions...\");return null;};\
    };\
   };\
  };\
 };\
 for(var p=0 ; p < len ; p++){\
  in_fun = infun[p];In_Fun = in_fun.toUpperCase();w_cnt = 0;\
  if(math_fun.indexOf(In_Fun) != -1 ){\
   while(math_fun.indexOf(In_Fun) != -1){\
    math_fun = math_fun.replace(In_Fun,in_fun);\
    w_cnt++;if(w_cnt>1000){alert(\"hmmm \"+math_fun+\" ?\\nUse command plot for more complex math functions...\");return null;};\
   };\
  };\
 };\
 return math_fun;\
};\n");
}

void add_clear_button(FILE *js_include_file,int canvas_root_id,char *input_style,char *button_text){
/* 25/11/2014 added clearing of reply array
all members will be set to 0 eg reply[0] = 0 , reply[1] = 0 ...
hope this does not interfere with existing work... 
*/
/*
5/2016 changed  to 'setAttribute()' because of trouble on Chromium/Safari/IE 
10/2016 corrected contex-reset-flaw when using "userdraw text,color" and added inputs to the things we can remove
*/
fprintf(js_include_file,"<!-- add clear button -->\n\
clear_draw_area%d = function(){\
 if( typeof(context_userdraw) === 'object' ){\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  if( typeof(userdraw_text) != 'undefined'){ userdraw_text = []; };\
  if( document.getElementById(\"canvas_input0\") ){\
   var p = 0;var inp;\
   while( document.getElementById(\"canvas_input\"+p) ){\
    inp = document.getElementById(\"canvas_input\"+p);\
    canvas_div.removeChild(inp);\
    p++;\
   };\
   input_cnt = 0;start_input_cnt = 0; \
  };\
  userdraw_x = [];userdraw_y = [];userdraw_radius = [];xy_cnt = 0;\
  for(var p = 0;p < reply.length; p++){\
   reply[p] = 0;\
  };\
 };\
 return;\
};\
function add_clear_button(){\
 var tooltip_placeholder_div = document.getElementById(\"tooltip_placeholder_div%d\");\
 var button = document.createElement('input');\
 button.setAttribute(\"type\" , \"button\");\
 button.setAttribute(\"id\" , \"clearbutton%d\");\
 button.setAttribute(\"style\" , \"%s\");\
 button.setAttribute(\"value\" , \"%s\");\
 button.setAttribute(\"onclick\",\"clear_draw_area%d()\");\
 tooltip_placeholder_div.appendChild(button);\
};\
add_clear_button();\
",canvas_root_id,canvas_root_id,canvas_root_id,input_style,button_text,canvas_root_id);
}


/* GNU libmatheval library for evaluating mathematical functions. */
char *eval(int xsize,int ysize,char *fun,double xmin,double xmax,double ymin,double ymax,int plotsteps,int precision){
    void *f;
    double x;
    double y;
    int xv;
    int i = 0;
    int xstep =(int)(xsize/plotsteps);
    if( xstep == 0 ){xstep = 1;}
    double a = (xmax - xmin)/xsize;
    f = eval_create(fun);
    assert (f);
    if( f == NULL ){canvas_error("I'm having trouble parsing your \"expression\" ") ;}
    /* we supply the true x/y values...draw_curve() will convert these (x:y) to pixels : used for pan/scale */
    double xydata[MAX_BUFFER+1];/* hmmm */
    int lim_ymin =(int)( ymin - 4*fabs(ymin));/* 19-4-2015 replacing "abs" by "fabs"*/
    int lim_ymax =(int)( ymax + 4*fabs(ymax));/* 19-4-2015 replacing "abs" by "fabs"*/
    for ( xv = 0 ;xv < xsize ; xv = xv+xstep ){
	x = (double) (xv*a + xmin);
	if( i < MAX_BUFFER - 2){
	    y = eval_x(f, x);
	    if(y < lim_ymax && y > lim_ymin ){
		xydata[i++] = x;
	    	xydata[i++] = y;
	    }
	}
	else
	{
	    canvas_error("\nYour curve plotting produces too many data \n Use less plotsteps or some other means to reduce the amount of data... ");
	}
    }
    eval_destroy(f);
    return double_xy2js_array(xydata,i,find_number_of_digits(precision));
}
/* plot a very primitive (!) levelcurve : not to be compared with "flydraw levelcurve" */
char *eval_levelcurve(int xsize,int ysize,char *fun,double xmin,double xmax,double ymin,double ymax,int plotsteps,int precision,double level){
    void *f = eval_create(fun);
    assert (f);
    if( f == NULL ){canvas_error("I'm having trouble parsing your \"expression\" ") ;}
    double a = (double)((xmax - xmin)/plotsteps);
    double b = (double)((ymax - ymin)/plotsteps);
    double x;double y;double diff;
    double xydata[MAX_BUFFER+1];
    int i = 0;
    ymin = ymin - 1;
    xmin = xmin - 1;
    ymax = ymax + 1;
    xmax = xmax + 1;
    for( x = xmin ;x < xmax ; x = x + a ){
	for ( y = ymin ;y < ymax ; y = y + b ){
	    if( i < MAX_BUFFER - 2){
		diff = level - eval_x_y(f, x,y);
		if(diff < 0.1 && diff > -0.1){
		    xydata[i++] = x;
		    xydata[i++] = y;
		}
	    }
	    else
	    {
		canvas_error("\nYour curve plotting produces too many data \n Use less plotsteps, decrease image size...\nor some other means to reduce the amount of data... ");
	    }
	}
    }
    eval_destroy(f);
    return double_xy2js_array(xydata,i,find_number_of_digits(precision));
}

/* plot parametric function */
char *eval_parametric(int xsize,int ysize,char *fun1,char* fun2,double xmin,double xmax,double ymin,double ymax,
 double tmin,double tmax,int plotsteps,int precision){
    void *fx;
    void *fy;
    double t;
    int i = 0;
    double tstep = (tmax-tmin)/plotsteps;
    if( tstep == 0 ){canvas_error("zero step for t variable : reduce plotsteps or inrease trange");}
    fx = eval_create(fun1);
    fy = eval_create(fun2);
    assert(fx);
    assert(fy);
    if( fx == NULL || fy == NULL ){canvas_error("I'm having trouble parsing your \"expression\" ") ;}
    /* we supply the true x/y values...draw_curve() will convert these (x:y) to pixels : used for pan/scale */
    double xydata[MAX_BUFFER+1];/* hmmm */
    double x; /* real x-values */
    double y; /* real y-values */
    int lim_ymin =(int)( ymin - 4*fabs(ymin));/* 19-4-2015 replacing "abs" by "fabs"*/
    int lim_ymax =(int)( ymax + 4*fabs(ymax));/* 19-4-2015 replacing "abs" by "fabs"*/
    for( t = tmin ;t <= tmax ; t = t + tstep ){
	if( i < MAX_BUFFER - 2 ){
	    y = eval_t(fy, t);
	    if(y > lim_ymin && y < lim_ymax){
		x = eval_t(fx, t);
		xydata[i++] = x;
		xydata[i++] = y;
	    }
	}
	else
	{
	    canvas_error("\nYour curve plotting produces too many data \n Use less plotsteps or some other means to reduce the amount of data... ");
	}
    }
    eval_destroy(fx);
    eval_destroy(fy);
    return double_xy2js_array(xydata,i,find_number_of_digits(precision));
}

char *double_xy2js_array(double xy[],int len,int decimals){
 /*
    1,2,3,4,5,6,7,8 --> [1,3,5,7],[2,4,6,8]
    int xy[] is already checked for errors or overflow in "get_real()"
    just to be sure we double check the size of "temp"
*/
    char temp[2*MAX_BUFFER], *string;
    char *tmp = my_newmem(16);/* <= 9999999999999999  */
    memset(temp,'\0',2*MAX_BUFFER);/* clear memory */
    int i;int space_left;
    temp[0] = '[';/* start js-array */
    for(i = 0; i < len;i = i + 2){ /*  x_points[] */
	if(i == len - 2){sprintf(tmp, "%.*f",decimals, xy[i]);}else{sprintf(tmp, "%.*f,",decimals,xy[i]);}
	space_left = (int) (sizeof(temp) - strlen(temp) - strlen(tmp) - 1);
	if( space_left > 0 ){ strncat(temp,tmp,space_left - 1);}else{canvas_error("can not parse integer to js-array:\nYour curve plotting produces too many data \nreduce your image size or plotsteps ");}
    }
    strncat(temp,"],[",3); /* close js x_values array and start new */
    for(i = 1; i < len;i = i + 2){ /* y_points */
	if(i == len - 1){ sprintf(tmp, "%.*f",decimals,xy[i]);}else{sprintf(tmp, "%.*f,",decimals,xy[i]);}
	space_left = (int) (sizeof(temp) - strlen(temp) - strlen(tmp) - 1);
	if( space_left > 0 ){ strncat(temp,tmp,space_left - 1);}else{canvas_error("can not parse integer to js-array:\nYour curve plotting produces too many data \nreduce your image size or plotsteps");}
    }
    strncat(temp,"]",1);
    string=(char *)my_newmem(sizeof(temp));
    snprintf(string,sizeof(temp),"%s",temp);
    return string;
}

char *xy2js_array(int xy[],int len){
 /*
    1,2,3,4,5,6,7,8 --> [1,3,5,7],[2,4,6,8]
    int xy[] is already checked for errors or overflow in "get_real()"
    just to be sure we double check the size of "temp"
*/
    char temp[MAX_BUFFER], *string;
    char *tmp = my_newmem(16);/* <= 9999999999999999  */
    memset(temp,'\0',MAX_BUFFER);/* clear memory */
    int i;int space_left;
    temp[0] = '[';/* start js-array */
    for(i = 0; i < len;i = i + 2){ /*  x_points[] */
	if(i == len - 2){sprintf(tmp, "%d", xy[i]);}else{sprintf(tmp, "%d,", xy[i]);}
	space_left = (int) (sizeof(temp) - strlen(temp) - strlen(tmp) - 1);
	if( space_left > 0 ){ strncat(temp,tmp,space_left - 1);}else{canvas_error("can not parse integer to js-array:\nYour curve plotting produces too many data \nreduce image size or plotsteps ");}
    }
    strncat(temp,"],[",3); /* close js x_values array and start new */
    for(i = 1; i < len;i = i + 2){ /* y_points */
	if(i == len - 1){ sprintf(tmp, "%d", xy[i]);}else{sprintf(tmp, "%d,", xy[i]);}
	space_left = (int) (sizeof(temp) - strlen(temp) - strlen(tmp) - 1);
	if( space_left > 0 ){ strncat(temp,tmp,space_left - 1);}else{canvas_error("can not parse integer to js-array:\nYour curve plotting produces too many data\nreduce image size or plotsteps \n");}
    }
    strncat(temp,"]",1);
    string=(char *)my_newmem(sizeof(temp));
    snprintf(string,sizeof(temp),"%s",temp);
    return string;
}

char *data2js_array(int data[],int len){
 /*
    1,2,3,4,5,6,7,8 --> [1,2,3,4,5,6,7,8]
    int data[] is already checked for errors or overflow in "get_real()"
    just to be sure we double check the size of "temp"
*/
    char temp[MAX_BUFFER], *string;
    char *tmp = my_newmem(16);/* <= 9999999999999999  */
    memset(temp,'\0',MAX_BUFFER);/* clear memory */
    int i;int space_left;
    temp[0] = '[';/* start js-array */
    for(i = 0; i < len; i++){
	if(i == len - 1){sprintf(tmp, "%d", data[i]);}else{sprintf(tmp, "%d,", data[i]);}
	space_left = (int) (sizeof(temp) - strlen(temp) - strlen(tmp) - 1);
	if( space_left > 0 ){ strncat(temp,tmp,space_left - 1);}else{canvas_error("can not parse integer to js-array:\nYour curve plotting produces too many data \nreduce image size or plotsteps ");}
    }
    strncat(temp,"]",1);
    string=(char *)my_newmem(sizeof(temp));
    snprintf(string,sizeof(temp),"%s",temp);
    return string;
}


void *my_newmem(size_t size){
	void	*p;
	if ((p = malloc(size +1)) == NULL){canvas_error("canvasdraw: ran out of memory\n");}
	return p;
}

int find_number_of_digits(int i){
    if(i < 0 ){ i = -1*i;}
    int digits = 0;
    while ( i > 0){
	digits++;
        i = i/10;
    }
    return digits;
}

struct colors colors[]={
 {"#FF0000","red","255,0,0"},
 {"#00FF00","lime","0,255,0"},
 {"#0000FF","blue","0,0,255"},
 {"#FFA500","orange","255,165,0"},
 {"#E9967A","darksalmon","233,150,122"},
 {"#F0FFFF","azure","240,255,255"},
 {"#CD5C5C","indianred","205,92,92"},
 {"#E0FFFF","lightcyan","224,255,255"},
 {"#FFE4E1","mistyrose","255,228,225"},
 {"#DC143C","crimson","220,20,60"},
 {"#FFC0CB","pink","255,192,203"},
 {"#FFD700","gold","255,215,0"},
 {"#E6E6FA","lavender","230,230,250"},
 {"#808080","gray","128,128,128"},
 {"#F0F8FF","aliceblue","240,248,255"},
 {"#C71585","mediumvioletred","199,21,133"},
 {"#FFF0F5","lavenderblush","255,240,245"},
 {"#DAA520","goldenrod","218,165,32"},
 {"#FFB6C1","lightpink","255,182,193"},
 {"#00FFFF","aqua","0,255,255"},
 {"#FF69B4","hotpink","255,105,180"},
 {"#00FFFF","cyan","0,255,255"},
 {"#FF1493","deeppink","255,20,147"},
 {"#7FFFD4","aquamarine","127,255,212"},
 {"#FA8072","salmon","250,128,114"},
 {"#DEB887","burlywood","222,184,135"},
 {"#DB7093","palevioletred","219,112,147"},
 {"#D2B48C","tan","210,180,140"},
 {"#BDB76B","darkkhaki","189,183,107"},
 {"#B22222","firebrick","178,34,34"},
 {"#FF4500","orangered","255,69,0"},
 {"#8B4513","saddlebrown","139,69,19"},
 {"#FF8C00","darkorange","255,140,0"},
 {"#FFFFE0","lightyellow","255,255,224"},
 {"#FFFF00","yellow","255,255,0"},
 {"#FFFACD","lemonchiffon","255,250,205"},
 {"#F5F5DC","beige","245,245,220"},
 {"#FFEFD5","papayawhip","255,239,213"},
 {"#FAFAD2","lightgoldenrodyellow","250,250,210"},
 {"#FFE4B5","moccasin","255,228,181"},
 {"#B8860B","darkgoldenrod","184,134,11"},
 {"#FFF8DC","cornsilk","255,248,220"},
 {"#FFEBCD","blanchedalmond","255,235,205"},
 {"#FFE4C4","bisque","255,228,196"},
 {"#FFDEAD","navajowhite","255,222,173"},
 {"#F5DEB3","wheat","245,222,179"},
 {"#CD853F","peru","205,133,63"},
 {"#D2691E","chocolate","210,105,30"},
 {"#A0522D","sienna","160,82,45"},
 {"#A52A2A","brown","165,42,42"},
 {"#BC8F8F","rosybrown","188,143,143"},
 {"#F08080","lightcoral","240,128,128"},
 {"#FFA07A","lightsalmon","255,160,122"},
 {"#8B0000","darkred","139,0,0"},
 {"#800000","maroon","128,0,0"},
 {"#FAA460","sandybrown","250,164,96"},
 {"#FF7F50","coral","255,127,80"},
 {"#FF6347","tomato","255,99,71"},
 {"#FFDAB9","peachpuff","255,218,185"},
 {"#EEE8AA","palegoldenrod","238,232,170"},
 {"#F0E68C","khaki","240,230,140"},
 {"#D8BFD8","thistle","216,191,216"},
 {"#DDA0DD","plum","221,160,221"},
 {"#FF00FF","fuchsia","255,0,255"},
 {"#FF00FF","magenta","255,0,255"},
 {"#EE82EE","violet","238,130,238"},
 {"#DA70D6","orchid","218,112,214"},
 {"#BA55D3","mediumorchid","186,85,211"},
 {"#9370DB","mediumpurple","147,112,219"},
 {"#8A2BE2","blueviolet","138,43,226"},
 {"#9400D3","darkviolet","148,0,211"},
 {"#9932CC","darkorchid","153,50,204"},
 {"#8B008B","darkmagenta","139,0,139"},
 {"#800080","purple","128,0,128"},
 {"#4B0082","indigo","75,0,130"},
 {"#483D8B","darkslateblue","72,61,139"},
 {"#6A5ACD","slateblue","106,90,205"},
 {"#7B68EE","mediumslateblue","123,104,238"},
 {"#98FB98","palegreen","152,251,152"},
 {"#ADFF2F","greenyellow","173,255,47"},
 {"#7FFF00","chartreuse","127,255,0"},
 {"#7CFC00","lawngreen","124,252,0"},
 {"#00FF7F","springgreen","0,255,127"},
 {"#00FA9A","mediumspringgreen","0,250,154"},
 {"#90EE90","lightgreen","144,238,144"},
 {"#32CD32","limegreen","50,205,50"},
 {"#3CB371","mediumseagreen","60,179,113"},
 {"#2E8B57","seagreen","46,139,87"},
 {"#228B22","forestgreen","34,139,34"},
 {"#008000","green","0,128,0"},
 {"#006400","darkgreen","0,100,0"},
 {"#9ACD32","yellowgreen","154,205,50"},
 {"#6B8E23","olivedrab","107,142,35"},
 {"#808000","olive","128,128,0"},
 {"#556B2F","darkolivegreen","85,107,47"},
 {"#8FBC8F","darkseagreen","143,188,143"},
 {"#66CDAA","mediumaquamarine","102,205,170"},
 {"#20B2AA","lightseagreen","32,178,170"},
 {"#008B8B","darkcyan","0,139,139"},
 {"#008080","teal","0,128,128"},
 {"#AFEEEE","paleturquoise","175,238,238"},
 {"#40E0D0","turquoise","64,224,208"},
 {"#48D1CC","mediumturquoise","72,209,204"},
 {"#00CED1","darkturquoise","0,206,209"},
 {"#5F9EA0","cadetblue","95,158,160"},
 {"#4682B4","steelblue","70,130,180"},
 {"#B0C4DE","lightsteelblue","176,196,222"},
 {"#B0E0E6","powderblue","176,224,230"},
 {"#ADD8E6","lightblue","173,216,230"},
 {"#87CEEB","skyblue","135,206,235"},
 {"#87CEFA","lightskyblue","135,206,250"},
 {"#00BFFF","deepskyblue","0,191,255"},
 {"#1E90FF","dodgerblue","30,144,255"},
 {"#6495ED","cornflowerblue","100,149,237"},
 {"#4169E1","royalblue","65,105,225"},
 {"#0000CD","mediumblue","0,0,205"},
 {"#00008B","darkblue","0,0,139"},
 {"#000080","navy","0,0,128"},
 {"#191970","midnightblue","25,25,112"},
 {"#DCDCDC","gainsboro","220,220,220"},
 {"#D3D3D3","lightgrey","211,211,211"},
 {"#808080","grey","128,128,128"},
 {"#C0C0C0","silver","192,192,192"},
 {"#A9A9A9","darkgray","169,169,169"},
 {"#778899","lightslategray","119,136,153"},
 {"#708090","slategray","112,128,144"},
 {"#696969","dimgray","105,105,105"},
 {"#2F4F4F","darkslategray","47,79,79"},
 {"#000000","black","0,0,0"},
 {"#F5FFFA","mintcream","245,255,250"},
 {"#FFFFFF","white","255,255,255"},
 {"#F0FFF0","honeydew","240,255,240"},
 {"#F5F5F5","whitesmoke","245,245,245"},
 {"#F8F8FF","ghostwhite","248,248,255"},
 {"#FFFFF0","ivory","255,255,240"},
 {"#FFFAFA","snow","255,250,250"},
 {"#FFFAF0","floralwhite","255,250,240"},
 {"#FFF5EE","seashell","255,245,238"},
 {"#FDF5E6","oldlace","253,245,230"},
 {"#FAF0E6","linen","250,240,230"},
 {"#FAEBD7","antiquewhite","250,235,215"},
 };
int NUMBER_OF_COLORNAMES=(sizeof(colors)/sizeof(colors[0]));

void add_drag_code(FILE *js_include_file,int canvas_cnt,int canvas_root_id ){
/* in drag& drop / onclick library:
    obj_type = 1 == rect / rects
    obj_type = 2 == point / points (do not scale with zoom)
    obj_type = 3 == ellipse
    obj_type = 4 == polyline / segment / segments /line / vline / hline
    obj_type = 5 == closed path (polygon)
    obj_type = 6 == roundrect /roundrects
    obj_type = 7 == crosshair / crosshairs
    obj_type = 8 == arrow / arrows
    obj_type = 9 == curve
    obj_type = 10== arrow2 / arrows2
    obj_type = 11== parallel  (no drag or onclick)
    obj_type = 12== arc : radius is in pixels , so no zooming in/out
    obj_type = 13== circle / circles (will scale on zoom)
    obj_type = 14== text (will not scale or pan on zoom)
    obj_type = 15== animated point on curve
    obj_type = 16== pixels
    obj_type = 17== new arc [command angle] :radius in x-range, so will scale on zooming in/out
    obj_type = 18== halfline
    obj_type = 19== yerrorbars
    obj_type = 20== xerrorbars
    
    
    arc
x[0] = x[1] = xc = double_data[0]                                                               
y[0] = y[1] = yc = double_data[1]                                                               
w[0] = width = int_data[0]                                                                      
w[1] = height = int_data[1]                                                                     
h[0] = start_angle = double_data[2]                                                             
h[1] = end_angle = double_data[3]  
      myState.selection.line_width = org_line_width;myState.selection.font_family = org_font_family;break;\

*/
fprintf(js_include_file,"\n<!-- begin drag_drop_onclick shape library -->\n\
if( typeof(dragdrop_precision) == 'undefined' ){var dragdrop_precision = 100;};\
function Shape(click_cnt,onclick,direction,type,x,y,w,h,line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_filled,use_dashed,dashtype0,dashtype1,use_rotate,angle,text,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt,rotation_center){\
 this.slider = slider || 0;\
 this.slider_cnt = slider_cnt || 0;\
 this.text = text || 0;\
 this.font_size = font_size || 12;\
 if( font_family.indexOf('px') > 0 ){this.font_family = font_family;}else{this.font_family = this.font_size+'px Ariel';};\
 this.use_rotate = use_rotate || 0;\
 this.angle = angle*(Math.PI/180) || 0;\
 this.use_affine = use_affine || 0;\
 this.affine_matrix = affine_matrix || [1,0,0,1,0,0];\
 this.click_cnt = click_cnt || 0;\
 this.onclick = onclick || 0;\
 if(this.onclick == 1 ){reply[click_cnt] = 0;};\
 this.direction = direction || 0;\
 this.type = type || 1;\
 this.xorg = x;\
 this.yorg = y;\
 this.x = [x.length];\
 this.y = [x.length];\
 this.w = [x.length];\
 this.h = [x.length];\
 for(var p=0;p<x.length;p++){\
  this.x[p] = x2px(x[p]-xstart);\
  this.y[p] = y2px(y[p]-ystart);\
  if( p > w.length){\
    this.w[p] = w[0];\
    this.h[p] = h[0];\
  }\
  else\
  {\
    this.w[p] = w[p];\
    this.h[p] = h[p];\
  }\
 };\
 if( rotation_center != null ){\
  this.rotation_center = [x2px(rotation_center[0]),y2px(rotation_center[1])];\
 }else{this.rotation_center = [this.x[0],this.y[0]];};\
 this.line_width = line_width || 30;\
 this.org_line_width = line_width || 30;\
 this.stroke_opacity = stroke_opacity || 1.0;\
 this.stroke_color = \"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\" || '#FF0000';\
 this.fill_opacity = fill_opacity || 1.0;\
 this.fill_color = \"rgba(\"+fill_color+\",\"+fill_opacity+\")\" || '#FF0000';\
 this.use_filled = use_filled || 0;\
 this.use_dashed = use_dashed || 0;\
 this.dashtype0 = dashtype0 || 4;\
 this.dashtype1 = dashtype1 || 4;\
};\
Shape.prototype.draw = function(ctx)\
{\
 ctx.lineWidth = this.line_width;\
 ctx.strokeStyle = this.stroke_color;\
 ctx.fillStyle = this.fill_color;\
 ctx.lineJoin = \"round\";\
 ctx.save();\
 if(this.use_rotate == 1){\
   ctx.translate(this.rotation_center[0],this.rotation_center[1]);\
   ctx.rotate(this.angle);\
   ctx.translate(-1*(this.rotation_center[0]),-1*(this.rotation_center[1]));\
 };\
 if( this.use_affine == 1 ){\
  ctx.setTransform(this.affine_matrix[0],this.affine_matrix[1],this.affine_matrix[2],this.affine_matrix[3],this.affine_matrix[4],this.affine_matrix[5]);\
 };\
 ctx.beginPath();\
  if(this.line_width%%2 == 1){ctx.translate(0.5,0.5);};\
  switch(this.type){\
  case 1: for(var p = 0 ; p < this.x.length;p = p+4){ctx.rect(this.x[p], this.y[p], this.x[p+1]-this.x[p], this.y[p+2] - this.y[p]);};break;\
  case 2: ctx.arc(this.x[0],this.y[0],0.5*this.w[0],0,2*Math.PI,false);break;\
  case 3: ctx.save();var w = 0.5*(scale_x_radius(this.w[0]));var h = 0.5*(scale_y_radius(this.h[0]));ctx.scale(1,h/w);ctx.beginPath();ctx.arc(this.x[0], w/h*this.y[0], w, 0, 2 * Math.PI);if(this.use_filled == 1){ ctx.fillStyle = this.fill_color; ctx.fill(); };ctx.closePath();ctx.stroke();ctx.restore();break;\
  case 4: for(var p = 0; p < this.x.length - 1;p++){ctx.moveTo(this.x[p], this.y[p]);ctx.lineTo(this.x[p+1],this.y[p+1]);};break;\
  case 5: ctx.moveTo(this.x[0],this.y[0]);for(var p = 1; p < this.x.length;p++){ctx.lineTo(this.x[p],this.y[p]);};ctx.lineTo(this.x[0],this.y[0]);break;\
  case 6: var w = this.x[1] - this.x[0];var h = this.y[1] - this.y[0];var r = this.w[0];ctx.beginPath();ctx.moveTo(this.x[0] + r, this.y[0]);ctx.lineTo(this.x[0] + w - r, this.y[0]);ctx.quadraticCurveTo(this.x[0] + w, this.y[0], this.x[0] + w, this.y[0] + r);ctx.lineTo(this.x[0] + w, this.y[0] + h - r);ctx.quadraticCurveTo(this.x[0] + w, this.y[0] + h, this.x[0] + w - r, this.y[0] + h);ctx.lineTo(this.x[0] + r, this.y[0] + h);ctx.quadraticCurveTo(this.x[0], this.y[0] + h, this.x[0], this.y[0] + h - r);ctx.lineTo(this.x[0], this.y[0] + r);ctx.quadraticCurveTo(this.x[0], this.y[0], this.x[0] + r, this.y[0]);ctx.closePath();break;\
  case 7: ctx.moveTo(this.x[0]-this.w[0],this.y[0]-this.h[0]);ctx.lineTo(this.x[0]+this.w[0],this.y[0]+this.h[0]);ctx.moveTo(this.x[0]-this.w[0],this.y[0]+this.h[0]);ctx.lineTo(this.x[0]+this.w[0],this.y[0]-this.h[0]);break;\
  case 8: var dx;var dy;var len;var arrow_head = this.w[0];for(var p = 0; p < this.x.length - 1;p++){ctx.save();if(this.use_dashed == 1 ){if( ctx.setLineDash ){ ctx.setLineDash([this.dashtype0,this.dashtype1]);}else{ ctx.mozDash = [this.dashtype0,this.dashtype1];};};dx = this.x[p+1] - this.x[p];dy = this.y[p+1] - this.y[p];len = Math.sqrt(dx*dx+dy*dy);ctx.translate(this.x[p+1],this.y[p+1]);ctx.rotate(Math.atan2(dy,dx));ctx.lineCap = \"round\";ctx.beginPath();ctx.moveTo(0,0);ctx.lineTo(-len,0);ctx.closePath();ctx.stroke();ctx.beginPath();ctx.moveTo(0,0);ctx.lineTo(-1*arrow_head,-0.5*arrow_head);ctx.lineTo(-1*arrow_head, 0.5*arrow_head);ctx.closePath();ctx.fill();ctx.restore();};break;\
  case 9: ctx.moveTo(this.x[0], this.y[0]);for(var p = 1; p < this.x.length - 1;p++){if( Math.abs(this.y[p] - this.y[p-1]) < ysize && Math.abs(this.y[p+1] - this.y[p]) < ysize ){ctx.lineTo(this.x[p],this.y[p]);}else{ctx.moveTo(this.x[p],this.y[p]);};};break;\
  case 10: var dx;var dy;var len;ctx.save();if(this.use_dashed == 1 ){if( ctx.setLineDash ){ ctx.setLineDash([this.dashtype0,this.dashtype1]);}else{ ctx.mozDash = [this.dashtype0,this.dashtype1];};};dx = this.x[1] - this.x[0];dy = this.y[1] - this.y[0];len = Math.sqrt(dx*dx+dy*dy);ctx.translate(this.x[1],this.y[1]);ctx.rotate(Math.atan2(dy,dx));ctx.beginPath();ctx.moveTo(0,0);ctx.lineTo(-len,0);ctx.closePath();ctx.stroke();ctx.beginPath();ctx.moveTo(0,0);ctx.lineTo(-1*this.w[0],0.5*this.w[0]);ctx.lineTo(-1*this.w[0],-0.5*this.w[0]);ctx.closePath();ctx.lineCap = \"round\";ctx.fill();ctx.restore();ctx.save();ctx.translate(this.x[0],this.y[0]);ctx.rotate(Math.atan2(dy,dx));ctx.beginPath();ctx.moveTo(0,0);ctx.lineTo(this.w[0],0.4*this.w[0]);ctx.lineTo(this.w[0],-0.4*this.w[0]);ctx.closePath();ctx.lineCap = \"round\";ctx.fill(); break;\
  case 11: var x1 = this.x[0];var y1 = this.y[0];var x2 = this.x[1];var y2 = this.y[1];var dx = this.x[2];var dy = this.y[2];var n  = this.w[0];for(var p = 0 ; p < n ; p++ ){ctx.beginPath();ctx.moveTo(x1,y1);ctx.lineTo(x2,y2);ctx.stroke();x1 = x1 + dx;y1 = y1 + dy;x2 = x2 + dx;y2 = y2 + dy;ctx.closePath();};break;\
  case 12: ctx.save();var start;var end;if(this.h[0] < this.h[1]){start = this.h[0];end = this.h[1]}else{start = this.h[1];end = this.h[0];};start=360-start;end=360-end;var w = 0.5*(scale_x_radius(this.w[0]));var h = 0.5*(scale_y_radius(this.w[1]));ctx.scale(1,h/w);ctx.arc(this.x[0], w/h*this.y[0], w,start*(Math.PI / 180), end*(Math.PI / 180),true);ctx.stroke();if(this.use_filled == 1){ ctx.fillStyle = this.fill_color; ctx.lineTo(this.x[0],this.y[0]);ctx.fill(); };ctx.restore();break;\
  case 13: for(var p = 0; p < this.x.length; p++){ ctx.arc(this.x[p],this.y[p],scale_x_radius(this.w[p]),0,2*Math.PI,false);};break;\
  case 14: ctx.font = this.font_family ;ctx.fillText(this.text,this.x[0],this.y[0]);break;\
  case 15: break;\
  case 16: for(var p = 0; p < this.x.length;p++){ctx.fillRect( this.x[p], this.y[p],this.line_width,this.line_width );};break;\
  case 17: ctx.save();var start;var end;if(this.h[0] < this.h[1]){start = this.h[0];end = this.h[1]}else{start = this.h[1];end = this.h[0];};start=360-start;end=360-end;var r = scale_x_radius(this.w[0]);ctx.arc(this.x[0], this.y[0], r, start*(Math.PI / 180), end*(Math.PI / 180),true);if(this.use_filled){ctx.lineTo(this.x[0],this.y[0]);ctx.fill();};ctx.restore();break;\
  case 18: for(var p=0 ; p < this.x.length ;p=p+2){ctx.moveTo(this.x[p], this.y[p]);ctx.lineTo(this.x[p+1],this.y[p+1]);};break;\
  case 19: ctx.arc(this.x[0],this.y[0],this.line_width,0,2*Math.PI,false);var E1 = y2px(px2y(this.y[0]) - this.h[0]);var E2 = y2px(px2y(this.y[0]) + this.w[0]);ctx.moveTo(this.x[0],E1);ctx.lineTo(this.x[0],E2);ctx.moveTo(this.x[0] - 2*(this.line_width),E1);ctx.lineTo(this.x[0] + 2*(this.line_width),E1);ctx.moveTo(this.x[0] - 2*(this.line_width),E2);ctx.lineTo(this.x[0] + 2*(this.line_width),E2);break;\
  case 20: ctx.arc(this.x[0],this.y[0],this.line_width,0,2*Math.PI,false);var E1 = x2px(px2x(this.x[0]) - this.w[0]);var E2 = x2px(px2x(this.x[0]) + this.h[0]);ctx.moveTo(E1,this.y[0]);ctx.lineTo(E2,this.y[0]);ctx.moveTo(E1,this.y[0]-2*(this.line_width));ctx.lineTo(E1,this.y[0]+2*(this.line_width));ctx.moveTo(E2,this.y[0]-2*(this.line_width));ctx.lineTo(E2,this.y[0]+2*(this.line_width));break;\
  default: alert(\"draw primitive unknown\");break;\
 };\
 if(this.use_filled == 1){ ctx.fill();}\
 if(this.use_dashed == 1 ){if( ctx.setLineDash ){ ctx.setLineDash([this.dashtype0,this.dashtype1]);}else{ ctx.mozDash = [this.dashtype0,this.dashtype1];};};\
 ctx.stroke();\
 ctx.restore();\
};\
Shape.prototype.contains = function(mx, my){\
 var marge = 2*this.line_width;\
 switch(this.type){\
  case 1: for(var p = 0 ; p < this.x.length; p++ ){if( mx < this.x[p] + marge &&  mx > this.x[p] - marge ){if( my < this.y[p]+marge && my > this.y[p] - marge ){return p;};};};break;\
  case 2: for(var p = 0 ; p < this.x.length; p++ ){if( Math.abs(distance(this.x[p],this.y[p],mx,my) ) < this.w[p] + 4*marge ){return p;break;};};break;\
  case 3: for(var p = 0 ; p < this.x.length; p++ ){if( Math.abs(distance(this.x[p],this.y[p],mx,my) ) < scale_x_radius(this.w[p]) + marge ){return p;break;};};break;\
  case 4: var diff;var q;var r;for(var p = 0 ; p < this.x.length-1; p = p+2  ){if( ((this.x[p+1] - this.x[p]) != 0)  && ((this.y[p+1]-this.y[p]) != 0) ){r = (this.y[p+1]-this.y[p])/(this.x[p+1]-this.x[p]);q = this.y[p] - (r)*(this.x[p]);diff = distance_to_line(r,q,mx,my);}else{if( (this.y[p+1]-this.y[p]) != 0 ){diff = Math.abs(this.x[p] - mx);}else{diff = Math.abs(this.y[p] - my);};};if( diff  < marge ){ return p;};}; break;\
  case 5: marge = 2*marge;for(var p = 0 ; p < this.x.length; p++ ){if( mx < this.x[p] + marge &&  mx > this.x[p] - marge ){if( my < this.y[p]+marge && my > this.y[p] - marge ){return p;};};};break;\
  case 6: marge = 0.5*this.w[0];for(var p = 0 ; p < this.x.length; p++ ){if( mx < this.x[p] + marge &&  mx > this.x[p] - marge ){if( my < this.y[p]+marge && my > this.y[p] - marge ){return p;};};};break;\
  case 7: for(var p = 0 ; p < this.x.length; p++ ){if( (this.x[p] - this.w[p] <= mx) && (this.x[p] + this.w[p] >= mx) &&  (this.y[p] - this.h[p] <= my) && (this.y[p] + this.h[p] >= my) ){return p;};};break;\
  case 8: var diff;var q;var r;for(var p = 0 ; p < this.x.length-1; p = p+2  ){if( ((this.x[p+1] - this.x[p]) != 0)  && ((this.y[p+1]-this.y[p]) != 0) ){r = (this.y[p+1]-this.y[p])/(this.x[p+1]-this.x[p]);q = this.y[p] - (r)*(this.x[p]);diff = distance_to_line(r,q,mx,my);}else{if( (this.y[p+1]-this.y[p]) != 0 ){diff = Math.abs(this.x[p] - mx);}else{diff = Math.abs(this.y[p] - my);};};if( diff  < marge ){ return p;};}; break;\
  case 9: for(var p = 0 ; p < this.x.length; p++ ){if( (this.x[p] - this.line_width <= mx) && (this.x[p] + this.w[p] + this.line_width >= mx) &&  (this.y[p] - this.line_width <= my) && (this.y[p] + this.h[p] +this.line_width  >= my) ){return p;};};break;\
  case 10: var diff;var q;var r;for(var p = 0 ; p < this.x.length-1; p = p+2  ){if( ((this.x[p+1] - this.x[p]) != 0)  && ((this.y[p+1]-this.y[p]) != 0) ){r = (this.y[p+1]-this.y[p])/(this.x[p+1]-this.x[p]);q = this.y[p] - (r)*(this.x[p]);diff = distance_to_line(r,q,mx,my);}else{if( (this.y[p+1]-this.y[p]) != 0 ){diff = Math.abs(this.x[p] - mx);}else{diff = Math.abs(this.y[p] - my);};};if( diff  < marge ){ return p;};}; break;\
  case 11: break;\
  case 12: break;\
  case 13: for(var p = 0 ; p < this.x.length; p++ ){if( Math.abs(distance(this.x[p],this.y[p],mx,my) ) < scale_x_radius(this.w[p]) + marge ){return p;break;};};break;\
  case 14: for(var p = 0 ; p < this.x.length; p++ ){if(this.y[p] < my + 0.5*(this.font_size) && this.y[p] > my - 0.5*(this.font_size)){var w = parseInt(0.8*(this.font_size)*((this.text).length));if(this.x[p] < mx + w && this.x[p] > mx - w ){ return p;break;};};};break;\
  case 15: break;\
  case 16: break;\
  case 17: break;\
  case 18: var diff;var q;var r;if(((this.x[1] - this.x[0]) != 0) && ((this.y[1]-this.y[0]) != 0)){r = (this.y[1]-this.y[0])/(this.x[1]-this.x[0]);q = this.y[0] - (r)*(this.x[0]);diff = distance_to_line(r,q,mx,my);}else{if((this.y[1]-this.y[0])!= 0){diff = Math.abs(this.x[0] - mx);}else{diff = Math.abs(this.y[0] - my);};};if( diff  < marge ){ return 0;};break;\
  default: for(var p = 0 ; p < this.x.length; p++ ){if( (this.x[p] - this.line_width <= mx) && (this.x[p] + this.w[p] + this.line_width >= mx) &&  (this.y[p] - this.line_width <= my) && (this.y[p] + this.h[p] +this.line_width  >= my) ){return p;};};break;\
 };\
 return -1;\
};\
var reply = [];\
function CanvasState(canvas,container_div){\
 this.canvas = canvas;\
 this.width = canvas.width;\
 this.height = canvas.height;\
 var ctx = canvas.getContext(\"2d\");\
 this.ctx = ctx;\
 this.valid = false;\
 this.shapes = [];\
 this.moved = [];\
 this.dragging = false;\
 this.selection = null;\
 var myState = this;\
 container_div.addEventListener( 'mouseup'    , mouseup,  false);\
 container_div.addEventListener( 'mousemove'  , mousemove,false);\
 container_div.addEventListener( 'mousedown'  , mousedown,false);\
 container_div.addEventListener('touchstart'  , function(e) { e.preventDefault(); mousedown(e.changedTouches[0]);},false);\
 container_div.addEventListener( 'touchmove'  , function(e) { e.preventDefault(); mousemove(e.changedTouches[0]);},false);\
 container_div.addEventListener( 'touchend'   , function(e) { e.preventDefault(); mouseup(  e.changedTouches[0]);},false);\
 function mousedown(e){\
  var mouse = myState.getMouse(e,canvas);\
  var mx = mouse.x;\
  var my = mouse.y;\
  if( use_pan_and_zoom == 1 && my > ysize - 15){\
   check_zoom_or_pan(mx);\
  }\
  else\
  {\
   if( wims_status == \"done\"){return null;};\
   var shapes = myState.shapes;\
   var l = shapes.length;\
   var chk = -1;\
   for(var i=0;i<l;i++){\
    chk = shapes[i].contains(mx, my);\
    if ( chk != -1 ){\
     if( myState.moved[shapes[i].click_cnt] != 1){\
      myState.moved[shapes[i].click_cnt] = 1;\
      myState.x_start = shapes[i].x[chk];\
      myState.y_start = shapes[i].y[chk];\
     };\
     myState.chk = chk;\
     myState.selection = shapes[i];\
     myState.valid = false;\
     switch(shapes[i].onclick){\
      case 0: myState.dragging = false;break;\
      case 1: \
       if( reply[myState.selection.click_cnt] == 0 ){\
        myState.selection.line_width = 3*(myState.selection.org_line_width);\
        reply[myState.selection.click_cnt] = 1;\
       }else{ reply[myState.selection.click_cnt] = 0;myState.selection.line_width = myState.selection.org_line_width;};\
       myState.dragging = false;myState.draw();\
       break;\
      case 2: myState.dragging = true;break;\
      default:break;\
     };\
     return;\
    };\
   };\
  };\
  myState.selection = null;\
  myState.valid = true;\
  return;\
 };\
 function mouseup(e){;\
  if(myState.selection != null ){\
   if(myState.selection.onclick == 2 ){\
    if( x_use_snap_to_grid == 1 || y_use_snap_to_grid == 1 || use_snap_to_points != 0){\
     var mouse = myState.getMouse(e,canvas);\
     var dx=mouse.x;\
     var dy=mouse.y;\
     if( use_snap_to_points != 0){\
      var xy = new Array(2);\
      if(use_snap_to_points == 1 ){\
       xy = snap_to_points(dx,dy);\
      }\
      else\
      {\
       xy = snap_to_fun(dx,dy);\
      };\
      dx = xy[0] - myState.selection.x[myState.chk];\
      dy = xy[1] - myState.selection.y[myState.chk];\
     }\
     else\
     {\
      if( x_use_snap_to_grid == 1 && y_use_snap_to_grid == 1 ){ \
       dx = snap_to_x(dx) - myState.selection.x[myState.chk];\
       dy = snap_to_y(dy) - myState.selection.y[myState.chk];\
      }else{\
       if( x_use_snap_to_grid == 1 ){ \
        dx = snap_to_x(dx) - myState.selection.x[myState.chk];\
        dy = 0;\
       }\
       else\
       {\
        dx = 0;\
        dy = snap_to_y(dy) - myState.selection.y[myState.chk];\
       };\
      };\
     };\
     switch(myState.selection.direction){\
      case 0: myState.selection = move(myState.selection,dx,dy);break;\
      case 1: myState.selection = move(myState.selection,dx,0);break;\
      case 2: myState.selection = move(myState.selection,0,dy); break;\
     };\
    };\
    reply[myState.selection.click_cnt] = myState.selection.click_cnt+\":\"+px2x(myState.x_start)+\":\"+px2y(myState.y_start)+\":\"+(Math.round(dragdrop_precision*(px2x(myState.selection.x[myState.chk]))))/dragdrop_precision+\":\"+(Math.round(dragdrop_precision*(px2y(myState.selection.y[myState.chk]))))/dragdrop_precision;\
    myState.valid = false;\
    myState.draw();\
    myState.valid = true;\
   };\
  };\
  myState.dragging = false;\
 };\
 function mousemove(e){\
  if(myState.dragging){\
   var mouse = myState.getMouse(e,canvas);\
   var dx=mouse.x - myState.selection.x[myState.chk];\
   var dy=mouse.y - myState.selection.y[myState.chk];\
   switch(myState.selection.direction){\
    case 0: myState.selection = move(myState.selection,dx,dy);break;\
    case 1: myState.selection = move(myState.selection,dx,0);break;\
    case 2: myState.selection = move(myState.selection,0,dy); break;\
    default:break;\
   };\
   myState.valid = false;\
  };\
 };\
 function check_zoom_or_pan(x){\
  var key = -1;\
  for(var p = 15 ; p < 106 ; p = p+15){\
    key++;\
    if(x > xsize - p){start_canvas%d(key);return;}\
  }\
  return;\
 };\
 this.interval = 30;\
 setInterval(function() { myState.draw(); }, myState.interval);\
};\
CanvasState.prototype.addShape = function(shape){\
 this.shapes.push(shape);\
 this.valid = false;\
};\
CanvasState.prototype.clear = function(){\
 this.ctx.clearRect(0, 0, this.width, this.height);\
};\
CanvasState.prototype.draw = function(){\
 if(this.valid == false ){\
  var shapes = this.shapes;\
  this.clear();\
  var l = shapes.length;var shape;\
  for(var i = 0; i < l; i++){\
   shape = shapes[i];\
   shape.draw(this.ctx);\
  };\
  this.valid = true;\
 }\
};\
CanvasState.prototype.Slide = function(slider_value,slider_count){\
 this.ctx.clearRect(0,0,xsize,ysize);\
 var what;var len = this.shapes.length;var shape;var lu;\
 for(var i = 0; i < len ; i++){\
  if( this.shapes[i] ){\
   shape = this.shapes[i];\
   if( shape.slider != 0 ){\
    if(shape.slider_cnt == slider_count ){\
     what = shape.slider;\
     lu = shape.x.length;\
     reply[shape.click_cnt] = shape.click_cnt+\":\"+slider_value;\
     switch(what){\
      case 3: if(shape.type == 12 || shape.type == 17){\
       shape.h[1] = 180*slider_value[0]/Math.PI;}\
       else\
       {shape.use_rotate = 1;shape.angle = -1*slider_value[1];};break;\
      default:slide(shape,slider_value[0],slider_value[1]);break;\
     };\
    };\
   };\
   this.valid = false;\
   shape.draw(this.ctx);\
  };\
 };\
};\
CanvasState.prototype.Zoom = function(xmin,xmax,ymin,ymax){\
 (this.ctx).clearRect(0,0,this.width,this.height);\
 var len = this.shapes.length;var shape;\
 for(var i = 0; i < len ; i++){\
  shape = this.shapes[i];\
  for(var p = 0 ; p < shape.x.length;p++){\
   shape.x[p] = x2px(shape.xorg[p]);\
   shape.y[p] = y2px(shape.yorg[p]);\
  }\
  this.valid = false;\
  shape.draw(this.ctx);\
 };\
};\
CanvasState.prototype.getMouse = function(e,element){\
 var mx,my;var offsetX = 0,offsetY = 0;\
  while( ( element = element.offsetParent) ){\
   offsetX += element.offsetLeft;\
   offsetY += element.offsetTop;\
  };\
 if(isTouch){\
  mx = e.pageX - offsetX;\
  my = e.pageY - offsetY;\
 }\
 else\
 {\
  mx = e.clientX - offsetX + (document.documentElement.scrollLeft ? document.documentElement.scrollLeft : document.body.scrollLeft);\
  my = e.clientY - offsetY + (document.documentElement.scrollTop ? document.documentElement.scrollTop :document.body.scrollTop);\
 };\
 return {x: mx, y: my};\
};\
CanvasState.prototype.read_dragdrop = function(){\
 if( wims_status == \"done\" || use_dragdrop_reply == -1 ){return null;};\
 var moved_objects = new Array();\
 var c = 0;\
 for(var p = 0 ; p < reply.length ; p++){\
  if( reply[p] != null ){\
   moved_objects[c] = reply[p];\
   c++;\
  };\
 }\
 return moved_objects;\
};\
var obj = create_canvas%d(%d,xsize,ysize);\
var container_div = document.getElementById(\"canvas_div%d\");\
var dragstuff = new CanvasState(obj,container_div);\
read_dragdrop%d = dragstuff.read_dragdrop;\n",canvas_root_id,canvas_root_id,DRAG_CANVAS,canvas_root_id,canvas_root_id);
}

/*
#define BG_CANVAS 0 may be used for floodfill
#define STATIC_CANVAS 1 may be used for floodfill
#define MOUSE_CANVAS 2 xx
#define GRID_CANVAS 3 may be used for floodfill
#define DRAG_CANVAS 4 default for floodfill
#define DRAW_CANVAS 5 may be used for floodfill

*/
void add_js_clickfill(FILE *js_include_file,int canvas_root_id,char *clickcolor,int opacity){
fprintf(js_include_file,"\n<!-- begin command clickfill -->\n\
function user_drag(evt){return;};\
function user_draw(evt){\
 var mouse = dragstuff.getMouse(evt,canvas_userdraw);\
 var x = mouse.x;\
 var y = mouse.y;\
 if( use_snap_to_points != 0 ){\
  var xy = new Array(2);\
  if( use_snap_to_points == 1 ){\
   xy = snap_to_points(x,y);\
  }\
  else\
  {\
   xy = snap_to_fun(x,y);\
  };\
  x = xy[0];y = xy[1];\
 }\
 else\
 {\
  if( x_use_snap_to_grid == 1 ){\
    x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
 };\
 userdraw_x[0] = x;\
 userdraw_y[0] = y;\
 filltoborder( px2x(mouse.x),px2y(mouse.y),[%s,%d],[%s,%d]);\
};",clickcolor,opacity,clickcolor,opacity);
}

/* 10/2016 does not react to border color !! just any border will stop the filling */
void add_js_filltoborder(FILE *js_include_file,int canvas_root_id,int canvas_type){
fprintf(js_include_file,"\n<!-- begin command filltoborder -->\n\
var filltoborder = function(xs,ys,bordercolor,color){\
 var canvas = document.getElementById(\"wims_canvas%d%d\");\
 if( ! canvas ){ return; };\
 var ctx = canvas.getContext(\"2d\");\
 ctx.save();\
 xs = x2px(xs);\
 ys = y2px(ys);\
 var image = ctx.getImageData(0, 0, xsize, ysize);\
 var imageData = image.data;\
 var pixelStack = [[xs, ys]];\
 var px1;\
 var newPos;\
 var pixelPos;\
 var found_left_border;\
 var found_right_border;\
 function _getPixel(pixelPos){\
  return {r:imageData[pixelPos], g:imageData[pixelPos+1], b:imageData[pixelPos+2], a:imageData[pixelPos+3]};\
 };\
 function _setPixel(pixelPos){\
  imageData[pixelPos] = color.r;\
  imageData[pixelPos+1] = color.g;\
  imageData[pixelPos+2] = color.b;\
  imageData[pixelPos+3] = color.a;\
 };\
 function _comparePixel(px2){\
  if(px2.r === px1.r && px2.g === px1.g && px2.b === px1.b ){ return true;};\
  return false;\
 };\
 px1 = _getPixel(((ys * xsize) + xs) * 4);\
 color = {\
  r: parseInt(color[0], 10),\
  g: parseInt(color[1], 10),\
  b: parseInt(color[2], 10),\
  a: parseInt(color[3] || 255, 10)\
 };\
 bordercolor = {\
  r: parseInt(bordercolor[0], 10),\
  g: parseInt(bordercolor[1], 10),\
  b: parseInt(bordercolor[2], 10),\
  a: parseInt(bordercolor[3] || 255, 10)\
 };\
 if( _comparePixel(color) ) { return true; }\
 while (pixelStack.length) {\
  newPos = pixelStack.pop();\
  xs = newPos[0];ys = newPos[1];\
  pixelPos = (ys*xsize + xs) * 4;\
  while(ys >= 0 && _comparePixel(_getPixel(pixelPos))){\
   ys -= 1;\
   pixelPos -= xsize * 4;\
  }\
  pixelPos += xsize * 4;\
  ys += 1;\
  found_left_border = false;\
  found_right_border = false;\
  while( ys <= ysize-1 && _comparePixel(_getPixel(pixelPos))  ){\
   ys += 1;\
   _setPixel(pixelPos);\
   if( xs > 1 ){\
    if( _comparePixel(_getPixel(pixelPos - 4)) ){\
    if( !found_left_border ){\
     pixelStack.push( [xs - 1, ys] );\
     found_left_border = true;\
    };\
   }\
   else if( found_left_border ){\
     found_left_border = false;\
    }\
   }\
   if( xs < xsize - 1 ){\
    if( _comparePixel(_getPixel(pixelPos + 4)) ){\
     if( !found_right_border){\
      pixelStack.push( [xs + 1, ys] );\
      found_right_border = true;\
     }\
    }\
    else if(found_right_border){\
      found_right_border = false;\
     }\
    }\
   pixelPos += xsize * 4;\
  }\
 };\
 var fill_canvas = create_canvas%d(%d,xsize,ysize);\
 var fill_canvas_ctx = fill_canvas.getContext(\"2d\");\
 fill_canvas_ctx.clearRect(0,0,xsize,ysize);\
 fill_canvas_ctx.putImageData(image, 0, 0);\
};",canvas_root_id,canvas_type,canvas_root_id,FILL_CANVAS);
}

void add_js_ruler(FILE *js_include_file,
int canvas_root_id,double x,double y,double sizex,double sizey,char *font,
char *stroke_color,double stroke_opacity,char *fill_color,double fill_opacity,
int line_width,int dynamic){
 fprintf(js_include_file,"\n<!-- begin command ruler -->\n\
 var ruler_data = new Array(3);\
 var ruler%d = function(){\
  var full = 2*Math.PI;\
  var once = true;\
  var canvas = create_canvas%d(3000,xsize,ysize);\
  var ctx = canvas.getContext(\"2d\");\
  var canvas_temp =  document.createElement(\"canvas\");\
  var size_x = xsize*(%f)/(xmax - xmin);\
  var size_y = ysize*(%f)/(ymax - ymin);\
  var dx = xsize/(xmax - xmin);\
  var dy = 0.8*ysize/(ymax - ymin);\
  canvas_temp.width = xsize;\
  canvas_temp.height = ysize;\
  var ctx_temp = canvas_temp.getContext(\"2d\");\
  var xcenter = x2px(%f);\
  var ycenter = y2px(%f);\
  var ruler_x = xcenter;\
  var ruler_y = ycenter;\
  ctx_temp.font = \"%s\";\
  ctx_temp.strokeStyle = \"rgba(%s,%f)\";\
  ctx_temp.fillStyle = \"rgba(%s,%f)\";\
  ctx_temp.lineWidth = %d;\
  ctx_temp.save();\
  if(once){\
   ctx_temp.beginPath();\
   ctx_temp.moveTo(ruler_x,ruler_y);\
   ctx_temp.lineTo(ruler_x+size_x,ruler_y);\
   ctx_temp.lineTo(ruler_x+size_x,ruler_y-size_y);\
   ctx_temp.lineTo(ruler_x,ruler_y-size_y);\
   ctx_temp.lineTo(ruler_x,ruler_y);\
   ctx_temp.closePath();\
   ctx_temp.fill();\
   ctx_temp.stroke();\
   ctx_temp.fillStyle = ctx_temp.strokeStyle;\
   var txtsize;\
   var num = 1;\
   for(var p = dx ; p < size_x ; p = p+dx){\
     txtsize = 0.5*(ctx_temp.measureText(num).width);\
     ctx_temp.fillText(num,ruler_x + p -txtsize,ruler_y - 0.9*dy);\
     num++;\
   };\
   ctx_temp.strokeStyle = \"rgba(0,0,255,0.6)\";\
   ctx_temp.lineWidth = 2;\
   for(var p = 0; p < size_x ; p = p+dx){\
    ctx_temp.beginPath();\
    ctx_temp.moveTo(ruler_x+p,ruler_y);\
    ctx_temp.lineTo(ruler_x+p,ruler_y-0.8*dy);\
    ctx_temp.closePath();\
    ctx_temp.stroke();\
   };\
   ctx_temp.strokeStyle = \"rgba(0,0,255,0.6)\";\
   ctx_temp.lineWidth = 1;\
   for(var p = 0; p < size_x ; p = p+0.5*dx){\
    ctx_temp.beginPath();\
    ctx_temp.moveTo(ruler_x+p,ruler_y);\
    ctx_temp.lineTo(ruler_x+p,ruler_y-0.6*dy);\
    ctx_temp.closePath();\
    ctx_temp.stroke();\
   };\
   ctx_temp.strokeStyle = \"rgba(255,0,0,0.6)\";\
   ctx_temp.lineWidth = 0.5;\
   for(var p = 0; p < size_x ; p = p+0.1*dx){\
    ctx_temp.beginPath();\
    ctx_temp.moveTo(ruler_x+p,ruler_y);\
    ctx_temp.lineTo(ruler_x+p,ruler_y-0.4*dy);\
    ctx_temp.closePath();\
    ctx_temp.stroke();\
   };\
   ctx_temp.drawImage(canvas,ruler_x,ruler_y);\
   once = false;\
  }",canvas_root_id,canvas_root_id,sizex,sizey,x,y,font,stroke_color,stroke_opacity,fill_color,fill_opacity,line_width);
 
 if( dynamic == -1 ){
 fprintf(js_include_file,"\
 ctx.drawImage(canvas_temp,0,0);\
   if(wims_status != \"done\"){\
    canvas_div.addEventListener( 'mouseup'   , ruler_stop,false);\
    canvas_div.addEventListener( 'mousedown' , ruler_start,false);\
    canvas_div.addEventListener( 'mousemove' , ruler_move,false);\
    canvas_div.addEventListener( 'touchstart', function(e){ e.preventDefault();ruler_start(e.changedTouches[0]);},false);\
    canvas_div.addEventListener( 'touchmove', function(e){ e.preventDefault();ruler_move(e.changedTouches[0]);},false);\
    canvas_div.addEventListener( 'touchend', function(e){ e.preventDefault();ruler_stop(e.changedTouches[0]);},false);\
   };\
   function ruler_stop(evt){\
    ruler_data[0] = ruler_x;\
    ruler_data[1] = ruler_y;\
    ruler_data[2] = angle;\
    return;\
   };\
   var ruler_click_cnt = 0;\
   function ruler_start(evt){\
    var mouse = dragstuff.getMouse(evt,canvas);\
    var mouse_y = mouse.y;\
    if( mouse_y > ysize - 20 ){return;};\
    var mouse_x = mouse.x;\
    if( mouse_x > ruler_x - 50 && mouse_x < ruler_x + size_x + 50){\
     if( mouse_y > ruler_y - 50 && mouse_y < ruler_y + size_y + 50){\
      ruler_click_cnt++;\
      ruler_move(evt);\
      return;\
     };\
    }else{ruler_click_cnt = 0; return;};\
   };\
   var angle = 0;\
   function ruler_move(evt){\
    var mouse = dragstuff.getMouse(evt,canvas);\
    switch(ruler_click_cnt){\
     case 1:\
      angle = 0;\
      ruler_y = mouse.y;\
      if( ruler_y > ysize - 20 ){ruler_y = 0.5*ysize;ruler_x = 0.5*xsize;return;};\
      ruler_x = mouse.x;\
      if( x_use_snap_to_grid == 1 ){\
       ruler_x = snap_to_x(ruler_x);\
      };\
      if( y_use_snap_to_grid == 1 ){\
       ruler_y = snap_to_y(ruler_y);\
      };\
      ctx.clearRect(0,0,xsize,ysize);\
      ctx.save();\
      ctx.translate(ruler_x - xcenter,ruler_y - ycenter);\
      ctx.drawImage(canvas_temp,0,0);\
      ctx.restore();\
      break;\
     case 2:\
      angle = find_angle(ruler_x,ruler_y,mouse.x,mouse.y);\
      ctx.clearRect(0,0,xsize,ysize);\
      ctx.save();\
      ctx.translate(ruler_x,ruler_y);\
      ctx.rotate(angle);\
      ctx.translate( -1*xcenter, -1*ycenter );\
      ctx.drawImage( canvas_temp,0,0 );\
      ctx.restore();\
      userdraw_radius[0] = 2*Math.PI - angle;\
      break;\
     case 3:ruler_click_cnt = 0;break;\
     default:ruler_stop(evt);break;\
    };\
   };\
  };\
  ruler%d();\n",canvas_root_id);
 }
 else
 {
  fprintf(js_include_file,"\
   ctx.clearRect(0,0,xsize,ysize);\
   ctx.save();\
   ctx.translate(ruler_x,ruler_y);\
   ctx.rotate(%d*Math.PI/180);\
   ctx.translate( -1*xcenter, -1*ycenter );\
   ctx.drawImage( canvas_temp,0,0 );\
   ctx.restore();\
  };\
  ruler%d();",dynamic,canvas_root_id);
 }
}

void add_js_protractor(FILE *js_include_file,int canvas_root_id,int type,double xcenter,double ycenter,int size,char *font,char *stroke_color,double stroke_opacity,char *fill_color,double fill_opacity,int line_width,int use_scale,int dynamic){

/*
use_slider_display = 2 : angle in degrees
use_slider_display = 3 : angle in radians
void add_slider_display(FILE *js_include_file,int canvas_root_id,int precision,int font_size,char *font_color,double stroke_opacity){
fprintf(js_include_file,"<!-- begin add_slider_display -->\n\
function show_slider_value(value,use_slider_display)
*/

if( type == 1 ){ /* geodriehoek */
 fprintf(js_include_file,"\n<!-- begin command protractor type 1 -->\n\
 var protractor_data = new Array(3);\
 var protractor%d = function(){\
  var once = true;\
  var full = 2*Math.PI;\
  var canvas = create_canvas%d(2000,xsize,ysize);\
  var ctx = canvas.getContext(\"2d\");\
  var canvas_temp =  document.createElement(\"canvas\");\
  var size = parseInt(xsize*(%d)/(xmax - xmin));\
  canvas_temp.width = xsize;\
  canvas_temp.height = ysize;\
  var ctx_temp = canvas_temp.getContext(\"2d\");\
  var type = %d;\
  var xcenter = x2px(%f);\
  var ycenter = y2px(%f);\
  var half = 0.5*size;\
  var radius1 = 0.6*half;\
  var radius2 = 0.65*half;\
  var radius3 = 0.7*half;\
  ctx_temp.font = \"%s\";\
  ctx_temp.strokeStyle = \"rgba(%s,%f)\";\
  ctx_temp.fillStyle = \"rgba(%s,%f)\";\
  ctx_temp.lineWidth =%d;\
  var use_scale = %d;\
  if( once ){\
   ctx_temp.clearRect(0,0,canvas_temp.width,canvas_temp.height);\
   ctx_temp.beginPath();\
   ctx_temp.moveTo(xcenter-half,ycenter );\
   ctx_temp.lineTo(xcenter,ycenter-half);\
   ctx_temp.lineTo(xcenter+half,ycenter);\
   ctx_temp.lineTo(xcenter-half,ycenter);\
   ctx_temp.moveTo(xcenter,ycenter );\
   ctx_temp.lineTo(xcenter+0.5*half,ycenter-0.5*half);\
   ctx_temp.moveTo(xcenter,ycenter );\
   ctx_temp.lineTo(xcenter-0.5*half,ycenter-0.5*half);\
   ctx_temp.moveTo(xcenter,ycenter );\
   ctx_temp.lineTo(xcenter,ycenter-half);\
   ctx_temp.closePath();\
   ctx_temp.fill();\
   ctx_temp.stroke();\
   ctx_temp.beginPath();\
   ctx_temp.arc(xcenter,ycenter,radius1,0,Math.PI,false);\
   ctx_temp.closePath();\
   if( use_scale == 1 ){\
    ctx_temp.fillStyle = ctx_temp.strokeStyle;\
    var txtsize;\
    for(var p = 45 ; p < 180;p = p+45){\
     txtsize = 0.5*(ctx_temp.measureText(p).width);\
     ctx_temp.fillText(p,xcenter+0.5*half*Math.cos(p*Math.PI/180) - txtsize,ycenter-0.5*half*Math.sin(p*Math.PI/180));\
    };\
   };\
   for(var p = 10 ; p < 180;p = p+10){\
    ctx_temp.beginPath();\
    ctx_temp.moveTo(xcenter+radius1*Math.cos(p*Math.PI/180),ycenter-radius1*Math.sin(p*Math.PI/180));\
    ctx_temp.lineTo(xcenter+radius3*Math.cos(p*Math.PI/180),ycenter-radius3*Math.sin(p*Math.PI/180));\
    ctx_temp.closePath();\
    ctx_temp.stroke();\
   };\
   for(var p = 0 ; p < 180;p=p+2){\
    if(p%%10 != 0){\
     ctx_temp.beginPath();\
     ctx_temp.moveTo(xcenter+radius1*Math.cos(p*Math.PI/180),ycenter-radius1*Math.sin(p*Math.PI/180));\
     ctx_temp.lineTo(xcenter+radius2*Math.cos(p*Math.PI/180),ycenter-radius2*Math.sin(p*Math.PI/180));\
     ctx_temp.closePath();\
     ctx_temp.stroke();\
    };\
   };\
   ctx_temp.drawImage(canvas,xcenter,ycenter);\
   ctx_temp.save();\
   once = false;\
  };\
  ",canvas_root_id,canvas_root_id,size,type,xcenter,ycenter,font,stroke_color,stroke_opacity,fill_color,fill_opacity,line_width,use_scale);
}

if( type != 1 ){
 fprintf(js_include_file,"\n<!-- begin command protractor type 0 -->\n\
 var protractor_data = new Array(3);\
 var protractor%d = function(){\
  var once = true;\
  var full = 2*Math.PI;\
  var canvas = create_canvas%d(2000,xsize,ysize);\
  var ctx = canvas.getContext(\"2d\");\
  var canvas_temp =  document.createElement(\"canvas\");\
  var size = parseInt(xsize*(%d)/(xmax - xmin));\
  canvas_temp.width = xsize;\
  canvas_temp.height = ysize;\
  var ctx_temp = canvas_temp.getContext(\"2d\");\
  var type = %d;\
  var xcenter = x2px(%f);\
  var ycenter = y2px(%f);\
  var half = 0.5*size;\
  var radius1 = 0.8*half;\
  var radius2 = 0.9*half;\
  var radius3 = half;\
  ctx_temp.font = \"%s\";\
  ctx_temp.strokeStyle = \"rgba(%s,%f)\";\
  ctx_temp.fillStyle = \"rgba(%s,%f)\";\
  ctx_temp.lineWidth =%d;\
  var use_scale = %d;\
  if( once ){\
   ctx_temp.clearRect(0,0,xsize,ysize);\
   ctx_temp.arc(xcenter,ycenter,radius1,0,2*Math.PI,false);\
   ctx_temp.arc(xcenter,ycenter,radius2,0,2*Math.PI,false);\
   ctx_temp.arc(xcenter,ycenter,radius3,0,2*Math.PI,false);\
   ctx_temp.fill();\
   ctx_temp.stroke();\
   if( use_scale == 1 ){\
    ctx_temp.fillStyle = ctx_temp.strokeStyle;\
    var txtsize;\
    for(var p = 0 ; p < 360;p = p+45){\
     txtsize = 0.5*(ctx_temp.measureText(p).width);\
     ctx_temp.fillText(p,xcenter+0.6*half*Math.cos(p*Math.PI/180) - txtsize,ycenter-0.6*half*Math.sin(p*Math.PI/180));\
    };\
   };\
   ctx_temp.strokeStyle = \"rgba(255,0,0,0.4)\";\
   for(var p = 0 ; p < 360;p = p+10){\
    ctx_temp.beginPath();\
    ctx_temp.moveTo(xcenter+radius1*Math.cos(p*Math.PI/180),ycenter-radius1*Math.sin(p*Math.PI/180));\
    ctx_temp.lineTo(xcenter+radius3*Math.cos(p*Math.PI/180),ycenter-radius3*Math.sin(p*Math.PI/180));\
    ctx_temp.closePath();\
    ctx_temp.stroke();\
   };\
   ctx_temp.strokeStyle = \"rgba(0,0,255,0.4)\";\
   for(var p = 0 ; p < 360;p=p+2){\
     ctx_temp.beginPath();\
     ctx_temp.moveTo(xcenter+radius2*Math.cos(p*Math.PI/180),ycenter-radius2*Math.sin(p*Math.PI/180));\
     ctx_temp.lineTo(xcenter+radius3*Math.cos(p*Math.PI/180),ycenter-radius3*Math.sin(p*Math.PI/180));\
     ctx_temp.closePath();\
     ctx_temp.stroke();\
   };\
   ctx_temp.strokeStyle = \"rgba(0,0,0,0.6)\";\
   for(var p = 0 ; p < 360;p=p+45){\
     ctx_temp.beginPath();\
     ctx_temp.moveTo(xcenter,ycenter);\
     ctx_temp.lineTo(xcenter+radius3*Math.cos(p*Math.PI/180),ycenter-radius3*Math.sin(p*Math.PI/180));\
     ctx_temp.closePath();\
     ctx_temp.stroke();\
   };\
   ctx_temp.drawImage(canvas,0,0);\
   ctx_temp.save();\
   once = false;\
  };\n",canvas_root_id,canvas_root_id,size,type,xcenter,ycenter,font,stroke_color,stroke_opacity,fill_color,fill_opacity,line_width,use_scale);
}
if( dynamic == -1 ){ /* rotate the protractors */
 fprintf(js_include_file,"\
  var protractor_x = xcenter;\
  var protractor_y = ycenter;\
  ctx.drawImage(canvas_temp,0,0);\
  var angle = 0;\
  if(wims_status != \"done\"){\
   canvas_div.addEventListener( 'mouseup'   , protractor_stop,false);\
   canvas_div.addEventListener( 'mousedown' , protractor_start,false);\
   canvas_div.addEventListener( 'mousemove' , protractor_move,false);\
   canvas_div.addEventListener( 'touchstart', function(e){ e.preventDefault();protractor_start(e.changedTouches[0]);},false);\
   canvas_div.addEventListener( 'touchmove', function(e){ e.preventDefault();protractor_move(e.changedTouches[0]);},false);\
   canvas_div.addEventListener( 'touchend', function(e){ e.preventDefault();protractor_stop(e.changedTouches[0]);},false);\
  };\
  function protractor_stop(evt){\
   protractor_data[0] = protractor_x;\
   protractor_data[1] = protractor_y;\
   protractor_data[2] = angle;\
   return;\
  };\
  var protractor_click_cnt = 0;\
  function protractor_start(evt){\
   var mouse = dragstuff.getMouse(evt,canvas);\
   var mouse_y = mouse.y;\
   if( mouse_y > ysize - 20 ){return;};\
   var mouse_x = mouse.x;\
   if( mouse_x > protractor_x - half && mouse_x < protractor_x + half ){\
    if( mouse_y > protractor_y - half && mouse_y < protractor_y + half ){\
     protractor_click_cnt++;\
     protractor_move(evt);\
     return;\
    };\
   }else{protractor_click_cnt = 0; return;};\
  };\
  function protractor_move(evt){\
   var mouse = dragstuff.getMouse(evt,canvas);\
   switch(protractor_click_cnt){\
    case 1:\
      angle = 0;\
      protractor_y = mouse.y;\
      if( protractor_y > ysize - 20 ){protractor_y = 0.5*ysize;protractor_x = 0.5*xsize;return;};\
      protractor_x = mouse.x;\
      if( x_use_snap_to_grid == 1 ){\
       protractor_x = snap_to_x(protractor_x);\
      };\
      if( y_use_snap_to_grid == 1 ){\
       protractor_y = snap_to_y(protractor_y);\
      };\
      ctx.clearRect(0,0,xsize,ysize);\
      ctx.save();\
      ctx.translate(protractor_x - xcenter,protractor_y - ycenter);\
      ctx.drawImage(canvas_temp,0,0);\
      ctx.restore();\
      break;\
    case 2:\
     angle = find_angle(protractor_x,protractor_y,mouse.x,mouse.y);\
     ctx.clearRect(0,0,xsize,ysize);\
     ctx.save();\
     ctx.translate(protractor_x,protractor_y);\
     ctx.rotate(angle);\
     ctx.translate( -1*xcenter, -1*ycenter );\
     ctx.drawImage( canvas_temp,0,0 );\
     ctx.restore();\
     userdraw_radius[0] =2*Math.PI- angle;\
     break;\
    case 3:protractor_click_cnt = 0;break;\
    default:protractor_stop(evt);\
   };\
  };\
 };\
 protractor%d();\n\
",canvas_root_id);
}
else
{
 fprintf(js_include_file,"\
  ctx.save();\
  ctx.translate(xcenter,ycenter);\
  ctx.rotate(%d*Math.PI/180);\
  ctx.translate( -1*xcenter, -1*ycenter );\
  ctx.drawImage( canvas_temp,0,0 );\
  ctx.restore();\
 };\
 protractor%d();\
",dynamic,canvas_root_id);
} /* end dynamic == -1*/

}

