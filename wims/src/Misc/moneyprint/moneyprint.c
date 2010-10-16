/*
*********************************************************************************
* J.M. Evers 10/2010								*
* This is all amateur scriblings... So no copyrights.				*
* This source code file, and compiled objects derived from it,			*
* can be used and distributed without restriction, including for commercial use	*
* No warrenty whatoever								*
*********************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <string.h>

main( int argc , char *argv[]){
    /* test for correct argument */
    if( argc != 2){
	fprintf(stdout,"error !\nusage:\n!exec moneyprint $your_wims_item_list\nexample:\nmoney=!exec moneyprint 1.2,30.1,.4,-.23123456\nThe result is a comma separated list: 1.20,30.10,0.40,-0.23\nNote: no calculations are done.\nNote: all numbers will be rounded to 2 decimals.\n",argc - 1);
	exit(0);
    }
    /* test for illegal characters */
    const char *invalid_characters = "\n\"\'!+=ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#$%^*&()[]{}:;~><?/\\|";
    char *inp;
    inp = argv[1];
    while (*inp){
	if ( strchr(invalid_characters, *inp) ){
	    fprintf(stdout,"error !\nfound illegal character \"%c\" in argument\n",*inp);
	    return(0);
	}
	inp++;
    }
    
    int cnt;
    char *ptr;
    char *sign;
    float n,t2;
    int t1;
    int t3;
    cnt = 0;
    inp = argv[1];
    ptr = (char *) strtok(inp,",");
    while (ptr != NULL){
	sign="";
	n = atof(ptr);
	if(n > 100000000){fprintf(stdout,"error!\nNumber \"%f\" is too large for realistic money print...\n",n);return(0);}
	n = (round(100*n))/100;
	if(n < 0 ){sign = "-"; n = -1*n;}
	t1 = floor(n);
	t2 = 1000*(n - t1);
	t2=(round(t2)/1000);
	t3 = 100*t2;
	if(cnt == 0){
	    if(t3<10){fprintf(stdout,"%s%d.0%d",sign,t1,t3);}
	    else{fprintf(stdout,"%s%d.%d",sign,t1,t3);}
	}
	else
	{
	    if(t3<10){fprintf(stdout,",%s%d.0%d",sign,t1,t3);}
	    else{fprintf(stdout,",%s%d.%d",sign,t1,t3);}
	}
	cnt = 1;
        ptr = (char *)  strtok(NULL, ",");
    }
    fprintf(stdout,"\n");
    return (0);
}

