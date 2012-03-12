/*
*********************************************************************************
* J.M. Evers 10/2010								*
* This is all amateur scriblings... So no copyrights.				*
* This source code file, and compiled objects derived from it,			*
* can be used and distributed without restriction, including for commercial use	*
* No warrenty whatoever								*
*********************************************************************************
2/2012
 modified for general rounding usage; a word 'DECIMALS' can be added to the list of numbers
 !exec moneyprint 2.1,4.123,5  2   // 2 decimals
 2.10,4.12,5.00
 !exec moneyprint 2.1,4.123,5  4   // 4 decimals
 2.1000,4.1230,5.0000

 !exec moneyprint 2.1,4.123,5
 2.10,4.12,5.00
 
 default value (or old syntax) is 2 decimals  
    
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc , char *argv[]){
    /* test for correct argument */
    int DECIMALS;

    if(argv[2] != NULL){DECIMALS = atoi(argv[2]);}else{DECIMALS = 2;}

    if( argc != 2 && argc != 3){
	fprintf(stdout,"error !\nusage:\n!exec moneyprint $your_wims_item_list $precision_word\nexample:\nmoney=!exec moneyprint 1.2,30.1,.4,-.23123456 2\nThe result is a comma separated list: 1.20,30.10,0.40,-0.23\n using 2 decimals\nNote: no calculations are done.\nNote: all numbers will be rounded to 2 decimals.\n");
	exit(0);
    }

    /* test for illegal characters */
    const char *invalid_characters = "\n\"\'!+=ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#$%^*&()[]{};:~><?/\\|";
    int cnt;
    char *inp,*ptr;
    inp = argv[1];
    while (*inp){
	if ( strchr(invalid_characters, *inp) ){
	    fprintf(stdout,"error !\nfound illegal character \"%c\" in argument\n",*inp);
	    return(0);
	}
	inp++;
    }

    cnt = 0;
    inp = argv[1];
    ptr = (char *) strtok(inp,",");
    while( ptr != NULL){
	if(cnt != 0 ){fprintf( stdout ,",");}
	switch (DECIMALS){
	    
	    case 0  : fprintf( stdout , "%.0f" , atof(ptr) );break;
	    case 1  : fprintf( stdout , "%.1f" , atof(ptr) );break;
	    case 2  : fprintf( stdout , "%.2f" , atof(ptr) );break;
	    case 3  : fprintf( stdout , "%.3f" , atof(ptr) );break;
	    case 4  : fprintf( stdout , "%.4f" , atof(ptr) );break;
	    case 5  : fprintf( stdout , "%.5f" , atof(ptr) );break;
	    case 6  : fprintf( stdout , "%.6f" , atof(ptr) );break;
	    case 7  : fprintf( stdout , "%.7f" , atof(ptr) );break;
	    case 8  : fprintf( stdout , "%.8f" , atof(ptr) );break;
	    case 9  : fprintf( stdout , "%.9f" , atof(ptr) );break;
	    case 10 : fprintf( stdout , "%.10f", atof(ptr) );break;

	    default : fprintf( stdout , "%.2f" , atof(ptr) );
	}
	cnt=1;
	ptr = (char *) strtok(NULL,",");
    }
    fprintf(stdout,"\n");
    return (0);
}

