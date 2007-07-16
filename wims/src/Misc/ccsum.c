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

	/* Computes class connection count (unit: student-minutes) */

#include "../wimsdef.h"
#include "../includes.h"

	/* The maximal number of sessions within one day */
#define MAX_SESSIONS (128*1024)
	/* The maximal number of classes within one day */
#define MAX_CLASSES 8192
	/* At least these minutes will be counted for each session */
#define MIN_CONNECT 2
	/* Add this number of minutes to each session */
#define MIN_ADD 1
	/* Accounting discontinues after this number of idle minutes */
#define MAX_LAPSE 15

struct {
    char s[4], u[32];
    int cl, start, end, cnt;
} ses[MAX_SESSIONS];
int sescnt;

char *datestr;

struct cls {
    int cl, cnt;
} cls[MAX_CLASSES];
int clscnt;

void *xmalloc(size_t n)
{
    void *p;
    p=malloc(n);
    if(p==NULL) {
	fprintf(stderr,"Malloc failure."); exit(1);
    }
    return p;
}

	/* Points to the end of the word */
char *find_word_end(char *p)
{
    int i;
    for(i=0;!isspace(*p) && *p!=0 && i<MAX_LINELEN; p++,i++);
    return p;
}

	/* Strips leading spaces */
char *find_word_start(char *p)
{
    int i;
    for(i=0; isspace(*p) && i<MAX_LINELEN; p++,i++);
    return p;
}

	/* Read/write to a file with variable parms to print filename */
void accessfile(char *content, char *type, char *s,...)
{
    va_list vp;
    char buf[MAX_LINELEN+1];
    FILE *f;
    int l;

    va_start(vp,s);
    vsnprintf(buf,sizeof(buf),s,vp);
    va_end(vp);
    f=fopen(buf,type); if(f==NULL) {
	if(*type=='r') content[0]=0; return;
    }
    switch(*type) {
	case 'a':
	case 'w': {
	    l=strlen(content); fwrite(content,1,l,f); break;
	}
	case 'r': {
	    l=fread(content,1,MAX_LINELEN-1,f);
	    if(l>0 && l<MAX_LINELEN) content[l]=0;
	    else content[0]=0;
	    break;
	}
	default: {
	    content[0]=0; break;
	}
    }
    fclose(f);
}

	/* returns -1 if error */
long int filelength(char *fn,...)
{
    char buf[4096];
    va_list vp;
    struct stat st;
    int l;
    
    va_start(vp,fn);
    vsnprintf(buf,sizeof(buf),fn,vp); va_end(vp);
    l=stat(buf,&st); if(l) return -1;
    return st.st_size;
}

	/* recursively generate a directory structure */
void mkdirs(char *s)
{
    struct stat st;
    char *buf;
    if(stat(s,&st)==-1) {
	if(strrchr(s,'/')!=NULL) {
	    buf=xmalloc(strlen(s)+1);
	    strcpy(buf,s); *strrchr(buf,'/')=0;
	    mkdirs(buf); free(buf);
	}
	mkdir(s,-1);
    }
}

void oneline(char *p)
{
    char tbuf[8], sbuf[8], ubuf[256], cbuf[64];
    char *p1, *p2;
    int i,t,cl;
    memmove(tbuf,p+9,6); tbuf[2]=tbuf[5]=0;
    t=atoi(tbuf)*60+atoi(tbuf+3);
    memmove(sbuf,p+18,4); sbuf[4]=0;
    p1=strchr(p,','); if(p1==NULL) return;
    if(!isdigit(*(p1+1))) return;
    snprintf(cbuf,sizeof(cbuf),"%s",p1+1);
    for(p2=cbuf;isdigit(*p2); p2++); *p2=0; cl=atoi(cbuf);
    *p1=0; for(p1--;p1>p && !isspace(*(p1-1)); p1--);
    snprintf(ubuf,sizeof(ubuf),"%s",p1);
    for(i=0;i<sescnt;i++) {
	if(cl==ses[i].cl && memcmp(sbuf,ses[i].s,4)==0 &&
	   ses[i].end>=t-MAX_LAPSE) {
	    ses[i].end=t; return;
	}
    }
    if(sescnt>=MAX_SESSIONS) return;
    memmove(ses[sescnt].s,sbuf,4); ses[sescnt].cl=cl;
    ses[sescnt].start=ses[sescnt].end=t;
    snprintf(ses[sescnt].u,sizeof(ses[sescnt].u),"%s",ubuf);
    sescnt++;
}

