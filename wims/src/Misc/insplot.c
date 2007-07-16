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

	/* Interface gnuplot to wims */

/*************** Customization: change values hereafter ****************/

#define tmpdir "/tmp"
	/* limit of input/output file sizes */
#define fsizelim 131072
	/* limit of parameter string */
#define parmlim 131072
	/* number of versions */
#define versions 2
	/* gp prompt string */
#define gpprompt "\n? "
	/* string which defines the start of gp output 
	 * (in order to cut gp header) */
#define startstring "start line 49521845"
	/* This is the good bye string of gp, signaling end of output. */
#define goodbyestring "? Good bye!"

char header[]="Pi=pi\n\
PI=pi\n\
e=exp(1)\n\
E=exp(1)\n\
ln(x) = log(x)\n\
ch(x) = cosh(x)\n\
sh(x) = sinh(x)\n\
th(x) = tanh(x)\n\
arccos(x) = acos(x)\n\
arcsin(x) = asin(x)\n\
tg(x)	  = tan(x)\n\
arctan(x) = atan(x)\n\
arctg(x)  = atan(x)\n\
Argch(x)  = acosh(x)\n\
Argsh(x)  = asinh(x)\n\
Argth(x)  = atanh(x)\n\
argch(x)  = acosh(x)\n\
argsh(x)  = asinh(x)\n\
argth(x)  = atanh(x)\n\
set samples 400\n\
";

/***************** Nothing should need change hereafter *****************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>

#define SETUP_NO (sizeof(setups)/sizeof(setups[0]))
#define MYNAME_NO (sizeof(name2version)/sizeof(name2version[0]))

	/* gpversion=0: gp1.39; gpversion=1: gp2.0. */
int gpversion, mypid, precision;
char inputfname[256], outputfname[256];
char *parm;

void *xmalloc(size_t n)
{
    void *p;
    p=malloc(n);
    if(p==NULL) {
	fprintf(stderr, "pari: Malloc failure.");
	exit(1);
    }
    return p;
}

	/* system(), but with variable parms */
int call_sh(char *s,...)
{
    va_list vp;
    char buf[1024];
    
    va_start(vp,s);
    vsnprintf(buf,sizeof(buf),s,vp);
    va_end(vp);
    return system(buf);
}

	/* check for security violations in command string */
void check_parm(void)
{
    char *p;
    for(p=parm;*p!=0;p++) {
	  /* no espace commands. */
	if(*p!='\n') continue;
	while(*p!=0 && isspace(*p)) p++;
	if(*p=='\\' && *(p+1)!='v') *p='.';
    }
}

	/* patches the gnuplot integer division (mis)feature. */
void gnuplot_patch(char *p,int oneline)
{
    char *pp;
    for(pp=strchr(p,'/');pp!=NULL;pp=strchr(pp+1,'/')) {
	char *p1;
	if(pp<=p || !isdigit(*(pp-1)) || !isdigit(*(pp+1))) continue;
	for(p1=pp-2;p1>=p && isdigit(*p1);p1--);
	if(p1>=p && *p1=='.') continue;
	for(p1=pp+2;*p1 && isdigit(*p1);p1++);
	if(*p1=='.') continue;
	string_modify(p,p1,p1,".0");
    }
    for(pp=strchr(p,'^');pp!=NULL;pp=strchr(pp+1,'^'))
      string_modify(p,pp,pp+1,"**");
    	/* disallow new lines and ';' */
    if(oneline)
      for(pp=p;*pp!=0;pp++) if(*pp==';' || *pp=='\n') *pp=' ';
}

	/* This is to disable pipe in the gnuplot plotting function.
	 * We do not allow ' followed by < . */
