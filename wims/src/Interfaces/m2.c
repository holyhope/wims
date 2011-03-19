/*    Copyright (C) 1998-2003 XIAO, Gang of Universite de Nice - Sophia Antipolis
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

	/* Interface Macaulay2 to wims */

/*************** Customization: change values hereafter ****************/

	/* limit of input/output file sizes */
#define fsizelim 131072
	/* This string tells m2 to exit. */
#define quitstring "\nexit;\n"
	/* The way to print a string in the program. */
#define stringprinter "print(\"%s\");\n"
	/* This is m2 home page. To be kept up to date. */
#define homepage "http://www.math.uiuc.edu/Macaulay2/"

char *nameofcmd="M2";
int precision=20;	/* default */
char header[]="Thing#{Standard,BeforePrint} = toString; \
scan(methods {Standard,AfterPrint}, (a,b) -> installMethod(a,b,identity));\
";

struct {
    char *wname;    char *defaultval;	char *setname;
} setups[]={
/*	{"w_m2_precision",	"20",	"fpprec"}
*/};

	/* names which are not allowed */
char *illegal[]={
      "exec","run","fork",
      "input",  /* "load","needs", */
      "tmpname", "path", "processID",
      "getWWW", "getenv",
      "<<", "close"
};

	/* name parts which are not allowed */
char *illpart[]={
};

/***************** Nothing should need change hereafter *****************/

#define progname "m2"
#include "common.h"
#include "common.c"

	/* check for security violations in command string */
void check_parm(char *pm)
{
    find_illegal(pm);
}

char *find_prompt(char *p)
{
    char *pp=p, *pt;
    redo:
    if(*pp==0) return NULL;
    pp=strstr(pp,"\ni");
    pt=pp;
    if(pp!=NULL) {
	pp+=2; while(isdigit(*pp)) pp++;
	if(*pp!=' ') goto redo;
	while(*pp==' ') pp++;
	if(*pp!=':' || *(pp+1)!=' ') goto redo;
    }
    return pt;
}

	/* process and print m2 output */
void output(char *p)
{
    int i,n;
    char *pp, *pe, *pt;

    pp=find_prompt(p);
    while(pp!=NULL && *pp!=0) {
	pe=find_prompt(pp+1); pp=strchr(pp+1,'\n');
	if(pp==NULL) return;
	if(pe==NULL) pe=pp+strlen(pp); else *pe++=0;
	pp++;
	if(strlen(pp)==0) {
	    emptyline:
	    puts(""); pp=pe; continue;
	}
	n=strlen(pp); if(n==0) goto emptyline;
	  /* strip leading and trailing spaces */
	while(isspace(*pp) && pp<pe) pp++;
	pt=pp+strlen(pp)-1;
	while(pt>=pp && isspace(*pt)) *pt--=0;
		/* make every output one-line */
	for(i=0;i<n;i++) {
	    if(*(pp+i)=='\n') *(pp+i)='#';
	}
	puts(pp); pp=pe;
    }
}

void about(void)
{
    char *p;

    cmdparm=""; prepabout(quitstring,"/dev/null",outputfname);
    if(readabout()>0) {
	p=strchr(aboutbuf,'\n'); if(p!=NULL) *p=0;
	strip_trailing_spaces(aboutbuf);
	printf("<a href=\"%s\">%s</a>",homepage,aboutbuf);
    }
}

char *dynsetup(char *ptr, char *end)
{
    int i;
    char *p, *pp;
    
    for(i=0;i<SETUP_NO;i++) {
	p=getenv(setups[i].wname);
	if(p!=NULL) for(pp=p;*pp;pp++) if(!isspace(*pp) && !isalnum(*pp)) p="";
	if(p==NULL || *p==0) p=setups[i].defaultval;
	snprintf(ptr,end-ptr,"%s:%s;\n",setups[i].setname,p);
	ptr+=strlen(ptr);
	if(strstr(setups[i].wname,"m2_precision")!=NULL)
	  precision=atoi(p);
	if(precision<0) precision=-precision;
    }
    return ptr;
}

int main(int argc,char *argv[])
{
    prepare1();
    run();
    return 0;    
}

