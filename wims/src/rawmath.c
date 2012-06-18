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
	ovlstrcpy(rm_vbuf,p);
	for(p=rm_vbuf;*p;p++) if(*p==',') *p=' ';
	for(p1=find_word_start(rm_vbuf);*p1;p1=find_word_start(p2)) {
	    rm_uservar[rm_uservars++]=p1;
	    p2=find_word_end(p1);
	    if(*p2!=0) *(p2++)=0;
	}
    }
    p=getvar("wims_rawmath_functions");
    if(p!=NULL && *p!=0) {
	ovlstrcpy(rm_fbuf,p);
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

int __replace_badchar (char *p, char *old, char *new)
{ int cnt = 0;
  char *p1 ;
  while((p1=strstr(p,old))!=NULL) {
	string_modify(p,p1,p1+strlen(old),"%s",new);
	cnt++; 
  }
  return cnt ;
}

/* translate |x| into abs(x) -- gives error in mathml ??*/
int __replace_abs ( char *p )
{  
    char *p1, *p2 ;
    while((p1=strchr(p,'|'))!=NULL) {
	p2=find_matching(p1+1,'|');
	if(p2==NULL) { return 1; break;} 	/* error; drop it. */
	*p2=')'; string_modify(p,p1,p1+1,"abs(");
    }
    return 0;
}

/* signs: translate ++, +-, -+, ... into one sign. */
int __replace_plusminus ( char *p )
{ 
   char *p1, *p2;
   int cnt=0 ;
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
	    ovlstrcpy(p1+1,p2);
	    cnt ++;
    }
   }
   return cnt ;
}

/* dangling decimal points
4. --> 4.0  4.x -> 4.0x
.5 -> 0.5
another treatment is done in insmath (will replace .. by , )
*/
void __treat_decimal(char *p)
{ char *p1 ;
  for(p1=strchr(p,'.'); p1!=NULL; p1=strchr(p1+1,'.')) {
		/* multiple .. is conserved */
	if(*(p1+1)=='.') {
	    do p1++; while(*p1=='.'); continue;
	}
	if(p1>p && myisdigit(*(p1-1)) && myisdigit(*(p1+1))) continue;
		/* Non-digit dangling '.' is removed */
	if((p1<=p || !myisdigit(*(p1-1))) && !myisdigit(*(p1+1))) {
	    ovlstrcpy(p1,p1+1); p1--; continue;
	}
	if(p1==p || !myisdigit(*(p1-1))) { // nondigit.digit
	    string_modify(p,p1,p1,"0"); p1++; //add zero before point
	}
	if(!myisdigit(*(p1+1))) string_modify(p,p1+1,p1+1,"0"); //add zero after point
    }
}

/* replace new-lines, tabs. */
void __replace_space(char *p)
{ 
 char *p1 ;
 for(p1=p;*p1!=0; p1++) {	
    if(*p1=='\\' || isspace(*p1)) *p1=' ';// replace \ and all spaces by a simple space - should be
	if(*p1=='\"') string_modify(p,p1,p1+1,"''"); p1++; // replace " by '' (this is needed in mathml)
  }
}

	/* Error-tolerante raw math translation routine */
	/* Translate error-laden raw math into machine-understandable form. */
/* where is "modified" used? */

