#include <assert.h>
#include "../../Lib/libwims.h"
#define MAX_INT		128
#define MAX_BUFFER 16384
#define MAX_COLOR_STRING	32
#define MAX_JS_FUNCTIONS 64

/* the commmand / keyword name collecton */
#define END 		-1
#define COMMENT 	-2
#define SIZE 		1
#define XRANGE 		2
#define YRANGE 		3
#define FONTFAMILY 	4
#define MATHML 		5
#define INPUT 		6
#define TEXTAREA 	7
#define LINEWIDTH 	8
#define POLYLINE 	9
#define POLY 		10
#define SEGMENT		15
#define LINE 		16
#define DLINE 		17
#define RECT 		18
#define ARC 		19
#define NEW 		20
#define STRING 		21
#define STRINGUP 	22
#define COPY	 	23
#define COPYRESIZED 	24
#define TRANSPARENT 	25
#define POINT 		26
#define CIRCLE 		27
#define GETPIXEL 	28
#define SQUARE 		29
#define ELLIPSE 	31
#define ROTATE 		32
#define TYPE 		33
#define QUALITY 	34
#define INPUTSTYLE 	35
#define POINTS 		36
#define TRIANGLE 	37
#define HLINE		38
#define VLINE		39
#define GRID		40
#define ZOOM		41
#define ARROW		42
#define DARROW		43
#define AXIS		44
#define FONTSIZE	46
#define	CURVE		50
#define PLOTSTEPS	51
#define TRANGE		53
#define MOUSE_PRECISION 54
#define FLY_TEXT	55
#define FLY_TEXTUP	56
#define BGIMAGE		57
#define DASHED		58
#define PARALLEL	59
#define LATTICE		60
#define OPACITY		61
#define AXIS_NUMBERING	62
#define RAYS		63
#define OUTPUT		64
#define CLOCK		65
#define STYLE		66
#define USERDRAW	67
#define MOUSE		68
#define AUDIO		69
#define AUDIOOBJECT	70
#define STOP		71
#define RESTART		72
#define FILLCOLOR	73
#define CUBE		74
#define CLEARBUTTON	75
#define ONCLICK		76
#define CROSSHAIR	77
#define CROSSHAIRS	78
#define BLINK		79
#define DASHTYPE	80
#define HTML		81
#define CROSSHAIRSIZE	82
#define ARROWHEAD	83
#define DRAG		84
#define HTTP		85
#define SLIDER		86
#define CLICKTILE	88
#define CLICKTILE_COLORS	89
#define TRANSLATION	90
#define KILLTRANSLATION	91
#define ARROW2		92
#define DARROW2		93
#define SVGCODE		95
#define ROUNDRECT	96
#define HATCHFILL	97
#define PATTERNFILL	98
#define DIAMONDFILL	99
#define DOTFILL		100
#define GRIDFILL	101
#define IMAGEFILL	102
#define FILL		103
#define FILLED		104
#define XYLOGSCALE	105
#define XLOGSCALE	106
#define YLOGSCALE	107
#define XLOGBASE	108
#define INTOOLTIP	109
#define REPLYFORMAT	110
#define VIDEO		111
#define BGCOLOR		112
#define FLOODFILL	113
#define FILLTOBORDER	114
#define SETPIXEL	117
#define PIXELS		118
#define PIXELSIZE	119
#define X_AXIS_STRINGS	121
#define Y_AXIS_STRINGS	122
#define FONTCOLOR	123
#define PIECHART	124
#define LEGEND		125
#define BARCHART	126
#define LINEGRAPH	127
#define STROKECOLOR	128
#define XLABEL		129
#define YLABEL		130
#define LEGENDCOLORS	131
#define ANIMATE		132
#define STATUS		133
#define SNAPTOGRID	134
#define XSNAPTOGRID	135
#define YSNAPTOGRID	136
#define USERINPUT_XY	137
#define USERTEXTAREA_XY	138
#define SGRAPH		139
#define YLOGBASE	140
#define AFFINE		141
#define KILLAFFINE	142
#define LEVELCURVE	143
#define JSMATH		144
#define TRACE_JSCURVE	145
#define SETLIMITS	146
#define JSCURVE		147
#define CENTERSTRING	148
#define MOUSEX		149
#define MOUSEY		150
#define MOUSE_DEGREE	151
#define MOUSE_DISPLAY	152
#define XUNIT		153
#define YUNIT		154
#define KILLSLIDER	155
#define ANGLE		156
#define USERINPUT_FUNCTION 157
#define USERINPUT	158
#define HALFLINE	159
#define FUNCTION_LABEL	160
#define SEGMENTS	161
#define ARROWS		162
#define CIRCLES		163
#define ARROWS2		164
#define LINES		165
#define RECTS		166
#define HALFLINES	167
#define HLINES		168
#define VLINES		169
#define ROUNDRECTS	170
#define BEZIER		171
#define SNAPTOPOINTS	172
#define SLIDER_X	173
#define SLIDER_Y	174
#define SNAPTOFUNCTION  175
#define MULTIDRAW	176
#define MULTILINEWIDTH	177
#define MULTISTROKECOLORS	178
#define MULTISTROKEOPACITY	179
#define MULTIFILLCOLORS	180
#define MULTIFILLOPACITY	181
#define MULTIFILL	182
#define MULTILABEL	183
#define MULTIDASH	184
#define MULTISNAPTOGRID 185
#define MULTIUSERINPUT  186
#define PROTRACTOR	187
#define RULER		188
#define TRIANGLES 	189
#define POPUP		190
#define X_AXIS_STRINGS_UP 191
#define CURSOR		192
#define XERRORBARS	193
#define YERRORBARS	194
#define BOXPLOT		195
#define BOXPLOTDATA	196
#define USERBOXPLOT	197
#define USERBOXPLOTDATA	198
#define ROTATION_CENTER 199
#define KILLROTATE	200
#define CANVASTYPE	201
#define NOXAXIS		202
#define NOYAXIS		203

