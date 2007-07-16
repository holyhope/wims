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

/* internal variable */
int rawmath_easy=0;

#include "hmname.c"

enum {RM_UNKNOWN, RM_FN, RM_VAR, RM_PREFIX};

struct {
    char *name;
    int style;
    char *replace;
} mathname[]={
      {"Arc",	RM_PREFIX,	"arc"},
      {"Arg",	RM_PREFIX,	"arg"},
      {"Ci",	RM_FN,		""},
      {"E",	RM_VAR,		""},
      {"Euler", RM_VAR,		""},
      {"I",	RM_VAR,		""},
      {"Int",	RM_FN,		""},
      {"PI",	RM_VAR,		""},
      {"Pi",	RM_VAR,		""},
      {"Prod",	RM_FN,		""},
      {"Si",	RM_FN,		""},
      {"Sum",	RM_FN,		""},
      {"arc",	RM_PREFIX,	""},
      {"arg",	RM_PREFIX,	""},
      {"binomial",RM_FN,	""},
      {"diff",	RM_FN,		""},
      {"e",	RM_VAR,		""},
      {"erf",	RM_FN,		""},
      {"euler", RM_VAR,		""},
      {"i",	RM_VAR,		""},
      {"infinity",RM_VAR,	""},
      {"int",	RM_FN,		""},
      {"integrate",RM_FN,	""},
      {"neq",	RM_VAR,		""},
      {"pi",	RM_VAR,		""},
      {"prod",	RM_FN,		""},
      {"product",RM_FN,		""},
      {"psi",	RM_FN,		""},
      {"sum",	RM_FN,		""},
      {"theta", RM_FN,		""},
      {"x",	RM_VAR,		""},
      {"y",	RM_VAR,		""},
      {"z",	RM_VAR,		""},
      {"zeta",  RM_FN,		""},
};
#define mathname_no (sizeof(mathname)/sizeof(mathname[0]))
char rm_vbuf[MAX_LINELEN+1],rm_fbuf[MAX_LINELEN+1];
char *rm_uservar[MAX_LINELEN+1],*rm_userfn[MAX_LINELEN+1];
int  rm_uservars,rm_userfns;

	/* add user-defined variables and function names,
	 * internal, only called by rawmath(). */
void getuservar(void)
{
    char *p1, *p2, *p;
    rm_uservars=rm_userfns=0;
    p=getvar("wims_rawmath_variables");
    if(p!=NULL && *p!=0) {
	strcpy(rm_vbuf,p);
	for(p=rm_vbuf;*p;p++) if(*p==',') *p=' ';
	for(p1=find_word_start(rm_vbuf);*p1;p1=find_word_start(p2)) {
	    rm_uservar[rm_uservars++]=p1;
	    p2=find_word_end(p1);
	    if(*p2!=0) *(p2++)=0;
	}
    }
    p=getvar("wims_rawmath_functions");
    if(p!=NULL && *p!=0) {
	strcpy(rm_fbuf,p);
	for(p=rm_fbuf;*p;p++) if(*p==',') *p=' ';
	for(p1=find_word_start(rm_fbuf);*p1;p1=find_word_start(p2)) {
	    rm_userfn[rm_userfns++]=p1;
	    p2=find_word_end(p1);
	    if(*p2!=0) *(p2++)=0;
	}
    }
}

	/* Try to split a word into recognizable variables */
