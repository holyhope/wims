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

	/* these are patches for rawmath.c */
char *getvar(char *p) {return NULL;}
void setvar(char *p, char *v) {return;}

char *exec_if(char *p)
{
    char *p1, *p2, *p3, *p4, *p5, *p6, *pp;
    char buf[MAX_LINELEN+1];
    p1=find_word_start(p); if(*p1!='{') return p;
    p2=find_matching(p1+1,'}'); if(p2==NULL) return p;
    p3=find_word_start(p2+1); if(*p3!='{') return p;
    p4=find_matching(p3+1,'}'); if(p4==NULL) return p;
    *p2=0; snprintf(buf,sizeof(buf),"%s",p1+1);
    for(pp=strchr(buf,'\\'); pp!=NULL; pp=strchr(pp+1,'\\')) {
	if(isalnum(*(pp+1))) string_modify(buf,pp,pp+1,"$m_");
    }
    fprintf(outf," \n!if %s \n$()",buf);
    p5=find_word_start(p4+1);
    if(*p5=='{' && (p6=find_matching(p5+1,'}'))!=NULL) {
	*p4=elsechar; *p5=' '; *p6=endifchar;
    }
    else *p4=endifchar;
    return p3+1;
}

char *exec_for(char *p)
{
    char *p1, *p2, *p3, *p4, *pp;
    char buf[MAX_LINELEN+1];
    p1=find_word_start(p); if(*p1!='{') return p;
    p2=find_matching(p1+1,'}'); if(p2==NULL) return p;
    p3=find_word_start(p2+1); if(*p3!='{') return p;
    p4=find_matching(p3+1,'}'); if(p4==NULL) return p;
    *p2=0; snprintf(buf,sizeof(buf),"%s",p1+1);
    for(pp=strchr(buf,'\\'); pp!=NULL; pp=strchr(pp+1,'\\')) {
	if(isalnum(*(pp+1))) string_modify(buf,pp,pp+1,"$m_");
    }
    fprintf(outf," \n!for m_%s \n$()",find_word_start(buf));
    *p4=nextchar;
    return p3+1;    
}

void process_formula(char *p)
{
    char *p3, bf[MAX_LINELEN+1];
    
    if(strlen(p)>=MAX_LINELEN) error("formula too long");
    while((p3=strstr(p,"&lt;"))!=NULL) memmove(p3," <  ",4);
    while((p3=strstr(p,"&gt;"))!=NULL) memmove(p3," >  ",4);
    for(p3=strchr(p,'\n'); p3!=NULL; p3=strchr(p3,'\n')) *p3=' ';
    snprintf(bf,sizeof(bf),"%s",p); 
    if(strchr(bf,'\\')==NULL && strchr(bf,'}')==NULL && strlen(bf)>2) {
	for(p3=strstr(bf,".."); p3!=NULL; p3=strstr(p3,"..")) {
	    if(*(p3+2)=='.' || *(p3+2)==',') {
		do p3++; while(*p3=='.'); continue;
	    }
	    *p3=','; *(p3+1)=' ';
	}
    }
    fprintf(outf,"\n!insmath %s\n$()",bf);
}