/* the draw_function collection */
#define DRAW_GRID	0
#define DRAW_SEGMENTS	1
#define DRAW_CROSSHAIRS	2
#define DRAW_RECTS	3
#define DRAW_ROUNDRECTS	4
#define DRAW_ARROWS	6
#define DRAW_GRIDFILL	7
#define DRAW_XML	8
#define DRAW_CIRCLES	9
#define DRAW_ARCS	10
#define DRAW_ELLIPSES	11
#define DRAW_TEXTS	12
#define DRAW_CURVE	13
#define DRAW_PATHS	14
#define DRAW_LATTICE	15
#define DRAW_INPUTS	16
#define DRAW_TEXTAREAS	17
#define DRAW_HTTP	18
#define DRAW_AUDIO	19
#define DRAW_VIDEO	20
#define DRAW_DOTFILL	21
#define DRAW_HATCHFILL	22
#define DRAW_IMAGEFILL  23
#define DRAW_FLOODFILL	24
#define DRAW_FILLTOBORDER	25
#define DRAW_PIXELS	26
#define DRAW_POLY	27
#define DRAW_LINES	28
#define DRAW_PIECHART	29
#define DRAW_CLOCK	30
#define DRAW_EXTERNAL_IMAGE	32
#define DRAW_DIAMONDFILL	33
#define DRAW_SGRAPH	34
#define DRAW_POLYLINE	35
#define DRAW_YLOGSCALE	36
#define DRAW_XLOGSCALE	37
#define DRAW_XYLOGSCALE	38
#define DRAW_CENTERSTRING 39
#define DRAW_JSFUNCTION	40
#define DRAW_DEMILINES	41
#define DRAW_BEZIER	42
#define DRAW_BOXPLOT	43
#define DRAW_JSBOXPLOT  44
#define JS_FIND_ANGLE	45


