%option noyywrap
/* coding: iso-8859-1 */
     
   #include <stdlib.h>
   #include "unites.h"
     

spc            [ \t]+

/* les nombres */
digits         [0-9]
int            [+-]?{digits}+
mantisse       {digits}+
real           {int}([.]{mantisse})?{spc}*([Ee]{spc}*{int})?
signif         {spc}*\#{digits}+{spc}*
plusminpc      {spc}*~{digits}{digits}?{spc}*
plusminpcbis   {spc}*\+\-{spc}*{digits}{digits}?%{spc}*

/*quelques séparateurs particuliers*/
point          {spc}*\.{spc}*
barre          {spc}*\/{spc}*
puis           {spc}*^{spc}*
colon          {spc}*:{spc}*

/* les unités de temps hors système */
heure_ou_hecto h
minute         min

/* les unités du SI */
/* Handbook of Chemistry & Physics 78, CRC Press 1997, page 1-20 */
milli_ou_metre m
are            a
gramme         g
seconde        s
ampere         A
kelvin         K
degre_c        °C
mole           mol
candela        cd
hertz          Hz
newton         N
pascal         Pa
joule          J
watt           W
coulomb        C
volt           V
ohm            Ohm|ohm
siemens        S
farad          F
tera_ou_tesla  T
weber          Wb
henry          H
lumen          lm
lux            lx
becquerel      Bq
gray           Gy
sievert        Sv
radian         rad
steradian      sr

/* unités annexes, voir page 1-22 */
degre_angle    °
minute_angle   \'
seconde_angle  \'\'
angstrom       °A
barn           b
litre          l|L
tonne          t
bar            bar
ev             eV
uam            u|uma

/* prefixes sauf milli et téra */
/* Handbook of Chemistry & Physics 78, CRC Press 1997, page 1-21 */
prefixe_pur    [yzafpnµcdhkMGPEZY]|da

/* notation des exposants */
puissance      {puis}{int}
carre          ²
cube           ³


%%


{real}              { val_real = atof1(yytext); yylval.v=strdup(yytext); pos+=yyleng; return REAL;}
{heure_ou_hecto}    { pos+=yyleng; return Uh;}
{minute}            { pos+=yyleng; return Umin;}
{milli_ou_metre}    { pos+=yyleng; return Um;}
{are}               {pos+=yyleng; return Uare;}
{gramme}            { pos+=yyleng; return Ug;}
{seconde}           { pos+=yyleng; return Us;}
{ampere}            { pos+=yyleng; return UA;}
{kelvin}|{degre_c}  { pos+=yyleng; return UK;}
{mole}              { pos+=yyleng; return Umol;}
{candela}           { pos+=yyleng; return Ucd;}
{hertz}             { pos+=yyleng; return UHz;}
{newton}            { pos+=yyleng; return UN;}
{pascal}            { pos+=yyleng; return UPa;}
{joule}             { pos+=yyleng; return UJ;}
{watt}              { pos+=yyleng; return UW;}
{coulomb}           { pos+=yyleng; return UC;}
{volt}              { pos+=yyleng; return UV;}
{ohm}               { pos+=yyleng; return Uohm;}
{siemens}           { pos+=yyleng; return US;}
{farad}             { pos+=yyleng; return UF;}
{tera_ou_tesla}     { pos+=yyleng; return UT;}
{weber}             { pos+=yyleng; return UWb;}
{henry}             { pos+=yyleng; return UH;}
{lumen}             { pos+=yyleng; return Ulm;}
{lux}               { pos+=yyleng; return Ulx;}
{becquerel}         { pos+=yyleng; return UBq;}
{gray}              { pos+=yyleng; return UGy;}
{sievert}           { pos+=yyleng; return USv;}
{radian}            { pos+=yyleng; return Urad;}
{steradian}         { pos+=yyleng; return Usr;}
{puissance}         { pos+=yyleng; while (!index("-0123456789", *yytext)) yytext++; return PUIS;}
{carre}             { yytext="2"; pos+=yyleng; return PUIS;}
{cube}              { yytext="3"; pos+=yyleng; return PUIS;}
{prefixe_pur}       { pos+=yyleng; return PP;}
{point}             { pos+=yyleng; return POINT;}
{barre}             { pos+=yyleng; return BARRE;}
{degre_angle}       {pos+=yyleng; return Uda;}
{minute_angle}      {pos+=yyleng; return Uma;}
{seconde_angle}     {pos+=yyleng; return Usa;}
{angstrom}          {pos+=yyleng; return Uangs;}
{barn}              {pos+=yyleng; return Ubarn;}
{litre}             { pos+=yyleng; return Ul;}
{tonne}             {pos+=yyleng; return Ut;}
{bar}               {pos+=yyleng; return Ubar;}
{ev}                {pos+=yyleng; return UeV;}
{uam}               {pos+=yyleng; return Uuam;}
{spc}               { pos+=yyleng; return SPC;}
{signif}            {pos+=yyleng; val_int=atoi(strchr(yytext,'#')+1); return Signif;}
{plusminpc}         {pos+=yyleng; val_int=atoi(strchr(yytext,'~')+1); return PlusminPC;}
{plusminpcbis}      {pos+=yyleng; val_int=atoi(strchr(yytext,'+')+2); return PlusminPC;}
{colon}             {pos+=yyleng; return COLON;}

.                    pos+=yyleng;
\n                   pos+=yyleng;
