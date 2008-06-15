%{
/* inclusions, définition */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "unites.h"

  char * unit_names[BU_LAST]={"m","kg","s","A","K","mol","cd"};

  typedef struct{
    int i;
    double multip, maxmultip, wanted_multip;
    uniteSI unite;
    int base[BU_LAST];
    char * s, * v, * wanted_unit;
    double val;
    int signif;
    int pcent; /* percent tolerance */
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
/*TUt*/    {"t", "tonne", 1e3,           { 0, 1, 0, 0, 0, 0, 0}},
/*TUbar*/  {"bar", "bar", 1e5,           {-1, 1,-2, 0, 0, 0, 0}},
/*TUeV*/   {"eV", "eV", 1.60218e-19,     { 2, 1,-2, 0, 0, 0, 0}},
/*TUuam*/  {"uma", "uma", 1.66054e-27,   { 0, 1, 0, 0, 0, 0, 0}}
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

%}


%token REAL
%token SPC
%token COLON
%token Uh
%token Umin
%token Um
%token Ug
%token Us
%token UA
%token UK
%token Umol
%token Ucd
%token UHz
%token UN
%token UPa
%token UJ
%token UW
%token UC
%token UV
%token Uohm
%token US
%token UF
%token UT
%token UWb
%token UH
%token Ulm
%token Ulx
%token UBq
%token UGy
%token USv
%token Urad
%token Usr
%token PUIS
%token PP
%token POINT
%token BARRE
%token Uda
%token Uma
%token Usa
%token Uangs
%token Ubarn
%token Uare
%token Ul
%token Ut
%token Ubar
%token UeV
%token Uuam
%token Signif
%token PlusminPC

%%

/* les règles */

but : valeur_mixte {result = $1;}
| sans_unite {result = $1;}
;

valeur_mixte : valeur spc valeur_mixte {
  int i;
  for(i=0; i < BU_LAST; i++){
    if ($1.base[i] != $3.base[i]) yyerror ("not homogeneous units");
  }
  if ($1.multip <= $3.maxmultip) yyerror ("incorrect mutiple units ordering");
  $$.val=$1.val*$1.multip+$3.val*$3.multip;
  $$.multip=1; $$.maxmultip = $1.multip;
  $$.wanted_unit="";
}
| valeur {$$=$1; $$.maxmultip=$1.multip;$$.wanted_unit="";}
| valeur COLON style {
  int i;
  $$=$1; $$.maxmultip=$1.multip;
  for(i=0; i < BU_LAST; i++){
    if ($1.base[i] != $3.base[i]) yyerror ("wanted unit not homogeneous");
  }  
  $$.wanted_multip=$3.multip;
  $$.wanted_unit=$3.s;
}
;

style : unite {$$=$1;}
;

valeur : REAL spc unite {$$=$3; $$.val=val_real; $$.signif=0; $$.pcent=0;}
| REAL spc unite Signif {
  $$=$3; $$.val=val_real; 
  $$.signif=val_int; $$.pcent=0;
}
| REAL spc unite PlusminPC {
  $$=$3; $$.val=val_real; 
  $$.pcent=val_int; $$.signif=0;
}
;

sans_unite :REAL {
  int i;
  $$=$1;
  $$.val=val_real; 
  for (i=0; i < BU_LAST; i++){$$.base[i]=unites[TUnull].base[i];} 
  $$.multip=1.0; 
  $$.signif=0; $$.pcent=0;
  $$.wanted_unit=0;
}
| REAL Signif {
  int i;
  $$=$1;
  $$.val=val_real; 
  for (i=0; i < BU_LAST; i++){$$.base[i]=unites[TUnull].base[i];} 
  $$.multip=1.0; 
  $$.signif=val_int; $$.pcent=0;
}
| REAL PlusminPC {
  int i;
  $$=$1;
  $$.val=val_real; 
  for (i=0; i < BU_LAST; i++){$$.base[i]=unites[TUnull].base[i];} 
  $$.multip=1.0; 
  $$.signif=0; $$.pcent=val_int;
}
;
 
spc : /*rien*/
|SPC
;

unite : unite suiv_unit{
  int index;
  $$.unite = TU_LAST; /* unité non renseignée */
  strncpy(buffer,$1.s,MAXBUF); 
  strncat(buffer,$2.s,MAXBUF-strlen($1.s)); 
  free($1.s); free($2.s);
  $$.s=strdup(buffer);
  for(index=0; index< BU_LAST; index++){
    $$.base[index] = $1.base[index]+$2.base[index] ; 
  }
  $$.multip = $1.multip*$2.multip;
}
| prim_unit { $$=$1; }
;

suiv_unit : point prim_unit{
  $$=$2; strncpy(buffer,".",MAXBUF); 
  strncat(buffer,$2.s,MAXBUF-1); 
  free($2.s);
  $$.s=strdup(buffer);
}
| BARRE prim_unit{
  int index;
  $$=$2; 
  $$.multip = 1/ $$.multip;
  strncpy(buffer,"/",MAXBUF); 
  strncat(buffer,$2.s,MAXBUF-1); 
  free($2.s);
  $$.s=strdup(buffer);
  for(index=0; index< BU_LAST; index++){
    $$.base[index] *= -1; 
  }
}
;

point : POINT
;

prim_unit1 : 
Um base_unite {
  $$=$2;
  strncpy(buffer,"m",MAXBUF); 
  strncat(buffer,$2.s,MAXBUF-1); 
  free($2.s);
  $$.s = strdup(buffer); $$.multip*=1e-3; 
}
| UT base_unite {
  $$=$2;
  strncpy(buffer,"T",MAXBUF); 
  strncat(buffer,$2.s,MAXBUF-1); 
  free($2.s);
  $$.s = strdup(buffer); $$.multip*=1e12;
}
| Uh base_unite {
  $$=$2;
  strncpy(buffer,"h",MAXBUF); 
  strncat(buffer,$2.s,MAXBUF-1); 
  free($2.s);
  $$.s = strdup(buffer); $$.multip*=1e2;
}
|  prefixe base_unite {
  $$=$2;
  strncpy(buffer, $1.s,MAXBUF); 
  strncat(buffer, $2.s, MAXBUF-strlen($1.s));
  free($1.s); free($2.s);$$.s=strdup(buffer); 
  $$.multip*=$1.multip;
  }
| base_unite {
  $$=$1;
}
;

prim_unit : prim_unit1 puissance01 {
  int index;
  double r;

  $$.i=$2.i;
  strncpy(buffer, $1.s,MAXBUF);
  if ($2.i!=1){
    strncat(buffer, "^%d",MAXBUF-strlen($1.s)); 
    sprintf(buffer2, buffer, $2.i);
  }
  else strncpy(buffer2,buffer,MAXBUF);
  $$.s=strdup(buffer2); free($1.s);
  for(index=0; index< BU_LAST; index++){
    $$.base[index] = unites[$1.unite].base[index]*$2.i;
  }
  if ($2.i>0){
    for(index=0, r=1; index<$2.i ; index++){
      r*= $$.multip;
    }
  } else {
    for(index=0, r=1; index>$2.i ; index--){
      r /= $$.multip;
    }
  }
  $$.multip=r;
}
;

puissance01 : /*rien*/ {$$.i=1;}
| PUIS {$$.i = atoi(yytext);}
;

prefixe : 
PP {$$.s = strdup(yytext); $$.multip=1.0;
 switch (yytext[0]){
 case 'y' : $$.multip = 1e-24; break;
 case 'z' : $$.multip = 1e-21; break;
 case 'a' : $$.multip = 1e-18; break;
 case 'f' : $$.multip = 1e-15; break;
 case 'p' : $$.multip = 1e-12; break;
 case 'n' : $$.multip = 1e-9; break;
 case 'µ' : $$.multip = 1e-6; break;
 case 'c' : $$.multip = 1e-2; break;
 case 'd' : if (!strcmp (yytext,"da") ) $$.multip = 10.0;
    else $$.multip = 0.1; break;
 case 'h' : $$.multip = 1e2; break;
 case 'k' : $$.multip = 1e3; break;
 case 'M' : $$.multip = 1e6; break;
 case 'G' : $$.multip = 1e9; break;
 case 'P' : $$.multip = 1e15; break;
 case 'E' : $$.multip = 1e18; break;
 case 'Z' : $$.multip = 1e21; break;
 case 'Y': $$.multip = 1e24; break;
 }
}
;

base_unite :  
Uh {$$.unite=TUh; $$.s = strdup("h"); $$.multip=unites[$$.unite].multiplicateur;}
| Umin {$$.unite=TUmin; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}
| Um {$$.unite=TUm; $$.s = strdup("m"); $$.multip=unites[$$.unite].multiplicateur;}
| Ug {$$.unite=TUg; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}
| Us {$$.unite=TUs; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}
| UA { $$.unite = TUA; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| UK { $$.unite = TUK; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| Umol { $$.unite = TUmol; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| Ucd { $$.unite = TUcd; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| UHz { $$.unite = TUHz; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| UN { $$.unite = TUN; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| UPa { $$.unite = TUPa; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| UJ { $$.unite = TUJ; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}
| UT { $$.unite = TUT; $$.s = strdup("T"); $$.multip=unites[$$.unite].multiplicateur;}  
| UW { $$.unite = TUW; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| UC { $$.unite = TUC; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| UV { $$.unite = TUV; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| Uohm { $$.unite = TUohm; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| US { $$.unite = TUS; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| UF { $$.unite = TUF; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| UWb { $$.unite = TUWb; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| UH { $$.unite = TUH; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| Ulm { $$.unite = TUlm; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| Ulx { $$.unite = TUlx; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| UBq { $$.unite = TUBq; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| UGy { $$.unite = TUGy; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| USv { $$.unite = TUSv; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| Urad { $$.unite = TUrad; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| Usr { $$.unite = TUsr; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;}  
| Uda { $$.unite = TUda; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;} 
| Uma { $$.unite = TUma; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;} 
| Usa { $$.unite = TUsa; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;} 
| Uangs { $$.unite = TUangs; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;} 
| Ubarn { $$.unite = TUbarn; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;} 
| Uare { $$.unite = TUare; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;} 
| Ul { $$.unite = TUl; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;} 
| Ut { $$.unite = TUt; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;} 
| Ubar { $$.unite = TUbar; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;} 
| UeV { $$.unite = TUeV; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;} 
| Uuam { $$.unite = TUuam; $$.s = strdup(yytext); $$.multip=unites[$$.unite].multiplicateur;} 
;



%%

#include "lex.yy.c"
#include <stdio.h>
#include <stdbool.h>

#ifdef RECODE_SUPPORT
  #include <recode.h>
#endif

#include <regex.h>

const char *program_name;
int isUTF8;

/* le programme lui-même */

typedef enum {option_default, option_s, option_o, option_l} optiontype;

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
  /* tolérance (en pourcentage)                      */
  /***************************************************/
  int i,s=0,pc=0;

  yyparse();
  printf("%g", result.multip*result.val );
  if (count_signif){ //il faut prendre en compte les nombres significatifs
    if (!result.signif) {
      s=significative(result.v);
    } else {
      s=result.signif;
    }
  }
  pc=result.pcent;
  for (i=0; i<BU_LAST; i++){
    printf(" %3d", result.base[i]);
  }
  printf("    %d    %d\n",s,pc);
}

void printUnit(optiontype option, char * unit, int tolerance){
  char * indexohm;
  char buffer[128];
  char *codedunit;

#ifdef RECODE_SUPPORT
  if(isUTF8) {
    RECODE_OUTER outer = recode_new_outer (true);
    RECODE_REQUEST request = recode_new_request (outer);
    recode_scan_request (request, "latin1..utf8"); 
    codedunit=strdup(recode_string(request,unit));
  } else {
    codedunit=strdup(unit);
  }
#else
  codedunit=strdup(unit);
#endif

  if (option==option_l){
    strncpy(buffer, codedunit,sizeof(buffer));
    indexohm=strstr(buffer,"ohm");
    if (indexohm){
      strncpy(indexohm, "\\Omega", sizeof(buffer)-strlen("\\Omega")+strlen("ohm"));
    }
    printf(" %s",buffer);
  } else {
    printf(" %s",codedunit);
  }
  if (tolerance){
    if (option==option_l){
      printf(" \\pm %d\\,\\%%",tolerance);
    } else{
      printf(" +-%d%%",tolerance);
    }
  }
  printf("\n");
  free(codedunit);
}

void printValue(optiontype option, yystype result, int s){
  char buffer[128], val[128],exp[128], *i, *j, *indexE;
  regex_t regex;
  regmatch_t matches[3];
  int success,l;
  int vallen;
  if (s<=1){ 
    snprintf(buffer,sizeof(buffer),"%1.0e", result.multip*result.val );
  } else {
    snprintf(buffer,sizeof(buffer),"%1.*e", s-1,result.multip*result.val );
  }
  // simplifications
  regcomp(&regex, "^(.*)(e[+-][0-9]+)$", REG_EXTENDED);
  regexec(&regex,buffer, 3, matches,0);
  if (strcmp(buffer+matches[2].rm_so,"e+00")==0) {
    // removing e+00
    *(buffer+matches[2].rm_so)=0;
  }
  l=strlen(buffer);
  if (*(buffer+matches[2].rm_so+1)=='+'){
    j=buffer+matches[2].rm_so+2;
    while (*j=='0') j++;
    for(i=buffer+matches[2].rm_so+1; j<=buffer+l; i++,j++){
      // erasing +0* after e
      *i=*j;
    }
  }
  if (*(buffer+matches[2].rm_so+1)=='-'){
    j=buffer+matches[2].rm_so+2;
    while (*j=='0') j++;
    for(i=buffer+matches[2].rm_so+2; j<=buffer+l; i++,j++){
      // erasing 0* after e-
      *i=*j;
    }
  }
  if (option==option_l){
    indexE=strstr(buffer,"e");
    if (indexE){
      vallen=indexE-buffer;
      strncpy(val,buffer,vallen);
      val[vallen]=0;
      strncpy(exp,indexE+1,sizeof(exp));
      printf("%s\\times 10^{%s}\\,",val,exp);
    } else{
      printf("%s\\,",buffer);
    }
  } else {
    printf(buffer);
  }
}

double trunc(double x);
double round(double x);

void sortie_texte(optiontype option){
  /***************************************************/
  /* le format des données en sortie est :           */
  /* double string                                   */
  /* et signifie  dans l'ordre                       */
  /***************************************************/
  /* valeur (compte tenu des chiffres significatifs) */
  /* unité   (SI)  +- pcent %                        */
  /***************************************************/
  int i,j,
    s=0,pc=0,
    notfirst=0,
    trouve=0,
    nb_pref=sizeof(pref_units)/sizeof(pref_units[0]);
  double val,powten;
  int puisdix;

  yyparse();
  if (!result.signif) {
    s=significative(result.v);
  } else {
    s=result.signif;
  }
  pc=result.pcent;
  // arrondit en tenant compte du nombre de chiffres significatifs
  val=result.multip*result.val;
  puisdix=trunc(log(abs(val))/log(10));
  powten=pow(10,puisdix+1-s);
  val=round(val/powten)*powten;
  //affiche la valeur
  if (result.wanted_unit && strlen(result.wanted_unit)>0){
    result.multip /= result.wanted_multip;
  }else{ // met le multiplicateur à 1 si l'unité d'entrée a été repérée
    if (result.s && strlen(result.s)>0){
      result.multip = 1.0;
    }
  }
  printValue(option, result, s);
  // affiche l'unité SI.
  // renvoie l'unité demandée si elle existe
  if (result.wanted_unit && strlen(result.wanted_unit)>0){
    printUnit(option, result.wanted_unit, pc);
    return;
  }
  // affiche l'unité donnée à l'entrée par défaut
  if (result.s && strlen(result.s)>0){
    printUnit(option, result.s, pc);
    return;
  }
  // recherche s'il y a une unité préférentielle
  for (i=0; i<nb_pref; i++){
    trouve=(result.base[0]==pref_units[i].base[0]);
    for (j=1; j<BU_LAST; j++){
      trouve &= (result.base[j]==pref_units[i].base[j]);
    }
    if (trouve){
      printUnit(option, pref_units[i].sym, pc);
      return;
    }
  }
  for (i=0; i<BU_LAST; i++){
    if (result.base[i]!=0){
      if (notfirst) printf("."); else printf(" ");
      printf("%s",unit_names[i]);
      notfirst=1;
      if (result.base[i]!=1){
	if (option==option_l){
	  printf("^{%d}",result.base[i]);
	} else {
	  printf("^%d",result.base[i]);
	}
      }
    }
  }
  printUnit(option, "", pc);
}

int main(int argc, char * argv[]){
  char * optstr = "osl";
  char * envoption=getenv("units_option");
  // environmental option take precedence on command-line options

  optiontype option=option_default;
  
  int ch;
  while (-1 != (ch=getopt(argc,argv,optstr))){
    switch(ch){
    case 's': 
      option=option_s;
      break;
    case 'o':
      option=option_o;
      break;
    case 'l':
      option=option_l;
      break;
    default: 
      break;
    }
  }
  if (envoption && strncmp(envoption, "s", 2)==0) option=option_s;
  if (envoption && strncmp(envoption, "o", 2)==0) option=option_o;
  if (envoption && strncmp(envoption, "l", 2)==0) option=option_l;
#ifdef RECODE_SUPPORT
  // check if we are in a UTF8 environment
  char *lc_all=getenv("LC_ALL");
  isUTF8 = (lc_all!= NULL && strstr(lc_all,"UTF-8"));
#endif
  program_name = argv[0];

  // environmental option take precedence on command-line options
  switch(option){
  case option_s: 
    count_signif=1;
    sortie_normalisee();
    return 0;
    break;
  case option_o:
  case option_l:
    sortie_texte(option);
    return 0;
    break;
  default: 
    break;
  }
  /*test_verbeux();*/
  sortie_normalisee();
  return 0;
}

double atof1(char* s){
  /* like function atof, but spaces or tabs are eliminated */
  /* from the input string */
  char* s1=strdup(s);
  int i,j,l;
  double result;

  l=strlen(s1);
  for(i=0;i<l;i++){
    while (i<l && (s1[i]==' ' || s1[i]=='\t')){
      for(j=i+1; j<l; j++){
	s1[j-1]=s1[j];
      }
      l--;
      s1[l]=0;
    }
  }
  result=atof(s1);
  free(s1);
  return result;
}