void rawmath(char *p)
{
    char *p1, *p2, *p3, *p4;
    char warnbuf[1024];
    int modified=0,user_prohibited=0;
    int ambiguous=0,unknown=0,flatpower=0,badprec=0,unmatch=0;// for warning

	/* looks like a TeX source : do nothing - should continue if mathml ? */
	/* mathalign_base is always < 2 for the moment, prevision for mathml */
    if(mathalign_base < 2 && (strchr(p,'\\')!=NULL || strchr(p,'{')!=NULL)) return;
    if(strchr(p,'^')==NULL) flatpower=-1;
    if(strlen(p)>=MAX_LINELEN) {*p=0; return;}
    if(strncmp(p,"1-1+",strlen("1-1+"))==0) user_prohibited=1;
    p1=find_word_start(p);if(*p1==0) return;
    while(*p1=='+') p1++;
    if(p1>p) ovlstrcpy(p,p1);
    	/* translate ** into ^ */
    modified += __replace_badchar(p,"**", "^");
      /* translate '²' into ^ */
    int f= __replace_badchar(p,"²", "^2 ");
    modified += f ; if (f>0) flatpower=1;
    /* translate '³' into ^ */
    f= __replace_badchar(p,"³", "^3 ");
    modified += f ; if (f>0) flatpower=1;
/* why is it different
    while((p1=strchr(p,'¨'))!=NULL) {
	*p1='^'; modified++;
    }
*/
   modified += __replace_badchar(p,"¨", "^") ;
   if (mathalign_base < 2) unmatch=__replace_abs(p); 
   modified += __replace_plusminus(p) ; 
    __replace_space(p);
    __treat_decimal(p);
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
			ovlstrcpy(p2,p3);
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
		      ovlstrcpy(p2,p3); p1--; continue;
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

 /*  replace < and > by htmlcode - htmlmath_gtlt is only used in deduc - not documented*/
void __replace_htmlmath_gtlt (char *p) 
{   char *pp;
    char *p1=getvar("htmlmath_gtlt"); if(p1!=NULL && strcmp(p1,"yes")==0) {
	for(pp=strchr(p,'<'); pp!=NULL; pp=strchr(pp+1,'<'))
	  string_modify(p,pp,pp+1,"&lt;");
	for(pp=strchr(p,'>'); pp!=NULL; pp=strchr(pp+1,'>'))
	  string_modify(p,pp,pp+1,"&gt;");
   }
}

/* exponents : replace x^(zz) by html / mathml code.
 * Input p is destroyed. */
void __replace_exponent(char *p)
{
    char *p1;

    for(p1=strchr(p,'^');p1!=NULL;p1=strchr(p1+1,'^')) {
        char *p2, *p3, *pp;
        char c;
        p3 = p2 = find_word_start(p1+1);
        if(*p2=='+' || *p2=='-') p2++;
        p2 = find_word_start(p2);
        if(*p2=='(') { /* ^[+-]( */
            p2 = find_matching(p2+1,')');
            /* no matching ')' : p2 = end of line; otherwise just after ')' */
            if (p2==NULL) p2=p+strlen(p); else p2++;
            /* ^( followed by any number of digits/letters, up to p2
             * [FIXME: no sign?] */
            /* do we remove parentheses containing exponent group ? */
            if (*p3=='(') for(pp=p3+1;pp<p2-1;pp++) {
                if(!isalnum(*pp)) {
                    /* not a digit/letter. Remove (). */ 
                    p3++;*(p2-1)=0;break;
                }
                /* FIXME: x^(2), parentheses not removed */
            }
            /* p3: start of word after ^ */
            /* FIXME: I don't understand why we don't ALWAYS remove
             * matching parentheses from exponent group. : f^(4) 4-derivative */
            /* FIXME: I don't understand why we don't always ignore / remove
             * a leading + sign in exponent group : Cu^+ */
        } else { /* ^[+-] */
            char *ptt=p2;
            p2=find_word_start(find_mathvar_end(p2));
            if(*p2=='(' && isalpha(*ptt)) {
                /* ^[+-]var( */
                char *p2t;
                p2t=find_matching(p2+1,')'); if(p2t!=NULL) p2=p2t+1;
                /* FIXME: what if no matching ) ? */
            }
            /* ^[+-]var(...): p2 points after closing ')' */
            /* FIXME: I don't think this 'else' branch is sensible. One
             * should NOT accept x^b(c+1) as meaning x^[b(c+1)]. I would
             * remove it altogether */
        }
        /* p1 points at ^ before exponent group */
        /* p2 points at end of exponent group */
        /* p3 = exponent group (sometimes stripped, without parentheses) */

        /* truncate string p at p2 [ c = char deleted by truncation ] */
        c = *p2;if(c!=0) *p2++=0;
        /* replace ^<exponent group>. Add back missing character 'c' */
        string_modify(p,p1,p2, mathalign_base < 2? "<sup>%s</sup>%c"
                                                 : "^{%s}%c"
                             ,p3,c);
    }
}

/* explicit subscript why does not it the same as for the ^ */
	/* \( b_+(4+6)\) \( b^+(4-5)) has not the same behaviour*/
void __replace_subscript(char *p)
{
   char *p1, *p2;
   for(p1=strchr(p,'_');p1!=NULL;p1=strchr(p1+1,'_')) {
	char buff[256];
	p2=p1+1;
	if(*p2=='(') p2=find_matching(p2+1,')');
	else p2=find_mathvar_end(p2);
	if(p2==NULL || p2>p1+64) continue;
	if(*(p1+1)=='(') p2++;
	memmove(buff,p1+1,p2-p1-1); buff[p2-p1-1]=0;
	strip_enclosing_par(buff);
	string_modify(p,p1,p2,mathalign_base < 2? "<sub>%s</sub>":"_{%s}",buff);}
}

/* get rid of 1*.. ..*1  exemple : \(1f), \(1x\),  \(1 x\) , \( 1 + x) , \(1 * x), \( x/1 \)*/
void __replace_getrid1 (char *p)
{   char *p1, *p2, *p3 ; 
    for(p1=p;*p1;p1++) {
	if(*p1!='1') continue;
	if(myisdigit(*(p1+1)) || *(p1+1)=='.' ||
	   (p1>p && (isalnum(*(p1-1)) || *(p1-1)=='.')) ) continue;
	p2=find_word_start(p1+1);
	if(p1>p+2 && (*(p1-1)=='-' || *(p1-1)=='+')) {
	    for(p3=p1-2; p3>p && isspace(*p3); p3--);
	    if(p3>p+1 && (*p3=='E' || *p3=='e')) { /* ??? */ 
		p3--; while(p3>p && isspace(*p3)) p3--;
		if(myisdigit(*p3) || *p3=='.') continue;
	    }
	}
	if(p1==p) p3="+"; 
	else for(p3=p1-1;p3>p && isspace(*p3);p3--);
	if(*p2=='*' && *p3!='/') {/* delete 1 if 1* or /1 */
	    ovlstrcpy(p1,p2+1);continue;
	}
	if(isalpha(*p2) && *p3!='/') {
	    ovlstrcpy(p1,p2);continue;
	}
	if(*p3=='/' && *p2!='<') ovlstrcpy(p3,p2);

    }
}

/* get rid of '*' */
void __replace_getridstar (char *p)
{ char *p1 ;
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
	    ovlstrcpy(p1,p1+1);p1--;
	}
    }
}

	/* <=, >=, ->, =>, <=> */
