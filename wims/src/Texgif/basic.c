/*    Copyright (C) 2002-2003 XIAO, Gang of Universite de Nice - Sophia Antipolis
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

/* dvi 2 gif driver, tex standard */

void error(char *s)
{
    fprintf(stderr,"%s: %s\n",progname, s);
    exit(1);
}

void *xmalloc(size_t n)
{
    void *p;
    p=malloc(n);
    if(p==NULL) error("Malloc failure.");
    return p;
}

unsigned long int texint(void *bp, int l)
{
    unsigned long int o, t;
    unsigned char c, *p;
    int i;
    o=t=0; p=bp;
    for(i=0;i<l;i++) {
	c=p[i]; t=c; o<<=8; o+=t;
    }
    return o;
}

long int texintsigned(void *bp, int l)
{
    long int o, t;
    signed char c, *p;
    int i;
    if(l<=0) return 0;
    p=bp; o=*p;
    for(i=1;i<l;i++) {
	c=p[i]; t=c; o<<=8; o|=t&255;
    }
    return o;
}

	/* Strips leading spaces */
char *find_word_start(char *p)
{
    int i;
    for(i=0; isspace(*p); p++,i++);
    return p;
}

	/* Points to the end of the word */
char *find_word_end(char *p)
{
    int i;
    for(i=0;!isspace(*p) && *p!=0 && i<MAX_LINELEN; p++,i++);
    return p;
}

	/* searches a list. Returns index if found, -1 if nomatch. 
	 * Uses binary search, list must be sorted. */
int search_list(void *list, int items, size_t item_size, const char *str)
{
    int i1,i2,j,k;
    char **p;
    char c;
    
    if(items<=0) return -1;
    j=0; c=*str;
    p=list;
    k=**p-c; if(k==0) k=strcmp(*p,str);
    if(k==0) return k; if(k>0) return -1;
    p=list+(items-1)*item_size; 
    k=**p-c; if(k==0) k=strcmp(*p,str);
    if(k==0) return items-1; if(k<0) return -1;
    for(i1=0,i2=items-1;i2>i1+1;) {
	j=i1+(i2-i1)/2;
	p=list+(j*item_size);
	k=**p-c; if(k==0) k=strcmp(*p,str);
	if(k==0) return j;
	if(k>0) {i2=j; continue;}
	if(k<0) {i1=j; continue;}	
    }
    return -1;
}

	/* get the content of a file, and store in buf. */
int getfile(char *fname, unsigned char **buf)
{
    FILE *f;
    long l, l2;
    
    f=fopen(fname,"r"); if(f==NULL) return -1;
    fseek(f,0,SEEK_END); l=ftell(f); fseek(f,0,SEEK_SET);
    if(l>FILE_LENGTH_LIMIT || l<=0) {
	fclose(f); return -1;
    }
    *buf=xmalloc(l+16);
    l2=fread(*buf,1,l,f); fclose(f);
    if(l!=l2) {
	free(*buf); return -1;
    }
    return l;
}

int execredirected(char *cmdf, char *inf, char *outf, char *errf, char *arg[])
{
    pid_t pid;
    int status;

    fflush(NULL);	/* flush all output streams before forking
			 * otherwise they will be doubled */
    pid=fork(); if(pid==-1) return -1;
    if(!pid) {	/* child */
	if(inf!=NULL) freopen(inf,"r",stdin);
	if(outf!=NULL) freopen(outf,"w",stdout);
	if(errf!=NULL) freopen(errf,"w",stderr);
	if(wrapexec) {
	    setreuid(getuid(),getuid());setregid(getgid(),getgid());
	}
	if(strchr(cmdf,'/')) execv(cmdf,arg);
	else execvp(cmdf,arg);
	exit(127);
    }
    else {	/* parent */
	status=0; waitpid(pid,&status,0);
	return WEXITSTATUS(status);
    }
}

	/* system(), but with variable parms
	 * Uses sh to execute command. */
int call_sh(char *s,...)
{
    va_list vp;
    char buf[MAX_LINELEN+1];
    char *parmbuf[4];
    int t;

    va_start(vp,s);
    vsnprintf(buf,sizeof(buf),s,vp);
    va_end(vp);
    parmbuf[0]="sh"; parmbuf[1]="-c"; parmbuf[2]=buf; parmbuf[3]=NULL;
    wrapexec=0;
    t=execredirected("sh",NULL,NULL,NULL,parmbuf);
    sync(); return t;
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

