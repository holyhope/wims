/*

*********************************************************************************
* J.M. Evers 3/2012								*
* This is all amateur scriblings... So no copyrights.				*
* This source code file, and compiled objects derived from it,			*
* can be used and distributed without restriction, including for commercial use	*
* No warrenty whatsoever							*
*********************************************************************************

WIMS usage:
sci_num = !exec scienceprint number,significance,type

number: a number
significance : desired precision
type (optional args): calc = 0 / html = 1 / latex = 2  / prefix =3 

default  : calc   notation : 120000,3   -> 1.20*10^5
type = 0 : calc   notation : 120000,3,0 -> 1.20*10^5
type = 1 : html notation   : 120000,3,1 -> 1.20&times;10<sup>5</sup>
type = 2 : latex notation  : 120000,3,2 -> 1.20 \times 10^{5}
type = 3 : prefix-notation : 120000,3,3 -> 120.0 k
type = 3 : if -24 > prefix > 24  	-> type = 1 (html)

multiple conversion: use space between arguments
scienceprint 120000,4 122900,5 120036,6,3 --> 120.0*10^3,122.90*10^3,120.036 k

24  yotta 	Y 
21  zetta 	Z 
18  exa 	E 
15  peta	P 
12  tera 	T
9   giga 	G
6   mega 	M
3   kilo 	k 
2   hecto	h
1   deca 	da
-1  deci 	d 
-2  centi 	c 
-3  milli 	m
-6  micro 	µ
-9  nano 	n
-12 pico 	p
-15 femto 	f
-18 atto 	a
-21 zepto 	z
-24 yocto 	y

*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define MICRO "µ"
#define PREFIX_START (-24)
#define PREFIX_END 24
#define MAX_CONV 256

char *printscience(double value, int sig, int format , int cnt ){

    static char *prefix[] = { "y", "z", "a", "f", "p", "n", MICRO, "m", "", "k", "M", "G", "T", "P", "E", "Z", "Y" };
    double display, fract;
    char *sign = NULL;
    int exponent10;

    if(value < 0.0) {sign = "-";value = -value;} else {sign = "";}

    exponent10 = lrint( floor( log10(value) ) );//correctly round to desired precision
    value *= pow(10.0, sig - 1 - exponent10);
    fract = modf(value, &display);
    if(fract >= 0.5){display += 1.0;}
    value = display * pow(10.0, exponent10 - sig + 1);
    if(exponent10 > 0){exponent10 = (exponent10/3)*3;}else{exponent10 = ((-exponent10+3)/3)*(-3);}
    value *= pow(10.0, -exponent10);
    if(format != 3){ // allow all powers; not limited by prefix list
	if(value > 10.0){
	    while(value >= 10){
		value /= 10.0;
	        exponent10++;
	    }
	}
    }
    else // steps of powers dividable by 3 used for prefix notation
    {
	if (value >= 1000.0) {
	    value /= 1000.0;
	    exponent10 += 3;
	}
	else
	{
	    if(value >= 100.0){
		sig -= 2;
	    }
	    else
	    {
		if(value >= 10.0){
		    sig -= 1;
		}
	    }
	}
    }
    if(sig < 1){sig = 1;}
    if(cnt > 1){fprintf(stdout,",");}
    // check on format style versus exponent
    if(exponent10 == 0 ){
	format = 3; // do not use 1.23*10^0
    }
    else
    {
	if(exponent10 == 1){
	    format = 3;// do not use 1.23*10^1
	    value = value * 10;
	    sig = sig - 1;
	}
	else
	{
	    if(format == 3 && ((exponent10 < PREFIX_START) || (exponent10 > PREFIX_END))){ 
		format = 1; // if no prefix available, revert to html presentation
	    }
	}
    
    }
    if(format != 3 ){
	if( format == 0){ // 'calculable' presentation
	    fprintf(stdout, "%s%.*f*10^%d", sign, sig-1, value, exponent10);
	}
	else
	{
	    if( format == 1 ){ // html presentation
		fprintf(stdout, "%s%.*f&times;10<sup>%d</sup>", sign, sig-1, value, exponent10);
	    }
	    else // latex presentation
	    {
		fprintf(stdout, "%s%.*f \\times 10^{%d}", sign, sig-1, value, exponent10);
	    }
	}
    }	    
    else // format = 3 : prefix presentation or other more suitable presentation
    {
	fprintf(stdout, "%s%.*f %s", sign, sig-1, value,prefix[(exponent10-PREFIX_START)/3]);
    }
    return NULL;
}
  
int main( int argc , char *argv[]){

    if( argc < 2){
	fprintf(stdout,"syntax error : number1,significance1,type1 number2,significance2,type2 ... number_n,significance_n,type_n \n");
	return 0;
    }
    
    double number = 0;
    int significance = 0,type = 0,idx = 0,cnt = 1;
    char *input = "\0",*ptr = "\0";

    /* test for illegal characters */
    const char *invalid_characters = "\n\"\'!=ABCDFGHIJKLMNOPQRSTUVWXYZabcdfghijklmnopqrstuvwxyz@#$%^*&()[]{};:~><?/\\|";
    /* Ee +- are allowed : 12.34e+05  12.34e-08 */

    /* walk through argument 1 to end, and call function scienceprint(a,b,c) */
    input = argv[cnt];
    while( input != NULL ){
	if(cnt > MAX_CONV){fprintf(stdout,"\nerror: number of conversions exceeds limit of %d\n",MAX_CONV);return 0;}
        while (*input){ // loop through invalid chars.
	    if ( strchr(invalid_characters, *input) ){
		fprintf(stdout,"\nerror : found illegal characterin argument \"%s\" \n",input);
		return 0;
	    }
	    input++;
	}
	// reset input to actual value
	input = argv[cnt];
	ptr = (char *) strtok(input,",");
	idx = 0;
	type = 0;
	while( ptr != NULL ){
	    switch( idx ){
		case 0: number = atof(ptr); break;
		case 1: significance = atoi(ptr); break;
		case 2: type = atoi(ptr); if(type != 0 && type != 1 && type != 2 && type != 3){type = 0;} break;
		default: break;
	    }
	    idx++;
	    ptr = (char *) strtok(NULL,",");
	}
	// number and precision are mandatory:  default type=0 
	if( idx < 2 || idx > 3){fprintf(stdout,"\nsyntax error : number1,significance1,type1 number2,significance2,type2 ... number_n,significance_n,type_n \n");return 0;}
	// call conversion routine
	printscience(number, significance, type , cnt);
	cnt++;
	input = argv[cnt];
    }
    fprintf(stdout,"\n");
    return 0;
}