void __replace_arrow ( char *p) // to clean !
{ char *p1, *p2 ;

    for(p1=strstr(p,"&lt;="); p1!=NULL; p1=strstr(p1+1,"&lt;=")) {
	if(*(p1+5)!='&' && *(p1+5)!='=') 
	  string_modify(p,p1,p1+5,mathalign_base < 2 ? "$(%sle)" : "\\le",mathfont_prefix);
	else {
	    for(p2=p1+5; *p2=='='; p2++);
	    if(strncmp(p2,"&gt;",4)==0) {
	    // here m_ should be mathfont_prefix
		if(p2>p1+5) { string_modify(p,p1,p2+4,mathalign_base < 2 ? "$(%sLongleftrightarrow)":"\\Longleftrightarrow",mathfont_prefix);} 
		else { string_modify(p,p1,p2+4,mathalign_base < 2 ?"$(%sLeftrightarrow)": "\\Leftrightarrow",mathfont_prefix);} 
	    }
	    else { string_modify(p,p1,p2,mathalign_base < 2 ?"$(%sLongleftarrow)" : "\\Longleftarrow",mathfont_prefix);}
	}
    }
    for(p1=strstr(p,"&gt;="); p1!=NULL; p1=strstr(p1+1,"&gt;=")) {
	if(*(p1+5)!='=') { string_modify(p,p1,p1+5,mathalign_base < 2 ?"$(%sge)": "\\ge",mathfont_prefix);}
    }
    for(p1=strstr(p,"-&gt;"); p1; p1=strstr(p1+1,"-&gt;")) {
	for(p2=p1; p2>p && *(p2-1)=='-'; p2--);
	if(p2>p && *(p2-1)==';') continue;
	if(p2<p1) { string_modify(p,p2,p1+5,mathalign_base < 2 ?"$(%slongrightarrow)" : "\\longrightarrow",mathfont_prefix);}
	else {  string_modify(p,p1,p1+5,mathalign_base < 2 ?"$(%srightarrow)" : "\\rightarrow",mathfont_prefix);}
    }
    for(p1=strstr(p,"=&gt;"); p1; p1=strstr(p1+1,"=&gt;")) {
	for(p2=p1; p2>p && *(p2-1)=='='; p2--);
	if(p2>p && *(p2-1)==';') continue;
	if(p2<p1) { string_modify(p,p2,p1+5,mathalign_base < 2 ?"$(%sLongrightarrow)": "\\Longrightarrow",mathfont_prefix);}
	else { string_modify(p,p1,p1+5,mathalign_base < 2 ?"$(%sRightarrow)":"\\Rightarrow",mathfont_prefix) ;}
    }
	/* Not equal */
    for(p1=strstr(p,"!="); p1; p1=strstr(p1+1,"!=")) {
	if(p1>p && !isspace(*(p1-1))) continue;
	 string_modify(p,p1,p1+2,mathalign_base < 2 ?"$(%sneq)" : "\\neq",mathfont_prefix);
    }
}

