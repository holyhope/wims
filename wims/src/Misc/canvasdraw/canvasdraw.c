/*27/7/2013 version 0.01
"Inspired" by FLY program: http://martin.gleeson.com/fly
*********************************************************************************
* J.M. Evers 7/2013								*
* This is all just amateur scriblings... So no copyrights.			*
* This source code file, and compiled objects derived from it,			*
* can be used and distributed without restriction, including for commercial use	*
* No warrenty whatsoever							*
*********************************************************************************
*/
#include "canvasdraw.h"

/******************************************************************************
**  Internal Functions
******************************************************************************/
void	add_to_buffer(char *tmp); /* add tmp_buffer to the buffer */
void	sync_input(FILE *infile);/* proceed with inputfile */
void 	add_javascript_functions(int js_functions[], int canvas_root_id);
void	reset();/* reset some global variables like "use_filled" , "use_dashed" */
int	get_token(FILE *infile); /* read next char until EOL*/
/*
int 	x2px(double x);
int 	y2px(double y);
*/
double 	px2x(int x);
double 	px2y(int y);
double	get_real(FILE *infile,int last); /* read a value; calculation and symbols allowed */
char    *str_replace ( const char *word, const char *sub_word, const char *rep_word );
char 	*get_color(FILE *infile,int last); /* read hex-color or colorname -> hex */
char	*get_string(FILE *infile,int last); /* get the string at the end of a command */
char	*get_string_argument(FILE *infile,int last); /* the same, but with "comma" as  separator */
char 	*convert_hex2rgb(char *hexcolor);
void 	add_read_canvas(int canvas_root_id,int reply_format,int reply_precision);
void	make_js_include(int canvas_root_id);
void	check_string_length(int length);/* checks if the length of string argument of command is correct */
FILE 	*js_include_file;
FILE	*get_file(int *line_number, char **filename);
FILE 	*infile;    /* will be stdin */
/******************************************************************************
** global
******************************************************************************/
int finished = FALSE;/* main variable for signalling the end of the fly-script ; if finished = 1 ; write to stdout or canvasz */
int line_number = 1;/* used in canvas_error() ; keep track of line number in canvasdraw/fly - script */
/* set some variables to avoid trouble (NaN) in case of syntax and other usage errors */
int xsize = 320;
int ysize = 320;
double xmin = 0.0;
double xmax = 320.0;
double ymin = 0.0;
double ymax = 320.0;
double tmax = 2;
double tmin = -2;
/* flag to indicate parsing of line status */
int done = FALSE;
int type; /* eg command number */
int onclick = 0;/* 0 = noninteractive ; 1 = onclick ; 2 = draggable*/
int slider = 0;/* slider=1 : x-values ; slider=2 : y-values;slider=3 angle values */
int use_affine = FALSE;
int use_rotate = FALSE;
int use_filled = FALSE;
int use_dashed = FALSE; /* dashing not natively supported in firefox  , for now... */

char buffer[MAX_BUFFER];/* contains js-functions with arguments ... all other basic code is directly printed into js-include file */

/******************************************************************************
** Main Program
******************************************************************************/
int main(int argc, char *argv[]){
    /* need unique id for every call to canvasdraw : rand(); is too slow...will result in many identical id's */
    struct timeval tv;struct timezone tz;gettimeofday(&tv, &tz);unsigned int canvas_root_id = (unsigned int) tv.tv_usec;
    infile = stdin;/* read flyscript via stdin */
    int i,c;
    double double_data[MAX_INT+1];
    int int_data[MAX_INT+1];
    for(i=0;i<MAX_INT;i++){int_data[i]=0;double_data[i]=0;}
    int use_parametric = FALSE;/* will be reset after parametric plotting */
    int use_axis = FALSE;
    int use_axis_numbering = FALSE;
    int use_pan_and_zoom = FALSE;
    int use_safe_eval = FALSE; /* if true, add just once : js function to evaluate userinput values for plotting etc */
    int use_js_math = FALSE; /* if true add js-function to convert math_function --> javascript math_function */
    int use_js_plot = FALSE; /* if true , let js-engine plot the curve */
    int line_width = 1;
    int decimals = 2;
    int precision = 100; /* 10 = 1;100=2;1000=3 decimal display for mouse coordinates or grid coordinate.May be redefined before every object */
    int use_userdraw = FALSE; /* flag to indicate user interaction */
    int drag_type = -1;/* 0,1,2 : xy,x,y */
    int use_tooltip = FALSE;
    char *tooltip_text = "Click here";
    char *temp = ""; /* */
    char *bgcolor = "";/* used for background of canvas_div ; default is tranparent */
    char *stroke_color = "255,0,0";
    char *fill_color = "0,255,0";
    char *font_family = "12px Ariel"; /* commands xaxistext,yaxistext,legend,text/textup/string/stringup may us this */
    char *font_color = "#00000";
    char *draw_type = "points";
    char *fly_font = "normal";
    char *input_style = "";
    char *flytext = "";
    char *affine_matrix = "[1,0,0,1,0,0]";
    char *function_label = "f(x)=";
    int pixelsize = 1;
    int reply_format = 0;
    int input_cnt = 0;
    int ext_img_cnt = 0;
    int slider_cnt = 0;
    int font_size = 12;/* this may lead to problems when using something like "fontfamily Italic 24px Ariel" the "font_size" value is not substituted into fontfamily !! */ 
    int dashtype[2] = { 4 , 4 }; /* just line_px and space_px : may have more arguments...if needed in future*/
    int js_function[MAX_JS_FUNCTIONS]; /* javascript functions include objects on demand basis : only once per object type */
    for(i=0;i<MAX_JS_FUNCTIONS;i++){js_function[i]=0;}
    int arrow_head = 8; /* size in px needed for arrow based  userdraw:  "userdraw arrow,color" */
    int crosshair_size = 5; /* size in px*/
    int plot_steps = 250;/* the js-arrays with x_data_points and y_data_points will have size 250 each: use with care !!! use jscurve when precise plots are required  */
    int found_size_command = 0; /* 1 = found size ; 2 = found xrange; 3 = found yrange :just to flag an error message */
    int click_cnt = 1; /* counter to identify the "onclick" ojects */
    int clock_cnt = 0; /* counts the amount of clocks used -> unique object clock%d */
    int linegraph_cnt = 0; /* identifier for command 'linegraph' ; multiple line graphs may be plotted in a single plot*/
    int barchart_cnt = 0; /* identifier for command 'barchart' ; multiple charts may be plotted in a single plot*/
    int legend_cnt = -1; /* to allow multiple legends to be used, for multiple piecharts etc  */
    int reply_precision = 100; /* used for precision of student answers / drawings */
    double angle = 0.0;
    int clickfillmarge = 20; /* in pixels : if the 'remove click' is within this marge, the filling is removed */
    int animation_type = 9; /* REMOVED == object type curve in drag library */
    int use_input_xy = 0; /* 1= input fields 2= textarea 3=calc y value*/
    int use_slider_display = 0; /* in case of a slider, should we display it's value ?*/
    size_t string_length = 0; /* measure the size of the user input fly-string */
    double stroke_opacity = 0.8; /* use some opacity as default */
    double fill_opacity = 0.8;/* use some opacity as default */
    char *URL = "http://localhost/images";
    memset(buffer,'\0',MAX_BUFFER);
    void *tmp_buffer = "";

    /* default writing a unzipped js-include file into wims getfile directory */
    char *w_wims_session = getenv("w_wims_session");
    if(  w_wims_session == NULL || *w_wims_session == 0 ){
	canvas_error("Hmmm, your wims environment does not exist...\nCanvasdraw should be used within wims.");
    }
    int L0=strlen(w_wims_session) + 21;
    char *getfile_dir = my_newmem(L0); /* create memory to fit string precisely */
    snprintf(getfile_dir,L0, "../sessions/%s/getfile",w_wims_session);/* string will fit precisely  */
    mode_t process_mask = umask(0); /* check if file exists */
    int result = mkdir(getfile_dir, S_IRWXU | S_IRWXG | S_IRWXO);
    if( result == 0 || errno == EEXIST ){
     umask(process_mask); /* be sure to set correct permission */
     char *w_session = getenv("w_session");
     int L1 = (int) (strlen(w_session)) + find_number_of_digits(canvas_root_id) + 48;
    char *getfile_cmd = my_newmem(L1); /* create memory to fit string precisely */
     snprintf(getfile_cmd,L1,"wims.cgi?session=%s&cmd=getfile&special_parm=%d.js",w_session,canvas_root_id);/* extension ".gz" is MANDATORY for webserver */
    /* write the include tag to html page:<script type="text/javascript" src="wims.cgi?session=%s&cmd=getfile&special_parm=11223344_js"></script> */
    /* now write file into getfile dir*/
    char *w_wims_home = getenv("w_wims_home"); /* "/home/users/wims" : we need absolute path for location */
    int L2 = (int) (strlen(w_wims_home)) + (int) (strlen(w_wims_session)) + find_number_of_digits(canvas_root_id) + 23;
    char *location = my_newmem(L2); /* create memory to fit string precisely */
    snprintf(location,L2,"%s/sessions/%s/getfile/%d.js",w_wims_home,w_wims_session,canvas_root_id);/*absolute path */
    js_include_file = fopen(location,"w");/* open the file location for writing */
    /* check on opening...if nogood : mount readonly? disk full? permissions not set correctly? */
    if(js_include_file == NULL){ canvas_error("SHOULD NOT HAPPEN : could not write to javascript include file...check your system logfiles !" );}

/* ----------------------------------------------------- */
/* while more lines to process */

    while(!finished){
	if(line_number>1 && found_size_command == 0){canvas_error("command \"size xsize,ysize\" needs to come first ! ");}
	type = get_token(infile);
	done = FALSE;
	/*
	@canvasdraw
	@will try use the same syntax as flydraw or svgdraw to paint a html5 bitmap image<br />by generating a tailor-made javascript include file: providing only the js-functionality needed to perform the job.<br />thus ensuring a minimal strain on the client browser <br />(unlike some popular 'canvas-do-it-all' libraries, who have proven to be not suitable for low-end computers found in schools...)
	@General syntax <ul><li>The transparency of all objects can be controlled by command 'opacity [0-255],[0,255]'</il><li>a line based object can be controlled by command 'linewidth int'</li><li>a line based object may be dashed by using keyword 'dashed' before the object command.<br />the dashing type can be controled by command 'dashtype int,int'</li><li>a fillable object can be set fillable by starting the object command with an 'f'<br />(like frect,fcircle,ftriangle...)<br />or by using the keyword 'filled' before the object command.<br />The fill colour will be the stroke colour...(19/10/2013)</li><li> all draggable objects may have a slider for translation / rotation; several objects may be translated / rotated by a single slider</li> <li> a draggable object can be set draggable by a preceding command 'drag x/y/xy'<br />The translation can be read by javascript:read_dragdrop();The replyformat is : object_number : x-orig : y-orig : x-drag : y-drag<br />The x-orig/y-orig will be returned in maximum precision (javascript float)...<br />the x-drag/y-drag will be returned in defined 'precision' number of decimals<br />Multiple objects may be set draggable / clickable (no limit)<br /> not all flydraw objects may be dragged / clicked<br />Only draggable / clickable objects will be scaled on zoom and will be translated in case of panning</li><li> a 'onclick object' can be set 'clickable' by the preceding keyword 'onclick'<br />not all flydraw objects can be set clickable</li><li><b>remarks using a ';' as command separator</b><br />commands with only numeric or colour arguments may be using a ';' as command separator (in stead of a new line)<br />commands with a string argument may not use a ';' as command separator !<br />these exceptions are not really straight forward... so keep this in mind.</li></ul>
	@If needed multiple interactive scripts may be used in a single webpage.<br />A function 'read_canvas()' and / or 'read_dragdrop()' can read all interactive userdata from these images.<br />The global array 'canvas_scripts' will contain all unique random "canvas_root_id" of the included scripts.<br />The included local javascript "read" functions "read_canvas%d()" and "read_dragdrop%d()" will have this "%d = canvas_root_id"<br />e.g. canvas_scripts[0] will be the random id of the first script in the page and will thus provide a function<br />fun = eval("read_canvas"+canvas_scripts[0]) to read user based drawings / inputfield in this first image.<br />The read_dragdrop is analogue.<br />Use command 'replyformat' to format the replies for an individual canvas script,<br />To read all user interactions from all included canvas scripts , use something like:<br /><em>function read_all_canvas_images(){<br />&nbsp;var script_len = canvas_scripts.length;<br />&nbsp;var draw_reply = "";<br />&nbsp;var found_result = false;<br />&nbsp;for(var p = 0 ; p < script_len ; p++){<br />&nbsp;&nbsp;var fun = eval("read_canvas"+canvas_scripts[p]);<br />&nbsp;&nbsp;if( typeof fun === 'function'){<br />&nbsp;&nbsp;&nbsp;var result = fun();<br />&nbsp;&nbsp;&nbsp;if( result&nbsp;&nbsp;&& result.length != 0){<br />&nbsp;&nbsp;&nbsp;&nbsp;if(script_len == 1 ){ return result;};<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;found_result = true;<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;draw_reply = draw_reply + result + "\\n";<br />&nbsp;&nbsp;&nbsp;&nbsp;};<br />&nbsp;&nbsp;&nbsp;};<br />&nbsp;&nbsp;};<br />&nbsp;if( found_result ){return draw_reply;}else{return null;};<br />};</em>	
	*/
	switch(type){
	case END:
	finished = 1;
	done = TRUE;
	break;
	case 0:
	    sync_input(infile);
	    break;
	case COMMENT:
	    sync_input(infile);
	    break;
	case EMPTY:
	    sync_input(infile);
	    break;
	case SIZE:
	    /*
	    @size width,height
	    @set canvas size in pixels
	    @mandatory first command
	    @if xrange and/or yrange is not given the range will be set to pixels :<br />xrange 0,xsize yrange 0,ysize<br />note: lower left  corner is Origin (0:0) !!! this in contrast to flydraw
	    */
	    found_size_command = 1;
	    xsize = (int)(abs(round(get_real(infile,0)))); /* just to be sure that sizes > 0 */
	    ysize = (int)(abs(round(get_real(infile,1))));
	    /* sometimes we want xrange / yrange to be in pixels...without telling x/y-range */
	    xmin = 0;xmax = xsize;
	    ymin = 0;ymax = ysize;

/*
 The sequence in which stuff is finally printed is important !!
 for example, when writing a 'include.js" the may not be a "script tag <script>" etc etc
*/
fprintf(stdout,"\n<script type=\"text/javascript\">\
if( typeof wims_status === 'undefined' ){ var wims_status = \"$status\";};\
if( typeof use_dragdrop_reply === 'undefined' ){ var use_dragdrop_reply = false;};\
if( typeof canvas_scripts === 'undefined' ){ var canvas_scripts = new Array();};\
canvas_scripts.push(\"%d\");</script>\n\
<!-- canvasdraw div and tooltip placeholder, if needed -->\n\
<div tabindex=\"0\" id=\"canvas_div%d\" style=\"position:relative;width:%dpx;height:%dpx;margin-left:auto;margin-right:auto;\" ></div>\n\
<div id=\"tooltip_placeholder_div%d\" style=\"display:block;position:relative;margin-left:auto;margin-right:auto;margin-bottom:4px;\">\
<span id=\"tooltip_placeholder%d\" style=\"display:none;\">\n</span>\
</div>\n",canvas_root_id,canvas_root_id,xsize,ysize,canvas_root_id,canvas_root_id);
fprintf(stdout,"<!-- include actual object code via include file -->\n<script id=\"canvas_script%d\" type=\"text/javascript\" src=\"%s\"></script>\n",canvas_root_id,getfile_cmd);
fprintf(js_include_file,"\n<!-- begin generated javascript include for canvasdraw -->\n\
\"use strict\";\n\
<!-- these variables and functions must be global -->\n\
var read_dragdrop%d;\
var read_canvas%d;\
var set_clock;\
var clear_draw_area%d;\
var wims_canvas_function%d = function(){\n<!-- common used stuff -->\n\
var userdraw_x = [];var userdraw_y = [];var userdraw_radius = [];\n\
var xsize = %d;\
var ysize = %d;\
var precision = 100;\
var canvas_div = document.getElementById(\"canvas_div%d\");\
var create_canvas%d = function(canvas_type,size_x,size_y){var cnv;if(document.getElementById(\"wims_canvas%d\"+canvas_type)){ cnv = document.getElementById(\"wims_canvas%d\"+canvas_type);}else{try{ cnv = document.createElement(\"canvas\"); }catch(e){alert(\"Your browser does not support HTML5 CANVAS:GET FIREFOX !\");return;};canvas_div.appendChild(cnv);};cnv.width = size_x;cnv.height = size_y;cnv.style.top = 0;cnv.style.left = 0;cnv.style.position = \"absolute\";cnv.id = \"wims_canvas%d\"+canvas_type;return cnv;};\
function findPosX(i){ var obj = i;var curleft = 0;if(obj.offsetParent){while(1){curleft += obj.offsetLeft;if(!obj.offsetParent){break;};obj = obj.offsetParent;};}else{if(obj.x){curleft += obj.x;};};return curleft;};function findPosY(i){var obj = i;var curtop = 0;if(obj.offsetParent){while(1){curtop += obj.offsetTop;if(!obj.offsetParent){break;};obj = obj.offsetParent;};}else{if(obj.y){curtop += obj.y;};};return curtop;};\
function x2px(x){if(use_xlogscale == 0 ){return parseFloat(x*xsize/(xmax - xmin) - xsize*xmin/(xmax - xmin));}else{var x_max = Math.log(xmax)/Math.log(xlogbase);var x_min = Math.log(xmin)/Math.log(xlogbase);var x_in = Math.log(x)/Math.log(xlogbase);return x_in*xsize/(x_max - x_min) - xsize*x_min/(x_max - x_min);};};\
function px2x(px){if(use_xlogscale == 0 ){return parseFloat(px*(xmax - xmin)/xsize + xmin);}else{var x_max = Math.log(xmax)/Math.log(xlogbase);var x_min = Math.log(xmin)/Math.log(xlogbase);var x_out = x_min +px*(x_max - x_min)/(xsize);return Math.pow(xlogbase,x_out);};};\
function px2y(py){if(use_ylogscale == 0 ){return parseFloat(ymax - py*(ymax - ymin)/ysize);}else{var y_max = Math.log(ymax)/Math.log(ylogbase);var y_min = Math.log(ymin)/Math.log(ylogbase);var y_out = y_max +py*(y_min - y_max)/(ysize);return Math.pow(ylogbase,y_out);};};\
function y2px(y){if(use_ylogscale == 0){return parseFloat(-1*y*ysize/(ymax - ymin) + ymax*ysize/(ymax - ymin));}else{var y_max = Math.log(ymax)/Math.log(ylogbase);var y_min = Math.log(ymin)/Math.log(ylogbase);var y_in = Math.log(y)/Math.log(ylogbase);return (y_max - y_in)*ysize/(y_max - y_min);};};\
function scale_x_radius(rx){return rx*xsize/(xmax - xmin);};\
function scale_y_radius(ry){return ry*ysize/(ymax - ymin);};\
function distance(x1,y1,x2,y2){return parseInt(Math.sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ));};\
function distance_to_line (r,q,x,y){var c = (y) - (-1/r)*(x);var xs = r*(c - q)/(r*r+1);var ys = (r)*(xs)+(q);return parseInt(Math.sqrt( (xs-x)*(xs-x) + (ys-y)*(ys-y) ));};\
function move(obj,dx,dy){for(var p = 0 ; p < obj.x.length; p++){obj.x[p] = obj.x[p] + dx;obj.y[p] = obj.y[p] + dy;};return obj;};\
function slide(obj,dx,dy){for(var p = 0 ; p < obj.x.length; p++){obj.x[p] = x2px(obj.xorg[p] + dx);obj.y[p] = y2px(obj.yorg[p] + dy);};return obj;};\
var x_use_snap_to_grid = 0;var y_use_snap_to_grid = 0;var snap_x = 1;var snap_y = 1;\
function snap_to_x(x){return x2px(snap_x*(Math.round((px2x(x))/snap_x)));};\
function snap_to_y(y){return y2px(snap_y*(Math.round((px2y(y))/snap_y)));};\
var xlogbase = 10;\
var ylogbase = 10;\
var use_xlogscale = 0;\
var use_ylogscale = 0;\
var x_strings = null;\
var y_strings = null;\
var use_pan_and_zoom = 0;\
var use_jsmath = 0;\
var xstart = 0;\
var ystart = 0;\
var unit_x=\" \";\
var unit_y=\" \";",canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,xsize,ysize,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id);
/* default add the drag code : nearly always used ...*/
  add_drag_code(js_include_file,DRAG_CANVAS,canvas_root_id);

	    break;
	case XRANGE:
	/*
	@ xrange xmin,xmax
	@ if not given: 0,xsize (eg in pixels)
	*/
	    for(i = 0 ; i<2; i++){
		switch(i){
		    case 0: xmin = get_real(infile,0);break;
		    case 1: xmax = get_real(infile,1);break;
		    default: break;
		}
	    }
	    if(xmin >= xmax){canvas_error(" xrange is not OK : xmin &lt; xmax !\n");}
	    fprintf(js_include_file,"var xmin = %f;var xmax = %f;",xmin,xmax);
	    found_size_command++;
	    break;
	case YRANGE:
	/*
	@ yrange ymin,ymax
	@ if not given 0,ysize (eg in pixels)
	*/
	    for(i = 0 ; i<2; i++){
		switch(i){
		    case 0: ymin = get_real(infile,0);break;
		    case 1: ymax = get_real(infile,1);break;
		    default: break;
		}
	    }
	    if(ymin >= ymax){canvas_error(" yrange is not OK : ymin &lt; ymax !\n");}
	    fprintf(js_include_file,"var ymin = %f;var ymax = %f;",ymin,ymax);
	    found_size_command++;
	    break;
	case TRANGE:
	/*
	@ trange tmin,tmax
	@ default -2,2
	*/
	    use_parametric = TRUE;
	    for(i = 0 ; i<2; i++){
		switch(i){
		    case 0: tmin = get_real(infile,0);break;
		    case 1: tmax = get_real(infile,1);break;
		    default: break;
		}
	    }
	    if(tmin >= tmax ){canvas_error(" trange is not OK : tmin &lt; tmax!\n");}
	    break;
	case LINEWIDTH:
	/*
	@ linewidth int
	@ default 1
	*/
	    line_width = (int) (get_real(infile,1));
	    break;
	case ARROWHEAD:
	/*
	@ arrowhead int
	@ default 8 (pixels)
	*/
	    arrow_head = (int) (get_real(infile,1));
	    break;
	case CROSSHAIRSIZE:
	/*
	@ crosshairsize int
	@ default 8 (px)
	*/
	    crosshair_size = (int) (get_real(infile,1));
	    break;
	case CROSSHAIR:
	/*
	@ crosshair x,y,color
	@ draw a single crosshair point at (x;y) in color 'color'
	@ use command 'crosshairsize int' and / or 'linewidth int'  to adust
	@ may be set draggable / onclick
	*/
	    for(i=0;i<3;i++){
    		switch(i){
    		    case 0: double_data[0] = get_real(infile,0);break; /* x */
    		    case 1: double_data[1] = get_real(infile,0);break; /* y */
    		    case 2: stroke_color = get_color(infile,1);/* name or hex color */
    			decimals = find_number_of_digits(precision);
    			fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,7,[%.*f],[%.*f],[%d],[%d],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[1],crosshair_size,crosshair_size,line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_filled,0,0,0,use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
    			click_cnt++;reset();
    			break;
		    default:break;
		}
	    }
	    break;
	case CROSSHAIRS:
	/*
	@ crosshairs color,x1,y1,x2,y2,...,x_n,y_n
	@ draw multiple crosshair points at given coordinates in color 'color'
	@ use command 'crosshairsize int' and / or 'linewidth int'  to adust
	@ may be set draggable / onclick individually (!)
	*/
	    stroke_color=get_color(infile,0); /* how nice: now the color comes first...*/
	    fill_color = stroke_color;
	    i=0;
	    while( ! done ){     /* get next item until EOL*/
		if(i > MAX_INT - 1){canvas_error("to many points in argument: repeat command multiple times to fit");}
		if(i%2 == 0 ){
		    double_data[i] = get_real(infile,0); /* x */
		}
		else
		{
		    double_data[i] = get_real(infile,1); /* y */
		}
		i++;
	    }
	    decimals = find_number_of_digits(precision);
    	    for(c=0 ; c < i-1 ; c = c+2){
		fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,7,[%.*f],[%.*f],[%d],[%d],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[c],decimals,double_data[c+1],crosshair_size,crosshair_size,line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,1,0,0,0,use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		click_cnt++;
	    }
	    reset();
	    break;
	case POINT:
	/*
	@ point x,y,color
	@ draw a single point at (x;y) in color 'color'
	@ use command 'linewidth int'  to adust size
	@ may be set draggable / onclick
	@ will not resize on zooming <br />(command 'circle x,y,r,color' will resize on zooming)
	*/
    	    for(i=0;i<3;i++){
    		switch(i){
    		    case 0: double_data[0] = get_real(infile,0);break; /* x */
    		    case 1: double_data[1] = get_real(infile,0);break; /* y */
    		    case 2: stroke_color = get_color(infile,1);/* name or hex color */
		    decimals = find_number_of_digits(precision);
		    fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,2,[%.*f],[%.*f],[%d],[%d],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[1],line_width,line_width,line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,1,0,0,0,use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		    click_cnt++;break;
		    default: break;
		}
	    }
	    reset();
	    break;
	case POINTS:
	/*
	@ points color,x1,y1,x2,y2,...,x_n,y_n
	@ draw multiple points at given coordinates in color 'color'
	@ use command 'linewidth int'  to adust size
	@ may be set draggable / onclick individually (!)
	*/
	    stroke_color=get_color(infile,0); /* how nice: now the color comes first...*/
	    fill_color = stroke_color;
	    i=0;
	    while( ! done ){     /* get next item until EOL*/
		if(i > MAX_INT - 1){canvas_error("to many points in argument: repeat command multiple times to fit");}
		if(i%2 == 0 ){
		    double_data[i] = get_real(infile,0); /* x */
		}
		else
		{
		    double_data[i] = get_real(infile,1); /* y */
		}
		i++;
	    }
	    decimals = find_number_of_digits(precision);
	    for(c = 0 ; c < i-1 ; c = c+2){
		fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,2,[%.*f],[%.*f],[%d],[%d],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[c],decimals,double_data[c+1],line_width,line_width,line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,1,0,0,0,use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		click_cnt++;
	    }
	    reset();
	    break;
	case SEGMENTS:
	/*
	@ segments color,x1,y1,x2,y2,...,x_n,y_n
	@ draw multiple segments between points (x1:y1)--(x2:y2).....and... (x_n-1:y_n-1)--(x_n:y_n) in color 'color'
	@ use command 'linewidth int'  to adust size
	@ may be set draggable / onclick individually (!)
	*/
	    stroke_color=get_color(infile,0); /* how nice: now the color comes first...*/
	    fill_color = stroke_color;
	    i=0;
	    while( ! done ){     /* get next item until EOL*/
		if(i > MAX_INT - 1){canvas_error("to many points in argument: repeat command multiple times to fit");}
		if(i%2 == 0 ){
		    double_data[i] = get_real(infile,0); /* x */
		}
		else
		{
		    double_data[i] = get_real(infile,1); /* y */
		}
		i++;
	    }
	    decimals = find_number_of_digits(precision);
	    for(c = 0 ; c < i-1 ; c = c+4){
		fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,4,[%.*f,%.*f],[%.*f,%.*f],[30,30],[30,30],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[c],decimals,double_data[c+2],decimals,double_data[c+1],decimals,double_data[c+3],line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,0,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		click_cnt++;
	    }
	    reset();
	    break;
	case SEGMENT:
	/*
	@ segment x1,y1,x2,y2,color
	@ draw a line segment between points (x1:y1)--(x2:y2) in color 'color'
	@ may be set draggable / onclick
	*/
	    for(i=0;i<5;i++) {
		switch(i){
		    case 0: double_data[0]= get_real(infile,0);break; /* x1-values */
		    case 1: double_data[1]= get_real(infile,0);break; /* y1-values */
		    case 2: double_data[2]= get_real(infile,0);break; /* x2-values */
		    case 3: double_data[3]= get_real(infile,0);break; /* y2-values */
		    case 4: stroke_color=get_color(infile,1);/* name or hex color */
			decimals = find_number_of_digits(precision);
			fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,4,[%.*f,%.*f],[%.*f,%.*f],[30,30],[30,30],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[2],decimals,double_data[1],decimals,double_data[3],line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,0,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
			click_cnt++;reset();
			break;
		    default: break;
		}
	    }
	    break;
	case LINE:
	/*
	@ line x1,y1,x2,y2,color
	@ draw a line through points (x1:y1)--(x2:y2) in color 'color'
	@ or use command 'curve color,formula' to draw the line <br />(uses more points to draw the line; is however better draggable)
	@ may be set draggable / onclick
	*/
	    for(i=0;i<5;i++){
		switch(i){
		    case 0: double_data[10]= get_real(infile,0);break; /* x-values */
		    case 1: double_data[11]= get_real(infile,0);break; /* y-values */
		    case 2: double_data[12]= get_real(infile,0);break; /* x-values */
		    case 3: double_data[13]= get_real(infile,0);break; /* y-values */
		    case 4: stroke_color=get_color(infile,1);/* name or hex color */
		    if( double_data[10] == double_data[12] ){ /* vertical line*/
			double_data[1] = xmin;
			double_data[3] = ymax;
			double_data[0] = double_data[10];
			double_data[2] = double_data[10];
		    }
		    else
		    {
			if( double_data[11] == double_data[13] ){ /* horizontal line */
			    double_data[1] = double_data[11];
			    double_data[3] = double_data[11];
			    double_data[0] = ymin;
			    double_data[2] = xmax;
			}
			else
			{
			/* m */
			double_data[5] = (double_data[13] - double_data[11]) /(double_data[12] - double_data[10]);
			/* q */
			double_data[6] = double_data[11] - ((double_data[13] - double_data[11]) /(double_data[12] - double_data[10]))*double_data[10];

			/*xmin,m*xmin+q,xmax,m*xmax+q*/

			    double_data[1] = (double_data[5])*(xmin)+(double_data[6]);
			    double_data[3] = (double_data[5])*(xmax)+(double_data[6]);
			    double_data[0] = xmin;
			    double_data[2] = xmax;
			}
		    }
		    decimals = find_number_of_digits(precision);
		    fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,4,[%.*f,%.*f],[%.*f,%.*f],[30,30],[30,30],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[2],decimals,double_data[1],decimals,double_data[3],line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,0,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		    click_cnt++;reset();
		    break;
		}
	    }
	    break;
	case LINES:
	/*
	@ lines color,x1,y1,x2,y2...x_n-1,y_n-1,x_n,y_n
	@ draw multiple lines through points (x1:y1)--(x2:y2) ...(x_n-1:y_n-1)--(x_n:y_n) in color 'color'
	@ or use multiple commands 'curve color,formula' or "jscurve color,formule" to draw the line <br />(uses more points to draw the line; is however better draggable)
	@ may be set draggable / onclick
	@ <b>Attention</b>: the flydraw command "lines" is equivalent to canvasdraw command "polyline"
	*/
	    stroke_color=get_color(infile,0); /* how nice: now the color comes first...*/
	    fill_color = stroke_color;
	    i=0;
	    while( ! done ){     /* get next item until EOL*/
		if(i > MAX_INT - 1){canvas_error("to many points in argument: repeat command multiple times to fit");}
		if(i%2 == 0 ){
		    double_data[i] = get_real(infile,0); /* x */
		}
		else
		{
		    double_data[i] = get_real(infile,1); /* y */
		}
		i++;
	    }
	    decimals = find_number_of_digits(precision);
	    for(c = 0 ; c < i-1 ; c = c+4){
		if( double_data[c] == double_data[c+2] ){ /* vertical line*/
		    double_data[c+1] = xmin;
		    double_data[c+3] = ymax;
		    double_data[c+2] = double_data[c];
		}
		else
		{
		    if( double_data[c+1] == double_data[c+3] ){ /* horizontal line */
			double_data[c+3] = double_data[c+1];
			double_data[c] = ymin;
			double_data[c+2] = xmax;
		    }
		    else
		    {
			/* m */
			double m = (double_data[c+3] - double_data[c+1]) /(double_data[c+2] - double_data[c]);
			/* q */
			double q = double_data[c+1] - ((double_data[c+3] - double_data[c+1]) /(double_data[c+2] - double_data[c]))*double_data[c];
			/*xmin,m*xmin+q,xmax,m*xmax+q*/
			double_data[c+1] = (m)*(xmin)+(q);
			double_data[c+3] = (m)*(xmax)+(q);
			double_data[c] = xmin;
			double_data[c+2] = xmax;
		    }
		}
		fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,4,[%.*f,%.*f],[%.*f,%.*f],[30,30],[30,30],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[c],decimals,double_data[c+2],decimals,double_data[c+1],decimals,double_data[c+3],line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,0,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		click_cnt++;
	    }
	    reset();
	    break;
	case HALFLINE:
	/*
	@ demiline x1,y1,x2,y2,color
	@ alternative : halfline
	@ draws a halfline starting in (x1:y1) and through (x2:y2) in color 'color' (colorname or hex)
	@ may be set draggable / onclick
	*/
	    for(i=0;i<5;i++){
		switch(i){
		    case 0: double_data[0]= get_real(infile,0);break; /* x-values */
		    case 1: double_data[1]= get_real(infile,0);break; /* y-values */
		    case 2: double_data[10]= get_real(infile,0);break; /* x-values */
		    case 3: double_data[11]= get_real(infile,0);break; /* y-values */
		    case 4: stroke_color=get_color(infile,1);/* name or hex color */
		    if(double_data[0] == double_data[10]){ /* vertical halfline */
			if(double_data[1] < double_data[11]){
			 double_data[3] = ymax + 1000;
			}
			else
			{
			 double_data[3] = ymin - 1000;
			}
			double_data[2] = double_data[0]; 
		    }
		    else
		    { /* horizontal halfline*/
		     if( double_data[1] == double_data[11] ){
		      if( double_data[0] < double_data[10] ){
		        double_data[2] = xmax + 1000; /* halfline to the right */
		      }
		      else
		      {
		        double_data[2] = xmin - 1000; /* halfline to the left */
		      }
		      double_data[3] = double_data[1];
		     }
		     else
		     {
		      /* any other halfline */
		      /* slope */
		      double_data[12] = (double_data[11] - double_data[1])/(double_data[10] - double_data[0]);
		      /* const */
		      double_data[13] = double_data[1] - double_data[12]*double_data[0];
		      if( double_data[0] < double_data[10] ){
		       double_data[2] = double_data[2] + 1000;
		      }
		      else
		      {
		       double_data[2] = double_data[2] - 1000;
		      }
		      double_data[3] = double_data[12]*double_data[2] + double_data[13];
		     }
		    }    
		    decimals = find_number_of_digits(precision);
		    fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,18,[%.*f,%.*f],[%.*f,%.*f],[30,30],[30,30],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[2],decimals,double_data[1],decimals,double_data[3],line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,0,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		    click_cnt++;reset();
		    break;
		}
	    }
	    break;
	case HALFLINES:
	/*
	@ demilines color,x1,y1,x2,y2,....
	@ alternative : halflines
	@ draws halflines starting in (x1:y1) and through (x2:y2) in color 'color' (colorname or hex) etc etc
	@ may be set draggable / onclick indiviually
	*/
	    stroke_color=get_color(infile,0);
	    fill_color = stroke_color;
	    i=0;
	    while( ! done ){     /* get next item until EOL*/
		if(i > MAX_INT - 1){canvas_error("to many points in argument: repeat command multiple times to fit");}
		if(i%2 == 0 ){
		    double_data[i] = get_real(infile,0); /* x */
		}
		else
		{
		    double_data[i] = get_real(infile,1); /* y */
		}
		i++;
	    }
	    decimals = find_number_of_digits(precision);
	    for(c = 0 ; c < i-1 ; c = c+4){
		if( double_data[c] == double_data[c+2] ){ /* vertical line*/
		    if(double_data[c+1] < double_data[c+3]){ /* upright halfline */
			double_data[c+3] = ymax + 1000;
		    }
		    else
		    {
		     double_data[c+3] = ymin - 1000;/* descending halfline */
		    }
		}
		else
		{
		    if( double_data[c+1] == double_data[c+3] ){ /* horizontal line */
		        if(double_data[c] < double_data[c+2] ){ /* halfline to the right */
		    	    double_data[c+2] = xmax+100;
		    	}
		    	else
		    	{
		    	    double_data[c+2] = xmin-1000; /* halfline to the right */
		    	}
		    }
		    else
		    {
			/* m */
			double m = (double_data[c+3] - double_data[c+1]) /(double_data[c+2] - double_data[c]);
			/* q */
			double q = double_data[c+1] - ((double_data[c+3] - double_data[c+1]) /(double_data[c+2] - double_data[c]))*double_data[c];
			if(double_data[c] < double_data[c+2]){ /* to the right */
			    double_data[c+2] = xmax+1000; /* 1000 is needed for dragging...otherwise it's just segment */
			    double_data[c+3] = (m)*(double_data[c+2])+(q);
			}
			else
			{ /* to the left */
			    double_data[c+2] = xmin - 1000;
			    double_data[c+3] = (m)*(double_data[c+2])+(q);
			}
		    }
		}
		fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,18,[%.*f,%.*f],[%.*f,%.*f],[30,30],[30,30],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[c],decimals,double_data[c+2],decimals,double_data[c+1],decimals,double_data[c+3],line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,0,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		click_cnt++;
	    }
	    reset();
	    break;
	case HLINE:
	/*
	@ hline x,y,color
	@ draw a horizontal line through point (x:y) in color 'color'
	@ or use command 'curve color,formula' to draw the line <br />(uses more points to draw the line; is however better draggable)
	@ may be set draggable / onclick
	*/
	    for(i=0;i<3;i++) {
		switch(i){
		    case 0: double_data[0] = get_real(infile,0);break; /* x-values */
		    case 1: double_data[1] = get_real(infile,0);break; /* y-values */
		    case 2: stroke_color = get_color(infile,1);/* name or hex color */
		    double_data[3] = double_data[1];
		    decimals = find_number_of_digits(precision);
		    fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,4,[%.*f,%.*f],[%.*f,%.*f],[30,30],[30,30],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,xmin,decimals,xmax,decimals,double_data[1],decimals,double_data[3],line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,0,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		    click_cnt++;reset();
		    break;
		}
	    }
	    break;

	case HLINES:
	/*
	@ hlines color,x1,y1,x2,y2,...
	@ draw horizontal lines through points (x1:y1)...(xn:yn) in color 'color'
	@ may be set draggable / onclick individually
	*/
	    stroke_color=get_color(infile,0); /* how nice: now the color comes first...*/
	    fill_color = stroke_color;
	    i=0;
	    while( ! done ){     /* get next item until EOL*/
		if(i > MAX_INT - 1){canvas_error("to many points in argument: repeat command multiple times to fit");}
		if(i%2 == 0 ){
		    double_data[i] = get_real(infile,0); /* x */
		}
		else
		{
		    double_data[i] = get_real(infile,1); /* y */
		}
		i++;
	    }
	    decimals = find_number_of_digits(precision);
	    for(c = 0 ; c < i-1 ; c = c+2){
		fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,4,[%.*f,%.*f],[%.*f,%.*f],[30,30],[30,30],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,xmin,decimals,xmax,decimals,double_data[c+1],decimals,double_data[c+1],line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,0,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		click_cnt++;
	    }
	    reset();
	    break;
	case VLINE:
	/*
	@ vline x,y,color
	@ draw a vertical line through point (x1:y1)...(xn:yn) in color 'color'
	@ may be set draggable / onclick
	*/
	    for(i=0;i<3;i++) {
		switch(i){
		    case 0: double_data[0] = get_real(infile,0);break; /* x-values */
		    case 1: double_data[1] = get_real(infile,0);break; /* y-values */
		    case 2: stroke_color=get_color(infile,1);/* name or hex color */
			double_data[2] = double_data[0];
			decimals = find_number_of_digits(precision);
			fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,4,[%.*f,%.*f],[%.*f,%.*f],[30],[30],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[2],decimals,ymin,decimals,ymax,line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
			click_cnt++;reset();
		    break;
		}
	    }
	    break;
	case VLINES:
	/*
	@ vlines color,x1,y1,x2,y2....
	@ draw vertical lines through points (x1:y1) in color 'color'
	@ may be set draggable / onclick individually
	*/
	    stroke_color=get_color(infile,0); /* how nice: now the color comes first...*/
	    fill_color = stroke_color;
	    i=0;
	    while( ! done ){     /* get next item until EOL*/
		if(i > MAX_INT - 1){canvas_error("to many points in argument: repeat command multiple times to fit");}
		if(i%2 == 0 ){
		    double_data[i] = get_real(infile,0); /* x */
		}
		else
		{
		    double_data[i] = get_real(infile,1); /* y */
		}
		i++;
	    }
	    decimals = find_number_of_digits(precision);
	    for(c = 0 ; c < i-1 ; c = c+2){
		fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,4,[%.*f,%.*f],[%.*f,%.*f],[30],[30],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[c],decimals,double_data[c],decimals,ymin,decimals,ymax,line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		click_cnt++;
	    }
	    reset();
	    break;
	case SQUARE:
	/*
	@ square x,y,side (px) ,color
	@ draw a square with left top corner (x:y) with side 'side' in color 'color'
	@ use command 'fsquare x,y,side,color' for a filled square
	@ use command/keyword  'filled' before command 'square x,y,side,color'
	@ use command 'fillcolor color' before 'fsquare' to set the fill colour.
	@ may be set draggable / onclick
	*/
	    for(i=0;i<5;i++){
		switch(i){
		    case 0:double_data[0] = get_real(infile,0);break; /* x1-values */
		    case 1:double_data[1] = get_real(infile,0);break; /* y1-values */
		    case 2:double_data[2] = (int) (get_real(infile,0));break; /* width in px */
		    case 3:
			stroke_color = get_color(infile,1);/* name or hex color */
			decimals = find_number_of_digits(precision);
			double_data[3] = double_data[0] + (xmax - xmin)*double_data[2]/xsize;
			double_data[4] = double_data[1] + -1*(ymax - ymin)*double_data[2]/ysize;
			fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,1,[%.*f,%.*f,%.*f,%.*f],[%.*f,%.*f,%.*f,%.*f],[%d],[%d],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[3],decimals,double_data[3],decimals,double_data[0],decimals,double_data[1],decimals,double_data[1],decimals,double_data[4],decimals,double_data[4],line_width,line_width,line_width,stroke_color,stroke_opacity,stroke_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
			click_cnt++;reset();
			break;
		}
	    }
	    break;
	case ROUNDRECT:
	/*
	@ roundrect x1,y1,x2,y2,radius,color
	@ use command 'froundrect x1,y1,x2,y2,radius,color' for a filled rectangle
	@ use command/keyword  'filled' before command 'roundrect x1,y1,x2,y2,radius,color'
	@ use command 'fillcolor color' before 'froundrect' to set the fill colour.
	@ may be set draggable / onclick
	*/
	    for(i=0;i<6;i++){
		switch(i){
		    case 0:double_data[0] = get_real(infile,0);break; /* x-values */
		    case 1:double_data[1] = get_real(infile,0);break; /* y-values */
		    case 2:double_data[2] = get_real(infile,0);break; /* x-values */
		    case 3:double_data[3] = get_real(infile,0);break; /* y-values */
		    case 4:int_data[0] = (int) (get_real(infile,0));break; /* radius value in pixels */
		    case 5:stroke_color = get_color(infile,1);/* name or hex color */
			/* ensure no inverted roundrect is produced... */
			if( double_data[0] > double_data[2] ){double_data[4] = double_data[0];double_data[0] = double_data[2];double_data[2] = double_data[4];}
			if( double_data[3] > double_data[1] ){double_data[4] = double_data[1];double_data[1] = double_data[3];double_data[3] = double_data[4];}
    			decimals = find_number_of_digits(precision);
			fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,6,[%.*f,%.*f],[%.*f,%.*f],[%d,%d],[%d,%d],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[2],decimals,double_data[1],decimals,double_data[3],int_data[0],int_data[0],int_data[0],int_data[0],line_width,stroke_color,stroke_opacity,stroke_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
			click_cnt++;reset();
	            break;
		}
	    }
	    break;
	case RECT:
	/*
	@ rect x1,y1,x2,y2,color
	@ use command 'frect x1,y1,x2,y2,color' for a filled rectangle
	@ use command/keyword  'filled' before command 'rect x1,y1,x2,y2,color'
	@ use command 'fillcolor color' before 'frect' to set the fill colour.
	@ may be set draggable / onclick
	*/
	    for(i=0;i<5;i++){
		switch(i){
		    case 0:double_data[0] = get_real(infile,0);break; /* x-values */
		    case 1:double_data[1] = get_real(infile,0);break; /* y-values */
		    case 2:double_data[2] = get_real(infile,0);break; /* x-values */
		    case 3:double_data[3] = get_real(infile,0);break; /* y-values */
		    case 4:stroke_color = get_color(infile,1);/* name or hex color */
    			decimals = find_number_of_digits(precision);
			fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,1,[%.*f,%.*f,%.*f,%.*f],[%.*f,%.*f,%.*f,%.*f],[%d],[%d],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[2],decimals,double_data[2],decimals,double_data[0],decimals,double_data[1],decimals,double_data[1],decimals,double_data[3],decimals,double_data[3],line_width,line_width,line_width,stroke_color,stroke_opacity,stroke_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
			click_cnt++;reset();
			break;
		}
	    }
	    break;

	case RECTS:
	/*
	@ rects color,x1,y1,x2,y2,.....
	@ use command 'frect color,x1,y1,x2,y2,.....' for a filled rectangle
	@ use command/keyword  'filled' before command 'rects color,x1,y1,x2,y2,....'
	@ use command 'fillcolor color' before 'frects' to set the fill colour.
	@ may be set draggable / onclick individually
	*/
	    stroke_color=get_color(infile,0); /* how nice: now the color comes first...*/
	    fill_color = stroke_color;
	    i=0;
	    while( ! done ){     /* get next item until EOL*/
		if(i > MAX_INT - 1){canvas_error("to many points in argument: repeat command multiple times to fit");}
		if(i%2 == 0 ){
		    double_data[i] = get_real(infile,0); /* x */
		}
		else
		{
		    double_data[i] = get_real(infile,1); /* y */
		}
		i++;
	    }
	    decimals = find_number_of_digits(precision);
	    for(c = 0 ; c < i-1 ; c = c+4){
		fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,1,[%.*f,%.*f,%.*f,%.*f],[%.*f,%.*f,%.*f,%.*f],[%d],[%d],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[c],decimals,double_data[c+2],decimals,double_data[c+2],decimals,double_data[c],decimals,double_data[c+1],decimals,double_data[c+1],decimals,double_data[c+3],decimals,double_data[c+3],line_width,line_width,line_width,stroke_color,stroke_opacity,stroke_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		click_cnt++;
	    }
	    reset();
	    break;
	case POLYLINE:
	/*
	@ polyline color,x1,y1,x2,y2...x_n,y_n
	@ alternatives:<br />polylines color,x1,y1,x2,y2...x_n,y_n<br />brokenline color,x1,y1,x2,y2...x_n,y_n<br />brokenlines color,x1,y1,x2,y2...x_n,y_n
	@ draw a broken line interconnected between all points (not closed)
	@ equivalent to flydraw command "line color,x1,y1,x2,y2...x_n,y_n"
	@ use command "segments color,x1,y1,x2,y2...x_n,y_n" for not interconnected line segments.
	@ may be set draggable / onclick
	*/
	    stroke_color=get_color(infile,0); /* how nice: now the color comes first...*/
	    i=0;
	    c=0;
	    while( ! done ){     /* get next item until EOL*/
		if(i > MAX_INT - 1){canvas_error("to many points in argument: repeat command multiple times to fit");}
		for( c = 0 ; c < 2; c++){
		    if(c == 0 ){
			double_data[i] = get_real(infile,0);
			i++;
		    }
		    else
		    {
			double_data[i] = get_real(infile,1);
			i++;
		    }
		}
	    }
	    /* draw path : not closed & not filled */
    	    decimals = find_number_of_digits(precision);
	    fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,4,%s,[30],[30],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,double_xy2js_array(double_data,i,decimals),line_width,stroke_color,stroke_opacity,stroke_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
	    click_cnt++;reset();
	    break;
	case POLY:
	/*
	@ poly color,x1,y1,x2,y2...x_n,y_n
	@ draw closed polygon
	@ use command 'fpoly' to fill it, use command 'fillcolor color' to set the fill color
	@ may be set draggable / onclick
	*/
	    stroke_color=get_color(infile,0); /* how nice: now the color comes first...*/
	    i=0;
	    c=0;
	    while( ! done ){     /* get next item until EOL*/
		if(i > MAX_INT - 1){canvas_error("to many points in argument: repeat command multiple times to fit");}
		for( c = 0 ; c < 2; c++){
		    if(c == 0 ){
			double_data[i] = get_real(infile,0);
			i++;
		    }
		    else
		    {
			double_data[i] = get_real(infile,1);
			i++;
		    }
		}
	    }
	    /* draw path :  closed & optional filled */
    		decimals = find_number_of_digits(precision);
		fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,5,%s,[30],[30],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,double_xy2js_array(double_data,i,decimals),line_width,stroke_color,stroke_opacity,stroke_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		click_cnt++;reset();
	    break;
	case ARC:
	/*
	 @ arc xc,yc,width,height,start_angle,end_angle,color
	 @ can not be set "onclick" or "drag xy"
	 @ attention: width == height == radius in pixels
	 @ will not zoom in or zoom out (because radius is given in pixels an not in x/y-system !). Panning will work
	 @ use command 'angle' for scalable angle
	*/
	    for(i=0;i<7;i++){
		switch(i){
		    case 0:double_data[0] = get_real(infile,0);break; /* x-values */
		    case 1:double_data[1] = get_real(infile,0);break; /* y-values */
		    case 2:int_data[0] = (int)(get_real(infile,0));break; /* width in pixels ! */
		    case 3:int_data[1] = (int)(get_real(infile,0));break; /* height in pixels ! */
		    case 4:double_data[2] = get_real(infile,0);break; /* start angle in degrees */
		    case 5:double_data[3] = get_real(infile,0);break; /* end angle in degrees */
		    case 6:stroke_color = get_color(infile,1);/* name or hex color */
		    /* in Shape library:
			x[0] = x[1] = xc
			y[0] = y[1] = yc
			w[0] = w[1] = radius = width = height
			h[0] = start_angle ; h[1] = end_engle
		    */
    			decimals = find_number_of_digits(precision);
    			fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,12,[%.*f,%.*f],[%.*f,%.*f],[%d,%d],[%.*f,%.*f],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[0],decimals,double_data[1],decimals,double_data[1],int_data[0],int_data[0],decimals,double_data[2],decimals,double_data[3],line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
    			reset();
	            break;
		}
	    }
	    break;
	case ANGLE:
	/*
	 @ angle xc,yc,width,start_angle,end_angle,color
	 @ width is in x-range
	 @ will zoom in/out
	 @ if size is controlled by command 'slider' use radians to set limits of slider.
	*/
	    for(i=0;i<7;i++){
		switch(i){
		    case 0:double_data[0] = get_real(infile,0);break; /* x-values */
		    case 1:double_data[1] = get_real(infile,0);break; /* y-values */
		    case 2:double_data[2] = get_real(infile,0);break; /* width in pixels ! */
		    case 3:double_data[3] = get_real(infile,0);break; /* start angle in degrees */
		    case 4:double_data[4] = get_real(infile,0);break; /* end angle in degrees */
		    case 5:stroke_color = get_color(infile,1);/* name or hex color */
    			decimals = find_number_of_digits(precision);
    			fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,17,[%.*f,%.*f],[%.*f,%.*f],[%.*f,%.*f],[%.*f,%.*f],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[0],decimals,double_data[1],decimals,double_data[1],decimals,double_data[2],decimals,double_data[2],decimals,double_data[3],decimals,double_data[4],line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
    			reset();
	            break;
		}
	    }
	    break;

	case ELLIPSE:
	/*
	@ ellipse xc,yc,radius_x,radius_y,color
	@ a ellipse with center xc/yc in x/y-range
	@ radius_x and radius_y are in pixels
	@ may be set draggable / onclick
	@ will shrink / expand on zoom out / zoom in
	*/
	    for(i=0;i<5;i++){
		switch(i){
		    case 0:double_data[0] = get_real(infile,0);break; /* x-values */
		    case 1:double_data[1] = get_real(infile,0);break; /* y-values */
		    case 2:double_data[2] = get_real(infile,0);break; /* rx -> px  */
		    case 3:double_data[3] = get_real(infile,0);break; /* ry -> px  */
		    case 4:stroke_color = get_color(infile,1);/* name or hex color */
    			decimals = find_number_of_digits(precision);
			fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,3,[%.*f],[%.*f],[%.*f],[%.*f],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[1],decimals,double_data[2],decimals,double_data[3],line_width,stroke_color,stroke_opacity,stroke_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
			click_cnt++;reset();
		    break;
		}
	    }
	    break;
	case DASHTYPE:
	/*
	@ dashtype int ,int
	@ When dashed is set, the objects will be drawn with this dashtyp
	@ default value "dashtype 2,2"
	*/
	    for(i=0;i<2;i++){
		switch(i){
	    	    case 0 : dashtype[0] = (int) line_width*( get_real(infile,0)) ; break;
	    	    case 1 : dashtype[1] = (int) line_width*( get_real(infile,1)) ; break;
		}
	    }
	break;
	case CIRCLE:
	/*
	@ circle xc,yc,width (2*r in pixels),color
	@ use command 'fcircle xc,yc,d,color' or command 'filled' for a filled disk
	@ use command 'fillcolor color' to set the fillcolor
	@ may be set draggable / onclick
	@ will shrink / expand on zoom out / zoom in
	*/
    	    for(i=0;i<4;i++){
    		switch(i){
    		    case 0: double_data[0] = get_real(infile,0);break; /* x */
    		    case 1: double_data[1] = get_real(infile,0);break; /* y */
    		    case 2: double_data[2] = px2x((get_real(infile,0))/2) - px2x(0);break; /* for zoom in/out : radius in 'dx' xrange*/
    		    case 3: stroke_color = get_color(infile,1);/* name or hex color */
    			decimals = find_number_of_digits(precision);
			fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,13,[%.*f],[%.*f],[%.3f],[%.3f],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[1],double_data[2],double_data[2],line_width,stroke_color,stroke_opacity,stroke_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
			click_cnt++;reset();
			break;
		    default : break;
		}
	    }
	    break;

	case CIRCLES:
	/*
	@ circles color,xc1,yc1,r1,xc2,yc2,r2...xc_n,yc_n,r_n
	@ Attention r = radius in x-range (!)
	@ use command 'fillcolor color' to set the fillcolor
	@ may be set draggable / onclick (individually)
	@ will shrink / expand on zoom out / zoom in
	*/
	    stroke_color=get_color(infile,0); /* how nice: now the color comes first...*/
	    fill_color = stroke_color;
	    i=1;
	    while( ! done ){     /* get next item until EOL*/
		if(i > MAX_INT - 1){canvas_error("to many points in argument: repeat command multiple times to fit");}
		switch (i%3){
		 case 1:double_data[i-1] = get_real(infile,0);break; /* x */
		 case 2:double_data[i-1] = get_real(infile,0);break; /* y */
		 case 0:double_data[i-1] = get_real(infile,1);break; /* r */
		}
		i++;
	    }
	    decimals = find_number_of_digits(precision);
	    for(c = 0 ; c < i-1 ; c = c+3){
		fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,13,[%.*f],[%.*f],[%.3f],[%.3f],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[c],decimals,double_data[c+1],double_data[c+2],double_data[c+2],line_width,stroke_color,stroke_opacity,stroke_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		click_cnt++;
	    }
	    reset();
	    break;
	case RAYS:
	/*
	 @ rays color,xc,yc,x1,y1,x2,y2,x3,y3...x_n,y_n
	 @ draw rays in color 'color' and center (xc:yc)
	 @ may be set draggable or onclick (every individual ray)
	*/
	    stroke_color=get_color(infile,0);
	    fill_color = stroke_color;
	    double_data[0] = get_real(infile,0);/* xc */
	    double_data[1] = get_real(infile,0);/* yc */
	    i=2;
	    while( ! done ){     /* get next item until EOL*/
		if(i > MAX_INT - 1){canvas_error("in command rays to many points / rays in argument: repeat command multiple times to fit");}
		if(i%2 == 0 ){
		    double_data[i] = get_real(infile,0); /* x */
		}
		else
		{
		    double_data[i] = get_real(infile,1); /* y */
		}
	    fprintf(js_include_file,"/* double_data[%d] = %f */\n",i,double_data[i]);
		i++;
	    }

	    if( i%2 != 0 ){canvas_error("in command rays: unpaired x or y value");}
	    decimals = find_number_of_digits(precision);
	    for(c=2; c<i;c = c+2){
		click_cnt++;
		fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,4,[%.*f,%.*f],[%.*f,%.*f],[30,30],[30,30],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[c],decimals,double_data[1],decimals,double_data[c+1],line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,0,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
	    }
	    reset();
	    break;

	case ARROWS:
	/*
	@ arrows color,head (px),x1,y1,x2,y2...x_n,y_n
	@ draw single headed arrows / vectors from (x1:y1) to (x2:y2) ... (x3:y3) to (x4:y4) etc ... in color 'color'
	@ use command 'linewidth int' to adjust thickness of the arrow
	@ may be set draggable / onclick individually
	*/
	    stroke_color=get_color(infile,0); /* how nice: now the color comes first...*/
	    fill_color = stroke_color;
	    arrow_head = (int) get_real(infile,0);/* h */
	    i=0;
	    while( ! done ){     /* get next item until EOL*/
		if(i > MAX_INT - 1){canvas_error("to many points in argument: repeat command multiple times to fit");}
		if(i%2 == 0 ){
		    double_data[i] = get_real(infile,0); /* x */
		}
		else
		{
		    double_data[i] = get_real(infile,1); /* y */
		}
		i++;
	    }
	    decimals = find_number_of_digits(precision);
	    for(c = 0 ; c < i-1 ; c = c+4){
		fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,8,[%.*f,%.*f],[%.*f,%.*f],[%d,%d],[%d,%d],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[c],decimals,double_data[c+2],decimals,double_data[c+1],decimals,double_data[c+3],arrow_head,arrow_head,arrow_head,arrow_head,line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,0,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		click_cnt++;
	    }
	    reset();
	    break;
	case ARROW:
	/*
	@ arrow x1,y1,x2,y2,h,color
	@ draw a single headed arrow/vector from (x1:y1) to (x2:y2)<br />with arrowhead size h in px and in color 'color'
	@ use command 'linewidth int' to adjust thickness of the arrow
	@ may be set draggable / onclick
	*/
    	    for(i=0;i<6;i++){
    		switch(i){
    		    case 0: double_data[0] = get_real(infile,0);break; /* x */
    		    case 1: double_data[1] = get_real(infile,0);break; /* y */
    		    case 2: double_data[2] = get_real(infile,0);break; /* x */
    		    case 3: double_data[3] = get_real(infile,0);break; /* y */
    		    case 4: arrow_head = (int) get_real(infile,0);break;/* h */
    		    case 5: stroke_color = get_color(infile,1);/* name or hex color */
    			decimals = find_number_of_digits(precision);
			fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,8,[%.*f,%.*f],[%.*f,%.*f],[%d,%d],[%d,%d],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[2],decimals,double_data[1],decimals,double_data[3],arrow_head,arrow_head,arrow_head,arrow_head,line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,0,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
			click_cnt++;
			reset();
			break;
    		}
    	    }
    	    break;
	case ARROW2:
	/*
	@ arrow2 x1,y1,x2,y2,h,color
	@ draw a double headed arrow/vector from (x1:y1) to (x2:y2)<br />with arrowhead size h in px and  in color 'color'
	@ use command 'arrowhead int' to adjust the arrow head size
	@ use command 'linewidth int' to adjust thickness of the arrow
	@ may be set draggable / onclick
	*/
    	    for(i=0;i<6;i++){
    		switch(i){
    		    case 0: double_data[0] = get_real(infile,0);break; /* x */
    		    case 1: double_data[1] = get_real(infile,0);break; /* y */
    		    case 2: double_data[2] = get_real(infile,0);break; /* x */
    		    case 3: double_data[3] = get_real(infile,0);break; /* y */
    		    case 4: arrow_head = (int) get_real(infile,0);break;/* h */
    		    case 5: stroke_color = get_color(infile,1);/* name or hex color */
    			decimals = find_number_of_digits(precision);
			fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,10,[%.*f,%.*f],[%.*f,%.*f],[%d,%d],[%d,%d],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[2],decimals,double_data[1],decimals,double_data[3],arrow_head,arrow_head,arrow_head,arrow_head,line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,0,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
			click_cnt++;reset();
			break;
    		}
    	    }
    	    break;
	case ARROWS2:
	/*
	@ arrows2 color,head (px),x1,y1,x2,y2...x_n,y_n
	@ draw double headed arrows / vectors from (x1:y1) to (x2:y2) ... (x3:y3) to (x4:y4) etc ... in color 'color'
	@ use command 'linewidth int' to adjust thickness of the arrows
	@ may be set draggable / onclick individually
	*/
	    stroke_color=get_color(infile,0); /* how nice: now the color comes first...*/
	    fill_color = stroke_color;
	    arrow_head = (int) get_real(infile,0);/* h */
	    i=0;
	    while( ! done ){     /* get next item until EOL*/
		if(i > MAX_INT - 1){canvas_error("to many points in argument: repeat command multiple times to fit");}
		if(i%2 == 0 ){
		    double_data[i] = get_real(infile,0); /* x */
		}
		else
		{
		    double_data[i] = get_real(infile,1); /* y */
		}
		i++;
	    }
	    decimals = find_number_of_digits(precision);
	    for(c = 0 ; c < i-1 ; c = c+4){
		fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,10,[%.*f,%.*f],[%.*f,%.*f],[%d,%d],[%d,%d],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[c],decimals,double_data[c+2],decimals,double_data[c+1],decimals,double_data[c+3],arrow_head,arrow_head,arrow_head,arrow_head,line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,0,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		click_cnt++;
	    }
	    reset();
	    break;
	case PARALLEL:
	/*
	 @ parallel x1,y1,x2,y2,dx,dy,n,[colorname or #hexcolor]
	 @ can not be set "onclick" or "drag xy"
	*/
	    for( i = 0;i < 8; i++ ){
		switch(i){
		    case 0: double_data[0] = get_real(infile,0);break; /* x1-values  -> x-pixels*/
		    case 1: double_data[1] = get_real(infile,0);break; /* y1-values  -> y-pixels*/
		    case 2: double_data[2] = get_real(infile,0);break; /* x2-values  -> x-pixels*/
		    case 3: double_data[3] = get_real(infile,0);break; /* y2-values  -> y-pixels*/
		    case 4: double_data[4] = xmin + get_real(infile,0);break; /* xv -> x-pixels */
		    case 5: double_data[5] = ymax + get_real(infile,0);break; /* yv -> y-pixels */
		    case 6: int_data[0] = (int) (get_real(infile,0));break; /* n  */
		    case 7: stroke_color=get_color(infile,1);/* name or hex color */
    		    decimals = find_number_of_digits(precision);
		    fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,11,[%.*f,%.*f,%.*f],[%.*f,%.*f,%.*f],[%d,%d,%d],[%d,%d,%d],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[2],decimals,double_data[4],decimals,double_data[1],decimals,double_data[3],decimals,double_data[5],int_data[0],int_data[0],int_data[0],int_data[0],int_data[0],int_data[0],line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
		    click_cnt++;reset();
		    break;
		    default: break;
		}
	    }
	    break;
	case TRIANGLE:
	/*
	 @triangle x1,y1,x2,y2,x3,y3,color
	 @may be set draggable / onclic
	*/
    	    for(i=0;i<7;i++){
    		switch(i){
    		    case 0: double_data[0] = get_real(infile,0);break; /* x */
    		    case 1: double_data[1] = get_real(infile,0);break; /* y */
    		    case 2: double_data[2] = get_real(infile,0);break; /* x */
    		    case 3: double_data[3] = get_real(infile,0);break; /* y */
    		    case 4: double_data[4] = get_real(infile,0);break; /* x */
    		    case 5: double_data[5] = get_real(infile,0);break; /* y */
    		    case 6: stroke_color = get_color(infile,1);/* name or hex color */
    			decimals = find_number_of_digits(precision);
    			fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,5,%s,[30],[30],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,double_xy2js_array(double_data,6,decimals),line_width,stroke_color,stroke_opacity,stroke_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
    			click_cnt++;reset();
    			break;
    		    default: break;
    		}
    	    }
	    break;
	case LATTICE:
	/*
	 @lattice x0,y0,xv1,yv1,xv2,yv2,n1,n2,color
	 @can not be set "onclick" or "drag xy"
	*/
	    if( js_function[DRAW_LATTICE] != 1 ){ js_function[DRAW_LATTICE] = 1;}
	    for( i = 0; i<9; i++){
		switch(i){
		    case 0: int_data[0] = x2px(get_real(infile,0));break; /* x0-values  -> x-pixels*/
		    case 1: int_data[1] = y2px(get_real(infile,0));break; /* y0-values  -> y-pixels*/
		    case 2: int_data[2] = (int) (get_real(infile,0));break; /* x1-values  -> x-pixels*/
		    case 3: int_data[3] = (int) -1*(get_real(infile,0));break; /* y1-values  -> y-pixels*/
		    case 4: int_data[4] = (int) (get_real(infile,0));break; /* x2-values  -> x-pixels*/
		    case 5: int_data[5] = (int) -1*(get_real(infile,0));break; /* y2-values  -> y-pixels*/
		    case 6: int_data[6] = (int) (get_real(infile,0));break; /* n1-values */
		    case 7: int_data[7] = (int) (get_real(infile,0));break; /* n2-values */
		    case 8: stroke_color=get_color(infile,1);
    			decimals = find_number_of_digits(precision);
			string_length = snprintf(NULL,0,"draw_lattice(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,\"%s\",%.2f,\"%s\",%.2f,%d,%.2f,%d,%s);",STATIC_CANVAS,line_width,int_data[0],int_data[1],int_data[2],int_data[3],int_data[4],int_data[5],int_data[6],int_data[7],fill_color,fill_opacity,stroke_color,stroke_opacity,use_rotate,angle,use_affine,affine_matrix);
			check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
			snprintf(tmp_buffer,string_length,"draw_lattice(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,\"%s\",%.2f,\"%s\",%.2f,%d,%.2f,%d,%s);",STATIC_CANVAS,line_width,int_data[0],int_data[1],int_data[2],int_data[3],int_data[4],int_data[5],int_data[6],int_data[7],fill_color,fill_opacity,stroke_color,stroke_opacity,use_rotate,angle,use_affine,affine_matrix);
			add_to_buffer(tmp_buffer);
		    break;
		    default:break;
		}
	    }
	    reset();
	    break;
	case SNAPTOGRID:
	/*
	 @ snaptogrid
	 @ keyword (no arguments required)
	 @ in case of userdraw the drawn points will snap to xmajor / ymajor grid
	 @ if you do not want a visible grid, but you only want a 'snaptogrid' with some value...define this grid with opacity 0.
	 @ if xminor / yminor is defined,(use keyword 'axis' to activate the minor steps) the drawing will snap to xminor and yminor<br />use only even dividers in x/y-minor...for example<br />snaptogrid<br />axis<br />grid 2,1,grey,4,4,7,red<br /> will snap on x=0, x=0.5, x=1, x=1.5 ....<br /> will snap on y=0, y=0.25 y=0.5 y=0.75 ...<br />
	*/
	fprintf(js_include_file,"\nx_use_snap_to_grid = 1;y_use_snap_to_grid = 1;");
	break;
	case XSNAPTOGRID:
	/*
	 @ xsnaptogrid
	 @ keyword (no arguments required) 
	 @ in case of userdraw the drawn points will snap to xmajor grid
	 @ if you do not want a visible grid, but you only want a 'snaptogrid' with some value...define this grid with opacity 0.
	 @ if xminor is defined (use keyword 'axis' to activate xminor), the drawing will snap to xminor <br />use only even dividers in x-minor...for example<br />xsnaptogrid<br />axis<br />grid 2,1,grey,4,4,7,red<br /> will snap on x=0, x=0.5, x=1, x=1.5 ....<br /> will snap on y=0, y=0.25 y=0.5 y=0.75 ...<br />
	*/
	fprintf(js_include_file,"\nx_use_snap_to_grid = 1;y_use_snap_to_grid = 0;");
	break;
	case YSNAPTOGRID:
	/*
	 @ ysnaptogrid
	 @ keyword (no arguments required) 
	 @ in case of userdraw the drawn points will snap to ymajor grid
	 @ if you do not want a visible grid, but you only want a 'snaptogrid' with some value...define this grid with opacity 0.
	 @ if yminor is defined (use keyword 'axis' to activate yminor), the drawing will snap to yminor <br />use only even dividers in y-minor...for example<br />ysnaptogrid<br />axis<br />grid 2,1,grey,4,4,7,red<br /> will snap on x=0, x=0.5, x=1, x=1.5 ....<br /> will snap on y=0, y=0.25 y=0.5 y=0.75 ...<br />
	*/
	fprintf(js_include_file,"\nx_use_snap_to_grid = 0;y_use_snap_to_grid = 1;");
	break;
	case USERINPUT:
	/*
	 @ userinput function | textarea | inputfield
	 @ alternative command + argment to keywords "userinput_function","userinput_textarea" and "userinput_xy"
	 @ textarea and inputfield are only usable in combination with some 'userdraw draw_ type'
	 @ function may be used any time (e.g. without userdraw)
	 @ use command "functionlabel some_string" to define the inputfield text : default value "f(x)="
	 @ use command 'strokecolor some_color' to adjust the plot / functionlabel color
	 @ the userinput for the function will be corrected by a simple 'rawmath' implementation...
	*/
	    temp = get_string_argument(infile,1);
	    if(strstr(temp,"function") != 0  || strstr(temp,"curve") != 0  || strstr(temp,"plot") != 0 ){
	     if( js_function[DRAW_JSFUNCTION] != 1 ){
	      add_rawmath(js_include_file);/* add simple rawmath routine to correct user input of function */
	      js_function[DRAW_JSFUNCTION] = 1;
	      if(reply_format == 0){reply_format = 24;}/* read canvas_input values */
	      add_input_jsfunction(js_include_file,canvas_root_id,input_style,function_label,input_cnt,stroke_color,stroke_opacity,line_width,use_dashed,dashtype[0],dashtype[1]);
	      input_cnt++;
	     }
	     else 
	     {
	      /* no need to add DRAW_JSFUNCTION , just call it with the parameters */
	      fprintf(js_include_file,"add_input_jsfunction(%d,\"%s\",\"%s\",%d,\"%s\",\"%.2f\",%d,%d,%d);\n",input_cnt,input_style,function_label,line_width,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1]);
	      input_cnt++;
	     }
	     if( use_js_math == FALSE){/* add this stuff only once...*/
	      add_to_js_math(js_include_file);
	      use_js_math = TRUE;
	     }
	     if( use_js_plot == FALSE){
	      use_js_plot = TRUE;
	      add_jsplot(js_include_file,canvas_root_id); /* this plots the function on JSPLOT_CANVAS */
	     }
	    }
	    else
	    {
	     if(strstr(temp,"inputfield") != 0 ){
	      if( use_input_xy != 0 ){canvas_error("userinput_xy can not be combined with usertextarea_xy command");}
	      if( use_safe_eval == FALSE){use_safe_eval = TRUE;add_safe_eval(js_include_file);} /* just once */
	      use_input_xy = 1;
	     }
	     else
	     {
	      if(strstr(temp,"textarea") != 0 ){
	       if( use_input_xy != 0 ){canvas_error("usertextarea_xy can not be combined with userinput_xy command");}
	       if( use_safe_eval == FALSE){use_safe_eval = TRUE;add_safe_eval(js_include_file);} /* just once */
	       use_input_xy = 2;
	      }
	      else
	      {
	        canvas_error("userinput argument may be \"function,inputfield,textarea\"");
	      }
	     }
	    }
	    break;
	case USERTEXTAREA_XY:
	/*
	@ usertextarea_xy
	@ keyword
	@ to be used in combination with command "userdraw object_type,color" wherein object_type is only segment / polyline for the time being...
	@ if set two textareas are added to the document<br />(one for x-values , one for y-values)
	@ the student may use this as correction for (x:y) on a drawing (or to draw without mouse, using just the coordinates)
	@ user drawings will not zoom on zooming (or pan on panning)
	*/
	    if( use_input_xy != 0 ){canvas_error("usertextarea_xy can not be combined with userinput_xy command");}
	    if( use_safe_eval == FALSE){use_safe_eval = TRUE;add_safe_eval(js_include_file);} /* just once */
	    use_input_xy = 2;
	    break;
	case USERINPUT_XY:
	/*
	@ userinput_xy
	@ keyword
	@ to be used in combination with command "userdraw object_type,color"
	@ if set two (or three) input fields are added to the document<br />(one for x-values , one for y-values and in case of drawing circle one for radius-values)
	@ the student may use this as correction for (x:y) on a drawing (or to draw without mouse, using just the coordinates)
	@ math input is allowed (e.g something like: 1+3,2*6,1/3,sqrt(3), sin(pi/4),10^-2,log(2)...)<br />eval function is 'protected' against code injection.
	@ can not be combined with command "intooltip tiptext" <br />note: the 'tooltip div element' is used for placing inputfields
	@ user drawings will not zoom on zooming (or pan on panning)
	*/
	    /* add simple eval check to avoid code injection with unprotected eval(string) */
	    if( use_input_xy != 0 ){canvas_error("userinput_xy can not be combined with usertextarea_xy command");}
	    if( use_safe_eval == FALSE){use_safe_eval = TRUE;add_safe_eval(js_include_file);} /* just once */
	    use_input_xy = 1;
	    break;
	case FUNCTION_LABEL:
	/*
	 @ functionlabel 'some string'
	 @ default value "f(x)="
	 @ no mathml allowed (just ascii string)
	 @ if needed, use before every command 'userinput function | inputfield | textarea'
	*/
	    function_label = get_string_argument(infile,1);
	    break;
	case USERINPUT_FUNCTION:
	/*
	@ userinput_function
	@ keyword
	@ if set , a inputfield will be added to the page
	@ repeat keyword for more function input fields
	@ the userinput value will be plotted in the canvas
	@ this value may be read with 'read_canvas()'. <br />for do it yourself js-scripters : If this is the first inputfield in the script, it's id is canvas_input0
	@ use before this command 'userinput_function',<br />commands like 'inputstyle some_css' , 'xlabel some_description' , 'opacity int,int' , 'linewidth int' , 'dashed' and 'dashtype int,int' to modify
	@ incompatible with command 'intooltip link_text_or_image' : it uses the tooltip div for adding the inputfield
	*/
	    if( js_function[DRAW_JSFUNCTION] != 1 ){
	     js_function[DRAW_JSFUNCTION] = 1;
	     add_rawmath(js_include_file);
	     if(reply_format == 0){reply_format = 24;}/* read canvas_input values */
	     add_input_jsfunction(js_include_file,canvas_root_id,input_style,function_label,input_cnt,stroke_color,stroke_opacity,line_width,use_dashed,dashtype[0],dashtype[1]);
	     input_cnt++;
	    }
	    else 
	    {
	      /* no need to add DRAW_JSFUNCTION , just call it with the parameters */
	     fprintf(js_include_file,"add_input_jsfunction(%d,\"%s\",\"%s\",%d,\"%s\",\"%.2f\",%d,%d,%d);\n",input_cnt,input_style,function_label,line_width,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1]);
	     input_cnt++;
	    }
	    if( use_js_math == FALSE){/* add this stuff only once...*/
	     add_to_js_math(js_include_file);
	     use_js_math = TRUE;
	    }
	    if( use_js_plot == FALSE){
	     use_js_plot = TRUE;
	     add_jsplot(js_include_file,canvas_root_id); /* this plots the function on JSPLOT_CANVAS */
	    }
	    break;
	case USERDRAW:
	/*
	@ userdraw object_type,color
	@ implemented object_type: <ul><li>point</li><li>points</li><li>crosshair</li><li>crosshairs</li><li>line</li><li>lines</li><li>vline</li><li>vlines</li><li>hline</li><li>hlines</li><li>demiline</li><li>demilines</li><li>segment</li><li>segments</li><li>polyline</li><li>circle</li><li>circles</li><li>arrow</li><li>arrow2 (double arrow)</li><li>arrows</li><li>arrows2 (double arrows)</li><li>triangle</li><li>polygon</li><li>poly[3-9]</li><li>rect</li><li>roundrect</li><li>rects</li><li>roundrects</li><li>freehandline</li><li>freehandlines</li><li>path</li><li>paths</li><li>text</li><li>arc</li><li>arcs</li><li>input<br/>place a single inputfield on 'canvas'<br />use commands 'inputstyle' for css styling: use command 'linewidth' for adjusting the input field size (default 1)</li><li>inputs<br/>place multiple inputfield : placing inputfields on top of each other is not possible</li></ul>
	@ note: mouselisteners are only active if "$status != done " (eg only drawing in an active/non-finished exercise) <br /> to overrule use command/keyword "status" (no arguments required)
	@ note: object_type text: Any string or multiple strings may be placed anywhere on the canvas.<br />while typing the background of every typed char will be lightblue..."backspace / delete / esc" will remove typed text.<br />You will need to hit "enter" to add the text to the array "userdraw_txt()" : lightblue background will disappear<br />Placing the cursor somewhere on a typed text and hitting "delete/backspace/esc" , a confirm will popup asking to delete the selected text.This text will be removed from the "userdraw_txt()" answer array.<br />Use commands 'fontsize' and 'fontfamily' to control the text appearance
	@ note: object_type polygone: Will be finished (the object is closed) when clicked on the first point of the polygone again.
	@ note: all objects will be removed -after a javascript confirm box- when clicked on an object point with middle or right mouse butten (e.g. event.which != 1 : all buttons but left)
	@ use command "filled", "opacity int,int"  and "fillcolor color" to trigger coloured filling of fillable objects
	@ use command "dashed" and/or "dashtype int,int" to trigger dashing
	@ use command "replyformat int" to control / adjust output formatting of javascript function read_canvas();
	@ may be combined with onclick or drag xy  of other components of flyscript objects (although not very usefull...)
	@ may be combined with keyword 'userinput_xy' or
	@ note: when zooming / panning after a drawing, the drawing will NOT be zoomed / panned...this is a "design" flaw and not a feature <br />To avoid trouble do not use zooming / panning together width userdraw.!
	*/
	    if( use_userdraw == TRUE ){ /* only one object type may be drawn*/
		canvas_error("Only one userdraw primitive may be used: read documentation !!");
	    }
	    reply_precision = precision;
	    use_userdraw = TRUE;
	    fprintf(js_include_file,"\n<!-- begin userdraw mouse events -->\nuserdraw_x = new Array();userdraw_y = new Array();userdraw_radius = new Array();var xy_cnt=0;var canvas_userdraw = create_canvas%d(%d,xsize,ysize);var context_userdraw = canvas_userdraw.getContext(\"2d\");var use_dashed = %d;if(use_dashed == 1){if( context_userdraw.setLineDash ){context_userdraw.setLineDash([%d,%d]);}else{if(context_userdraw.mozDash){context_userdraw.mozDash = [%d,%d];};};};if(wims_status != \"done\"){canvas_div.addEventListener(\"mousedown\",user_draw,false);canvas_div.addEventListener(\"mousemove\",user_drag,false);canvas_div.addEventListener(\"touchstart\",user_draw,false);canvas_div.addEventListener(\"touchmove\",user_drag,false);}\n<!-- end userdraw mouse events -->",canvas_root_id,DRAW_CANVAS,use_dashed,dashtype[0],dashtype[1],dashtype[0],dashtype[1]);
	    draw_type = get_string_argument(infile,0);
	    stroke_color = get_color(infile,1);
	    if( strcmp(draw_type,"point") == 0 ){
		if( js_function[DRAW_CIRCLES] != 1 ){ js_function[DRAW_CIRCLES] = 1;}
		if(reply_format == 0 ){reply_format = 8;}
		/* 7 = x1:y1,x2:y2,x3:y3,x4:y4...x_n:y_n in x/y-range */
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 1){
		    add_input_circle(js_include_file,1,1);
		    add_input_xy(js_include_file,canvas_root_id);
		}
		add_js_points(js_include_file,1,draw_type,line_width,line_width,stroke_color,stroke_opacity,1,stroke_color,stroke_opacity,0,1,1);
	    }
	    else
	    if( strcmp(draw_type,"points") == 0 ){
	        if( js_function[DRAW_CIRCLES] != 1 ){ js_function[DRAW_CIRCLES] = 1;}
	        if(reply_format == 0 ){reply_format = 8;}
		/* 7 = x1:y1,x2:y2,x3:y3,x4:y4...x_n:y_n in x/y-range */
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 1){
		    add_input_circle(js_include_file,1,2);
		    add_input_xy(js_include_file,canvas_root_id);
		}
		add_js_points(js_include_file,2,draw_type,line_width,line_width,stroke_color,stroke_opacity,1,stroke_color,stroke_opacity,0,1,1);
	    }
	    else
	    if( strcmp(draw_type,"segment") == 0 ){
		if( js_function[DRAW_CIRCLES] != 1 ){ js_function[DRAW_CIRCLES] = 1;}
		if( js_function[DRAW_SEGMENTS] != 1 ){ js_function[DRAW_SEGMENTS] = 1;}
		if(reply_format == 0){reply_format = 11;}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 1){
		    add_input_segment(js_include_file,1);
		    add_input_x1y1x2y2(js_include_file,canvas_root_id);
		}
		add_js_segments(js_include_file,1,draw_type,line_width,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1]);
	    }
	    else
	    if( strcmp(draw_type,"polyline") == 0 ){
		if( js_function[DRAW_POLYLINE] != 1 ){ js_function[DRAW_POLYLINE] = 1;}
		if(reply_format == 0){reply_format = 23;}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
		if( use_input_xy == 1 ){
		    add_input_polyline(js_include_file);
		    add_input_xy(js_include_file,canvas_root_id);
		}
		add_js_polyline(js_include_file,draw_type,line_width,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1]);
	    }
	    else
	    if( strcmp(draw_type,"segments") == 0 ){
		if( js_function[DRAW_CIRCLES] != 1 ){ js_function[DRAW_CIRCLES] = 1;}
		if( js_function[DRAW_SEGMENTS] != 1 ){ js_function[DRAW_SEGMENTS] = 1;}
		if(reply_format == 0){reply_format = 11;}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 1){
		    add_input_segment(js_include_file,2);
		    add_input_x1y1x2y2(js_include_file,canvas_root_id);
		}
		add_js_segments(js_include_file,2,draw_type,line_width,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1]);
	    }
	    else
	    if( strcmp(draw_type,"circle") == 0 ){
		if( js_function[DRAW_CIRCLES] != 1 ){ js_function[DRAW_CIRCLES] = 1;}
		if(reply_format == 0){reply_format = 10;}
		/* 9 = x1:y1:r1,x2:y2:r2,x3:y3:r3,x4:y4:r3...x_n:y_n:r_n in x/y-range */
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 1){
		    add_input_circle(js_include_file,2,1);
		    add_input_xyr(js_include_file,canvas_root_id);
		}
		add_js_circles(js_include_file,1,draw_type,line_width,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype[0],dashtype[1]);
	    }
	    else
	    if( strcmp(draw_type,"circles") == 0 ){
		if( js_function[DRAW_CIRCLES] != 1 ){ js_function[DRAW_CIRCLES] = 1;}
		if(reply_format == 0){reply_format = 10;}
		/* 9 = x1:y1:r1,x2:y2:r2,x3:y3:r3,x4:y4:r3...x_n:y_n:r_n in x/y-range */
		add_js_circles(js_include_file,2,draw_type,line_width,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 1){
		    add_input_circle(js_include_file,2,2);
		    add_input_xyr(js_include_file,canvas_root_id);
		}
	    }
	    else
	    if(strcmp(draw_type,"crosshair") == 0 ){
		if( js_function[DRAW_CROSSHAIRS] != 1 ){ js_function[DRAW_CROSSHAIRS] = 1;}
		if(reply_format == 0){reply_format = 8;}
		/* 7 = x1:y1,x2:y2,x3:y3,x4:y4...x_n:y_n in x/y-range */
		add_js_crosshairs(js_include_file,1,draw_type,line_width,crosshair_size ,stroke_color,stroke_opacity);
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 1){
		    add_input_crosshair(js_include_file,1);
		    add_input_xy(js_include_file,canvas_root_id);
		}
	    }
	    else
	    if(strcmp(draw_type,"crosshairs") == 0 ){
		if( js_function[DRAW_CROSSHAIRS] != 1 ){ js_function[DRAW_CROSSHAIRS] = 1;}
		if(reply_format == 0){reply_format = 8;}
		/* 7 = x1:y1,x2:y2,x3:y3,x4:y4...x_n:y_n in x/y-range */
		add_js_crosshairs(js_include_file,2,draw_type,line_width,crosshair_size ,stroke_color,stroke_opacity);
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 1){
		    add_input_crosshair(js_include_file,2);
		    add_input_xy(js_include_file,canvas_root_id);
		}
	    }
	    else
	    if(strcmp(draw_type,"freehandline") == 0 ){
		if( js_function[DRAW_PATHS] != 1 ){ js_function[DRAW_PATHS] = 1;}
		if(reply_format == 0){reply_format = 6;}
		add_js_paths(js_include_file,1,draw_type,line_width,0,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if(strcmp(draw_type,"freehandlines") == 0 ){
		if( js_function[DRAW_PATHS] != 1 ){ js_function[DRAW_PATHS] = 1;}
		if(reply_format == 0){reply_format = 6;}
		add_js_paths(js_include_file,2,draw_type,line_width,0,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if(strcmp(draw_type,"path") == 0 ){
		if( js_function[DRAW_PATHS] != 1 ){ js_function[DRAW_PATHS] = 1;}
		if(reply_format == 0){reply_format = 6;}
		add_js_paths(js_include_file,1,draw_type,line_width,1,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if(strcmp(draw_type,"paths") == 0 ){
		if( js_function[DRAW_PATHS] != 1 ){ js_function[DRAW_PATHS] = 1;}
		if(reply_format == 0){reply_format = 6;}
		add_js_paths(js_include_file,2,draw_type,line_width,1,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if(strcmp(draw_type,"arrows") == 0 ){
		if( js_function[DRAW_ARROWS] != 1 ){ js_function[DRAW_ARROWS] = 1;}
		if(reply_format == 0){reply_format = 11;}
		add_js_arrows(js_include_file,2,draw_type,line_width,1,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1],arrow_head);
		if(use_input_xy == 1){
		    add_input_arrow(js_include_file,2);
		    add_input_x1y1x2y2(js_include_file,canvas_root_id);
		}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if(strcmp(draw_type,"arrows2") == 0 ){
		if( js_function[DRAW_ARROWS] != 1 ){ js_function[DRAW_ARROWS] = 1;}
		if(reply_format == 0){reply_format = 11;}
		add_js_arrows(js_include_file,2,draw_type,line_width,2,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1],arrow_head);
		if(use_input_xy == 1){
		    add_input_arrow(js_include_file,1);
		    add_input_x1y1x2y2(js_include_file,canvas_root_id);
		}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if(strcmp(draw_type,"arrow2") == 0 ){
		if( js_function[DRAW_ARROWS] != 1 ){ js_function[DRAW_ARROWS] = 1;}
		if(reply_format == 0){reply_format = 11;}
		add_js_arrows(js_include_file,1,draw_type,line_width,2,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1],arrow_head);
		if(use_input_xy == 1){
		    add_input_arrow(js_include_file,1);
		    add_input_x1y1x2y2(js_include_file,canvas_root_id);
		}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if(strcmp(draw_type,"arrow") == 0 ){
		if( js_function[DRAW_ARROWS] != 1 ){ js_function[DRAW_ARROWS] = 1;}
		if(reply_format == 0){reply_format = 11;}
		add_js_arrows(js_include_file,1,draw_type,line_width,1,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1],arrow_head);
		if(use_input_xy == 1){
		    add_input_arrow(js_include_file,1);
		    add_input_x1y1x2y2(js_include_file,canvas_root_id);
		}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if(strcmp(draw_type,"polygon") == 0){
		if( js_function[DRAW_PATHS] != 1 ){ js_function[DRAW_PATHS] = 1;}
		if(reply_format == 0){reply_format = 2;}
		add_js_poly(js_include_file,-1,draw_type,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){
		  add_textarea_polygon(js_include_file);
		  add_textarea_xy(js_include_file,canvas_root_id);
		}
	    }
	    else
	    if(strncmp(draw_type,"poly",4) == 0){
		if(strlen(draw_type) < 5){canvas_error("use command \"userdraw poly[3-9],color\" eg userdraw poly6,blue");}
		if( js_function[DRAW_PATHS] != 1 ){ js_function[DRAW_PATHS] = 1;}
		if(reply_format == 0){reply_format = 2;}
		add_js_poly(js_include_file,(int) (draw_type[4]-'0'),draw_type,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if(strcmp(draw_type,"triangle") == 0){
		if( js_function[DRAW_PATHS] != 1 ){ js_function[DRAW_PATHS] = 1;}
		if(reply_format == 0){reply_format = 2;}
		add_js_poly(js_include_file,3,draw_type,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"hline") == 0 ){
		if( js_function[DRAW_LINES] != 1 ){ js_function[DRAW_LINES] = 1;}
		if(reply_format == 0){reply_format = 11;}
		add_js_hlines(js_include_file,1,draw_type,line_width,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"hlines") == 0 ){
		if( js_function[DRAW_LINES] != 1 ){ js_function[DRAW_LINES] = 1;}
		if(reply_format == 0){reply_format = 11;}
		add_js_hlines(js_include_file,2,draw_type,line_width,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"vline") == 0 ){
		if( js_function[DRAW_LINES] != 1 ){ js_function[DRAW_LINES] = 1;}
		if(reply_format == 0){reply_format = 11;}
		add_js_hlines(js_include_file,3,draw_type,line_width,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"vlines") == 0 ){
		if( js_function[DRAW_LINES] != 1 ){ js_function[DRAW_LINES] = 1;}
		if(reply_format == 0){reply_format = 11;}
		add_js_hlines(js_include_file,4,draw_type,line_width,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"line") == 0 ){
		if( js_function[DRAW_CIRCLES] != 1 ){ js_function[DRAW_CIRCLES] = 1;}
		if( js_function[DRAW_LINES] != 1 ){ js_function[DRAW_LINES] = 1;}
		if(reply_format == 0){reply_format = 11;}
		add_js_lines(js_include_file,1,draw_type,line_width,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1]);
		if( use_input_xy == 1 ){
		    add_input_line(js_include_file,1);
		    add_input_x1y1x2y2(js_include_file,canvas_root_id);
		}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"lines") == 0 ){
		if( js_function[DRAW_CIRCLES] != 1 ){ js_function[DRAW_CIRCLES] = 1;}
		if( js_function[DRAW_LINES] != 1 ){ js_function[DRAW_LINES] = 1;}
		if(reply_format == 0){reply_format = 11;}
		add_js_lines(js_include_file,2,draw_type,line_width,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1]);
		if( use_input_xy == 1 ){
		    add_input_line(js_include_file,2);
		    add_input_x1y1x2y2(js_include_file,canvas_root_id);
		}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"demilines") == 0 || strcmp(draw_type,"halflines") == 0 ){
		if( js_function[DRAW_CIRCLES] != 1 ){ js_function[DRAW_CIRCLES] = 1;}
		if( js_function[DRAW_DEMILINES] != 1 ){ js_function[DRAW_DEMILINES] = 1;}
		if(reply_format == 0){reply_format = 11;}
		add_js_demilines(js_include_file,2,draw_type,line_width,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1]);
		if( use_input_xy == 1 ){
		    add_input_demiline(js_include_file,2);
		    add_input_x1y1x2y2(js_include_file,canvas_root_id);
		}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"demiline") == 0 || strcmp(draw_type,"halfline") == 0 ){
		if( js_function[DRAW_CIRCLES] != 1 ){ js_function[DRAW_CIRCLES] = 1;}
		if( js_function[DRAW_DEMILINES] != 1 ){ js_function[DRAW_DEMILINES] = 1;}
		if(reply_format == 0){reply_format = 11;}
		add_js_demilines(js_include_file,1,draw_type,line_width,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1]);
		if( use_input_xy == 1 ){
		    add_input_demiline(js_include_file,1);
		    add_input_x1y1x2y2(js_include_file,canvas_root_id);
		}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"rects") == 0){
		if( js_function[DRAW_RECTS] != 1 ){ js_function[DRAW_RECTS] = 1;}
		if(reply_format == 0){reply_format = 2;}
		add_js_rect(js_include_file,2,0,draw_type,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"roundrects") == 0){
		if( js_function[DRAW_ROUNDRECTS] != 1 ){ js_function[DRAW_ROUNDRECTS] = 1;}
		if(reply_format == 0){reply_format = 2;}
		add_js_rect(js_include_file,2,1,draw_type,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"rect") == 0){
		if( js_function[DRAW_RECTS] != 1 ){ js_function[DRAW_RECTS] = 1;}
		if(reply_format == 0){reply_format = 2;}
		add_js_rect(js_include_file,1,0,draw_type,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"roundrect") == 0){
		if( js_function[DRAW_ROUNDRECTS] != 1 ){ js_function[DRAW_ROUNDRECTS] = 1;}
		if(reply_format == 0){reply_format = 2;}
		add_js_rect(js_include_file,1,1,draw_type,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"arcs") == 0){
		if( js_function[DRAW_SEGMENTS] != 1 ){ js_function[DRAW_SEGMENTS] = 1;}
		if(reply_format == 0){reply_format = 25;}
		add_js_arc(js_include_file,canvas_root_id,2,line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"arc") == 0){
		if( js_function[DRAW_SEGMENTS] != 1 ){ js_function[DRAW_SEGMENTS] = 1;}
		if(reply_format == 0){reply_format = 25;}
		add_js_arc(js_include_file,canvas_root_id,1,line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_dashed,dashtype[0],dashtype[1]);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"text") == 0){
		if( js_function[DRAW_TEXTS] != 1 ){ js_function[DRAW_TEXTS] = 1;}
		if(reply_format == 0){reply_format = 17;}
		add_js_text(js_include_file,canvas_root_id,font_size,font_family,font_color,stroke_opacity);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"inputs") == 0){
		if( js_function[DRAW_INPUTS] != 1 ){ js_function[DRAW_INPUTS] = 1;}
		if(reply_format == 0){reply_format = 27;}
		add_js_inputs(js_include_file,canvas_root_id,2,input_cnt,input_style,line_width);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    if( strcmp(draw_type,"input") == 0){
		if( js_function[DRAW_INPUTS] != 1 ){ js_function[DRAW_INPUTS] = 1;}
		if(reply_format == 0){reply_format = 27;}
		add_js_inputs(js_include_file,canvas_root_id,1,input_cnt,input_style,line_width);
		if(use_input_xy == 1){ canvas_error("userinput_xy not yet implemented for this userdraw type !");}
		if(use_input_xy == 2){ canvas_error("usertextarea_xy not yet implemented for this userdraw type !");}
	    }
	    else
	    {
		canvas_error("unknown drawtype or typo? ");
	    }
	    reset();
	break;
	case PLOTSTEPS:
	    /*
	     @ plotsteps a_number
	     @ default 150
	     @ use with care !
	    */
	    plot_steps = (int) (get_real(infile,1));
	    break;
	case FONTSIZE:
	/*
	 @fontsize font_size
	 @default value 12
	*/
	    font_size = (int) (get_real(infile,1));
	    break;
	case FONTCOLOR:
	/*
	 @fontcolor color
	 @color: hexcolor or colorname
	 @default: black
	 @example usage: x/y-axis text
	*/
	    font_color = get_color(infile,1);
	    break;
	case ANIMATE:
	/*
	 @animate type
	 @REMOVED : this should be done with a slider
	 @type may be "point" (nothing else , yet...)
	 @the point is a filled rectangle ; adjust colour with command 'fillcolor colorname/hexnumber'
	 @will animate a point on the next plot/curve command
	 @the curve will not be draw
	 @moves repeatedly from xmin to xmax
	*/
	    if( strstr(get_string(infile,1),"point") != 0 ){animation_type = 15;}else{canvas_error("the only animation type (for now) is \"point\"...");}
	    break;
	case LEVELCURVE:
	/*
	@levelcurve color,expression in x/y,l1,l2,...
	@draws very primitive level curves for expression, with levels l1,l2,l3,...,l_n
	@the quality is <b>not to be compared</b> with the Flydraw levelcurve. <br />(choose flydraw if you want quality...)
	@every individual level curve may be set 'onclick / drag xy' <br />e.g. every single level curve (l1,l2,l3...l_n) has a unique identifier
	@note : the arrays for holding the javascript data are limited in size
	@note : reduce image size if javascript data arrays get overloaded<br />(command 'plotsteps int' will not control the data size of the plot...)
	*/
	    fill_color = get_color(infile,0);
	    char *fun1 = get_string_argument(infile,0);
	    if( strlen(fun1) == 0 ){canvas_error("function is NOT OK !");}
	    i = 0;
	    done = FALSE;
	    while( !done ){
	     double_data[i] = get_real(infile,1);
	     i++;
	    }
	    for(c = 0 ; c < i; c++){
	     fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,16,%s,[%d],[%d],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,eval_levelcurve(xsize,ysize,fun1,xmin,xmax,ymin,ymax,plot_steps,precision,double_data[c]),line_width,line_width,line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
	     click_cnt++;
	    }
	    reset();
	    break;
	case TRACE_JSCURVE:
	/*
	 @trace_jscurve some_math_function
	 @will use a crosshair to trace the jsmath curve
	 @two inputfields will display the current x/y-values (numerical evaluation by javascript)
	 @default labels 'x' and 'y'<br />the commands 'xlabel some_x_axis_name' and 'ylabel some_y_axis_name' will set the label for the input fields
	 @use linewidth,strokecolor,crosshairsize to adjust the corsshair.
	 @the client browser will convert your math function to javascript math.<br />use parenthesis and rawmath : use 2*x in stead of 2x etc etc<br />no check is done on the validity of your function and/or syntax<br />use error console to debug any errors...
	*/
	    if( js_function[DRAW_CROSSHAIRS] != 1 ){ js_function[DRAW_CROSSHAIRS] = 1;}
	    if( js_function[DRAW_LINES] != 1 ){ js_function[DRAW_LINES] = 1;}
	    if( use_js_math == FALSE){
		add_to_js_math(js_include_file);
		use_js_math = TRUE;
	    }
	    add_trace_js_mouse(js_include_file,TRACE_CANVAS,canvas_root_id,stroke_color,get_string(infile,1),font_size,stroke_opacity,line_width,crosshair_size);
	    break;
	case JSMATH:
	/*
	    @jsmath some_math_function
	    @will calculate an y-value from a userinput x-value and draws a crosshair on these coordinates.
	    @default labels 'x' and 'y'<br />the commands 'xlabel some_x_axis_name' and 'ylabel some_y_axis_name' will set the label for the input fields
	    @example: jsmath sin(x^2)
	    @the client browser will convert your math function to javascript math.<br />use parenthesis and rawmath : use 2*x in stead of 2x etc etc<br />no check is done on the validity of your function and/or syntax<br />use error console to debug any errors...
	*/
	    if( js_function[DRAW_CROSSHAIRS] != 1 ){ js_function[DRAW_CROSSHAIRS] = 1;}
	    if( use_js_math == FALSE){
		add_to_js_math(js_include_file);
		use_js_math = TRUE;
	    }
	    add_calc_y(js_include_file,canvas_root_id,get_string(infile,1));
	    break;
	case JSCURVE:
	/*
	 @jscurve color,formula(x)
	 @your function will be plotted by the javascript engine of the client browser.
	 @use only basic math in your curve:<br /> sqrt,^,asin,acos,atan,log,pi,abs,sin,cos,tan,e
	 @use parenthesis and rawmath : use 2*x in stead of 2x ; use 2^(sin(x))...etc etc<br />use error console to debug any errors...
	 @Attention : last "precision" command in the canvasdraw script determines the calculation precision of the javascript curve plot !
	 @no validity check is done by wims.
	 @zooming & panning are implemented :<br />use command 'zoom color' for mouse driven zooming<br />or use keyword 'setlimits' for inputfields setting xmin/xmax, ymin/ymax
	 @use command 'trace_jscurve formula(x)` for tracing
	 @use commmand 'jsmath  formula(x)` for calculating and displaying indiviual points on the curve
	 @can not be set draggable / onclick (yet)
	 @commands plotjump / plotstep are not active for 'jscurve'
	*/
	    stroke_color = get_color(infile,0);
	    if( use_js_math == FALSE){/* add this stuff only once...*/
		add_to_js_math(js_include_file);
		use_js_math = TRUE;
	    }
	    if( use_js_plot == FALSE){
		use_js_plot = TRUE;
		add_jsplot(js_include_file,canvas_root_id); /* this plots the function on JSPLOT_CANVAS */
	    }
	    temp = get_string_argument(infile,1);
	    string_length = snprintf(NULL,0,  "jsplot(%d,\"%s\",%d,\"%s\",%.2f,%d,%d,%d); ",JSPLOT_CANVAS+use_js_plot,temp,line_width,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1]);
	    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
	    snprintf(tmp_buffer,string_length,"jsplot(%d,\"%s\",%d,\"%s\",%.2f,%d,%d,%d); ",JSPLOT_CANVAS+use_js_plot,temp,line_width,stroke_color,stroke_opacity,use_dashed,dashtype[0],dashtype[1]);
	    add_to_buffer(tmp_buffer);
	    use_js_plot++; /* we need to create multiple canvasses, so we may zoom and pan ?? */

	break;
	case CURVE:
	/*
	 @curve color,formula(x)
	 @plot color,formula(x)
	 @use command trange before command curve / plot  (trange -pi,pi)<br />curve color,formula1(t),formula2(t)
	 @use command "precision" to increase the number of digits of the plotted points
	 @use command "plotsteps" to increase / decrease the amount of plotted points (default 150)
	 @may be set draggable / onclick
	*/
	    if( use_parametric == TRUE ){ /* parametric color,fun1(t),fun2(t)*/
		use_parametric = FALSE;
		stroke_color = get_color(infile,0);
		char *fun1 = get_string_argument(infile,0);
		char *fun2 = get_string_argument(infile,1);
	        if( strlen(fun1) == 0 || strlen(fun2) == 0 ){canvas_error("parametric functions are NOT OK !");}
		fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,%d,%s,[%d],[%d],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,animation_type,eval_parametric(xsize,ysize,fun1,fun2,xmin,xmax,ymin,ymax,tmin,tmax,plot_steps,precision),2*line_width,2*line_width,line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
    		click_cnt++;
    	    }
	    else
	    {
		stroke_color = get_color(infile,0);
	        char *fun1 = get_string_argument(infile,1);
		if( strlen(fun1) == 0 ){canvas_error("function is NOT OK !");}
    		fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,%d,%s,[%d],[%d],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%.1f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,animation_type,eval(xsize,ysize,fun1,xmin,xmax,ymin,ymax,plot_steps,precision),line_width,line_width,line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_filled,use_dashed,dashtype[0],dashtype[1],use_rotate,angle,flytext,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
    		click_cnt++;
	    }
	    animation_type = 9;/* reset to curve plotting without animation */
	    reset();
	    break;
	case FLY_TEXT:
	/*
	@ text fontcolor,x,y,font,text_string
	@ font may be described by keywords : giant,huge,normal,small,tiny
	@ use command 'fontsize' to increase base fontsize for these keywords
	@ may be set "onclick" or "drag xy"
	@ backwards compatible with flydraw
	@ unicode supported: text red,0,0,huge,\\u2232
	@ use command 'string' combined with 'fontfamily' for a more fine grained control over html5 canvas text element
	@ Avoid  mixing old flydraw commands 'text' 'textup' with new canvasdraw commands 'string' stringup'<br />If the fontfamily was set completely like "fontfamily italic 24px Ariel".<br />In that case reset 'fontfamily' to something lke 'fontfamily Ariel' before the old flydraw commands.
	*/
	    for(i = 0; i < 5 ;i++){
		switch(i){
		    case 0: stroke_color = get_color(infile,0);break;/* font_color == stroke_color name or hex color */
		    case 1: double_data[0] = get_real(infile,0);break; /* x */
		    case 2: double_data[1] = get_real(infile,0);break; /* y */
		    case 3: fly_font = get_string_argument(infile,0);
			    if(strcmp(fly_font,"giant") == 0){
				font_size = (int)(font_size + 24);
			    }
			    else
			    {
				if(strcmp(fly_font,"huge") == 0){
				    font_size = (int)(font_size + 14);
				}
				else
				{
				    if(strcmp(fly_font,"large") == 0){
					font_size = (int)(font_size + 6);
					}
					else
					{
					    if(strcmp(fly_font,"small") == 0){
						font_size = (int)(font_size - 4);
						if(font_size<0){font_size = 8;}
					}
				    }
				}
			    }
			    break; /* font_size ! */
		    case 4:
			temp = get_string_argument(infile,1);
			decimals = find_number_of_digits(precision);
			fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,14,[%.*f],[%.*f],[30],[30],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[1],line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,0,0,0,0,use_rotate,angle,temp,font_size,"null",use_affine,affine_matrix,slider,slider_cnt);
			click_cnt++;reset();break;
		    default:break;
		}
	    }
	    break;
	case FLY_TEXTUP:
	/*
	 @ textup fontcolor,x,y,font,text_string
	 @ can <b>not</b> be set "onclick" or "drag xy" (because of translaton matrix...mouse incompatible)
	 @ font may be described by keywords : giant,huge,normal,small,tiny
	 @ use command 'fontsize' to increase base fontsize for the keywords
	 @ backwards compatible with flydraw
	 @ unicode supported: textup red,0,0,huge,\\u2232
	 @ use command 'stringup' and 'fontfamily' for a more fine grained control over html5 canvas text element
	 @ Avoid  mixing old flydraw commands 'text' 'textup' with new canvasdraw commands 'string' stringup'<br />If the fontfamily was set completely like "fontfamily italic 24px Ariel".<br />In that case reset 'fontfamily' to something lke 'fontfamily Ariel' before the old flydraw commands.
	*/
	    if( js_function[DRAW_TEXTS] != 1 ){ js_function[DRAW_TEXTS] = 1;}
	    for(i = 0; i<5 ;i++){
		switch(i){
		    case 0: font_color = get_color(infile,0);break;/* name or hex color */
		    case 1: int_data[0] = x2px(get_real(infile,0));break; /* x */
		    case 2: int_data[1] = y2px(get_real(infile,0));break; /* y */
		    case 3: fly_font = get_string_argument(infile,0);
			    if(strcmp(fly_font,"giant") == 0){
				font_size = (int)(font_size + 24);
			    }
			    else
			    {
				if(strcmp(fly_font,"huge") == 0){
				    font_size = (int)(font_size + 14);
				}
				else
				{
				    if(strcmp(fly_font,"large") == 0){
					font_size = (int)(font_size + 6);
					}
					else
					{
					    if(strcmp(fly_font,"small") == 0){
						font_size = (int)(font_size - 4);
						if(font_size<0){font_size = 8;}
					}
				    }
				}
			    }
			    break; /* font_size ! */
		    case 4:
		    decimals = find_number_of_digits(precision);
		    temp = get_string_argument(infile,1);
		    string_length = snprintf(NULL,0,"draw_text(%d,%d,%d,%d,\"%s\",\"%s\",%.2f,90,\"%s\",%d,%.2f,%d,%s);\n",STATIC_CANVAS,int_data[0],int_data[1],font_size,"null",font_color,stroke_opacity,temp,use_rotate,angle,use_affine,affine_matrix);
		    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
		    snprintf(tmp_buffer,string_length,"draw_text(%d,%d,%d,%d,\"%s\",\"%s\",%.2f,90,\"%s\",%d,%.2f,%d,%s);\n",STATIC_CANVAS,int_data[0],int_data[1],font_size,"null",font_color,stroke_opacity,temp,use_rotate,angle,use_affine,affine_matrix);
		    add_to_buffer(tmp_buffer);
		    break;
		    default:break;
		}
	    }
	    reset();
	    break;
	case FONTFAMILY:
	/*
	 @ fontfamily font_description
	 @ set the font family; for browsers that support it
	 @ font_description: Ariel ,Courier, Helvetica etc
	 @ in case commands<br /> 'string color,x,y,the string'<br /> 'stringup color,x,y,rotation,the string'<br />fontfamily can be something like:<br />italic 34px Ariel
	 @ use correct syntax : 'font style' 'font size'px 'fontfamily'
	*/
	    font_family = get_string(infile,1);
	    break;
	case STRINGUP:
	/*
	 @ stringup color,x,y,rotation_degrees,the text string
	 @ can <b>not</b> be set "onclick" or "drag xy" (because of translaton matrix...mouse incompatible)
	 @ unicode supported: stringup red,0,0,45,\\u2232
	 @ use a command like 'fontfamily bold 34px Courier' <br />to set fonts on browser that support font change

	*/
	    if( js_function[DRAW_TEXTS] != 1 ){ js_function[DRAW_TEXTS] = 1;}	/* can not be added to shape library : rotate / mouse issues */
	    for(i=0;i<6;i++){
		switch(i){
		    case 0: font_color = get_color(infile,0);break;/* name or hex color */
		    case 1: int_data[0] = x2px(get_real(infile,0));break; /* x */
		    case 2: int_data[1] = y2px(get_real(infile,0));break; /* y */
		    case 3: double_data[0] = get_real(infile,0);break;/* rotation */
		    case 4: decimals = find_number_of_digits(precision);
			    temp = get_string_argument(infile,1);
			    string_length = snprintf(NULL,0,"draw_text(%d,%d,%d,%d,\"%s\",\"%s\",%.2f,%.2f,\"%s\",%d,%.2f,%d,%s);\n",STATIC_CANVAS,int_data[0],int_data[1],font_size,font_family,font_color,stroke_opacity,double_data[0],temp,use_rotate,angle,use_affine,affine_matrix);
			    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
			    snprintf(tmp_buffer,string_length,"draw_text(%d,%d,%d,%d,\"%s\",\"%s\",%.2f,%.2f,\"%s\",%d,%.2f,%d,%s);\n",STATIC_CANVAS,int_data[0],int_data[1],font_size,font_family,font_color,stroke_opacity,double_data[0],temp,use_rotate,angle,use_affine,affine_matrix);
			    add_to_buffer(tmp_buffer);
			    break;
		    default:break;
		}
	    }
	    reset();
	    break;
	case STRING:
	/*
	 @ string color,x,y,the text string
	 @ may be set "onclick" or "drag xy"
	 @ unicode supported: string red,0,0,\\u2232
	 @ use a command like 'fontfamily italic 24px Ariel' <br />to set fonts on browser that support font change
	*/
	    for(i=0;i<5;i++){
		switch(i){
		    case 0: stroke_color = get_color(infile,0);break;/* name or hex color */
		    case 1: double_data[0] = get_real(infile,0);break; /* x in xrange*/
		    case 2: double_data[1] = get_real(infile,0);break; /* y in yrange*/
		    case 3: decimals = find_number_of_digits(precision);
			temp = get_string_argument(infile,1);
			decimals = find_number_of_digits(precision);
			fprintf(js_include_file,"dragstuff.addShape(new Shape(%d,%d,%d,14,[%.*f],[%.*f],[30],[30],%d,\"%s\",%.2f,\"%s\",%.2f,%d,%d,%d,%d,%d,%f,\"%s\",%d,\"%s\",%d,%s,%d,%d));\n",click_cnt,onclick,drag_type,decimals,double_data[0],decimals,double_data[1],line_width,stroke_color,stroke_opacity,stroke_color,stroke_opacity,0,0,0,0,use_rotate,angle,temp,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt);
			click_cnt++;reset();break;
		    default:break;
		}
	    }
	    break;
	case CENTERSTRING:
	/*
	 @ centerstring color,y-value,the text string
	 @ title color,y-value,the text string
	 @ draw a string centered on the canvas at y = y-value
	 @ can not set "onclick" or "drag xy" (...)
	 @ unicode supported: centerstring red,5,\\u2232
	 @ use a command like 'fontfamily italic 24px Ariel' <br />to set fonts on browser that support font change
	*/
	    if( js_function[DRAW_CENTERSTRING] != 1 ){ js_function[DRAW_CENTERSTRING] = 1;}
	    for(i=0;i<3;i++){
		switch(i){
		    case 0: stroke_color = get_color(infile,0);break;/* name or hex color */
		    case 1: double_data[0] = get_real(infile,0);break; /* y in xrange*/
		    case 2: temp = get_string_argument(infile,1);
			    /* draw_text = function(canvas_type,y,font_family,stroke_color,stroke_opacity,text) */
			    decimals = find_number_of_digits(precision);
			    string_length = snprintf(NULL,0,
			    "draw_centerstring(%d,%.*f,\"%s\",\"%s\",%.2f,\"%s\");\n",canvas_root_id,decimals,double_data[0],font_family,stroke_color,stroke_opacity,temp);
			    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
			    snprintf(tmp_buffer,string_length,"draw_centerstring(%d,%.*f,\"%s\",\"%s\",%.2f,\"%s\");\n",canvas_root_id,decimals,double_data[0],font_family,stroke_color,stroke_opacity,temp);
			    add_to_buffer(tmp_buffer);
			    break;
		    default:break;
		}
	    }
	    break;
	case MATHML:
	/*
	@ mathml x1,y1,x2,y2,mathml_string
	@ mathml will be displayed in a rectangle left top (x1:y1) , right bottom (x2:y2)
	@ can be set onclick <br />(however dragging is not supported)<br />javascript:read_dragdrop(); will return click number of mathml-object
	@ if inputfields are incorporated in mathml (with id's : id='mathml0',id='mathml1',...id='mathml_n')<br />the user_input values will be read by javascript:read_mathml();<br />attention: if after this mathml-input object other user-interactions are included, these will read mathml too using "read_canvas();"
	@ If other inputfields (command input / command textarea) or userdraw is performed, the function read_canvas() will not read mathml. Use some generic function to read it....

	*/
	    if( js_function[DRAW_XML] != 1 ){ js_function[DRAW_XML] = 1;}
	    for(i=0;i<5;i++){
		switch(i){
		    case 0: int_data[0]=x2px(get_real(infile,0));break; /* x in x/y-range coord system -> pixel width */
		    case 1: int_data[1]=y2px(get_real(infile,0));break; /* y in x/y-range coord system  -> pixel height */
		    case 2: int_data[2]=x2px(get_real(infile,0)) - int_data[0];break; /* width in x/y-range coord system -> pixel width */
		    case 3: int_data[3]=y2px(get_real(infile,0)) - int_data[1];break; /* height in x/y-range coord system  -> pixel height */
		    case 4: decimals = find_number_of_digits(precision);
			    if(onclick == 1 ){ onclick = click_cnt;click_cnt++;}
			    temp = get_string(infile,1);
			    if( strstr(temp,"\"") != 0 ){ temp = str_replace(temp,"\"","'"); }
			    string_length = snprintf(NULL,0,"draw_xml(%d,%d,%d,%d,%d,\"%s\",%d);\n",canvas_root_id,int_data[0],int_data[1],int_data[2],int_data[3],temp,onclick);
			    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
			    snprintf(tmp_buffer,string_length,"draw_xml(%d,%d,%d,%d,%d,\"%s\",%d);\n",canvas_root_id,int_data[0],int_data[1],int_data[2],int_data[3],temp,onclick);
			    add_to_buffer(tmp_buffer);
			    /*
			     in case inputs are present , trigger adding the read_mathml()
			     if no other reply_format is defined
			     note: all other reply types will include a reading of elements with id='mathml'+p)
			     */
			    if(strstr(temp,"mathml0") != NULL){
			     if(reply_format == 0 ){reply_format = 16;} /* no other reply type is defined */
			    }
			    break;
		    default:break;
		}
	    }
	    reset();
	    break;
	case HTTP:
	/*
	 @http x1,y1,x2,y2,http://some_adress.com
	 @an active html-page will be displayed in an "iframe" rectangle left top (x1:y1) , right bottom (x2:y2)
	 @do not use interactivity (or mouse) if the mouse needs to be active in the iframe
	 @can not be 'set onclick' or 'drag xy'
	*/
	    if( js_function[DRAW_HTTP] != 1 ){ js_function[DRAW_HTTP] = 1;}
	    for(i=0;i<5;i++){
		switch(i){
		    case 0: int_data[0]=x2px(get_real(infile,0));break; /* x in x/y-range coord system -> pixel width */
		    case 1: int_data[1]=y2px(get_real(infile,0));break; /* y in x/y-range coord system  -> pixel height */
		    case 2: int_data[2]=x2px(get_real(infile,0)) - int_data[0];break; /* width in x/y-range coord system -> pixel width */
		    case 3: int_data[3]=y2px(get_real(infile,0)) - int_data[1];break; /* height in x/y-range coord system  -> pixel height */
		    case 4: decimals = find_number_of_digits(precision);
			    temp = get_string(infile,1);
			    if(strstr(temp,"\"") != 0 ){ temp = str_replace(temp,"\"","'");}
			    string_length = snprintf(NULL,0,"draw_http(%d,%d,%d,%d,%d,\"%s\");\n",canvas_root_id,int_data[0],int_data[1],int_data[2],int_data[3],temp);
			    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
			    snprintf(tmp_buffer,string_length,"draw_http(%d,%d,%d,%d,%d,\"%s\");\n",canvas_root_id,int_data[0],int_data[1],int_data[2],int_data[3],temp);
			    add_to_buffer(tmp_buffer);
		    break;
		}
	    }
	    reset();
	    break;
	case HTML:
	/*
	 @ html x1,y1,x2,y2,html_string
	 @ all tags are allowed
	 @ can be set onclick <br />(dragging not supported)<br />javascript:read_dragdrop(); will return click number of mathml-object
	 @ if inputfields are incorporated  (with id's : id='mathml0',id='mathml1',...id='mathml_n')<br />the user_input values will be read by javascript:read_canvas(); <br />If other inputfields (command input / command textarea) or userdraw is performed, these values will NOT be read as well.

	 note: uses the same code as 'mathml'
	*/
	    break;
	case X_AXIS_STRINGS:
	/*
	 @ xaxis num1:string1:num2:string2:num3:string3:num4:string4:....num_n:string_n
	 @ xaxistext num1:string1:num2:string2:num3:string3:num4:string4:....num_n:string_n
	 @ use these x-axis values in stead of default xmin...xmax
	 @ use command "fontcolor", "fontsize" , "fontfamily" to adjust font <br />defaults: black,12,Ariel
	 @ if the 'x-axis words' are to big amd will overlap, a simple alternating offset will be applied
	 @ example:<br />size 400,400<br />xrange 0,13<br />yrange -100,500<br />axis<br />xaxis 1:january:2:february:3:march:5:may:6:june:7:july:8:august:9:september:10:october:11:november:12:december<br />#'xmajor' steps should be synchronised with numbers eg. "1" in this example<br />grid 1,100,grey,1,4,6,grey
	 @ example:<br />size 400,400<br />xrange -5*pi,5*pi<br />yrange -100,500<br />axis<br />xaxis -4*pi:-4\\u03c0:-3*pi:-3\\u03c0:-2*pi:-2\\u03c0:-1*pi:-\\u03c0:0:0:pi:\\u03c0:2*pi:2\\u03c01:3*pi:3\\u03c0:4*pi:4\\u03c0<br />#'xmajor' steps should be synchronised with numbers eg. "1" in this example<br />grid pi,1,grey,1,3,6,grey
	*/
	    temp = get_string(infile,1);
	    if( strstr(temp,":") != 0 ){ temp = str_replace(temp,":","\",\"");}
	    if( strstr(temp,"pi") != 0 ){ temp = str_replace(temp,"pi","(3.1415927)");}/* we need to replace pi for javascript y-value*/
	    fprintf(js_include_file,"x_strings = [\"%s\"];\n ",temp);
	    use_axis_numbering = 1;
	    break;
	case Y_AXIS_STRINGS:
	/*
	 @ yaxis num1:string1:num2:string2:num3:string3:num4:string4:....num_n:string_n
	 @ yaxistext num1:string1:num2:string2:num3:string3:num4:string4:....num_n:string_n
	 @ use command "fontcolor", "fontsize" , "fontfamily" to adjust font <br />defaults: black,12,Ariel
	 @ use these y-axis values in stead of default ymin...ymax
	 @ example:<br />size 400,400<br />yrange 0,13<br />xrange -100,500<br />axis<br />yaxis 1:january:2:february:3:march:5:may:6:june:7:july:8:august:9:september:10:october:11:november:12:december<br />#'ymajor' steps should be synchronised with numbers eg. "1" in this example<br />grid 100,1,grey,4,1,6,grey
	*/
	    temp = get_string(infile,1);
	    if( strstr(temp,":") != 0 ){ temp = str_replace(temp,":","\",\"");}
	    if( strstr(temp,"pi") != 0 ){ temp = str_replace(temp,"pi","(3.1415927)");}/* we need to replace pi for javascript y-value*/
	    fprintf(js_include_file,"y_strings = [\"%s\"];\n ",temp);
	    use_axis_numbering = 1;
	    break;

	case AXIS_NUMBERING:
	/*
	    @ axisnumbering
	    @ keyword, no arguments required
	*/
	    use_axis_numbering = 1;
	    break;
	case AXIS:
	/*
	    @ axis
	    @ keyword, no arguments required

	*/
	    use_axis = TRUE;
	    break;
	case KILLSLIDER:
	/*
	 @ killslider
	 @ keyword, no arguments required
	 @ ends grouping of object under a preciously defined slider
	*/
	    slider = 0;
	    break;
	case SLIDER:
	/*
	@ slider start_value,end_value,width px,height px,type,label
	@ type: xy,x,y,angle
	@ if a value display is desired, use<br />type:xy display,x display,y display,angle radian,angle degree
	@ is a unit for x / y value display is needed, use commands 'xunit' and / or 'yunit'
	@ use commmand 'slider' before draggable/clickable objects.
	@ a slider will affect all draggable objects after the 'slider' command...<br />and can be used to group translate / rotate several objects...<br />until a next 'slider' or keyword 'killslider'
	@ amount of sliders is not limited.
	@ javascript:read_dragdrop(); will return an array with 'object_number:slider_value'
	@ type=xy: will produce a 2D 'slider' [rectangle width x heigh px] in your web page
	@ every draggable object may have it's own slider (no limit in amount of sliders)
	@ label: some slider text
	@ use fillcolor for slider ball
	@ use strokecolor for slider bar
	@ use fontfamily / fontcolor to set used fonts
	@ use opacity (only fill opacity will be used) to set transparency
	@ the slider canvas will be added to the 'tooltip div' : so incompatible with command tooltip ; setlimits etc
	*/
	    for(i=0; i<6 ; i++){
		switch(i){
		    case 0: double_data[0] = get_real(infile,0);break; /* start value */
		    case 1: double_data[1] = get_real(infile,0);break; /* end value */
		    case 2: int_data[0] = (int)(get_real(infile,0));break; /* width */
		    case 3: int_data[1] = (int)(get_real(infile,0));break; /* height */
		    case 4: temp = get_string_argument(infile,0); /* type : xy,x,y,angle */
		    /* xy display*/
		    if(strstr(temp,"xy")!= 0){
		     slider = 4;
		    }
		    else
		    {
		     if(strstr(temp,"x") != 0){
		      slider = 1;
		     }
		     else
		     {
		      if(strstr(temp,"y") != 0){
		       slider = 2;
		      }
		      else
		      {
		       if(strstr(temp,"angle") != 0){ /* angle diplay radian */
		        slider = 3;
		       }
		       else
		       {
		        canvas_error("slider types may be : x , y , xy , angle");
		       }
		      }
		     }
		    }
		    if(strstr(temp,"display")!=0){
		     use_slider_display = 1; /* show x xy values in canvas window */
		    }
		    else
		    {
		     if(strstr(temp,"degree")!= 0){
		      use_slider_display = 2; /* show angle values in canvas window */
		     }
		     else
		     {
		      if(strstr(temp,"radian")!=0){
		       use_slider_display = 3; /* show radian values in canvas window */
		      }
		     }
		    }
		    if(use_slider_display != 0 && slider_cnt == 0){ /*add just once the display js-code */
		     add_slider_display(js_include_file,canvas_root_id,precision,font_size,font_color,stroke_opacity);
		    }
		    break;
		    case 5: /* some string used for slider description  */
		    slider_cnt++;
		    if(slider == 4){
		     add_xyslider(js_include_file,canvas_root_id,double_data[0],double_data[1],int_data[0],int_data[1],slider,get_string_argument(infile,1),slider_cnt,stroke_color,fill_color,line_width,fill_opacity,font_family,font_color,use_slider_display );
		    }else{
		     add_slider(js_include_file,canvas_root_id,double_data[0],double_data[1],int_data[0],int_data[1],slider,get_string_argument(infile,1),slider_cnt,stroke_color,fill_color,line_width,fill_opacity,font_family,font_color,use_slider_display);
		    }
		    break;
		}
	     }
	    break;
	case SGRAPH:
	/*
	 @ sgraph xstart,ystart,xmajor,ymajor,xminor,yminor,majorgrid_color,minorgrid_color
	 @ primitive implementation of a 'broken scale' graph...
	 @ not very versatile: only usable in combination with userdraw <br />eg no other objects will obey this "coordinate system"<br />if you want to place an object into this coordinate system, be aware that 10% or 20% of xsize and/or ysize is 'lost'.<br />Use these "formulas" to recalculate the virtual coordinates:<br />factor=0.8 in case xstart != xmin (or ystart != ymin)<br />factor=0.9 in case xstart = xmin (or ystart = ymin)<br />px_x_point = ((factor*xsize)/(xmax - xstart))*(x_point - xmax)+xsize<br />x_recalculated = px*(xmax - xmin)/xsize + $xmin<br />px_y_point = -1*factor*y_point*ysize/(ymax - ystart) + ymax*factor*ysize/(ymax - ystart)<br />y_recalculated = ymax - py*(ymax - ymin)/ysize<br />
	 @ example:<br />size 400,400<br />xrange 0,10000<br />yrange 0,100<br />sgraph 9000,50,100,10,4,4,grey,blue<br />userinput_xy<br />linewidth 2<br />userdraw segments,red
	*/
	    if( js_function[DRAW_SGRAPH] != 1 ){ js_function[DRAW_SGRAPH] = 1;}
	    for(i = 0 ; i < 8 ;i++){
	        switch(i){
	    	    case 0:double_data[0] = get_real(infile,0);break;
	    	    case 1:double_data[1] = get_real(infile,0);break;
	    	    case 2:double_data[2] = get_real(infile,0);break;
	    	    case 3:double_data[3] = get_real(infile,0);break;
	    	    case 4:int_data[0] = (int)(get_real(infile,0));break;
	    	    case 5:int_data[1] = (int)(get_real(infile,0));break;
	    	    case 6:stroke_color = get_color(infile,0);break;
	    	    case 7:font_color = get_color(infile,1);
	    	    string_length = snprintf(NULL,0,"xstart = %f;\nystart = %f;\ndraw_sgraph(%d,%d,%f,%f,%d,%d,\"%s\",\"%s\",\"%s\",%f,%d);\n",double_data[0],double_data[1],GRID_CANVAS,precision,double_data[2],double_data[3],int_data[0],int_data[1],stroke_color,font_color,font_family,stroke_opacity,font_size);
	    	    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
	    	    snprintf(tmp_buffer,string_length,"xstart = %f;\nystart = %f;\ndraw_sgraph(%d,%d,%f,%f,%d,%d,\"%s\",\"%s\",\"%s\",%f,%d);\n",double_data[0],double_data[1],GRID_CANVAS,precision,double_data[2],double_data[3],int_data[0],int_data[1],stroke_color,font_color,font_family,stroke_opacity,font_size);
	    	    add_to_buffer(tmp_buffer);
	    	    break;
	    	    default:break;
	        }
	    }
	    /* sgraph(canvas_type,precision,xmajor,ymajor,xminor,yminor,majorcolor,minorcolor,fontfamily,opacity)*/
	    break;
	case GRID:/* xmajor,ymajor,color [,xminor,yminor,tick length (px) ,color]*/
	/*
	 @ grid step_x,step_y,gridcolor
	 @ use command "fontcolor", "fontsize" , "fontfamily" to adjust font <br />defaults: black,12,Ariel
	 @ if keywords "axis" or "axisnumbering" are set, use :<br />grid step_x,step_y,major_color,minor_x,minor_y,tics height in px,axis_color<br />minor x step = step_x / minor_x
	 @ if xmin > 0 and/or ymin > 0 and zooming / panning is not activ: <br /> be aware that the x/y-axis numbering and x/y major/minor tic marks will not be visual <br /> as they are placed under the x-axis and left to the y-axis (in Quadrant II and IV)
	 @ can not be set "onclick" or "drag xy"
	 @ use commands 'xlabel some_string' and/or 'ylabel some_string' to label axis;<br />use command "fontsize" to adjust size (the font family is non-configurable 'italic your_fontsize px Ariel')
	 @ see commands "xaxis" or "xaxistext", "yaxis" or "yaxistext" to set tailormade values on axis (the used font is set by command fontfamily; default '12px Ariel')
	 @ see command "legend" to set a legend for the graph ;<br />use command "fontsize" to adjust size (the font family is non-configurable 'bold your_fontsize px Ariel')
	*/
	    if( js_function[DRAW_YLOGSCALE] == 1 ){canvas_error("only one grid type is allowed...");}
	    if( js_function[DRAW_GRID] != 1 ){ js_function[DRAW_GRID] = 1;}
	    for(i=0;i<4;i++){
		switch(i){
		    case 0:double_data[0] = get_real(infile,0);break;/* xmajor */
		    case 1:double_data[1] = get_real(infile,0);break;/* ymajor */
		    case 2:
		    if( use_axis == TRUE ){
			stroke_color = get_color(infile,0);
			done = FALSE;
			int_data[0] = (int) (get_real(infile,0));/* xminor */
			int_data[1] = (int) (get_real(infile,0));/* yminor */
			int_data[2] = (int) (get_real(infile,0));/* tic_length */
			fill_color = get_color(infile,1); /* used as axis_color*/
		    }
		    else
		    {
			int_data[0] = 1;
			int_data[1] = 1;
			stroke_color = get_color(infile,1);
			fill_color = stroke_color;
		    }
		    if( double_data[0] <= 0 ||  double_data[1] <= 0 ||  int_data[0] <= 0 ||  int_data[1] <= 0 ){canvas_error("major or minor tickt must be positive !");}
		    /* set snap_x snap_y values in pixels */
		    fprintf(js_include_file,"snap_x = %f;snap_y = %f;",double_data[0] / int_data[0],double_data[1] / int_data[1]);
		    string_length = snprintf(NULL,0,  "draw_grid%d(%d,%d,%.2f,%.*f,%.*f,%d,%d,%d,%d,\"%s\",\"%s\",%d,\"%s\",%d,%d,%d,%.2f,%d,%s,%d,%d,%d,\"%s\",%.2f);\n",canvas_root_id,GRID_CANVAS,precision,stroke_opacity,decimals,double_data[0],decimals,double_data[1],int_data[0],int_data[1],int_data[2],line_width,stroke_color,fill_color,font_size,font_family,use_axis,use_axis_numbering,use_rotate,angle,use_affine,affine_matrix,use_dashed,dashtype[0],dashtype[1],font_color,fill_opacity);
		    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
		    snprintf(tmp_buffer,string_length,"draw_grid%d(%d,%d,%.2f,%.*f,%.*f,%d,%d,%d,%d,\"%s\",\"%s\",%d,\"%s\",%d,%d,%d,%.2f,%d,%s,%d,%d,%d,\"%s\",%.2f);\n",canvas_root_id,GRID_CANVAS,precision,stroke_opacity,decimals,double_data[0],decimals,double_data[1],int_data[0],int_data[1],int_data[2],line_width,stroke_color,fill_color,font_size,font_family,use_axis,use_axis_numbering,use_rotate,angle,use_affine,affine_matrix,use_dashed,dashtype[0],dashtype[1],font_color,fill_opacity);
		    add_to_buffer(tmp_buffer);
		    break;
		}
	    }
	    reset();
	    break;
	case OPACITY:
	/*
	@ opacity 0-255,0-255
	@
	*/
	    for(i = 0 ; i<2;i++){
		switch(i){
		    case 0: double_data[0]=(int)(get_real(infile,0));break;
		    case 1: double_data[1]=(int)(get_real(infile,1));break;
		    default: break;
		}
	    }
	    if( double_data[0] < 0 || double_data[0] > 255 || double_data[1] < 0 || double_data[1] > 255  ){ canvas_error("opacity [0 - 255] , [0 - 255]");}/* typo or non-RGB ? */
	    stroke_opacity = (double) (0.0039215*double_data[0]);/* 0.0 - 1.0 */
	    fill_opacity = (double) (0.0039215*double_data[1]);/* 0.0 - 1.0 */
	    break;
	case ROTATE:
	/*
	 @rotate rotation_angle
	 @angle in degrees
	*/
	    use_rotate = TRUE;
	    angle = -1*(get_real(infile,1));/* -1 : to be compatible with Flydraw... */
	    break;
	case KILLAFFINE:
	/*
	@ killaffine
	@ keyword : resets the transformation matrix to 1,0,0,1,0,0
	*/
	    use_affine = FALSE;
	    snprintf(affine_matrix,14,"[1,0,0,1,0,0]");
	    break;
	case AFFINE:
	/*
	 @affine a,b,c,d,tx,ty
	 @ defines a transformation matrix for subsequent objects
	 @ use keyword 'killaffine' to end the transformation
	 @ note 1: only 'draggable' / 'noclick' objects can be transformed.
	 @ note 2: do not use 'onclick' or 'drag xy' with tranformation objects : the mouse coordinates do not get transformed (yet)
	 @ note 3: no matrix operations on the transformation matrix implemented (yet)
	 @ a : Scales the drawings horizontally
	 @ b : Skews the drawings horizontally
	 @ c : Skews the drawings vertically
	 @ d : Scales the drawings vertically
	 @ tx: Moves the drawings horizontally in xrange coordinate system
	 @ ty: Moves the drawings vertically in yrange coordinate system
	 @ the data precision is 2 decimals (printf : %2.f)
	*/
	    for(i = 0 ; i<6;i++){
		switch(i){
		    case 0: double_data[0] = get_real(infile,0);break;
		    case 1: double_data[1] = get_real(infile,0);break;
		    case 2: double_data[2] = get_real(infile,0);break;
		    case 3: double_data[3] = get_real(infile,0);break;
		    case 4: double_data[4] = get_real(infile,0);break;
		    case 5: double_data[5] = get_real(infile,1);
			use_affine = TRUE;
			string_length = snprintf(NULL,0,     "[%.2f,%.2f,%.2f,%.2f,%.2f,%.2f] ",double_data[0],double_data[1],double_data[2],double_data[3],double_data[4]*xsize/(xmax - xmin),-1*double_data[5]*ysize/(ymax - ymin));
		        check_string_length(string_length);affine_matrix = my_newmem(string_length+1);
			snprintf(affine_matrix,string_length,"[%.2f,%.2f,%.2f,%.2f,%.2f,%.2f] ",double_data[0],double_data[1],double_data[2],double_data[3],double_data[4]*xsize/(xmax - xmin),-1*double_data[5]*ysize/(ymax - ymin));
			break;
		    default: break;
		}
	    }
	break;
	case KILLTRANSLATION:
	/*
	 killtranslation
	*/
	    use_affine = FALSE;
	    snprintf(affine_matrix,14,"[1,0,0,1,0,0]");
	    break;
	case TRANSLATION:
	/*
	 @translation tx,ty
	 @will translate the next object tx in xrange and ty in yrange
	 @uase command 'killtranstation' to end the command
	*/
	    for(i = 0 ; i<2;i++){
		switch(i){
		    case 0: double_data[0] = get_real(infile,0);break;
		    case 1: double_data[1] = get_real(infile,1);
			use_affine = TRUE;
			string_length = snprintf(NULL,0, "[1,0,0,1,%.2f,%.2f] ",double_data[0]*xsize/(xmax - xmin),-1*double_data[1]*ysize/(ymax - ymin));
		        check_string_length(string_length);affine_matrix = my_newmem(string_length+1);
			snprintf(affine_matrix,string_length,"[1,0,0,1,%.2f,%.2f] ",double_data[0]*xsize/(xmax - xmin),-1*double_data[1]*ysize/(ymax - ymin));
			break;
		    default: break;
		}
	    }
	break;

	case DASHED:
	/*
	@ keyword "dashed"
	@ next object will be drawn with a dashed line
	@ change dashing scheme by using command "dashtype int,int)
	*/
	    use_dashed = TRUE;
	    break;
	case FILLED:
	/*
	@ keyword "filled"
	@ the next 'fillable' object (only) will be filled
	@ use command "fillcolor color" to set fillcolor
	@ use command "opacity 0-255,0-255" to set stroke and fill-opacity
	@ use command "fill x,y,color" or "floodfill x,y,color" to fill the space around (x;y) with color <br />pixel operation implemented in javascript: use with care !
	*/
	    use_filled = TRUE;
	    break;
	case STYLE:
	/*
	 @highlight color,opacity,linewidth
	 @ NOT IMPLEMENTED
	 @ use command "onclick" : when the object receives a userclick it will increase it's linewidth
	*/
	    break;
	case FILLCOLOR:
	/*
	@ fillcolor colorname or #hex
	@ Set the color for a filled object : mainly used for command 'userdraw obj,stroke_color'
	@ All fillable massive object will have a fillcolor == strokecolor (just to be compatible with flydraw...)
	*/
	    fill_color = get_color(infile,1);
	    break;
	case STROKECOLOR:
	/*
	@ strokecolor colorname or #hex
	@ to be used for commands that do not supply a color argument (like command 'linegraph')
	*/
	    stroke_color = get_color(infile,1);
	    break;
	case BGIMAGE:
	/*
	 @bgimage image_location
	 @use an image as background .<br />(we use the background of 'canvas_div' )
	 @the background image will be resized to match "width = xsize" and "height = ysize"
	*/
	URL = get_string(infile,1);
	fprintf(js_include_file,"<!-- set background image to canvas div -->\ncanvas_div.style.backgroundImage = \"url(%s)\";canvas_div.style.backgroundSize = \"%dpx %dpx\";\n",URL,xsize,ysize);
	    break;
	case BGCOLOR:
	/*
	 @bgcolor colorname or #hex
	 @use this color as background of the "div" containing the canvas(es)
	*/
	/* [255,255,255]*/
	    bgcolor = get_string(infile,1);
	    if(strstr(bgcolor,"#") == NULL){ /* convert colorname -> #ff00ff */
		int found = 0;
	        for( i = 0; i < NUMBER_OF_COLORNAMES ; i++ ){
		    if( strcmp( colors[i].name , bgcolor ) == 0 ){
			bgcolor = colors[i].hex;
			found = 1;
		        break;
	    	    }
		}
		if(found == 0){canvas_error("your bgcolor is not in my rgb.txt data list : use hexcolor...something like #a0ffc4");}
	    }
	    fprintf(js_include_file,"<!-- set background color of canvas div -->\ncanvas_div.style.backgroundColor = \"%s\";canvas_div.style.opacity = %f;\n",bgcolor,fill_opacity);
	    break;
	case COPY:
	/*
	@ copy x,y,x1,y1,x2,y2,[filename URL]
	@ Insert the region from (x1,y1) to (x2,y2) (in pixels) of [filename] to (x,y) in x/y-range
	@ If x1=y1=x2=y2=-1, the whole [filename URL] is copied.
	@ [filename] is the URL of the image
	@ URL is normal URL of network reachable image file location<br />(eg special url for 'classexo' not -yet- implemented)
	@ if command 'drag x/y/xy' is set before command 'copy', the images will be draggable<br />javascript function read_canvas(); will return the x/y coordinate data in xrange/yrange of all -including non draggable- images<br />the command drag is only valuid for the next image<br />draggable / non-draggable images may be mixed
	@ if you want to draw / userdraw  on an "imported" image, make sure it is transparent.<br />for example GNUPlot: set terminal gif transparent

	context.drawImage(img,sx,sy,swidth,sheight,x,y,width,height);
	draw_external_image(canvas_type,URL,sx,sy,swidth,sheight,x,y,width,height,drag_drop){
	*/
	    for(i = 0 ; i<7;i++){
		switch(i){
		    case 0: int_data[0]=x2px(get_real(infile,0));break; /* x left top corner in x/y range  */
		    case 1: int_data[1]=y2px(get_real(infile,0));break; /* y left top corner in x/y range */
		    case 2: int_data[2]=(int)(get_real(infile,0));break;/* x1 in px of external image */
		    case 3: int_data[3]=(int)(get_real(infile,0));break;/* y1 in px of external image */
		    case 4: int_data[4]=(int)(get_real(infile,0));break;/* x2 --> width  */
		    case 5: int_data[5]=(int)(get_real(infile,0)) ;break;/* y2 --> height */
		    case 6: URL = get_string(infile,1);
			    int_data[6] = int_data[4] - int_data[2];/* swidth & width (if not scaling )*/
			    int_data[7] = int_data[5] - int_data[3];/* sheight & height (if not scaling )*/
			    if( drag_type > -1 ){
				if( js_function[DRAG_EXTERNAL_IMAGE] != 1 ){ js_function[DRAG_EXTERNAL_IMAGE] = 1;}
				if(reply_format == 0 ){reply_format = 20;}
				string_length = snprintf(NULL,0,"drag_external_image(\"%s\",%d,%d,%d,%d,%d,%d,%d,%d,%d,%d);\n",URL,int_data[2],int_data[3],int_data[6],int_data[7],int_data[0],int_data[1],int_data[6],int_data[7],ext_img_cnt,1);
				check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
				snprintf(tmp_buffer,string_length,"drag_external_image(\"%s\",%d,%d,%d,%d,%d,%d,%d,%d,%d,%d);\n",URL,int_data[2],int_data[3],int_data[6],int_data[7],int_data[0],int_data[1],int_data[6],int_data[7],ext_img_cnt,1);
				drag_type = -1;
				ext_img_cnt++;
			    }
			    else
			    {
				if( js_function[DRAW_EXTERNAL_IMAGE] != 1 ){ js_function[DRAW_EXTERNAL_IMAGE] = 1;}
				/*
				draw_external_image = function(URL,sx,sy,swidth,sheight,x0,y0,width,height,draggable){\n\
				*/
				string_length = snprintf(NULL,0,"draw_external_image(\"%s\",%d,%d,%d,%d,%d,%d,%d,%d,0);\n",URL,int_data[2],int_data[3],int_data[6],int_data[7],int_data[0],int_data[1],int_data[6],int_data[7]);
				check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
				snprintf(tmp_buffer,string_length,"draw_external_image(\"%s\",%d,%d,%d,%d,%d,%d,%d,%d,0);\n",URL,int_data[2],int_data[3],int_data[6],int_data[7],int_data[0],int_data[1],int_data[6],int_data[7]);
			    }
			    add_to_buffer(tmp_buffer);
			    break;
		    default: break;
		}
	    }
	    reset();
	    break;
/*
context.drawImage(img,sx,sy,swidth,sheight,x,y,width,height);
img 	Specifies the image, canvas, or video element to use
sx 	The x coordinate where to start clipping : x1 = int_data[0]
sy 	The y coordinate where to start clipping : x2 = int_data[1]
swidth 	The width of the clipped image : int_data[2] - int_data[0]
sheight The height of the clipped image : int_data[3] - int_data[1]
x 	The x coordinate where to place the image on the canvas : dx1 = int_data[4]
y 	The y coordinate where to place the image on the canvas : dy1 = int_data[5]
width 	The width of the image to use (stretch or reduce the image) : dx2 - dx1 = int_data[6]
height 	The height of the image to use (stretch or reduce the image) : dy2 - dy1 = int_data[7]
*/
	case COPYRESIZED:
	/*
	@ copyresized x1,y2,x2,y2,dx1,dy1,dx2,dy2,image_file_url
	@ Insert the region from (x1,y1) to (x2,y2) (in pixels) of [ filename], <br />possibly resized,<br />to the region of (dx1,dy1) to (dx2,dy2) in x/y-range
	@ If x1=y1=x2=y2=-1, the whole [filename / URL ] is copied and resized.
	@ URL is normal URL of network reachable image file location<br />(eg special url for 'classexo' not -yet- implemented)
	@ if command 'drag x/y/xy' is set before command 'copy', the images will be draggable<br />javascript function read_canvas(); will return the x/y coordinate data in xrange/yrange of all -including non draggable- images<br />the command drag is only valuid for the next image<br />draggable / non-draggable images may be mixed
	@ if you want to draw / userdraw  on an "imported" image, make sure it is transparent.<br />for example GNUPlot: set terminal gif transparent
	*/
	    for(i = 0 ; i<9;i++){
		switch(i){
		    case 0: int_data[0] = (int)(get_real(infile,0));break; /* x1 */
		    case 1: int_data[1] = (int)(get_real(infile,0));break; /* y1 */
		    case 2: int_data[2] = (int)(get_real(infile,0));break;/* x2 */
		    case 3: int_data[3] = (int)(get_real(infile,0));break;/* y2 */
		    case 4: int_data[4] = x2px(get_real(infile,0));break;/* dx1 */
		    case 5: int_data[5] = y2px(get_real(infile,0));break;/* dy1 */
		    case 6: int_data[6] = x2px(get_real(infile,0));break;/* dx2 */
		    case 7: int_data[7] = y2px(get_real(infile,0));break;/* dy2 */
		    case 8: URL = get_string(infile,1);
			    if( drag_type > -1 ){
				if( js_function[DRAG_EXTERNAL_IMAGE] != 1 ){ js_function[DRAG_EXTERNAL_IMAGE] = 1;}
				if(reply_format == 0 ){reply_format = 20;}
			        string_length = snprintf(NULL,0,"drag_external_image(\"%s\",%d,%d,%d,%d,%d,%d,%d,%d,%d,%d);\n",URL,int_data[0],int_data[1],int_data[2],int_data[3],int_data[4],int_data[5],int_data[6],int_data[7],ext_img_cnt,1);
				check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
				snprintf(tmp_buffer,string_length,"drag_external_image(\"%s\",%d,%d,%d,%d,%d,%d,%d,%d,%d,%d);\n",URL,int_data[0],int_data[1],int_data[2],int_data[3],int_data[4],int_data[5],int_data[6],int_data[7],ext_img_cnt,1);
				drag_type = -1;
				ext_img_cnt++;
			    }
			    else
			    {
				if( js_function[DRAW_EXTERNAL_IMAGE] != 1 ){ js_function[DRAW_EXTERNAL_IMAGE] = 1;}
			        string_length = snprintf(NULL,0,"draw_external_image(\"%s\",%d,%d,%d,%d,%d,%d,%d,%d,0);\n",URL,int_data[0],int_data[1],int_data[2],int_data[3],int_data[4],int_data[5],int_data[6],int_data[7]);
			        check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
			        snprintf(tmp_buffer,string_length,"draw_external_image(\"%s\",%d,%d,%d,%d,%d,%d,%d,%d,0);\n",URL,int_data[0],int_data[1],int_data[2],int_data[3],int_data[4],int_data[5],int_data[6],int_data[7]);
			    }
			    add_to_buffer(tmp_buffer);
		    default: break;
		}
	    }
	    reset();
	    break;
	case CLEARBUTTON:
	/*
	 @clearbutton value
	 @adds a button to clear the userdraw canvas with text 'value'
	 @normally userdraw primitives have the option to use middle/right mouse button on<br /> a point of the object to remove this specific object...this clear button will remove all drawings
	 @uses the tooltip placeholder div element: may not be used with command 'intooltip'
	 @use command 'inputstyle' to style the button...
	*/
	    add_clear_button(js_include_file,canvas_root_id,input_style,get_string(infile,1));
	break;
	case INPUTSTYLE:
	/*
	@ inputstyle style_description
	@ example: inputstyle color:blue;font-weight:bold;font-style:italic;font-size:16pt
	*/
	    input_style = get_string(infile,1);
	    break;
	case INPUT:
	/*
	 @ input x,y,size,editable,value
	 @ to set inputfield "readonly", use editable = 0
	 @ only active inputfields (editable = 1) will be read with read_canvas();
	 @ if "$status=done"  (e.g. in answer.phtml) the inputfield will be clearedand set readonly<br />Override this by keyword 'status'
	 @ may be further controlled by "inputstyle" (inputcss is not yet implemented...)
	 @ if mathml inputfields are present and / or some userdraw is performed, these data will NOT be send as well (javascript:read_canvas();)
	*/
	if( js_function[DRAW_INPUTS] != 1 ){ js_function[DRAW_INPUTS] = 1;}
	    for(i = 0 ; i<5;i++){
		switch(i){
		    case 0: int_data[0]=x2px(get_real(infile,0));break;/* x in px */
		    case 1: int_data[1]=y2px(get_real(infile,0));break;/* y in px */
		    case 2: int_data[2]=abs( (int)(get_real(infile,0)));break; /* size */
		    case 3: if( get_real(infile,1) >0){int_data[3] = 1;}else{int_data[3] = 0;};break; /* readonly */
		    case 4:
			    temp = get_string_argument(infile,1);
			    string_length = snprintf(NULL,0,  "draw_inputs(%d,%d,%d,%d,%d,%d,\"%s\",\"%s\");\n",canvas_root_id,input_cnt,int_data[0],int_data[1],int_data[2],int_data[3],input_style,temp);
			    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
			    snprintf(tmp_buffer,string_length,"draw_inputs(%d,%d,%d,%d,%d,%d,\"%s\",\"%s\");\n",canvas_root_id,input_cnt,int_data[0],int_data[1],int_data[2],int_data[3],input_style,temp);
			    add_to_buffer(tmp_buffer);
			    input_cnt++;break;
		    default: break;
		}
	    }
	    if(reply_format == 0 ){reply_format = 15;}
	    reset();
	    break;
	case TEXTAREA:
	/*
	 @ textarea x,y,cols,rows,readonly,value
	 @ may be further controlled by "inputstyle"
	 @ if "$status=done"  (e.g. in answer.phtml) the inputfield will be clearedand set readonly<br />Override this by keyword 'status'
	 @ if mathml inputfields are present and / or some userdraw is performed, these data will NOT be send as well (javascript:read_canvas();)
	*/
	    if( js_function[DRAW_TEXTAREAS] != 1 ){ js_function[DRAW_TEXTAREAS] = 1;}
	    for(i = 0 ; i<6;i++){
		switch(i){
		    case 0: int_data[0]=x2px(get_real(infile,0));break; /* x in px */
		    case 1: int_data[1]=y2px(get_real(infile,0));break; /* y in px */
		    case 2: int_data[2]=abs( (int)(get_real(infile,0)));break;/* cols */
		    case 3: int_data[3]=abs( (int)(get_real(infile,0)));break;/* rows */
		    case 4: if( get_real(infile,1) >0){int_data[4] = 1;}else{int_data[3] = 0;};break; /* readonly */
		    case 5: temp = get_string_argument(infile,1);
			    string_length = snprintf(NULL,0,  "draw_textareas(%d,%d,%d,%d,%d,%d,%d,\"%s\",\"%s\");\n",canvas_root_id,input_cnt,int_data[0],int_data[1],int_data[2],int_data[3],int_data[4],input_style,temp);
			    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
			    snprintf(tmp_buffer,string_length,"draw_textareas(%d,%d,%d,%d,%d,%d,%d,\"%s\",\"%s\");\n",canvas_root_id,input_cnt,int_data[0],int_data[1],int_data[2],int_data[3],int_data[4],input_style,temp);
			    add_to_buffer(tmp_buffer);
			    input_cnt++;break;
		    default: break;
		}
	    }
	    if(reply_format == 0 ){reply_format = 15;}
	    reset();
	    break;
	case MOUSE_PRECISION:
	/*
	    @ precision int
	    @ 1 = no decimals ; 10 = 1 decimal ; 100 = 2 decimals etc
	    @ may be used / changed before every object
	    @ In case of user interaction (like 'userdraw') this value will be used to determine the amount of decimals in the reply / answer
	*/
	    precision = (int) (get_real(infile,1));
	    if(precision < 1 ){precision = 1;};
	    break;
	case SETLIMITS:
	/*
	    @setlimits
	    @keyword : if set, it will produce 4 inputfields for 'xmin,xmax,ymin,ymax' and an 'ok' button
	    @may be used for inputfield based zooming / panning
	    @use command xlabel / ylabel to change text from xmin to 'xlabel'min etc
	    @note:the input value will not be checked on validity
	*/
	    if( use_safe_eval == FALSE){use_safe_eval = TRUE;add_safe_eval(js_include_file);} /* just once */
	    add_setlimits(js_include_file,canvas_root_id);
	    /* add_setlimits provides 'fprintf(js_include_file,"use_pan_and_zoom = 1;");' */
	    use_pan_and_zoom = TRUE;
	    done = TRUE;
	    break;
	case ZOOM:
	/*
	 @ zoom button_color
	 @ introduce a controlpanel at the lower right corner
	 @ giving six 15x15pixel 'active' rectangle areas<br />(for x,leftarrow,rightarrow,uparrow,downarrow and a '-' and a '+' sign ) for zooming and/or panning of the image
	 @ the 'x' symbol will do a 'location.reload' of the page, and thus reset all canvas drawings.
	 @ choose an appropriate colour, so the small 'x,arrows,-,+' are clearly visible
	 @ command 'opacity' may be used to set stroke_opacity of 'buttons
	 @ NOTE: use command 'zoom' at the end of your script code (the same is true for commanmd 'mouse')
	 @ NOTE: only objects that may be set draggable / clickable will be zoomed / panned
	 @ NOTE: when an object is dragged, zooming / panning will cause the coordinates to be reset to the original position :( <br />e.g. dragging / panning will get lost. (array with 'drag data' is erased)<br />This is a design flaw and not a feature !!
	*/
	    fprintf(js_include_file,"use_pan_and_zoom = 1;");
	    use_pan_and_zoom = TRUE;
	    stroke_color = get_color(infile,1);
	    /* we use BG_CANVAS (0) */
	    add_zoom_buttons(js_include_file,canvas_root_id,stroke_color,stroke_opacity);
	    done = TRUE;
	    break;
	case ONCLICK:
	/*
	 @ onclick
	 @ keyword, no arguments
	 @ if the next object is clicked, it's 'object sequence number' in fly script is returned <br /> by javascript:read_canvas();
	 @ Line based object will show an increase in linewidth<br />Font based objects will show the text in 'bold' when clicked.
	 @ NOTE: not all objects may be set clickable
	*/
	    fprintf(js_include_file,"use_dragdrop_reply = true;");
	    onclick = 1;
	    break;
	case DRAG:
	/*
	 @ drag [x][y][xy]
	 @ the next object will be draggable in x / y / xy direction
	 @ the displacement can be read by 'javascript:read_dragdrop();'
	 @ the precision (default 2 decimals) in the student reply may be set with command 'precision'.<br />Use this 'precision' command before this command 'drag x|y|xy' !
	 @ the answer is  : object_number : Xorg : Yorg : Xnew : Ynew<br />wherein object_number is the place of the draggable object in your script.<br />Only draggable object will have an object_number (e.g things like point,crosshair,line,segment,circle,rect,triangle...etc)
	 @ use keywordd 'snaptogrid' , 'xsnaptogrid' or 'ysnaptogrid' to switch from free to discrete movement
	 @ in case of external images (commands copy / copyresized) the external image can be set draggable ; always xy. <br />The function javascript;read_canvas() will return the xy-coordinates of all images.
	 @ NOTE: in case an object is dragged , zooming or panning will cause the coordinates to be reset to the original position :( <br />e.g. dragging / panning will get lost. (array with 'drag data' is erased)<br />This is a design flaw and not a feature !!
	*/
	    temp = get_string(infile,1);
	    if(strstr(temp,"xy") != NULL ){
		drag_type = 0;
	    }
	    else
	    {
		if(strstr(temp,"x") != NULL ){
		    drag_type = 1;
		}
		else
	        {
	    	    drag_type = 2;
	        }
	    }
	    fprintf(js_include_file,"dragdrop_precision = %d;use_dragdrop_reply = true;",precision);
	    onclick = 2;
	
	    /* if(use_userdraw == TRUE ){canvas_error("\"drag & drop\" may not be combined with \"userdraw\" or \"pan and zoom\" \n");} */
	    break;
	case BLINK:
	/*
	 @ blink time(seconds)
	 @ NOT IMPLEMETED -YET
	*/
	    break;
	case XUNIT:
	/*
	 @ xunit some_unit_for_x-values
	 @ unicode allowed (no html code)
	 @ use together with command mousex
	 @ will display the cursor x-coordinate 'unit'
	*/
	    fprintf(js_include_file,"unit_x = \"%s\";",get_string(infile,1));
	    break;
	case YUNIT:
	/*
	 @ yunit some_unit_for_y-values
	 @ unicode allowed (no html code)
	 @ use together with command mousex
	 @ will display the cursor y-coordinate 'unit'
	*/
	    fprintf(js_include_file,"unit_y = \"%s\";",get_string(infile,1));
	    break;
	case MOUSE_DISPLAY:
	/*
	 @display x|y|xy|degree|radius,color,fontsize
	 @will display the mouse cursor coordinates as x-only,y-only,(x:y),<br />the radius of a circle (this only in case 'userdraw circle(s),color' !!<br />or the angle in degrees ( rhe angle between x-axis;(0:0);(x:y)
	 @use commands 'xunit' and / or 'yunit' to add the units to the mouse values
	 @just like commands 'mouse','mousex','mousey','mouse_degree'...only other name)
	*/
	temp = get_string_argument(infile,0);
	if( strstr(temp,"xy") != NULL ){
	    int_data[0] = 2;
	}else{
	    if( strstr(temp,"y") != NULL ){
		int_data[0] = 1;
	    }else{
		if( strstr(temp,"x") != NULL ){
		    int_data[0] = 0;
		}else{
		    if(strstr(temp,"degree") != NULL){
			int_data[0] = 3;
		    }else{
			if(strstr(temp,"radius") != NULL){
			    int_data[0] = 4;
		        }else{
			    int_data[0] = 2;
			}
		    }
		}
	    }
	}
	stroke_color = get_color(infile,0);
	font_size = (int) (get_real(infile,1));
	tmp_buffer = my_newmem(26);
	snprintf(tmp_buffer,25,"use_mouse_coordinates();\n");add_to_buffer(tmp_buffer);
	add_js_mouse(js_include_file,MOUSE_CANVAS,canvas_root_id,precision,stroke_color,font_size,stroke_opacity,int_data[0]);
	break;
	case MOUSE_DEGREE:
	/*
	 @ mouse_degree color,fontsize
	 @ will display the angle in degrees between x-axis, (0:0) and the cursor (x:y) in 'color' and 'font size'<br /> using default fontfamily Ariel
	 @ The angle is positive in QI and QIII and the angle value is negative in QII and QIV
	 @ NOTE: use command 'mouse' at the end of your script code (the same is true for command 'zoom')

	*/
	    stroke_color = get_color(infile,0);
	    font_size = (int) (get_real(infile,1));
	    tmp_buffer = my_newmem(26);
	    snprintf(tmp_buffer,25,"use_mouse_coordinates();\n");add_to_buffer(tmp_buffer);
	    add_js_mouse(js_include_file,MOUSE_CANVAS,canvas_root_id,precision,stroke_color,font_size,stroke_opacity,3);
	    break;
	case MOUSEX:
	/*
	 @ mousex color,fontsize
	 @ will display the cursor x-coordinate in 'color' and 'font size'<br /> using default fontfamily Ariel
	 @ NOTE: use command 'mouse' at the end of your script code (the same is true for command 'zoom')

	*/
	    stroke_color = get_color(infile,0);
	    font_size = (int) (get_real(infile,1));
	    tmp_buffer = my_newmem(26);
	    snprintf(tmp_buffer,25,"use_mouse_coordinates();\n");add_to_buffer(tmp_buffer);
	    add_js_mouse(js_include_file,MOUSE_CANVAS,canvas_root_id,precision,stroke_color,font_size,stroke_opacity,0);
	    break;
	case MOUSEY:
	/*
	 @ mousey color,fontsize
	 @ will display the cursor y-coordinate in 'color' and 'font size'<br /> using default fontfamily Ariel
	 @ NOTE: use command 'mouse' at the end of your script code (the same is true for command 'zoom')

	*/
	    stroke_color = get_color(infile,0);
	    font_size = (int) (get_real(infile,1));
	    tmp_buffer = my_newmem(26);
	    snprintf(tmp_buffer,25,"use_mouse_coordinates();\n");add_to_buffer(tmp_buffer);
	    add_js_mouse(js_include_file,MOUSE_CANVAS,canvas_root_id,precision,stroke_color,font_size,stroke_opacity,1);
	    break;
	case MOUSE:
	/*
	 @ mouse color,fontsize
	 @ will display the cursor (x:y) coordinates  in 'color' and 'font size'<br /> using default fontfamily Ariel
	 @ NOTE: use command 'mouse' at the end of your script code (the same is true for commanmd 'zoom')

	*/
	    stroke_color = get_color(infile,0);
	    font_size = (int) (get_real(infile,1));
	    tmp_buffer = my_newmem(26);
	    snprintf(tmp_buffer,25,"use_mouse_coordinates();\n");add_to_buffer(tmp_buffer);
	    add_js_mouse(js_include_file,MOUSE_CANVAS,canvas_root_id,precision,stroke_color,font_size,stroke_opacity,2);
	    break;
	case INTOOLTIP:
	    /*
	    @ intooltip link_text
	    @ link_text is a single line (span-element)
	    @ link_text may also be an image URL http://some_server/images/my_image.png
	    @ link_text may contain HTML markup
	    @ the canvas will be displayed in a tooltip on 'link_text'
	    @ the canvas is default transparent: use command 'bgcolor color' to adjust background-color<br />the link test will alos be shown with this bgcolor.
	    */
	    if(use_input_xy != FALSE ){canvas_error("intooltip can not be combined with userinput_xy command");}
	    use_tooltip = TRUE;
	    tooltip_text = get_string(infile,1);
	    if(strstr(tooltip_text,"\"") != 0 ){ tooltip_text = str_replace(tooltip_text,"\"","'"); }
	    break;
	case AUDIO:
	/*
	@ audio x,y,w,h,loop,visible,audiofile location
	@ x,y : left top corner of audio element (in xrange / yrange)
	@ w,y : width and height in pixels
	@ loop : 0 or 1 ( 1 = loop audio fragment)
	@ visible : 0 or 1 (1 = show controls)
	@ audio format may be in *.mp3 or *.ogg
	@ If you are using *.mp3 : be aware that FireFox will not (never) play this ! (Pattented format)
	@ if you are using *.ogg : be aware that Microsoft based systems not support it natively
	@ To avoid problems supply both types (mp3 and ogg) of audiofiles.<br />the program will use both as source tag
	@ example: upload both audio1.ogg and audio1.mp3 to http://server/files/<br />audio 0,0,http://server/files/audio1.mp3<br />svdraw will copy html-tag audio1.mp3 to audio1.ogg<br /> and the browser will play the compatible file (audio1.ogg or audio1.mp3)<br />
	*/
	    if( js_function[DRAW_AUDIO] != 1 ){ js_function[DRAW_AUDIO] = 1;}
	    for(i=0;i<7;i++){
		switch(i){
		    case 0: int_data[0] = x2px(get_real(infile,0)); break; /* x in x/y-range coord system -> pixel */
		    case 1: int_data[1] = y2px(get_real(infile,0)); break; /* y in x/y-range coord system  -> pixel */
		    case 2: int_data[2] = (int) (get_real(infile,0)); break; /* pixel width */
		    case 3: int_data[3] = (int) (get_real(infile,0)); break; /* height pixel height */
		    case 4: int_data[4] = (int) (get_real(infile,0)); if(int_data[4] != TRUE){int_data[4] = FALSE;} break; /* loop boolean */
		    case 5: int_data[5] = (int) (get_real(infile,0)); if(int_data[5] != TRUE){int_data[5] = FALSE;} break; /* visible boolean */
		    case 6:
		    temp = get_string(infile,1);
		    if( strstr(temp,".mp3") != 0 ){ temp = str_replace(temp,".mp3","");}
		    if( strstr(temp,".ogg") != 0 ){ temp = str_replace(temp,".ogg","");}
		    string_length = snprintf(NULL,0,  "draw_audio(%d,%d,%d,%d,%d,%d,%d,\"%s.ogg\",\"%s.mp3\");\n",canvas_root_id,int_data[0],int_data[1],int_data[2],int_data[3],int_data[4],int_data[5],temp,temp);
		    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
		    snprintf(tmp_buffer,string_length,"draw_audio(%d,%d,%d,%d,%d,%d,%d,\"%s.ogg\",\"%s.mp3\");\n",canvas_root_id,int_data[0],int_data[1],int_data[2],int_data[3],int_data[4],int_data[5],temp,temp);
		    add_to_buffer(tmp_buffer);
		    break;
		    default:break;
		}
	    }
	    reset();
	    break;
	case VIDEO:
	/*
	@ video x,y,w,h,videofile location
	@ x,y : left top corner of audio element (in xrange / yrange)
	@ w,y : width and height in pixels
	@ example:<br />wims getfile : video 0,0,120,120,myvideo.mp4
	@ video format may be in *.mp4 (todo:other formats)
	*/
	    if( js_function[DRAW_VIDEO] != 1 ){ js_function[DRAW_VIDEO] = 1;}
	    for(i=0;i<5;i++){
		switch(i){
		    case 0: int_data[0] = x2px(get_real(infile,0)); break; /* x in x/y-range coord system -> pixel */
		    case 1: int_data[1] = y2px(get_real(infile,0)); break; /* y in x/y-range coord system  -> pixel */
		    case 2: int_data[2] = (int) (get_real(infile,0)); break; /* pixel width */
		    case 3: int_data[3] = (int) (get_real(infile,0)); break; /* height pixel height */
		    case 4: temp = get_string(infile,1);
			    string_length = snprintf(NULL,0,  "draw_video(%d,%d,%d,%d,%d,\"%s\");\n",canvas_root_id,int_data[0],int_data[1],int_data[2],int_data[3],temp);
			    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
			    snprintf(tmp_buffer,string_length,"draw_video(%d,%d,%d,%d,%d,\"%s\");\n",canvas_root_id,int_data[0],int_data[1],int_data[2],int_data[3],temp);
			    add_to_buffer(tmp_buffer);
			    break;
		    default:break;
		}
	    }
	    reset();
	    break;
	case HATCHFILL:
	/*
	@ hatchfill x0,y0,dx,dy,color
	@ x0,y0 in xrange / yrange
	@ distances dx,dy in pixels
	*/
	    if( js_function[DRAW_HATCHFILL] != 1 ){ js_function[DRAW_HATCHFILL] = 1;}
	    for(i=0;i<5;i++){
		switch(i){
		    case 0: int_data[0] = x2px(get_real(infile,0)); break; /* x */
		    case 1: int_data[1] = y2px(get_real(infile,0)); break; /* y  */
		    case 2: int_data[2] = (int) (get_real(infile,0)); break; /* dx pixel */
		    case 3: int_data[3] = (int) (get_real(infile,0)); break; /* dy pixel*/
		    case 4: stroke_color = get_color(infile,1);
		    /* draw_hatchfill(ctx,x0,y0,dx,dy,linewidth,color,opacity,xsize,ysize) */
		    string_length = snprintf(NULL,0,  "draw_hatchfill(%d,%d,%d,%d,%d,%d,\"%s\",%.2f,%d,%d);\n",STATIC_CANVAS,int_data[0],int_data[1],int_data[2],int_data[3],line_width,stroke_color,stroke_opacity,xsize,ysize);
		    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
		    snprintf(tmp_buffer,string_length,"draw_hatchfill(%d,%d,%d,%d,%d,%d,\"%s\",%.2f,%d,%d);\n",STATIC_CANVAS,int_data[0],int_data[1],int_data[2],int_data[3],line_width,stroke_color,stroke_opacity,xsize,ysize);
		    add_to_buffer(tmp_buffer);
		    break;
		    default:break;
		}
	    }
	    reset();
	break;
	case DIAMONDFILL:
	/*
	@ diamondfill x0,y0,dx,dy,color
	@ x0,y0 in xrange / yrange
	@ distances dx,dy in pixels
	*/
	    if( js_function[DRAW_DIAMONDFILL] != 1 ){ js_function[DRAW_DIAMONDFILL] = 1;}
	    for(i=0;i<5;i++){
		switch(i){
		    case 0: int_data[0] = x2px(get_real(infile,0)); break; /* x */
		    case 1: int_data[1] = y2px(get_real(infile,0)); break; /* y  */
		    case 2: int_data[2] = (int) (get_real(infile,0)); break; /* dx pixel */
		    case 3: int_data[3] = (int) (get_real(infile,0)); break; /* dy pixel*/
		    case 4: stroke_color = get_color(infile,1);
		    /* draw_hatchfill(ctx,x0,y0,dx,dy,linewidth,color,opacity,xsize,ysize) */
		    string_length = snprintf(NULL,0,  "draw_diamondfill(%d,%d,%d,%d,%d,%d,\"%s\",%.2f,%d,%d);\n",STATIC_CANVAS,int_data[0],int_data[1],int_data[2],int_data[3],line_width,stroke_color,stroke_opacity,xsize,ysize);
		    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
		    snprintf(tmp_buffer,string_length,"draw_diamondfill(%d,%d,%d,%d,%d,%d,\"%s\",%.2f,%d,%d);\n",STATIC_CANVAS,int_data[0],int_data[1],int_data[2],int_data[3],line_width,stroke_color,stroke_opacity,xsize,ysize);
		    add_to_buffer(tmp_buffer);
		    break;
		    default:break;
		}
	    }
	    reset();
	break;
	case GRIDFILL:
	/*
	@ gridfill x0,y0,dx,dy,color
	@ x0,y0 in xrange / yrange
	@ distances dx,dy in pixels
	@ a draggable object may snap_to_grid (using keywords xysnaptogrid,xsnaprogrid, ysnaptogrid)
	@ userdraw object may snap_to_grid
	*/
	    if( js_function[DRAW_GRIDFILL] != 1 ){ js_function[DRAW_GRIDFILL] = 1;}
	    for(i=0;i<5;i++){
		switch(i){
		    case 0: int_data[0] = x2px(get_real(infile,0)); break; /* x */
		    case 1: int_data[1] = y2px(get_real(infile,0)); break; /* y  */
		    case 2: int_data[2] = (int) (get_real(infile,0)); break; /* dx pixel */
		    case 3: int_data[3] = (int) (get_real(infile,0)); break; /* dy pixel*/
		    case 4: stroke_color = get_color(infile,1);
		    string_length = snprintf(NULL,0,  "draw_gridfill(%d,%d,%d,%d,%d,%d,\"%s\",%.2f,%d,%d);\n",STATIC_CANVAS,int_data[0],int_data[1],int_data[2],int_data[3],line_width,stroke_color,stroke_opacity,xsize,ysize);
		    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
		    snprintf(tmp_buffer,string_length,"draw_gridfill(%d,%d,%d,%d,%d,%d,\"%s\",%.2f,%d,%d);\n",STATIC_CANVAS,int_data[0],int_data[1],int_data[2],int_data[3],line_width,stroke_color,stroke_opacity,xsize,ysize);
		    add_to_buffer(tmp_buffer);
		    break;
		    default:break;
		}
	    }
	    reset();
	break;
	case DOTFILL:
	/*
	@ dotfill x0,y0,dx,dy,color
	@ x0,y0 in xrange / yrange
	@ distances dx,dy in pixels
	@ radius of dots is linewidth
	*/
	    if( js_function[DRAW_DOTFILL] != 1 ){ js_function[DRAW_DOTFILL] = 1;}
	    for(i=0;i<5;i++){
		switch(i){
		    case 0: int_data[0] = x2px(get_real(infile,0)); break; /* x */
		    case 1: int_data[1] = y2px(get_real(infile,0)); break; /* y  */
		    case 2: int_data[2] = (int) (get_real(infile,0)); break; /* dx pixel */
		    case 3: int_data[3] = (int) (get_real(infile,0)); break; /* dy pixel*/
		    case 4: stroke_color = get_color(infile,1);
		    /* draw_dotfill(ctx,x0,y0,dx,dy,radius,color,opacity,xsize,ysize) */
		    string_length = snprintf(NULL,0,  "draw_dotfill(%d,%d,%d,%d,%d,%d,\"%s\",%.2f,%d,%d);\n",STATIC_CANVAS,int_data[0],int_data[1],int_data[2],int_data[3],line_width,stroke_color,stroke_opacity,xsize,ysize);
		    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
		    snprintf(tmp_buffer,string_length,"draw_dotfill(%d,%d,%d,%d,%d,%d,\"%s\",%.2f,%d,%d);\n",STATIC_CANVAS,int_data[0],int_data[1],int_data[2],int_data[3],line_width,stroke_color,stroke_opacity,xsize,ysize);
		    add_to_buffer(tmp_buffer);
		    break;
		    default:break;
		}
	    }
	    reset();
	break;
	case IMAGEFILL:
	/*
	@ imagefill dx,dy,image_url
	@ The next suitable <b>filled object</b> will be filled with "image_url" tiled
	@ After pattern filling ,the fill-color should be reset !
	@ wims getins / image from class directory : imagefill 80,80,my_image.gif
	@ normal url : imagefill 80,80,$module_dir/gifs/my_image.gif
	@ normal url : imagefill 80,80,http://adres/a/b/c/my_image.jpg
	@ if dx,dy is larger than the image, the whole image will be background to the next object.
	*/
	    if( js_function[DRAW_IMAGEFILL] != 1 ){ js_function[DRAW_IMAGEFILL] = 1;}
	    for(i=0 ;i < 3 ; i++){
		switch(i){
		    case 0:int_data[0] = (int) (get_real(infile,0));break;
		    case 1:int_data[1] = (int) (get_real(infile,0));break;
		    case 2: URL = get_string_argument(infile,1);
			    string_length = snprintf(NULL,0,  "draw_imagefill(%d,%d,%d,\"%s\",%d,%d);\n",STATIC_CANVAS,int_data[0],int_data[1],URL,xsize,ysize);
			    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
			    snprintf(tmp_buffer,string_length,"draw_imagefill(%d,%d,%d,\"%s\",%d,%d);\n",STATIC_CANVAS,int_data[0],int_data[1],URL,xsize,ysize);
			    add_to_buffer(tmp_buffer);
		    break;
		}
	    }
	    reset();
	break;
	case FILLTOBORDER:
	/*
	@ filltoborder x,y,bordercolor,color
	@ fill the region  of point (x:y) bounded by 'bordercolor' with color 'color'
	@ any other color will not act as border to the bucket fill
	@ use this command  after all boundary objects are declared.
	@ NOTE: filltoborder is a very (client) cpu intensive operation!<br />filling is done pixel by pixel<br/>e.g. image size of 400x400 uses 160000 pixels : each pixel contains 4 data (R,G,B,Opacity) = 640000 data.<br />on every data a few operations / comparisons are done...<br />So have pity on your students CPU..
	*/
	    for(i=0 ;i < 4 ; i++){
		switch(i){
		    case 0:double_data[0] = get_real(infile,0);break;
		    case 1:double_data[1] = get_real(infile,0);break;
		    case 2:bgcolor = get_color(infile,0);break;
		    case 3:fill_color = get_color(infile,1);
			   if(js_function[DRAW_FILLTOBORDER] != 1 ){/* use only once */
				js_function[DRAW_FILLTOBORDER] = 1;
				add_js_filltoborder(js_include_file,canvas_root_id);
			   }
			   decimals = find_number_of_digits(precision);
			   /* we need to set a timeout: the canvas is not yet draw in memory? when floodfill is called directly... */
			   string_length = snprintf(NULL,0,  "setTimeout(function(){filltoborder(%.*f,%.*f,[%s,%d],[%s,%d]);},1000);\n",decimals,double_data[0],decimals,double_data[1],bgcolor,(int) (fill_opacity/0.0039215),fill_color,(int) (fill_opacity/0.0039215));
			   check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
			   snprintf(tmp_buffer,string_length,"setTimeout(function(){filltoborder(%.*f,%.*f,[%s,%d],[%s,%d]);},1000);\n",decimals,double_data[0],decimals,double_data[1],bgcolor,(int) (fill_opacity/0.0039215),fill_color,(int) (fill_opacity/0.0039215));
			   add_to_buffer(tmp_buffer);
			   break;
		    default:break;
		}
	    }
	    reset();
	break;
	case FLOODFILL:
	/*
	@ floodfill x,y,color
	@ alternative syntax: fill x,y,color
	@ fill the region of point (x:y) with color 'color'
	@ any other color or size of picture (borders of picture) will act as border to the bucket fill
	@ use this command  after all boundary objects are declared.
	@ Use command 'clickfill,color' for user click driven flood fill.
	@ NOTE: recognised colour boundaries are in the "drag canvas" e.g. only for objects that can be set draggable / clickable
	@ NOTE: floodfill is a very (client) cpu intensive operation!<br />filling is done pixel by pixel<br/>e.g. image size of 400x400 uses 160000 pixels : each pixel contains 4 data (R,G,B,Opacity) = 640000 data.<br />on every data a few operations / comparisons are done...<br />So have pity on your students CPU..
	*/
	    for(i=0 ;i < 4 ; i++){
		switch(i){
		    case 0:double_data[0] = get_real(infile,0);break;
		    case 1:double_data[1] = get_real(infile,0);break;
		    case 2:fill_color = get_color(infile,1);
			   if(js_function[DRAW_FLOODFILL] != 1 ){/* use only once */
				js_function[DRAW_FLOODFILL] = 1;
				add_js_floodfill(js_include_file,canvas_root_id);
			   }
			   decimals = find_number_of_digits(precision);/*floodfill(interaction,x,y,[R,G,B,A]) */
			   /* we need to set a timeout: the canvas is not yet draw in memory? when floodfill is called directly... */
			   string_length = snprintf(NULL,0,  "setTimeout(function(){floodfill(0,%.*f,%.*f,[%s,%d]);},1000);\n",decimals,double_data[0],decimals,double_data[1],fill_color,(int) (fill_opacity/0.0039215));
			   check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
			   snprintf(tmp_buffer,string_length,"setTimeout(function(){floodfill(0,%.*f,%.*f,[%s,%d]);},1000);\n",decimals,double_data[0],decimals,double_data[1],fill_color,(int) (fill_opacity/0.0039215));
			   add_to_buffer(tmp_buffer);
			   break;
		    default:break;
		}
	    }
	    reset();
	break;
	case CLICKFILLMARGE:
	    clickfillmarge = (int) (get_real(infile,1));
	    break;
	/*
	@ clickfillmarge int
	@ default 20 (pixels)
	@ when using command "clickfill fillcolor" a coloured area my be reverted ("undo") <br />back to background colour with a middle mouse click<br />when the click is in a 40x40 rectangle around a stored m mouseclick (userdraw_x[] and userdraw_y[])
	*/
	case CLICKFILL:
	/*
	@ clickfill fillcolor
	@ user left mouse click will floodfill the area with fillcolor
	@ multiple areas may be coloured
	@ the coloured areas can be removed (changed to "bgcolor") by  middle / right mouse click <br />(if the click is in an 40x40 pixel area of the click coordinate that "painted" the area)
	@ the answer will be read as the (x:y) click coordinates per coloured area
	@ background color of main div may be set by using command "bgcolos color"
	@ may not be combined with command "userdraw"
	@ NOTE: recognised colour boundaries are in the "drag canvas" e.g. only for objects that can be set draggable / clickable
	*/
	 fill_color = get_color(infile,1);
	 if(js_function[DRAW_FLOODFILL] != 1 ){/* use only once */
	    js_function[DRAW_FLOODFILL] = 1;
	    add_js_floodfill(js_include_file,canvas_root_id);
	 }
	 fprintf(js_include_file,"\n<!-- begin command clickfill -->\nvar marge_xy = %d;userdraw_x = new Array();userdraw_y = new Array();var user_clickfill_cnt = 0;\ncanvas_div.addEventListener(\"mousedown\",clickfill,false);function clickfill(evt){var x = evt.clientX - findPosX(canvas_div) + document.body.scrollLeft + document.documentElement.scrollLeft;var y = evt.clientY - findPosY(canvas_div) + document.body.scrollTop + document.documentElement.scrollTop;if(evt.which != 1){for(var p=0; p < user_clickfill_cnt;p++){if(userdraw_x[p] + marge_xy > x && userdraw_x[p] - marge_xy < x){if(userdraw_y[p] + marge_xy > y && userdraw_y[p] - marge_xy < y){if(confirm(\"Clear ?\")){floodfill(1,userdraw_x[p],userdraw_y[p],canvas_div.style.backgroundColor || [255,255,255,0]);userdraw_x.splice(p,2);userdraw_y.splice(p,2);user_clickfill_cnt--;return;};};};};};userdraw_x[user_clickfill_cnt] = x;userdraw_y[user_clickfill_cnt] = y;user_clickfill_cnt++;floodfill(1,x,y,[%s,%d]);};",clickfillmarge,fill_color,(int) (fill_opacity/0.0039215));
	 add_read_canvas(canvas_root_id,1,reply_precision);
	 reset();
	break;
	case SETPIXEL:
	/*
	@ setpixel x,y,color
	@ A "point" with diameter 1 pixel centeres at (x:y) in xrange / yrange
	@ pixels can not be dragged or clicked
	@ "pixelsize = 1" may be changed by command "pixelsize int"
	*/
	    if( js_function[DRAW_PIXELS] != 1 ){ js_function[DRAW_PIXELS] = 1;}
	    for(i=0;i<3;i++){
		switch(i){
		    case 0: double_data[0] = get_real(infile,0); break; /* x */
		    case 1: double_data[1] = get_real(infile,0); break; /* y  */
		    case 2: stroke_color = get_color(infile,1);
			   string_length = snprintf(NULL,0,"draw_setpixel([%f],[%f],\"%s\",%.2f,%d);\n",double_data[0],double_data[1],stroke_color,stroke_opacity,pixelsize);
			   check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
			   snprintf(tmp_buffer,string_length,"draw_setpixel([%f],[%f],\"%s\",%.2f,%d);\n",double_data[0],double_data[1],stroke_color,stroke_opacity,pixelsize);
			   add_to_buffer(tmp_buffer);
			   break;
		    default:break;
		}
	    }
	    reset();
	break;
	case PIXELSIZE:
	/*
	@ pixelsize int
	@ in case you want to deviate from default pixelsize = 1...
	*/
	    pixelsize = (int) get_real(infile,1);
	break;
	case PIXELS:
	/*
	@ pixels color,x1,y1,x2,y2,x3,y3...
	@ Draw  "points" with diameter 1 pixel
	@ pixels can not be dragged or clicked
	@ "pixelsize = 1" may be changed by command "pixelsize int"
	*/
	    if( js_function[DRAW_PIXELS] != 1 ){ js_function[DRAW_PIXELS] = 1;}
	    stroke_color=get_color(infile,0);
	    i=0;
	    c=0;
	    while( ! done ){     /* get next item until EOL*/
		if(i > MAX_INT - 1){canvas_error("to many points in argument: repeat command multiple times to fit");}
		for( c = 0 ; c < 2; c++){
		    if(c == 0 ){
			double_data[i] = get_real(infile,0);
			i++;
		    }
		    else
		    {
			double_data[i] = get_real(infile,1);
			i++;
		    }
		}
	    }
	    decimals = find_number_of_digits(precision);
	    /*  *double_xy2js_array(double xy[],int len,int decimals) */
	    string_length = snprintf(NULL,0,  "draw_setpixel(%s,\"%s\",%.2f,%d);\n",double_xy2js_array(double_data,i,decimals),stroke_color,stroke_opacity,pixelsize);
	    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
	    snprintf(tmp_buffer,string_length,"draw_setpixel(%s,\"%s\",%.2f,%d);\n",double_xy2js_array(double_data,i,decimals),stroke_color,stroke_opacity,pixelsize);
	    add_to_buffer(tmp_buffer);
	    reset();
	    break;
	case REPLYFORMAT:
	/*
	@ replyformat number
	@ use number=-1 to deactivate the js-functions read_canvas() and read_dragdrop()
	@ default values should be fine !
	@ use command 'precision [0,1,10,100,1000,10000...]' before command 'replyformat' to set the desired number of decimals in the student reply / drawing
	@ the last value for 'precision int' will be used to calculate  the reply coordinates, if needed (read_canvas();)
	@ choose<ul><li>1 = x1,x2,x3,x4....x_n<br />y1,y2,y3,y4....y_n<br /><br />x/y in pixels</li><li>2 = x1,x2,x3,x4....x_n<br />  y1,y2,y3,y4....y_n<br /> x/y in xrange / yrange coordinate system<br /></li><li>3 = x1,x2,x3,x4....x_n<br />  y1,y2,y3,y4....y_n<br />  r1,r2,r3,r4....r_n<br />  x/y in pixels <br />  r in pixels</li><li>4 = x1,x2,x3,x4....x_n<br />  y1,y2,y3,y4....y_n<br />  r1,r2,r3,r4....r_n<br />  x/y in xrange / yrange coordinate system<br />  r in pixels</li><li>5 = Ax1,Ax2,Ax3,Ax4....Ax_n<br />  Ay1,Ay2,Ay3,Ay4....Ay_n<br />  Bx1,Bx2,Bx3,Bx4....Bx_n<br />  By1,By2,By3,By4....By_n<br />  Cx1,Cx2,Cx3,Cx4....Cx_n<br />  Cy1,Cy2,Cy3,Cy4....Cy_n<br />  ....<br />  Zx1,Zx2,Zx3,Zx4....Zx_n<br />  Zy1,Zy2,Zy3,Zy4....Zy_n<br />  x/y in pixels<br /></li><li>6 = Ax1,Ax2,Ax3,Ax4....Ax_n<br />  Ay1,Ay2,Ay3,Ay4....Ay_n<br />  Bx1,Bx2,Bx3,Bx4....Bx_n<br />  By1,By2,By3,By4....By_n<br />  Cx1,Cx2,Cx3,Cx4....Cx_n<br />  Cy1,Cy2,Cy3,Cy4....Cy_n<br />  ....<br />  Zx1,Zx2,Zx3,Zx4....Zx_n<br />  Zy1,Zy2,Zy3,Zy4....Zy_n<br />  x/y in xrange / yrange coordinate system<br /></li><li>7 = x1:y1,x2:y2,x3:y3,x4:y4...x_n:y_n<br />  x/y in pixels</li><li>8 = x1:y1,x2:y2,x3:y3,x4:y4...x_n:y_n<br />  x/y in xrange / yrange coordinate system</li><li>9 = x1:y1:r1,x2:y2:r2,x3:y3:r3,x4:y4:r3...x_n:y_n:r_n<br />  x/y in pixels</li><li>10 = x1:y1:r1,x2:y2:r2,x3:y3:r3,x4:y4:r3...x_n:y_n:r_n<br />  x/y in xrange / yrange coordinate system</li><li>11 = Ax1,Ay1,Ax2,Ay2<br />   Bx1,By1,Bx2,By2<br />   Cx1,Cy1,Cx2,Cy2<br />   Dx1,Dy1,Dx2,Dy2<br />   ......<br />   Zx1,Zy1,Zx2,Zy2<br />  x/y in xrange / yrange coordinate system</li><li>12 = Ax1,Ay1,Ax2,Ay2<br />   Bx1,By1,Bx2,By2<br />Cx1,Cy1,Cx2,Cy2<br />   Dx1,Dy1,Dx2,Dy2<br />   ......<br />   Zx1,Zy1,Zx2,Zy2<br />  x/y in pixels</li><li>13 = Ax1:Ay1:Ax2:Ay2,Bx1:By1:Bx2:By2,Cx1:Cy1:Cx2:Cy2,Dx1:Dy1:Dx2:Dy2, ... ,Zx1:Zy1:Zx2:Zy2<br />  x/y in xrange / yrange coordinate system</li><li>14 = Ax1:Ay1:Ax2:Ay2,Bx1:By1:Bx2:By2....Zx1:Zy1:Zx2:Zy2<br />  x/y in pixels</li><li>15 = reply from inputfields,textareas<br />  reply1,reply2,reply3,...,reply_n</li><li>16 = mathml input fields </li><li>17 = read "userdraw text,color" only (x1:y1:text1,x2:y2:text2...x_n:y_n:text_n</li><li>18 = read_canvas() will read all interactive clocks in H1:M1:S1,H2:M2:S2...Hn:Mn:Sn</li><li>19 = read_canvas() will return the object number of marked / clicked object (clock)<br />analogue to (shape library) onclick command </li><li>21 = (x1:y1) (x2:y2) ... (x_n:y_n)<br />verbatim coordinate return</li>22 = returns an array .... reply[0]=x1 reply[1]=y1 reply[2]=x2 reply[3]=y2 ... reply[n-1]=x_n reply[n]=y_n<br />  x/y in xrange / yrange coordinate system</li><li>replyformat 23 : can only be used for drawtype 'polyline'<br />a typical click sequence in drawtype polyline isx1,y1,x2,y2,x2,y2,x3,y3,x3,y3.....,x(n-1),y(n-1),x(n-1),y(n-1),xn,yn --replyformat 23--> x1,y1,x2,y2,x3,y3,.....x(n-1),y(n-1),xn,yn multiple occurences will be filtered out.The reply will be in x-y-range (xreply \\n yreply)</li><li>replyformat 24 = read all inputfield values: even those set 'readonly'</li><li>format 25 = angle1,angle2...angle_n : will return the radius (one or many) of the user drawn circle segment in degrees </li><li>format 26 = rad1,rad2...rad_n : will return the radius (one or many) of the user drawn circle segment in radians </li><li>27 = return (only) userdraw inputfields array: x1:y1:text1,x2:y2:text2...</li><li>28 = x1,y1,r1,x2,y2,r2...x_n,y_n,r_n <br />x / y / r in  xrange / yrange coordinate system: may be used to reinput into command 'circles color,x1,y1,r1,x2,y2,r2...x_n,y_n,r_n'<br /> will not return anything else (e.g. no inputfields , text etc)</li></ul>
	@ note to 'userdraw text,color' : the x / y-values are in pixels ! (this to avoid too lengthy calculations in javascript...)
	*/
	 reply_format = (int) get_real(infile,1);
	 reply_precision = precision;
	break;
	case LEGENDCOLORS:
	/*
	@ legendcolors color1:color2:color3:...:color_n
	@ will be used to colour a legend: use this command after the legend command ! e.g.<br />legend test1:test2:test3<br />legendcolors blue:red:orange<br />
	@ make sure the number of colours match the number of legend items
	@ command 'legend' in case of 'piechart' and 'barchart' will use these colours per default (no need to specify 'legendcolors'
	*/
	    if(legend_cnt == -1){canvas_error("use command \"legend\" before command \"legendcolors\" ! ");}
	    temp = get_string(infile,1);
	    if( strstr( temp,":") != 0 ){ temp = str_replace(temp,":","\",\""); }
	    fprintf(js_include_file,"var legendcolors%d = [\"%s\"];",legend_cnt,temp);
	    break;
	case LEGEND:
	/*
	@ legend string1:string2:string3....string_n
	@ will be used to create a legend for a graph
	@ also see command 'piechart'
	@ will use the same colors per default as used in the graphs : use command 'legendcolors' to override the default
	*/
	    temp = get_string(infile,1);
	    if( strstr( temp,":") != 0 ){ temp = str_replace(temp,":","\",\""); }
	    legend_cnt++; /* attention :starts with -1 : it will be used in piechart etc */
	    fprintf(js_include_file,"var legend%d = [\"%s\"];",legend_cnt,temp);
	    break;
	case XLABEL:
	/*
	@ xlabel some_string
	@ will be used to create a label for the x-axis (label is in quadrant I)
	@ can only be used together with command 'grid'<br />not depending on keywords 'axis' and 'axisnumbering'
	@ font setting: italic Courier, fontsize will be slightly larger (fontsize + 4)
	*/
	    temp = get_string(infile,1);
	    fprintf(js_include_file,"var xaxislabel = \"%s\";",temp);
	    break;
	case YLABEL:
	/*
	@ ylabel some_string
	@ will be used to create a (vertical) label for the y-axis (label is in quadrant I)
	@ can only be used together with command 'grid'<br />not depending on keywords 'axis' and 'axisnumbering'
	@ font setting: italic Courier, fontsize will be slightly larger (fontsize + 4)
	*/
	    temp = get_string(infile,1);
	    fprintf(js_include_file,"var yaxislabel = \"%s\";",temp);
	    break;
	case LINEGRAPH: /* scheme: var linegraph_0 = [ 'stroke_color','line_width','use_dashed' ,'dashtype0','dashtype1','x1','y1',...,'x_n','y_n'];*/
	/*
	@ linegraph x1:y1;x2:y2...x_n:y_n
	@ will plot your data in a graph
	@ may only to be used together with command 'grid'
	@ can be used together with freestyle x-axis/y-axis texts : see commands 'xaxis' and 'yaxis'
	@ use command 'legend' to provide an optional legend in right-top-corner
	@ also see command 'piechart'
	@ multiple linegraphs may be used in a single plot
	@ NOTE: your arguments are not checked by canvasdraw : use your javascript console in case of trouble...
	@ <ul><li>use command 'strokecolor' before command 'linegraph' to set the color of this graph</li><li>use command 'linewidth' before command 'linegraph' to set linewidth of this graph</li><li>use command 'dashed' before command 'linegraph' to set dashing of the graph</li><li>if dashing is set, use command 'dashtype' before command 'linegraph' to set the type of dashing of the graph</li></ul>
	*/
	    temp = get_string(infile,1);
	    if( strstr( temp,":") != 0 ){ temp = str_replace(temp,":","\",\""); }
	    fprintf(js_include_file,"var linegraph_%d = [\"%s\",\"%d\",\"%d\",\"%d\",\"%d\",\"%s\"];",linegraph_cnt,stroke_color,line_width,use_dashed,dashtype[0],dashtype[1],temp);
	    linegraph_cnt++;
	    reset();
	    break;
	case BARCHART:
	/*
	@ barchart x_1:y_1:color_1:x_2:y_2:color_2:...x_n:y_n:color_n
	@ will be used to create a legend for bar graph
	@ may only to be used together with command 'grid'
	@ can be used together with freestyle x-axis/y-axis texts : see commands 'xaxis' and 'yaxis'
	@ use command 'legend' to provide an optional legend in right-top-corner
	@ also see command 'piechart'
	@ NOTE: your arguments are not checked by canvasdraw : use your javascript console in case of trouble...
	*/
	    temp = get_string(infile,1);
	    if( strstr( temp,":" ) != 0 ){ temp = str_replace(temp,":","\",\""); }
	    fprintf(js_include_file,"var barchart_%d = [\"%s\"];",barchart_cnt,temp);
	    barchart_cnt++;
	    reset();
	    break;
	case CLOCK:
	/*
	@ clock x,y,r(px),H,M,S,type hourglass,interactive [ ,H_color,M_color,S_color,background_color,foreground_color ]
	@ use command 'opacity stroke-opacity,fill-opacity' to adjust foreground (stroke) and background (fill) transparency
	@ type hourglass:<br />type = 0 : only segments<br />type = 1 : only numbers<br />type = 2 : numbers and segments
	@ colors are optional: if not defined, default values will be used<br />default colours: clock 0,0,60,4,35,45,1,2,[space]<br />default colours: clock 0,0,60,4,35,45,1,2,,,,,<br />custom colours: clock 0,0,60,4,35,45,1,2,,,,yellow,red<br />custom colours: clock 0,0,60,4,35,45,1,2,white,white,white,black,yellow
	@ if you don't want a seconds hand (or minutes...), just make it invisible by using the background color of the hourglass...
	@ interactive <ul><li>0 : not interactive, just clock(s)</li><li>1 : function read_canvas() will read all active clocks in H:M:S format<br />The active clock(s) can be adjusted by pupils</li><li>2 : function read_canvas() will return the clicked clock <br />(like multiplechoice; first clock in script in nr. 0 )</li></ul>
	@ canvasdraw will not check validity of colornames...the javascript console is your best friend
	@ no combinations with other reply_types allowed, for now
	@ if interactive, 6 buttons per clock will be displayed for adjusting a clock (H+ M+ S+ H- M- S-)<br /> set_clock(clock_id,type,incr) <br />first clock has clock_id=0 ; type : H=1,M=2,S=3 ; incr : increment integer
	@ NOTE: if you need multiple clocks on a webpage, use multiple 'clock' commands in a single script !<br />and <i>not multiple canvas scripts</i> in a single page
	*/
	    if( js_function[DRAW_CLOCK] != 1 ){ js_function[DRAW_CLOCK] = 1;}

	/*    var clock = function(xc,yc,radius,H,M,S,h_color,m_color,s_color,bg_color,fg_color) */
	    for(i=0;i<9;i++){
	     switch(i){
	      case 0: int_data[0] = x2px(get_real(infile,0)); break; /* xc */
	      case 1: int_data[1] = y2px(get_real(infile,0)); break; /* yc */
	      case 2: int_data[2] = get_real(infile,0);break;/* radius in px */
	      case 3: int_data[3] = get_real(infile,0);break;/* hours */
	      case 4: int_data[4] = get_real(infile,0);break;/* minutes */
	      case 5: int_data[5] = get_real(infile,0);break;/* seconds */
	      case 6: int_data[6] = get_real(infile,0);if(int_data[6] < 0 || int_data[6] > 2){canvas_error("hourglass can be 0,1 or 2");}break;/* type hourglass */
	      case 7: int_data[7] = (int)(get_real(infile,0));/* interactive 0,1,2*/
	        switch(int_data[7]){
		    case 0:break;
	    	    case 1:if(clock_cnt == 0){
	    			if( reply_format == 0 ){
	    			     reply_format = 18; /* user sets clock */
	    			    /* string_length = snprintf(NULL,0,"set_clock = function(num,type,diff){var name = eval(\"clocks\"+num);switch(type){case 1:name.H = parseInt(name.H+diff);break;case 2:name.M = parseInt(name.M+diff);break;case 3:name.S = parseInt(name.S+diff);break;default: break;};name = clock(name.xc,name.yc,name.radius,name.H,name.M,name.S,name.type,name.interaction,name.H_color,name.M_color,name.S_color,name.bg_color,name.fg_color);};\n");
	    			     check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
	    			     snprintf(tmp_buffer,string_length,"set_clock = function(num,type,diff){var name = eval(\"clocks\"+num);switch(type){case 1:name.H = parseInt(name.H+diff);break;case 2:name.M = parseInt(name.M+diff);break;case 3:name.S = parseInt(name.S+diff);break;default: break;};name = clock(name.xc,name.yc,name.radius,name.H,name.M,name.S,name.type,name.interaction,name.H_color,name.M_color,name.S_color,name.bg_color,name.fg_color);};\n");
	    			     add_to_buffer(tmp_buffer);
	    			    */
				     fprintf(js_include_file,"set_clock = function(num,type,diff){if(wims_status == \"done\"){return;};var name = eval(\"clocks\"+num);switch(type){case 1:name.H = parseInt(name.H+diff);break;case 2:name.M = parseInt(name.M+diff);break;case 3:name.S = parseInt(name.S+diff);break;default: break;};name = new clock(name.xc,name.yc,name.radius,name.H,name.M,name.S,name.type,name.interaction,name.H_color,name.M_color,name.S_color,name.bg_color,name.fg_color);};\n");
	    			}
				else
				{
				    canvas_error("interactive clock may not be used together with other reply_types...");
			    	}
			     }
			    fprintf(stdout,"<p style=\"text-align:center\"><input style=\"%s\" type=\"button\" onclick=\"javascript:set_clock(%d,1,1)\" value=\"H+\" /><input style=\"%s\" type=\"button\" onclick=\"javascript:set_clock(%d,2,1)\" value=\"M+\" /><input style=\"%s\" type=\"button\" onclick=\"javascript:set_clock(%d,3,1)\" value=\"S+\" /><br /><input style=\"%s\" type=\"button\" onclick=\"javascript:set_clock(%d,1,-1)\" value=\"H&minus;\" /><input style=\"%s\" type=\"button\" onclick=\"javascript:set_clock(%d,2,-1)\" value=\"M&minus;\" /><input style=\"%s\" type=\"button\" onclick=\"javascript:set_clock(%d,3,-1)\" value=\"S&minus;\" /></p>",input_style,clock_cnt,input_style,clock_cnt,input_style,clock_cnt,input_style,clock_cnt,input_style,clock_cnt,input_style,clock_cnt);
		    break;
		    case 2:if( reply_format == 0 ){
				reply_format = 19; /* "onclick */
				fprintf(js_include_file,"\n<!-- begin onclick handler for clocks -->\nvar reply = new Array();\n\ncanvas_div.addEventListener( 'mousedown', user_click,false);\n\nfunction user_click(evt){if(evt.which == 1){var canvas_rect = clock_canvas.getBoundingClientRect();\nvar x = evt.clientX - canvas_rect.left;\nvar y = evt.clientY - canvas_rect.top;\nvar p = 0;\nvar name;\nvar t = true;\nwhile(t){try{name = eval('clocks'+p);\nif( x < name.xc + name.radius && x > name.xc - name.radius ){if( y < name.yc + name.radius && y > name.yc - name.radius ){reply[0] = p;\nname = new clock(name.xc,name.yc,name.radius,name.H,name.M,name.S,name.type,name.interaction,name.H_color,name.M_color,name.S_color,\"lightblue\",name.fg_color);\n};\n}else{clock_ctx.clearRect(name.xc-name.radius,name.yc-name.radius,name.xc+name.radius,name.yc+name.radius);\nname = new clock(name.xc,name.yc,name.radius,name.H,name.M,name.S,name.type,name.interaction,name.H_color,name.M_color,name.S_color,name.bg_color,name.fg_color);\n};\np++;\n}catch(e){t=false;\n};\n};\n};\n};\n\n<!-- end onclick handler for clocks -->\n ");
			    }
			    else
			    {
			    	if( reply_format != 19){
			    	   canvas_error("clickable clock(s) may not be used together with other reply_types...");
			    	 }
			    }
		     break;
		     default: canvas_error("interactive must be set 0,1 or 2");break;
		}
		break;
		case 8:
			if(clock_cnt == 0 ){ /* set opacity's just once .... it should be a argument to clock() , for now it's OK */
			    fprintf(js_include_file,"var clock_bg_opacity = %.2f;var clock_fg_opacity = %.2f;",fill_opacity,stroke_opacity);
			}
			temp = get_string(infile,1);
			if( strstr( temp,",") != 0 ){ temp = str_replace(temp,",","\",\""); }
			if( strlen(temp) < 1 ){temp = ",\"\",\"\",\"\",\"\",\"\"";}
			string_length = snprintf(NULL,0,"var clocks%d = new clock(%d,%d,%d,%d,%d,%d,%d,%d,\"%s\");\n",clock_cnt,int_data[0],int_data[1],int_data[2],int_data[3],int_data[4],int_data[5],int_data[6],int_data[7],temp);
	    		check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
			snprintf(tmp_buffer,string_length,"var clocks%d = new clock(%d,%d,%d,%d,%d,%d,%d,%d,\"%s\");\n",clock_cnt,int_data[0],int_data[1],int_data[2],int_data[3],int_data[4],int_data[5],int_data[6],int_data[7],temp);
			add_to_buffer(tmp_buffer);
			clock_cnt++;
			break;
		default:break;
	     }
	    }
	    break;
	case PIECHART:
	/*
	@ piechart xc,yc,radius,'data+colorlist'
	@ (xc : yc) center of circle diagram in xrange/yrange
	@ radius in pixels
	@ data+color list: a colon separated list of raw data and corresponding colours<br />canvasdraw will not check validity of colornames...<br />in case of trouble look into javascript debugging of your browser
	@ example data+colorlist : 132:red:23565:green:323:black:234324:orange:23434:yellow:2543:white
	@ the number of colors must match the number of data.
	@ use command "opacity 0-255,0-255" to adjust fill_opacity of colours
	@ use command "legend string1:string2:...:string_n" to automatically create a legend <br />using the same colours as pie segments<br />unicode allowed in legend<br />expect javascript trouble if the amount of 'pie-slices', 'pie-colours' 'pie-legend-titles' do not match<br />a javascript console is your best friend...<br />use command 'fontfamily' to set the font of the legend.
	*/
	    if( js_function[DRAW_PIECHART] != 1 ){ js_function[DRAW_PIECHART] = 1;}
	    for(i=0;i<5;i++){
		switch(i){
		    case 0: int_data[0] = x2px(get_real(infile,0)); break; /* x */
		    case 1: int_data[1] = y2px(get_real(infile,0)); break; /* y  */
		    case 2: int_data[2] = (int)(get_real(infile,1));break;/* radius*/
		    case 3: temp = get_string(infile,1);
			    if( strstr( temp, ":" ) != 0 ){ temp = str_replace(temp,":","\",\"");}
			    string_length = snprintf(NULL,0,"draw_piechart(%d,%d,%d,%d,[\"%s\"],%.2f,%d,\"%s\");\n",PIECHART,int_data[0],int_data[1],int_data[2],temp,fill_opacity,legend_cnt,font_family);
			    check_string_length(string_length);tmp_buffer = my_newmem(string_length+1);
			    snprintf(tmp_buffer,string_length,"draw_piechart(%d,%d,%d,%d,[\"%s\"],%.2f,%d,\"%s\");\n",PIECHART,int_data[0],int_data[1],int_data[2],temp,fill_opacity,legend_cnt,font_family);
			    add_to_buffer(tmp_buffer);
			   break;
		    default:break;
		}
	    }
	    reset();
	break;
	case STATUS:
	/*
	@status
	@keyword
	@alernative keyword: nostatus
	@used to override the effects of "status=done" in wims (answer.phtml)
	@affects inputfields / textarea's in canvasimage and all userdraw based commands
	@e.g.: if keyword 'status' is set, the pupil will be able to modify the canvas when the 'wims status variable' is set to 'done'
	*/

	    fprintf(js_include_file,"\nwims_status=\"waiting\";\n");
	    break;
	case XLOGBASE:
	/*
	@ xlogbase number
	@ sets the logbase number for the x-axis
	@ default value 10
	@ use together with commands xlogscale / xylogscale
	*/
	    fprintf(js_include_file,"xlogbase=%d;",(int)(get_real(infile,1)));
	    break;
	case YLOGBASE:
	/*
	@ ylogbase number
	@ sets the logbase number for the y-axis
	@ default value 10
	@ use together with commands ylogscale / xylogscale
	*/
	    fprintf(js_include_file,"ylogbase=%d;",(int)(get_real(infile,1)));
	    break;
	case XLOGSCALE:
	/*
	 @ xlogscale ymajor,yminor,majorcolor,minorcolor
	 @ the x/y-range are set using commands 'xrange xmin,xmax' and 'yrange ymin,ymax'
	 @ ymajor is the major step on the y-axis; yminor is the divisor for the y-step
	 @ the linewidth is set using command 'linewidth int'
	 @ the opacity of major / minor grid lines is set by command 'opacity [0-255],[0-255]'
	 @ default logbase number = 10 ... when needed , set the logbase number with command 'xlogbase number'
	 @ the x/y- axis numbering is triggered by keyword 'axisnumbering'<ul><li>use command 'precision' before 'xlogscale' command to set the precision (decimals) of the axis numbering</li><li>use commands 'xlabel some_text' and/or 'ylabel some_text' for text on axis : use command 'fontsize int' to set the fontsize (default 12px)</li><li>use command 'fontfamily fnt_family_string' to set the fonts for axis-numbering</li><li>use command'fontcolor' to set the colour</li></ul>
	 @ note: the complete canvas will be used for the 'log paper'
	 @ note: userdrawings are done in the log paper, e.g. javascript:read_canvas() will return the real values
	 @ note: command 'mouse color,fontsize' will show the real values in the logpaper.<br />\
	 @ note: when using something like 'xrange 0.0001,0.01'...combined with commands 'mouse color,fontsize' and/or 'userdraw type,color'...<br /> make sure the precision is set accordingly (eg command 'precision 10000')
	 @ note: in case of userdraw , the use of keyword 'userinput_xy' may be handy !
	 @ attention: keyword 'snaptogrid' may not lead to the desired result...
	*/
	    if( js_function[DRAW_GRID] == 1 ){canvas_error("only one type of grid is allowed...");}
	    if( js_function[DRAW_XLOGSCALE] != 1 ){ js_function[DRAW_XLOGSCALE] = 1;}
	    for(i=0;i<4;i++){
		switch(i){
		    case 0: double_data[0] = get_real(infile,0);break; /* xmajor */
		    case 1: int_data[0] = (int) (get_real(infile,0));break; /* xminor */
		    case 2: stroke_color = get_color(infile,0); break;
		    case 3: fill_color = get_color(infile,1);
			string_length = snprintf(NULL,0,"draw_grid%d(%d,%d,\"%s\",\"%s\",%.2f,%.2f,%d,\"%s\",\"%s\",%d,%f,%d,%d); ",canvas_root_id,GRID_CANVAS,line_width,stroke_color,fill_color,stroke_opacity,fill_opacity,font_size,font_family,font_color,use_axis_numbering,double_data[0],int_data[0],precision);
			tmp_buffer = my_newmem(string_length+1);
		        snprintf(tmp_buffer,string_length,"draw_grid%d(%d,%d,\"%s\",\"%s\",%.2f,%.2f,%d,\"%s\",\"%s\",%d,%f,%d,%d); ",canvas_root_id,GRID_CANVAS,line_width,stroke_color,fill_color,stroke_opacity,fill_opacity,font_size,font_family,font_color,use_axis_numbering,double_data[0],int_data[0],precision);
		        fprintf(js_include_file,"use_xlogscale=1;snap_y = %f;snap_x = xlogbase;",double_data[0]/int_data[0]);
			add_to_buffer(tmp_buffer);
		        break;
		    default:break;
		}
	    }
	    break;
	case YLOGSCALE:
	/*
	 @ ylogscale xmajor,xminor,majorcolor,minorcolor
	 @ the x/y-range are set using commands 'xrange xmin,xmax' and 'yrange ymin,ymax'
	 @ xmajor is the major step on the x-axis; xminor is the divisor for the x-step
	 @ the linewidth is set using command 'linewidth int'
	 @ the opacity of major / minor grid lines is set by command 'opacity [0-255],[0-255]'
	 @ default logbase number = 10 ... when needed , set the logbase number with command 'ylogbase number'
	 @ the x/y- axis numbering is triggered by keyword 'axisnumbering'<ul><li>use command 'precision' before 'ylogscale' command to set the precision (decimals) of the axis numbering</li><li>use commands 'xlabel some_text' and/or 'ylabel some_text' for text on axis : use command 'fontsize int' to set the fontsize (default 12px)</li><li>use command 'fontfamily fnt_family_string' to set the fonts for axis-numbering</li><li>use command'fontcolor' to set the colour</li></ul>
	 @ note: the complete canvas will be used for the 'log paper'
	 @ note: userdrawings are done in the log paper, e.g. javascript:read_canvas() will return the real values
	 @ note: command 'mouse color,fontsize' will show the real values in the logpaper.<br />\
	 @ note: when using something like 'yrange 0.0001,0.01'...combined with commands 'mouse color,fontsize' and/or 'userdraw type,color'...<br /> make sure the precision is set accordingly (eg command 'precision 10000')
	 @ note: in case of userdraw , the use of keyword 'userinput_xy' may be handy !
	 @ attention: keyword 'snaptogrid' may not lead to the desired result...
	*/
	    if( js_function[DRAW_GRID] == 1 ){canvas_error("only one type of grid is allowed...");}
	    if( js_function[DRAW_YLOGSCALE] != 1 ){ js_function[DRAW_YLOGSCALE] = 1;}
	    for(i=0;i<4;i++){
		switch(i){
		    case 0: double_data[0] = get_real(infile,0);break; /* xmajor */
		    case 1: int_data[0] = (int) (get_real(infile,0));break; /* xminor */
		    case 2: stroke_color = get_color(infile,0); break;
		    case 3: fill_color = get_color(infile,1);
			string_length = snprintf(NULL,0,"draw_grid%d(%d,%d,\"%s\",\"%s\",%.2f,%.2f,%d,\"%s\",\"%s\",%d,%f,%d,%d); ",canvas_root_id,GRID_CANVAS,line_width,stroke_color,fill_color,stroke_opacity,fill_opacity,font_size,font_family,font_color,use_axis_numbering,double_data[0],int_data[0],precision);
			tmp_buffer = my_newmem(string_length+1);
		        snprintf(tmp_buffer,string_length,"draw_grid%d(%d,%d,\"%s\",\"%s\",%.2f,%.2f,%d,\"%s\",\"%s\",%d,%f,%d,%d); ",canvas_root_id,GRID_CANVAS,line_width,stroke_color,fill_color,stroke_opacity,fill_opacity,font_size,font_family,font_color,use_axis_numbering,double_data[0],int_data[0],precision);
		        fprintf(js_include_file,"use_ylogscale=1;snap_x = %f;snap_y = ylogbase;",double_data[0]/int_data[0]);
			add_to_buffer(tmp_buffer);
		        break;
		    default:break;
		}
	    }
	    break;
	case XYLOGSCALE:
	/*
	 @ xylogscale majorcolor,minorcolor
	 @ the x/y-range are set using commands 'xrange xmin,xmax' and 'yrange ymin,ymax'
	 @ the linewidth is set using command 'linewidth int'
	 @ the opacity of major / minor grid lines is set by command 'opacity [0-255],[0-255]'
	 @ default logbase number = 10 ... when needed , set the logbase number with command 'xlogbase number' and/or 'ylogbase number'
	 @ the x/y- axis numbering is triggered by keyword 'axisnumbering'<ul><li>use commands 'xlabel some_text' and/or 'ylabel some_text' for text on axis : use command 'fontsize int' to set the fontsize (default 12px)</li><li>use command 'fontfamily fnt_family_string' to set the fonts for axis-numbering</li><li>use command'fontcolor' to set the colour</li></ul>
	 @ note: the complete canvas will be used for the 'log paper'
	 @ note: userdrawings are done in the log paper, e.g. javascript:read_canvas() will return the real values
	 @ note: command 'mouse color,fontsize' will show the real values in the logpaper.<br />\
	 @ note: when using something like 'yrange 0.0001,0.01'...combined with commands 'mouse color,fontsize' and/or 'userdraw type,color'...<br /> make sure the precision is set accordingly (eg command 'precision 10000')
	 @ note: in case of userdraw , the use of keyword 'userinput_xy' may be handy !
	 @ attention: keyword 'snaptogrid' may not lead to the desired result...
	*/
	    if( js_function[DRAW_GRID] == 1 ){canvas_error("only one type of grid is allowed...");}
	    if( js_function[DRAW_XYLOGSCALE] != 1 ){ js_function[DRAW_XYLOGSCALE] = 1;}
	    for(i=0;i<2;i++){
		switch(i){
		    case 0: stroke_color = get_color(infile,0); break;
		    case 1: fill_color = get_color(infile,1);
			string_length = snprintf(NULL,0,"draw_grid%d(%d,%d,\"%s\",\"%s\",%.2f,%.2f,%d,\"%s\",\"%s\",%d,%d); ",canvas_root_id,GRID_CANVAS,line_width,stroke_color,fill_color,stroke_opacity,fill_opacity,font_size,font_family,font_color,use_axis_numbering,precision);
			tmp_buffer = my_newmem(string_length+1);
		        snprintf(tmp_buffer,string_length,"draw_grid%d(%d,%d,\"%s\",\"%s\",%.2f,%.2f,%d,\"%s\",\"%s\",%d,%d); ",canvas_root_id,GRID_CANVAS,line_width,stroke_color,fill_color,stroke_opacity,fill_opacity,font_size,font_family,font_color,use_axis_numbering,precision);
		        fprintf(js_include_file,"use_xlogscale=1;use_ylogscale=1;snap_x = xlogbase;snap_y = ylogbase;");
			add_to_buffer(tmp_buffer);
		        break;
		    default:break;
		}
	    }
	break;
	default:sync_input(infile);
	break;
    }
  }
  /* we are done parsing script file */
  /* check if xrange / yrange was set explicit ... or use xmin=0 xmax=xsize ymin=0 ymax=ysize : Quadrant I */
  if( found_size_command == 1 ){
    fprintf(js_include_file,"var xmin = 0;var xmax = %d;var ymin = 0;var ymax = %d",xsize,ysize);
  }
  else
  {
    if( found_size_command != 3 ){
     canvas_error("Please specify both xrange and yrange ...");
    }
  }

  /* if needed, add generic draw functions (grid / xml etc) to buffer : these are no draggable/clickable shapes / objects  ! */
  add_javascript_functions(js_function,canvas_root_id);
   /* add read_canvas() etc functions if needed */
  if( reply_format > 0 ){ add_read_canvas(canvas_root_id,reply_format,reply_precision);}
  if( use_pan_and_zoom == TRUE ){
  /* in case of zooming ... */
  fprintf(js_include_file,"\n<!-- some extra global stuff : need to rethink panning and zooming !!! -->\n\
  precision = %d;var xmin_start=xmin;var xmax_start=xmax;\
  var ymin_start=ymin;var ymax_start=xmax;\
  var zoom_x_increment=0;var zoom_y_increment=0;\
  var pan_x_increment=0;var pan_y_increment=0;\
  if(use_ylogscale == 0 ){\
   zoom_x_increment = (xmax - xmin)/20;zoom_y_increment = (ymax - ymin)/20;pan_x_increment = (xmax - xmin)/20;pan_y_increment = (ymax - ymin)/20;\
  }else{\
   zoom_x_increment = (xmax - xmin)/20;\
   pan_x_increment = (xmax - xmin)/20;\
  };\
  function start_canvas%d(type){\
   switch(type){\
    case 0:xmin = xmin + zoom_x_increment;ymin = ymin + zoom_y_increment;xmax = xmax - zoom_x_increment;ymax = ymax - zoom_y_increment;break;\
    case 1:xmin = xmin - zoom_x_increment;ymin = ymin - zoom_y_increment;xmax = xmax + zoom_x_increment;ymax = ymax + zoom_y_increment;break;\
    case 2:xmin = xmin - pan_x_increment;ymin = ymin ;xmax = xmax - pan_x_increment;ymax = ymax;break;\
    case 3:xmin = xmin + pan_x_increment;ymin = ymin ;xmax = xmax + pan_x_increment;ymax = ymax;break;\
    case 4:xmin = xmin;ymin = ymin - pan_y_increment ;xmax = xmax;ymax = ymax - pan_y_increment;break;\
    case 5:xmin = xmin;ymin = ymin + pan_y_increment ;xmax = xmax;ymax = ymax + pan_y_increment;break;\
    case 6:location.reload();break;\
    default:break;\
   };\
   if(xmax<=xmin){xmin=xmin_start;xmax=xmax_start;};\
   if(ymax<=ymin){ymin=ymin_start;ymax=ymax_start;};\
   try{dragstuff.Zoom(xmin,xmax,ymin,ymax);}catch(e){}\
   %s\
  };\
  start_canvas%d(333);\
 };\n\
<!-- end wims_canvas_function -->\n\
wims_canvas_function%d();\n",precision,canvas_root_id,buffer,canvas_root_id,canvas_root_id);
  }
  else
  {
  /* no zoom, just add buffer */
  fprintf(js_include_file,"\n<!-- add buffer -->\n\
  %s\
 };\n\
<!-- end wims_canvas_function -->\n\
wims_canvas_function%d();\n",buffer,canvas_root_id);
  }
/* done writing the javascript include file */
fclose(js_include_file);

}

/* if using a tooltip, this should always be printed to the *.phtml file, so stdout */
if(use_tooltip == TRUE){
  add_js_tooltip(canvas_root_id,tooltip_text,bgcolor,xsize,ysize);
}
exit(EXIT_SUCCESS);
}
/* end main() */

/******************************************************************************
**
**  sync_input
**
**  synchronises input line - reads to end of line, leaving file pointer
**  at first character of next line.
**
**  Used by:
**  main program - error handling.
**
******************************************************************************/
void sync_input(FILE *infile)
{
	int c = 0;

	if( c == '\n' || c == ';' ) return;
	while( ( (c=getc(infile)) != EOF ) && (c != '\n') && (c != '\r') && (c != ';')) ;
	if( c == EOF ) finished = 1;
	if( c == '\n' || c == '\r' || c == ';') line_number++;
	return;
}

/******************************************************************************/

char *str_replace(const char *str, const char *old, const char *new){
/* http://creativeandcritical.net/str-replace-c/ */
    if(strlen(str) > MAX_BUFFER){canvas_error("string argument too big");}
    char *ret, *r;
    const char *p, *q;
    size_t oldlen = strlen(old);
    size_t count = 0;
    size_t retlen = 0;
    size_t newlen = strlen(new);
    if (oldlen != newlen){
	for (count = 0, p = str; (q = strstr(p, old)) != NULL; p = q + oldlen){
	    count++;
	    retlen = p - str + strlen(p) + count * (newlen - oldlen);
	}
    }
    else
    {
	retlen = strlen(str);
    }

    if ((ret = malloc(retlen + 1)) == NULL){
	ret = NULL;
	canvas_error("string argument is NULL");
    }
    else
    {
	for (r = ret, p = str; (q = strstr(p, old)) != NULL; p = q + oldlen) {
	    size_t l = q - p;
	    memcpy(r, p, l);
	    r += l;
	    memcpy(r, new, newlen);
	    r += newlen;
	}
	strcpy(r, p);
    }
    return ret;
}

/******************************************************************************/

char *get_color(FILE *infile , int last){
    int c,i = 0,is_hex = 0;
    char temp[MAX_COLOR_STRING], *string;
    const char *not_allowed = "0123456789";
    while(( (c=getc(infile)) != EOF ) && ( c != '\n') && ( c != ',' ) && ( c != ';' ) ){
	if( i > MAX_COLOR_STRING ){ canvas_error("colour string is too big ... ? ");}
	if( c == '#' ){
	    is_hex = 1;
	}
	if( c != ' '){
	    if( is_hex == 0 ){if(strchr(not_allowed,c) != 0){canvas_error("found something like a number...but is should have been a colour or #hex color number...<br />Do not use R,G,B !!! ");}}
	    temp[i]=tolower(c);
	    i++;
	}
    }
    if( ( c == '\n' || c == EOF || c == ';' ) && last == 0){canvas_error("expecting more arguments in command");}
    if( c == '\n' || c == ';' ){ done = TRUE; line_number++; }
    if( c == EOF ){finished = 1;}
    if( finished == 1 && last != 1 ){ canvas_error("expected more arguments");}
    temp[i]='\0';
    if( strlen(temp) == 0 ){ canvas_error("expected a colorname or hexnumber, but found nothing !!");}
    if( is_hex == 1 ){
	char red[3], green[3], blue[3];
	red[0]   = toupper(temp[1]); red[1]   = toupper(temp[2]); red[2]   = '\0';
	green[0] = toupper(temp[3]); green[1] = toupper(temp[4]); green[2] = '\0';
	blue[0]  = toupper(temp[5]); blue[1]  = toupper(temp[6]); blue[2]  = '\0';
	int r = (int) strtol(red,   NULL, 16);
	int g = (int) strtol(green, NULL, 16);
	int b = (int) strtol(blue,  NULL, 16);
        string = (char *)my_newmem(12);
	snprintf(string,11,"%d,%d,%d",r,g,b);
	return string;
    }
    else
    {
        string = (char *)my_newmem(sizeof(temp));
	snprintf(string,sizeof(temp),"%s",temp);
	for( i = 0; i < NUMBER_OF_COLORNAMES ; i++ ){
	    if( strcmp( colors[i].name , string ) == 0 ){
		return colors[i].rgb;
	    }
	}
	canvas_error("I was expecting a color name or hexnumber...but found nothing.");
    }
    return "0,0,255";
}

char *get_string(FILE *infile,int last){ /* last = 0 : more arguments ; last=1 final argument */
    int c,i=0;
    char  temp[MAX_BUFFER], *string;
    while(( (c=getc(infile)) != EOF ) && ( c != '\n') ){
	temp[i]=c;
	i++;
	if(i > MAX_BUFFER){ canvas_error("string size too big...repeat command to fit string");break;}
    }
    if( ( c == '\n' || c == EOF ) && last == 0){canvas_error("expecting more arguments in command");}
    if( c == '\n') { done = TRUE; line_number++; }
    if( c == EOF ) {
	finished = 1;
	if( last != 1 ){ canvas_error("expected more arguments");}
    }
    temp[i]='\0';
    if( strlen(temp) == 0 ){ canvas_error("expected a word or string, but found nothing !!");}
    string=(char *)my_newmem(strlen(temp));
    snprintf(string,sizeof(temp),"%s",temp);
    return string;
}

char *get_string_argument(FILE *infile,int last){  /* last = 0 : more arguments ; last=1 final argument */
    int c,i=0;
    char temp[MAX_BUFFER], *string;
    while(( (c=getc(infile)) != EOF ) && ( c != '\n') && ( c != ',')){
	temp[i]=c;
	i++;
	if(i > MAX_BUFFER){ canvas_error("string size too big...will cut it off");break;}
    }
    if( ( c == '\n' || c == EOF) && last == 0){canvas_error("expecting more arguments in command");}
    if( c == '\n') { line_number++; }
    if( c == EOF ) {finished = 1;}
    if( finished == 1 && last != 1 ){ canvas_error("expected more arguments");}
    temp[i]='\0';
/*    
    17.10.2014 removed (question Perrin)
    may cause some unwanted effects...
    if( strlen(temp) == 0 ){ canvas_error("expected a word or string (without comma) , but found nothing !!");}
*/
    string=(char *)my_newmem(sizeof(temp));
    snprintf(string,sizeof(temp),"%s",temp);
    done = TRUE;
    return string;
}

double get_real(FILE *infile, int last){ /* accept anything that looks like an number ?  last = 0 : more arguments ; last=1 final argument */
    int c,i=0,found_calc = 0;
    double y;
    char tmp[MAX_INT];
    /* 
     these things are 'allowed functions' : *,^,+,-,/,(,),e,arc,cos,tan,pi,log,ln,sqrt,abs 
     but thereshould be a better way to avoid segfaults !
    */
    const char *allowed = "earcostanpilogqb*+-/^()";/* assuming these are allowed stuff in a 'number'*/
    const char *not_allowed = "#dfhjkmuvwxyz{}[]%&~!$";/* avoid segmentation faults in a "atof()" and "wims eval" */
    while(( (c=getc(infile)) != EOF ) && ( c != ',') && (c != '\n') && ( c != ';')){
     if( c != ' ' ){
      if( i == 0 &&  c == '+' ){
       continue;
      }
      else
      {
       c = tolower(c);
       if( strchr(not_allowed,c) != 0 ){canvas_error("found a character not associated with a number...");}
       if( strchr(allowed,c) != 0 ){found_calc = 1;}/* hand the string over to wims eval() */
       tmp[i] = c;
       i++;
      }
     }
     if( i > MAX_INT - 1){canvas_error("number too large");}
    }
    if( ( c == '\n' || c == EOF || c == ';' ) && last == 0){canvas_error("expecting more arguments in command");}
    if( c == '\n' || c == ';' ){ done = TRUE; line_number++; }
    if( c == EOF ){done = TRUE ; finished = 1;}
    tmp[i]='\0';
    if( strlen(tmp) == 0 ){canvas_error("expected a number , but found nothing !!");}
    if( found_calc == 1 ){ /* use wims eval to calculate 2*pi/3 */
     void *f = eval_create(tmp);
     assert(f);if( f == NULL ){canvas_error("I'm having trouble parsing your \"expression\" ") ;}
     y = eval_x(f, 1);
     /* if function is bogus; y = 1 : so no core dumps */
     eval_destroy(f);
    }
    else
    {
     y = atof(tmp);
    }
    return y;
}


void canvas_error(char *msg){
    fprintf(stdout,"\n</script><hr /><span style=\"color:red\">FATAL syntax error:line %d : %s</span><hr />",line_number-1,msg);
    finished = 1;
    exit(EXIT_SUCCESS);
}


/* convert x/y coordinates to pixel */
int x2px(double x){
 return x*xsize/(xmax - xmin) -  xsize*xmin/(xmax - xmin);
}

int y2px(double y){
 return -1*y*ysize/(ymax - ymin) + ymax*ysize/(ymax - ymin);
}

double px2x(int x){
 return (x*(xmax - xmin)/xsize + xmin);
}
double px2y(int y){
 return (y*(ymax - ymin)/ysize + ymin);
}

void add_to_buffer(char *tmp){
 if( tmp == NULL || tmp == 0 ){ canvas_error("nothing to add_to_buffer()...");}
 /*  do we have enough space left in buffer[MAX_BUFFER] ? */
 int space_left = (int) (sizeof(buffer) - strlen(buffer));
 if( space_left > strlen(tmp)){
  strncat(buffer,tmp,space_left - 1);/* add safely "tmp" to the string buffer */
 }
 else
 {
  canvas_error("buffer is too big\n");
 }
 tmp = NULL;free(tmp);
 return;
}

void reset(){
 if(use_filled == TRUE){use_filled = FALSE;}
 if(use_dashed == TRUE){use_dashed = FALSE;}
 if(use_rotate == TRUE){use_rotate = FALSE;}
   onclick = 0;
}



/* What reply format in read_canvas();

note:if userdraw is combined with inputfields...every "userdraw" based answer will append "\n" and  inputfield.value()
1 = x1,x2,x3,x4....x_n
    y1,y2,y3,y4....y_n

    x/y in pixels

2 = x1,x2,x3,x4....x_n
    y1,y2,y3,y4....y_n
    x/y in  xrange / yrange coordinate system

3 = x1,x2,x3,x4....x_n
    y1,y2,y3,y4....y_n
    r1,r2,r3,r4....r_n

    x/y in pixels
    r in pixels

4 = x1,x2,x3,x4....x_n
    y1,y2,y3,y4....y_n
    r1,r2,r3,r4....r_n

    x/y in  xrange / yrange coordinate system
    r in pixels

5 = Ax1,Ax2,Ax3,Ax4....Ax_n
    Ay1,Ay2,Ay3,Ay4....Ay_n
    Bx1,Bx2,Bx3,Bx4....Bx_n
    By1,By2,By3,By4....By_n
    Cx1,Cx2,Cx3,Cx4....Cx_n
    Cy1,Cy2,Cy3,Cy4....Cy_n
    ....
    Zx1,Zx2,Zx3,Zx4....Zx_n
    Zy1,Zy2,Zy3,Zy4....Zy_n

    x/y in pixels

6 = Ax1,Ax2,Ax3,Ax4....Ax_n
    Ay1,Ay2,Ay3,Ay4....Ay_n
    Bx1,Bx2,Bx3,Bx4....Bx_n
    By1,By2,By3,By4....By_n
    Cx1,Cx2,Cx3,Cx4....Cx_n
    Cy1,Cy2,Cy3,Cy4....Cy_n
    ....
    Zx1,Zx2,Zx3,Zx4....Zx_n
    Zy1,Zy2,Zy3,Zy4....Zy_n

    x/y in  xrange / yrange coordinate system

7 = x1:y1,x2:y2,x3:y3,x4:y4...x_n:y_n

    x/y in pixels

8 = x1:y1,x2:y2,x3:y3,x4:y4...x_n:y_n

    x/y in  xrange / yrange coordinate system

9 = x1:y1:r1,x2:y2:r2,x3:y3:r3,x4:y4:r3...x_n:y_n:r_n

    x/y in pixels

10 = x1:y1:r1,x2:y2:r2,x3:y3:r3,x4:y4:r3...x_n:y_n:r_n

    x/y in  xrange / yrange coordinate system

11 = Ax1,Ay1,Ax2,Ay2
     Bx1,By1,Bx2,By2
     Cx1,Cy1,Cx2,Cy2
     Dx1,Dy1,Dx2,Dy2
     ......
     Zx1,Zy1,Zx2,Zy2

    x/y in  xrange / yrange coordinate system

12 = Ax1,Ay1,Ax2,Ay2
     Bx1,By1,Bx2,By2
     Cx1,Cy1,Cx2,Cy2
     Dx1,Dy1,Dx2,Dy2
     ......
     Zx1,Zy1,Zx2,Zy2

    x/y in pixels

13 = Ax1:Ay1:Ax2:Ay2,Bx1:By1:Bx2:By2,Cx1:Cy1:Cx2:Cy2,Dx1:Dy1:Dx2:Dy2, ... ,Zx1:Zy1:Zx2:Zy2

    x/y in  xrange / yrange coordinate system
14 = Ax1:Ay1:Ax2:Ay2,Bx1:By1:Bx2:By2....Zx1:Zy1:Zx2:Zy2
    x/y in pixels
15 = reply from inputfields,textareas
    reply1,reply2,reply3,...,reply_n
    only fields set write (a.g. will not read 'readonly' inputfield values'

16 = read mathml inputfields only

17 = read userdraw text only (x1:y1:text1,x2:y2:text2...x_n:y_n:text_n
 when ready : calculate size_t of string via snprintf(NULL,0,"blah blah...");

18 = read clock(s) : H1:M1:S1,H2:M2:S2,...H_n:M_n:S_n
19 = return clicked object number (analogue to shape-library onclick)
20 = return x/y-data in x-range/y-range of all 'draggable' images
21 = return verbatim coordinates (x1:y1) (x2:y2)...(x_n:y_n)
22 = array : x1,y1,x2,y2,x3,y3,x4,y4...x_n,y_n
    x/y in  xrange / yrange coordinate system
23 = answertype for a polyline : remove multiple occurences  due to reclick on a point to create next polyline segment
24 = read all inputfield values: even those set 'readonly'
25 = return all userdrawn arcs in degrees:
26 = return all userdrawn arcs in radians:
27 = return (only) userdraw inputfields array: x1:y1:text1,x2:y2:text2...
28 = x1,y1,r1,x2,y2,r2...x_n,y_n,r_n
    x/y/r in  xrange / yrange coordinate system: may be used to reinput into command 
    'circles color,x1,y1,r1,x2,y2,r2...x_n,y_n,r_n'
    will not return anything else (e.g. no inputfields , text etc)
*/


void add_read_canvas(int canvas_root_id,int type_reply,int reply_precision){
/* just 1 reply type allowed */
fprintf(js_include_file,"\
\n<!-- begin set_reply_precision() -->\n\
function set_reply_precision(){\
 var len = userdraw_x.length;\
 var prec = %d;\
 for(var p = 0 ; p < len ; p++ ){\
  userdraw_x[p] = (Math.round(prec*userdraw_x[p]))/prec;\
  userdraw_y[p] = (Math.round(prec*userdraw_y[p]))/prec;\
 };\
 len = userdraw_radius.length;\
 if( len > 0 ){\
  for(var p = 0 ; p < len ; p++ ){\
   userdraw_radius[p] = (Math.round(prec*userdraw_radius[p]))/prec;\
  };\
 };\
};",reply_precision);

switch(type_reply){
/*
answers may have:
x-values,y-values,r-values,input-fields,mathml-inputfields,text-typed answers
*/
    case 1: fprintf(js_include_file,"\
\n<!-- begin function 1 read_canvas%d() -->\n\
read_canvas%d = function(){\
 if( userdraw_x.length == 0){alert(\"nothing drawn...\");return;}\
 set_reply_precision();\
 if( document.getElementById(\"canvas_input0\") || document.getElementById(\"mathml0\") ){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return userdraw_x+\"\\n\"+userdraw_y+\"\\n\"+input_reply + \"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return userdraw_x+\"\\n\"+userdraw_y+\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return userdraw_x+\"\\n\"+userdraw_y+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return userdraw_x+\"\\n\"+userdraw_y;\
  }\
 };\
};\n\
<!-- end function 1 read_canvas%d() -->",canvas_root_id,canvas_root_id,canvas_root_id);
    break;
    case 2: fprintf(js_include_file,"\
\n<!-- begin function 2 read_canvas%d() -->\n\
read_canvas%d = function(){\
 if( userdraw_x.length == 0){alert(\"nothing drawn...\");return;}\
 set_reply_precision();\
 var reply_x = new Array();var reply_y = new Array();var p = 0;\
 var prec = %d;\
 while(userdraw_x[p]){\
  reply_x[p] = (Math.round(prec*(px2x(userdraw_x[p]))))/prec;\
  reply_y[p] = (Math.round(prec*(px2y(userdraw_y[p]))))/prec;\
  p++;\
 };\
 if(p == 0){alert(\"nothing drawn...\");return;};\
 if( document.getElementById(\"canvas_input0\")){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return reply_x+\"\\n\"+reply_y+\"\\n\"+input_reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply_x+\"\\n\"+reply_y+\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return reply_x+\"\\n\"+reply_y+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply_x+\"\\n\"+reply_y;\
  };\
 };\
};\n\
<!-- end function 2 read_canvas%d() -->",canvas_root_id,canvas_root_id,reply_precision,canvas_root_id);
    break;
    case 3: fprintf(js_include_file,"\
\n<!-- begin function 3 read_canvas%d() -->\n\
read_canvas%d = function(){\
 if( userdraw_x.length == 0){alert(\"nothing drawn...\");return;}\
 set_reply_precision();\
 if( document.getElementById(\"canvas_input0\") || document.getElementById(\"mathml0\") ){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return userdraw_x+\"\\n\"+userdraw_y+\"\\n\"+userdraw_radius+\"\\n\"+input_reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return userdraw_x+\"\\n\"+userdraw_y+\"\\n\"+userdraw_radius+\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return userdraw_x+\"\\n\"+userdraw_y+\"\\n\"+userdraw_radius+\"\\n\"+userdrawW_text;\
  }\
  else\
  {\
   return userdraw_x+\"\\n\"+userdraw_y+\"\\n\"+userdraw_radius;\
  }\
 }\
};\n\
<!-- end function 3 read_canvas%d() -->",canvas_root_id,canvas_root_id,canvas_root_id);
    break;
    case 4: fprintf(js_include_file,"\
\n<!-- begin function 4 read_canvas%d() -->\n\
read_canvas%d = function(){\
 var prec = %d;\
 var reply_x = new Array();var reply_y = new Array();var p = 0;\
 while(userdraw_x[p]){\
  reply_x[p] = (Math.round(prec*(px2x(userdraw_x[p]))))/prec;\
  reply_y[p] = (Math.round(prec*(px2y(userdraw_y[p]))))/prec;;\
  p++;\
 };\
 if(p == 0){alert(\"nothing drawn...\");return;};\
 if( document.getElementById(\"canvas_input0\") || document.getElementById(\"mathml0\") ){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return reply_x+\"\\n\"+reply_y +\"\\n\"+userdraw_radius+\"\\n\"+input_reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply_x+\"\\n\"+reply_y +\"\\n\"+userdraw_radius+\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return reply_x+\"\\n\"+reply_y+\"\\n\"+userdraw_radius+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply_x+\"\\n\"+reply_y+\"\\n\"+userdraw_radius;\
  }\
 };\
};\n\
<!-- end function 4 read_canvas%d() -->",canvas_root_id,canvas_root_id,reply_precision,canvas_root_id);
    break;
    /*
	attention: we reset userdraw_x / userdraw_y  : because  userdraw_x = [][] userdraw_y = [][]
	used for userdraw multiple paths
    */
    case 5: fprintf(js_include_file,"\
\n<!-- begin function 5 read_canvas%d() -->\n\
read_canvas%d = function(){\
 set_reply_precision();\
 var p = 0;\
 var reply = \"\";\
 for(p = 0; p < userdraw_x.length;p++){\
  if(userdraw_x[p] != null ){\
   reply = reply + userdraw_x[p]+\"\\n\"+userdraw_y[p]+\"\\n\";\
  };\
 };\
 if(p == 0){alert(\"nothing drawn...\");return;};\
 userdraw_x = [];userdraw_y = [];\
 if( document.getElementById(\"canvas_input0\") || document.getElementById(\"mathml0\") ){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+input_reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply +\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply;\
  }\
 };\
};\n\
<!-- end function 5 read_canvas%d() -->",canvas_root_id,canvas_root_id,canvas_root_id);
    break;
    /*
	attention: we reset userdraw_x / userdraw_y  : because  userdraw_x = [][] userdraw_y = [][]
	used for userdraw multiple paths
    */
    case 6: fprintf(js_include_file,"\
\n<!-- begin function 6 read_canvas%d() -->\n\
read_canvas%d = function(){\
 var p = 0;\
 var reply = \"\";\
 var tmp_x = new Array();\
 var tmp_y = new Array();\
 var prec = %d;\
 for(p = 0 ; p < userdraw_x.length; p++){\
  tmp_x = userdraw_x[p];\
  tmp_y = userdraw_y[p];\
  if(tmp_x != null){\
   for(var i = 0 ; i < tmp_x.length ; i++){\
    tmp_x[i] = (Math.round(prec*(px2x(tmp_x[i]))))/prec;\
    tmp_y[i] = (Math.round(prec*(px2y(tmp_y[i]))))/prec;\
   };\
   reply = reply + tmp_x + \"\\n\" + tmp_y +\"\\n\";\
  };\
 };\
 if(p == 0){alert(\"nothing drawn...\");return;};\
 userdraw_x = [];userdraw_y = [];\
 if( document.getElementById(\"canvas_input0\") ){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+input_reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply +\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply;\
  }\
 };\
};\n\
<!-- end function 6 read_canvas%d() -->",canvas_root_id,canvas_root_id,reply_precision,canvas_root_id);
    break;
    case 7: fprintf(js_include_file,"\
\n<!-- begin function 7 read_canvas%d() -->\n\
read_canvas%d = function(){\
 set_reply_precision();\
 var reply = new Array();\
 var p = 0;\
 while(userdraw_x[p]){\
  reply[p] = userdraw_x[p] +\":\" + userdraw_y[p];\
  p++;\
 };\
 if(p == 0){alert(\"nothing drawn...\");return;};\
 if( document.getElementById(\"canvas_input0\") ){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return reply+\"\\n\"+input_reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply+\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply;\
  }\
 };\
};\n\
<!-- end function 7 read_canvas%d() -->",canvas_root_id,canvas_root_id,canvas_root_id);
    break;
    case 8: fprintf(js_include_file,"\
\n<!-- begin function 8 read_canvas%d() -->\n\
read_canvas%d = function(){\
 var reply = new Array();\
 var p = 0;\
 var prec = %d;\
 while(userdraw_x[p]){\
  reply[p] = (Math.round(prec*(px2x(userdraw_x[p]))))/prec +\":\" + (Math.round(prec*(px2y(userdraw_y[p]))))/prec;\
  p++;\
 };\
 if(p == 0){alert(\"nothing drawn...\");return;};\
 if( document.getElementById(\"canvas_input0\") || document.getElementById(\"mathml0\") ){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+input_reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply +\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply;\
  }\
 };\
};\n\
<!-- end function 8 read_canvas%d() -->",canvas_root_id,canvas_root_id,reply_precision,canvas_root_id);
    break;
    case 9: fprintf(js_include_file,"\
\n<!-- begin function 9 read_canvas%d() -->\n\
read_canvas%d = function(){\
 set_reply_precision();\
 var reply = new Array();\
 var p = 0;\
 while(userdraw_x[p]){\
  reply[p] = userdraw_x[p] +\":\" + userdraw_y[p] + \":\" + userdraw_radius[p];\
  p++;\
 };\
 if(p == 0){alert(\"nothing drawn...\");return;};\
 if( document.getElementById(\"canvas_input0\") ){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+input_reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply +\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply;\
  }\
 };\
};\n\
<!-- end function 9 read_canvas%d() -->",canvas_root_id,canvas_root_id,canvas_root_id);
    break;
    case 10: fprintf(js_include_file,"\
\n<!-- begin function 10 read_canvas%d() -->\n\
read_canvas%d = function(){\
 var reply = new Array();\
 var p = 0;\
 var prec = %d;\
 while(userdraw_x[p]){\
  reply[p] = (Math.round(prec*(px2x(userdraw_x[p]))))/prec +\":\" + (Math.round(prec*(px2y(userdraw_y[p]))))/prec +\":\" + (Math.round(prec*userdraw_radius[p]))/prec;\
  p++;\
 };\
 if(p == 0){alert(\"nothing drawn...\");return;};\
 if( document.getElementById(\"canvas_input0\") ){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+input_reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply +\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply;\
  }\
 };\
};\n\
<!-- end function 10 read_canvas%d() -->",canvas_root_id,canvas_root_id,reply_precision,canvas_root_id);
    break;
    case 11: fprintf(js_include_file,"\
\n<!-- begin function 11 read_canvas%d() -->\n\
read_canvas%d = function(){\
 var reply = \"\";\
 var p = 0;\
 var prec = %d;\
 while(userdraw_x[p]){\
  reply = reply + (Math.round(prec*(px2x(userdraw_x[p]))))/prec +\",\" + (Math.round(prec*(px2y(userdraw_y[p]))))/prec +\",\" + (Math.round(prec*(px2x(userdraw_x[p+1]))))/prec +\",\" + (Math.round(prec*(px2y(userdraw_y[p+1]))))/prec +\"\\n\" ;\
  p = p+2;\
 };\
 if(p == 0){alert(\"nothing drawn...\");return;};\
 if( document.getElementById(\"canvas_input0\") || document.getElementById(\"mathml0\") ){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+input_reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply +\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply;\
  }\
 };\
};\n\
<!-- end function 11 read_canvas%d() -->",canvas_root_id,canvas_root_id,reply_precision,canvas_root_id);
    break;
    case 12: fprintf(js_include_file,"\
\n<!-- begin function 12 read_canvas%d() -->\n\
read_canvas%d = function(){\
 set_reply_precision();\
 var reply = \"\";\
 var p = 0;\
 for(p = 0; p< userdraw_x.lenght;p = p+2){\
  if(userdraw_x[p] != null){\
    reply = reply + userdraw_x[p] +\",\" + userdraw_y[p] +\",\" + userdraw_x[p+1] +\",\" + userdraw_y[p+1] +\"\\n\" ;\
  };\
 };\
 if(p == 0){alert(\"nothing drawn...\");return;};\
 if( document.getElementById(\"canvas_input0\") ){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+input_reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply +\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+userdraw_text\
  }\
  else\
  {\
   return reply;\
  }\
 };\
};\n\
<!-- end function 12 read_canvas%d() -->",canvas_root_id,canvas_root_id,canvas_root_id);
    break;
    case 13: fprintf(js_include_file,"\
\n<!-- begin function 13 read_canvas%d() -->\n\
read_canvas%d = function(){\
 var reply = new Array();\
 var p = 0;var i = 0;\
 var prec = %d;\
 while(userdraw_x[p]){\
  reply[i] = (Math.round(prec*(px2x(userdraw_x[p]))))/prec +\":\" + (Math.round(prec*(px2y(userdraw_y[p]))))/prec +\":\" + (Math.round(prec*(px2x(userdraw_x[p+1]))))/prec +\":\" + (Math.round(prec*(px2y(userdraw_y[p+1]))))/prec;\
  p = p+2;i++;\
 };\
 if(p == 0){alert(\"nothing drawn...\");return;};\
 if( document.getElementById(\"canvas_input0\") ){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+input_reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply +\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+userdraw_text\
  }\
  else\
  {\
   return reply;\
  }\
 };\
};\n\
<!-- end function 13 read_canvas%d() -->",canvas_root_id,canvas_root_id,reply_precision,canvas_root_id);
    break;
    case 14: fprintf(js_include_file,"\
\n<!-- begin function 14 read_canvas%d() -->\n\
read_canvas%d = function(){\
 set_reply_precision();\
 var reply = new Array();\
 var p = 0;var i = 0;\
 while(userdraw_x[p]){\
  reply[i] = userdraw_x[p] +\":\" + userdraw_y[p] +\":\" + userdraw_x[p+1] +\":\" + userdraw_y[p+1];\
  p = p+2;i++;\
 };\
 if(p == 0){alert(\"nothing drawn...\");return;};\
 if( document.getElementById(\"canvas_input0\") ){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+input_reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply +\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply;\
  }\
 };\
};\n\
<!-- end function 14 read_canvas%d() -->",canvas_root_id,canvas_root_id,canvas_root_id);
    break;
    case 15: fprintf(js_include_file,"\
\n<!-- begin function 15  read_canvas%d() -->\n\
read_canvas%d = function(){\
 var input_reply = new Array();\
 var p = 0;\
 if( document.getElementById(\"canvas_input0\")){\
  var t = 0;\
  while(document.getElementById(\"canvas_input\"+t)){\
   if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
    input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
    p++;\
   };\
   t++;\
  };\
 };\
 if( typeof userdraw_text != 'undefined' ){\
   return input_reply +\"\\n\"+userdraw_text;\
 }\
 else\
 {\
  return input_reply;\
 };\
};\n\
<!-- end function 15 read_canvas%d() -->",canvas_root_id,canvas_root_id,canvas_root_id);
    break;
    case 16: fprintf(js_include_file,"\
\n<!-- begin function 16 read_mathml() -->\n\
function read_mathml(){\
 var reply = new Array();\
 var p = 0;\
 if( document.getElementById(\"mathml0\")){\
  while(document.getElementById(\"mathml\"+p)){\
   reply[p] = document.getElementById(\"mathml\"+p).value;\
   p++;\
  };\
 };\
return reply;\
};\
this.read_mathml = read_mathml;\n\
<!-- end function 16 read_mathml() -->");
    break;
    case 17:  fprintf(js_include_file,"\
\n<!-- begin function 17 read_canvas%d() -->\n\
read_canvas%d = function(){\
 if( userdraw_text.length == 0){alert(\"no text typed...\");return;}\
 return userdraw_text;\
};\n\
<!-- end function 17 read_canvas%d() -->",canvas_root_id,canvas_root_id,canvas_root_id);
    break;
    case 18: fprintf(js_include_file,"\
\n<!-- begin function 18 read_canvas%d() -->\n\
read_canvas%d = function(){\
 var p = 0;\
 var reply = new Array();\
 var name;\
 var t = true;\
 var h;var m;var s;\
 while(t){\
  try{\
   name = eval('clocks'+p);\
   h = name.H;m = name.M;s = name.S;\
   if(s < 0){s = 60 + s;m = m - 1;};\
   if(m < 0){m = 60 + m;h = h - 1;};\
   if(h < 0){h = 12 + h;};\
   h = parseInt((h+m/60+s/3600)%%12);m = parseInt((m + s/60)%%60);s = parseInt(s%%60);\
   reply[p] = h+\":\"+m+\":\"+s;\
   p++;\
  }catch(e){t=false;};\
 };\
 if( p == 0 ){alert(\"clock(s) not modified...\");return;}\
 return reply;\
};\n\
<!-- end function 18 read_canvas%d() -->",canvas_root_id,canvas_root_id,canvas_root_id);
    break;
    case 19: fprintf(js_include_file,"\
\n<!-- begin function 19 read_canvas%d() -->\n\
read_canvas%d = function(){\
 return reply[0];\
};\n\
<!-- end function 19 read_canvas%d() -->",canvas_root_id,canvas_root_id,canvas_root_id);
    break;
    case 20: fprintf(js_include_file,"\
\n<!-- begin function 20 read_canvas%d() -->\n\
read_canvas%d = function(){\
 var prec = %d;\
 var len  = ext_drag_images.length;\
 var reply = new Array(len);\
 for(var p = 0 ; p < len ; p++){\
    var img = ext_drag_images[p];\
    reply[p] = (Math.round(prec*(px2x(img[6]))))/prec+\":\"+(Math.round(prec*(px2y(img[7]))))/prec;\
 };\
 return reply;\
};\n\
<!-- end function 20 read_canvas%d() -->",canvas_root_id,canvas_root_id,reply_precision,canvas_root_id);
    break;
    case 21: fprintf(js_include_file,"\
\n<!-- begin function 21 read_canvas%d() -->\n\
read_canvas%d = function(){\
 if( userdraw_x.length == 0){alert(\"nothing drawn...\");return;}\
 var reply_coord = new Array();var p = 0;\
 var prec = %d;\
 while(userdraw_x[p]){\
  reply_coord[p] = \"(\"+(Math.round(prec*(px2x(userdraw_x[p]))))/prec+\":\"+(Math.round(prec*(px2y(userdraw_y[p]))))/prec+\")\";\
  p++;\
 };\
 if(p == 0){alert(\"nothing drawn...\");return;};\
 if( document.getElementById(\"canvas_input0\") ){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return reply_coord+\"\\n\"+input_reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply_coord+\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return reply_coord+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply_coord;\
  };\
 };\
};\n\
<!-- end function 21 read_canvas%d() -->",canvas_root_id,canvas_root_id,reply_precision,canvas_root_id);
    break;
    case 22: fprintf(js_include_file,"\
\n<!-- begin function 22 read_canvas%d() -->\n\
read_canvas%d = function(){\
 var reply = new Array();\
 var lu = userdraw_x.length;\
 if(lu == 0){alert(\"nothing drawn...\");return;};\
 var idx = 0;\
 var prec = %d;\
 for(var p = 0 ; p < lu ; p++){\
  reply[idx] = (Math.round(prec*(px2x(userdraw_x[p]))))/prec;idx++;\
  reply[idx] = (Math.round(prec*(px2y(userdraw_y[p]))))/prec;idx++;\
 };\
 if( document.getElementById(\"canvas_input0\") ){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+input_reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply +\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return reply +\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply;\
  }\
 };\
};\n\
<!-- end function 22 read_canvas%d() -->",canvas_root_id,canvas_root_id,reply_precision,canvas_root_id);
    break;
    case 23: fprintf(js_include_file,"\
\n<!-- begin function 23 read_canvas%d() default 5 px marge -->\n\
read_canvas%d = function(){\
 if( userdraw_x.length < 2){alert(\"nothing drawn...\");return;}\
 var lu = userdraw_x.length;\
 if( lu != userdraw_y.length ){ alert(\"x / y mismatch !\");return;}\
 var reply_x = new Array();var reply_y = new Array();\
 var marge = 5;var p = 0;\
 var prec = %d;\
 for(var i = 0; i < lu - 1 ; i++ ){\
  if( Math.abs(userdraw_x[i] - userdraw_x[i+1])){\
   reply_x[p] = (Math.round(prec*(px2x(userdraw_x[i]))))/prec;reply_y[p] = (Math.round(prec*(px2y(userdraw_y[i]))))/prec;\
   if( isNaN(reply_x[p]) || isNaN(reply_y[p]) ){ alert(\"hmmmm ?\");return; };\
   p++;\
  };\
  reply_x[p] = (Math.round(prec*(px2x(userdraw_x[lu-1]))))/prec;reply_y[p] = (Math.round(prec*(px2y(userdraw_y[lu-1]))))/prec;\
 };\
 if( document.getElementById(\"canvas_input0\")){\
  var p = 0;var input_reply = new Array();\
  if( document.getElementById(\"canvas_input0\")){\
   var t = 0;\
   while(document.getElementById(\"canvas_input\"+t)){\
    if( ! document.getElementById(\"canvas_input\"+t).getAttribute(\"readonly\")){\
     input_reply[p] = document.getElementById(\"canvas_input\"+t).value;\
     p++;\
    };\
    t++;\
   };\
  };\
  if( typeof userdraw_text != 'undefined' ){\
   return reply_x+\"\\n\"+reply_y+\"\\n\"+input_reply+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply_x+\"\\n\"+reply_y+\"\\n\"+input_reply;\
  }\
 }\
 else\
 {\
  if( typeof userdraw_text != 'undefined' ){\
   return reply_x+\"\\n\"+reply_y+\"\\n\"+userdraw_text;\
  }\
  else\
  {\
   return reply_x+\"\\n\"+reply_y;\
  };\
 };\
};\n\
<!-- end function 23 read_canvas%d() -->",canvas_root_id,canvas_root_id,reply_precision,canvas_root_id);
    break;
    case 24: fprintf(js_include_file,"\n\
<!-- begin function 24  read_canvas%d() -->\n\
read_canvas%d = function(){\
 var input_reply = new Array();\
 var p = 0;\
 if( document.getElementById(\"canvas_input0\")){\
  while(document.getElementById(\"canvas_input\"+p)){\
    input_reply[p] = document.getElementById(\"canvas_input\"+p).value;\
    p++;\
  };\
  return input_reply;\
 };\
};\n\
<!-- end function 24 read_canvas%d() -->",canvas_root_id,canvas_root_id,canvas_root_id);
    break;
    case 25:
    fprintf(js_include_file,"\n<!-- begin function 25 read_canvas%d() : angle(s) in degrees-->\n\
read_canvas%d = function(){\
 if( userdraw_radius.length < 1){alert(\"nothing drawn...\");return;}\
 var lu = userdraw_radius.length;\
 var prec = %d;\
 var angle_reply = new Array(lu);\
 for(var p = 0 ; p < lu ; p++){\
  angle_reply[p] = (Math.round(prec*180*(userdraw_radius[p])/Math.PI))/prec;\
 };\
 return angle_reply;\
};\n\
<!-- end function 25 read_canvas%d() -->",canvas_root_id,canvas_root_id,reply_precision,canvas_root_id);
    break;
    case 26:
    fprintf(js_include_file,"\n<!-- begin function 26 read_canvas%d() : angle(s) in radians-->\n\
read_canvas%d = function(){\
 if( userdraw_radius.length < 1){alert(\"nothing drawn...\");return;}\
 var lu = userdraw_radius.length;\
 var prec = %d;\
 var angle_reply = new Array(lu);\
 for(var p = 0 ; p < lu ; p++){\
  angle_reply[p] = (Math.round(prec*(userdraw_radius[p])))/prec;\
 };\
 return angle_reply;\
};\n\
<!-- end function 26 read_canvas%d() -->",canvas_root_id,canvas_root_id,reply_precision,canvas_root_id);
    break;
    case 27:
    fprintf(js_include_file,"\n<!-- begin function 27 read_canvas%d()  : inputfield(s) location and their values : -->\n\
read_canvas%d = function(){\
 var lu = userdraw_x.length;\
 if( lu < 1){alert(\"nothing drawn...\");return;}\
 set_reply_precision();\
 var prec = %d;\
 for(var p = 0 ; p < lu ; p++){\
   reply[p] = (Math.round(prec*(px2x(userdraw_x[p]))))/prec+\":\"+(Math.round(prec*(px2y(userdraw_y[p]))))/prec+\":\"+ document.getElementById(\"canvas_input\"+p).value;\
 };\
 return reply;\
};\n\
<!-- end function 27 read_canvas%d() -->",canvas_root_id,canvas_root_id,reply_precision,canvas_root_id);
    break;
    case 28:
    fprintf(js_include_file,"\n<!-- begin function 28 read_canvas%d() -->\n\
read_canvas%d = function(){\
 var prec = %d;\
 var reply = new Array();var p = 0;\
 var idx = 0;\
 while(userdraw_x[p]){\
  reply[idx] = (Math.round(prec*(px2x(userdraw_x[p]))))/prec;\
  idx++;\
  reply[idx] = (Math.round(prec*(px2y(userdraw_y[p]))))/prec;\
  idx++;\
  reply[idx] = (Math.round(prec*(px2x(userdraw_radius[p]) - px2x(0))))/prec;\
  idx++;\
  p++;\
 };\
 if( p == 0){alert(\"nothing drawn...\");return;}\
 return reply;\
};\n\
<!-- end function 4 read_canvas%d() -->",canvas_root_id,canvas_root_id,reply_precision,canvas_root_id);
    break;
    default: canvas_error("hmmm unknown replyformat...");break;
}
 return;
}


/*
 add drawfunction :
 - functions used by userdraw_primitives (circle,rect,path,triangle...)
 - things not covered by the drag&drop library (static objects like parallel, lattice ,gridfill , imagefill)
 - grid / mathml
 - will not scale or zoom in
 - will not be filled via pixel operations like fill / floodfill / filltoborder / clickfill
 - is printed directly into 'js_include_file'
*/

void add_javascript_functions(int js_functions[],int canvas_root_id){
int i;
for(i = 0 ; i < MAX_JS_FUNCTIONS; i++){
 if( js_functions[i] == 1){
    switch(i){
    case DRAG_EXTERNAL_IMAGE:
fprintf(js_include_file,"\n<!-- drag external images --->\n\
var external_canvas = create_canvas%d(7,xsize,ysize);\
var external_ctx = external_canvas.getContext(\"2d\");\
var external_canvas_rect = external_canvas.getBoundingClientRect();\
canvas_div.addEventListener(\"mousedown\",setxy,false);\
canvas_div.addEventListener(\"mouseup\",dragstop,false);\
canvas_div.addEventListener(\"mousemove\",dragxy,false);\
var selected_image = null;\
var ext_image_cnt = 0;\
var ext_drag_images = new Array();\
function drag_external_image(URL,sx,sy,swidth,sheight,x0,y0,width,height,idx,draggable){\
 ext_image_cnt = idx;\
 var image = new Image();\
 image.src = URL;\
 image.onload = function(){\
  if( x0 < 1 ){ x0 = 0; };if( y0 < 1 ){ y0 = 0; };if( sx < 1 ){ sx = 0; };if( sy < 1 ){ sy = 0; };\
  if( width < 1 ){ width = image.width; };if( height < 1 ){ height = image.height; };\
  if( swidth < 1 ){ swidth = image.width; };if( sheight < 1 ){ sheight = image.height; };\
  var img = new Array(10);\
  img[0] = draggable;img[1] = image;img[2] = sx;img[3] = sy;img[4] = swidth;img[5] = sheight;\
  img[6] = x0;img[7] = y0;img[8] = width;img[9] = height;\
  ext_drag_images[idx] = img;\
  external_ctx.drawImage(img[1],img[2],img[3],img[4],img[5],img[6],img[7],img[8],img[9]);\
 };\
};\
function dragstop(evt){\
 selected_image = null;return;\
};\
function dragxy(evt){\
 if( selected_image != null ){\
  var xoff = (document.documentElement.scrollLeft ? document.documentElement.scrollLeft : document.body.scrollLeft);\
  var yoff = (document.documentElement.scrollTop ? document.documentElement.scrollTop : document.body.scrollTop);\
  var s_img = ext_drag_images[selected_image];\
  s_img[6] = evt.clientX - external_canvas_rect.left + xoff;\
  s_img[7] = evt.clientY - external_canvas_rect.top + yoff;\
  ext_drag_images[selected_image] = s_img;\
  external_ctx.clearRect(0,0,xsize,ysize);\
  for(var i = 0; i <= ext_image_cnt ; i++){\
   var img = ext_drag_images[i];\
   external_ctx.drawImage(img[1],img[2],img[3],img[4],img[5],img[6],img[7],img[8],img[9]);\
  };\
 };\
};\
function setxy(evt){\
 if( ! selected_image && evt.which == 1 ){\
  var xoff = (document.documentElement.scrollLeft ? document.documentElement.scrollLeft : document.body.scrollLeft);\
  var yoff = (document.documentElement.scrollTop ? document.documentElement.scrollTop : document.body.scrollTop);\
  var xm = evt.clientX - external_canvas_rect.left + xoff;\
  var ym = evt.clientY - external_canvas_rect.top + yoff;\
  for(var p = 0 ; p <= ext_image_cnt ; p++){\
   var img = ext_drag_images[p];\
   if( img[0] == 1 ){\
    var w = img.width;\
    var h = img.height;\
    if( xm > img[6] && xm < img[6] + img[4]){\
     if( ym > img[7] && ym < img[7] + img[5]){\
      img[6] = xm;\
      img[7] = ym;\
      ext_drag_images[p] = img;\
      selected_image = p;\
      dragxy(evt);\
     };\
    };\
   };\
  };\
 }\
 else\
 {\
  selected_image = null;\
 };\
};",canvas_root_id);
    break;

    case DRAW_EXTERNAL_IMAGE:
fprintf(js_include_file,"\n<!-- draw external images -->\n\
var draw_external_image = function(URL,sx,sy,swidth,sheight,x0,y0,width,height,draggable){\
 var image = new Image();\
 image.src = URL;\
 var canvas_bg_div = document.getElementById(\"canvas_div%d\");\
 image.onload = function(){\
  if( x0 < 1 ){ x0 = 0; };\
  if( y0 < 1 ){ y0 = 0; };\
  if( sx < 1 ){ sx = 0; };\
  if( sy < 1 ){ sy = 0; };\
  if( width < 1 ){ width = image.width;};\
  if( height < 1 ){ height = image.height;};\
  if( swidth < 1 ){ swidth = image.width;};\
  if( sheight < 1 ){ sheight = image.height;};\
  var ml = x0 - sx;\
  var mh = y0 - sy;\
  canvas_bg_div.style.backgroundPosition= \"left \"+ml+\"px top \"+mh+\"px\";\
  canvas_bg_div.style.backgroundSize = width+\"px \"+height+\"px\";\
  canvas_bg_div.style.backgroundRepeat = \"no-repeat\";\
  canvas_bg_div.style.backgroundPosition= sx+\"px \"+sy+\"px\";\
  canvas_bg_div.style.backgroundImage = \"url(\" + URL + \")\";\
 };\
};",canvas_root_id);
    break;
    case DRAW_GRIDFILL:/* not used for userdraw */
fprintf(js_include_file,"\n<!-- draw gridfill -->\n\
var draw_gridfill = function(canvas_type,x0,y0,dx,dy,linewidth,color,opacity,xsize,ysize){\
 var obj;\
 if( document.getElementById(\"wims_canvas%d\"+canvas_type) ){\
  obj = document.getElementById(\"wims_canvas%d\"+canvas_type);\
 }\
 else\
 {\
  obj = create_canvas%d(canvas_type,xsize,ysize);\
 };\
 var ctx = obj.getContext(\"2d\");\
 var x,y;\
 snap_x = dx;snap_y = dy;\
 ctx.save();\
 ctx.strokeStyle=\"rgba(\"+color+\",\"+opacity+\")\";\
 for( x = x0 ; x < xsize+dx ; x = x + dx ){\
    ctx.moveTo(x,y0);\
    ctx.lineTo(x,ysize);\
 };\
 for( y = y0 ; y < ysize+dy; y = y + dy ){\
    ctx.moveTo(x0,y);\
    ctx.lineTo(xsize,y);\
 };\
 ctx.stroke();\
 ctx.restore();\
 return;};",canvas_root_id,canvas_root_id,canvas_root_id);
    break;

    case DRAW_IMAGEFILL:/* not  used for userdraw */
fprintf(js_include_file,"\n<!-- draw imagefill -->\n\
var draw_imagefill = function(canvas_type,x0,y0,URL,xsize,ysize){\
 var obj;\
 if( document.getElementById(\"wims_canvas%d\"+canvas_type) ){\
  obj = document.getElementById(\"wims_canvas%d\"+canvas_type);\
 }\
 else\
 {\
  obj = create_canvas%d(canvas_type,xsize,ysize);\
 };\
 var ctx = obj.getContext(\"2d\");\
 ctx.save();\
 var img = new Image();\
 img.src = URL;\
 img.onload = function(){\
  if( (img.width > xsize-x0) && (img.height > ysize-y0) ){\
    ctx.drawImage(img,x0,y0,xsize,ysize);\
  }\
  else\
  {\
    var repeat = \"repeat\";\
    if(img.width > xsize - x0){\
	repeat = \"repeat-y\";\
    }\
    else\
    {\
     if( img.height > ysize -x0 ){\
      repeat = \"repeat-x\";\
     }\
    }\
    var pattern = ctx.createPattern(img,repeat);\
    ctx.rect(x0,y0,xsize,ysize);\
    ctx.fillStyle = pattern;\
  }\
  ctx.fill();\
 };\
 ctx.restore();\
 return;\
};",canvas_root_id,canvas_root_id,canvas_root_id);
    break;

    case DRAW_DOTFILL:/* not  used for userdraw */
fprintf(js_include_file,"\n<!-- draw dotfill -->\n\
var draw_dotfill = function(canvas_type,x0,y0,dx,dy,radius,color,opacity,xsize,ysize){\
 var obj;\
 if( document.getElementById(\"wims_canvas%d\"+canvas_type) ){\
  obj = document.getElementById(\"wims_canvas%d\"+canvas_type);\
 }\
 else\
 {\
  obj = create_canvas%d(canvas_type,xsize,ysize);\
 };\
 var ctx = obj.getContext(\"2d\");\
 var x,y;\
 ctx.closePath();\
 ctx.save();\
 snap_x = dx;snap_y = dy;\
 ctx.fillStyle=\"rgba(\"+color+\",\"+opacity+\")\";\
 for( x = x0 ; x < xsize+dx ; x = x + dx ){\
  for( y = y0 ; y < ysize+dy ; y = y + dy ){\
   ctx.arc(x,y,radius,0,2*Math.PI,false);\
   ctx.closePath();\
  }\
 }\
 ctx.fill();\
 ctx.restore();\
 return;};",canvas_root_id,canvas_root_id,canvas_root_id);
    break;

    case DRAW_DIAMONDFILL:/* not used for userdraw */
fprintf(js_include_file,"\n<!-- draw hatch fill -->\n\
var draw_diamondfill = function(canvas_type,x0,y0,dx,dy,linewidth,stroke_color,stroke_opacity,xsize,ysize){\
  var obj;\
 if( document.getElementById(\"wims_canvas%d\"+canvas_type) ){\
  obj = document.getElementById(\"wims_canvas%d\"+canvas_type);\
 }\
 else\
 {\
  obj = create_canvas%d(canvas_type,xsize,ysize);\
 };\
 var ctx = obj.getContext(\"2d\");\
 var x;\
 var y;\
 ctx.save();\
 ctx.lineWidth = linewidth;\
 ctx.strokeStyle=\"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 y = ysize;\
 for( x = x0 ; x < xsize ; x = x + dx ){\
  ctx.moveTo(x,y0);\
  ctx.lineTo(xsize,y);\
  y = y - dy;\
 };\
 y = y0;\
 for( x = xsize ; x > 0 ; x = x - dx){\
  ctx.moveTo(x,ysize);\
  ctx.lineTo(x0,y);\
  y = y + dy;\
 };\
 x = x0;\
 for( y = y0 ; y < ysize ; y = y + dy ){\
  ctx.moveTo(xsize,y);\
  ctx.lineTo(x,ysize);\
  x = x + dx;\
 };\
 x = xsize;\
 for( y = ysize ; y > y0 ; y = y - dy ){\
  ctx.moveTo(x,y0);\
  ctx.lineTo(x0,y);\
  x = x - dx;\
 };\
 ctx.stroke();\
 ctx.restore();\
 return;\
 }",canvas_root_id,canvas_root_id,canvas_root_id);
    break;

    case DRAW_HATCHFILL:/* not used for userdraw */
fprintf(js_include_file,"\n<!-- draw hatch fill -->\n\
var draw_hatchfill = function(canvas_type,x0,y0,dx,dy,linewidth,stroke_color,stroke_opacity,xsize,ysize){\
  var obj;\
 if( document.getElementById(\"wims_canvas%d\"+canvas_type) ){\
  obj = document.getElementById(\"wims_canvas%d\"+canvas_type);\
 }\
 else\
 {\
  obj = create_canvas%d(canvas_type,xsize,ysize);\
 };\
 var ctx = obj.getContext(\"2d\");\
 var x;\
 var y;\
 ctx.save();\
 ctx.lineWidth = linewidth;\
 ctx.strokeStyle=\"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 y = ysize;\
 for( x = x0 ; x < xsize ; x = x + dx ){\
  ctx.moveTo(x,y0);\
  ctx.lineTo(xsize,y);\
  y = y - dy;\
 };\
 y = y0;\
 for( x = xsize ; x >= dx ; x = x - dx){\
  ctx.moveTo(x,ysize);\
  ctx.lineTo(x0,y);\
  y = y + dy;\
 };\
 ctx.stroke();\
 ctx.restore();\
 return;\
 };",canvas_root_id,canvas_root_id,canvas_root_id);
    break;
    case DRAW_CIRCLES:/*  used for userdraw */
fprintf(js_include_file,"\n<!-- draw circles -->\n\
var draw_circles = function(ctx,x_points,y_points,radius,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,use_affine,affine_matrix){\
 ctx.save();\
 if(use_affine == 1 ){ctx.translate(affine_matrix[4],affine_matrix[5]);}\
 if(use_rotate == 1 ){ctx.rotate(angle*Math.PI/180);}\
 ctx.lineWidth = line_width;\
 for(var p = 0 ; p < x_points.length ; p++ ){\
  ctx.beginPath();\
  ctx.arc(x_points[p],y_points[p],radius[p],0,2*Math.PI,false);\
  ctx.closePath();\
  if(use_dashed == 1){if(ctx.setLineDash){ctx.setLineDash([dashtype0,dashtype1]);}else{ctx.mozDash = [dashtype0,dashtype1];};};\
  if(use_filled == 1){ctx.fillStyle = \"rgba(\"+fill_color+\",\"+fill_opacity+\")\";ctx.fill();}\
  ctx.strokeStyle=\"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
  ctx.stroke();\
 }\
 ctx.restore();\
 return;\
};");
    break;
    case DRAW_POLYLINE:/* user for userdraw : draw lines through points */
fprintf(js_include_file,"\n<!-- draw polyline -->\n\
var draw_polyline = function(ctx,x_points,y_points,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,use_affine,affine_matrix){\
 ctx.save();\
 if(use_affine == 1 ){ctx.translate(affine_matrix[4],affine_matrix[5]);}\
 if(use_rotate == 1 ){ctx.rotate(angle*Math.PI/180);}\
 ctx.lineWidth = line_width;\
 ctx.strokeStyle=\"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 if(use_dashed == 1){if(ctx.setLineDash){ctx.setLineDash([dashtype0,dashtype1]);}else{ctx.mozDash = [dashtype0,dashtype1];};};\
 ctx.clearRect(0,0,xsize,ysize);\
 ctx.beginPath();\
 for(var p = 0 ; p < x_points.length-1 ; p++ ){\
  ctx.moveTo(x_points[p],y_points[p]);\
  ctx.lineTo(x_points[p+1],y_points[p+1]);\
 }\
 ctx.closePath();\
 ctx.stroke();\
 ctx.fillStyle =\"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 for(var p = 0 ; p < x_points.length ; p++ ){\
  ctx.beginPath();\
  ctx.arc(x_points[p],y_points[p],line_width,0,2*Math.PI,false);\
  ctx.closePath();ctx.fill();ctx.stroke();\
 };\
 ctx.restore();\
 return;\
};");
    break;

    case DRAW_SEGMENTS:/*  used for userdraw */
fprintf(js_include_file,"\n<!-- draw segments -->\n\
var draw_segments = function(ctx,x_points,y_points,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,use_affine,affine_matrix){\
 ctx.save();\
 if(use_affine == 1 ){ctx.translate(affine_matrix[4],affine_matrix[5]);}\
 if(use_rotate == 1 ){ctx.rotate(angle*Math.PI/180);}\
 ctx.lineWidth = line_width;\
 ctx.strokeStyle=\"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 if(use_dashed == 1){if(ctx.setLineDash){ctx.setLineDash([dashtype0,dashtype1]);}else{ctx.mozDash = [dashtype0,dashtype1];};};\
 for(var p = 0 ; p < x_points.length ; p = p+2 ){\
  ctx.beginPath();\
  ctx.moveTo(x_points[p],y_points[p]);\
  ctx.lineTo(x_points[p+1],y_points[p+1]);\
  ctx.closePath();\
  ctx.stroke();\
  }\
  ctx.restore();\
  return;\
 };");
    break;

    case DRAW_LINES:/*  used for userdraw */
fprintf(js_include_file,"\n<!-- draw lines -->\n\
function calc_line(x1,x2,y1,y2){\
 var marge = 2;\
 if(x1 < x2+marge && x1>x2-marge){\
  return [x1,0,x1,ysize];\
 };\
 if(y1 < y2+marge && y1>y2-marge){\
  return [0,y1,xsize,y1];\
 };\
 var Y1 = y1 - (x1)*(y2 - y1)/(x2 - x1);\
 var Y2 = y1 + (xsize - x1)*(y2 - y1)/(x2 - x1);\
 return [0,Y1,xsize,Y2];\
};\
var draw_lines = function(ctx,x_points,y_points,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,use_affine,affine_matrix){\
 ctx.save();\
 var line = new Array(4);\
 if(use_affine == 1 ){ctx.translate(affine_matrix[4],affine_matrix[5]);}\
 if(use_rotate == 1 ){ctx.rotate(angle*Math.PI/180);}\
 ctx.lineWidth = line_width;\
 ctx.strokeStyle=\"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 if(use_dashed == 1){if(ctx.setLineDash){ctx.setLineDash([dashtype0,dashtype1]);}else{ctx.mozDash = [dashtype0,dashtype1];};};\
 for(var p = 0 ; p < x_points.length ; p = p+2 ){\
  line = calc_line(x_points[p],x_points[p+1],y_points[p],y_points[p+1]);\
  ctx.beginPath();\
  ctx.moveTo(line[0],line[1]);\
  ctx.lineTo(line[2],line[3]);\
  ctx.closePath();\
  ctx.stroke();\
  }\
  ctx.restore();\
  return;\
 };");
    break;

    case DRAW_DEMILINES:/*  used for userdraw */
fprintf(js_include_file,"\n<!-- draw demilines -->\n\
function find_inf_point(x1,y1,x2,y2){\
 if(x1<x2+2 && x1>x2-2){if(y1<y2){return [x1,y1,x1,ysize];}else{return [x1,0,x1,y1];};};\
 var rc = (y2 - y1)/(x2 - x1);var q = y1 - (x1)*rc;\
 if( x1 < x2 ){ return [x1,y1,xsize,rc*xsize+q];}else{return [x1,y1,0,q];};\
};\
var draw_demilines = function(ctx,x_points,y_points,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,use_affine,affine_matrix){\
 ctx.save();\
 if(use_affine == 1 ){ctx.translate(affine_matrix[4],affine_matrix[5]);}\
 if(use_rotate == 1 ){ctx.rotate(angle*Math.PI/180);}\
 ctx.lineWidth = line_width;\
 ctx.strokeStyle=\"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 if(use_dashed == 1){if(ctx.setLineDash){ctx.setLineDash([dashtype0,dashtype1]);}else{ctx.mozDash = [dashtype0,dashtype1];};};\
 var pair = new Array(4);\
 for(var p = 0 ; p < x_points.length ; p = p+2 ){\
  pair = find_inf_point(x_points[p],y_points[p],x_points[p+1],y_points[p+1]);\
  ctx.beginPath();\
  ctx.moveTo(pair[0],pair[1]);\
  ctx.lineTo(pair[2],pair[3]);\
  ctx.closePath();\
  ctx.stroke();\
  }\
  ctx.restore();\
  return;\
 };");
    break;

    case DRAW_CROSSHAIRS:/*  used for userdraw */
fprintf(js_include_file,"\n<!-- draw crosshairs  -->\n\
var draw_crosshairs = function(ctx,x_points,y_points,line_width,crosshair_size,stroke_color,stroke_opacity,use_rotate,angle,use_affine,affine_matrix){\
 if(use_affine == 1 ){ctx.translate(affine_matrix[4],affine_matrix[5]);}\
 if(use_rotate == 1 ){ctx.rotate(angle*Math.PI/180);}\
 ctx.lineWidth = line_width;\
 ctx.strokeStyle=\"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 var x1,x2,y1,y2;\
 for(var p = 0 ; p < x_points.length ; p++ ){\
  x1 = x_points[p] - crosshair_size;\
  x2 = x_points[p] + crosshair_size;\
  y1 = y_points[p] - crosshair_size;\
  y2 = y_points[p] + crosshair_size;\
  ctx.beginPath();\
  ctx.moveTo(x1,y1);\
  ctx.lineTo(x2,y2);\
  ctx.closePath();\
  ctx.stroke();\
  ctx.beginPath();\
  ctx.moveTo(x2,y1);\
  ctx.lineTo(x1,y2);\
  ctx.closePath();\
  ctx.stroke();\
 }\
 ctx.restore();\
  return;\
};");
    break;

    case DRAW_RECTS:/*  used for userdraw */
fprintf(js_include_file,"\n<!-- draw rects -->\n\
var draw_rects = function(ctx,x_points,y_points,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,use_affine,affine_matrix){\
 ctx.save();\
 if(use_affine == 1 ){ctx.translate(affine_matrix[4],affine_matrix[5]);}\
 if(use_rotate == 1 ){ctx.rotate(angle*Math.PI/180);}\
 ctx.lineWidth = line_width;\
 ctx.strokeStyle = \"rgba('+stroke_color+','+stroke_opacity+')\";\
 if(use_dashed == 1){if(ctx.setLineDash){ctx.setLineDash([dashtype0,dashtype1]);}else{ctx.mozDash = [dashtype0,dashtype1];}};\
 for(var p = 0 ; p < x_points.length ; p = p + 2){\
  ctx.beginPath();\
  ctx.rect(x_points[p],y_points[p],x_points[p+1]-x_points[p],y_points[p+1]-y_points[p]);\
  ctx.closePath();\
  if(use_filled == 1 ){ctx.fillStyle = \"rgba(\"+fill_color+\",\"+fill_opacity+\")\";ctx.fill();}\
  ctx.stroke();\
 };\
 ctx.restore();\
 return;\
};");
    break;

    case DRAW_ROUNDRECTS:/*  used for userdraw */
fprintf(js_include_file,"\n<!-- draw round rects -->\n\
var draw_roundrects = function(ctx,x_points,y_points,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,use_rotate,angle,use_affine,affine_matrix){\
 ctx.save();\
 if(use_affine == 1 ){ctx.translate(affine_matrix[4],affine_matrix[5]);}\
 if(use_dashed == 1){if(ctx.setLineDash){ctx.setLineDash([dashtype0,dashtype1]);}else{ctx.mozDash = [dashtype0,dashtype1];};};\
 if(use_rotate == 1 ){ctx.rotate(angle*Math.PI/180);}\
 var x,y,w,h,r;\
 for(var p = 0; p < x_points.length; p = p+2){\
  x = x_points[p];y = y_points[p];w = x_points[p+1] - x;h = y_points[p+1] - y;r = parseInt(0.1*w);\
  ctx.beginPath();ctx.moveTo(x + r, y);\
  ctx.lineTo(x + w - r, y);\
  ctx.quadraticCurveTo(x + w, y, x + w, y + r);\
  ctx.lineTo(x + w, y + h - r);\
  ctx.quadraticCurveTo(x + w, y + h, x + w - r, y + h);\
  ctx.lineTo(x + r, y + h);\
  ctx.quadraticCurveTo(x, y + h, x, y + h - r);\
  ctx.lineTo(x, y + r);\
  ctx.quadraticCurveTo(x, y, x + r, y);\
  ctx.closePath();if( use_dashed == 1 ){ctx.setLineDash([dashtype0,dashtype1]);};\
  ctx.strokeStyle =\"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
  if( use_filled == 1 ){ctx.fillStyle =\"rgba(\"+fill_color+\",\"+fill_opacity+\")\";ctx.fill();};\
  ctx.stroke();\
 }\
 ctx.restore();\
};");
    break;

    case DRAW_ELLIPSES:/* not  used for userdraw */
fprintf(js_include_file,"\n<!-- draw ellipses -->\n\
var draw_ellipses = function(canvas_type,x_points,y_points,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,use_rotate,angle,use_affine,affine_matrix){\
 var obj;\
 if( document.getElementById(\"wims_canvas%d\"+canvas_type) ){\
  obj = document.getElementById(\"wims_canvas%d\"+canvas_type);\
 }\
 else\
 {\
  obj = create_canvas%d(canvas_type,xsize,ysize);\
 };\
 var ctx = obj.getContext(\"2d\");\
 ctx.save();\
 if(use_affine == 1 ){ctx.translate(affine_matrix[4],affine_matrix[5]);}\
 if(use_rotate == 1 ){ctx.rotate(angle*Math.PI/180);}\
 var cx,cy,ry,rx;\
 ctx.lineWidth = line_width;\
 if( use_filled == 1 ){ctx.fillStyle =\"rgba(\"+fill_color+\",\"+fill_opacity+\")\";};\
 if(use_dashed == 1){if(ctx.setLineDash){ctx.setLineDash([dashtype0,dashtype1]);}else{ctx.mozDash = [dashtype0,dashtype1];};};\
 ctx.strokeStyle=\"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 for(var p=0;p< x_points.length;p = p+2){\
  ctx.beginPath();\
  cx = x_points[p];cy = y_points[p];rx = 0.25*x_points[p+1];ry = 0.25*y_points[p+1];\
  ctx.translate(cx - rx, cy - ry);\
  ctx.scale(rx, ry);\
  ctx.arc(1, 1, 1, 0, 2 * Math.PI, false);\
  if( use_filled == 1 ){ctx.fill();}\
  ctx.stroke();\
 };\
 ctx.restore();\
};",canvas_root_id,canvas_root_id,canvas_root_id);
    break;

    case DRAW_PATHS: /*  used for userdraw */
fprintf(js_include_file,"\n<!-- draw paths -->\n\
var draw_paths = function(ctx,x_points,y_points,line_width,closed_path,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,use_rotate,angle,use_affine,affine_matrix){\
 ctx.save();\
 if(use_affine == 1 ){ctx.translate(affine_matrix[4],affine_matrix[5]);}\
 if(use_rotate == 1 ){ctx.rotate(angle*Math.PI/180);}\
 ctx.lineWidth = line_width;\
 ctx.lineJoin = \"round\";\
 ctx.strokeStyle=\"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 ctx.beginPath();\
 ctx.moveTo(x_points[0],y_points[0]);\
 for(var p = 1 ; p < x_points.length ; p++ ){ctx.lineTo(x_points[p],y_points[p]);}\
 if(closed_path == 1){ctx.lineTo(x_points[0],y_points[0]);ctx.closePath();}\
 if(use_dashed == 1){if(ctx.setLineDash){ctx.setLineDash([dashtype0,dashtype1]);}else{ctx.mozDash = [dashtype0,dashtype1];};};\
 if(use_filled == 1){ctx.fillStyle = \"rgba(\"+fill_color+\",\"+fill_opacity+\")\";ctx.fill();}\
 ctx.stroke();\
 ctx.restore();\
 return;\
};");

    break;
    case DRAW_ARROWS:/*  used for userdraw */
fprintf(js_include_file,"\n<!-- draw arrows -->\n\
var draw_arrows = function(ctx,x_points,y_points,arrow_head,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,dashtype1,type,use_rotate,angle,use_affine,affine_matrix){\
 ctx.save();\
 if(use_affine == 1 ){ctx.translate(affine_matrix[4],affine_matrix[5]);}\
 if(use_rotate == 1 ){ctx.rotate(angle*Math.PI/180);}\
 ctx.strokeStyle = \"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 ctx.fillStyle = \"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 ctx.lineWidth = line_width;\
 if(use_dashed == 1){if(ctx.setLineDash){ctx.setLineDash([dashtype0,dashtype1]);}else{ctx.mozDash = [dashtype0,dashtype1];};};\
 ctx.lineCap = \"round\";\
 var x1,y1,x2,y2,dx,dy,len;\
 for(var p = 0 ; p < x_points.length - 1 ; p = p +2){\
   ctx.save();\
   x1 = x_points[p];y1 = y_points[p];x2 = x_points[p+1];y2 = y_points[p+1];dx = x2 - x1;dy = y2 - y1;\
   len = Math.sqrt(dx*dx+dy*dy);\
   ctx.translate(x2,y2);\
   ctx.rotate(Math.atan2(dy,dx));\
   ctx.lineCap = \"round\";\
   ctx.beginPath();\
   ctx.moveTo(0,0);\
   ctx.lineTo(-len,0);\
   ctx.closePath();\
   ctx.stroke();\
   ctx.beginPath();\
   ctx.moveTo(0,0);\
   ctx.lineTo(-1*arrow_head,-0.5*arrow_head);\
   ctx.lineTo(-1*arrow_head, 0.5*arrow_head);\
   ctx.closePath();\
   ctx.fill();\
   ctx.restore();\
   if( type == 2 ){\
     ctx.save();\
     ctx.translate(x1,y1);\
     ctx.rotate(Math.atan2(-dy,-dx));\
     ctx.beginPath();\
     ctx.moveTo(0,0);\
     ctx.lineTo(-1*arrow_head,-0.4*arrow_head);\
     ctx.lineTo(-1*arrow_head, 0.4*arrow_head);\
     ctx.closePath();\
     ctx.stroke();\
     ctx.fill();\
     ctx.restore();\
   }\
  }\
  ctx.restore();\
  return;\
};");
    break;

    case DRAW_VIDEO:/* not  used for userdraw */
fprintf(js_include_file,"\n<!-- draw video -->\n\
var draw_video = function(canvas_root_id,x,y,w,h,URL){\
 var canvas_div = document.getElementById(\"canvas_div\"+canvas_root_id);\
 var video_div = document.createElement(\"div\");\
 canvas_div.appendChild(video_div);\
 video_div.style.position = \"absolute\";\
 video_div.style.left = x+\"px\";\
 video_div.style.top = y+\"px\";\
 video_div.style.width = w+\"px\";\
 video_div.style.height = h+\"px\";\
 var video = document.createElement(\"video\");\
 video_div.appendChild(video);\
 video.style.width = w+\"px\";\
 video.style.height = h+\"px\";\
 video.autobuffer = true;\
 video.controls = true;video.autoplay = false;\
 var src = document.createElement(\"source\");\
 src.type = \"video/mp4\";\
 src.src = URL;\
 video.appendChild(src);\
 video.load();\
 return;\
};");
    break;

    case DRAW_AUDIO:/* not used for userdraw */
fprintf(js_include_file,"\n<!-- draw audio -->\n\
var draw_audio = function(canvas_root_id,x,y,w,h,loop,visible,URL1,URL2){\
 var canvas_div = document.getElementById(\"canvas_div\"+canvas_root_id);\
 var audio_div = document.createElement(\"div\");\
 canvas_div.appendChild(audio_div);\
 audio_div.style.position = \"absolute\";\
 audio_div.style.left = x+\"px\";\
 audio_div.style.top = y+\"px\";\
 audio_div.style.width = w+\"px\";\
 audio_div.style.height = h+\"px\";\
 var audio = document.createElement(\"audio\");\
 audio_div.appendChild(audio);\
 audio.setAttribute(\"style\",\"width:\"+w+\"px;height:\"+h+\"px\");\
 audio.autobuffer = true;\
 if(visible == 1 ){ audio.controls = true;audio.autoplay = false;}else{ audio.controls = false;audio.autoplay = true;}\
 if(loop == 1 ){ audio.loop = true;}else{ audio.loop = false;}\
 var src1 = document.createElement(\"source\");\
 src1.type = \"audio/ogg\";\
 src1.src = URL1;\
 audio.appendChild(src1);\
 var src2 = document.createElement(\"source\");\
 src2.type = \"audio/mpeg\";\
 src2.src = URL2;\
 audio.appendChild(src2);\
 audio.load();\
 return;\
};");
    break;

    case DRAW_HTTP:/* not  used for userdraw */
fprintf(js_include_file,"\n<!-- draw http -->\n\
var draw_http = function(canvas_root_id,x,y,w,h,URL){\
 var canvas_div = document.getElementById(\"canvas_div\"+canvas_root_id);\
 var http_div = document.createElement(\"div\");\
 var iframe = document.createElement(\"iframe\");\
 canvas_div.appendChild(http_div);\
 http_div.appendChild(iframe);\
 iframe.src = URL;\
 iframe.setAttribute(\"width\",w);\
 iframe.setAttribute(\"height\",h);\
 return;\
};");
    break;

    case DRAW_XML:
fprintf(js_include_file,"\n<!-- draw xml -->\n\
var draw_xml = function(canvas_root_id,x,y,w,h,mathml,onclick){\
 var canvas_div = document.getElementById(\"canvas_div\"+canvas_root_id);\
 var xml_div = document.createElement(\"div\");\
 canvas_div.appendChild(xml_div);\
 xml_div.innerHTML = mathml;\
 if(onclick != 0){\
  xml_div.onclick = function(){\
   reply[0] = onclick;\
   alert(\"send \"+onclick+\" ?\");\
  };\
 };\
 xml_div.style.position = \"absolute\";\
 xml_div.style.left = x+\"px\";\
 xml_div.style.top = y+\"px\";\
 xml_div.style.width = w+\"px\";\
 xml_div.style.height = h+\"px\";\
 return;\
};"
);
    break;
    case DRAW_SGRAPH:
/*
 xstart = given
 ystart = given
 sgraph(canvas_type,precision,xmajor,ymajor,xminor,yminor,majorcolor,minorcolor,fontfamily)
*/
fprintf(js_include_file,"\n<!-- draw sgraph -->\n\
var draw_sgraph = function(canvas_type,precision,xmajor,ymajor,xminor,yminor,majorcolor,minorcolor,fontfamily,opacity,font_size){\
 var obj;if( document.getElementById(\"wims_canvas%d\"+canvas_type) ){obj = document.getElementById(\"wims_canvas%d\"+canvas_type);}else{ obj = create_canvas%d(canvas_type,xsize,ysize);};\
 var ctx = obj.getContext(\"2d\");\
 ctx.font = fontfamily;\
 var minor_opacity = 0.8*opacity;\
 ctx.clearRect(0,0,xsize,ysize);\
 var zero_x = 0.1*xsize;\
 var zero_y = 0.9*ysize;\
 var snor_x;var snor_y;\
 if( xstart != xmin){\
  snor_x = 0.1*xsize;\
 }\
 else\
 {\
  snor_x = 0;\
  xstart = xmin;\
 };\
 ctx.strokeStyle = \"rgba(\"+majorcolor+\",\"+opacity+\")\";\
 ctx.lineWidth = 2;\
 ctx.beginPath();\
 ctx.moveTo(xsize,zero_y);\
 ctx.lineTo(zero_x,zero_y);\
 ctx.lineTo(zero_x,0);\
 ctx.stroke();\
 ctx.closePath();\
 ctx.beginPath();\
 ctx.moveTo(zero_x,zero_y);\
 ctx.lineTo(zero_x + 0.25*snor_x,zero_y - 0.1*snor_x);\
 ctx.lineTo(zero_x + 0.5*snor_x,zero_y + 0.1*snor_x);\
 ctx.lineTo(zero_x + 0.75*snor_x,zero_y - 0.1*snor_x);\
 ctx.lineTo(zero_x + snor_x,zero_y);\
 ctx.stroke();\
 ctx.closePath();\
 ctx.beginPath();\
 var num = xstart;\
 var flipflop = 1;\
 var step_x = xmajor*(xsize - zero_x - snor_x)/(xmax - xstart);\
 var txtsize;var txt_marge=step_x - 5;\
 for(var x = zero_x+snor_x ; x < xsize;x = x + step_x){\
  txtsize = ctx.measureText(num).width;\
  if( txtsize > txt_marge ){if( flipflop == 1 ){flipflop = 0;}else{flipflop = 1;};};\
  if( flipflop == 1){\
   ctx.fillText(num,x - 0.5*txtsize,zero_y+font_size);\
  }\
  else\
  {\
   ctx.fillText(num,x - 0.5*txtsize,zero_y+2*font_size);\
  }\
  num = num + xmajor;\
 };\
 ctx.stroke();\
 ctx.closePath();\
 ctx.lineWidth = 1;\
 ctx.beginPath();\
 for(var x = zero_x+snor_x ; x < xsize;x = x + step_x){\
   ctx.moveTo(x,zero_y);\
   ctx.lineTo(x,0);\
 };\
 ctx.stroke();\
 ctx.closePath();\
 if( xminor > 1){\
  ctx.lineWidth = 0.5;\
  ctx.beginPath();\
  ctx.strokeStyle = \"rgba(\"+minorcolor+\",\"+minor_opacity+\")\";\
  var minor_step_x = step_x / xminor;\
  var nx;\
  for(var x = zero_x+snor_x; x < xsize;x = x + step_x){\
    num = 1;\
    for(var p = 1 ; p < xminor ; p++){\
     nx = x + num*minor_step_x;\
     ctx.moveTo(nx,zero_y);\
     ctx.lineTo(nx,0);\
     num++;\
    };\
  };\
  ctx.stroke();\
  ctx.closePath();\
  ctx.beginPath();\
  ctx.lineWidth = 2;\
  ctx.strokeStyle = \"rgba(\"+majorcolor+\",\"+opacity+\")\";\
  for(var x = zero_x+snor_x ; x < xsize;x = x + step_x){\
   ctx.moveTo(x,zero_y);ctx.lineTo(x,zero_y - 12);\
  };\
  for(var x = zero_x+snor_x ; x < xsize;x = x + minor_step_x){\
   ctx.moveTo(x,zero_y);ctx.lineTo(x,zero_y - 6);\
  };\
  ctx.stroke();\
  ctx.closePath();\
  ctx.lineWidth = 0.5;\
 };\
 xmin = xstart - (xmajor*(zero_x+snor_x)/step_x);\
 if( ystart != ymin){\
  snor_y = 0.1*ysize;\
 }\
 else\
 {\
  snor_y = 0;\
  ystart = ymin;\
 };\
 ctx.lineWidth = 2;\
 ctx.strokeStyle = \"rgba(\"+majorcolor+\",\"+opacity+\")\";\
 ctx.beginPath();\
 ctx.moveTo(zero_x,zero_y);\
 ctx.lineTo(zero_x - 0.1*snor_y,zero_y - 0.25*snor_y);\
 ctx.lineTo(zero_x + 0.1*snor_y,zero_y - 0.5*snor_y);\
 ctx.lineTo(zero_x - 0.1*snor_y,zero_y - 0.75*snor_y);\
 ctx.lineTo(zero_x,zero_y - snor_y);\
 ctx.stroke();\
 ctx.closePath();\
 ctx.beginPath();\
 ctx.lineWidth = 1;\
 num = ystart;\
 var step_y = ymajor*(zero_y - snor_y)/(ymax - ystart);\
 for(var y = zero_y - snor_y ; y > 0; y = y - step_y){\
  ctx.moveTo(zero_x,y);\
  ctx.lineTo(xsize,y);\
  ctx.fillText(num,zero_x - ctx.measureText(num+\" \").width,parseInt(y+0.2*font_size));\
  num = num + ymajor;\
 };\
 ctx.stroke();\
 ctx.closePath();\
 if( yminor > 1){\
  ctx.lineWidth = 0.5;\
  ctx.beginPath();\
  ctx.strokeStyle = \"rgba(\"+minorcolor+\",\"+minor_opacity+\")\";\
  var minor_step_y = step_y / yminor;\
  var ny;\
  for(var y = 0 ; y < zero_y - snor_y ;y = y + step_y){\
   num = 1;\
   for(var p = 1 ;p < yminor;p++){\
     ny = y + num*minor_step_y;\
     ctx.moveTo(zero_x,ny);\
     ctx.lineTo(xsize,ny);\
     num++;\
    };\
  };\
  ctx.stroke();\
  ctx.closePath();\
  ctx.lineWidth = 2;\
  ctx.beginPath();\
  ctx.strokeStyle = \"rgba(\"+majorcolor+\",\"+opacity+\")\";\
  for(var y = zero_y - snor_y ; y > 0 ;y = y - step_y){\
   ctx.moveTo(zero_x,y);\
   ctx.lineTo(zero_x+12,y);\
  };\
  for(var y = zero_y - snor_y ; y > 0 ;y = y - minor_step_y){\
   ctx.moveTo(zero_x,y);\
   ctx.lineTo(zero_x+6,y);\
  };\
  ctx.stroke();\
  ctx.closePath();\
 };\
 ymin = ystart - (ymajor*(ysize - zero_y + snor_y)/step_y);\
 if( typeof legend%d  !== 'undefined' ){\
  ctx.globalAlpha = 1.0;\
  var y_offset = 2*font_size;\
  var txt;var txt_size;\
  var x_offset = xsize - 2*font_size;\
  var l_length = legend%d.length;var barcolor = new Array();\
  if( typeof legendcolors%d !== 'undefined' ){\
   for(var p = 0 ; p < l_length ; p++){\
    barcolor[p] = legendcolors%d[p];\
   };\
  }else{\
   if( barcolor.length == 0 ){\
    for(var p = 0 ; p < l_length ; p++){\
     barcolor[p] = stroke_color;\
    };\
   };\
  };\
  for(var p = 0; p < l_length; p++){\
   ctx.fillStyle = barcolor[p];\
   txt = legend%d[p];\
   txt_size = ctx.measureText(txt).width;\
   ctx.fillText(legend%d[p],x_offset - txt_size, y_offset);\
   y_offset = parseInt(y_offset + 1.5*font_size);\
  };\
 };\
 if( typeof xaxislabel !== 'undefined' ){\
   ctx.fillStyle = \'#000000\';\
   var txt_size = ctx.measureText(xaxislabel).width + 4 ;\
   ctx.fillText(xaxislabel,xsize - txt_size, zero_y - 7);\
 };\
 if( typeof yaxislabel !== 'undefined'){\
   ctx.save();\
   ctx.fillStyle = \'#000000\';\
   var txt_size = ctx.measureText(yaxislabel).width;\
   ctx.translate(zero_x+8 + font_size,txt_size+font_size);\
   ctx.rotate(-0.5*Math.PI);\
   ctx.fillText(yaxislabel,0,0);\
   ctx.restore();\
 };\
};\n",canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id);
    break;

    case DRAW_GRID:/* not used for userdraw */
fprintf(js_include_file,"\n<!-- draw grid -->\n\
var draw_grid%d = function(canvas_type,precision,stroke_opacity,xmajor,ymajor,xminor,yminor,tics_length,line_width,stroke_color,axis_color,font_size,font_family,use_axis,use_axis_numbering,use_rotate,angle,use_affine,affine_matrix,use_dashed,dashtype0,dashtype1,font_color,fill_opacity){\
var obj;if( document.getElementById(\"wims_canvas%d\"+canvas_type) ){obj = document.getElementById(\"wims_canvas%d\"+canvas_type);}else{obj = create_canvas%d(canvas_type,xsize,ysize);};\
var ctx = obj.getContext(\"2d\");ctx.clearRect(0,0,xsize,ysize);\
if(use_dashed == 1){if(ctx.setLineDash){ctx.setLineDash([dashtype0,dashtype1]);}else{ctx.mozDash = [dashtype0,dashtype1];};};\
ctx.save();\
if( use_affine == 1 ){ctx.translate(affine_matrix[4],affine_matrix[5]);};\
if( use_rotate == 1 ){ctx.translate(x2px(0),y2px(0));ctx.rotate(angle*Math.PI/180);ctx.translate(-1*(x2px(0)),-1*(y2px(0)));};\
var stroke_color = \"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
ctx.fillStyle = \"rgba(\"+font_color+\",\"+1.0+\")\";\
var axis_color = \"rgba(\"+axis_color+\",\"+stroke_opacity+\")\";\
ctx.font = font_family;\
var barcolor = new Array();\
var xstep = xsize*xmajor/(xmax - xmin);\
var ystep = ysize*ymajor/(ymax - ymin);\
var x2step = xstep / xminor;\
var y2step = ystep / yminor;\
var zero_x = x2px(0);;var zero_y = y2px(0);var f_x;var f_y;\
if(xmin < 0 ){ f_x = -1;}else{ f_x = 1;}\
if(ymin < 0 ){ f_y = -1;}else{ f_y = 1;}\
ctx.beginPath();\
ctx.lineWidth = line_width;\
ctx.strokeStyle = stroke_color;\
for(var p = zero_x ; p < xsize; p = p + xstep){\
 ctx.moveTo(p,0);\
 ctx.lineTo(p,ysize);\
};\
for(var p = zero_x ; p > 0; p = p - xstep){\
 ctx.moveTo(p,0);\
 ctx.lineTo(p,ysize);\
};\
for(var p = zero_y ; p < ysize; p = p + ystep){\
 ctx.moveTo(0,p);\
 ctx.lineTo(xsize,p);\
};\
for(var p = zero_y ; p > 0; p = p - ystep){\
 ctx.moveTo(0,p);\
 ctx.lineTo(xsize,p);\
};\
if( typeof xaxislabel !== 'undefined' ){\
 ctx.save();\
 ctx.font = \"italic \"+font_size+\"px Ariel\";\
 var corr =  ctx.measureText(xaxislabel).width;\
 ctx.fillText(xaxislabel,xsize - 1.5*corr,zero_y - tics_length - 0.4*font_size);\
 ctx.restore();\
};\
if( typeof yaxislabel !== 'undefined' ){\
 ctx.save();\
 ctx.font = \"italic \"+font_size+\"px Ariel\";\
 var corr =  ctx.measureText(yaxislabel).width;\
 ctx.translate(zero_x+tics_length + font_size,corr+font_size);\
 ctx.rotate(-0.5*Math.PI);\
 ctx.fillText(yaxislabel,0,0);\
 ctx.restore();\
};\
ctx.stroke();\
ctx.closePath();\
if( use_axis == 1 ){\
 ctx.save();\
 ctx.beginPath();\
 ctx.strokeStyle = stroke_color;\
 ctx.lineWidth = 0.6*line_width;\
 for(var p = zero_x ; p < xsize; p = p + x2step){\
  ctx.moveTo(p,0);\
  ctx.lineTo(p,ysize);\
 };\
 for(var p = zero_x ; p > 0; p = p - x2step){\
  ctx.moveTo(p,0);\
  ctx.lineTo(p,ysize);\
 };\
 for(var p = zero_y ; p < ysize; p = p + y2step){\
  ctx.moveTo(0,p);\
  ctx.lineTo(xsize,p);\
 };\
 for(var p = zero_y ; p > 0; p = p - y2step){\
  ctx.moveTo(0,p);\
  ctx.lineTo(xsize,p);\
 };\
 ctx.stroke();\
 ctx.closePath();\
 ctx.beginPath();\
 ctx.lineWidth = 2*line_width;\
 ctx.strokeStyle = axis_color;\
 ctx.moveTo(0,zero_y);\
 ctx.lineTo(xsize,zero_y);\
 ctx.moveTo(zero_x,0);\
 ctx.lineTo(zero_x,ysize);\
 ctx.stroke();\
 ctx.closePath();\
 ctx.lineWidth = line_width+0.5;\
 ctx.beginPath();\
 for(var p = zero_x ; p < xsize; p = p + xstep){\
  ctx.moveTo(p,zero_y-tics_length);\
  ctx.lineTo(p,zero_y+tics_length);\
 };\
 for(var p = zero_x ; p > 0; p = p - xstep){\
  ctx.moveTo(p,zero_y-tics_length);\
  ctx.lineTo(p,zero_y+tics_length);\
 };\
 for(var p = zero_y ; p < ysize; p = p + ystep){\
  ctx.moveTo(zero_x-tics_length,p);\
  ctx.lineTo(zero_x+tics_length,p);\
 };\
 for(var p = zero_y ; p > 0; p = p - ystep){\
  ctx.moveTo(zero_x-tics_length,p);\
  ctx.lineTo(zero_x+tics_length,p);\
 };\
 for(var p = zero_x ; p < xsize; p = p + x2step){\
  ctx.moveTo(p,zero_y-0.5*tics_length);\
  ctx.lineTo(p,zero_y+0.5*tics_length);\
 };\
 for(var p = zero_x ; p > 0; p = p - x2step){\
  ctx.moveTo(p,zero_y-0.5*tics_length);\
  ctx.lineTo(p,zero_y+0.5*tics_length);\
 };\
 for(var p = zero_y ; p < ysize; p = p + y2step){\
  ctx.moveTo(zero_x-0.5*tics_length,p);\
  ctx.lineTo(zero_x+0.5*tics_length,p);\
 };\
 for(var p = zero_y ; p > 0; p = p - y2step){\
  ctx.moveTo(zero_x-0.5*tics_length,p);\
  ctx.lineTo(zero_x+0.5*tics_length,p);\
 };\
 ctx.stroke();\
 ctx.closePath();\
 ctx.restore();\
};\
if( use_axis_numbering == 1 ){\
 ctx.save();\
 ctx.fillColor = axis_color;\
 ctx.strokeStyle = axis_color;\
 ctx.lineWidth = 2*line_width;\
 ctx.font = font_family;\
 var shift = zero_y+2*font_size;var flip=0;var skip=0;var corr;var cnt;var disp_cnt;var prec;\
 if( x_strings != null ){\
  var len = x_strings.length;if((len/2+0.5)%%2 == 0){ alert(\"xaxis number unpaired:  text missing ! \");return;};\
  ctx.beginPath();\
  for(var p = 0 ; p < len ; p = p+2){\
   var x_nums = x2px(eval(x_strings[p]));\
   var x_text = x_strings[p+1];\
   corr = ctx.measureText(x_text).width;\
   skip = 1.2*corr/xstep;\
   if( zero_y+2*font_size > ysize ){shift = ysize - 2*font_size;};\
   if( skip > 1 ){if(flip == 0 ){flip = 1; shift = shift + font_size;}else{flip = 0; shift = shift - font_size;}};\
   ctx.fillText(x_text,parseInt(x_nums-0.5*corr),shift);\
   ctx.moveTo(x_nums,zero_y - tics_length);\
   ctx.lineTo(x_nums,zero_y + tics_length);\
  };\
  ctx.closePath();\
 }\
 else\
 {\
  skip = 1;cnt = px2x(zero_x);\
  prec = Math.log(precision)/(Math.log(10));\
  var y_basis;if(f_y == 1){ y_basis = ysize }else{ y_basis = zero_y + 1.4*font_size;};\
  for( var p = zero_x ; p < xsize ; p = p+xstep){\
   if(skip == 0 ){\
    disp_cnt = cnt.toFixed(prec);\
    corr = ctx.measureText(disp_cnt).width;\
    skip = parseInt(1.2*corr/xstep);\
    ctx.fillText(disp_cnt,p-0.5*corr,y_basis);\
   }\
   else\
   {\
    skip--;\
   };\
   cnt = cnt + xmajor;\
  };\
  cnt = px2x(zero_x);skip = 1;\
  for( var p = zero_x ; p > 0 ; p = p-xstep){\
   if(skip == 0 ){\
    disp_cnt = cnt.toFixed(prec);\
    corr = ctx.measureText(disp_cnt).width;\
    skip = parseInt(1.2*corr/xstep);\
    ctx.fillText(disp_cnt,p-0.5*corr,y_basis);\
   }\
   else\
   {\
    skip--;\
   };\
   cnt = cnt - xmajor;\
  };\
 };\
 if( y_strings != null ){\
  var len = y_strings.length;if((len/2+0.5)%%2 == 0){ alert(\"yaxis number unpaired:  text missing ! \");return;};\
  ctx.beginPath();\
  for(var p = 0 ; p < len ; p = p+2){\
   var y_nums = y2px(eval(y_strings[p]));\
   var y_text = y_strings[p+1];\
   corr = 2 + tics_length + ctx.measureText(y_text).width;\
   if( corr > zero_x){corr = parseInt(zero_x+2); }\
   ctx.fillText(y_text,zero_x - corr,y_nums + 0.5*font_size);\
   ctx.moveTo(zero_x - tics_length,y_nums);\
   ctx.lineTo(zero_x + tics_length,y_nums);\
  };\
  ctx.closePath();\
 }\
 else\
 {\
  if(f_x == 1){ corr = 1.5*tics_length; }\
  cnt = px2y(zero_y);skip = 1;\
  for( var p = zero_y ; p < ysize ; p = p+ystep){\
   if(skip == 0 ){\
    skip = parseInt(1.4*font_size/ystep);\
    disp_cnt = cnt.toFixed(prec);\
    if(f_x == -1 ){ corr = parseInt(zero_x - (2 + tics_length + ctx.measureText(disp_cnt).width));};\
    ctx.fillText(disp_cnt,parseInt(corr),parseInt(p+(0.4*font_size)));\
   }\
   else\
   {\
    skip--;\
   };\
   cnt = cnt - ymajor;\
  };\
  corr = 0;cnt = px2y(zero_y);skip = 1;\
  if(f_x == 1){ corr = 1.5*tics_length; }\
  for( var p = zero_y ; p > 0 ; p = p-ystep){\
   if(skip == 0 ){\
    skip = parseInt(1.4*font_size/ystep);\
    disp_cnt = cnt.toFixed(prec);\
    if(f_x == -1 ){corr = parseInt(zero_x - (2 + tics_length + ctx.measureText(disp_cnt).width));};\
    ctx.fillText(disp_cnt,parseInt(corr),parseInt(p+(0.4*font_size)));\
   }\
   else\
   {\
    skip--;\
   };\
   cnt = cnt + ymajor;\
  };\
 };\
 ctx.stroke();\
 ctx.restore();\
};\
if( typeof legend0  !== 'undefined' ){\
 ctx.save();\
 ctx.globalAlpha = 1.0;\
 ctx.font = \"bold \"+font_size+\"px Ariel\";\
 var y_offset = 2*font_size;\
 var txt;var txt_size;\
 var x_offset = xsize - 2*font_size;\
 var l_length = legend0.length;\
 if( typeof legendcolors0 !== 'undefined' ){\
  for(var p = 0 ; p < l_length ; p++){\
    barcolor[p] = legendcolors0[p];\
  };\
 }\
 else\
 {\
  if( barcolor.length == 0 ){\
   for(var p = 0 ; p < l_length ; p++){\
    barcolor[p] = stroke_color;\
   };\
  };\
 };\
 for(var p = 0; p < l_length; p++){\
  ctx.fillStyle = barcolor[p];\
  txt = legend0[p];\
  txt_size = ctx.measureText(txt).width;\
  ctx.fillText(legend0[p],x_offset - txt_size, y_offset);\
  y_offset = parseInt(y_offset + 1.5*font_size);\
 };\
 ctx.restore();\
};\
if( typeof barchart_0  !== 'undefined' ){\
 ctx.save();\
 var num_barcharts = 0;\
 var bar_name = eval('barchart_0');\
 while( typeof bar_name !== 'undefined' ){\
    try{ bar_name = eval('barchart_'+num_barcharts);num_barcharts++;}catch(e){break;};\
 };\
 var bar_width = parseInt(0.8*xstep/(num_barcharts));\
 for(var i=0 ; i< num_barcharts ; i++){\
  bar_name = eval('barchart_'+i);\
  var bar_x = new Array();\
  var bar_y = new Array();\
  var lb = bar_name.length;\
  var idx = 0;\
  var dx = parseInt(0.5*i*bar_width);\
  for( var p = 0 ; p < lb ; p = p + 3 ){\
   bar_x[idx] = x2px(bar_name[p]);\
   bar_y[idx] = y2px(bar_name[p+1]);\
   barcolor[idx] = bar_name[p+2];\
   idx++;\
  };\
  ctx.globalAlpha = fill_opacity;\
  ctx.beginPath();\
  for( var p = 0; p < idx ; p++ ){\
   ctx.strokeStyle = barcolor[p];\
   ctx.fillStyle = barcolor[p];\
   ctx.rect(bar_x[p]-0.4*xstep+dx,bar_y[p],bar_width,zero_y - bar_y[p]);\
  };\
  ctx.fill();\
  ctx.stroke();\
  ctx.closePath();\
 };\
 ctx.restore();\
};\
if( typeof linegraph_0 !== 'undefined' ){\
 ctx.save();\
 ctx.globalAlpha = 1.0;\
 var i = 0;\
 var line_name = eval('linegraph_'+i);\
 while ( typeof line_name !== 'undefined' ){\
  ctx.strokeStyle = 'rgba('+line_name[0]+','+stroke_opacity+')';\
  ctx.lineWidth = parseInt(line_name[1]);\
  if(line_name[2] == \"1\"){\
   var d1 = parseInt(line_name[3]);\
   var d2 = parseInt(line_name[4]);\
   if(ctx.setLineDash){ ctx.setLineDash([d1,d2]); } else { ctx.mozDash = [d1,d2];};\
  }\
  else\
  {\
  if(ctx.setLineDash){ctx.setLineDash = null;}\
  if(ctx.mozDash){ctx.mozDash = null;}\
  };\
  var data_x = new Array();\
  var data_y = new Array();\
  var lb = line_name.length;\
  var idx = 0;\
  for( var p = 5 ; p < lb ; p = p + 2 ){\
   data_x[idx] = x2px(line_name[p]);\
   data_y[idx] = y2px(line_name[p+1]);\
   idx++;\
  };\
  for( var p = 0; p < idx ; p++){\
   ctx.beginPath();\
   ctx.moveTo(data_x[p],data_y[p]);\
   ctx.lineTo(data_x[p+1],data_y[p+1]);\
   ctx.stroke();\
   ctx.closePath();\
  };\
  i++;\
  try{ line_name = eval('linegraph_'+i); }catch(e){ break; }\
 };\
 ctx.restore();\
};\
return;\
};",canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id);
    break;

    case DRAW_PIECHART:
fprintf(js_include_file,"\n<!-- draw piecharts -->\n\
function draw_piechart(canvas_type,x_center,y_center,radius, data_color_list,fill_opacity,legend_cnt,font_family){\
 if( document.getElementById(\"wims_canvas%d\"+canvas_type) ){\
  obj = document.getElementById(\"wims_canvas%d\"+canvas_type);\
 }\
 else\
 {\
  obj = create_canvas%d(canvas_type,xsize,ysize);\
 };\
 var ld = data_color_list.length;\
 var sum = 0;\
 var idx = 0;\
 var font_size = parseInt(font_family.replace(/[^0-9\\.]+/g, \"\"));\
 var colors = new Array();\
 var data = new Array();\
 for(var p = 0;p < ld; p = p + 2){\
  data[idx] = parseFloat(data_color_list[p]);\
  sum = sum + data[idx];\
  colors[idx] = data_color_list[p+1];\
  idx++;\
 };\
 var ctx = obj.getContext(\"2d\");\
 ctx.save();\
 var angle;\
 var angle_end = 0;\
 var offset = Math.PI / 2;\
 ctx.globalAlpha = fill_opacity;\
 for(var p=0; p < idx; p++){\
  ctx.beginPath();\
  ctx.fillStyle = colors[p];\
  ctx.moveTo(x_center,y_center);\
  angle = Math.PI * (2 * data[p] / sum);\
  ctx.arc(x_center,y_center, radius, angle_end - offset, angle_end + angle - offset, false);\
  ctx.lineTo(x_center, y_center);\
  ctx.fill();\
  ctx.closePath();\
  angle_end  = angle_end + angle;\
 };\
 if(typeof legend0 !== 'undefined'){\
  var legenda = eval(\"legend\"+legend_cnt);\
  ctx.globalAlpha = 1.0;\
  ctx.font = font_family;\
  var y_offset = font_size; \
  var x_offset = 0;\
  var txt;var txt_size;\
  for(var p = 0; p < idx; p++){\
   ctx.fillStyle = colors[p];\
   txt = legenda[p];\
   txt_size = ctx.measureText(txt).width;\
   if( x_center + radius + txt_size > xsize ){ x_offset =  x_center + radius + txt_size - xsize;} else { x_offset = 0; };\
   ctx.fillText(txt,x_center + radius - x_offset, y_center - radius + y_offset);\
   y_offset = parseInt(y_offset + 1.5*font_size);\
  };\
 };\
 ctx.restore();\
};",canvas_root_id,canvas_root_id,canvas_root_id);

    break;
    case DRAW_ARCS:
fprintf(js_include_file,"\n<!-- draw arcs -->\n\
var draw_arc = function(ctx,xc,yc,r,start,end,line_width,stroke_color,stroke_opacity,use_filled,fill_color,fill_opacity,use_dashed,dashtype0,dashtype1,use_rotate,angle,use_affine,affine_matrix){\
 ctx.save();\
 if( use_dashed == 1){if(ctx.setLineDash){ctx.setLineDash([dashtype0,dashtype1]);}else{if(ctx.mozDash){ ctx.mozDash = [dashtype0,dashtype1];};};};\
 if( use_affine == 1 ){ctx.translate(affine_matrix[4],affine_matrix[5]);};\
 if( use_rotate == 1 ){ctx.rotate(angle*Math.PI/180);};\
 if(end < start){var tmp = end;end = start;start=tmp;};\
 start = 360 - start;\
 end = 360 - end;\
 ctx.lineWidth = line_width;\
 ctx.strokeStyle =  \"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 ctx.fillStyle = \"rgba(\"+fill_color+\",\"+fill_opacity+\")\";\
 ctx.beginPath();\
 ctx.moveTo(xc,yc);\
 ctx.arc(xc, yc, r, start*(Math.PI / 180), end*(Math.PI / 180),true);\
 ctx.lineTo(xc,yc);\
 ctx.closePath();\
 if( use_filled == 1 ){\
  ctx.fill();\
 };\
 ctx.stroke();\
 ctx.restore();\
};");

    break;
    case DRAW_CENTERSTRING:
fprintf(js_include_file,"\n<!-- draw centerstring -->\n\
var draw_centerstring = function(canvas_type,y,font_family,stroke_color,stroke_opacity,text){\
 var obj;\
 if( document.getElementById(\"wims_canvas%d\"+canvas_type) ){\
  obj = document.getElementById(\"wims_canvas%d\"+canvas_type);\
 }\
 else\
 {\
  obj = create_canvas%d(canvas_type,xsize,ysize);\
 };\
 var ctx = obj.getContext(\"2d\");\
 ctx.save();\
 ctx.font = font_family;\
 ctx.fillStyle = \"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 var stringwidth = ctx.measureText(text).width;\
 var x = parseInt((xsize - stringwidth)/2);if( x < 0 ){x = 0;};\
 ctx.fillText(text,x,y2px(y));\
return;\
};",canvas_root_id,canvas_root_id,canvas_root_id);
    break;
    case DRAW_TEXTS:
fprintf(js_include_file,"\n<!-- draw text -->\n\
var draw_text = function(canvas_type,x,y,font_size,font_family,stroke_color,stroke_opacity,angle2,text,use_rotate,angle,use_affine,affine_matrix){\
  var obj;\
  if( document.getElementById(\"wims_canvas%d\"+canvas_type) ){\
   obj = document.getElementById(\"wims_canvas%d\"+canvas_type);\
  }\
  else\
  {\
   obj = create_canvas%d(canvas_type,xsize,ysize);\
  };\
  var ctx = obj.getContext(\"2d\");\
  if(angle2 == 0 && angle != 0){\
   ctx.save();\
   if(use_affine == 1 ){ctx.translate(affine_matrix[4],affine_matrix[5]);}\
   if(use_rotate == 1 ){ctx.rotate(angle*Math.PI/180);}\
  };\
  if( font_family.indexOf('px') != null ){\
   ctx.font = font_family;\
  }\
  else\
  {\
   ctx.font = font_family;\
  };\
  ctx.fillStyle = \"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
  if(angle2 != 0){\
   ctx.save();\
   ctx.translate(x,y);\
   ctx.rotate((360-angle2)*(Math.PI / 180));\
   ctx.fillText(text,0,0);\
   ctx.restore();\
  }else{ctx.fillText(text,x,y);};\
 ctx.restore();\
 return;\
 };",canvas_root_id,canvas_root_id,canvas_root_id);
    break;
    case DRAW_CURVE:
fprintf(js_include_file,"\n<!-- draw curve -->\n\
var draw_curve = function(canvas_type,type,x_points,y_points,line_width,stroke_color,stroke_opacity,use_dashed,dashtype0,use_rotate,angle,use_affine,affine_matrix){\
 var obj;\
 if( document.getElementById(\"wims_canvas%d\"+canvas_type) ){\
  obj = document.getElementById(\"wims_canvas%d\"+canvas_type);\
 }\
 else\
 {\
  obj = create_canvas%d(canvas_type,xsize,ysize);\
 };\
 var ctx = obj.getContext(\"2d\");\
 ctx.save();\
 if(use_affine == 1 ){ctx.translate(affine_matrix[4],affine_matrix[5]);}\
 if(use_rotate == 1 ){ctx.rotate(angle*Math.PI/180);}\
 ctx.beginPath();ctx.lineWidth = line_width;\
 if(use_dashed == 1){if(ctx.setLineDash){ctx.setLineDash([dashtype0,dashtype1]);}else{ctx.mozDash = [dashtype0,dashtype1];};};\
 ctx.strokeStyle = \"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 ctx.moveTo(x2px(x_points[0]),y2px(y_points[0]));\
 for(var p = 1 ; p < x_points.length ; p++){\
  if( y2px(y_points[p]) > -5 && y2px(y_points[p]) < ysize+5 ){\
  ctx.lineTo(x2px(x_points[p]),y2px(y_points[p]));\
  }\
  else\
  {\
   ctx.stroke();\
   ctx.beginPath();\
   p++;\
   ctx.moveTo(x2px(x_points[p]),y2px(y_points[p]));\
  };\
 };\
 ctx.stroke();\
 ctx.restore();\
};",canvas_root_id,canvas_root_id,canvas_root_id);
    break;

    case DRAW_INPUTS:
fprintf(js_include_file,"\n<!-- draw input fields -->\n\
var draw_inputs = function(root_id,input_cnt,x,y,size,readonly,style,value){\
var canvas_div = document.getElementById(\"canvas_div\"+root_id);\
var input = document.createElement(\"input\");\
input.setAttribute(\"id\",\"canvas_input\"+input_cnt);\
input.setAttribute(\"style\",\"position:absolute;left:\"+x+\"px;top:\"+y+\"px;\"+style);\
input.setAttribute(\"size\",size);\
input.setAttribute(\"value\",value);\
if( readonly == 0 || wims_status == \"done\" ){ input.setAttribute(\"readonly\",\"readonly\");if( wims_status == \"done\" ){input.setAttribute(\"value\",\"\");};};\
canvas_div.appendChild(input);};");
    break;

    case DRAW_TEXTAREAS:
fprintf(js_include_file,"\n<!-- draw text area inputfields -->\n\
var draw_textareas = function(root_id,input_cnt,x,y,cols,rows,readonly,style,value){\
var canvas_div = document.getElementById(\"canvas_div\"+root_id);\
var textarea = document.createElement(\"textarea\");\
textarea.setAttribute(\"id\",\"canvas_input\"+input_cnt);\
textarea.setAttribute(\"style\",\"position:absolute;left:\"+x+\"px;top:\"+y+\"px;\"+style);\
textarea.setAttribute(\"cols\",cols);\
textarea.setAttribute(\"rows\",rows);\
textarea.value = value;\
if( readonly == 0 || wims_status == \"done\" ){ textarea.setAttribute(\"readonly\",\"readonly\");if( wims_status == \"done\" ){textarea.value=\"\";};};\
canvas_div.appendChild(textarea);};");
    break;

case DRAW_PIXELS:
fprintf(js_include_file,"\n<!-- draw pixel -->\n\
var draw_setpixel = function(x,y,color,opacity,pixelsize){\
 var canvas = create_canvas%d(10,xsize,ysize);\
 var d = 0.5*pixelsize;\
 var ctx = canvas.getContext(\"2d\");\
 ctx.fillStyle = \"rgba(\"+color+\",\"+opacity+\")\";\
 ctx.clearRect(0,0,xsize,ysize);\
 for(var p=0; p<x.length;p++){\
  ctx.fillRect( x2px(x[p]) - d, y2px(y[p]) - d , pixelsize, pixelsize );\
 };\
 ctx.fill();ctx.stroke();\
};",canvas_root_id);
break;

case DRAW_CLOCK:
fprintf(js_include_file,"\n<!-- begin command clock -->\n\
var clock_canvas = create_canvas%d(%d,xsize,ysize);\
var clock_ctx = clock_canvas.getContext(\"2d\");\
var clock = function(xc,yc,radius,H,M,S,type,interaction,h_color,m_color,s_color,bg_color,fg_color){\
 clock_ctx.clearRect(xc - radius,yc - radius,2*radius,2*radius);\
 clock_ctx.save();\
 clock_ctx.globalAlpha = clock_bg_opacity;\
 this.type = type || 0;\
 this.interaction = interaction || 0;\
 this.H = H;\
 this.M = M;\
 this.S = S;\
 if(this.S == -1){this.S = 59;this.M = this.M - 1;};\
 if(this.M == -1){this.M = 59;this.H = this.H - 1;};\
 if(this.H == -1){this.H = 11;};\
 this.xc = xc || xsize/2;\
 this.yc = yc || ysize/2;\
 this.radius = radius || xsize/4;\
 var font_size = parseInt(0.2*this.radius);\
 this.H_color = h_color || \"blue\";\
 this.M_color = m_color || \"blue\";\
 this.S_color = s_color || \"blue\";\
 this.fg_color = fg_color || \"red\";\
 this.bg_color = bg_color || \"white\";\
 clock_ctx.translate(this.xc,this.yc);\
 clock_ctx.beginPath();\
 clock_ctx.arc(0,0,this.radius,0,2*Math.PI,false);\
 clock_ctx.fillStyle = this.bg_color;\
 clock_ctx.fill();\
 clock_ctx.closePath();\
 clock_ctx.beginPath();\
 clock_ctx.font = font_size+\"px Arial\";\
 clock_ctx.fillStyle = this.fg_color;\
 clock_ctx.textAlign = \"center\";\
 clock_ctx.textBaseline = 'middle';\
 var angle;var x1,y1,x2,y2;\
 var angle_cos;var angle_sin;\
 clock_ctx.globalAlpha = clock_fg_opacity;\
 switch(type){\
 case 0:clock_ctx.beginPath();\
 for(var p = 1; p <= 12 ; p++){\
  angle_cos = this.radius*(Math.cos(p * (Math.PI * 2) / 12));\
  angle_sin = this.radius*(Math.sin(p * (Math.PI * 2) / 12));\
  x1 = 0.8*angle_cos;y1 = 0.8*angle_sin;x2 = angle_cos;y2 = angle_sin;\
  clock_ctx.moveTo(x1,y1);\
  clock_ctx.lineTo(x2,y2);\
 };\
 for(var p = 1; p <= 60 ; p++){\
  angle_cos = this.radius*(Math.cos(p * (Math.PI * 2) / 60));\
  angle_sin = this.radius*(Math.sin(p * (Math.PI * 2) / 60));\
  x1 = 0.9*angle_cos;y1 = 0.9*angle_sin;x2 = angle_cos;y2 = angle_sin;\
  clock_ctx.moveTo(x1,y1);\
  clock_ctx.lineTo(x2,y2);\
 };\
 clock_ctx.closePath();\
 clock_ctx.stroke();\
 break;\
 case 1:\
 for(var p= 1; p <= 12 ; p++){ angle = (p - 3) * (Math.PI * 2) / 12;x1 = 0.9*this.radius*Math.cos(angle);y1 = 0.9*this.radius*Math.sin(angle);clock_ctx.fillText(p, x1, y1);};break;\
 case 2:\
 for(var p= 1; p <= 12 ; p++){ angle = (p - 3) * (Math.PI * 2) / 12;x1 = 0.8*this.radius*Math.cos(angle);y1 = 0.8*this.radius*Math.sin(angle);clock_ctx.fillText(p, x1, y1);};\
 clock_ctx.beginPath();\
 for(var p = 1; p <= 12 ; p++){\
  angle_cos = this.radius*(Math.cos(p * (Math.PI * 2) / 12));\
  angle_sin = this.radius*(Math.sin(p * (Math.PI * 2) / 12));\
  x1 = 0.9*angle_cos;y1 = 0.9*angle_sin;x2 = angle_cos;y2 = angle_sin;\
  clock_ctx.moveTo(x1,y1);\
  clock_ctx.lineTo(x2,y2);\
 };\
 for(var p = 1; p <= 60 ; p++){\
  angle_cos = this.radius*(Math.cos(p * (Math.PI * 2) / 60));\
  angle_sin = this.radius*(Math.sin(p * (Math.PI * 2) / 60));\
  x1 = 0.95*angle_cos;y1 = 0.95*angle_sin;x2 = angle_cos;y2 = angle_sin;\
  clock_ctx.moveTo(x1,y1);\
  clock_ctx.lineTo(x2,y2);\
 };\
 clock_ctx.closePath();\
 clock_ctx.stroke();\
 break;\
 };\
 angle = (this.H - 3 + this.M/60 ) * 2 * Math.PI / 12;\
 clock_ctx.rotate(angle);\
 clock_ctx.beginPath();\
 clock_ctx.moveTo(-3, -2);\
 clock_ctx.lineTo(-3, 2);\
 clock_ctx.lineTo(this.radius * 0.7, 1);\
 clock_ctx.lineTo(this.radius  * 0.7, -1);\
 clock_ctx.fillStyle = this.H_color;\
 clock_ctx.fill();\
 clock_ctx.rotate(-angle);\
 angle = (this.M - 15 + this.S/60) * 2 * Math.PI / 60;\
 clock_ctx.rotate(angle);\
 clock_ctx.beginPath();\
 clock_ctx.moveTo(-3, -2);\
 clock_ctx.lineTo(-3, 2);\
 clock_ctx.lineTo(this.radius  * 0.8, 1);\
 clock_ctx.lineTo(this.radius  * 0.8, -1);\
 clock_ctx.fillStyle = this.M_color;\
 clock_ctx.fill();\
 clock_ctx.rotate(-angle);\
 angle = (this.S - 15) * 2 * Math.PI / 60;\
 clock_ctx.rotate(angle);\
 clock_ctx.beginPath();\
 clock_ctx.moveTo(0,0);\
 clock_ctx.lineTo(this.radius  * 0.95, 0);\
 clock_ctx.lineTo(this.radius  * 0.9, -1);\
 clock_ctx.strokeStyle = this.S_color;\
 clock_ctx.stroke();\
 clock_ctx.restore();\
};",canvas_root_id,CLOCK_CANVAS);
break;

case DRAW_LATTICE:
fprintf(js_include_file,"\n<!-- draw lattice -->\n\
var draw_lattice = function(canvas_type,line_width,x0,y0,dx1,dy1,dx2,dy2,n1,n2,fill_color,fill_opacity,stroke_color,stroke_opacity,use_rotate,angle,use_affine,affine_matrix){\
 var obj;\
 if( document.getElementById(\"wims_canvas%d\"+canvas_type) ){\
  obj = document.getElementById(\"wims_canvas%d\"+canvas_type);\
 }\
 else\
 {\
  obj = create_canvas%d(canvas_type,xsize,ysize);\
 };\
 var ctx = obj.getContext(\"2d\");\
 ctx.save();\
 if(use_affine == 1 ){ctx.translate(affine_matrix[4],affine_matrix[5]);}\
 if(use_rotate == 1 ){ctx.rotate(angle*Math.PI/180);}\
 ctx.fillStyle =\"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 ctx.strokeStyle=\"rgba(\"+stroke_color+\",\"+stroke_opacity+\")\";\
 var radius = line_width;\
 var x = 0;\
 var y = 0;\
 var x_step_px = xsize/(xmax-xmin);\
 var y_step_px = ysize/(ymax-ymin);\
 var xv1 = dx1*x_step_px;\
 var yv1 = dy1*y_step_px;\
 var xv2 = dx2*x_step_px;\
 var yv2 = dy2*y_step_px;\
 for(var p = 0; p < n1 ;p++){\
  x = p*xv1 + x0;\
  y = p*yv1 + y0;\
  for(var c = 0; c < n2 ; c++){\
   ctx.beginPath();\
   ctx.arc(x+c*xv2,y+c*yv2,radius,0,2*Math.PI,false);\
   ctx.fill();\
   ctx.stroke();\
   ctx.closePath();\
  };\
 };\
 ctx.restore();\
 return;\
};",canvas_root_id,canvas_root_id,canvas_root_id);
    break;
case DRAW_XYLOGSCALE:
fprintf(js_include_file,"\n<!-- draw xylogscale -->\n\
var draw_grid%d = function(canvas_type,line_width,major_color,minor_color,major_opacity,minor_opacity,font_size,font_family,font_color,use_axis_numbering,precision){\
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
 ctx.save();\
 var xmarge;var ymarge;var x_e;var y_e;var num;var corr;var xtxt;var ytxt;\
 var x_min = Math.log(xmin)/Math.log(xlogbase);\
 var x_max = Math.log(xmax)/Math.log(xlogbase);\
 var y_min = Math.log(ymin)/Math.log(ylogbase);\
 var y_max = Math.log(ymax)/Math.log(ylogbase);\
 if(use_axis_numbering == 1){\
  ctx.font = font_family;\
  xmarge = ctx.measureText(ylogbase+'^'+y_max.toFixed(0)+' ').width;\
  ymarge = parseInt(1.5*font_size);\
  ctx.save();\
  ctx.fillStyle=\"rgba(255,215,0,0.2)\";\
  ctx.rect(0,0,xmarge,ysize);\
  ctx.rect(0,ysize-ymarge,xsize,ysize);\
  ctx.fill();\
  ctx.restore();\
 }else{xmarge = 0;ymarge = 0;};\
 if( typeof xaxislabel !== 'undefined' ){\
  ctx.save();\
  ctx.font = \"italic \"+font_size+\"px Ariel\";\
  ctx.fillStyle = \"rgba(\"+font_color+\",\"+major_opacity+\")\";\
  corr =  ctx.measureText(xaxislabel).width;\
  ctx.fillText(xaxislabel,xsize - 1.5*corr,ysize - 2*font_size);\
  ctx.restore();\
 };\
 if( typeof yaxislabel !== 'undefined' ){\
  ctx.save();\
  ctx.font = \"italic \"+font_size+\"px Ariel\";\
  ctx.fillStyle = \"rgba(\"+font_color+\",\"+major_opacity+\")\";\
  corr = ctx.measureText(yaxislabel).width;\
  ctx.translate(xmarge+font_size,corr+font_size);\
  ctx.rotate(-0.5*Math.PI);\
  ctx.fillText(yaxislabel,0,0);\
  ctx.restore();\
 };\
 ctx.fillStyle = \"rgba(\"+font_color+\",\"+major_opacity+\")\";\
 ctx.lineWidth = line_width;\
 for(var p = x_min; p <= x_max ; p++){\
  num = Math.pow(xlogbase,p);\
  for(var i = 1 ; i < xlogbase ; i++){\
   x_e = x2px(i*num);\
   if( i == 1 ){\
    ctx.lineWidth = line_width;\
    ctx.strokeStyle=\"rgba(\"+major_color+\",\"+major_opacity+\")\";\
    if( use_axis_numbering == 1 && p > x_min){\
      xtxt = xlogbase+'^'+p.toFixed(0);\
      corr = 0.5*(ctx.measureText(xtxt).width);\
      ctx.fillText(xtxt,x_e - corr,ysize - 4);\
    };\
   }else{\
    ctx.lineWidth = 0.2*line_width;\
    ctx.strokeStyle=\"rgba(\"+minor_color+\",\"+minor_opacity+\")\";\
   };\
   if( x_e >= xmarge ){\
    ctx.beginPath();\
    ctx.moveTo(x_e,0);\
    ctx.lineTo(x_e,ysize - ymarge);\
    ctx.stroke();\
    ctx.closePath();\
   };\
  };\
 };\
 for(var p = y_min; p <= y_max ; p++){\
  num = Math.pow(ylogbase,p);\
  for(var i = 1 ; i < ylogbase ; i++){\
   y_e = y2px(i*num);\
   if( i == 1 ){\
    ctx.lineWidth = line_width;\
    ctx.strokeStyle=\"rgba(\"+major_color+\",\"+major_opacity+\")\";\
    if( use_axis_numbering == 1 && p > y_min){\
     ctx.fillText(ylogbase+'^'+p.toFixed(0),0,y_e);\
    };\
   }else{\
    ctx.lineWidth = 0.2*line_width;\
    ctx.strokeStyle=\"rgba(\"+minor_color+\",\"+minor_opacity+\")\";\
   };\
   ctx.beginPath();\
   ctx.moveTo(xmarge,y_e);\
   ctx.lineTo(xsize,y_e);\
   ctx.stroke();\
   ctx.closePath();\
  };\
 };\
 ctx.restore();\
};",canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id);
    break;

case DRAW_XLOGSCALE:
fprintf(js_include_file,"\n<!-- draw xlogscale -->\n\
var draw_grid%d = function(canvas_type,line_width,major_color,minor_color,major_opacity,minor_opacity,font_size,font_family,font_color,use_axis_numbering,ymajor,yminor,precision){\
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
 ctx.save();\
 ctx.lineWidth = line_width;\
 var prec = Math.log(precision)/Math.log(10);\
 var x_min = Math.log(xmin)/Math.log(xlogbase);\
 var x_max = Math.log(xmax)/Math.log(xlogbase);\
 var y_min = 0;var y_max = ysize;var x_e;var corr;\
 var xtxt;var ytxt;var num;var xmarge;var ymarge;\
 if(use_axis_numbering == 1){\
  ctx.font = font_family;\
  xmarge = ctx.measureText(ymax.toFixed(prec)+' ').width;\
  ymarge = parseInt(1.5*font_size);\
  ctx.save();\
  ctx.fillStyle=\"rgba(255,215,0,0.2)\";\
  ctx.rect(0,0,xmarge,ysize);\
  ctx.rect(0,ysize-ymarge,xsize,ysize);\
  ctx.fill();\
  ctx.restore();\
 }else{xmarge = 0;ymarge = 0;};\
 if( typeof xaxislabel !== 'undefined' ){\
  ctx.save();\
  ctx.font = \"italic \"+font_size+\"px Ariel\";\
  ctx.fillStyle = \"rgba(\"+font_color+\",\"+major_opacity+\")\";\
  corr =  ctx.measureText(xaxislabel).width;\
  ctx.fillText(xaxislabel,xsize - 1.5*corr,ysize - 2*font_size);\
  ctx.restore();\
 };\
 if( typeof yaxislabel !== 'undefined' ){\
  ctx.save();\
  ctx.font = \"italic \"+font_size+\"px Ariel\";\
  ctx.fillStyle = \"rgba(\"+font_color+\",\"+major_opacity+\")\";\
  corr = ctx.measureText(yaxislabel).width;\
  ctx.translate(xmarge+font_size,corr+font_size);\
  ctx.rotate(-0.5*Math.PI);\
  ctx.fillText(yaxislabel,0,0);\
  ctx.restore();\
 };\
 ctx.fillStyle = \"rgba(\"+font_color+\",\"+major_opacity+\")\";\
 ctx.lineWidth = line_width;\
 for(var p = x_min; p <= x_max ; p++){\
  num = Math.pow(xlogbase,p);\
  for(var i = 1 ; i < xlogbase ; i++){\
   x_e = x2px(i*num);\
   if( i == 1 ){\
     ctx.lineWidth = line_width;\
     ctx.strokeStyle=\"rgba(\"+major_color+\",\"+major_opacity+\")\";\
    if( use_axis_numbering == 1 && p > x_min ){\
      xtxt = xlogbase+'^'+p.toFixed(0);\
      corr = 0.5*(ctx.measureText(xtxt).width);\
      ctx.fillText(xtxt,x_e - corr,ysize - 4);\
    };\
   }else{\
    ctx.lineWidth = 0.2*line_width;\
    ctx.strokeStyle=\"rgba(\"+minor_color+\",\"+minor_opacity+\")\";\
   };\
   if( x_e >= xmarge ){\
    ctx.beginPath();\
    ctx.moveTo(x_e,0);\
    ctx.lineTo(x_e,ysize - ymarge);\
    ctx.stroke();\
    ctx.closePath();\
   };\
  };\
 };\
 var stepy = Math.abs(y2px(ymajor) - y2px(0));\
 var minor_step = stepy / yminor;\
 for(var y = 0 ; y < ysize - stepy ; y = y + stepy){\
  ctx.strokeStyle=\"rgba(\"+major_color+\",\"+major_opacity+\")\";\
  ctx.lineWidth = line_width;\
  ctx.beginPath();\
  ctx.moveTo(xmarge,y);\
  ctx.lineTo(xsize,y);\
  ctx.stroke();\
  ctx.closePath();\
  if( use_axis_numbering == 1){\
   ytxt = (px2y(y)).toFixed(prec);\
   ctx.fillText( ytxt,0 ,y + 0.5*font_size );\
  };\
  for(var dy = 1 ; dy < yminor ; dy++){\
   ctx.strokeStyle=\"rgba(\"+minor_color+\",\"+minor_opacity+\")\";\
   ctx.lineWidth = 0.2*line_width;\
   ctx.beginPath();\
   ctx.moveTo(xmarge,y+dy*minor_step);\
   ctx.lineTo(xsize,y+dy*minor_step);\
   ctx.stroke();\
   ctx.closePath();\
  };\
 };\
 ctx.restore();\
};",canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id);
    break;
case DRAW_YLOGSCALE:
fprintf(js_include_file,"\n<!-- draw ylogscale -->\n\
var draw_grid%d = function(canvas_type,line_width,major_color,minor_color,major_opacity,minor_opacity,font_size,font_family,font_color,use_axis_numbering,xmajor,xminor,precision){\
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
 ctx.save();\
 ctx.lineWidth = line_width;\
 var y_min = Math.log(ymin)/Math.log(ylogbase);\
 var y_max = Math.log(ymax)/Math.log(ylogbase);\
 var x_min = 0;var x_max = xsize;var y_s;var y_e;var num;var xmarge;var ymarge;\
 if(use_axis_numbering == 1){\
  ctx.font = font_family;\
  xmarge = ctx.measureText(ylogbase+\"^\"+y_max.toFixed(0)+' ').width;\
  ymarge = 2*font_size;\
  ctx.save();\
  ctx.fillStyle=\"rgba(255,215,0,0.2)\";\
  ctx.rect(0,0,xmarge,ysize);\
  ctx.rect(0,ysize-ymarge,xsize,ysize);\
  ctx.fill();\
  ctx.restore();\
 }else{xmarge = 0;ymarge = 0;};\
 if( typeof xaxislabel !== 'undefined' ){\
  ctx.save();\
  ctx.font = \"italic \"+font_size+\"px Ariel\";\
  ctx.fillStyle = \"rgba(\"+font_color+\",\"+major_opacity+\")\";\
  corr =  ctx.measureText(xaxislabel).width;\
  ctx.fillText(xaxislabel,xsize - 1.5*corr,ysize - 2*font_size);\
  ctx.restore();\
 };\
 if( typeof yaxislabel !== 'undefined' ){\
  ctx.save();\
  ctx.font = \"italic \"+font_size+\"px Ariel\";\
  ctx.fillStyle = \"rgba(\"+font_color+\",\"+major_opacity+\")\";\
  corr = ctx.measureText(yaxislabel).width;\
  ctx.translate(xmarge+font_size,corr+font_size);\
  ctx.rotate(-0.5*Math.PI);\
  ctx.fillText(yaxislabel,0,0);\
  ctx.restore();\
 };\
 ctx.fillStyle = \"rgba(\"+font_color+\",\"+major_opacity+\")\";\
 ctx.lineWidth = line_width;\
 for(var p = y_min; p <= y_max ; p++){\
  num = Math.pow(ylogbase,p);\
  for(var i = 1 ; i < ylogbase ; i++){\
   y_e = y2px(i*num);\
   if( i == 1 ){\
    ctx.lineWidth = line_width;\
    ctx.strokeStyle=\"rgba(\"+major_color+\",\"+major_opacity+\")\";\
    if( use_axis_numbering == 1 && p > y_min){\
     ctx.fillText(ylogbase+'^'+p.toFixed(0),0,y_e);\
    };\
   }else{\
    ctx.lineWidth = 0.2*line_width;\
    ctx.strokeStyle=\"rgba(\"+minor_color+\",\"+minor_opacity+\")\";\
   };\
   ctx.beginPath();\
   ctx.moveTo(xmarge,y_e);\
   ctx.lineTo(xsize,y_e);\
   ctx.stroke();\
   ctx.closePath();\
  };\
 };\
 var stepx = Math.abs(x2px(xmajor) - x2px(0));\
 var minor_step = stepx / xminor;\
 var prec = Math.log(precision)/Math.log(10);\
 var xtxt;var corr;var flip = 0;\
 for(var x = stepx ; x < xsize ; x = x + stepx){\
  ctx.strokeStyle=\"rgba(\"+major_color+\",\"+major_opacity+\")\";\
  ctx.lineWidth = line_width;\
  ctx.beginPath();\
  ctx.moveTo(x,ysize-ymarge);\
  ctx.lineTo(x,0);\
  ctx.stroke();\
  ctx.closePath();\
  if( use_axis_numbering == 1){\
   xtxt = (px2x(x)).toFixed(prec);\
   corr = 0.5*(ctx.measureText(xtxt).width);\
   if(flip == 0 ){flip = 1;ctx.fillText( xtxt,x - corr ,ysize - 0.2*font_size );}else{\
   flip = 0;ctx.fillText( xtxt,x - corr ,ysize - 1.2*font_size );};\
  };\
  for(var dx = 1 ; dx < xminor ; dx++){\
   ctx.strokeStyle=\"rgba(\"+minor_color+\",\"+minor_opacity+\")\";\
   ctx.lineWidth = 0.2*line_width;\
   ctx.beginPath();\
   ctx.moveTo(x+dx*minor_step,ysize - ymarge);\
   ctx.lineTo(x+dx*minor_step,0);\
   ctx.stroke();\
   ctx.closePath();\
  };\
 };\
 ctx.restore();\
};",canvas_root_id,canvas_root_id,canvas_root_id,canvas_root_id);
    break;
    default:break;
   }
  }
 }
  return;
}

void check_string_length(int L){
 if(L<1 || L > MAX_BUFFER-1){
  canvas_error("problem with your arguments to command...");
 }
 return;
}


int get_token(FILE *infile){
	int     c,i=0;
	char    temp[MAX_INT], *input_type;
	char	*line="line",
	*audio="audio",
	*blink="blink",
	*arrowhead="arrowhead",
	*crosshairsize="crosshairsize",
	*crosshair="crosshair",
	*crosshairs="crosshairs",
	*audioobject="audioobject",
	*style="style",
	*mouse="mouse",
	*mousex="mousex",
	*mousey="mousey",
	*mouse_display="display",
	*mouse_degree="mouse_degree",
	*userdraw="userdraw",
	*highlight="highlight",
	*http="http",
	*rays="rays",
	*dashtype="dashtype",
	*dashed="dashed",
	*filled="filled",
	*lattice="lattice",
	*parallel="parallel",
	*segment="segment",
	*segments="segments",
	*dsegment="dsegment",
	*seg="seg",
	*bgimage="bgimage",
	*bgcolor="bgcolor",
	*strokecolor="strokecolor",
	*backgroundimage="backgroundimage",
	*text="text",
	*textup="textup",
	*mouseprecision="mouseprecision",
	*precision="precision",
	*plotsteps="plotsteps",
	*plotstep="plotstep",
	*tsteps="tsteps",
	*curve="curve",
	*dcurve="dcurve",
	*plot="plot",
	*dplot="dplot",
	*levelcurve="levelcurve",
	*fontsize="fontsize",
	*fontcolor="fontcolor",
	*axis="axis",
	*axisnumbering="axisnumbering",
	*axisnumbers="axisnumbers",
	*arrow="arrow",
	*darrow="darrow",
	*arrow2="arrow2",
	*darrow2="darrow2",
	*arrows="arrows",
	*arrows2="arrows2",
	*zoom="zoom",
	*grid="grid",
	*hline="hline",
	*dhline="dhline",
	*drag="drag",
	*horizontalline="horizontalline",
	*vline="vline",
	*dvline="dvline",
	*verticalline="verticalline",
	*triangle="triangle",
	*ftriangle="ftriangle",
	*mathml="mathml",
	*html="html",
	*input="input",
	*clearbutton="clearbutton",
	*inputstyle="inputstyle",
	*textarea="textarea",
	*trange="trange",
	*ranget="ranget",
	*xrange="xrange",
	*yrange="yrange",
	*rangex="rangex",
	*rangey="rangey",
	*polyline="polyline",
	*polylines="polylines",
	*brokenline="brokenline",
	*brokenlines="brokenlines",
	*lines="lines",
	*poly="poly",
	*polygon="polygon",
	*fpolygon="fpolygon",
	*fpoly="fpoly",
	*filledpoly="filledpoly",
	*filledpolygon="filledpolygon",
	*rect="rect",
	*frect="frect",
	*rectangle="rectangle",
	*frectangle="frectangle",
	*square="square",
	*fsquare="fsquare",
	*rects="rects",
	*frects="frects",
	*dline="dline",
	*arc="arc",
	*filledarc="filledarc",
	*size="size",
	*string="string",
	*stringup="stringup",
	*copy="copy",
	*copyresized="copyresized",
	*opacity="opacity",
	*transparent="transparent",
	*fill="fill",
	*point="point",
	*points="points",
	*linewidth="linewidth",
	*circle="circle",
	*circles="circles",
	*fcircle="fcircle",
	*disk="disk",
	*comment="#",
	*end="end",
	*ellipse="ellipse",
	*fellipse="fellipse",
	*rotate="rotate",
	*affine="affine",
	*killaffine="killaffine",
	*fontfamily="fontfamily",
	*fillcolor="fillcolor",
	*clicktile="clicktile",
	*clicktile_colors="clicktile_colors",
	*translation="translation",
	*translate="translate",
	*killtranslation="killtranslation",
	*killtranslate="killtranslate",
	*onclick="onclick",
	*roundrect="roundrect",
	*froundrect="froundrect",
	*roundrectangle="roundrectangle",
	*patternfill="patternfill",
	*hatchfill="hatchfill",
	*diafill="diafill",
	*diamondfill="diamondfill",
	*dotfill="dotfill",
	*gridfill="gridfill",
	*imagefill="imagefill",
	*xlogbase="xlogbase",
	*ylogbase="ylogbase",
	*xlogscale="xlogscale",
	*ylogscale="ylogscale",
	*xylogscale="xylogscale",
	*intooltip="intooltip",
	*replyformat="replyformat",
	*floodfill="floodfill",
	*filltoborder="filltoborder",
	*clickfill="clickfill",
	*setpixel="setpixel",
	*pixels="pixels",
	*pixelsize="pixelsize",
	*clickfillmarge="clickfillmarge",
	*xaxis="xaxis",
	*yaxis="yaxis",
	*xaxistext="xaxistext",
	*yaxistext="yaxistext",
	*piechart="piechart",
	*legend="legend",
	*legendcolors="legendcolors",
	*xlabel="xlabel",
	*ylabel="ylabel",
	*barchart="barchart",
	*linegraph="linegraph",
	*clock="clock",
	*animate="animate",
	*video="video",
	*status="status",
	*nostatus="nostatus",
	*snaptogrid="snaptogrid",
	*xsnaptogrid="xsnaptogrid",
	*ysnaptogrid="ysnaptogrid",
	*userinput_xy="userinput_xy",
	*userinput_function="userinput_function",
	*usertextarea_xy="usertextarea_xy",
	*userinput="userinput",
	*jsmath="jsmath",
	*trace_jscurve="trace_jscurve",
	*setlimits="setlimits",
	*jscurve="jscurve",
	*jsplot="jsplot",
	*sgraph="sgraph",
	*title="title",
	*centerstring="centerstring",
	*xunit="xunit",
	*yunit="yunit",
	*slider="slider",
	*killslider="killslider",
	*angle="angle",
	*halflines="halflines",
	*demilines="demilines",
	*halfline="halfline",
	*demiline="demiline",
	*hlines="hlines",
	*vlines="vlines",
	*functionlabel="functionlabel";

	while(((c = getc(infile)) != EOF)&&(c!='\n')&&(c!=',')&&(c!='=')&&(c!='\r')){
	    if( i == 0 && (c == ' ' || c == '\t') ){
	continue; /* white spaces or tabs allowed before first command identifier */
	    }
	    else
	    {
	if( c == ' ' || c == '\t' ){
	    break;
	}
	else
	{
	    temp[i] = c;
	    if(i > MAX_INT - 2){canvas_error("command string too long !");}
	    i++;
	}
	    }
	    if(temp[0] == '#') break;
	}
	if (c == EOF) finished = 1;

	if (c == '\n' || c == '\r') {
	line_number++;
	if (i == 0) { return EMPTY; }
	} else if (c == EOF) {
	return 0;
	}

	temp[i]='\0';
	input_type=(char*)my_newmem(strlen(temp));
	snprintf(input_type,sizeof(temp),"%s",temp);

	if( strcmp(input_type, size) == 0 ){
	free(input_type);
	return SIZE;
	}
	if( strcmp(input_type, xrange) == 0 ){
	free(input_type);
	return XRANGE;
	}
	if( strcmp(input_type, rangex) == 0 ){
	free(input_type);
	return XRANGE;
	}
	if( strcmp(input_type, trange) == 0 ){
	free(input_type);
	return TRANGE;
	}
	if( strcmp(input_type, ranget) == 0 ){
	free(input_type);
	return TRANGE;
	}
	if( strcmp(input_type, yrange) == 0 ){
	free(input_type);
	return YRANGE;
	}
	if( strcmp(input_type, rangey) == 0 ){
	free(input_type);
	return YRANGE;
	}
	if( strcmp(input_type, linewidth) == 0 ){
	free(input_type);
	return LINEWIDTH;
	}
	if( strcmp(input_type, dashed) == 0 ){
	free(input_type);
	return DASHED;
	}
	if( strcmp(input_type, dashtype) == 0 ){
	free(input_type);
	return DASHTYPE;
	}
	if( strcmp(input_type, axisnumbering) == 0 ){
	free(input_type);
	return AXIS_NUMBERING;
	}
	if( strcmp(input_type, axisnumbers) == 0 ){
	free(input_type);
	return AXIS_NUMBERING;
	}
	if( strcmp(input_type, axis) == 0 ){
	free(input_type);
	return AXIS;
	}
	if( strcmp(input_type, grid) == 0 ){
	free(input_type);
	return GRID;
	}
	if( strcmp(input_type, parallel) == 0 ){
	free(input_type);
	return PARALLEL;
	}
	if( strcmp(input_type, hlines) == 0 ){
	free(input_type);
	return HLINES;
	}
	if( strcmp(input_type, vlines) == 0 ){
	free(input_type);
	return VLINES;
	}
	if( strcmp(input_type, hline) == 0 ||  strcmp(input_type, horizontalline) == 0 ){
	free(input_type);
	return HLINE;
	}
	if( strcmp(input_type, vline) == 0 ||  strcmp(input_type, verticalline) == 0 ){
	free(input_type);
	return VLINE;
	}
	if( strcmp(input_type, line) == 0 ){
	free(input_type);
	return LINE;
	}
	if( strcmp(input_type, segments) == 0 ){
	free(input_type);
	return SEGMENTS;
	}
	if( strcmp(input_type, seg) == 0 ||  strcmp(input_type, segment) == 0 ){
	free(input_type);
	return SEGMENT;
	}
	if( strcmp(input_type, dsegment) == 0 ){
	free(input_type);
	use_dashed = TRUE;
	return SEGMENT;
	}
	if( strcmp(input_type, crosshairsize) == 0 ){
	free(input_type);
	return CROSSHAIRSIZE;
	}
	if( strcmp(input_type, arrowhead) == 0 ){
	free(input_type);
	return ARROWHEAD;
	}
	if( strcmp(input_type, crosshairs) == 0 ){
	free(input_type);
	return CROSSHAIRS;
	}
	if( strcmp(input_type, crosshair) == 0 ){
	free(input_type);
	return CROSSHAIR;
	}
	if( strcmp(input_type, onclick) == 0 ){
	free(input_type);
	return ONCLICK;
	}
	if( strcmp(input_type, drag) == 0 ){
	free(input_type);
	return DRAG;
	}
	if( strcmp(input_type, userdraw) == 0 ){
	free(input_type);
	return USERDRAW;
	}
	if( strcmp(input_type, highlight) == 0 || strcmp(input_type, style) == 0 ){
	free(input_type);
	return STYLE;
	}
	if( strcmp(input_type, fillcolor) == 0 ){
	free(input_type);
	return FILLCOLOR;
	}
	if( strcmp(input_type, strokecolor) == 0 ){
	free(input_type);
	return STROKECOLOR;
	}
	if( strcmp(input_type, filled) == 0  ){
	free(input_type);
	return FILLED;
	}
	if( strcmp(input_type, http) == 0 ){
	free(input_type);
	return HTTP;
	}
	if( strcmp(input_type, rays) == 0 ){
	free(input_type);
	return RAYS;
	}
	if( strcmp(input_type, lattice) == 0 ){
	free(input_type);
	return LATTICE;
	}
	if( strcmp(input_type, bgimage) == 0 ){
	free(input_type);
	return BGIMAGE;
	}
	if( strcmp(input_type, bgcolor) == 0 ){
	free(input_type);
	return BGCOLOR;
	}
	if( strcmp(input_type, backgroundimage) == 0 ){
	free(input_type);
	return BGIMAGE;
	}
	if( strcmp(input_type, text) == 0 ){
	free(input_type);
	return FLY_TEXT;
	}
	if( strcmp(input_type, textup) == 0 ){
	free(input_type);
	return FLY_TEXTUP;
	}
	if( strcmp(input_type, mouse) == 0 ){
	free(input_type);
	return MOUSE;
	}
	if( strcmp(input_type, mousex) == 0 ){
	free(input_type);
	return MOUSEX;
	}
	if( strcmp(input_type, mousey) == 0 ){
	free(input_type);
	return MOUSEY;
	}
	if( strcmp(input_type, mouse_degree) == 0 ){
	free(input_type);
	return MOUSE_DEGREE;
	}
	if( strcmp(input_type, mouse_display) == 0 ){
	free(input_type);
	return MOUSE_DISPLAY;
	}
	if( strcmp(input_type, mouseprecision) == 0 ){
	free(input_type);
	return MOUSE_PRECISION;
	}
	if( strcmp(input_type, precision) == 0 ){
	free(input_type);
	return MOUSE_PRECISION;
	}
	if( strcmp(input_type, curve) == 0 ){
	free(input_type);
	return CURVE;
	}
	if( strcmp(input_type, dcurve) == 0 ){
	use_dashed = TRUE;
	free(input_type);
	return CURVE;
	}
	if( strcmp(input_type, plot) == 0 ){
	free(input_type);
	return CURVE;
	}
	if( strcmp(input_type, dplot) == 0 ){
	use_dashed = TRUE;
	free(input_type);
	return CURVE;
	}
	if( strcmp(input_type, levelcurve) == 0 ){
	free(input_type);
	return LEVELCURVE;
	}
	if( strcmp(input_type, plotsteps) == 0 ){
	free(input_type);
	return PLOTSTEPS;
	}
	if( strcmp(input_type, plotstep) == 0 ){
	free(input_type);
	return PLOTSTEPS;
	}
	if( strcmp(input_type, tsteps) == 0 ){
	free(input_type);
	return PLOTSTEPS;
	}
	if( strcmp(input_type, fontsize) == 0 ){
	free(input_type);
	return FONTSIZE;
	}
	if( strcmp(input_type, fontcolor) == 0 ){
	free(input_type);
	return FONTCOLOR;
	}
	if( strcmp(input_type, arrow2) == 0 ){
	free(input_type);
	return ARROW2;
	}
	if( strcmp(input_type, darrow) == 0 ){
	free(input_type);
	use_dashed = TRUE;
	return ARROW;
	}
	if( strcmp(input_type, darrow2) == 0 ){
	free(input_type);
	use_dashed = TRUE;
	return ARROW2;
	}
	if( strcmp(input_type, arrows2) == 0 ){
	free(input_type);
	return ARROWS2;
	}
	if( strcmp(input_type, arrows) == 0 ){
	free(input_type);
	return ARROWS;
	}
	if( strcmp(input_type, arrow) == 0 ){
	free(input_type);
	return ARROW;
	}
	if( strcmp(input_type, zoom) == 0 ){
	free(input_type);
	return ZOOM;
	}
	if( strcmp(input_type, triangle) == 0 ){
	free(input_type);
	return TRIANGLE;
	}
	if( strcmp(input_type, ftriangle) == 0 ){
	free(input_type);
	use_filled = TRUE;
	return TRIANGLE;
	}
	if( strcmp(input_type, input) == 0 ){
	free(input_type);
	return INPUT;
	}
	if( strcmp(input_type, inputstyle) == 0 ){
	free(input_type);
	return INPUTSTYLE;
	}
	if( strcmp(input_type, textarea) == 0 ){
	free(input_type);
	return TEXTAREA;
	}
	if( strcmp(input_type, mathml) == 0 ){
	free(input_type);
	return MATHML;
	}
	if( strcmp(input_type, html) == 0 ){
	free(input_type);
	return MATHML;
	}
	if( strcmp(input_type, fontfamily) == 0 ){
	free(input_type);
	return FONTFAMILY;
	}
	if( strcmp(input_type, polyline) == 0 || strcmp(input_type, polylines) == 0 || strcmp(input_type, brokenline) == 0  || strcmp(input_type, brokenlines) == 0  ){
	free(input_type);
	return POLYLINE;
	}
	if( strcmp(input_type, lines) == 0 ){
	free(input_type);
	return LINES;
	}
	if( strcmp(input_type, frects) == 0 ){
	free(input_type);
	use_filled = TRUE;
	return RECTS;
	}
	if( strcmp(input_type, rects) == 0 ){
	free(input_type);
	return RECTS;
	}
	if( strcmp(input_type, rect) == 0  ||  strcmp(input_type, rectangle) == 0 ){
	free(input_type);
	return RECT;
	}
	if( strcmp(input_type, roundrect) == 0  ||  strcmp(input_type, roundrectangle) == 0 ){
	free(input_type);
	return ROUNDRECT;
	}
	if( strcmp(input_type, froundrect) == 0 ){
	free(input_type);
	use_filled = TRUE;
	return ROUNDRECT;
	}
	if( strcmp(input_type, square) == 0 ){
	free(input_type);
	return SQUARE;
	}
	if( strcmp(input_type, fsquare) == 0 ){
	free(input_type);
	use_filled = TRUE;
	return SQUARE;
	}
	if( strcmp(input_type, dline) == 0 ){
	use_dashed = TRUE;
	free(input_type);
	return LINE;
	}
	if( strcmp(input_type, dvline) == 0 ){
	use_dashed = TRUE;
	free(input_type);
	return VLINE;
	}
	if( strcmp(input_type, dhline) == 0 ){
	use_dashed = TRUE;
	free(input_type);
	return HLINE;
	}
	if( strcmp(input_type, frect) == 0 || strcmp(input_type, frectangle) == 0 ){
	use_filled = TRUE;
	free(input_type);
	return RECT;
	}
	if( strcmp(input_type, circles) == 0 ){
	free(input_type);
	return CIRCLES;
	}
	if( strcmp(input_type, fcircle) == 0  ||  strcmp(input_type, disk) == 0 ){
	use_filled = TRUE;
	free(input_type);
	return CIRCLE;
	}
	if( strcmp(input_type, circle) == 0 ){
	free(input_type);
	return CIRCLE;
	}
	if( strcmp(input_type, point) == 0 ){
	free(input_type);
	return POINT;
	}
	if( strcmp(input_type, points) == 0 ){
	free(input_type);
	return POINTS;
	}
	if( strcmp(input_type, filledarc) == 0 ){
	use_filled = TRUE;
	free(input_type);
	return ARC;
	}
	if( strcmp(input_type, arc) == 0 ){
	free(input_type);
	return ARC;
	}
	if( strcmp(input_type, poly) == 0 ||  strcmp(input_type, polygon) == 0 ){
	free(input_type);
	return POLY;
	}
	if( strcmp(input_type, fpoly) == 0 ||  strcmp(input_type, filledpoly) == 0 || strcmp(input_type,filledpolygon) == 0  || strcmp(input_type,fpolygon) == 0  ){
	use_filled = TRUE;
	free(input_type);
	return POLY;
	}
	if( strcmp(input_type, ellipse) == 0){
	free(input_type);
	return ELLIPSE;
	}
	if( strcmp(input_type, fill) == 0 ){
	free(input_type);
	return FLOODFILL;
	}
	if( strcmp(input_type, string) == 0 ){
	free(input_type);
	return STRING;
	}
	if( strcmp(input_type, stringup) == 0 ){
	free(input_type);
	return STRINGUP;
	}
	if( strcmp(input_type, opacity) == 0 ){
	free(input_type);
	return OPACITY;
	}
	if( strcmp(input_type, comment) == 0){
	free(input_type);
	return COMMENT;
	}
	if( strcmp(input_type, end) == 0){
	free(input_type);
	return END;
	}
	if( strcmp(input_type, fellipse) == 0){
	free(input_type);
	use_filled = TRUE;
	return ELLIPSE;
	}
	if( strcmp(input_type, blink) == 0 ){
	free(input_type);
	return BLINK;
	}
	if( strcmp(input_type, clearbutton) == 0){
	free(input_type);
	return CLEARBUTTON;
	}
	if( strcmp(input_type, translation) == 0 ||  strcmp(input_type, translate) == 0  ){
	free(input_type);
	return TRANSLATION;
	}
	if( strcmp(input_type, killtranslation) == 0 ||  strcmp(input_type, killtranslate) == 0){
	free(input_type);
	return KILLTRANSLATION;
	}
	if( strcmp(input_type, rotate) == 0){
	free(input_type);
	return ROTATE;
	}
	if( strcmp(input_type, affine) == 0){
	free(input_type);
	return AFFINE;
	}
	if( strcmp(input_type, killaffine) == 0){
	free(input_type);
	return KILLAFFINE;
	}
	if( strcmp(input_type, audio) == 0 ){
	free(input_type);
	return AUDIO;
	}
	if( strcmp(input_type, audioobject) == 0 ){
	free(input_type);
	return AUDIOOBJECT;
	}
	if( strcmp(input_type, slider) == 0 ){
	free(input_type);
	return SLIDER;
	}
	if( strcmp(input_type, killslider) == 0 ){
	free(input_type);
	return KILLSLIDER;
	}
	if( strcmp(input_type, copy) == 0 ){
	free(input_type);
	return COPY;
	}
	if( strcmp(input_type, copyresized) == 0 ){
	free(input_type);
	return COPYRESIZED;
	}
	if( strcmp(input_type, patternfill) == 0 ){
	free(input_type);
	return PATTERNFILL;
	}
	if( strcmp(input_type, hatchfill) == 0 ){
	free(input_type);
	return HATCHFILL;
	}
	if( strcmp(input_type, diafill) == 0  || strcmp(input_type, diamondfill) == 0  ){
	free(input_type);
	return DIAMONDFILL;
	}
	if( strcmp(input_type, dotfill) == 0 ){
	free(input_type);
	return DOTFILL;
	}
	if( strcmp(input_type, gridfill) == 0 ){
	free(input_type);
	return GRIDFILL;
	}
	if( strcmp(input_type, imagefill) == 0 ){
	free(input_type);
	return IMAGEFILL;
	}
	if( strcmp(input_type, clicktile_colors) == 0 ){
	free(input_type);
	return CLICKTILE_COLORS;
	}
	if( strcmp(input_type, clicktile) == 0 ){
	free(input_type);
	return CLICKTILE;
	}
	if( strcmp(input_type, xlogscale) == 0 ){
	free(input_type);
	return XLOGSCALE;
	}
	if( strcmp(input_type, ylogscale) == 0 ){
	free(input_type);
	return YLOGSCALE;
	}
	if( strcmp(input_type, xylogscale) == 0 ){
	free(input_type);
	return XYLOGSCALE;
	}
	if( strcmp(input_type, ylogscale) == 0 ){
	free(input_type);
	return YLOGSCALE;
	}
	if( strcmp(input_type, xlogbase) == 0 ){
	free(input_type);
	return XLOGBASE;
	}
	if( strcmp(input_type, ylogbase) == 0 ){
	free(input_type);
	return YLOGBASE;
	}
	if( strcmp(input_type, intooltip) == 0 ){
	free(input_type);
	return INTOOLTIP;
	}
	if( strcmp(input_type,video) == 0 ){
	free(input_type);
	return VIDEO;
	}
	if( strcmp(input_type,floodfill) == 0 || strcmp(input_type,fill) == 0 ){
	free(input_type);
	return FLOODFILL;
	}
	if( strcmp(input_type,filltoborder) == 0 ){
	free(input_type);
	return FILLTOBORDER;
	}
	if( strcmp(input_type,clickfill) == 0 ){
	free(input_type);
	return CLICKFILL;
	}
	if( strcmp(input_type, replyformat) == 0 ){
	free(input_type);
	return REPLYFORMAT;
	}
	if( strcmp(input_type, pixelsize) == 0 ){
	free(input_type);
	return PIXELSIZE;
	}
	if( strcmp(input_type, setpixel) == 0 ){
	free(input_type);
	return SETPIXEL;
	}
	if( strcmp(input_type, pixels) == 0 ){
	free(input_type);
	return PIXELS;
	}
	if( strcmp(input_type, clickfillmarge) == 0 ){
	free(input_type);
	return CLICKFILLMARGE;
	}
	if( strcmp(input_type, xaxis) == 0 || strcmp(input_type, xaxistext) == 0 ){
	free(input_type);
	return X_AXIS_STRINGS;
	}
	if( strcmp(input_type, yaxis) == 0  ||  strcmp(input_type, yaxistext) == 0 ){
	free(input_type);
	return Y_AXIS_STRINGS;
	}
	if( strcmp(input_type, piechart) == 0  ){
	free(input_type);
	return PIECHART;
	}
	if( strcmp(input_type, barchart) == 0  ){
	free(input_type);
	return BARCHART;
	}
	if( strcmp(input_type, linegraph) == 0  ){
	free(input_type);
	return LINEGRAPH;
	}
	if( strcmp(input_type, clock) == 0  ){
	free(input_type);
	return CLOCK;
	}
	if( strcmp(input_type, legend) == 0  ){
	free(input_type);
	return LEGEND;
	}
	if( strcmp(input_type, legendcolors) == 0  ){
	free(input_type);
	return LEGENDCOLORS;
	}
	if( strcmp(input_type, xlabel) == 0  ){
	free(input_type);
	return XLABEL;
	}
	if( strcmp(input_type, ylabel) == 0  ){
	free(input_type);
	return YLABEL;
	}
	if( strcmp(input_type, animate) == 0  ){
	free(input_type);
	return ANIMATE;
	}
	/* these are bitmap related flydraw commmands...must be removed. eventually */
	if( strcmp(input_type, transparent) == 0 ){
	free(input_type);
	return TRANSPARENT;
	}
	if( strcmp(input_type, status) == 0 || strcmp(input_type, nostatus) == 0 ){
	free(input_type);
	return STATUS;
	}
	if( strcmp(input_type, snaptogrid) == 0 ){
	free(input_type);
	return SNAPTOGRID;
	}
	if( strcmp(input_type, xsnaptogrid) == 0 ){
	free(input_type);
	return XSNAPTOGRID;
	}
	if( strcmp(input_type, ysnaptogrid) == 0 ){
	free(input_type);
	return YSNAPTOGRID;
	}
	if( strcmp(input_type, userinput_xy) == 0 ){
	free(input_type);
	return USERINPUT_XY;
	}
	if( strcmp(input_type, userinput_function) == 0 ){
	free(input_type);
	return USERINPUT_FUNCTION;
	}
	if( strcmp(input_type, usertextarea_xy) == 0 ){
	free(input_type);
	return USERTEXTAREA_XY;
	}
	if( strcmp(input_type, userinput) == 0 ){
	free(input_type);
	return USERINPUT;
	}
	if( strcmp(input_type, sgraph) == 0 ){
	free(input_type);
	return SGRAPH;
	}
	if( strcmp(input_type, jsmath) == 0 ){
	free(input_type);
	return JSMATH;
	}
	if( strcmp(input_type, trace_jscurve) == 0 ){
	free(input_type);
	return TRACE_JSCURVE;
	}
	if( strcmp(input_type, jscurve) == 0  ||  strcmp(input_type, jsplot) == 0 ){
	free(input_type);
	return JSCURVE;
	}
	if( strcmp(input_type, centerstring) == 0 || strcmp(input_type, title) == 0 ){
	free(input_type);
	return CENTERSTRING;
	}
	if( strcmp(input_type, setlimits) == 0 ){
	free(input_type);
	return SETLIMITS;
	}
	if( strcmp(input_type, xunit) == 0 ){
	free(input_type);
	return XUNIT;
	}
	if( strcmp(input_type, yunit) == 0 ){
	free(input_type);
	return YUNIT;
	}
	if( strcmp(input_type, angle) == 0 ){
	free(input_type);
	return ANGLE;
	}
	if( strcmp(input_type, halflines) == 0 || strcmp(input_type, demilines) == 0  ){
	free(input_type);
	return HALFLINES;
	}
	if( strcmp(input_type, halfline) == 0 || strcmp(input_type, demiline) == 0  ){
	free(input_type);
	return HALFLINE;
	}
	if( strcmp(input_type, functionlabel) == 0 ){
	free(input_type);
	return FUNCTION_LABEL;
	}
	free(input_type);
	ungetc(c,infile);
	return 0;
}