void out_exec(char *s1, char *s2)
{
    char *ps, *p, *pp, *pe, *pp2, *pe2, *pt, c;
    char *p2, *p3;
    if(s2) fprintf(outf,"\n!exit\n\n:%s\n$()",s2);
    ps=s1;
    for(p=ps;*p;p++) {
	if(*p==nextchar) {
	    *p=0;
	    fprintf(outf,"%s \n!next\n$()",ps); ps=p+1; continue;
	}
	if(*p==elsechar) {
	    *p=0;
	    fprintf(outf,"%s \n!else\n$()",ps); ps=p+1; continue;
	}
	if(*p==endifchar) {
	    *p=0;
	    fprintf(outf,"%s \n!endif\n$()",ps); ps=p+1; continue;
	}
	if(*p!='\\') continue;
	c=*(p+1);
	if(isalnum(c)) {
		/* exit */
	    if(strncmp(p+1,"exit",4)==0 && !isalnum(*(p+5))) {
		*p=0; fprintf(outf,"%s\n!exit\n",ps); p+=5; ps=p;
		continue;
	    }
		/* for */
	    if(strncmp(p+1,"for",3)==0 && *find_word_start(p+4)=='{') {
		char *pt;
		*p=0; fprintf(outf,"%s",ps); p++; ps=p;
		pt=exec_for(p+3); if(pt>p+3) {p=pt-1;ps=pt;}
		continue;
	    }
	    	/* if */
	    if(strncmp(p+1,"if",2)==0 && *find_word_start(p+3)=='{') {
		char *pt;
		*p=0; fprintf(outf,"%s",ps); p++; ps=p;
		pt=exec_if(p+2); if(pt>p+2) {p=pt-1;ps=pt;}
		continue;
	    }
	    	/* draw */
	    if(strncmp(p+1,"draw",4)==0 && *find_word_start(p+5)=='{') {
		pe=pp2=pe2="";
		pp=find_word_start(p+5);
		if(*pp) pe=find_matching(pp+1,'}');
		if(pe) pp2=find_word_start(pe+1); else continue;
		if(pp2) pe2=find_matching(pp2+1,'}'); else continue;
		if(pe2 && *pp2=='{' && *pe2=='}') {
		    pp++; pp2++; *p=*pe=*pe2=0;
		    while((pt=strstr(pp2,"$val1/"))!=NULL) 
		      ovlstrcpy(pt,pt+strlen("$val1/"));
		    fprintf(outf,"%s \n\
!read oef/draw.phtml %s \\\n%s \n$()", ps,pp,pp2);
		    ps=p=pe2; ps++; continue;
		}
	    }
	    	/* img */
	    if(strncmp(p+1,"img",3)==0 && *find_word_start(p+4)=='{') {
		pe=pp2=NULL;
		pp=find_word_start(p+4);
		if(*pp=='{') pe=find_matching(pp+1,'}');
		if(pe) pp2=find_word_start(pe+1); else continue;
		pe2=pe;
		if(*pp2=='{') {
		    pe2=find_matching(++pp2,'}');
		    if(pe2) *pe2=0;
		}
		else pp2="";
		if(*pp=='{' && *pe=='}') {
		    pp++; *p=*pe=0;
		    fprintf(outf,"%s \n\
!read oef/img.phtml %s %s \n$()", ps,pp,pp2);
		    ps=p=pe2; ps++; continue;
		}
	    }
	    if(strncmp(p+1,"embed",5)==0 && *find_word_start(p+6)=='{') {
		pe=pp2=pe2="";
		pp=find_word_start(p+6);
		if(*pp) pe=find_matching(pp+1,'}');
		if(pe && *pp=='{' && *pe=='}') {
		    pp++; *p=*pe=0;
		    fprintf(outf,"%s \n\
!read oef/embed.phtml %s \n$()", ps,pp);
		    ps=p=pe; ps++; embedcnt++; continue;
		}
	    }
	    if(strncmp(p+1,"special",7)==0 && *find_word_start(p+8)=='{') {
		pe=pp2=pe2="";
		pp=find_word_start(p+8);
		if(*pp) pe=find_matching(pp+1,'}');
		if(pe && *pp=='{' && *pe=='}') {
		    pp++; *p=*pe=0;
		    fprintf(outf,"%s \n\
!read oef/special.phtml %s \n$()", ps,pp);
		    ps=p=pe; ps++; embedcnt++; continue;
		}
	    }
	    *p++=0; fprintf(outf,"%s$m_",ps); ps=p; continue;
	}
	if(c=='\\') {
	    ovlstrcpy(p,p+1); continue;
	}
	if(c=='(') {
	    p2=find_matching(p+2,')'); p3=strstr(p,"\\)");
	    if((p2==NULL && p3!=NULL) ||
	       (p2!=NULL && p3!=NULL && p3<p2)) p2=p3+1;
	    if(p2==NULL) continue;
	    *p++=0; fprintf(outf,"%s",ps);
	    *p2=0; if(*(p2-1)=='\\') *(p2-1)=0;
	    process_formula(p+1); 
	    formulaend: p=p2; ps=p+1;
	    continue;
	}
	if(c=='{') {
	    p2=find_matching(p+2,'}'); p3=strstr(p,"\\}");
	    if((p2==NULL && p3!=NULL) ||
	       (p2!=NULL && p3!=NULL && p3<p2)) p2=p3+1;
	    if(p2==NULL) continue;
	    *p++=0; fprintf(outf,"%s",ps);
	    *p2=0; process_formula(p+1); 
	    goto formulaend;
	}
    }
    fprintf(outf,"%s\n$()",ps);
}