void prepare_insplot_parm(char *p)
{
    int i,j; char *pp, *s;
    double d;
    char setbuf[MAX_LINELEN+10],buf[MAX_LINELEN+1];
    
    j=strlen(p);
      /* pipe in plot command */
    for(i=0;i<j;i++) {
	if(*(p+i)!='\'' && *(p+i)!='"') continue;
	pp=find_word_start(p+i+1); if(*pp=='<') {
	    module_error("illegal_plot_cmd"); exit(1);
	}
    }
    gnuplot_patch(p,1);
	/* multiplot */
    pp=getvar("insplot_split");i=evalue(pp);
	/* arbitrary limit: 16 multiplots */
    if(i>0 && i<=16) {
	char tbuf[MAX_LINELEN+1];
	snprintf(buf,sizeof(buf),"%d",i); setenv("multiplot",buf,1);
	for(j=1;j<=i;j++) {
	    snprintf(buf,sizeof(buf),"insplot_parm_%d",j);
	    pp=getvar(buf);
	    snprintf(tbuf,sizeof(tbuf),"%s",pp);
	    gnuplot_patch(tbuf,1);
	    setenv(buf,tbuf,1);
	}
	
    }
	/* no illegal chaining */
    pp=getvar("insplot_font"); if(pp!=NULL) {
	for(s=pp;s<pp+MAX_LINELEN && *s;s++) 
	  if(*s==';' || *s=='\n' || *s==' ') *s=0;
	if(s>=pp+MAX_LINELEN) *s=0;
	setvar("insplot_font",pp);
    }
    pp=getvar("insplot_set"); if(pp!=NULL) {
	char tbuf[MAX_LINELEN+1];
	snprintf(tbuf,sizeof(tbuf),"%s",pp);
	i=strlen(tbuf)-1;
	while(i>0 && isspace(tbuf[i])) i--;
	if(tbuf[i]==';') tbuf[i]=0;
	gnuplot_patch(tbuf,0);pp=tbuf;
	strcpy(setbuf,"set "); j=strlen("set ");
	for(i=0; *(pp+i)!=0 && j<MAX_LINELEN; i++) {
	    if(*(pp+i)=='\n') {setbuf[j++]=' '; continue;}
	    if(*(pp+i)!=';') {setbuf[j++]=*(pp+i); continue;}
	    strcpy(setbuf+j,"\nset "); j+=strlen("\nset ");
	}
	setbuf[j]=0;
	setenv("insplot_set",setbuf,1);
    }
    else setenv("insplot_set","",1);
      /* frames of animation */
    pp=getvar("ins_anim_frames");
    if(pp!=NULL) i=evalue(pp); else i=1;
    if(i>=INS_LIMIT) i=INS_LIMIT-1; if(i<1) i=1;
    if(strstr(setbuf,"step")==NULL && strstr(p,"step")==NULL
       && varchr(setbuf,"s")==NULL && varchr(p,"s")==NULL) i=1;
    snprintf(buf,sizeof(buf),"%d",i);
    setenv("ins_anim_frames",buf,1);
    setvar("ins_anim_frames","");
      /* delay of animation */
    pp=getvar("ins_anim_delay");
    if(pp!=NULL) d=evalue(pp); else d=0;
    if(d>=10) d=10; if(d<0) d=0;
    i=d*100;
    snprintf(buf,sizeof(buf),"%d",i);
    setenv("ins_anim_delay",buf,1);
}

	/* strip trailing zeros */
void strip_zeros(char *p)
{
    char *pp, *p2, *numend, *ee;
    int i;
    for(pp=p;*pp!=0;pp++) {
	if(!isdigit(*pp)) continue;
	i=0;
	for(numend=pp;isdigit(*numend) || *numend=='.';numend++)
	  if(*numend=='.') i=1;
	if(i==0) {
	    pp=numend-1;continue;
	}
	for(p2=numend;p2>pp && *(p2-1)=='0';p2--);
	for(ee=numend;isspace(*ee);ee++);
	if(*(pp+1)=='.' && (*ee=='E' || *ee=='e') 
	   && *(ee+1)=='-') {
	    int k=0;
	    char *pt=ee+2;
	    while(isdigit(*pt)) {
		k*=10;k+=*pt-'0';pt++;
	    }
	    if(k>precision*2 || (k>precision && *pp=='0')) {
		
		sprintf(pp,"0.0%s",pt);
		
		pp+=strlen("0.0")-1;
		continue;
	    }
	}
	
	if(*(p2-1)=='.' && p2<numend) p2++; 
	
	if(p2<numend) {
	    strcpy(p2,numend);numend=p2;
	}
	pp=numend-1;
    }
}

	/* process and print gp output */
