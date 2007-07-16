/* A Bison parser, made from unites.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	REAL	257
# define	SPC	258
# define	Uh	259
# define	Umin	260
# define	Um	261
# define	Ug	262
# define	Us	263
# define	UA	264
# define	UK	265
# define	Umol	266
# define	Ucd	267
# define	UHz	268
# define	UN	269
# define	UPa	270
# define	UJ	271
# define	UW	272
# define	UC	273
# define	UV	274
# define	Uohm	275
# define	US	276
# define	UF	277
# define	UT	278
# define	UWb	279
# define	UH	280
# define	Ulm	281
# define	Ulx	282
# define	UBq	283
# define	UGy	284
# define	USv	285
# define	Urad	286
# define	Usr	287
# define	PUIS	288
# define	PP	289
# define	POINT	290
# define	BARRE	291
# define	Uda	292
# define	Uma	293
# define	Usa	294
# define	Uangs	295
# define	Ubarn	296
# define	Uare	297
# define	Ul	298
# define	Ut	299
# define	Ubar	300
# define	UeV	301
# define	Uuam	302
# define	Signif	303

#line 1 "unites.y"

/* inclusions, définition */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "unites.h"

  char * unit_names[BU_LAST]={"m","kg","s","A","K","mol","cd"};

  typedef struct{
    int i;
    double multip, maxmultip;
    uniteSI unite;
    int base[BU_LAST];
    char * s, * v;
    double val;
    int signif;
  } yystype;
  
#define YYSTYPE yystype 

 extern char * yytext;
 extern FILE * yyin;

/* variables globales */
#define MAXBUF 255
 char buffer[MAXBUF+1], buffer2[MAXBUF+1];
 yystype result;
 double val_real;
 int val_int, count_signif=0;
 long pos;

