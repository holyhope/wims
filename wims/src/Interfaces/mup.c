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

	/* Interface MuPAD to wims */

/*************** Customization: change values hereafter ****************/

	/* limit of input/output file sizes */
#define fsizelim 2621440
	/* String to tell the program to quit. */
#define quitstring "\nquit;\n"
	/* The way to print a string in the program. */
#define stringprinter "print(\"%s\");\n"

	/* default path setups */
char *nameofcmd="/usr/local/lib/mupad/share/bin/mupad";
int precision=20; 	/* default */

#define libpath "lib"
#define helppath "doc/ascii"
#define homepage "http://www.mupad.de/"

char header[]="log:=ln;Pi:=PI;pi:=PI;e:=E;euler:=EULER;Euler:=EULER;\n\
log10:=proc(x) begin ln(x)/ln(10); end_proc: lg:=log10;\n\
log2:=proc(x) begin ln(x)/ln(2); end_proc: \n\
i:=I;sgn:=sign;ch:=cosh;sh:=sinh;th:=tanh;\n\
arcsin:=asin;arccos:=acos;tg:=tan;arctan:=atan;arctg:=atan;\n\
Argch:=acosh;Argsh:=asinh;Argth:=atanh;argch:=acosh;argsh:=asinh;argth:=atanh;\n\
cotan:=cot;ctg:=cot;rint:=round;factorial:=fact;\n\
PRETTYPRINT:=PRETTY_PRINT;\n";

struct {
    char *wname;    char *defaultval;    char *setname;
} setups[]={
    	{"w_mup_precision",	"20",	"DIGITS"},
	{"w_mup_prettyprint",   "FALSE","PRETTY_PRINT"},
	{"w_mup_textwidth",	"1024","TEXTWIDTH"},
    	{"w_mupad_precision",	"20",	"DIGITS"},
	{"w_mupad_prettyprint",   "FALSE","PRETTY_PRINT"},
	{"w_mupad_textwidth",	"1024","TEXTWIDTH"}
};

	/* names which are not allowed */
char *illegal[]={
      "manual","help",
      "fclose","fopen","fprint","fread","ftextinput",
      "input","pathname","protocol",
      "read","system","write"
};

	/* name parts which are not allowed */
char *illpart[]={
    "plot", "PATH"
};

/***************** Nothing should need change hereafter *****************/

#define progname "mupad"
#include "common.h"
#include "common.c"

int patch_tex;

	/* verify illegal strings in parms. */
void check_parm(char *p)
{
    char *pp, *p3;
    
    	/* the character ! allows escaping into operating system */
    for(pp=strchr(p,'!');pp!=NULL; pp=strchr(pp+1,'!')) {
	if(pp<=p) {
	    bad: fprintf(stderr,"Illegal under WIMS.\n");  exit(1);
	}
	for(p3=pp-1;p3>=p && isspace(*p3); p3--);
	if(p3<p || *p3=='(' || *p3==';' || *p3=='[') goto bad;
    }
    find_illegal(p);
}

	/* process and print gp output */
void output(char *p)
{
    int n;
    char *pp, *pe, *p2, *p3;
    pp=strstr(p,"\n>>"); if(pp==NULL) return;
    pp++;
    while(pp-1!=NULL) {
	pe=strstr(pp,"\n>>");
	if(pe>=pp) *pe=0;
	p2=strchr(pp,'\n');
	if(p2==NULL) p2=pp+strlen(pp); else p2++;
	pp=p2;
	n=strlen(pp); if(n==0) {pp=pe+1; continue;}
		/* take off warning and error messages,
		 * and make every output one-line */
	p2=pp; do {
	    p3=strchr(p2,'\n');
	      /* patch for stupidities in mupad tex output */
	    if(p3>pp && *(p3-1)=='\\' && (p3==pp+1 || *(p3-2)!='\\')) {
		ovlstrcpy(p3-1,p3+1); continue;
	    }
	    if(p3!=NULL) *p3=0;
	    if(strstr(p2,"Warning")!=NULL || strstr(p2,"Error")!=NULL) {
		fprintf(stderr,"%s\n",p2);
		if(p3!=NULL) {
		    memmove(p2,p3+1,strlen(p3+1)+1); continue;
		}
		else {
		    *p2=0; break;
		}
	    }
	    if(p3!=NULL) {
		*p3=' '; p2=p3+1;
	    }
	}
	while(p3!=NULL);
	
	/* translating array to pmatrix; should be done in script. */
	for(p3=strstr(pp,"\\begin{array}"); p3!=NULL; p3=strstr(p3,"\\begin{array}")) {
	    memmove  (p3,"\\pmatrix{       ",strlen("\\begin{array}"));
	    p3+=strlen  ("\\begin{array}");
	    while(*p3!='}') *p3++=' '; *p3=' ';
	}
	for(p3=strstr(pp,"\\end{array}"); p3!=NULL; p3=strstr(p3,"\\end{array}")) {
	    memmove  (p3,"}             ",strlen("\\end{array}"));
	}
	      
	if(*pp=='[' && *(pp+strlen(pp)-1)==']') {
	    *(pp+strlen(pp)-1)=0; pp++;
	}
	/* patch latex output of \sqrt[n] */
	for(p3=strstr(pp,"\\sqrt["); p3!=NULL; p3=strstr(p3+1,"\\sqrt[")) {
	    char *p4;
	    memmove(p3,"\\ROOT{",strlen("\\ROOT{"));
	    p4=strchr(p3,']'); if(p4!=NULL) *p4='}';
	}
	/* patch of the superscript bug of mupad tex generation. */
	if(patch_tex) {
	    char *p4, *p5, c;
	    while((p4=strchr(pp,'^'))!=NULL) {
		c=*(p4+1);
		if(c=='{') {
		    *(p4+1)=0; printf("%s%c",pp,c);
		    pp=p4+2;continue;
		}
		if(c=='(') {
		    p5=find_matching(p4+2,')');
		    if(p5!=NULL) {
			*(p4+1)='{'; *p5=0;
			printf("%s}",pp);pp=p5+1;
		    }
		    else {
			*(p4+1)=0; printf("%s",pp); pp=p4+2;
		    }
		    continue;
		}
		*(p4+1)=0; p4+=2;
		printf("%s{%c",pp,c);
		while(isdigit(*p4) || *p4=='.') printf("%c",*p4++);
		printf("}");pp=p4;
	    }
	}
	puts(find_word_start(pp)); pp=pe+1;
    }
}

void about(void)
{
    char *p, *pp;

    prepabout(quitstring,outputfname,NULL);
    if(readabout()>0) {
        for(p=aboutbuf;*p!=0 && memcmp(p,"MuPAD",5)!=0;
	    p=find_word_start(find_word_end(p)));
	if(*p!=0) {
	    pp=find_word_start(find_word_end(p));
	    pp=find_word_end(pp); *pp=0;
	    printf("<A HREF=\"%s\">%s</A>",homepage,p);
	}
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
	snprintf(ptr,end-ptr,"%s:=%s;\n",setups[i].setname,p);
	ptr+=strlen(ptr);
	if(strstr(setups[i].wname,"mupad_precision")!=NULL)
	  precision=atoi(p);
	if(precision<0) precision=-precision;
    }
    return ptr;
}

int main(int argc,char *argv[])
{
    char *p;
    
    p=getenv("w_mupad_tex_patch");
    if(p!=NULL && *p!=0) patch_tex=1; else patch_tex=0;
    prepare1();
    run();
    if(!isabout) setenv("w_mupad_tex_patch","",1);
    return 0;    
}