#define EXTERNAL_IMAGE_CANVAS 0 /* this is created first !!! in order to draw on it */
#define BG_CANVAS	1
#define STATIC_CANVAS	2
#define MOUSE_CANVAS	3
#define GRID_CANVAS	4
#define DRAG_CANVAS	5
#define DRAW_CANVAS	6
#define TEXT_CANVAS	7
#define CLOCK_CANVAS	8
#define ANIMATE_CANVAS	9
#define TRACE_CANVAS	10
#define JSPLOT_CANVAS	111 /* JSPLOT_canvas will be increased with every added inputfield... 13,14,14... should not conflict with other images*/
#define FILL_CANVAS	12
#define USERDRAW_JSPLOT 13 /* USERDRAW_JSPLOT will be increased with every added inputfield... 13,14,14... should not conflict with other images*/

#ifndef STD_H
#define STD_H

#ifndef bool
#define bool            char
#endif
#ifndef TRUE
#define TRUE            1
#endif
#ifndef FALSE
#define FALSE           0
#endif

#endif

void add_drag_code(FILE *js_include_file,int canvas_cnt,int canvas_root_id);
void add_trace_js_mouse(FILE *js_include_file,int canvas_cnt,int canvas_root_id,char *stroke_color,char *jsmath,int font_size,double stroke_opacity,int line_width,int crosshair_size,char *input_style);
void add_setlimits(FILE *js_include_file, int canvas_root_id,int font_size,char *input_style);
void add_safe_eval(FILE *js_include_file);
void add_to_js_math(FILE *js_include_file);
void add_calc_y(FILE *js_include_file,int canvas_root_id,char *jsmath,int font_size,char *input_style);
void add_jsplot(FILE *js_include_file,int canvas_root_id);
void add_slider(FILE *js_include_file, int canvas_root_id,double v1,double v2,int width,int height,int type,char *label,int slider_cnt,char *stroke_color,char *fill_color,int line_width,double opacity,char *font_family,char *font_color,int use_slider_display);
void add_slider_display(FILE *js_include_file, int canvas_root_id,int precision,int font_size,char *font_color,double stroke_opacity);
void add_xyslider(FILE *js_include_file, int canvas_root_id,double v1,double v2,int width,int height,int type,char *label,int slider_cnt,char *stroke_color,char *fill_color,int line_width,double opacity,char *font_family,char *font_color,int use_slider_display);
void *my_newmem(size_t size);
void canvas_error(char *msg);
char *eval(int xsize,int ysize,char *fun,double xmin,double xmax,double ymin,double ymax,int xsteps,int precision);
char *eval_parametric(int xsize,int ysize,char *fun1,char* fun2,double xmin,double xmax,double ymin,double ymax, double tmin,double tmax,int plotsteps,int precision);
char *eval_levelcurve(int xsize,int ysize,char *fun,double xmin,double xmax,double ymin,double ymax,int plotsteps,int precision,double level);

char *double_xy2js_array(double xy[],int len,int decimals);
int find_number_of_digits(int i);
int x2px(double x);
int y2px(double y);