/* les unités du SI */
/* Handbook of Chemistry & Physics 78, CRC Press 1997, page 1-20 */
unite_data unites[TU_LAST] ={
/*TUh*/   {"h",    "seconde",3600.0,     { 0, 0, 1, 0, 0, 0, 0}},
/*TUmin*/ {"min",   "seconde", 60.0,     { 0, 0, 1, 0, 0, 0, 0}},
/*TUm*/   {"m",      "mètre",   1.0,     { 1, 0, 0, 0, 0, 0, 0}},
/*TUg*/   {"g",    "kilogramme",1.0e-3,  { 0, 1, 0, 0, 0, 0, 0}},
/*TUs*/   {"s",      "seconde", 1.0,     { 0, 0, 1, 0, 0, 0, 0}},
/*TUA*/   {"A",      "ampère",  1.0,     { 0, 0, 0, 1, 0, 0, 0}},
/*TUK*/   {"K",      "kelvin",  1.0,     { 0, 0, 0, 0, 1, 0, 0}},
/*TUmol*/ {"mol",    "mol",     1.0,     { 0, 0, 0, 0, 0, 1, 0}},
/*TUcd*/  {"cd",     "candela", 1.0,     { 0, 0, 0, 0, 0, 0, 1}},
/*TUHz*/  {"Hz",     "hetrz",   1.0,     { 0,-1, 0, 0, 0, 0, 0}},
/*TUN*/   {"N",      "newton",  1.0,     { 1, 1,-2, 0, 0, 0, 0}},
/*TUPa*/  {"Pa",     "pascal",  1.0,     {-1, 1,-2, 0, 0, 0, 0}},
/*TUJ*/   {"J",      "joule",   1.0,     { 2, 1,-2, 0, 0, 0, 0}},
/*TUW */  {"W",      "watt",    1.0,     { 2, 1,-3, 0, 0, 0, 0}},
/*TUC*/   {"C",      "coulomb", 1.0,     { 0, 0, 1, 1, 0, 0, 0}},
/*TUV*/   {"V",      "volt",    1.0,     { 2, 1,-3,-1, 0, 0, 0}},
/*TUohm*/ {"\\Omega","ohm",     1.0,     { 2, 1,-3,-2, 0, 0, 0}},
/*TUS*/   {"S",      "siemens", 1.0,     {-2,-1, 3, 2, 0, 0, 0}},
/*TUF*/   {"F",      "farad",   1.0,     {-2,-1, 4, 2, 0, 0, 0}},
/*TUT*/   {"T",      "tesla",   1.0,     { 0, 1,-2,-1, 0, 0, 0}},
/*TUWb*/  {"Wb",     "weber",   1.0,     { 2, 1,-2,-1, 0, 0, 0}},
/*TUH*/   {"H",      "henry",   1.0,     { 2, 1,-2,-2, 0, 0, 0}},
/*TUlm*/  {"lm",     "lumen",   1.0,     { 0, 0, 0, 0, 0, 0, 1}},
/*TUlx*/  {"lx",     "lux",     1.0,     {-2, 0, 0, 0, 0, 0, 1}},
/*TUBq */ {"Bq",     "becquerel",1.0,    { 0, 0,-1, 0, 0, 0, 0}},
/*TUGy*/  {"Gy",     "gray",     1.0,    { 2, 0,-2, 0, 0, 0, 0}},
/*TUSv*/  {"Sv",     "sievert",  1.0,    { 2, 0,-2, 0, 0, 0, 0}},
/*TUrad*/ {"rad",    "radian",   1.0,    { 0, 0, 0, 0, 0, 0, 0}},
/*TUsr*/  {"sr" ,    "stéradian",1.0,    { 0, 0, 0, 0, 0, 0, 0}},
/*TUnull*/{"" ,    "sans unité",1.0,     { 0, 0, 0, 0, 0, 0, 0}},
/*TUda*/  {"°", "degré", M_PI/180.0,     { 0, 0, 0, 0, 0, 0, 0}},
/*TUma*/  {"'", "minute", M_PI/10800,    { 0, 0, 0, 0, 0, 0, 0}},
/*TUsa*/  {"''","seconde",M_PI/648000 ,  { 0, 0, 0, 0, 0, 0, 0}},
/*TUangs*/ {"\\o{A}", "angström", 1e-10, { 1, 0, 0, 0, 0, 0, 0}},
/*TUbarn*/ {"b", "barn", 1e-28,          { 2, 0, 0, 0, 0, 0, 0}},
/*TUare*/  {"a", "are", 1e2,             { 2, 0, 0, 0, 0, 0, 0}},
/*TUl*/    {"L", "litre", 1e-3,          { 3, 0, 0, 0, 0, 0, 0}},
/*TUt*/    {"t", "tonne", 1e3,              { 0, 1, 0, 0, 0, 0, 0}},
/*TUbar*/  {"bar", "bar", 1e5,            {-1, 1,-2, 0, 0, 0, 0}},
/*TUeV*/   {"eV", "eV", 1.60218e-19,       { 0, 0, 1, 1, 0, 0, 0}},
/*TUuam*/  {"uma", "uma", 1.66054e-27,    { 0, 1, 0, 0, 0, 0, 0}}
};

unite_data pref_units[] ={
/*TUm*/   {"m",      "mètre",   1.0,     { 1, 0, 0, 0, 0, 0, 0}},
/*   */   {"kg",    "kilogramme",1.0,    { 0, 1, 0, 0, 0, 0, 0}},
/*TUs*/   {"s",      "seconde", 1.0,     { 0, 0, 1, 0, 0, 0, 0}},
/*TUA*/   {"A",      "ampère",  1.0,     { 0, 0, 0, 1, 0, 0, 0}},
/*TUK*/   {"K",      "kelvin",  1.0,     { 0, 0, 0, 0, 1, 0, 0}},
/*TUmol*/ {"mol",    "mol",     1.0,     { 0, 0, 0, 0, 0, 1, 0}},
/*TUcd*/  {"cd",     "candela", 1.0,     { 0, 0, 0, 0, 0, 0, 1}},
/*TUHz*/  {"Hz",     "hetrz",   1.0,     { 0,-1, 0, 0, 0, 0, 0}},
/*TUN*/   {"N",      "newton",  1.0,     { 1, 1,-2, 0, 0, 0, 0}},
/*TUPa*/  {"Pa",     "pascal",  1.0,     {-1, 1,-2, 0, 0, 0, 0}},
/*TUJ*/   {"J",      "joule",   1.0,     { 2, 1,-2, 0, 0, 0, 0}},
/*TUW */  {"W",      "watt",    1.0,     { 2, 1,-3, 0, 0, 0, 0}},
/*TUC*/   {"C",      "coulomb", 1.0,     { 0, 0, 1, 1, 0, 0, 0}},
/*TUV*/   {"V",      "volt",    1.0,     { 2, 1,-3,-1, 0, 0, 0}},
/*TUohm*/ {"ohm",    "ohm",     1.0,     { 2, 1,-3,-2, 0, 0, 0}},
/*TUS*/   {"S",      "siemens", 1.0,     {-2,-1, 3, 2, 0, 0, 0}},
/*TUF*/   {"F",      "farad",   1.0,     {-2,-1, 4, 2, 0, 0, 0}},
/*TUT*/   {"T",      "tesla",   1.0,     { 0, 1,-2,-1, 0, 0, 0}},
/*TUWb*/  {"Wb",     "weber",   1.0,     { 2, 1,-2,-1, 0, 0, 0}},
/*TUH*/   {"H",      "henry",   1.0,     { 2, 1,-2,-2, 0, 0, 0}},
/*TUlm*/  {"lm",     "lumen",   1.0,     { 0, 0, 0, 0, 0, 0, 1}},
/*TUlx*/  {"lx",     "lux",     1.0,     {-2, 0, 0, 0, 0, 0, 1}},
};

