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

	/* Interface gap to wims */

/*************** Customization: change values hereafter ****************/

	/* limit of input/output file sizes */
#define fsizelim 131072
	/* gap prompt string */
#define gapprompt "gap> "
	/* This string tells gap to exit. */
#define quitstring "\nquit;\n"
	/* The way to print a string in the program. */
#define stringprinter "Print(\"%s\\n\");\n"
	/* This is GAP home page. To be kept up to date. */
#define homepage "http://www-gap.dcs.st-and.ac.uk/~gap"

char *nameofcmd="gap.sh -T -n";
int precision=20; /* default */
char header[]="\n\
";

struct {
    char *wname;    char *defaultval;
} setups[]={
};

	/* names which are not allowed */
char *illegal[]={
      "Reread","Process","Exec","Filename","SaveWorkspace"
};

	/* name parts which are not allowed */
char *illpart[]={
    "File", "Path", "Read", "To"
};

/***************** Nothing should need change hereafter *****************/

#define progname "gap"
#include "common.h"
#include "common.c"

	/* check for security violations in command string */
void check_parm(char *pm)
{
    char *pp; int l;
	  /* Underscore replacement */
    for(pp=strchr(pm,'_'); pp!=NULL; pp=strchr(pp+1,'_')) *pp='K';
    strip_trailing_spaces(pm); l=strlen(pm);
    if(l>0 && pm[l-1]!=';') strcat(pm,";");
    find_illegal(pm);
}

	/* process and print gap output */
void output(char *p)
{
    int i,n;
    char *pp, *pe, *pt;

    pp=strstr(p,gapprompt); if(pp==NULL) return;
    while((pt=strstr(pp,"\\\n"))!=NULL) strcpy(pt,pt+2);
    while(pp!=NULL) {
	pp+=strlen(gapprompt);
	pe=strstr(pp,gapprompt);
	if(pe>=pp) *pe=0;
	if(pe!=NULL && pp>=pe) {
	    emptyline:
	    puts(""); pp=pe; continue;
	}
	n=strlen(pp);
	if(n==0) goto emptyline;
		/* make every output one-line */
	for(i=0;i<n;i++) {
	    if(*(pp+i)=='\n') {
		if(*(pp+i+1)!='%') *(pp+i)=' ';
		else {*(pp+i)=0; break;}
	    }
	}
	  /* strip leading and trailing spaces */
	while(isspace(*pp) && pp<pe) pp++;
	pt=pp+strlen(pp)-1;
	while(isspace(*pt) && pt>pp) *pt--=0;
	if(*pp=='[' && *pt==']') {
	    *(pt--)=0; pp++;
	}
	puts(pp); pp=pe;
    }
}

void about(void)
{
/*    char *p;
*/
    printf("<A HREF=\"%s\">GAP4</A>",homepage); return;
/*    prepabout(quitstring,outputfname,NULL);
    if(readabout()>0) {
	p=strchr(aboutbuf,'\n'); if(p!=NULL) *p=0;
	strip_trailing_spaces(aboutbuf);
	printf("<A HREF=\"%s\">%s</A>",homepage,aboutbuf);
    }
*/
}

char *dynsetup(char *ptr, char *end)
{
    int i;
    char *p, *pp;
    for(i=0;i<SETUP_NO;i++) {
	p=getenv(setups[i].wname);
	if(p!=NULL) for(pp=p;*pp;pp++) if(!isspace(*pp) && !isalnum(*pp)) p="";
	if(p==NULL || *p==0) p=setups[i].defaultval;
    }
    return ptr;
}

int main(int argc,char *argv[])
{
    prepare1();
    run();
    return 0;    
}