void add_clear_button(FILE *js_include_file,int canvas_root_id,char *input_style,char *button_text);
void add_js_inputs(FILE *js_include_file,int canvas_root_id,int num,int input_cnt,char *input_style,int line_width);
void add_js_mouse(FILE *js_include_file,int canvas_cnt,int canvas_root_id,int precision,char *stroke_color,int font_size,double stroke_opacity,int type);
void add_js_points(FILE *js_include_file,int num,char *draw_type,int line_width, int radius ,char *stroke_color,double stroke_opacity,int use_filled,char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_circles(FILE *js_include_file,int num,char *draw_type, int line_width, int radius , char *stroke_color,double stroke_opacity,int use_filled,char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_segments(FILE *js_include_file,int num,char *draw_type,int line_width, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_demilines(FILE *js_include_file,int num,char *draw_type,int line_width, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_polyline(FILE *js_include_file,char *draw_type,int line_width, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_lines(FILE *js_include_file,int num,char *draw_type,int line_width, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_hlines(FILE *js_include_file,int num,char *draw_type,int line_width, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_arrows(FILE *js_include_file,int num,char *draw_type,int line_width,int type, char *stroke_color,double stroke_opacity,int use_dashed,int dashtype0,int dashtype1,int arrow_head);
void add_js_crosshairs(FILE *js_include_file,int num,char *draw_type,int line_width, int crosshair_size ,char *stroke_color,double stroke_opacity);
void add_js_paths(FILE *js_include_file,int num,char *draw_type,int line_width, int closed_path,char *stroke_color,double stroke_opacity,int use_filled, char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_poly(FILE *js_include_file,int num,char *draw_type,int line_width,char *stroke_color,double stroke_opacity,int use_filled,char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_rect(FILE *js_include_file,int num,int roundrect,char *draw_type,int line_width,char *stroke_color,double stroke_opacity,int use_filled,char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_clickfill(FILE *js_include_file,int canvas_root_id,char *clickcolor,int opacity);
void add_js_filltoborder(FILE *js_include_file,int canvas_root_id,int canvas_type);
void add_js_arc(FILE *js_include_file,int canvas_root_id,int num,int line_width,char *stroke_color,double stroke_opacity,char *fill_color,double fill_opacity,int use_dashed,int dashtype0,int dashtype1);
void add_js_text(FILE *js_include_file,int canvas_root_id,int font_size,char *font_family,char *font_color,double stroke_opacity);
void add_js_multidraw(FILE *js_include_file,int canvas_root_id,char *draw_types,char *button_style);
/* these should  be harmonized via switch key !!*/
void add_input_circle(FILE *js_include_file,int type,int num);
void add_input_segment(FILE *js_include_file,int num);
void add_input_demiline(FILE *js_include_file,int num);
void add_input_line(FILE *js_include_file,int num);
void add_input_polyline(FILE *js_include_file);
void add_textarea_polygon(FILE *js_include_file);
void add_input_crosshair(FILE *js_include_file,int num);
void add_input_arrow(FILE *js_include_file,int num);
void add_input_xy(FILE *js_include_file, int canvas_root_id,int font_size,char *input_style);
void add_input_xyr(FILE *js_include_file, int canvas_root_id,int font_size,char *input_style);
void add_input_x1y1x2y2(FILE *js_include_file, int canvas_root_id,int font_size,char *input_style);
void add_textarea_xy(FILE *js_include_file, int canvas_root_id,char *input_style);
void add_zoom_buttons(FILE *js_include_file,int canvas_root_id,char *stroke_color,double stroke_opacity);
void add_js_tooltip(int canvas_root_id,char *tooltip_text,char *bgcolor,int xsize,int ysize);
void add_js_popup(int canvas_root_id,int xsize,int ysize,char *getfile_cmd);
void add_input_jsfunction(FILE *js_include_file, int canvas_root_id,char *input_style,char *input_label,int input_cnt,char *stroke_color,float stroke_opacity,int line_width,int use_dashed,int dashtype0,int dashtype1,int font_size);
void add_rawmath(FILE *js_include_file);
void add_js_protractor(FILE *js_include_file,int canvas_root_id,int type,double xcenter,double ycenter,int size,char *font,char *stroke_color,double stroke_opacity,char *fill_color,double fill_opacity,int line_width,int use_scale,int dynamic);
void add_js_ruler(FILE *js_include_file,int canvas_root_id,double x,double y,double sizex,double sizey,char *font,char *stroke_color,double stroke_opacity,char *fill_color,double fill_opacity,int line_width,int dynamic);

extern int NUMBER_OF_COLORNAMES;
extern struct colors { char *hex; char *name; char *rgb; } colors[];