int significative(char* text);
int significative(char* text){
  // returns the number of significative numbers of a real
  // if the real is null returns zero.
  int i,j,result=0;
  for(i=0;
      i<strlen(text)&&(text[i]=='0'||text[i]=='.'|| text[i]=='+'||text[i]=='-');
      i++){
    //skip leading plus,minus,zeros and the decimal point
  }
  for(j=i;j<strlen(text)&&(text[j]>='0'&&text[j]<='9'||text[j]=='.');j++){
    if (text[j]!='.') {
      result++;
    } else {
      //skip the decimal point
    }
  }
  return result;
}

#ifndef YYSTYPE
# define YYSTYPE int
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		75
#define	YYFLAG		-32768
#define	YYNTBASE	50

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 303 ? yytranslate[x] : 63)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     4,     8,    10,    14,    19,    21,    24,
      25,    27,    30,    32,    35,    38,    40,    43,    46,    49,
      52,    54,    57,    58,    60,    62,    64,    66,    68,    70,
      72,    74,    76,    78,    80,    82,    84,    86,    88,    90,
      92,    94,    96,    98,   100,   102,   104,   106,   108,   110,
     112,   114,   116,   118,   120,   122,   124,   126,   128,   130,
     132,   134,   136,   138,   140
};
static const short yyrhs[] =
{
      51,     0,    53,     0,    52,    54,    51,     0,    52,     0,
       3,    54,    55,     0,     3,    54,    55,    49,     0,     3,
       0,     3,    49,     0,     0,     4,     0,    55,    56,     0,
      59,     0,    57,    59,     0,    37,    59,     0,    36,     0,
       7,    62,     0,    24,    62,     0,     5,    62,     0,    61,
      62,     0,    62,     0,    58,    60,     0,     0,    34,     0,
      35,     0,     5,     0,     6,     0,     7,     0,     8,     0,
       9,     0,    10,     0,    11,     0,    12,     0,    13,     0,
      14,     0,    15,     0,    16,     0,    17,     0,    24,     0,
      18,     0,    19,     0,    20,     0,    21,     0,    22,     0,
      23,     0,    25,     0,    26,     0,    27,     0,    28,     0,
      29,     0,    30,     0,    31,     0,    32,     0,    33,     0,
      38,     0,    39,     0,    40,     0,    41,     0,    42,     0,
      43,     0,    44,     0,    45,     0,    46,     0,    47,     0,
      48,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   180,   181,   184,   193,   196,   197,   203,   211,   221,
     222,   225,   237,   240,   246,   260,   263,   271,   278,   285,
     292,   297,   319,   320,   323,   348,   350,   351,   352,   353,
     354,   355,   356,   357,   358,   359,   360,   361,   362,   363,
     364,   365,   366,   367,   368,   369,   370,   371,   372,   373,
     374,   375,   376,   377,   378,   379,   380,   381,   382,   383,
     384,   385,   386,   387,   388
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "REAL", "SPC", "Uh", "Umin", "Um", "Ug", 
  "Us", "UA", "UK", "Umol", "Ucd", "UHz", "UN", "UPa", "UJ", "UW", "UC", 
  "UV", "Uohm", "US", "UF", "UT", "UWb", "UH", "Ulm", "Ulx", "UBq", "UGy", 
  "USv", "Urad", "Usr", "PUIS", "PP", "POINT", "BARRE", "Uda", "Uma", 
  "Usa", "Uangs", "Ubarn", "Uare", "Ul", "Ut", "Ubar", "UeV", "Uuam", 
  "Signif", "but", "valeur_mixte", "valeur", "sans_unite", "spc", "unite", 
  "suiv_unit", "point", "prim_unit1", "prim_unit", "puissance01", 
  "prefixe", "base_unite", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    50,    50,    51,    51,    52,    52,    53,    53,    54,
      54,    55,    55,    56,    56,    57,    58,    58,    58,    58,
      58,    59,    60,    60,    61,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     1,     3,     1,     3,     4,     1,     2,     0,
       1,     2,     1,     2,     2,     1,     2,     2,     2,     2,
       1,     2,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       0,     9,     1,     4,     2,    10,     8,     0,     0,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    39,    40,    41,    42,    43,    44,    38,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    24,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       5,    22,    12,     0,    20,     9,     3,    25,    27,    38,
      18,    16,    17,    15,     0,     6,    11,     0,    23,    21,
      19,    14,    13,     0,     0,     0
};