char *mathname_split(char *p)
{
    int c,i,j,type;

    c=0;
    beg: for(i=get_evalcnt()-1;
	i>=0 && strncmp(p,get_evalname(i),strlen(get_evalname(i)))!=0;
	i--);
    if(i>=0 && get_evaltype(i)>0) {
	type=RM_FN;
	j=strlen(get_evalname(i));
	gotit:
	if(!*(p+j)) return p;
	if(myisdigit(*(p+j)) && type!=RM_FN) return NULL;
	if(!c) {string_modify(p,p+j,p+j," "); p+=j+1;}
	else p+=j;
	c++; goto beg;
    }
    for(i=mathname_no-1;
	i>=0 && 
	(strncmp(p,mathname[i].name,strlen(mathname[i].name))!=0
	 || mathname[i].style==RM_PREFIX);
	i--);
    if(i>=0) {
	type=mathname[i].style;
	j=strlen(mathname[i].name);
	goto gotit;
    }
    for(i=0;i<rm_uservars && 
	strncmp(rm_uservar[i],p,strlen(rm_uservar[i]));i++);
    if(i<rm_uservars) {
	type=RM_VAR;
	j=strlen(rm_uservar[i]); goto gotit;
    }
    for(i=0;i<rm_userfns && 
	strncmp(p,rm_userfn[i],strlen(rm_userfn[i]));i++);
    if(i<rm_userfns) {
	type=RM_FN;
	j=strlen(rm_userfn[i]); goto gotit;
    }
    return NULL;    
}

	/* Error-tolerante raw math translation routine */
	/* Translate error-laden raw math into machine-understandable form. */
