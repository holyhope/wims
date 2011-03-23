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

		/* Caches and its management */

	/* General information of an exercise. Size: 10 bytes. */
typedef struct exodata {
    unsigned short int num;
    float weight, require;
} exodata;

struct classdata {
    char name[MAX_CLASSLEN+1];
    time_t start, last, modif;
    int exocnt, examcnt, examstart, access;
    struct exodata exos[MAX_CLASSEXOS];
    char ctbuf[CTBUFLEN];
    short int ctptr[MAX_EXOS];
} classdata[MAX_CLASSCACHE];

struct classcache {
    struct classdata *ptr;
} classcache[MAX_CLASSCACHE];
int classcaches;

struct sheetdata {
    char buffer[SHEETBUFLEN];
    int name,header,status,exocnt,exo[MAX_EXOS];
    time_t start, last;
    int access;
} sheetdata[MAX_SHEETCACHE];

struct sheetcache {
    struct sheetdata *ptr;
} sheetcache[MAX_SHEETCACHE];
int sheetcaches;

 	/* searches a list. Returns index if found, -1 if nomatch. 
	 * Uses binary search, list must be sorted. */
int search_data(void *list, int items, size_t item_size, unsigned short int t)
{
    int i1,i2,j,k;
    unsigned short int *p;
    
    if(items<=0) return -1;
    j=0; p=list; k=*p-t;
    if(k==0) return k; if(k>0) return -1;
    p=list+(items-1)*item_size; 
    k=*p-t; if(k==0) return items-1; if(k<0) return ~items;
    for(i1=0,i2=items-1;i2>i1+1;) {
	j=(i2+i1)/2;
	p=list+(j*item_size);
	k=*p-t;
	if(k==0) return j;
	if(k>0) {i2=j; continue;}
	if(k<0) {i1=j; continue;}	
    }
    return ~i2;
}

	/* remove old cache items */
void cleancache(void)
{
    int i;
    time_t now;
    struct classdata *cd;
    struct sheetdata *sd;
    now=time(NULL);
    for(i=0;i<classcaches;i++) {
	cd=classcache[i].ptr;
	if(now<cd->start+CLASSCACHE_DELAY) continue;
	cd->access=0;
	memmove(classcache+i,classcache+i+1,(classcaches-i-1)*sizeof(classcache[0]));
	classcaches--;
    }
    for(i=0;i<sheetcaches;i++) {
	sd=sheetcache[i].ptr;
	if(now<sd->start+SHEETCACHE_DELAY) continue;
	sd->access=0;
	memmove(sheetcache+i,sheetcache+i+1,(sheetcaches-i-1)*sizeof(sheetcache[0]));
	sheetcaches--;
    }
}

	/* Locate the cache number of a class */
struct classdata *getclasscache(char *cl)
{
    int i,j,k,l,m,n, oldest;
    struct stat st;
    struct classdata *cd;
    char buf[MAX_LINELEN+1], buf2[MAX_LINELEN+1];
    char *p1, *p2, *q1, *q2;
    time_t tt;
    tt=0, oldest=0;
    for(i=0;i<classcaches;i++) {
	cd=classcache[i].ptr;
	if(tt>cd->start) {tt=cd->start; oldest=i;}
	if(strcmp(cd->name,cl)==0) {
	    cd->access++;
	    return cd;
	}
    }
    if(classcaches>=MAX_CLASSCACHE) {
	i=oldest;cd=classcache[i].ptr;
	cd->access=0;
	memmove(classcache+i,classcache+i+1,(classcaches-i-1)*sizeof(classcache[0]));
	classcaches--;
    }
    for(i=0;i<MAX_CLASSCACHE && classdata[i].access>0; i++);
    if(i>classcaches) return NULL;
    cd=classdata+i; cd->access=1;
    classcache[classcaches++].ptr=cd;
    snprintf(cd->name,sizeof(cd->name),"%s",cl);
    cd->start=time(NULL); cd->exocnt=0;
	/* Now get the exo data */
    accessfile(buf,"r","sheets/.require");
    for(i=k=0,p1=buf; *p1; i++,p1=p2) {
	p2=strchr(p1,'\n'); if(p2) *p2++=0; else p2=p1+strlen(p1);
	for(j=0,q1=find_word_start(p1); *q1 && k<MAX_CLASSEXOS; j++,q1=find_word_start(q2)) {
	    q2=find_word_end(q1); if(*q2) *q2++=0;
	    cd->exos[k].num=(i<<8)+j;cd->exos[k].require=atof(q1);
	    cd->exos[k].weight=0;
	    k++;	    
	}
	
    }
    if(k>=MAX_CLASSEXOS) return NULL;
    cd->exocnt=k; cd->examstart=k; cd->modif=0;
    accessfile(buf,"r","sheets/.weight");
    for(i=k=0,p1=buf; *p1; i++,p1=p2) {
	p2=strchr(p1,'\n'); if(p2) *p2++=0; else p2=p1+strlen(p1);
	for(j=0,q1=find_word_start(p1); *q1 && k<MAX_CLASSEXOS; j++,q1=find_word_start(q2)) {
	    q2=find_word_end(q1); if(*q2) *q2++=0;
	    if(cd->exos[k].num==(i<<8)+j) {
		cd->exos[k].weight=atof(q1);
		k++;
	    }
	    else while(k<cd->exocnt && cd->exos[k].num<(i<<8)+j) k++;
	}
    }
    if(stat("exams/.exams",&st)==0) cd->modif=st.st_mtime; else return cd;
    accessfile(buf,"r","exams/.exams");
    if(buf[0]==0) return cd;
    if(buf[0]==':') p1=buf-1; else p1=strstr(buf,"\n:");
    for(n=m=0,k=cd->exocnt; p1 && k<MAX_CLASSEXOS && m<MAX_EXOS; p1=p2,m++) {
	p1+=2;
	p2=strstr(p1,"\n:"); if(p2) *p2=0;
//	if(*find_word_start(p1)<'1') continue;	/* status */
	fnd_line(p1,3,buf2); if(buf2[0]==0) continue;
	q1=find_word_start(buf2); q2=find_word_end(q1);
	if(*q2) *q2++=0;
	q2=find_word_start(q2); *find_word_end(q2)=0;
	i=atoi(q1); j=atoi(q2); if(i<=0 || j<=0) continue;
	cd->exos[k].num=0xFF00+m;
	cd->exos[k].weight=i; cd->exos[k].require=j;	/* weight: duration. require: retries */
	fnd_line(p1,6,buf2); q1=find_word_start(buf2);
	singlespace(q1); strip_trailing_spaces(q1);
	cd->ctptr[k-cd->exocnt]=n; cd->ctbuf[n]=0;
	if(n+strlen(q1)>CTBUFLEN-MAX_EXOS-16) *q1=0;	/* silent truncation */
	l=strlen(q1)+1; memmove(cd->ctbuf+n,q1,l); n+=l;
	k++;
    }
    cd->examcnt=k-cd->exocnt; cd->exocnt=k;
    return cd;
}

	/* prepare cache for a sheet */
struct sheetata *getsheetcache(char *cl, char *sh)
{
    
    
    
    return NULL;
}