/* not useful in mathml ? why <tt> is used sometimes ? */
void __replace_italics (char *p)
{ char *p1, *p2, *p3, pbuf[16];
 for(p1=p;*p1;p1++) {
	if(*p1=='<') {
	    p1=strchr(p1,'>'); if(p1==NULL) break; //recognize an html tag < >
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
}
/* exponents of 10, or greek letters - should be cut*/
/* exponents of 10 : 3E+021 -> 3 × 10^{21} - 3E-21 -> 3 × 10^{-21} ; should replace E-05 by 1O^{-5}*/
/* almost the same as putnumber in texmath.c*/

void __replace_expgrec(char *p)
{
   char *p1,*p2,*p3 ;

    for(p1=find_mathvar_start(p);*p1!=0;p1=find_mathvar_start(p2)) {
	char buf[MAX_LINELEN+1];
	p2=find_mathvar_end(p1);
	memmove(buf,p1,p2-p1);buf[p2-p1]=0;
	if(myisdigit(buf[0])) { /* number : 3E+021 -> 3 × 10^{21} - 3E-21 -> 3 × 10^{-21} ; should replace E-05 by 1O^{-5}*/
	    int k;
	    if((p3=strchr(buf,'e'))==NULL && (p3=strchr(buf,'E'))==NULL)
	      continue;
	    p1+=p3-buf;
	    for(k=1;*(p1+k)=='0' || *(p1+k)=='+';k++);//count the number of 0 or +
//FIXME  E-05 is not replaced by 10^-5
	    if( mathalign_base < 2 ) { char expstr[]=" &times; 10<sup>"; string_modify(p,p1,p1+k,expstr);
	       p2+=strlen(expstr)-k;
	      string_modify(p,p2,p2,"</sup>"); p2+=strlen("</sup>");}
	    else { char expstr[]= " \\times 10^{" ; string_modify(p,p1,p1+k,expstr);
	       p2+=strlen(expstr)-k; string_modify(p,p2,p2,"}"); p2+=strlen("}");}
	}
	else {	/* alphabetic name */
	    int i;
	    i=search_list(hmname,hmname_no,sizeof(hmname[0]),buf);
	    if(i<0) { //don't understand what is done
		if(myisdigit(buf[strlen(buf)-1])) {
		    int k;
		    for(k=strlen(buf);k>0 && myisdigit(buf[k-1]); k--);
		    if(mathalign_base<2) {
		    string_modify(buf,buf+k,buf+k,"<sub>");
		    string_modify(p,p1,p2,"%s</sub>",buf);
		    p2+=strlen("<sub>")+strlen("</sub>");
		    }
		    else
		    {
		    string_modify(buf,buf+k,buf+k,"_{");
		    string_modify(p,p1,p2,"%s}",buf);
		    p2+=strlen("_{")+strlen("}");
		    }
		}
		continue;
	    }
	    if(mathalign_base < 2) {
	     if(hmname[i].replace[0]==0) {// do not recognize any name from hmnames - insert math_prefix
		  string_modify(p,p1,p2,"$(%s%s)",mathfont_prefix,hmname[i].name);
		  p2=p1+strlen(hmname[i].name)+5;
	     }
	     else { // replace according to hmname (second column)
		  string_modify(p,p1,p2,"%s",hmname[i].replace);
		  p2=p1+strlen(hmname[i].replace);
	     }
	    }
	    else
	    {
	     if(hmname[i].replacem[0]==0) {// do not recognize any name from hmnames - insert math_prefix
		  string_modify(p,p1,p2,"$(%s%s)",mathfont_prefix,hmname[i].name);
		  p2=p1+strlen(hmname[i].name)+5;
	     }
	     else { // replace according to hmname (third column)
	      string_modify(p,p1,p2,"%s",hmname[i].replacem);
	      p2=p1+strlen(hmname[i].replacem); 
	     }
	    }
	 }
    }
}

/* translate raw math expression into best html way */
void __htmlmath(char *p)
{
    if(!rawmath_easy) {
	rawmath_easy=1; rawmath(p); rawmath_easy=0;
    }
    __replace_htmlmath_gtlt(p); //only used in deduc
    __replace_exponent(p) ;
	__replace_subscript(p) ;
    __replace_getrid1(p) ;
    __replace_expgrec(p);
    __replace_getridstar(p) ;
    __replace_arrow(p) ;
	/* Now make substitutions */
    substit(p);
	/* Make single names italic - done automatically by mathml */
   if (mathalign_base < 2) __replace_italics(p);
   strip_trailing_spaces(p);
}

void htmlmath(char *p) 
{
  __htmlmath(p) ;
}
