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
	/* line input / output / translation routines
	 * and error routines */

#include <stdarg.h>

	/* these are patches for rawmath.c */
char *getvar(char *p) {return NULL;}
void setvar(char *p, char *v) {return;}

void error(char *p)
{
    fprintf(stderr,"%s\n",p);
}

void bailout(int i1, int i2, char *msg)
{
    if(*msg) error(msg);
    printf("%d %d",i1,i2); exit(0);
}

	/* find html tag end */
char *find_tag_end(char *p)
{
    char *pp;
    
    p++; if(*p=='!') {
	if(*(p+1)=='-' && *(p+2)=='-') {
	    pp=strstr(p,"-->"); if(pp==NULL) return p+strlen(p);
	    else return p+2;
	}
    }
    /* else */ {
	pp=strchr(p,'>'); if(pp==NULL) return p+strlen(p); 
	else return pp;
    }
    	/* Now the following is not executed. */
/*    for(pp=p;*pp;pp++) {
	switch(*pp) {
	    case '>': return pp;
	    case '"': {
		pp=strchr(++pp,'"'); if(pp==NULL) return p+strlen(p);
		break;
	    }
	    default: break;
	}
    }
    return pp;
*/
}

	/* Points to the end of a name */
char *find_name_end(char *p)
{
    int i;
    for(i=0;isalnum(*p) && i<MAX_LINELEN; p++,i++);
    return p;
}

	/* Find the beginning of a name */
char *find_name_start(char *p)
{
    int i;
    for(i=0; !isalpha(*p) && i<MAX_LINELEN; p++,i++);
    return p;
}

void collapse_item(char *p, int n)
{
    int i;
    char *pp;
    if(n<1) return;
    for(i=1,pp=strchr(p,','); i<n && pp!=NULL; i++,pp=strchr(pp+1,','));
    if(pp==NULL) *p=0;
    else strcpy(p,pp+1);
}

	/* modify a string. Bufferlen must be ast least MAX_LINELEN */
void string_modify2(char *start, char *bad_beg, char *bad_end, char *good,...)
{
    char buf[MAX_LINELEN+1];
    va_list vp;
    
    va_start(vp,good);
    vsnprintf(buf,sizeof(buf),good,vp); va_end(vp);
    if(strlen(start)-(bad_end-bad_beg)+strlen(buf)>=MAX_LINELEN)
      bailout(inlen,0,"string too long");
    strcat(buf,bad_end);
    strcpy(bad_beg,buf);
}

	/* strcmp() to be used within qsort(). */
int _scmp(const void *p1, const void *p2)
{
    const char **s1,**s2;
    
    s1=(const char **) p1; s2=(const char **) p2;
    return strcmp(*s1,*s2);
}

char *substit(char *p)
{
    char *pp;
    while((pp=strchr(p,'$'))!=NULL) *pp=' ';
    return p;
}