static const short yydefgoto[] =
{
      73,     2,     3,     4,     7,    50,    66,    67,    51,    52,
      69,    53,    54
};

static const short yypact[] =
{
      -1,     0,-32768,     5,-32768,-32768,-32768,    45,     8,    89,
  -32768,    89,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    89,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
     -31,   -22,-32768,    89,-32768,     9,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,    45,-32768,-32768,    45,-32768,-32768,
  -32768,-32768,-32768,    14,    15,-32768
};

static const short yypgoto[] =
{
  -32768,    11,-32768,-32768,    13,-32768,-32768,-32768,-32768,   -57,
  -32768,-32768,    -8
};


#define	YYLAST		137


static const short yytable[] =
{
      -7,    60,     1,    61,     5,    63,    64,    71,    -9,     5,
      72,    55,    68,     5,    74,    75,     8,     0,    65,    56,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    70,     0,     0,     0,     6,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,     0,
      38,     0,     0,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    57,    10,    58,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    59,    29,    30,    31,    32,    33,    34,
      35,    36,    37,     0,     0,     0,     0,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49
};

static const short yycheck[] =
{
       0,     9,     3,    11,     4,    36,    37,    64,     3,     4,
      67,     3,    34,     4,     0,     0,     3,    -1,    49,     8,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    49,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 315 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
#line 180 "unites.y"
{result = yyvsp[0];;
    break;}
case 2:
#line 181 "unites.y"
{result = yyvsp[0];;
    break;}
case 3:
#line 184 "unites.y"
{
  int i;
  for(i=0; i < BU_LAST; i++){
    if (yyvsp[-2].base[i] != yyvsp[0].base[i]) yyerror ("not homogeneous units");
  }
  if (yyvsp[-2].multip <= yyvsp[0].maxmultip) yyerror ("incorrect mutiple units ordering");
  yyval.val=yyvsp[-2].val*yyvsp[-2].multip+yyvsp[0].val*yyvsp[0].multip;
  yyval.multip=1; yyval.maxmultip = yyvsp[-2].multip;
;
    break;}
case 4:
#line 193 "unites.y"
{yyval=yyvsp[0]; yyval.maxmultip=yyvsp[0].multip;;
    break;}
case 5:
#line 196 "unites.y"
{yyval=yyvsp[0]; yyval.val=val_real; yyval.signif=0;;
    break;}
case 6:
#line 197 "unites.y"
{
  yyval=yyvsp[-1]; yyval.val=val_real; 
  yyval.signif=val_int;
;
    break;}
case 7:
#line 203 "unites.y"
{
  int i;
  yyval=yyvsp[0];
  yyval.val=val_real; 
  for (i=0; i < BU_LAST; i++){yyval.base[i]=unites[TUnull].base[i];} 
  yyval.multip=1.0; 
  yyval.signif=0;
;
    break;}
case 8:
#line 211 "unites.y"
{
  int i;
  yyval=yyvsp[-1];
  yyval.val=val_real; 
  for (i=0; i < BU_LAST; i++){yyval.base[i]=unites[TUnull].base[i];} 
  yyval.multip=1.0; 
  yyval.signif=val_int;
;
    break;}
case 11:
#line 225 "unites.y"
{
  int index;
  yyval.unite = TU_LAST; /* unité non renseignée */
  strncpy(buffer,yyvsp[-1].s,MAXBUF); 
  strncat(buffer,yyvsp[0].s,MAXBUF-strlen(yyvsp[0].s)); 
  free(yyvsp[-1].s); free(yyvsp[0].s);
  yyval.s=strdup(buffer);
  for(index=0; index< BU_LAST; index++){
    yyval.base[index] = yyvsp[-1].base[index]+yyvsp[0].base[index] ; 
  }
  yyval.multip = yyvsp[-1].multip*yyvsp[0].multip;
;
    break;}
case 12:
#line 237 "unites.y"
{ yyval=yyvsp[0]; ;
    break;}
case 13:
#line 240 "unites.y"
{
  yyval=yyvsp[0]; strncpy(buffer,".",MAXBUF); 
  strncat(buffer,yyvsp[0].s,MAXBUF-strlen(yyvsp[0].s)); 
  free(yyvsp[0].s);
  yyval.s=strdup(buffer);
;
    break;}
case 14:
#line 246 "unites.y"
{
  int index;
  yyval=yyvsp[0]; 
  yyval.multip = 1/ yyval.multip;
  strncpy(buffer,"/",MAXBUF); 
  strncat(buffer,yyvsp[0].s,MAXBUF-strlen(yyvsp[0].s)); 
  free(yyvsp[0].s);
  yyval.s=strdup(buffer);
  for(index=0; index< BU_LAST; index++){
    yyval.base[index] *= -1; 
  }
;
    break;}
case 16:
#line 264 "unites.y"
{
  yyval=yyvsp[0];
  strncpy(buffer,"m",MAXBUF); 
  strncat(buffer,yyvsp[0].s,MAXBUF-strlen(yyvsp[0].s)); 
  free(yyvsp[0].s);
  yyval.s = strdup(buffer); yyval.multip*=1e-3; 
;
    break;}
case 17:
#line 271 "unites.y"
{
  yyval=yyvsp[0];
  strncpy(buffer,"T",MAXBUF); 
  strncat(buffer,yyvsp[0].s,MAXBUF-strlen(yyvsp[0].s)); 
  free(yyvsp[0].s);
  yyval.s = strdup(buffer); yyval.multip*=1e12;
;
    break;}
case 18:
#line 278 "unites.y"
{
  yyval=yyvsp[0];
  strncpy(buffer,"h",MAXBUF); 
  strncat(buffer,yyvsp[0].s,MAXBUF-strlen(yyvsp[0].s)); 
  free(yyvsp[0].s);
  yyval.s = strdup(buffer); yyval.multip*=1e2;
;
    break;}
case 19:
#line 285 "unites.y"
{
  yyval=yyvsp[0];
  strncpy(buffer, yyvsp[-1].s,MAXBUF); 
  strncat(buffer, yyvsp[0].s, MAXBUF-strlen(yyvsp[0].s));
  free(yyvsp[-1].s); free(yyvsp[0].s);yyval.s=strdup(buffer); 
  yyval.multip*=yyvsp[-1].multip;
  ;
    break;}
case 20:
#line 292 "unites.y"
{
  yyval=yyvsp[0];
;
    break;}
case 21:
#line 297 "unites.y"
{
  int index;
  double r;

  yyval.i=yyvsp[0].i;
  strncpy(buffer, yyvsp[-1].s,MAXBUF);
  if (yyvsp[0].i!=1){
    strncat(buffer, "^{%d}",MAXBUF-strlen( "^{%d}")); 
    sprintf(buffer2, buffer, yyvsp[0].i);
  }
  else strncpy(buffer2,buffer,MAXBUF);
  yyval.s=strdup(buffer2); free(yyvsp[-1].s);
  for(index=0; index< BU_LAST; index++){
    yyval.base[index] = unites[yyvsp[-1].unite].base[index]*yyvsp[0].i;
  }
  for(index=0, r=1; index<yyvsp[0].i ; index++){
    r*= yyval.multip;
  }
  yyval.multip=r;
;
    break;}
case 22:
#line 319 "unites.y"
{yyval.i=1;;
    break;}
case 23:
#line 320 "unites.y"
{yyval.i = atoi(yytext);;
    break;}
case 24:
#line 324 "unites.y"
{yyval.s = strdup(yytext); yyval.multip=1.0;
 switch (yytext[0]){
 case 'y' : yyval.multip = 1e-24; break;
 case 'z' : yyval.multip = 1e-21; break;
 case 'a' : yyval.multip = 1e-18; break;
 case 'f' : yyval.multip = 1e-15; break;
 case 'p' : yyval.multip = 1e-12; break;
 case 'n' : yyval.multip = 1e-9; break;
 case 'µ' : yyval.multip = 1e-6; break;
 case 'c' : yyval.multip = 1e-2; break;
 case 'd' : if (!strcmp (yytext,"da") ) yyval.multip = 10.0;
    else yyval.multip = 0.1; break;
 case 'h' : yyval.multip = 1e2; break;
 case 'k' : yyval.multip = 1e3; break;
 case 'M' : yyval.multip = 1e6; break;
 case 'G' : yyval.multip = 1e9; break;
 case 'P' : yyval.multip = 1e15; break;
 case 'E' : yyval.multip = 1e18; break;
 case 'Z' : yyval.multip = 1e21; break;
 case 'Y': yyval.multip = 1e24; break;
 }
;
    break;}
case 25:
#line 349 "unites.y"
{yyval.unite=TUh; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 26:
#line 350 "unites.y"
{yyval.unite=TUmin; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 27:
#line 351 "unites.y"
{yyval.unite=TUm; yyval.s = strdup("m"); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 28:
#line 352 "unites.y"
{yyval.unite=TUg; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 29:
#line 353 "unites.y"
{yyval.unite=TUs; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 30:
#line 354 "unites.y"
{ yyval.unite = TUA; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 31:
#line 355 "unites.y"
{ yyval.unite = TUK; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 32:
#line 356 "unites.y"
{ yyval.unite = TUmol; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 33:
#line 357 "unites.y"
{ yyval.unite = TUcd; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 34:
#line 358 "unites.y"
{ yyval.unite = TUHz; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 35:
#line 359 "unites.y"
{ yyval.unite = TUN; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 36:
#line 360 "unites.y"
{ yyval.unite = TUPa; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 37:
#line 361 "unites.y"
{ yyval.unite = TUJ; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 38:
#line 362 "unites.y"
{ yyval.unite = TUT; yyval.s = strdup("T"); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 39:
#line 363 "unites.y"
{ yyval.unite = TUW; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 40:
#line 364 "unites.y"
{ yyval.unite = TUC; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 41:
#line 365 "unites.y"
{ yyval.unite = TUV; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 42:
#line 366 "unites.y"
{ yyval.unite = TUohm; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 43:
#line 367 "unites.y"
{ yyval.unite = TUS; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 44:
#line 368 "unites.y"
{ yyval.unite = TUF; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 45:
#line 369 "unites.y"
{ yyval.unite = TUWb; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 46:
#line 370 "unites.y"
{ yyval.unite = TUH; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 47:
#line 371 "unites.y"
{ yyval.unite = TUlm; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 48:
#line 372 "unites.y"
{ yyval.unite = TUlx; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 49:
#line 373 "unites.y"
{ yyval.unite = TUBq; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 50:
#line 374 "unites.y"
{ yyval.unite = TUGy; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 51:
#line 375 "unites.y"
{ yyval.unite = TUSv; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 52:
#line 376 "unites.y"
{ yyval.unite = TUrad; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 53:
#line 377 "unites.y"
{ yyval.unite = TUsr; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 54:
#line 378 "unites.y"
{ yyval.unite = TUda; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 55:
#line 379 "unites.y"
{ yyval.unite = TUma; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 56:
#line 380 "unites.y"
{ yyval.unite = TUsa; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 57:
#line 381 "unites.y"
{ yyval.unite = TUangs; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 58:
#line 382 "unites.y"
{ yyval.unite = TUbarn; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 59:
#line 383 "unites.y"
{ yyval.unite = TUare; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 60:
#line 384 "unites.y"
{ yyval.unite = TUl; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 61:
#line 385 "unites.y"
{ yyval.unite = TUt; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 62:
#line 386 "unites.y"
{ yyval.unite = TUbar; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 63:
#line 387 "unites.y"
{ yyval.unite = TUeV; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
case 64:
#line 388 "unites.y"
{ yyval.unite = TUuam; yyval.s = strdup(yytext); yyval.multip=unites[yyval.unite].multiplicateur;;
    break;}
}

#line 705 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 393 "unites.y"


#include "lex.yy.c"
/* le programme lui-même */

inline int yyerror(char * msg){
  printf("ERROR at %ld : %s\n", pos, msg);
  exit(1);
}

void test_verbeux(){
  int i;
  yyparse();
  if (result.s) {
    if (result.unite == TU_LAST){
      printf("%s %g SI (équation aux dimensions : ", result.s, 
	     result.multip*result.val );
      for (i=0; i<BU_LAST; i++){
	printf("%3d", result.base[i]);
      }
      printf(")\n");
    }
    else {
      if (result.i!=1) 
	printf ("%s (%g %s)^{%d}\n", result.s, 
		result.multip*result.val, 
		unites[result.unite].nom, result.i);
      else printf("%s %g %s\n", result.s, 
		  result.multip*result.val, 
		  unites[result.unite].nom);
    }
  }
  else fprintf(stderr, "problème : result.s = null\n");
}

void sortie_normalisee(){
  /***************************************************/
  /* le format des données en sortie est :           */
  /* double int int int int int int int              */
  /* et signifie  dans l'ordre                       */
  /***************************************************/
  /* valeur                                          */
  /* puissance en unité de longueur (m)              */
  /* puissance en unité de masse (kg)                */
  /* puissance en unité de temps (s)                 */
  /* puissance en unité de courant (A)               */
  /* puissance en unité de température (K)           */
  /* puissance en unité de quantité de matière (mol) */
  /* puissance en unité de inutensité lumineuse (cd) */
  /* nombre de chiffres significatifs                */
  /* un zéro pour des extensions futures             */
  /***************************************************/
  int i,s=0;

  yyparse();
  printf("%g", result.multip*result.val );
  if (count_signif){ //il faut prendre en compte les nombres significatifs
    if (!result.signif) {
      s=significative(result.v);
    } else {
      s=result.signif;
    }
  }
  for (i=0; i<BU_LAST; i++){
    printf(" %3d", result.base[i]);
  }
  printf("    %d    0\n",s);
}

void sortie_texte(){
  /***************************************************/
  /* le format des données en sortie est :           */
  /* double string                                   */
  /* et signifie  dans l'ordre                       */
  /***************************************************/
  /* valeur  (compte tenu des ciffres significatifs) */
  /* unité   (SI)                                    */
  /***************************************************/
  int i,j,
    s=0,
    notfirst=0,
    trouve=0,
    nb_pref=sizeof(pref_units)/sizeof(pref_units[0]);

  yyparse();
  if (!result.signif) {
    s=significative(result.v);
  } else {
    s=result.signif;
  }
  // affiche la valeur
  if (s<=1){
    printf("%1.0e", result.multip*result.val );
  } else {
    printf("%1.*e", s-1,result.multip*result.val );
  }
  //affiche l'unité SI.
  //recherche s'il y a une unité préférentielle
  for (i=0; i<nb_pref; i++){
    trouve=(result.base[0]==pref_units[i].base[0]);
    for (j=1; j<BU_LAST; j++){
      trouve &= (result.base[j]==pref_units[i].base[j]);
    }
    if (trouve){
      printf("%s\n",pref_units[i].sym);
      return;
    }
  }
  for (i=0; i<BU_LAST; i++){
    if (result.base[i]!=0){
      if (notfirst) printf(".");
      printf("%s",unit_names[i]);
      notfirst=1;
      if (result.base[i]!=1){
	printf("^%d",result.base[i]);
      }
    }
  }
  printf("\n");
}

int main(int argc, char * argv[]){
  char * optstr = "os";
  int ch;
  while (-1 != (ch=getopt(argc,argv,optstr))){
    switch(ch){
    case 's': 
      count_signif=1;
      sortie_normalisee();
      return 0;
      break;
    case 'o':
      sortie_texte();
      return 0;
      break;
    default: 
      break;
    }
  }
  /*test_verbeux();*/
  sortie_normalisee();
  return 0;
}
