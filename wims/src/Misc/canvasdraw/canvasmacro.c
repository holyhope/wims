void add_drag_code(FILE *js_include_file,int canvas_cnt,int canvas_root_id);
void add_trace_js_mouse(FILE *js_include_file,int canvas_cnt,int canvas_root_id,char *stroke_color,char *jsmath,int font_size,double stroke_opacity,int line_width,int crosshair_size);
void add_setlimits(FILE *js_include_file, int canvas_root_id);
void add_safe_eval(FILE *js_include_file);
void add_to_js_math(FILE *js_include_file);
void add_calc_y(FILE *js_include_file,int canvas_root_id,char *jsmath);
void add_jsplot(FILE *js_include_file,int canvas_root_id);

void *my_newmem(size_t size);
void canvas_error(char *msg);
char *eval(int xsize,int ysize,char *fun,double xmin,double xmax,double ymin,double ymax,int xsteps,int precision);
char *eval_parametric(int xsize,int ysize,char *fun1,char* fun2,double xmin,double xmax,double ymin,double ymax, double tmin,double tmax,int plotsteps,int precision);
char *eval_levelcurve(int xsize,int ysize,char *fun,double xmin,double xmax,double ymin,double ymax,int plotsteps,int precision,double level);
char *data2js_array(int data[],int len);
char *xy2js_array(int xy[],int len);
char *double_xy2js_array(double xy[],int len,int decimals);
int find_number_of_digits(int i);
int x2px(double x);
int y2px(double y);
void add_js_mouse(FILE *js_include_file,int canvas_cnt,int canvas_root_id,int precision,char *stroke_color,int font_size,double stroke_opacity);
void add_js_points(FILE *js_include_file,int num,char *draw_type,int line_width, int radius ,char *stroke_color,double stroke_opacity,int use_filled,char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_circles(FILE *js_include_file,int num,char *draw_type, int line_width, int radius , char *stroke_color,double stroke_opacity,int use_filled,char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_segments(FILE *js_include_file,int num,char *draw_type,int line_width, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_polyline(FILE *js_include_file,char *draw_type,int line_width, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_lines(FILE *js_include_file,int num,char *draw_type,int line_width, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_arrows(FILE *js_include_file,int num,char *draw_type,int line_width,int type, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1,int arrow_head);
void add_js_crosshairs(FILE *js_include_file,int num,char *draw_type,int line_width, int crosshair_size ,char *stroke_color,double stroke_opacity);
void add_js_paths(FILE *js_include_file,int num,char *draw_type,int line_width, int closed_path,char *stroke_color,double stroke_opacity,int use_filled, char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_poly(FILE *js_include_file,int num,char *draw_type,int line_width,char *stroke_color,double stroke_opacity,int use_filled,char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_rect(FILE *js_include_file,int num,int roundrect,char *draw_type,int line_width,char *stroke_color,double stroke_opacity,int use_filled,char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_floodfill(FILE *js_include_file,int canvas_root_id);
void add_js_filltoborder(FILE *js_include_file,int canvas_root_id);
void add_js_text(FILE *js_include_file,int canvas_root_id,int fontsize,char *font_family,char *font_color,double stroke_opacity,int use_rotate,int angle,int use_translate,int translate_x,int translate_y);
void add_input_circle(FILE *js_include_file,int type,int num);
void add_input_segment(FILE *js_include_file,int num);
void add_input_line(FILE *js_include_file,int num);
void add_input_polyline(FILE *js_include_file);
void add_textarea_polygon(FILE *js_include_file);
void add_input_crosshair(FILE *js_include_file,int num);
void add_input_arrow(FILE *js_include_file,int num);
void add_input_xy(FILE *js_include_file, int canvas_root_id);
void add_input_xyr(FILE *js_include_file, int canvas_root_id);
void add_input_x1y1x2y2(FILE *js_include_file, int canvas_root_id);
void add_textarea_xy(FILE *js_include_file, int canvas_root_id);


/* prints to stdout : should be last */
void add_js_tooltip(int canvas_root_id,char *tooltip_text,char *bgcolor,int xsize,int ysize);
/* ............. */
 
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
var canvas_rect;\
function user_draw(evt){\
 canvas_rect = canvas_userdraw.getBoundingClientRect();\
 y0 = evt.clientY - canvas_rect.top;\
 if(y0 < ysize + 1){\
  x0 = evt.clientX - canvas_rect.left;\
  if( x_use_snap_to_grid == 1 ){\
   x0 = snap_to_x(x0);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y0 = snap_to_y(y0);\
  };\
  if(evt.which == 1){\
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
    canvas_rect = canvas_userdraw.getBoundingClientRect();\
    y1 = evt.clientY - canvas_rect.top;\
    x1 = evt.clientX - canvas_rect.left;\
    if( x_use_snap_to_grid == 1 ){\
     x0 = snap_to_x(x0);\
    };\
    if( y_use_snap_to_grid == 1 ){\
     y0 = snap_to_y(y0);\
    };\
    userdraw_radius[xy_cnt] = parseInt(Math.sqrt( (x1-x0)*(x1-x0) + (y1-y0)*(y1-y0) ));\
    userdraw_x[xy_cnt] = x0;\
    userdraw_y[xy_cnt] = y0;\
    context_userdraw.clearRect(0,0,xsize,ysize);\
    draw_circles(context_userdraw,userdraw_x,userdraw_y,userdraw_radius,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);\
  }\
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

void add_js_crosshairs(FILE *js_include_file,int num,char *draw_type,int line_width, int crosshair_size ,char *stroke_color,double stroke_opacity){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on currect active canvas -->\n\
var num = %d;\
var crosshair_size = parseInt(0.5*%d);\
var canvas_rect;\
var line_width = %d;\
var stroke_color = \"%s\";\
var stroke_opacity = %f;\
context_userdraw.lineWidth = line_width;\
context_userdraw.strokeStyle=\"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
function user_drag(evt){return;}\
function user_draw(evt){\
 canvas_rect = canvas_userdraw.getBoundingClientRect();\
 var x = evt.clientX - canvas_rect.left;\
 var y = evt.clientY - canvas_rect.top;\
 if( x_use_snap_to_grid == 1 ){\
  x = snap_to_x(x);\
 };\
 if( y_use_snap_to_grid == 1 ){\
  y = snap_to_y(y);\
 };\
 var x1,y1,x2,y2;\
 if(evt.which == 1){\
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
    context_userdraw = null;context_userdraw = canvas_userdraw.getContext(\"2d\");context_userdraw.clearRect(0,0,xsize,ysize);xy_cnt--;\
    draw_crosshairs(context_userdraw,userdraw_x,userdraw_y,line_width,crosshair_size,stroke_color,stroke_opacity,0,0,0,[0,0]);\
    return;\
   }\
  }\
 }\
};",draw_type,num,crosshair_size,line_width,stroke_color,stroke_opacity);
}

void add_js_rect(FILE *js_include_file,int num,int roundrect,char *draw_type,int line_width,char *stroke_color,double stroke_opacity,int use_filled,char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on currect active canvas -->\n\
var canvas_rect;\
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
var use_translate = 0;\
var vector=[0,0];\
var closed_path = 1;\
var clickcnt = 0;\
xy_cnt = 0;\
var x0,y0,x1,y1;\
var marge = 10*line_width;\
function user_draw(evt){\
 canvas_rect = canvas_userdraw.getBoundingClientRect();\
 y0 = evt.clientY - canvas_rect.top;\
 if( y0  < ysize + 1 ){\
  x0 = evt.clientX - canvas_rect.left;\
  if( x_use_snap_to_grid == 1 ){\
   x0 = snap_to_x(x0);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y0 = snap_to_y(y0);\
  };\
  if( evt.which == 1 ){\
   if(clickcnt == 0 ){\
    clickcnt = 1;\
    userdraw_x[xy_cnt] = x0;userdraw_y[xy_cnt] = y0;xy_cnt++;\
   }\
   else\
   {\
    clickcnt = 0;\
    if(roundrect == 0 ){\
     draw_rects(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,use_translate,vector);\
    }\
    else\
    {\
     draw_roundrects(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,use_translate,vector);\
    }\
    if( num != 1 ){ xy_cnt++; }else{xy_cnt--;}\
   }\
  }\
  else\
  {\
   canvas_remove(x0,y0);\
  };\
 };\
};\
function user_drag(evt){\
 if( clickcnt == 1 ){\
  canvas_rect = canvas_userdraw.getBoundingClientRect();\
  y1 = evt.clientY - canvas_rect.top;\
  x1 = evt.clientX - canvas_rect.left;\
  if( x_use_snap_to_grid == 1 ){\
  x1 = snap_to_x(x1);\
  };\
  if( y_use_snap_to_grid == 1 ){\
  y1 = snap_to_y(y1);\
  };\
  userdraw_x[xy_cnt] = x1;\
  userdraw_y[xy_cnt] = y1;\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  if( roundrect == 0 ){\
   draw_rects(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,use_translate,vector);\
  }\
  else\
  {\
   draw_roundrects(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,use_translate,vector);\
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
     xy_cnt--;\
     context_userdraw.clearRect(0,0,xsize,ysize);\
     if(xy_cnt < 2){xy_cnt = 0;click_cnt = 0;userdraw_x = [];userdraw_y = [];return;};\
     if( roundrect == 0 ){\
      draw_rects(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,use_translate,vector);\
     }\
     else\
     {\
      draw_roundrects(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,use_translate,vector);\
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
var canvas_rect;\
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
function user_draw(evt){\
 canvas_rect = canvas_userdraw.getBoundingClientRect();\
 y = evt.clientY - canvas_rect.top;\
 if( y < ysize + 1 ){\
  x = evt.clientX - canvas_rect.left;\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
  if( evt.which == 1){\
   if( num == -1 && xy_cnt > 2 ){\
    if( x - marge < userdraw_x[0] && x + marge > userdraw_x[0]){\
     if( y - marge < userdraw_y[0] && y + marge > userdraw_y[0]){\
      userdraw_x.splice(xy_cnt,1);userdraw_y.splice(xy_cnt,1);\
      draw_paths(context_userdraw,userdraw_x,userdraw_y,line_width,closed_path,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,use_translate,vector);\
      done = 1;return;\
     };\
    };\
   }\
   else\
   {\
    if( xy_cnt == num - 1){\
     draw_paths(context_userdraw,userdraw_x,userdraw_y,line_width,closed_path,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,use_translate,vector);\
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
};\
function user_drag(evt){\
 if( done == 0 ){\
  canvas_rect = canvas_userdraw.getBoundingClientRect();\
  x = evt.clientX - canvas_rect.left;\
  y = evt.clientY - canvas_rect.top;\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  userdraw_x[xy_cnt] = x;userdraw_y[xy_cnt] = y;\
  draw_paths(context_userdraw,userdraw_x,userdraw_y,line_width,closed_path,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,use_translate,vector);\
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

/*  function draw_circles(ctx,x_points,y_points,radius,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);*/
void add_js_points(FILE *js_include_file,int num,char *draw_type,int line_width, int radius ,char *stroke_color,double stroke_opacity,int use_filled,char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on final canvas -->\n\
var num = %d;\
var canvas_rect;\
userdraw_radius[0] = %d;\
var line_width = %d;\
var stroke_color = \"%s\";\
var stroke_opacity = %f;\
var use_filled = %d;\
var fill_color = \"%s\";\
var fill_opacity = %f;\
var use_dashed = %d;\
var dashtype0 = %d;\
var dashtype1 = %d;\
function user_drag(evt){return;};\
function user_draw(evt){\
 canvas_rect = canvas_userdraw.getBoundingClientRect();\
 var y = evt.clientY - canvas_rect.top;\
 if( y < ysize + 1 ){\
  var lu = userdraw_x.length;\
  var x = evt.clientX - canvas_rect.left;\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
  if(evt.which == 1){\
   if( num == 1 ){\
   userdraw_x[0] = x;\
   userdraw_y[0] = y;\
   }\
   else\
   {\
   userdraw_x[lu] = x;\
   userdraw_y[lu] = y;\
   userdraw_radius[lu] = userdraw_radius[0];\
   };\
   context_userdraw.clearRect(0,0,xsize,ysize);\
   draw_circles(context_userdraw,userdraw_x,userdraw_y,userdraw_radius,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);\
  }\
  else\
  {\
  canvas_remove(x,y);\
  }\
 }\
};\
function canvas_remove(x,y){\
 var marge = 4*line_width;\
 for(var p = 0;p < userdraw_x.length ; p++){\
  if(userdraw_x[p] < x + marge && userdraw_x[p] > x - marge ){\
   if(userdraw_y[p] < y + marge && userdraw_y[p] > y - marge ){\
    userdraw_x.splice(p,1);userdraw_y.splice(p,1);\
    context_userdraw = null;context_userdraw = canvas_userdraw.getContext(\"2d\");context_userdraw.clearRect(0,0,xsize,ysize);\
    draw_circles(context_userdraw,userdraw_x,userdraw_y,userdraw_radius,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);\
    return;\
   }\
  }\
 }\
};",draw_type,num,radius,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1);

}
void add_js_polyline(FILE *js_include_file,char *draw_type,int line_width, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on final canvas -->\n\
var canvas_rect;\
var cnt = 0;\
var line_width = %d;\
var stroke_color = \"%s\";\
var stroke_opacity = %f;\
var use_dashed = %d;\
var dashtype0 = %d;\
var dashtype1 = %d;\
function user_draw(evt){\
 canvas_rect = canvas_userdraw.getBoundingClientRect();\
 var x = evt.clientX - canvas_rect.left;\
 var y = evt.clientY - canvas_rect.top;\
 var lu = userdraw_x.length;\
 canvas_rect = canvas_userdraw.getBoundingClientRect();\
 if( x_use_snap_to_grid == 1 ){\
  x = snap_to_x(x);\
 };\
 if( y_use_snap_to_grid == 1 ){\
  y = snap_to_y(y);\
 };\
 if( evt.which == 1 ){\
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
  canvas_rect = canvas_userdraw.getBoundingClientRect();\
  var x = evt.clientX - canvas_rect.left;\
  var y = evt.clientY - canvas_rect.top;\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
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
  return;\
 }\
};",draw_type,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);
}

void add_js_segments(FILE *js_include_file,int num,char *draw_type,int line_width, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on final canvas -->\n\
var canvas_rect;\
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
 var y = evt.clientY - canvas_rect.top;\
 if( y < ysize + 1){\
  canvas_rect = canvas_userdraw.getBoundingClientRect();\
  var x = evt.clientX - canvas_rect.left;\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
  if( evt.which == 1 ){\
   if( lu%%2 == 0){\
    x0 = x;y0 = y;\
    if(num == 1){ userdraw_x = [];userdraw_y = [];userdraw_x[0] = x0;userdraw_y[0] = y0;} else {userdraw_x[lu] = x0;userdraw_y[lu] = y0;}\
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
 }\
};\
function user_drag(evt){\
 canvas_rect = canvas_userdraw.getBoundingClientRect();\
 var x = evt.clientX - canvas_rect.left;\
 var y = evt.clientY - canvas_rect.top;\
 var lu = userdraw_x.length;\
 if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
 };\
 if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
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
     draw_segments(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\
    }\
    return;\
   }\
  }\
 }\
};",draw_type,num,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);
}

void add_js_lines(FILE *js_include_file,int num,char *draw_type,int line_width, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1){
fprintf(js_include_file,"\n<!-- begin userdraw \"%s\" on final canvas -->\n\
var canvas_rect;\
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
 var y = evt.clientY - canvas_rect.top;\
 if( y < ysize + 1){\
  canvas_rect = canvas_userdraw.getBoundingClientRect();\
  var x = evt.clientX - canvas_rect.left;\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
  if( evt.which == 1 ){\
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
   }\
  }\
  else\
  {\
   canvas_remove(x,y);\
  }\
 }\
};\
function user_drag(evt){\
 canvas_rect = canvas_userdraw.getBoundingClientRect();\
 var x = evt.clientX - canvas_rect.left;\
 var y = evt.clientY - canvas_rect.top;\
 var lu = userdraw_x.length;\
 if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
 };\
 if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
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
var canvas_rect;\
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
  draw_arrows(context_userdraw,userdraw_x,userdraw_y,arrow_head,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,type,use_rotate,angle,use_translate,vector);\
 }\
 var y = evt.clientY - canvas_rect.top;\
 if( y < ysize + 1){\
  canvas_rect = canvas_userdraw.getBoundingClientRect();\
  var x = evt.clientX - canvas_rect.left;\
  if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
  };\
  if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
  };\
  if( evt.which == 1 ){\
   if( lu%%2 == 0){\
    x0 = x;y0 = y;\
    if(num == 1){ userdraw_x = [];userdraw_y = [];userdraw_x[0] = x0;userdraw_y[0] = y0;} else {userdraw_x[lu] = x0;userdraw_y[lu] = y0;}\
    user_drag(evt);\
   }\
   else\
   {\
    if( num == 1 ){ userdraw_x[1] = x;userdraw_y[1] = y;} else {userdraw_x[lu] = x;userdraw_y[lu] = y;};\
    draw_arrows(context_userdraw,userdraw_x,userdraw_y,arrow_head,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,type,use_rotate,angle,use_translate,vector);\
   }\
  }\
  else\
  {\
   canvas_remove(x,y);\
  }\
 }\
};\
function user_drag(evt){\
 canvas_rect = canvas_userdraw.getBoundingClientRect();\
 var x = evt.clientX - canvas_rect.left;\
 var y = evt.clientY - canvas_rect.top;\
 var lu = userdraw_x.length;\
 if( x_use_snap_to_grid == 1 ){\
   x = snap_to_x(x);\
 };\
 if( y_use_snap_to_grid == 1 ){\
   y = snap_to_y(y);\
 };\
 if( lu%%2 != 0 ){\
  context_userdraw.clearRect(0,0,xsize,ysize);\
  draw_arrows(context_userdraw,[x0,x],[y0,y],arrow_head,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,type,use_rotate,angle,use_translate,vector);\
  if( lu > 0){\
    draw_arrows(context_userdraw,userdraw_x,userdraw_y,arrow_head,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,type,use_rotate,angle,use_translate,vector);\
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
     draw_arrows(context_userdraw,userdraw_x,userdraw_y,arrow_head,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,type,use_rotate,angle,use_translate,vector,type,use_rotate,angle,use_translate,vector);\
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
temp_x = [];\
temp_y = [];\
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
var x0,y0;\
canvas_rect = canvas_userdraw.getBoundingClientRect();\
function user_draw(evt){\
 if(evt.which == 1 ){\
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
   canvas_remove(evt.clientX - canvas_rect.left,evt.clientY - canvas_rect.top);\
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
  temp_y[xy_cnt] = evt.clientY - canvas_rect.top;\
  if( temp_y[xy_cnt] < ysize + 1){\
   temp_x[xy_cnt] = evt.clientX - canvas_rect.left;\
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


void add_js_text(FILE *js_include_file,int canvas_root_id,int font_size,char *font_family,char *font_color,double stroke_opacity,int use_rotate,int angle,int use_translate,int translate_x,int translate_y){
fprintf(js_include_file,"\n<!-- begin command userdraw text -->\n\
canvas_div.addEventListener(\"keydown\",user_text,false);\
var context_userdraw = canvas_userdraw.getContext(\"2d\");\
var font_color = \"%s\";\
var font_opacity = %f;\
var font_size = %d;\
var font_family = \"%s\";\
context_userdraw.fillStyle = \"rgba(\"+font_color+\",\"+font_opacity+\")\";\
context_userdraw.font = font_family;\
var userdraw_text = new Array();\
var txt_cnt = 0;\
var txt=\"\";\
var x_txt = 0;\
var y_txt = 0;\
var w_txt = 0;\
var typing = 0;\
var canvas_rect = canvas_userdraw.getBoundingClientRect();\
function user_draw(evt){\
 y_txt = evt.clientY - canvas_rect.top;\
 x_txt = evt.clientX - canvas_rect.left;\
 if( x_use_snap_to_grid == 1 ){\
   x_txt = snap_to_x(x_txt);\
 };\
 if( y_use_snap_to_grid == 1 ){\
   y_txt = snap_to_y(y_txt);\
 };\
 return;\
};\
function user_drag(evt){\
return;\
};\
function user_text(evt){\
 var kc = evt.keyCode;\
 if( kc== 8 || kc == 27 || kc == 46 ){\
  if(typing == 1 ){\
    w = context_userdraw.measureText(txt).width;\
    context_userdraw.clearRect(x_txt-2,y_txt-font_size-2,w+2,font_size+2);\
    txt = \"\";\
  }\
  else\
  {\
   for( var p=0 ; p < txt_cnt; p++){\
    var tmp = (userdraw_text[p]).split(\":\");\
    w = context_userdraw.measureText(tmp[0]).width;\
    var y1 = y_txt - font_size;\
    var y2 = y_txt + font_size;\
    if( tmp[1] < y2 && tmp[1] > y1){\
     var x1 = x_txt - font_size;\
     var x2 = x_txt + w;\
     if( tmp[0] < x2 && tmp[0] > x1){\
      if (confirm(\"delete this text : \"+tmp[2]+\"?\")){\
       context_userdraw.clearRect(x1,y1,x2,y2);\
       userdraw_text.splice(p,1);\
       txt_cnt--;\
       return;\
      };\
     };\
    };\
   };\
  };\
 }\
 else\
 {\
  if( kc < 126 && kc > 40 ){\
   typing = 1;\
   txt=txt+String.fromCharCode(kc);\
   w = context_userdraw.measureText(txt).width;\
   context_userdraw.save();\
   context_userdraw.fillStyle = \"lightblue\";\
   context_userdraw.beginPath();\
   context_userdraw.rect(x_txt,y_txt-font_size,w,font_size);\
   context_userdraw.closePath();\
   context_userdraw.fill();\
   context_userdraw.restore();\
   context_userdraw.fillText(txt,x_txt,y_txt);\
  }\
  else\
  {\
   if(kc == 13 ){\
    w = context_userdraw.measureText(txt).width;\
    context_userdraw.clearRect(x_txt,y_txt-font_size,w,font_size);\
    context_userdraw.fillText(txt,x_txt,y_txt);\
    userdraw_text[txt_cnt] = x_txt+\":\"+y_txt+\":\"+txt;\
    txt=\"\";\
    w = 0;\
    txt_cnt++;\
    typing = 0;\
    return;\
   };\
  };\
 };\
};",font_color,stroke_opacity,font_size,font_family);

}


void add_js_mouse(FILE *js_include_file,int canvas_cnt,int canvas_root_id,int precision,char *stroke_color,int font_size,double stroke_opacity){
fprintf(js_include_file,"\n<!-- begin command mouse on current canvas -->\n\
function use_mouse_coordinates(){\
 var current_canvas = create_canvas%d(%d,xsize,ysize);\
 var current_context = current_canvas.getContext(\"2d\");\
 current_context.clearRect(0,0,xsize,ysize);\
 current_canvas.addEventListener(\"mousemove\",show_coordinate%d,false);\
 current_canvas.addEventListener(\"touchmove\",show_coordinate%d,false);\
 var prec = Math.log(%d)/(Math.log(10));\
 function show_coordinate%d(evt){\
  var canvas_rect = (current_canvas).getBoundingClientRect();\
  var x = evt.clientX - canvas_rect.left;\
  var y = evt.clientY - canvas_rect.top;\
  var m_data = \"(\"+(px2x(x)).toFixed(prec)+\":\"+(px2y(y)).toFixed(prec)+\")\";\
  var s = parseInt(0.8*%d*(m_data.toString()).length);\
  current_context.font = \"%dpx Ariel\";\
  current_context.fillStyle = \"rgba(%s,%f)\";\
  current_context.clearRect(0,0,s,1.2*%d);\
  current_context.fillText(m_data,0,%d);\
 };\
};",canvas_root_id,MOUSE_CANVAS,canvas_root_id,canvas_root_id,precision,canvas_root_id,font_size,font_size,stroke_color,stroke_opacity,font_size,font_size);
}
/* to avoid easy js-code injection...but is it a real problem ? */
void add_safe_eval(FILE *js_include_file){
fprintf(js_include_file," \nfunction safe_eval(exp){\
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
adds inputfield for x-value: returns the js-calculated y-value after click on 'OK' button
draws a non-configurable crosshair on this calculated location
*/
void add_calc_y(FILE *js_include_file,int canvas_root_id,char *jsmath){
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
if( typeof xaxislabel !== 'undefined' ){label_x = xaxislabel;}\
if( typeof yaxislabel !== 'undefined' ){label_y = yaxislabel;}\
calc_div.innerHTML=\"<br /><span style='font-style:italic;font-size:10px'>\"+label_x+\" : <input type='text' size='4' value='' id='calc_input_x' style='text-align:center;color:blue;background-color:orange;' />&nbsp;\"+ label_y+\" : <input type='text' size='6' value='' id='calc_output_y' style='text-align:center;color:blue;background-color:lightgreen;' readonly' /><input id='calc_button' type='button' value='OK' onclick=''  style='color:red;background-color:lightblue;' /></span> \";\
var calc_button = document.getElementById(\"calc_button\");\
calc_button.addEventListener(\"mousedown\",function(e){var x_value=document.getElementById(\"calc_input_x\").value;\
var y_value = eval_jsmath(x_value);\
document.getElementById(\"calc_output_y\").value = y_value;\
if(isNaN(y_value)){return;};\
var canvas = create_canvas%d(123,xsize,ysize);\
var ctx = canvas.getContext(\"2d\");\
draw_crosshairs(ctx,[x2px(x_value)],[y2px(y_value)],1,5,\"#000000\",1,0,0,0,[0,0]);return;},false);\
};add_calc_y();",jsmath,canvas_root_id,canvas_root_id);
}
/*
 x-value of the mouse will be used to calculate via javascript the corresponding y-value using the verbatim js-math function
 a configurable crosshair and vertical/horizontal crosshair lines will be drawn
 function is called "use_mouse_coordinates() and thus can not be combined with command 'mouse'
*/
void add_trace_js_mouse(FILE *js_include_file,int canvas_cnt,int canvas_root_id,char *stroke_color,char *jsmath,int font_size,double stroke_opacity,int line_width,int crosshair_size){
fprintf(js_include_file,"\n<!-- begin command add_trace_jsmath  trace_canvas -->\n\
use_jsmath=1;\
function use_trace_jsmath(){\
if( wims_status == \"done\" ){return;};\
 var label_x = \"x\";var label_y = \"y\";\
 if( typeof xaxislabel !== 'undefined' ){label_x = xaxislabel;}\
 if( typeof yaxislabel !== 'undefined' ){label_y = yaxislabel;}\
 var trace_canvas = create_canvas%d(%d,xsize,ysize);\
 var trace_context = trace_canvas.getContext(\"2d\");\
 var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
 var trace_div = document.createElement('div');\
 trace_div.id = \"trace_div\";\
 tooltip_div.appendChild(trace_div);\
 trace_div.innerHTML = \"<br /><span style='font-style:italic;font-size:10px'>\"+label_x+\" : <input type='text' size='4' value='' id='trace_input_x' style='text-align:center;color:blue;background-color:lightgreen;' />\"+label_y+\" : <input type='text' size='6' value='' id='trace_input_y' style='text-align:center;color:blue;background-color:lightgreen;' readonly' /></span> \";\
 canvas_div.addEventListener(\"mousemove\",trace,false);\
 canvas_div.addEventListener(\"touchmove\",trace,false);\
 var fun = to_js_math(\"%s\");if(fun == null){return;};\
 function eval_jsmath(x){return parseFloat(eval(fun));};\
 function trace(evt){\
  var canvas_rect = (trace_canvas).getBoundingClientRect();\
  var x_px = evt.clientX - canvas_rect.left;\
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
};use_trace_jsmath();",canvas_root_id,canvas_cnt,canvas_root_id,jsmath,line_width,crosshair_size,stroke_color,stroke_opacity);
}

/* 
add a table with 2 textarea's labeled 'x' 'y' ( or 'xlabel' 'ylabel' if defined) 
add two buttons: OK and NOK (OK draws; NOK will delete last item pair from userdraw_x / userdraw_y array's
*/
void add_textarea_xy(FILE *js_include_file, int canvas_root_id){
fprintf(js_include_file,"\n<!-- begin add_textarea_xy -->\n\
function add_textarea_xy(){\
if( wims_status == \"done\" ){return;};\
var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
var textarea_div = document.createElement('div');\
textarea_div.id = \"textarea_div\";\
tooltip_div.appendChild(textarea_div);\
var label_x = \"x\";var label_y = \"y\";\
if( typeof xaxislabel !== 'undefined' ){label_x = xaxislabel;}\
if( typeof yaxislabel !== 'undefined' ){label_y = yaxislabel;}\
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
 <td><textarea rows='5' cols='2' id='userinput_x' style='text-align:center;color:blue;background-color:orange;' ></textarea></td>\
 <td><textarea rows='5' cols='2' id='userinput_y' style='text-align:center;color:blue;background-color:orange;' ></textarea></td>\
</tr>\
</table>\";\
var textarea_ok_button = document.getElementById(\"textarea_ok_button\");\
var textarea_nok_button = document.getElementById(\"textarea_nok_button\");\
textarea_ok_button.addEventListener(\"mousedown\",function(e){user_redraw(1);return;},false);\
textarea_nok_button.addEventListener(\"mousedown\",function(e){user_redraw(-1);return;},false);\
return;\
};add_textarea_xy();",canvas_root_id);
}

/*

*/
void add_setlimits(FILE *js_include_file, int canvas_root_id){
fprintf(js_include_file,"\n<!-- begin add_setlimits -->\n\
use_pan_and_zoom = 1;\n\
function use_setlimits(){\
if( wims_status == \"done\" ){return;};\
var label_x = \"x\";var label_y = \"y\";\
if( typeof xaxislabel !== 'undefined' ){label_x = xaxislabel;}\
if( typeof yaxislabel !== 'undefined' ){label_y = yaxislabel;}\
var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
var setlim_div = document.createElement('div');\
setlim_div.id = \"setlim_div\";\
tooltip_div.appendChild(setlim_div);\
setlim_div.innerHTML=\"<br /><span style='font-style:italic;font-size:10px'>\"+label_x+\"min = <input type='text' size='4' value='\"+xmin+\"' id='userinput_xmin' style='text-align:center;color:blue;background-color:orange;' /> \"+label_x+\"max = <input type='text' size='4' value='\"+xmax+\"' id='userinput_xmax' style='text-align:center;color:blue;background-color:orange;' /><br />\"+label_y+\"min = <input type='text' size='4' value='\"+ymin+\"' id='userinput_ymin' style='text-align:center;color:blue;background-color:orange;' /> \"+label_y+\"max = <input type='text' size='4' value='\"+ymax+\"' id='userinput_ymax' style='text-align:center;color:blue;background-color:orange;' /><br /><input id='set_limits' type='button' value='OK' onclick='' style='color:red;background-color:lightblue;' />\";\
var setlimit_button = document.getElementById(\"set_limits\");\
function set_limits(e){\
xmin = safe_eval(document.getElementById('userinput_xmin').value);\
xmax = safe_eval(document.getElementById('userinput_xmax').value);\
ymin = safe_eval(document.getElementById('userinput_ymin').value);\
ymax = safe_eval(document.getElementById('userinput_ymax').value);\
if(xmin > xmax || ymin > ymax){alert(\"your limits are not correct...\");return;}\
try{start_canvas%d(1234)}catch(e){};try{dragstuff.Zoom(xmin,xmax,ymin,ymax)}catch(e){};return;};\
setlimit_button.addEventListener(\"mousedown\",function(e){set_limits();},false);\
};use_setlimits();",canvas_root_id,canvas_root_id);
}
/* 
adds 2 inputfields (x:y) and 'ok' | 'nok' button 
these are used for user drawing with inputfields...
*/

void add_input_xy(FILE *js_include_file, int canvas_root_id){
fprintf(js_include_file,"\n<!-- begin add_input_xy -->\n\
function add_input_xy(){\
if( wims_status == \"done\" ){return;};\
var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
var input_xy_div = document.createElement('div');\
input_xy_div.id = \"input_xy_div\";\
tooltip_div.appendChild(input_xy_div);\
var label_x = \"x\";var label_y = \"y\";\
input_xy_div.innerHTML=\"<br /><span style='font-style:italic;font-size:10px'><b>( <input type='text' size='6' value='' id='userinput_x' style='text-align:center;color:blue;background-color:orange;' /> : <input type='text' size='6' value='' id='userinput_y' style='text-align:center;color:blue;background-color:orange;' /> )</b><input id='update_button' type='button' value='OK' onclick=''  style='color:red;background-color:lightblue;'/><input id='delete_button' type='button' value='NOK' onclick='' style='color:blue;background-color:red;'/></span> \";\
var update_button = document.getElementById(\"update_button\");\
var delete_button = document.getElementById(\"delete_button\");\
update_button.addEventListener(\"mousedown\",function(e){user_redraw(1);return;},false);\
delete_button.addEventListener(\"mousedown\",function(e){user_redraw(-1);return;},false);\
};add_input_xy();",canvas_root_id);
}

/* adds 4 inputfields (x1:y1) --- (x2:y2) and 'ok' + 'nok' button */
void add_input_x1y1x2y2(FILE *js_include_file, int canvas_root_id){
fprintf(js_include_file,"\n<!-- begin add_input_x1y1x2y2 -->\n\
function add_input_x1y1x2y2(){\
if( wims_status == \"done\" ){return;};\
var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
var input_x1y1x2y2_div = document.createElement('div');\
input_x1y1x2y2_div.id = \"input_x1y1x2y2_div\";\
tooltip_div.appendChild(input_x1y1x2y2_div);\
input_x1y1x2y2_div.innerHTML=\"<br /><span><b>( <input type='text' size='6' value='' id='userinput_x1' style='text-align:center;color:blue;background-color:orange;' /> : <input type='text' size='6' value='' id='userinput_y1' style='text-align:center;color:blue;background-color:orange;' /> ) ----- ( <input type='text' size='6' value='' id='userinput_x2' style='text-align:center;color:blue;background-color:orange;' /> : <input type='text' size='6' value='' id='userinput_y2' style='text-align:center;color:blue;background-color:orange;'/> )</b><input id='update_button' type='button' value='OK' onclick='' style='color:red;background-color:lightblue;'/><input id='delete_button' type='button' value='NOK' onclick='' style='color:blue;background-color:red;' /></span> \";\
var update_button = document.getElementById(\"update_button\");\
var delete_button = document.getElementById(\"delete_button\");\
update_button.addEventListener(\"mousedown\",function(e){user_redraw(1);return;},false);\
delete_button.addEventListener(\"mousedown\",function(e){user_redraw(-1);return;},false);\
};add_input_x1y1x2y2();",canvas_root_id);
}

/* adds 3 inputfields Center (x:y) Radius r and 'ok'+'nok' buttons */
void add_input_xyr(FILE *js_include_file, int canvas_root_id){
fprintf(js_include_file,"\n<!-- begin add_input_xyr -->\n\
function add_input_xyr(){\
if( wims_status == \"done\" ){return;};\
var tooltip_div = document.getElementById(\"tooltip_placeholder_div%d\");\
var input_xyr_div = document.createElement('div');\
input_xyr_div.id = \"input_xyr_div\";\
tooltip_div.appendChild(input_xyr_div);\
input_xyr_div.innerHTML=\"<br /><span style='font-style:italic;font-size:10px'><b>Center : ( <input type='text' size='6' value='' id='userinput_x' style='text-align:center;color:blue;background-color:orange;' /> : <input type='text' size='6' value='' id='userinput_y' style='text-align:center;color:blue;background-color:orange;' /> ) Radius : <input type='text' size='6' value='' id='userinput_r' style='text-align:center;color:blue;background-color:orange;' /></b><input id='update_button' type='button' value='OK' onclick='' style='color:red;background-color:lightblue;'/><input id='delete_button' type='button' value='NOK' onclick='' style='color:blue;background-color:red;'/></span> \";\
var update_button = document.getElementById(\"update_button\");\
var delete_button = document.getElementById(\"delete_button\");\
update_button.addEventListener(\"mousedown\",function(e){user_redraw(1);return;},false);\
delete_button.addEventListener(\"mousedown\",function(e){user_redraw(-1);return;},false);\
};add_input_xyr();",canvas_root_id);
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
  draw_arrows(context_userdraw,userdraw_x,userdraw_y,arrow_head,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,type,use_rotate,angle,use_translate,vector);\
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
  draw_arrows(context_userdraw,userdraw_x,userdraw_y,arrow_head,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,type,use_rotate,angle,use_translate,vector);\
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
 var lu = userdraw_x.length;\n\
 cnt = 1;\
 if( t == -1 && lu > 0){\
  userdraw_x.splice(lu-1,1);\n\
  userdraw_y.splice(lu-1,1);\n\
  context_userdraw.clearRect(0,0,xsize,ysize);\n\
  draw_polyline(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\n\
  return;\n\
 };\n\
 var add_x = safe_eval( document.getElementById(\"userinput_x\").value );\n\
 var add_y = safe_eval( document.getElementById(\"userinput_y\").value );\n\
 if(add_x != null && add_y != null ){\
  userdraw_x.push(x2px(add_x));\n\
  userdraw_y.push(y2px(add_y));\n\
  context_userdraw.clearRect(0,0,xsize,ysize);\n\
  draw_polyline(context_userdraw,userdraw_x,userdraw_y,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1);\n\
 };\n\
 return;\n\
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
  draw_paths(context_userdraw,userdraw_x,userdraw_y,line_width,closed_path,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,use_rotate,angle,use_translate,vector);\
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
 draw_paths(context_userdraw,userdraw_x,userdraw_y,line_width,closed_path,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,use_rotate,angle,use_translate,vector);\
 cnt = 1;\
 return;\
};");
}

void add_jsplot(FILE *js_include_file,int canvas_root_id){
fprintf(js_include_file,"\n<!-- begin jsplot() -->\n\
var jsplot = function(canvas_type,f,linewidth,color,opacity,use_dashed,dashtype0,dashtype1){\
 var obj;\
 if( document.getElementById(\"wims_canvas%d\"+canvas_type) ){\
  obj = document.getElementById(\"wims_canvas%d\"+canvas_type);\
 }\
 else\
 {\
  obj = create_canvas%d(canvas_type,xsize,ysize);\
 };\
 var ctx = obj.getContext(\"2d\");\
 ctx.clearRect(0,0,xsize,ysize);\
 function eval_jsmath(x){return parseFloat(eval(fun));};\
 var fun = to_js_math(f);if(fun == null){return;};\
 ctx.lineWidth = linewidth;\
 ctx.strokeStyle=\"rgba(\"+color+\",\"+opacity+\")\";\
 if(use_dashed == 1){if(ctx.setLineDash){ctx.setLineDash([dashtype0,dashtype1]);}else{ctx.mozDash =[dashtype0,dashtype1];}};\
 var y1;var x1;var y2;var x2;\
 ctx.beginPath();\
 for(var p=0 ; p<xsize;p++){\
  x1 = px2x(p);\
  y1 = y2px(parseFloat(eval_jsmath(x1)));\
  x2 = px2x(p+1);\
  y2 = y2px(parseFloat(eval_jsmath(x2)));\
  if(Math.abs(y2-y1) < ysize ){\
    ctx.moveTo(p,y1);\
    ctx.lineTo(p+1,y2);\
  };\
 };\
 ctx.closePath();\
 ctx.stroke();\
};",canvas_root_id,canvas_root_id,canvas_root_id);
}

void add_to_js_math(FILE *js_include_file){
fprintf(js_include_file,"\n<!-- begin to_js_math() -->\n\
var to_js_math = function(math_fun){\
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
 };\n\
 for(var p=0 ; p < len ; p++){\n\
  in_fun = infun[p];In_Fun = in_fun.toUpperCase();w_cnt = 0;\n\
  if(math_fun.indexOf(In_Fun) != -1 ){\n\
   while(math_fun.indexOf(In_Fun) != -1){\n\
    math_fun = math_fun.replace(In_Fun,in_fun);\n\
    w_cnt++;if(w_cnt>1000){alert(\"hmmm \"+math_fun+\" ?\\nUse command plot for more complex math functions...\");return null;};\n\
   };\n\
  };\n\
 };\n\
 return math_fun;\n\
};\n");
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
    int lim_ymin =(int)( ymin - 4*abs(ymin));
    int lim_ymax =(int)( ymax + 4*abs(ymax));
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
    int lim_ymin =(int)( ymin - 4*abs(ymin));
    int lim_ymax =(int)( ymax + 4*abs(ymax));
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
/* change this when colornames / numbers are added to struct */
#define NUMBER_OF_COLORNAMES	140
struct { 
    char *hex;
    char *name;
    char *rgb;
} colors[]={
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


void add_drag_code(FILE *js_include_file,int canvas_cnt,int canvas_root_id){
/* in drag& drop / onclick library:
    obj_type = 1 == rect
    obj_type = 2 == point / points (do not scale with zoom)
    obj_type = 3 == ellipse 
    obj_type = 4 == polyline / segment /line / vline / hline
    obj_type = 5 == closed path (polygon)
    obj_type = 6 == roundrect
    obj_type = 7 == crosshair / crosshairs
    obj_type = 8 == arrow
    obj_type = 9 == curve
    obj_type = 10== arrow2 
    obj_type = 11== parallel  (no drag or onclick) 
    obj_type = 12== arc
    obj_type = 13== circle (will scale on zoom)
    obj_type = 14== text (will not scale or pan on zoom)
    obj_type = 15== animated point on curve
    obj_type = 16== pixels
*/
fprintf(js_include_file,"\n<!-- begin drag_drop_onclick shape library -->\n\
function Shape(click_cnt,onclick,direction,type,x,y,w,h,line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_filled,use_dashed,dashtype0,dashtype1,use_rotate,angle,text,font_size,font_family,use_affine,affine_matrix){\
 this.text = text || 0;\
 this.font_size = font_size || 12;\
 if( font_family.indexOf('px') > 0 ){this.font_family = font_family;}else{this.font_family = this.font_size+'px Ariel';};\
 this.use_rotate = use_rotate || 0;\
 this.angle = angle*(Math.PI/180) || 0;\
 this.use_affine = use_affine || 0;\
 this.affine_matrix = affine_matrix || [1,0,0,1,0,0];\
 this.click_cnt = click_cnt || 1;\
 this.onclick = onclick || 0;\
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
 this.line_width = line_width || 30;\
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
 var x_c = x2px(0);\
 var y_c = y2px(0);\
 ctx.translate(x_c,y_c);\
 ctx.rotate(this.angle);ctx.translate(-x_c,-y_c);};\
 if( this.use_affine == 1 ){\
  ctx.setTransform(this.affine_matrix[0],this.affine_matrix[1],this.affine_matrix[2],this.affine_matrix[3],this.affine_matrix[4],this.affine_matrix[5]);\
 };\
 ctx.beginPath();\
 switch(this.type){\
  case 1: ctx.rect(this.x[0], this.y[0], this.x[1]-this.x[0], this.y[2] - this.y[0]);break;\
  case 2: ctx.arc(this.x[0],this.y[0],this.w[0],0,2*Math.PI,false);break;\
  case 3: var w = 0.5*(scale_x_radius(this.w[0]));var h = 0.5*(scale_y_radius(this.h[0]));ctx.beginPath();ctx.moveTo(this.x[0], this.y[0] - h);ctx.bezierCurveTo(this.x[0] + w, this.y[0] - h,this.x[0] + w, this.y[0] + h,this.x[0],this.y[0] + h);ctx.bezierCurveTo(this.x[0] - w, this.y[0] + h,this.x[0] - w, this.y[0] - h,this.x[0], this.y[0] - h);if(this.use_filled == 1){ ctx.fillStyle = this.fill_color; ctx.fill(); }; ctx.closePath();break;\
  case 4: for(var p = 0; p < this.x.length - 1;p++){ctx.moveTo(this.x[p], this.y[p]);ctx.lineTo(this.x[p+1],this.y[p+1]);};break;\
  case 5: ctx.moveTo(this.x[0], this.y[0]);for(var p = 1; p < this.x.length;p++){ctx.lineTo(this.x[p],this.y[p]);};ctx.lineTo(this.x[0],this.y[0]);break;\
  case 6: var w = this.x[1] - this.x[0];var h = this.y[1] - this.y[0];var r = this.w[0];ctx.beginPath();ctx.moveTo(this.x[0] + r, this.y[0]);ctx.lineTo(this.x[0] + w - r, this.y[0]);ctx.quadraticCurveTo(this.x[0] + w, this.y[0], this.x[0] + w, this.y[0] + r);ctx.lineTo(this.x[0] + w, this.y[0] + h - r);ctx.quadraticCurveTo(this.x[0] + w, this.y[0] + h, this.x[0] + w - r, this.y[0] + h);ctx.lineTo(this.x[0] + r, this.y[0] + h);ctx.quadraticCurveTo(this.x[0], this.y[0] + h, this.x[0], this.y[0] + h - r);ctx.lineTo(this.x[0], this.y[0] + r);ctx.quadraticCurveTo(this.x[0], this.y[0], this.x[0] + r, this.y[0]);ctx.closePath();break;\
  case 7: ctx.moveTo(this.x[0]-this.w[0],this.y[0]-this.h[0]);ctx.lineTo(this.x[0]+this.w[0],this.y[0]+this.h[0]);ctx.moveTo(this.x[0]-this.w[0],this.y[0]+this.h[0]);ctx.lineTo(this.x[0]+this.w[0],this.y[0]-this.h[0]);break;\
  case 8: var dx;var dy;var len;var arrow_head = this.w[0];for(var p = 0; p < this.x.length - 1;p++){ctx.restore();ctx.save();dx = this.x[p+1] - this.x[p];dy = this.y[p+1] - this.y[p];len = Math.sqrt(dx*dx+dy*dy);ctx.translate(this.x[p+1],this.y[p+1]);ctx.rotate(Math.atan2(dy,dx));ctx.lineCap = \"round\";ctx.beginPath();ctx.moveTo(0,0);ctx.lineTo(-len,0);ctx.closePath();ctx.stroke();ctx.beginPath();ctx.moveTo(0,0);ctx.lineTo(-1*arrow_head,-0.5*arrow_head);ctx.lineTo(-1*arrow_head, 0.5*arrow_head);ctx.closePath();ctx.fill();};break;\
  case 9: ctx.moveTo(this.x[0], this.y[0]);for(var p = 1; p < this.x.length - 1;p++){if( Math.abs(this.y[p] - this.y[p-1]) < ysize && Math.abs(this.y[p+1] - this.y[p]) < ysize ){ctx.lineTo(this.x[p],this.y[p]);}else{ctx.moveTo(this.x[p],this.y[p]);};};break;\
  case 10: var dx;var dy;var len;ctx.restore();ctx.save();dx = this.x[1] - this.x[0];dy = this.y[1] - this.y[0];len = Math.sqrt(dx*dx+dy*dy);ctx.translate(this.x[1],this.y[1]);ctx.rotate(Math.atan2(dy,dx));ctx.beginPath();ctx.moveTo(0,0);ctx.lineTo(-len,0);ctx.closePath();ctx.stroke();ctx.beginPath();ctx.moveTo(0,0);ctx.lineTo(-1*this.w[0],-1*this.w[0]);ctx.lineTo(-1*this.w[0],this.w[0]);ctx.closePath();ctx.lineCap = \"round\";ctx.fill();ctx.restore();ctx.save();ctx.translate(this.x[0],this.y[0]);ctx.rotate(Math.atan2(dy,dx));ctx.beginPath();ctx.moveTo(0,0);ctx.lineTo(this.w[0],-0.5*this.w[0]);ctx.lineTo(this.w[0], 0.5*this.w[0]);ctx.closePath();ctx.lineCap = \"round\";ctx.fill(); break;\
  case 11: var x1 = this.x[0];var y1 = this.y[0];var x2 = this.x[1];var y2 = this.y[1];var dx = this.x[2];var dy = this.y[2];var n  = this.w[0];for(var p = 0 ; p < n ; p++ ){ctx.beginPath();ctx.moveTo(x1,y1);ctx.lineTo(x2,y2);ctx.stroke();x1 = x1 + dx;y1 = y1 + dy;x2 = x2 + dx;y2 = y2 + dy;ctx.closePath();};break;\
  case 12: ctx.save();var start;var end;if(this.h[0] < this.h[1]){start = this.h[0];end = this.h[1]}else{start = this.h[1];end = this.w[0];};start=360-start;end=360-end;var r = this.w[0];ctx.arc(this.x[0], this.y[0], r, start*(Math.PI / 180), end*(Math.PI / 180),true);if(this.use_filled){ctx.lineTo(this.x[0],this.y[0]);ctx.fill();};ctx.restore();break;\
  case 13: ctx.arc(this.x[0],this.y[0],scale_x_radius(this.w[0]),0,2*Math.PI,false);break;\
  case 14: ctx.font = this.font_family ;ctx.fillText(this.text,this.x[0],this.y[0]);break;\
  case 15: var animate_canvas = create_canvas%d(%d,xsize,ysize);var animate_ctx = animate_canvas.getContext(\"2d\");animate_ctx.moveTo(this.x[0], this.y[0]);animate_ctx.strokeStyle = this.stroke_color;animate_ctx.fillStyle = this.fill_color;animate_ctx.lineWidth = this.line_width;var p=0;var X = this.x;var Y = this.y;var fps=10;var W = this.w[0];var W2 = 0.5*W;use_filled = true;function animate(){animate_ctx.fillRect(X[p]-W2,Y[p]-W2,W,W);setTimeout(function(){requestAnimationFrame(animate);}, 1000 / fps);p++;if(p == X.length - 1){p = 0;animate_ctx.clearRect(0,0,xsize,ysize);};};animate();break;\
  case 16: for(var p = 0; p < this.x.length;p++){ctx.fillRect( this.x[p], this.y[p],this.line_width,this.line_width );};break;\
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
  case 2: for(var p = 0 ; p < this.x.length; p++ ){if( Math.abs(distance(this.x[p],this.y[p],mx,my) ) < this.w[p] + marge ){return p;break;};};break;\
  case 3: for(var p = 0 ; p < this.x.length; p++ ){if( Math.abs(distance(this.x[p],this.y[p],mx,my) ) < scale_x_radius(this.w[p]) + marge ){return p;break;};};break;\
  case 4: var diff;var q;var r;for(var p = 0 ; p < this.x.length-1; p = p+2  ){if( ((this.x[p+1] - this.x[p]) != 0)  && ((this.y[p+1]-this.y[p]) != 0) ){r = (this.y[p+1]-this.y[p])/(this.x[p+1]-this.x[p]);q = this.y[p] - (r)*(this.x[p]);diff = distance_to_line(r,q,mx,my);}else{if( (this.y[p+1]-this.y[p]) != 0 ){diff = Math.abs(this.x[p] - mx);}else{diff = Math.abs(this.y[p] - my);};};if( diff  < marge ){ return p;};}; break;\
  case 6: for(var p = 0 ; p < this.x.length; p++ ){if( mx < this.x[p] + marge &&  mx > this.x[p] - marge ){if( my < this.y[p]+marge && my > this.y[p] - marge ){return p;};};};break;\
  case 7: for(var p = 0 ; p < this.x.length; p++ ){if( (this.x[p] - this.w[p] <= mx) && (this.x[p] + this.w[p] >= mx) &&  (this.y[p] - this.h[p] <= my) && (this.y[p] + this.h[p] >= my) ){return p;};};break;\
  case 8: var diff;var q;var r;for(var p = 0 ; p < this.x.length-1; p = p+2  ){if( ((this.x[p+1] - this.x[p]) != 0)  && ((this.y[p+1]-this.y[p]) != 0) ){r = (this.y[p+1]-this.y[p])/(this.x[p+1]-this.x[p]);q = this.y[p] - (r)*(this.x[p]);diff = distance_to_line(r,q,mx,my);}else{if( (this.y[p+1]-this.y[p]) != 0 ){diff = Math.abs(this.x[p] - mx);}else{diff = Math.abs(this.y[p] - my);};};if( diff  < marge ){ return p;};}; break;\
  case 9: for(var p = 0 ; p < this.x.length; p++ ){if( (this.x[p] - this.line_width <= mx) && (this.x[p] + this.w[p] + this.line_width >= mx) &&  (this.y[p] - this.line_width <= my) && (this.y[p] + this.h[p] +this.line_width  >= my) ){return p;};};break;\
  case 11: break;\
  case 12: break;\
  case 13: for(var p = 0 ; p < this.x.length; p++ ){if( Math.abs(distance(this.x[p],this.y[p],mx,my) ) < scale_x_radius(this.w[p]) + marge ){return p;break;};};break;\
  case 14: for(var p = 0 ; p < this.x.length; p++ ){if(this.y[p] < my + 0.5*(this.font_size) && this.y[p] > my - 0.5*(this.font_size)){var w = parseInt(0.8*(this.font_size)*((this.text).length));if(this.x[p] < mx + w && this.x[p] > mx - w ){ return p;break;};};};break;\
  default: for(var p = 0 ; p < this.x.length; p++ ){if( (this.x[p] - this.line_width <= mx) && (this.x[p] + this.w[p] + this.line_width >= mx) &&  (this.y[p] - this.line_width <= my) && (this.y[p] + this.h[p] +this.line_width  >= my) ){return p;};};break;\
 };\
 return -1;\
};\
var reply = [];\
\
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
 container_div.addEventListener( 'mouseup'    , mouseup,false);\
 container_div.addEventListener( 'mousemove'  , mousemove,false);\
 container_div.addEventListener( 'mousedown'  , mousedown,false);\
 container_div.addEventListener( 'touchend'   , mouseup,false);\
 container_div.addEventListener( 'selectstart', function(e) { e.preventDefault(); return false; }, false);\
 container_div.addEventListener( 'touchstart' , mousedown,false);\
 container_div.addEventListener( 'touchmove'  , mousemove,false);\
 function mousedown(e){\
  var mouse = myState.getMouse(e);\
  var mx = mouse.x;\
  var my = mouse.y;\
  if( use_pan_and_zoom == 1 && my > ysize - 15){\
   check_zoom_or_pan(mx);\
  }\
  else\
  {\
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
     var org_line_width = shapes[i].line_width;\
     var org_font_family = shapes[i].font_family;\
     var org_stroke_opacity = shapes[i].stroke_opacity;\
     myState.chk = chk;\
     myState.selection = shapes[i];\
     myState.valid = false;\
     switch(shapes[i].onclick){\
      case 0: myState.dragging = false;break;\
      case 1: myState.selection.line_width = 3*org_line_width;myState.selection.font_family = \"bold italic \"+myState.selection.font_size+\"px Courier\";myState.dragging = false;myState.draw();reply[0] = myState.selection.click_cnt;myState.selection.line_width = org_line_width;myState.selection.font_family = org_font_family;break;\
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
    if( x_use_snap_to_grid == 1 || y_use_snap_to_grid == 1){\
     var mouse = myState.getMouse(e);\
     var dx=mouse.x;\
     var dy=mouse.y;\
     if( x_use_snap_to_grid == 1 && y_use_snap_to_grid == 1 ){ \
      dx = snap_to_x(dx) - myState.selection.x[myState.chk];\
      dy = snap_to_y(dy) - myState.selection.y[myState.chk];\
     }else{\
      if( x_use_snap_to_grid == 1 ){ \
       dx = snap_to_x(dx) - myState.selection.x[myState.chk];\
       dy = 0;\
      }else{\
       dx = 0;\
       dy = snap_to_y(dy) - myState.selection.y[myState.chk];\
      };\
     };\
     switch(myState.selection.direction){\
      case 0: myState.selection = move(myState.selection,dx,dy);break;\
      case 1: myState.selection = move(myState.selection,dx,0);break;\
      case 2: myState.selection = move(myState.selection,0,dy); break;\
     };\
    };\
    reply[myState.selection.click_cnt] = myState.selection.click_cnt+\":\"+px2x(myState.x_start)+\":\"+px2y(myState.y_start)+\":\"+px2x(myState.selection.x[myState.chk])+\":\"+px2y(myState.selection.y[myState.chk]);\
   };\
   myState.valid = false;\
   myState.draw();\
   myState.valid = true;\
  };\
  myState.dragging = false;\
 };\
 function mousemove(e){\
  if(myState.dragging){\
   var mouse = myState.getMouse(e);\
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
  for(p = 15 ; p < 106 ; p = p+15){\
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
CanvasState.prototype.Zoom = function(xmin,xmax,ymin,ymax){\
 (this.ctx).clearRect(0,0,this.width,this.height);\
 for(var i = 0; i < this.shapes.length ; i++){\
  for(var p = 0 ; p < this.shapes[i].x.length;p++){\
   this.shapes[i].x[p] = x2px(this.shapes[i].xorg[p]);\
   this.shapes[i].y[p] = y2px(this.shapes[i].yorg[p]);\
  }\
  this.valid = false;\
  this.shapes[i].draw(this.ctx);\
 };\
 reply = new Array();\
};\
CanvasState.prototype.getMouse = function(e){\
var element = this.canvas, offsetX = 0,offsetY = 0;\
while( ( element = element.offsetParent) ){\
offsetX += element.offsetLeft;\
offsetY += element.offsetTop;\
}\
var mx = e.clientX - offsetX + (document.documentElement.scrollLeft ? document.documentElement.scrollLeft : document.body.scrollLeft);\
var my = e.clientY - offsetY + (document.documentElement.scrollTop ? document.documentElement.scrollTop :document.body.scrollTop);\
 return {x: mx, y: my};\
};\
function read_dragdrop(){\
var moved_objects = [];var c = 0;\
for(var p=0 ; p<reply.length ; p++){\
if(reply[p]){moved_objects[c] = reply[p];c++}\
}\
return moved_objects;\
};\
this.read_dragdrop = read_dragdrop;\
var obj = create_canvas%d(%d,xsize,ysize);\
var container_div = document.getElementById(\"canvas_div%d\");\
var dragstuff = new CanvasState(obj,container_div);",canvas_root_id,ANIMATE_CANVAS,canvas_root_id,canvas_root_id,DRAG_CANVAS,canvas_root_id);
}

/*
#define BG_CANVAS 0 may be used for floodfill
#define STATIC_CANVAS 1 may be used for floodfill
#define MOUSE_CANVAS 2 xx
#define GRID_CANVAS 3 may be used for floodfill
#define DRAG_CANVAS 4 default for floodfill
#define DRAW_CANVAS 5 may be used for floodfill

*/

void add_js_filltoborder(FILE *js_include_file,int canvas_root_id){
fprintf(js_include_file,"\n<!-- begin command filltoborder -->\n\
filltoborder_cnt = 200;\
filltoborder = function(x,y,bordercolor,color){\
 x = x2px(x);\
 y = y2px(y);\
 var canvas;\
 var ctx;\
 suitable_canvases = [4,5,1,0];\
 var c_id;var found = -1;\
 for( var p = 0 ; p < 5; p++ ){\
  c_id = suitable_canvases[p];\
  if( document.getElementById(\"wims_canvas%d\"+c_id) ){\
   canvas = document.getElementById(\"wims_canvas%d\"+c_id);\
   found = c_id;\
   break;\
  };\
 };\
 if( found == -1 ){alert(\"Something is very wrong...\\nNo suitable canvas found for filling operation!!\");return;}\
 ctx = canvas.getContext(\"2d\");ctx.save();\
 var image = ctx.getImageData(0, 0, xsize, ysize);\
 var imageData = image.data;\
 var pixelStack = [[x, y]];\
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
  return (px1.r === px2.r && px1.g === px2.g && px1.b === px2.b && px1.a === px2.a);\
 };\
 function _checkBorder(px2){\
  return (bordercolor.r === px2.r && bordercolor.g === px2.g && bordercolor.b === px2.b && bordercolor.a === px2.a);\
 };\
 px1 = _getPixel(((y * xsize) + x) * 4);\
 bordercolor = {\
  r: parseInt(bordercolor[0], 10),\
  g: parseInt(bordercolor[1], 10),\
  b: parseInt(bordercolor[2], 10),\
  a: parseInt(bordercolor[3] || 255, 10)\
 };\
 color = {\
  r: parseInt(color[0], 10),\
  g: parseInt(color[1], 10),\
  b: parseInt(color[2], 10),\
  a: parseInt(color[3] || 255, 10)\
 };\
 if( _comparePixel(color) ) { return true; }\
 while (pixelStack.length) {\
  newPos = pixelStack.pop();\
  pixelPos = (newPos[1]*xsize + newPos[0]) * 4;\
  while(newPos[1]-- >= 0 && ( ! _checkBorder(_getPixel(pixelPos))) ){\
   pixelPos -= xsize * 4;\
  }\
  pixelPos += xsize * 4;\
  ++newPos[1];\
  found_left_border = false;\
  found_right_border = false;\
  while( newPos[1]++ < ysize-1 && ( ! _checkBorder(_getPixel(pixelPos))) ){\
   _setPixel(pixelPos);\
   if( newPos[0] > 0 ){\
    if( _comparePixel(_getPixel(pixelPos - 4)) ){\
    if( !found_left_border ){\
     pixelStack.push( [newPos[0] - 1, newPos[1]] );\
     found_left_border = true;\
    }\
   }\
   else if( found_left_border ){\
     found_left_border = false;\
    }\
   }\
   if( newPos[0] < xsize-1 ){\
    if( _comparePixel(_getPixel(pixelPos + 4)) ){\
     if( !found_right_border){\
      pixelStack.push( [newPos[0] + 1, newPos[1]] );\
      found_right_border = true;\
     }\
    }\
    else if(found_right_border){\
      found_right_border = false;\
     }\
    }\
   pixelPos += xsize * 4;\
  }\
 }\
 var _canvas = create_canvas%d(filltoborder_cnt,xsize,ysize);\
 filltoborder_cnt++;\
 var _ctx = _canvas.getContext(\"2d\");\
 _ctx.putImageData(image, 0, 0);\
 ctx.restore();\
};",canvas_root_id,canvas_root_id,canvas_root_id);

}
void add_js_floodfill(FILE *js_include_file,int canvas_root_id){
fprintf(js_include_file,"\n<!-- begin command floodfill -->\n\
floodfill = function(interaction,xs,ys,color){\n\
 var canvas = document.getElementById(\"wims_canvas%d%d\");\n\
 if( ! canvas ){ return; };\n\
 var ctx = canvas.getContext(\"2d\");\
 ctx.save();\n\
 if(interaction == 1 ){\n\
  if( ys > ysize - 15){return;}\n\
 }\n\
 else\n\
 {\n\
  xs = x2px(xs);\n\
  ys = y2px(ys);\n\
 };\n\
 var image = ctx.getImageData(0, 0, xsize, ysize);\n\
 var imageData = image.data;\n\
 var pixelStack = [[xs, ys]];\n\
 var px1;\n\
 var newPos;\n\
 var pixelPos;\n\
 var found_left_border;\n\
 var found_right_border;\n\
 function _getPixel(pixelPos){\n\
  return {r:imageData[pixelPos], g:imageData[pixelPos+1], b:imageData[pixelPos+2], a:imageData[pixelPos+3]};\n\
 };\n\
 function _setPixel(pixelPos){\n\
  imageData[pixelPos] = color.r;\n\
  imageData[pixelPos+1] = color.g;\n\
  imageData[pixelPos+2] = color.b;\n\
  imageData[pixelPos+3] = color.a;\n\
 };\n\
 function _comparePixel(px2){\n\
  return (px1.r === px2.r && px1.g === px2.g && px1.b === px2.b && px1.a === px2.a);\n\
 };\n\
 px1 = _getPixel(((ys * xsize) + xs) * 4);\n\
 color = {\n\
  r: parseInt(color[0], 10),\n\
  g: parseInt(color[1], 10),\n\
  b: parseInt(color[2], 10),\n\
  a: parseInt(color[3] || 255, 10)\n\
 };\n\
 if( _comparePixel(color) ) { return true; }\n\
 while (pixelStack.length) {\n\
  newPos = pixelStack.pop();\n\
  xs = newPos[0];ys = newPos[1];\n\
  pixelPos = (ys*xsize + xs) * 4;\n\
  while(ys-- >= 0 && _comparePixel(_getPixel(pixelPos))){\n\
   pixelPos -= xsize * 4;\n\
  }\n\
  pixelPos += xsize * 4;\n\
  ++ys;\n\
  found_left_border = false;\n\
  found_right_border = false;\n\
  while( ys++ < ysize-1 && _comparePixel(_getPixel(pixelPos)) ){\n\
   _setPixel(pixelPos);\n\
   if( xs > 0 ){\n\
    if( _comparePixel(_getPixel(pixelPos - 4)) ){\n\
    if( !found_left_border ){\n\
     pixelStack.push( [xs - 1, ys] );\n\
     found_left_border = true;\n\
    }\n\
   }\n\
   else if( found_left_border ){\n\
     found_left_border = false;\n\
    }\n\
   }\n\
   if( xs < xsize-1 ){\n\
    if( _comparePixel(_getPixel(pixelPos + 4)) ){\n\
     if( !found_right_border){\n\
      pixelStack.push( [xs + 1, ys] );\n\
      found_right_border = true;\n\
     }\n\
    }\n\
    else if(found_right_border){\n\
      found_right_border = false;\n\
     }\n\
    }\n\
   pixelPos += xsize * 4;\n\
  }\n\
 };\n\
 ctx.putImageData(image, 0, 0);\n\
 ctx.restore();\n\
};",canvas_root_id,DRAG_CANVAS);

}

