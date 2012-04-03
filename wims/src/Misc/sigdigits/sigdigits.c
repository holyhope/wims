/*
*********************************************************************************
* J.M. Evers 3/2012								*
* This is all amateur scriblings... So no copyrights.				*
* This source code file, and compiled objects derived from it,			*
* can be used and distributed without restriction, including for commercial use	*
* No warrenty whatsoever							*
*********************************************************************************
syntax number_1 number2 number_3 ... number_n

example
!exec sigdigits 0001.0200 01.0200*10^-4 1.023*10^5
3,2,4,4,0,0
3,2,2,4,-4,0
4,3,1,3,5,1

result is 
1 line per input number
6 items per line:

item 1) real number of significant digits in number_x (eg without leading zeros)
item 2) real number of "significant decimals" (eg without trailing zero's)

item 3) number of digits left from decimal point (including non-significant) 
	or if no decimals: total number of digits (length)
item 4) number of digits right from decimal point (including non-significant)

item 5) exponent (if not present : 0)

item 6) indication : is the number correctly written ?  1 or 0  ( 000.1 is not correct...)

exponent '10^' or 'e': 1.23*10^-4 1.23e-4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DIGITS 64
#define MAX_CONV 64

void append(char* s, char c){
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

int main( int argc , char *argv[]){
    if( argc < 2){
	fprintf(stdout,"syntax error\n");
	exit(0);
    }
    char word[MAX_DIGITS];
    char *input;
    char exp[MAX_DIGITS];
    int cnt,i,ok,length,zeros,sig1,sig2,found_digit,found_point,dec1,dec2,pow,found_power,found_multiply;
    const char *invalid_characters = "\n\"\'!=ABCDFGHIJKLMNOPQRSTUVWXYZabcdfghijklmnopqrstuvwxyz@#$%&()[]{};:~><?/\\|";
    /* Ee +- are allowed : 12.34e+05  12.34e-08  1.234*10^123*/ 
    cnt = 1;
    input = argv[cnt];
    while( input != NULL){
	if(cnt > MAX_CONV){fprintf(stdout,"error : number of conversions exceeds limit of %d\n",MAX_CONV);return 0;}
	length = strlen(input);
        if( length > MAX_DIGITS){                                                                                                           
            fprintf(stdout,"error : number is larger than %d digits\n",MAX_DIGITS);                                                            
            exit(0);                                                                                                                       
        }
	/* test for illegal characters */
	while (*input){ 
	    if ( strchr(invalid_characters, *input) ){
		fprintf(stdout,"error : found illegal character in argument \"%s\" \n",input);
		return 0;
	    }
	    input++;
	}
	input = argv[cnt];
	strncpy( word, input, length );
	// reset
	found_digit = 0;
	found_point = 0;
	found_power = 0;
	found_multiply = 0;
	sig1 = 0; // real significant digits
	dec1 = 0; // real "significant decimals" 
	sig2 = 0; // integer part [including leading zeros]
	dec2 = 0; // decimal part [including trailing zeros]
	pow = 0; // exponent
	zeros = 0; // leading or trailing zeros
	exp[0]='\0';
	for( i = length - 1 ; i >= 0 ; i--){ // walk from rightside to left through the 'number'
	    switch( word[i] ){
		case '^' : found_power = 1;break;
		case '*' : found_power = 1;pow = length - i;sig1 = 0;dec1 = 0;found_digit = 0;zeros = 0;found_multiply = 1;break;
		case 'e' : found_power = 1;pow = length - i;sig1 = 0;dec1 = 0;found_digit = 0;zeros = 0;found_multiply = 1;break;
		case 'E' : found_power = 1;pow = length - i;sig1 = 0;dec1 = 0;found_digit = 0;zeros = 0;found_multiply = 1;break;
		case '0' : 
		    if(i == 0){//last char 
			sig1 = sig1 - zeros;
			sig2++;
		    }
		    else
		    {
			if( found_point == 1 ){ sig2++; }
			if( found_digit == 1 ){ sig1++; }
			zeros++;
		    } 
		    break;
		case '.' : dec1 = sig1; dec2 = length - i - pow - 1;found_point = 1; break;
		case '1' : sig1++;if(found_point == 1){sig2++;} found_digit = 1;zeros = 0; break;
		case '2' : sig1++;if(found_point == 1){sig2++;} found_digit = 1;zeros = 0; break;
		case '3' : sig1++;if(found_point == 1){sig2++;} found_digit = 1;zeros = 0; break;
		case '4' : sig1++;if(found_point == 1){sig2++;} found_digit = 1;zeros = 0; break;
		case '5' : sig1++;if(found_point == 1){sig2++;} found_digit = 1;zeros = 0; break;
		case '6' : sig1++;if(found_point == 1){sig2++;} found_digit = 1;zeros = 0; break;
		case '7' : sig1++;if(found_point == 1){sig2++;} found_digit = 1;zeros = 0; break;
		case '8' : sig1++;if(found_point == 1){sig2++;} found_digit = 1;zeros = 0; break;
		case '9' : sig1++;if(found_point == 1){sig2++;} found_digit = 1;zeros = 0; break;
		default :  break;
	    }
	    
	    if(found_power == 0){ append(exp,word[i]); } // maybe a power was used ?
        }
	
	if(found_point == 0){ sig2 = length; }	// just a number 12345
	//several possible correct way of writing...
	if( ( sig1 == sig2 + dec2 ) || ( sig1 + dec1 == sig2 + dec2 ) || ( dec1 == dec2 && sig2 == 1 ) ){ ok  = 1; } else { ok = 0; }
	
	if( found_power == 1){ // reverse appended char array ... 123+ --> +321
	    int len = strlen(exp);
	    char exponent[len];
	    int w = len - 1;
	    for(i = 0 ; i < len ; i++){
		exponent[i] = exp[w];
		w--;
	    }
	    exponent[len] = '\0';
	    if( found_multiply == 0 ){ // e+4 10^6 
		fprintf(stdout,"0,%d,%d,%d,%s,1\n",dec1,sig2,dec2,exponent);
	    }
	    else
	    {	// 1.23e6 1.23*10^5	
		fprintf(stdout,"%d,%d,%d,%d,%s,%d\n",sig1,dec1,sig2,dec2,exponent,ok);
	    }
	}
	else
	{
	    fprintf(stdout,"%d,%d,%d,%d,0,%d\n",sig1,dec1,sig2,dec2,ok);
	}
	cnt++;
	input = argv[cnt];
    }
    return (0);
}
