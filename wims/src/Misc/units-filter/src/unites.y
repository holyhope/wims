%{
/* inclusions, définition */
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gmp.h>
#include <gmpxx.h>
#include "unites.h"
#include <iostream>

  int yylex();
  int yyerror(const char * msg);

  const char * unit_names[BU_LAST]={"m","kg","s","A","K","mol","cd"};

/*   typedef struct{ */
/*     int i; */
/*     mpq_class multip, maxmultip, wanted_multip;  */
/*     /\* mutiplicators are mutiprecisions rationals *\/ */
/*     uniteSI unite; */
/*     int base[BU_LAST]; */
/*     char * s, * v; */
/*     std::string wanted_unit; */
/*     mpq_class val; */
/*     /\* values are mutiprecisions rationals *\/ */
/*     int signif; */
/*     int pcent; /\* percent tolerance *\/ */
/*   } yystype; */
  
  class yystype{
  public:
    int i;
    mpq_class multip, maxmultip, wanted_multip;
    /* mutiplicators are mutiprecisions rationals */
    uniteSI unite;
    int base[BU_LAST];
    char * s, * v;
    std::string wanted_unit;
    mpq_class val;
    /* values are mutiprecisions rationals */
    int signif;
    int pcent; /* percent tolerance */
    yystype(){
      s=(char*) NULL;
      v=(char*) NULL;
    }
  };

  std::ostream & operator << (std::ostream & o, yystype data);
  std::ostream & operator << (std::ostream & o, yystype data){
    o << "YYSTYPE[" <<"i="<<data.i<<", multip="<<data.multip;
    o<<", maxmultip="<<data.maxmultip<<", wanted_multip="<<data.wanted_multip;
    o<<", unite="<<data.unite<<", base={";
    for (int i=0;i<BU_LAST;i++){
      o<<data.base[i]<<" ";
    }
    o<<"}";
    if(data.s!=NULL){ o<<", s="<<data.s;}else{o<<", s=NULL";}
    if(data.v!=NULL){o<<", v="<<data.v;}else{o<<", v=NULL";}
    o<<", wanted_unit="<<data.wanted_unit;
    o<<", val="<<data.val<<", signif="<<data.signif<<", pcent="<<data.pcent;
    o<<"] ";
    return o;
  }
  
#define YYSTYPE yystype 

 extern FILE * yyin;

/* variables globales */
#define MAXBUF 255
 char buffer[MAXBUF+1], buffer2[MAXBUF+1];
 yystype result;
 mpq_class val_real; /* a multiprecision rational */
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
  $$.wanted_unit="";
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
  mpq_class r;

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
| PUIS {$$.i = val_int;}
;

prefixe : 
PP {$$.multip=1.0; char c=$$.s[0]; 
 switch (c){
 case 'y' : $$.multip = 1e-24; break;
 case 'z' : $$.multip = 1e-21; break;
 case 'a' : $$.multip = 1e-18; break;
 case 'f' : $$.multip = 1e-15; break;
 case 'p' : $$.multip = 1e-12; break;
 case 'n' : $$.multip = 1e-9; break;
 case 'µ' : $$.multip = 1e-6; break;
 case 'c' : $$.multip = 1e-2; break;
 case 'd' : if (!strcmp ($$.s,"da") ) $$.multip = 10.0;
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
| Umin {$$.unite=TUmin;  $$.multip=unites[$$.unite].multiplicateur;}
| Um {$$.unite=TUm; $$.s = strdup("m"); $$.multip=unites[$$.unite].multiplicateur;}
| Ug {$$.unite=TUg;  $$.multip=unites[$$.unite].multiplicateur;}
| Us {$$.unite=TUs;  $$.multip=unites[$$.unite].multiplicateur;}
| UA { $$.unite = TUA;  $$.multip=unites[$$.unite].multiplicateur;}  
| UK { $$.unite = TUK;  $$.multip=unites[$$.unite].multiplicateur;}  
| Umol { $$.unite = TUmol;  $$.multip=unites[$$.unite].multiplicateur;}  
| Ucd { $$.unite = TUcd;  $$.multip=unites[$$.unite].multiplicateur;}  
| UHz { $$.unite = TUHz;  $$.multip=unites[$$.unite].multiplicateur;}  
| UN { $$.unite = TUN;  $$.multip=unites[$$.unite].multiplicateur;}  
| UPa { $$.unite = TUPa;  $$.multip=unites[$$.unite].multiplicateur;}  
| UJ { $$.unite = TUJ;  $$.multip=unites[$$.unite].multiplicateur;}
| UT { $$.unite = TUT; $$.s = strdup("T"); $$.multip=unites[$$.unite].multiplicateur;}  
| UW { $$.unite = TUW;  $$.multip=unites[$$.unite].multiplicateur;}  
| UC { $$.unite = TUC;  $$.multip=unites[$$.unite].multiplicateur;}  
| UV { $$.unite = TUV;  $$.multip=unites[$$.unite].multiplicateur;}  
| Uohm { $$.unite = TUohm;  $$.multip=unites[$$.unite].multiplicateur;}  
| US { $$.unite = TUS;  $$.multip=unites[$$.unite].multiplicateur;}  
| UF { $$.unite = TUF;  $$.multip=unites[$$.unite].multiplicateur;}  
| UWb { $$.unite = TUWb;  $$.multip=unites[$$.unite].multiplicateur;}  
| UH { $$.unite = TUH;  $$.multip=unites[$$.unite].multiplicateur;}  
| Ulm { $$.unite = TUlm;  $$.multip=unites[$$.unite].multiplicateur;}  
| Ulx { $$.unite = TUlx;  $$.multip=unites[$$.unite].multiplicateur;}  
| UBq { $$.unite = TUBq;  $$.multip=unites[$$.unite].multiplicateur;}  
| UGy { $$.unite = TUGy;  $$.multip=unites[$$.unite].multiplicateur;}  
| USv { $$.unite = TUSv;  $$.multip=unites[$$.unite].multiplicateur;}  
| Urad { $$.unite = TUrad;  $$.multip=unites[$$.unite].multiplicateur;}  
| Usr { $$.unite = TUsr;  $$.multip=unites[$$.unite].multiplicateur;}  
| Uda { $$.unite = TUda;  $$.multip=unites[$$.unite].multiplicateur;} 
| Uma { $$.unite = TUma;  $$.multip=unites[$$.unite].multiplicateur;} 
| Usa { $$.unite = TUsa;  $$.multip=unites[$$.unite].multiplicateur;} 
| Uangs { $$.unite = TUangs;  $$.multip=unites[$$.unite].multiplicateur;} 
| Ubarn { $$.unite = TUbarn;  $$.multip=unites[$$.unite].multiplicateur;} 
| Uare { $$.unite = TUare;  $$.multip=unites[$$.unite].multiplicateur;} 
| Ul { $$.unite = TUl;  $$.multip=unites[$$.unite].multiplicateur;} 
| Ut { $$.unite = TUt;  $$.multip=unites[$$.unite].multiplicateur;} 
| Ubar { $$.unite = TUbar;  $$.multip=unites[$$.unite].multiplicateur;} 
| UeV { $$.unite = TUeV;  $$.multip=unites[$$.unite].multiplicateur;} 
| Uuam { $$.unite = TUuam;  $$.multip=unites[$$.unite].multiplicateur;} 
;



%%

#include "uniteslex.cc"
#include <stdlib.h>
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

yyFlexLexer lexer;
yyFlexLexer * thelexer = &lexer;

int yylex(){
  return thelexer->yylex();
}


inline int yyerror(const char * msg){
  printf("ERROR at %ld : %s\n", pos, msg);
  exit(1);
}

void test_verbeux(){
  int i;
  yyparse();
  if (result.s) {
    if (result.unite == TU_LAST){
      std::cout << result.s << " " << result.multip*result.val << " SI (équation aux dimensions : ";
      for (i=0; i<BU_LAST; i++){
	printf("%3d", result.base[i]);
      }
      printf(")\n");
    }
    else {
      if (result.i!=1) 
	std::cout <<  result.s << " (" << result.multip*result.val 
		  << " " << unites[result.unite].nom << ")^{" << result.i 
		  << "}\n";
      else 
	std::cout << result.s << " " << result.multip*result.val 
		  << " " << unites[result.unite].nom << "\n";
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
  // il faut afficher le résultat sous forme d'un nombre décimal et pas d'une
  // fraction
  //std::cout << result.multip*result.val;
  std::cout << mpf_class(result.multip*result.val);
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

void printUnit(optiontype option, std::string unit, int tolerance){
  char * indexohm;
  char buffer[128];
  char *codedunit;

#ifdef RECODE_SUPPORT
  if(isUTF8) {
    RECODE_OUTER outer = recode_new_outer (true);
    RECODE_REQUEST request = recode_new_request (outer);
    recode_scan_request (request, "latin1..utf8"); 
    codedunit=strdup(recode_string(request,unit.c_str()));
  } else {
    codedunit=strdup(unit.c_str());
  }
#else
  codedunit=strdup(unit.c_str());
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

mpq_class round_mpc(const mpq_class & x);

void printValue(optiontype option, yystype result, int s){
  char val[128],exp[128], *i, *j, *indexE;
  char buf[128];
  regex_t regex;
  regmatch_t matches[3];
  int success,l;
  int vallen;

  mpq_class value=result.multip*result.val;
  mpq_class absval=abs(value);
  mpq_class puisdix=trunc(log(absval.get_d())/log(10))+1-s;
  mpq_class powten=1;
  if (puisdix>0) for(int i=0; i < puisdix; i++) powten=powten*10;
  if (puisdix<0) for(int i=-1; i < -puisdix; i++) powten=powten/10;
  mpz_class r=round_mpc(value/powten);
  value=r*powten;
  if (s<=1){ 
    snprintf(buf,sizeof(buf),"%1.0e", value.get_d() );
  } else {
    snprintf(buf,sizeof(buf),"%1.*e", s-1,value.get_d() );
  }
  // simplifications
  regcomp(&regex, "^(.*)(e[+-][0-9]+)$", REG_EXTENDED);
  regexec(&regex, buf, 3, matches,0);
  if (strcmp(buf+matches[2].rm_so,"e+00")==0) {
    // removing e+00
    *(buf+matches[2].rm_so)=0;
  }
  l=strlen(buf);
  if (*(buf+matches[2].rm_so+1)=='+'){
    j=buf+matches[2].rm_so+2;
    while (*j=='0') j++;
    for(i=buf+matches[2].rm_so+1; j<=buf+l; i++,j++){
      // erasing +0* after e
      *i=*j;
    }
  }
  if (*(buf+matches[2].rm_so+1)=='-'){
    j=buf+matches[2].rm_so+2;
    while (*j=='0') j++;
    for(i=buf+matches[2].rm_so+2; j<=buf+l; i++,j++){
      // erasing 0* after e-
      *i=*j;
    }
  }
  if (option==option_l){
    indexE=strstr(buf,"e");
    if (indexE){
      vallen=indexE-buf;
      strncpy(val,buf,vallen);
      val[vallen]=0;
      strncpy(exp,indexE+1,sizeof(exp));
      printf("%s\\times 10^{%s}\\,",val,exp);
    } else{
      printf("%s\\,",buf);
    }
  } else {
    printf(buf);
  }
}

double trunc(double x);

mpq_class round_mpc(const mpq_class & x){
  /**
   * computes a rounded multiprecision integer from the input data
   * this may be valid only for positive inputs.
   * @param x the input data
   * @result the rouded value : 1499999/1000000 is rounded towards 1
   * and 3/2 is rounded towards 2
   */
  // half unity is defined as slightly greater than 1/2 because
  // values submitted to this function are frequently made from
  // flots whose mantissas are approximately 0.5 (many examples 
  // made by teachers are based on integer data, and use a division 
  // by 2). Unfortunately flots whose mantissas had to be 0.5 are
  // actually slightly less : 0.4999999999999998 or so. The following 
  // definition  of the constant "halfUnit" is a workaround for this
  // current issue.
  mpq_class halfUnit=mpq_class(1000000001,2000000000);
  mpq_class y = x+halfUnit;
  mpz_class q=y.get_num()/y.get_den();
  return q;
}


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
  //mpq_class val, r, powten, absval; /* val r powten and absval are multiprecision rationals */
  int puisdix;

  yyparse();
  if (!result.signif) {
    s=significative(result.v);
    /* le nombre de chiffres significatifs est déduit de la valeur donnée */
  } else {
    s=result.signif;
    /* le nombre de chiffres significatifs a été explicité */
  }
  pc=result.pcent;
  // arrondit en tenant compte du nombre de chiffres significatifs
  if (result.wanted_unit.length()>0){
    result.multip /= result.wanted_multip;
  }else{ // met le multiplicateur à 1 si l'unité d'entrée a été repérée
    if (result.s && strlen(result.s)>0){
      result.multip = mpq_class(1,1);
    }
  }
  printValue(option, result, s);
  // affiche l'unité SI.
  // renvoie l'unité demandée si elle existe
  if (result.wanted_unit.length()>0){
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
  // on teste s'il y aura une unité visible
  int visible_unit=0;
  for (i=0; i<BU_LAST; i++){
    if (result.base[i]!=0) visible_unit=1;
  }
  if (result.wanted_unit.length()>0) visible_unit=1;
  if(visible_unit!=0){ // on ne marque les unités que s'il y en a !
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
  }
  printUnit(option, "", pc);
}

int main(int argc, char * argv[]){
  const char * optstr = "osl";
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

void atof1(char* s, mpq_class & r){
  /**
   * ascii to fraction
   * @param s : a string, where the spaces and tabs will be removed
   * @param r : the result which is the fraction.
   */
  double result=atof(s);
  r=result;
  return;
}