void rawmath(char *p)
{
    char *p1, *p2, *p3, *p4;
    char warnbuf[1024];
    int modified=0,user_prohibited=0;
    int ambiguous=0,unknown=0,flatpower=0,badprec=0,unmatch=0;

	/* looks like a TeX source */
    if(strchr(p,'\\')!=NULL || strchr(p,'{')!=NULL) return;
    if(strchr(p,'^')==NULL) flatpower=-1;
    if(strlen(p)>=MAX_LINELEN) {*p=0; return;}
    if(strncmp(p,"1-1+",strlen("1-1+"))==0) user_prohibited=1;
    p1=find_word_start(p);if(*p1==0) return;
    while(*p1=='+') p1++;
    if(p1>p) strcpy(p,p1);
    	/* translate ** into ^ */
    while((p1=strstr(p,"**"))!=NULL) {
	string_modify(p,p1,p1+strlen("**"),"^");
	modified++;
    }
    while((p1=strchr(p,'²'))!=NULL) {
	string_modify(p,p1,p1+1,"^2 ");
	flatpower=1;
	modified++;
    }
    while((p1=strchr(p,'³'))!=NULL) {
	string_modify(p,p1,p1+1,"^3 ");
	flatpower=1;
	modified++;
    }
    while((p1=strchr(p,'¨'))!=NULL) {
	*p1='^'; modified++;
    }
	/* translate |x| into abs(x) */
    while((p1=strchr(p,'|'))!=NULL) {
	p2=find_matching(p1+1,'|');
	if(p2==NULL) {unmatch=1; break;} 	/* error; drop it. */
	*p2=')'; string_modify(p,p1,p1+1,"abs(");
    }
        /* signs: translate ++, +-, -+, ... into one sign. */
    for(p1=p;*p1!=0;p1++) {
	int sign, redundant;
	if(*p1!='+' && *p1!='-') continue;
	if(*p1=='+') sign=1; else sign=-1;
	redundant=0;
	for(p2=find_word_start(p1+1);*p2=='+' || *p2=='-';
	    p2=find_word_start(p2+1)) {
	     if(*p2=='-') sign*=-1;
	     redundant=1;
	}
	if(redundant && *p2!='>' && strncmp(p2,"&gt;",4)!=0) {
	    if(sign==1) *p1='+'; else *p1='-';
	    strcpy(p1+1,p2);
	    modified++;
	}
    }
    	/* First translation: lower cases, parentheses, new-lines, tabs. */
    for(p1=p;*p1!=0; p1++) {
	/* *p1=tolower(*p1); */
/*	if(*p1=='[' || *p1=='{') *p1='(';
	if(*p1==']' || *p1=='}') *p1=')';
*/	if(*p1=='\\' || isspace(*p1)) *p1=' ';
	if(*p1=='\"') {
	    string_modify(p,p1,p1+1,"''"); p1++;
	}
    }
    	/* dangling decimal points */
    for(p1=strchr(p,'.'); p1!=NULL; p1=strchr(p1+1,'.')) {
		/* multiple .. is conserved */
	if(*(p1+1)=='.') {
	    do p1++; while(*p1=='.'); continue;
	}
	if(p1>p && myisdigit(*(p1-1)) && myisdigit(*(p1+1))) continue;
		/* Non-digit dangling '.' is removed */
	if((p1<=p || !myisdigit(*(p1-1))) && !myisdigit(*(p1+1))) {
	    strcpy(p1,p1+1); p1--; continue;
	}
	if(p1==p || !myisdigit(*(p1-1))) {
	    string_modify(p,p1,p1,"0"); p1++;
	}
	if(!myisdigit(*(p1+1))) string_modify(p,p1+1,p1+1,"0");
    }
    if(rawmath_easy || user_prohibited) return;
    	/* Principal translation: justapositions to multiplications */
    if(strstr(p,"^1/")!=NULL) badprec=1;
    getuservar();
    for(p1=p;*p1;p1++) {
	if(!isalnum(*p1) && *p1!=')' && *p1!=']') continue;
	if(*p1==')' || *p1==']') {
	    p2=find_word_start(++p1);
	    add_star:
	    if(isalnum(*p2) || *p2=='(' || *p2=='[') {
		if(*p2=='(' && *p1==')') ambiguous=1;
		if(p2>p1) *p1='*';
		else string_modify(p,p1,p1,"*");
		modified++;
	    }
	    p1--;continue;
	}
	p2=find_mathvar_end(p1); p3=find_word_start(p2);
	if(myisdigit(*p1)) {
	    p1=p2; p2=p3; goto add_star;
	}
	else {
	    char buf[MAX_LINELEN+1];
	    int i;
	    if(p2-p2>30) goto ambig;
	    memcpy(buf,p1,p2-p1);buf[p2-p1]=0;
	    i=search_evaltab(buf);
	    if(i>=0 && get_evaltype(i)>0) {
		fnname1:
		p1=p2;p2=p3;
		/*fnname:*/
		if(*p2 && *p2!='(' && *p2!='*' && *p2!='/') {
		    char hatbuf[MAX_LINELEN+1];
		    hatbuf[0]=')'; hatbuf[1]=0;
		    if(*p2=='^') {
			p3=p2+1;while(*p3==' ' || *p3=='+' || *p3=='-') p3++;
		        if(*p3=='(') {
			    p3=find_matching(p3+1,')');
			    if(p3==NULL) {unmatch=1; p3=p+strlen(p);}
			    else p3++;
			}
			else p3=find_mathvar_end(p3);
			memmove(hatbuf+1,p2,p3-p2);hatbuf[p3-p2+1]=0;
			strcpy(p2,p3);
			while(*p2==' ') p2++;
			if(*p2=='*' || *p2=='/') {
			    p1--;continue;
			}
			if(*p2=='(') {
			    p3=find_matching(p2+1,')');
			    if(p3==NULL) {unmatch=1; p3=p+strlen(p);}
			    else p3++;
			    string_modify(p,p3,p3,"%s",hatbuf+1);
			    goto dd2;
			}
		    }
		    p3=p2;if(*p3=='+' || *p3=='-') p3++;
		    while(isalnum(*p3) || *p3=='*' || *p3=='/' || *p3=='.')
		      p3++;
		    for(p4=p2; p4<p3 && !isalnum(*p4); p4++);
		    if(p4>=p3) {
			if(hatbuf[1]) string_modify(p,p2,p2,"%s",hatbuf+1);
		    }
		    else {
			string_modify(p,p3,p3,"%s",hatbuf);
			if(p1==p2) string_modify(p,p2,p2,"(");
			else *p1='(';
		    }
		    dd2:
		    modified++;ambiguous=1;
		}
		p1--;continue;
	    }
	    i=search_list(mathname,mathname_no,sizeof(mathname[0]),buf);
	    if(i>=0) {
		if(mathname[i].replace[0]!=0) {
		    string_modify(p,p1,p2,mathname[i].replace);
		    p2=p1+strlen(mathname[i].replace);
		    p3=find_word_start(p2);
		}
		switch(mathname[i].style) {
		    case RM_FN:
		      goto fnname1;
		    
		    case RM_VAR:
		      p1=p2;p2=p3; goto add_star;
		    
		    case RM_PREFIX:
		      if(*p3!='c' && *p3!='s' && *p3!='t' && 
			 *p3!='C' && *p3!='S' && *p3!='T') break;
		      ambiguous=1;
		      strcpy(p2,p3); p1--; continue;
		}
	    }
	    i=search_list(hmname,hmname_no,sizeof(hmname[0]),buf);
	    if(i>=0) {
		p1=p2; p2=p3; goto add_star;
	    }
	    for(i=0;i<rm_uservars && strcmp(buf,rm_uservar[i]);i++);
	    if(i<rm_uservars) {
		p1=p2;p2=p3;goto add_star;
	    }
	    for(i=0;i<rm_userfns && strcmp(buf,rm_userfn[i]);i++);
	    if(i<rm_userfns) goto fnname1;
	    if(p2-p1>8) goto ambig;
	    if(mathname_split(buf)!=NULL) {
		ambiguous=1;
		string_modify(p,p1,p2,"%s",buf);
		p1--; continue;
	    }
	     /* unknown name */
	    ambig: p1=p2;p2=p3;
	    if(strlen(buf)>1) {
		for(p3=buf;*p3!=0 && !myisdigit(*p3);p3++);
		if(*p3!=0 && flatpower!=0) flatpower=1; 
		else {
		    unknown=1;
		    force_setvar("wims_warn_rawmath_parm",buf);
		}
	    }
	    else {
		if(*p2=='(') ambiguous=1;
	    }
	    if(isalnum(*p2)) {
		if(p2>p1) *p1='*';
		else string_modify(p,p1,p1,"*");
		modified++;
	    }
	    p1--;continue;
	}
    }
    warnbuf[0]=0;
    if(ambiguous) strcat(warnbuf," ambiguous");
    if(unknown) strcat(warnbuf," unknown");
    if(flatpower>0) strcat(warnbuf," flatpower");
    if(badprec>0) strcat(warnbuf," badprec");
    if(unmatch>0) strcat(warnbuf," unmatched_parentheses");
    if(warnbuf[0]) {
	char buf[MAX_LINELEN+1],*p;
	p=getvar("wims_warn_rawmath");
	if(p!=NULL && *p!=0) {
	    snprintf(buf,sizeof(buf),"%s %s",p,warnbuf);
	    force_setvar("wims_warn_rawmath",buf);
	}
	else force_setvar("wims_warn_rawmath",warnbuf);
    }
}

	/* translate raw math expression into best html way */