void output(char *p)
{
    int i,n;
    char *pp, *pe, *pt;
    pp=strstr(p,startstring);
    if(pp==NULL) return;
    pp=strstr(pp,gpprompt); if(pp==NULL) return;
    pe=strstr(pp,goodbyestring);
    if(pe>=pp) *pe=0;
    while(pp!=NULL) {
	pp++;
	pe=strstr(pp,gpprompt);
	if(pe>=pp) *pe=0;
	pp=strchr(pp,'\n');
	if(pp==NULL) {
	    emptyline:
	    puts(""); pp=pe; continue;
	}
	pp++; n=strlen(pp);
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
	while(isspace(*pt) && pt>pp) pt--;
	  /* remove parentheses of matrix output */
	if(memcmp(pp,"Mat(",4)==0 && *pt==')') {
	    *(pt--)=0; pp+=4;
	}
	if(*pp=='[' && *pt==']') {
	    *(pt--)=0; pp++;
	}
	strip_zeros(pp);
	puts(pp); pp=pe;
    }
}

void call_gnuplot(void)
{
    int i,r;
    char *p;
    FILE *ff;
    struct timeval t;
    
    setenv(gprcenv,gprc[gpversion],1);
    mypid=getpid();
    snprintf(inputfname,sizeof(inputfname),"%s/gp_input.%d",tmpdir,mypid);
    snprintf(outputfname,sizeof(outputfname),"%s/gp_output.%d",tmpdir,mypid);
    ff=fopen(inputfname,"w");
    if(ff==NULL) {
	fprintf(stderr,"insplot: cannot open file %s.\n",inputfname); exit(1);
    }
    gettimeofday(&t,NULL);
    r=t.tv_usec*t.tv_sec;
    fprintf(ff,"\nsetrand(%d)\n",r);
    for(i=0;i<SETUP_NO;i++) {
	p=getenv(setups[i].wname);
	if(p==NULL || *p==0) p=setups[i].defaultval;
	fprintf(ff,"%s%s\n",setups[i].gpset[gpversion],p);
	if(strstr(setups[i].wname,"pari_precision")!=NULL)
	  precision=atoi(p);
	if(precision<0) precision=-precision;
    }
    fputs(header,ff);
    fprintf(ff,"print(\"%s\")\n",startstring);
    check_parm();
    fwrite(parm,1,strlen(parm),ff);
    fclose(ff);
    call_sh("%s <%s >%s",gpcmd[gpversion],inputfname,outputfname);
    ff=fopen(outputfname,"r");
    if(ff!=NULL) {
	long int l;
	char *obuf;
	fseek(ff,0,SEEK_END); l=ftell(ff); fseek(ff,0,SEEK_SET);
	if(l<0) l=0; if(l>fsizelim) l=fsizelim;
	obuf=xmalloc(l+1);
	l=fread(obuf,1,l,ff); fclose(ff);
	if(l>0) obuf[l]=0; else obuf[0]=0;
	output(obuf);	
    }
    unlink(inputfname); unlink(outputfname);
}

int main(int argc,char *argv[])
{
    char *p;
    int i;
	/* Must have at least 2 parameters. */
    if(argc<3) return 0;
    parm=getenv("ins_source");
    	/* nothing to do if no parameter */
    if(parm==NULL || *parm==0) return 0;
    i=strlen(parm); if(i<0 || i>parmlim) {
	fprintf(stderr,"insplot..processor: parameter too long. \n"); exit(1);
    }
    call_gnuplot();
    return 0;    
}

