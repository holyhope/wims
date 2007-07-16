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

	/* Interface Yacas to wims */

/*************** Customization: change values hereafter ****************/

	/* This is yacas home page. To be kept up to date. */
#define homepage "http://yacas.sourceforge.net/"
	/* String to tell the program to quit. */
#define quitstring "\nquit\n"
	/* The way to print a string in the program. */
#define stringprinter "\"%s\"\n"
	/* limit of input/output file sizes */
int fsizelim=131072;
int precision=20; 	/* default */

char *inprompt="\nIn>";
char *outprompt="Out>";

char *nameofcmd="yacas -p";

#include "yacasheader.c"

struct {
    char *wname;    char *defaultval;    char *yacasset;
} setups[]={
      {"w_yacas_precision",	"20",	"\\precision=",},
      {"w_yacas_serieslength",	"8",	"\\serieslength="}
};

	/* names which are not allowed */
char *illegal[]={
    "SystemCall", "Use", "Vi", "GetYacasPID", "ShowPS",
      "MakeFunctionPlugin"
};

	/* name parts which are not allowed */
char *illpart[]={
    "File", "Load", "Plot"
};

/***************** Nothing should need change hereafter *****************/

#define progname "yacas"
#include "common.h"
#include "common.c"

	/* check for security violations in command string */
void check_parm(char *pm)
{
    char *p, *pp, *p2, buf[16];
    int i;
    
    for(p=pm;*p!=0;p++) {
	if(*p!='\\') continue;
	if(*(p+1)=='\n') *p=*(p+1)=' ';
	if(*(p+1)==0) *p=' ';
    }
    for(p=pm; *p!=0; p++) {
	if(!isalpha(*p)) continue;
	for(p2=p+1; isalpha(*p2); p2++);
	if(p2-p>10) {p=p2-1; continue;}
	memmove(buf,p,p2-p); buf[p2-p]=0; pp=p; p=p2-1;
	for(p2=buf; islower(*p2); p2++);
	if(*p2) continue;
	i=search_list(firstupper,firstupperno,sizeof(firstupper[0]),buf);
	if(i>=0) *pp=toupper(*pp);
    }
    find_illegal(pm);
}


	/* process and print yacas output */
void output(char *p)
{
    int i,n;
    char *pp, *pe, *p1, *pt;
    char outbuf[MAX_LINELEN+1];
    
    pp=strstr(p,inprompt); if(pp==NULL) return;
    while(pp!=NULL && *pp!=0) {
	pp+=strlen(inprompt); p1=find_word_start(pp);
	pe=strstr(pp,outprompt);
	pt=strstr(pp,inprompt);
	if(pe==NULL || (pt!=NULL && pt<pe)) { /* error */
	    if(pt==NULL) pp=pp+strlen(pp); else pp=pt;
	    n=pp-p1; if(n>MAX_LINELEN) n=MAX_LINELEN; if(n<0) n=0;
	    memmove(outbuf,p1,n); outbuf[n]=0;
	    fprintf(stderr,"%s\n",outbuf);
	    puts(""); continue;
	}
	else {
	    *pe=0; pe=find_word_start(pe+strlen(outprompt));
	}
	pp=strstr(pe,inprompt);
	if(pp==NULL) pp=pe+strlen(pe);
	if(*p1==0) {
	    if(pp>=pe+sizeof(outbuf)) break;
	    n=pp-pe; if(n>MAX_LINELEN) n=MAX_LINELEN; if(n<0) n=0;
	    memmove(outbuf,pe,n); outbuf[n]=0;
	}
	else {
	    snprintf(outbuf,sizeof(outbuf),"%s",p1);
	    n=strlen(outbuf);
	}
		/* make every output one-line */
	for(i=0;i<n;i++) {
	    if(outbuf[i]=='\n') outbuf[i]=' ';
	}
	  /* strip leading and trailing spaces */
	for(i=n-1;i>=0 && isspace(outbuf[i]); i--) outbuf[i]=0;
	if(outbuf[i]==';') outbuf[i]=0;
	for(pe=outbuf; *pe; pe++) if(isupper(*pe)) *pe=tolower(*pe);
	for(pe=outbuf; isspace(*pe); pe++);
	/* strip_zeros(pe); */
	puts(pe);
    }
}

void about(void)
{
    cmdparm="-v"; prepabout("",outputfname,NULL);
    if(readabout()>0)
      printf("<A HREF=\"%s\">Yacas %s</A>",homepage,aboutbuf);
}

char *dynsetup(char *ptr, char *end)
{
    int i; char *p, *pp;
    
    for(i=0;i<SETUP_NO;i++) {
	p=getenv(setups[i].wname);
	if(p!=NULL) for(pp=p;*pp;pp++) if(!isspace(*pp) && !isalnum(*pp)) p="";
	if(p==NULL || *p==0) p=setups[i].defaultval;
	if(strstr(setups[i].wname,"yacas_precision")!=NULL)
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