void htmlmath(char *p)
{
    char *p1,*p2,*p3,*pp,pbuf[16];
    char c;

    if(!rawmath_easy) {
	rawmath_easy=1; rawmath(p); rawmath_easy=0;
    }
    p1=getvar("htmlmath_gtlt"); if(p1!=NULL && strcmp(p1,"yes")==0) {
	for(pp=strchr(p,'<'); pp!=NULL; pp=strchr(pp+1,'<'))
	  string_modify(p,pp,pp+1,"&lt;");
	for(pp=strchr(p,'>'); pp!=NULL; pp=strchr(pp+1,'>'))
	  string_modify(p,pp,pp+1,"&gt;");
    }
      /* exponents */
    for(p1=strchr(p,'^');p1!=NULL;p1=strchr(p1+1,'^')) {
	p3=p2=find_word_start(p1+1);
	if(*p2=='+' || *p2=='-') p2++;
	p2=find_word_start(p2);
	if(*p2=='(') {
	    p2=find_matching(p2+1,')');
	    if(p2==NULL) p2=p+strlen(p); else p2++;
	    if(*p3=='(') for(pp=p3+1;pp<p2-1;pp++) {
		if(!isalnum(*pp)) {
		    p3++;*(p2-1)=0;break;
		}
	    }
	}
	else {
	    char *ptt=p2;
	    p2=find_word_start(find_mathvar_end(p2));
	    if(*p2=='(' && isalpha(*ptt)) {
		char *p2t;
		p2t=find_matching(p2+1,')'); if(p2t!=NULL) p2=p2t+1;
	    }
	}
	c=*p2;if(c!=0) *p2++=0;
	string_modify(p,p1,p2,"<sup>%s</sup>%c",p3,c);
    }
	/* explicit subscription */
    for(p1=strchr(p,'_');p1!=NULL;p1=strchr(p1+1,'_')) {
	char buff[256];
	p2=p1+1;
	if(*p2=='(') p2=find_matching(p2+1,')');
	else p2=find_mathvar_end(p2);
	if(p2==NULL || p2>p1+64) continue;
	if(*(p1+1)=='(') p2++;
	memmove(buff,p1+1,p2-p1-1); buff[p2-p1-1]=0;
	strip_enclosing_par(buff);
	string_modify(p,p1,p2,"<sub>%s</sub>",buff);
    }
      /* get rid of 1*.. ..*1 */
    for(p1=p;*p1;p1++) {
	if(*p1!='1') continue;
	if(myisdigit(*(p1+1)) || *(p1+1)=='.' ||
	   (p1>p && (isalnum(*(p1-1)) || *(p1-1)=='.')) ) continue;
	p2=find_word_start(p1+1);
	if(p1>p+2 && (*(p1-1)=='-' || *(p1-1)=='+')) {
	    for(p3=p1-2; p3>p && isspace(*p3); p3--);
	    if(p3>p+1 && (*p3=='E' || *p3=='e')) {
		p3--; while(p3>p && isspace(*p3)) p3--;
		if(myisdigit(*p3) || *p3=='.') continue;
	    }
	}
	if(p1==p) p3="+"; 
	else for(p3=p1-1;p3>p && isspace(*p3);p3--);
	if(*p2=='*' && *p3!='/') {
	    strcpy(p1,p2+1);continue;
	}
	if(isalpha(*p2) && *p3!='/') {
	    strcpy(p1,p2);continue;
	}
	if(*p3=='/' && *p2!='<') strcpy(p3,p2);

    }
	/* exponents of 10, or greek letters */
    for(p1=find_mathvar_start(p);*p1!=0;p1=find_mathvar_start(p2)) {
	char buf[MAX_LINELEN+1];
	char expstr[]=" &times; 10<sup>";
	p2=find_mathvar_end(p1);
	memmove(buf,p1,p2-p1);buf[p2-p1]=0;
	if(myisdigit(buf[0])) { /* number */
	    int k;
	    if((p3=strchr(buf,'e'))==NULL && (p3=strchr(buf,'E'))==NULL)
	      continue;
	    p1+=p3-buf;
	    for(k=1;*(p1+k)=='0' || *(p1+k)=='+';k++);
	    string_modify(p,p1,p1+k,expstr);
	    p2+=strlen(expstr)-1;
	    string_modify(p,p2,p2,"</sup>");
	    p2+=strlen("</sup>");
	}
	else {	/* alphabetic name */
	    int i;
	    i=search_list(hmname,hmname_no,sizeof(hmname[0]),buf);
	    if(i<0) {
		if(myisdigit(buf[strlen(buf)-1])) {
		    int k;
		    for(k=strlen(buf);k>0 && myisdigit(buf[k-1]); k--);
		    string_modify(buf,buf+k,buf+k,"<sub>");
		    string_modify(p,p1,p2,"%s</sub>",buf);
		    p2+=strlen("<sub>")+strlen("</sub>");
		}
		continue;
	    }
	    if(hmname[i].replace[0]==0) {
		string_modify(p,p1,p2,"$(m_%s)",hmname[i].name);
		p2=p1+strlen(hmname[i].name)+5;
	    }
	    else {
		string_modify(p,p1,p2,"%s",hmname[i].replace);
		p2=p1+strlen(hmname[i].replace);
	    }
	}
    }
      /* get rid of '*' */
    for(p1=strchr(p,'*');p1!=NULL;p1=strchr(p1+1,'*')) {
	char *pq;
	pq=find_word_start(p1+1);
	if(myisdigit(*pq)) {
	    string_modify(p,p1,pq,"&times;");
	    continue;
	}
	if(p1>p && (isalpha(*(p1-1)) || *(p1-1)==')' || *(p1-1)=='>')
	   && (isalnum(*pq) || *pq=='$')) *p1=' ';
	else {
	    strcpy(p1,p1+1);p1--;
	}
    }
	/* <=, >=, ->, =>, <=> */
    for(p1=strstr(p,"&lt;="); p1!=NULL; p1=strstr(p1+1,"&lt;=")) {
	if(*(p1+5)!='&' && *(p1+5)!='=') 
	  string_modify(p,p1,p1+5,"$(m_le)");
	else {
	    for(p2=p1+5; *p2=='='; p2++);
	    if(strncmp(p2,"&gt;",4)==0) {
		if(p2>p1+5) string_modify(p,p1,p2+4,"$(m_Longleftrightarrow)");
		else string_modify(p,p1,p2+4,"$(m_Leftrightarrow)");
	    }
	    else string_modify(p,p1,p2,"$(m_Longleftarrow)");
	}
    }
    for(p1=strstr(p,"&gt;="); p1!=NULL; p1=strstr(p1+1,"&gt;=")) {
	if(*(p1+5)!='=') string_modify(p,p1,p1+5,"$(m_ge)");
    }
    for(p1=strstr(p,"-&gt;"); p1; p1=strstr(p1+1,"-&gt;")) {
	for(p2=p1; p2>p && *(p2-1)=='-'; p2--);
	if(p2>p && *(p2-1)==';') continue;
	if(p2<p1) string_modify(p,p2,p1+5,"$(m_longrightarrow)");
	else string_modify(p,p1,p1+5,"$(m_rightarrow)");
    }
    for(p1=strstr(p,"=&gt;"); p1; p1=strstr(p1+1,"=&gt;")) {
	for(p2=p1; p2>p && *(p2-1)=='='; p2--);
	if(p2>p && *(p2-1)==';') continue;
	if(p2<p1) string_modify(p,p2,p1+5,"$(m_Longrightarrow)");
	else string_modify(p,p1,p1+5,"$(m_Rightarrow)");
    }
	/* Not equal */
    for(p1=strstr(p,"!="); p1; p1=strstr(p1+1,"!=")) {
	if(p1>p && !isspace(*(p1-1))) continue;
	string_modify(p,p1,p1+2,"$(m_neq)");
    }
	/* Now make substitutions */
    substit(p);
	/* Make single names italic */
    for(p1=p;*p1;p1++) {
	if(*p1=='<') {
	    p1=strchr(p1,'>'); if(p1==NULL) break;
	    else continue;
	}
	if(*p1=='=' && *(p1+1)=='-') {
	    string_modify(p,p1+1,p1+1," "); p1+=2; continue;
	}
	if(*p1=='\'') {
	    for(p2=p1+1;*p2=='\'';p2++);
	    memmove(pbuf,p1,p2-p1); pbuf[p2-p1]=0;
	    string_modify(p,p1,p2,"<i><tt>%s</tt></i>",pbuf);
	    p1=p2+strlen("<i><tt></i></tt>")-1;
	    continue;
	}
	if(!isalpha(*p1)) continue;
	for(p2=p1+1;isalpha(*p2);p2++);
	p3=find_word_start(p2);
	if(p2>p1+5 ||
	   (p2>p1+1 && (*p3==';' || *p3=='(' || myisdigit(*p2))))
	    {p1=p2-1; continue;}
	if(strncasecmp(p3,"</i>",strlen("</i>"))==0) continue;
	memmove(pbuf,p1,p2-p1); pbuf[p2-p1]=0;
	string_modify(p,p1,p2,"<i>%s</i>",pbuf);
	p1=p2+strlen("<i></i>")-1;
    }
    strip_trailing_spaces(p);
}