void onefile(char *fname)
{
    FILE *f;
    long l;
    char *fbuf, *p1, *p2, *p3;
    l=filelength(fname); if(l<=0) return;
    f=fopen(fname,"r"); if(f==NULL) return;
    fbuf=xmalloc(l+16); fread(fbuf,1,l,f); fclose(f); fbuf[l]=0;
    for(p1=fbuf; *p1; p1=p2) {
	p2=strchr(p1,'\n'); if(p2==NULL) p2=p1+strlen(p1); else *p2++=0;
	p3=strchr(p1,','); if(p3==NULL) continue;
	if(strncmp(p1,datestr,8)!=0) continue;
	oneline(p1);
    }
}

void classaccount(void)
{
    int i,j;
    clscnt=0;
    for(i=0;i<sescnt;i++) {
	ses[i].cnt=ses[i].end-ses[i].start+MIN_ADD;
	if(ses[i].cnt<MIN_CONNECT) ses[i].cnt=MIN_CONNECT;
	for(j=0;j<clscnt && ses[i].cl!=cls[j].cl;j++);
	if(j<clscnt) cls[j].cnt+=ses[i].cnt;
	else if(clscnt<MAX_CLASSES) {
	    cls[clscnt].cl=ses[i].cl;
	    cls[clscnt].cnt=ses[i].cnt;
	    clscnt++;
	}
    }
}

int clscmp(const void *c1, const void *c2)
{
    struct cls *cl1, *cl2;
    cl1=(struct cls *) c1; cl2=(struct cls *) c2;
    return cl1->cl-cl2->cl;
}

void output(void)
{
    char *p, buf[1024], dbuf[1024];
    int i,t;
    p=getenv("ccsum_outdir"); if(p==NULL || *p==0) return;
    for(i=0;i<sescnt;i++) {
	snprintf(dbuf,sizeof(dbuf),"%s/%d",p,ses[i].cl);
	mkdirs(dbuf);
	snprintf(buf,sizeof(buf),"%s.%02d:%02d %d\n",
		 datestr,ses[i].start/60,ses[i].start%60,ses[i].cnt);
	accessfile(buf,"a","%s/%s",dbuf,ses[i].u);
    }
    snprintf(dbuf,sizeof(dbuf),"%s/bydate/%.4s",p,datestr);
    mkdirs(dbuf);
    snprintf(dbuf+strlen(dbuf),sizeof(dbuf)-strlen(dbuf),"/%.2s",datestr+4);
    t=0;
    qsort(cls,clscnt,sizeof(cls[0]),clscmp);
    for(i=0;i<clscnt;i++) {
	snprintf(buf,sizeof(buf),"%s %d\n",datestr,cls[i].cnt);
	accessfile(buf,"a","%s/%d/.total",p,cls[i].cl);
	snprintf(buf,sizeof(buf),"%s %d %d\n",datestr+4,cls[i].cl,cls[i].cnt);
	accessfile(buf,"a","%s",dbuf);
	t+=cls[i].cnt;
    }
    snprintf(buf,sizeof(buf),"%s %d %d\n",datestr,t,(t+30)/60);
    accessfile(buf,"a","%s/done",p);
}

int main(int argc, char *argv[])
{
    sescnt=0;
    if(argc<2) return 1;
    datestr=getenv("ccsum_date");
    if(datestr==NULL || strlen(datestr)!=8) return 2;
    onefile(argv[1]);
    classaccount();
    output();
    return 0;
}

