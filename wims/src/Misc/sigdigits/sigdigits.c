/*
*********************************************************************************
* J.M. Evers 3/2012								*
* This is all amateur scriblings... So no copyrights.				*
* This source code file, and compiled objects derived from it,			*
* can be used and distributed without restriction, including for commercial use	*
* No warrenty whatsoever							*
*********************************************************************************


usage:
1) discard trailing zeros : use no flags (default)
!exec sigdigits 1.10000 2.0001000 123.0100010000
2,1  
5,4  
9,6

or use flag "0"
!exec sigdigits 1.10000,0 2.0001000,0 123.0100010000,0
2,1  
5,4  
9,6

2) include trailing zeros : use flag "1" (due to accuracy measurement...)
!exec sigdigits 1.10000,1 2.0001000,1 123.0100010000,1
7,5
9,7
14,10

3) scientific notation allowed:
!exec sigdigits 1.2300000*10^15
3,2
!exec sigdigits 1.2300001*10^15
8,7
!exec sigdigits 1.2300000e+15
3,2
!exec sigdigits 1.2300001e+15
8,7

4) all other 'numbers' using pi,log,ln,sin,etc...will produce an error 

5)output "2 items per line"
    first item is total amount of significant digits
    second item is amount of decimals

6) no evaluation on the 'size' of the number is performed.

It can be used in an answer checkfile,
to check if the pupil uses the correct amount of significant digits in the reply .
Example:
A circle with "R=2.01 cm" has a surface area of ? 
The 'math' answer is approx 12.69234847976812366271292553 cm2
The 'physics' answer is 12.7 ... using 3 significant digits 
(due to the precision of the given R. note: there is no checking of the unit 'cm')


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DIGITS 64
#define MAX_CONV 64


int main( int argc , char *argv[]){
    if( argc < 2){
	fprintf(stdout,"syntax error\n");
	exit(0);
    }
    char word[MAX_DIGITS];
    char *input;
    int use_all_zeros,cnt,i,length,zeros,significance,found_digit,found_point,decimals;
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
	decimals = 0;
	significance = 0;
	zeros = 0;
	use_all_zeros = 0; // trailing zeros are not significant...unless
	for( i = length - 1 ; i >= 0 ; i--){ // walk from rightside to left through the 'number'
	    switch( word[i] ){
		case '*' : significance = 0;decimals = 0;found_digit = 0;zeros = 0;break;
		case 'e' : significance = 0;decimals = 0;found_digit = 0;zeros = 0;break;
		case 'E' : significance = 0;decimals = 0;found_digit = 0;zeros = 0;break;
		case ',' : // signaling a flag '1'
		    if( i+1 < length ){ 
			if(word[i + 1] == '1'){ use_all_zeros = 1;}
		    } 
		    significance = 0;
		    decimals = 0;
		    found_digit = 0;
		    zeros = 0;
		    break;
		case '0' : 
		    if(i == 0){//last char
			significance = significance - zeros;
		    }
		    else
		    {
			if( found_digit == 1 ){
		    	    significance++;
			}
			else
			{
			    if( found_point == 0 && use_all_zeros == 1){
				significance++;
			    }
			}
			zeros++;
		    } 
		    break;
		case '.' : decimals = significance; found_point = 1; break;
		case '1' : significance++;found_digit = 1;zeros = 0; break;
		case '2' : significance++;found_digit = 1;zeros = 0; break;
		case '3' : significance++;found_digit = 1;zeros = 0; break;
		case '4' : significance++;found_digit = 1;zeros = 0; break;
		case '5' : significance++;found_digit = 1;zeros = 0; break;
		case '6' : significance++;found_digit = 1;zeros = 0; break;
		case '7' : significance++;found_digit = 1;zeros = 0; break;
		case '8' : significance++;found_digit = 1;zeros = 0; break;
		case '9' : significance++;found_digit = 1;zeros = 0; break;
		default :  break;
	    }
        }
	cnt++;
	input = argv[cnt];
	fprintf(stdout,"%d,%d\n",significance,decimals);
    }
    return (0);
}
