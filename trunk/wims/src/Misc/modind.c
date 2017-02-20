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

/*  This is an internal program,
 * used to index modules for search engine.
 */

#include "../Lib/libwims.h"
#include "translator_.h"
#include "suffix.h"

#define MAX_LANGS    MAX_LANGUAGES
#define MAX_MODULES    65536
char *moduledir=    "public_html/modules";
char *sheetdir=     "public_html/bases/sheet";
char *dicdir=       "public_html/bases";
char *outdir=       "public_html/bases/site2";
char *sheetoutdir=  "public_html/bases/sheet/index";
char *maindic=      "sys/words";
char *groupdic=     "sys/wgrp/wgrp";
char *suffixdic=    "sys/suffix";
char *domaindic=    "sys/domaindic";
char *ignoredic=    "sys/indignore";
char *conffile=     "log/wims.conf";
char *mlistbase=    "lists";

char lang[MAX_LANGS][4]={
    "en","fr","cn","es","it","nl","si","ca","pt"
};
#define DEFAULT_LANGCNT    6
char allang[MAX_LANGS][4]={
    "en","fr","cn","es","it","nl","de","si","ca","pt"
};
#define allangcnt 8
char ignore[MAX_LANGS][MAX_LINELEN+1];
char mlistfile[MAX_LANGS][256];
int langcnt;
FILE *langf, *titf, *descf, *weightf, *robotf, *indf, *listf, *addrf, *serialf, *authorf, *versionf, *remf, *titlef;

struct cat {
    char *name;
    char typ;
} cat[]={
    {"all_types", 'A'},
    {"exercise",  'X'},
    {"oef",       'O'},
    {"tool",      'T'},
    {"recreation",'R'},
    {"reference", 'Y'},
    {"document",  'D'},
    {"popup",     'P'},
    {"datamodule",'M'}
};
#define catno (sizeof(cat)/sizeof(cat[0]))

struct mod {
    char *name;
    unsigned char langs[MAX_LANGS];
    int counts[MAX_LANGS];
    int  langcnt;
} mod[MAX_MODULES];
int modcnt;

char *mlist;

/*  fold known accented letters to unaccented, other strange characters to space
 *  apostrophe is among the exceptions to be kept (important for multi-word expressions)
 */
void deaccent2(char *p)
{
    char *sp;
    char *v;
    for(sp=p;*sp;sp++) {
    if(*sp<0 && (v=strchr(acctab,*sp))!=NULL)
      *sp=*(deatab+(v-acctab));
    if(!isalnum(*sp) && strchr(",.&$+*",*sp)==0) *sp=' ';
    else *sp=tolower(*sp);
    }
}

/*  translate everything non-alphanumeric into space */
void towords(char *p)
{
    char *pp;
    for(pp=p;*pp;pp++) if(!isalnum(*pp) && strchr("&$+*",*pp)==0) *pp=' ';
}

/*  Find first occurrence of word */
char *wordchr2(char *p, char *w)
{
    char *r;

    for(r=strstr(p,w);r!=NULL &&
    ( (r>p && !isspace(*(r-1))) || (!isspace(*(r+strlen(w))) && *(r+strlen(w))!=0) );
    r=strstr(r+1,w));
    return r;
}

char *find_tag_end(char *p)
{
    char *pp;
    pp=p; if(*pp=='<') pp++;
    for(; *pp && *pp!='>'; pp++) {
    if(*pp=='<') {
        pp=find_tag_end(pp)-1; continue;
    }
    if(*pp=='"') {
        pp=strchr(pp+1,'"');
        if(pp==NULL) return p+strlen(p); else continue;
    }
    if(*pp=='\'') {
        pp=strchr(pp+1,'\'');
        if(pp==NULL) return p+strlen(p); else continue;
    }
    }
    if(*pp=='>') pp++;
    return pp;
}

char *find_tag(char *p, char *tag)
{
    char *pp;
    int len;
    len=strlen(tag);
    for(pp=strchr(p,'<'); pp!=NULL && *pp; pp=strchr(pp+1,'<')) {
    if(strncasecmp(pp+1,tag,len)==0 && !isalnum(*(pp+1+len))) return pp;
    }
    return p+strlen(p);
}

/*  remove all html tags */
void detag(char *p)
{
    char *pp, *p2;
    for(pp=strchr(p,'<'); pp!=NULL; pp=strchr(pp,'<')) {
    p2=find_tag_end(pp);
    if(*p2==0) {*pp=0; return; }
    ovlstrcpy(pp,p2);
    }
}

/* add a space after comma to see end of words */

void comma(char *p)
{
    char *pp;
    for(pp=strchr(p,','); pp; pp=strchr(pp+1,','))
      string_modify3(p,pp,pp+1,", ");
}

void _getdef(char buf[], char *name, char value[])
{
    char *p1, *p2, *p3;

    value[0]=0;
    for(p1=strstr(buf,name); p1!=NULL; p1=strstr(p1+1,name)) {
    p2=find_word_start(p1+strlen(name));
    if((p1>buf && !isspace(*(p1-1))) || *p2!='=') continue;
    p3=p1; while(p3>buf && isspace(*(p3-1)) && *(p3-1)!='\n') p3--;
    if(p3>buf && *(p3-1)!='\n') continue;
    p3=strchr(p2,'\n');
    p2=find_word_start(p2+1);
    if(p3 <= p2) continue;
    snprintf(value,MAX_LINELEN,"%s",p2);
    if(p3!=NULL && p3-p2<MAX_LINELEN) value[p3-p2]=0;
    strip_trailing_spaces2(value);
    break;
    }
}

/*  Get variable definition from a file.
 * Result stored in buffer value of length MAX_LINELEN.
 */
void getdef(char *fname, char *name, char value[])
{
    FILE *f;
    char *buf;
    int l;

    value[0]=0;
    f=fopen(fname,"r"); if(f==NULL) return;
    fseek(f,0,SEEK_END); l=ftell(f); fseek(f,0,SEEK_SET);
    buf=xmalloc(l+256); l=fread(buf,1,l,f);
    fclose(f);
    if(l<=0) return; else buf[l]=0;
    _getdef(buf,name,value);
    free(buf);
}

char *mdicbuf, *gdicbuf, *ddicbuf, *gentry, *mentry, *dentry;

int gentrycount, mentrycount, dentrycount;

/*  Preparation of data */
void prep(void)
{
    char buf[MAX_LINELEN+1];
    char *p1,*p2,*s,*old;
    int i,l,thislang,t;
    FILE *f;

    s=getenv("modind_outdir"); if(s!=NULL && *s!=0) outdir=s;
    s=getenv("modind_sheetdir"); if(s!=NULL && *s!=0) sheetdir=s;
    s=getenv("modind_sheetoutdir"); if(s!=NULL && *s!=0) sheetoutdir=s;
    snprintf(buf,sizeof(buf),"%s/addr",outdir);
    addrf=fopen(buf,"w");
    if(!addrf) { fprintf(stderr,"modind: error creating output files addr.\n"); exit(1);}
    snprintf(buf,sizeof(buf),"%s/serial",outdir);
    serialf=fopen(buf,"w");
    if(!serialf) { fprintf(stderr,"modind: error creating output files serial.\n"); exit(1);}
    modcnt=langcnt=0;
/* take the langs declared in conffile */
    getdef(conffile,"site_languages",buf);
    for(p1=buf;*p1;p1++) if(!isalnum(*p1)) *p1=' ';
    for(p1=find_word_start(buf); *p1 && langcnt<MAX_LANGS; p1=find_word_start(p2)) {
    p2=find_word_end(p1);
    if(p2!=p1+2 || !isalpha(*p1) || !isalpha(*(p1+1))) continue;
    memmove(lang[langcnt],p1,2); lang[langcnt++][2]=0;
    }
    if(langcnt==0) {/*  default languages */
    langcnt=DEFAULT_LANGCNT;
    }
    s=getenv("mlist"); if(s==NULL) exit(1);
    l=strlen(s); if(l<0 || l>100*MAX_LINELEN) exit(1);
    mlist=xmalloc(l+16); ovlstrcpy(mlist,s); old="";
    for(i=0;i<langcnt;i++) {
      snprintf(buf,sizeof(buf),"%s/%s.%s",dicdir,ignoredic,lang[i]);
      f=fopen(buf,"r"); if(f==NULL) continue;
      l=fread(ignore[i],1,MAX_LINELEN,f);fclose(f);
      if(l<0 || l>=MAX_LINELEN) l=0;
      ignore[i][l]=0;
    }
    for(t=0, p1=find_word_start(mlist); *p1 && modcnt<MAX_MODULES;
        p1=find_word_start(p2), t++) {
      p2=find_word_end(p1);
      l=p2-p1; if(*p2) *p2++=0;
      fprintf(addrf,"%d:%s\n",t,p1);
      fprintf(serialf,"%s:%d\n",p1,t);
      thislang=-1;
/* language is taken from the address */
      if(l>3 && p1[l-3]=='.') {
        for(i=0;i<langcnt;i++) if(strcasecmp(lang[i],p1+l-2)==0) break;
        if(i<langcnt) {p1[l-3]=0; thislang=i;}
        else {/*  unknown language, not referenced */
        continue;
        }
      }
      if(modcnt>0 && strcmp(old,p1)==0 && thislang>=0) {
        if(mod[modcnt-1].langcnt<langcnt) {
        mod[modcnt-1].langs[mod[modcnt-1].langcnt]=thislang;
        mod[modcnt-1].counts[mod[modcnt-1].langcnt]=t;
        (mod[modcnt-1].langcnt)++;
        }
     }
     else {
        mod[modcnt].name=old=p1;
        if(thislang>=0) {
          mod[modcnt].langs[0]=thislang;
          mod[modcnt].langcnt=1;
        }
        else mod[modcnt].langcnt=0;
        mod[modcnt].counts[0]=t;
        modcnt++;
    }
    }
    snprintf(buf,sizeof(buf),"%s/language",outdir);
    langf=fopen(buf,"w");
    snprintf(buf,sizeof(buf),"%s/title",outdir);
    titf=fopen(buf,"w");
    snprintf(buf,sizeof(buf),"%s/description",outdir);
    descf=fopen(buf,"w");
    snprintf(buf,sizeof(buf),"%s/author",outdir);
    authorf=fopen(buf,"w");
    snprintf(buf,sizeof(buf),"%s/version",outdir);
    versionf=fopen(buf,"w");
    snprintf(buf,sizeof(buf),"%s/%s/robot.phtml",outdir,mlistbase);
    robotf=fopen(buf,"w");
    fclose(addrf); fclose(serialf);
    if(!robotf || !versionf || !authorf || !descf || !titf || !langf) {
      fprintf(stderr,"modind: error creating output files.\n");
      exit(1);
    }
}

void sprep(void)
{
    char *p1,*p2,*s;
    int i,l,thislang;

    modcnt=0;
    s=getenv("slist"); if(s==NULL) return;
    l=strlen(s); if(l<0 || l>100*MAX_LINELEN) return;
    mlist=xmalloc(l+16); ovlstrcpy(mlist,s);
    for(p1=find_word_start(mlist); *p1 && modcnt<MAX_MODULES; p1=find_word_start(p2)) {
    p2=find_word_end(p1);
    l=p2-p1; if(*p2) *p2++=0;
    for(i=0;i<langcnt;i++) if(strncasecmp(lang[i],p1,2)==0) break;
    if(i<langcnt) thislang=i; else continue;
    mod[modcnt].name=p1;
    mod[modcnt].langs[0]=thislang;
    mod[modcnt].langcnt=1;
    modcnt++;
    }
}

void clean(void)
{
    fclose(langf); fclose(titf); fclose(descf); fclose(robotf);
    fclose(authorf); fclose(versionf);
}

char *sheetindex[]={
      "title", "description",
      "duration", "severity",
      "level", "domain",
      "keywords", "reserved1", "reserved2", "information"
};
#define SHEETINDEX_NO (sizeof(sheetindex)/sizeof(sheetindex[0]))
char sindbuf[SHEETINDEX_NO][MAX_LINELEN+1];
enum{s_title, s_description,
      s_duration, s_severity,
      s_level, s_domain,
      s_keywords, s_reserved1, s_reserved2,
      s_information
};

char *modindex[]={
      "title", "description",
      "author", "address", "copyright",
      "version", "wims_version", "language",
      "category", "level", "domain", "keywords",
      "keywords_ca", "keywords_en", "keywords_fr", "keywords_it", "keywords_nl",
      "title_ca", "title_en", "title_fr", "title_it", "title_nl",
      "require"
};
#define MODINDEX_NO (sizeof(modindex)/sizeof(modindex[0]))
char indbuf[MODINDEX_NO][MAX_LINELEN+1];
enum{i_title, i_description,
      i_author,i_address,i_copyright,
      i_version,i_wims_version,i_language,
      i_category,i_level,i_domain,i_keywords,
      i_keywords_ca,i_keywords_en,i_keywords_fr,i_keywords_it,i_keywords_nl,
      i_title_ca,i_title_en,i_title_fr,i_title_it,i_title_nl,
      i_require
};

char *module_special_file[]={
    "intro","help","about"
};
#define MODSPEC_NO (sizeof(module_special_file)/sizeof(module_special_file[0]))
char module_language[4];

/*  read and treat module's INDEX file */
int module_index(const char *name)
{
    char *p, fbuf[MAX_LINELEN+1], ibuf[MAX_LINELEN+1];
    FILE *indf;
    int i,l;

    snprintf(fbuf,sizeof(fbuf),"%s/%s/INDEX",moduledir,name);
    indf=fopen(fbuf,"r");
    if(indf==NULL) {
      fprintf(stderr,"modind: INDEX of %s not found\n",fbuf); return -1;
    }
    l=fread(ibuf,1,MAX_LINELEN,indf); fclose(indf);
    if(l>0 && l<MAX_LINELEN) ibuf[l]=0; else return -1;
/* treate all fields in *modindex */
    for(i=0;i<MODINDEX_NO;i++) {
      _getdef(ibuf,modindex[i],indbuf[i]);
/*  compatibility precaution */
      if(indbuf[i][0]==':') indbuf[i][0]='.';
    }
    p=find_word_start(indbuf[i_language]);
    if(isalpha(*p) && isalpha(*(p+1))) {
      memmove(module_language,p,2); module_language[2]=0;
    }
    else ovlstrcpy(module_language,"en");
    return 0;
}

int sheet_index(int serial)
{
    char *p1, *p2, fbuf[MAX_LINELEN+1], ibuf[MAX_LINELEN+1];
    FILE *indf;
    int i,l;

    snprintf(fbuf,sizeof(fbuf),"%s/%s.def",sheetdir,mod[serial].name);
    indf=fopen(fbuf,"r"); if(indf==NULL) return -1;
    l=fread(ibuf,1,MAX_LINELEN,indf); fclose(indf);
    if(l>0 && l<MAX_LINELEN) ibuf[l]=0; else return -1;
    for(i=0;i<SHEETINDEX_NO;i++) sindbuf[i][0]=0;
    for(i=0,p1=find_word_start(ibuf);
      i<SHEETINDEX_NO-1 && *p1!=':' && *p1!=0;
      i++,p1=p2) {
       p2=strchr(p1,'\n');
       if(p2!=NULL) *p2++=0; else p2=p1+strlen(p1);
       p1=find_word_start(p1); strip_trailing_spaces2(p1);
       snprintf(sindbuf[i],MAX_LINELEN,"%s",p1);
    }
    p2=strstr(p1,"\n:"); if(p2==NULL) p2=p1+strlen(p1);
    else *p2=0;
    p1=find_word_start(p1); strip_trailing_spaces2(p1);
    for(p2=p1;*p2;p2++) if(*p2=='\n') *p2=' ';
    ovlstrcpy(sindbuf[s_information],p1);
    return 0;
}

unsigned char categories[16];
char taken[MAX_LINELEN+1];
int catcnt, takenlen, tweight;

void appenditem(char *word, int lind, int serial, int weight, char *l)
{
    char nbuf[MAX_LINELEN+1], buf[MAX_LINELEN+1];
    int i, ll;
    char *p;
    FILE *f;

    if(!isalnum(*word) || (ll=strlen(word))<2 ||
       wordchr2(taken,word)!=NULL ||
       wordchr2(ignore[lind],word)!=NULL ||
       takenlen>=MAX_LINELEN-ll-16)
      return;
    if(ll==2 && (!isdigit(word[0]) || !isalpha(word[1]))) return;
    for(p=word;*p;p++) if(!isalnum(*p) && *p!=' ') return;
    taken[takenlen++]=' '; taken[takenlen++]=' ';
    ovlstrcpy(taken+takenlen,word);
    takenlen+=ll; tweight+=weight;
    snprintf(buf,sizeof(buf),"%s:%d?%d\n",word,serial,weight);
    for(i=0;i<catcnt;i++) {
    snprintf(nbuf,sizeof(nbuf),"%s/%c.%s",
         outdir,categories[i],lang[lind]);
    f=fopen(nbuf,"a");
    if(f!=NULL) {fputs(buf,f); fclose(f);}
    }
}

void appenditem1 (char *buf, int lind, int serial, int weight, char *l )
{
  char *p1, *p2 ;
  for(p1=find_word_start(buf); *p1;
    p1=find_word_start(p2)) {
    p2=strchr(p1,',');
    if(p2!=NULL) *p2++=0; else p2=p1+strlen(p1);
    if(strlen(p1)<=0) continue;
    appenditem(p1,lind,serial,weight,module_language);
  }
}
void appenditem2 (char *buf, int lind, int serial, int weight, char *l )
{
  char *p1, *p2 ;
  for(p1=find_word_start(buf);*p1;
    p1=find_word_start(p2)) {
    p2=find_word_end(p1); if(*p2) *p2++=0;
    appenditem(p1,lind,serial,weight,module_language);
  }
}
void onemodule(const char *name, int serial, int lind)
{
    int i;
    unsigned char trlist[]={
    i_title,i_description,i_category,i_domain,i_keywords,
      i_require,i_author,
      i_keywords_ca,i_keywords_en,i_keywords_fr,i_keywords_it,i_keywords_nl,
      i_title_ca,i_title_en,i_title_fr,i_title_it,i_title_nl
    };
    #define trcnt (sizeof(trlist)/sizeof(trlist[0]))
    char *p1, *p2, *pp, *q, buf[MAX_LINELEN+1], lbuf[16];
    FILE *f;

    if(module_index(name)) return;
    towords(indbuf[i_category]);
/*   list the categories (among A=all,X=eXercise,O,D,...) corresponding
 *   to this module
 */
    for(i=catcnt=0;i<catno && catcnt<16;i++) {
    if(wordchr2(indbuf[i_category],cat[i].name)!=NULL)
      categories[catcnt++]=cat[i].typ;
    }
    if(catcnt==0) return;
    if(categories[0]!=cat[0].typ)
      categories[catcnt++]=cat[0].typ;
/*  write module's name in the category.language files, for instance lists/X.fr
 * for french exercises
 */
    for(i=0;i<catcnt;i++) {
      snprintf(buf,sizeof(buf),"%s/%s/%c.%s",
         outdir,mlistbase,categories[i],lang[lind]);
      f=fopen(buf,"a");
      if(f!=NULL) {fprintf(f,"%s\n",name); fclose(f);}
    }
/*   add serial number and language (resp.title, ...) to corresponding file  */
    fprintf(langf,"%d:%s\n",serial,module_language);
    fprintf(titf,"%d:%s\n",serial,indbuf[i_title]);
    fprintf(descf,"%d:%s\n",serial,indbuf[i_description]);
    fprintf(authorf,"%d:%s\n",serial,indbuf[i_author]);
    fprintf(versionf,"%d:%s\n",serial,indbuf[i_version]);

/*   add module's information in html page for robots  */
    snprintf(buf,sizeof(buf),"%s",indbuf[i_description]);
    for(pp=strchr(buf,','); pp; pp=strchr(pp,','))
      string_modify3(buf,pp,pp+1,"&#44;");
    if(strcmp(module_language,lang[lind])==0)
      fprintf(robotf,"%s ,%s,%s,%s,%s\n",name,module_language,name,
          indbuf[i_title], buf);

/*   Normalize the information of trlist, using dictionary
 *  -- bases/sys/domain.xx without suffix translation (--> english version)
 */
    entrycount=dentrycount; dicbuf=ddicbuf;
    memmove(entry,dentry,dentrycount*sizeof(entry[0]));
    unknown_type=unk_leave;
    for(i=0;i<trcnt;i++) {
    detag(indbuf[trlist[i]]);
    deaccent2(indbuf[trlist[i]]);
    comma(indbuf[trlist[i]]);
    singlespace2(indbuf[trlist[i]]);
    translate(indbuf[trlist[i]]);
    }
/*   Normalize the information, using dictionary
 *   bases/sys/words.xx with suffix translation
 */
    entrycount=mentrycount; dicbuf=mdicbuf;
    memmove(entry,mentry,mentrycount*sizeof(entry[0]));
    unknown_type=unk_leave;/*  used in translator_.c */
    for(i=0;i<trcnt;i++) {
    suffix_translate(indbuf[trlist[i]]);
    translate(indbuf[trlist[i]]);
    }

/* taken contains all words already seen in the module index */
    taken[0]=0; takenlen=tweight=0;
/*  append words of title  */
    ovlstrcpy(buf,indbuf[i_title]); towords(buf);
    appenditem2(buf,lind,serial,4,module_language);

/*  extract words of every other information except level */
    snprintf(buf,sizeof(buf),"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
         indbuf[i_description],indbuf[i_keywords],
         indbuf[i_keywords_ca],indbuf[i_keywords_en],indbuf[i_keywords_fr],
         indbuf[i_keywords_it],indbuf[i_keywords_nl],
         indbuf[i_title_ca],indbuf[i_title_en],indbuf[i_title_fr],
         indbuf[i_title_it],indbuf[i_title_nl],
         indbuf[i_domain],indbuf[i_require],indbuf[i_author]);
    towords(buf);
    appenditem2(buf,lind,serial,2,module_language);

/*   this time the dictionary is the group dictionary  sys/wgrp/wgrp
 *   with a g (groupdic), not an m (maindic) . see below main, suffix, group.
 *   and delete unknown ?? and translate
 */
    entrycount=gentrycount; dicbuf=gdicbuf;
    memmove(entry,gentry,gentrycount*sizeof(entry[0]));

/*  append words of every title information  */
    ovlstrcpy(buf,indbuf[i_title]);
    unknown_type=unk_delete;
    translate(buf);
    appenditem1(buf,lind,serial,2,module_language);

/*  append words of information of description except level  */
    snprintf(buf,sizeof(buf),"%s", indbuf[i_description]);
    unknown_type=unk_delete;
    translate(buf);
    appenditem1(buf,lind,serial,4,module_language);

/*  append words (or group of words) of keywords and domain  */
    snprintf(buf,sizeof(buf),"%s, %s, %s, %s, %s, %s, %s",
         indbuf[i_domain],indbuf[i_keywords],
         indbuf[i_keywords_ca], indbuf[i_keywords_en],indbuf[i_keywords_fr],
         indbuf[i_keywords_it], indbuf[i_keywords_nl]);
    unknown_type=unk_leave;
    translate(buf);
    appenditem1(buf,lind,serial,2,module_language);

/*   append level information, with weight 2 */
    snprintf(buf,sizeof(buf),"%s",indbuf[i_level]);
    ovlstrcpy(lbuf,"level");
    for(p1=buf; *p1; p1++) if(!isalnum(*p1)) *p1=' ';
    q=buf+strlen(buf);
    for(p1=find_word_start(buf); (*p1) && (p1 < q) ;
    p1=find_word_start(p2)) {
      p2=find_word_end(p1);
      if(p2!=NULL) *p2++=0; else p2=p1+strlen(p1);
      if(!isalpha(*p1) ||
       (!isdigit(*(p1+1)) && *(p1+1)!=0) ||
       (*(p1+1)!=0 && *(p1+2)!=0))
      continue;
      *p1=tolower(*p1);
      ovlstrcpy(lbuf+strlen("level"),p1);
      appenditem(lbuf,lind,serial,2,module_language);
    }
/*   append total weight of module to weight file site2/weight.xx  */
    fprintf(weightf,"%d:%d\n",serial,tweight);
}

void modules(void)
{
    int i,j,k,d;
    char namebuf[MAX_LINELEN+1];
    char mdic[MAX_LINELEN+1], sdic[MAX_LINELEN+1], gdic[MAX_LINELEN+1], ddic[MAX_LINELEN+1];

    for(j=0;j<langcnt;j++) {
    snprintf(namebuf,sizeof(namebuf),"%s/weight.%s",outdir,lang[j]);
    weightf=fopen(namebuf,"w");
    snprintf(mdic,sizeof(mdic),"%s/%s.%s",dicdir,maindic,lang[j]);
    snprintf(sdic,sizeof(sdic),"%s/%s.%s",dicdir,suffixdic,lang[j]);
    snprintf(gdic,sizeof(gdic),"%s/%s.%s",dicdir,groupdic,lang[j]);
    snprintf(ddic,sizeof(ddic),"%s/%s.%s",dicdir,domaindic,lang[j]);
    suffix_dic(sdic); prepare_dic(gdic);
    gdicbuf=dicbuf; gentrycount=entrycount;
    memmove(gentry,entry,gentrycount*sizeof(entry[0]));
    prepare_dic(mdic);
    mdicbuf=dicbuf; mentrycount=entrycount;
    memmove(mentry,entry,mentrycount*sizeof(entry[0]));
    prepare_dic(ddic);
    ddicbuf=dicbuf; dentrycount=entrycount;
    memmove(dentry,entry,dentrycount*sizeof(entry[0]));
    unknown_type=unk_leave; translate(ignore[j]);
    for(i=0;i<modcnt;i++) {
        if(mod[i].langcnt>0) {
        for(d=k=0;k<mod[i].langcnt;k++)
          if(mod[i].langs[k]<mod[i].langs[d]) d=k;
        for(k=0;k<mod[i].langcnt && mod[i].langs[k]!=j;k++);
        if(k>=mod[i].langcnt) k=d;
        snprintf(namebuf,MAX_LINELEN,"%s.%s",mod[i].name,
             lang[mod[i].langs[k]]);
        onemodule(namebuf,mod[i].counts[k],j);
        }
        else {
        onemodule(mod[i].name,mod[i].counts[0],j);
        }
    }
    if(mentrycount>0) free(mdicbuf);
    if(gentrycount>0) free(gdicbuf);
    if(suffixcnt>0) free(sufbuf);
    if(dentrycount>0) free(ddicbuf);
    if(weightf) fclose(weightf);
    }
}

/* FIXME ? differences with appenditem - use fprintf instead of  snprintf */
void sappenditem(char *word, int lind, int serial, int weight)
{
    int ll;
    char *p;

    if(!isalnum(*word) || (ll=strlen(word))<2 ||
       wordchr2(taken,word)!=NULL ||
       wordchr2(ignore[lind],word)!=NULL ||
       takenlen>=MAX_LINELEN-ll-16)
      return;
    if(ll==2 && (!isdigit(word[0]) || !isalpha(word[1]))) return;
    for(p=word;*p;p++) if(!isalnum(*p) && *p!=' ') return;
    taken[takenlen++]=' ';taken[takenlen++]=' ';
    ovlstrcpy(taken+takenlen,word);
    takenlen+=ll; tweight+=weight;
    fprintf(indf,"%s:%d?%d\n",word,serial,weight);
}

void onesheet(int serial, int lind)
{
    int i;
    unsigned char trlist[]={
    s_title,s_description,s_domain,s_keywords,s_information
    };
    #define trcnt (sizeof(trlist)/sizeof(trlist[0]))
    char *p1, *p2, buf[MAX_LINELEN+1];

    if(sheet_index(serial)) return;
    fprintf(listf,"%s\n",mod[serial].name+3);
    fprintf(titf,"%d:%s\n",serial,sindbuf[s_title]);
    fprintf(descf,"%d:%s\n",serial,sindbuf[s_description]);
    fprintf(remf,"%d:%s\n",serial,sindbuf[s_information]);
    fprintf(titlef,"%s:%s\n",mod[serial].name,sindbuf[s_title]);

    entrycount=dentrycount; dicbuf=ddicbuf;
    memmove(entry,dentry,dentrycount*sizeof(entry[0]));
    unknown_type=unk_leave;
    for(i=0;i<trcnt;i++) {
    detag(sindbuf[trlist[i]]);
    deaccent2(sindbuf[trlist[i]]);
    comma(sindbuf[trlist[i]]);
    singlespace2(sindbuf[trlist[i]]);
    translate(sindbuf[trlist[i]]);
    }

    entrycount=mentrycount; dicbuf=mdicbuf;
    memmove(entry,mentry,mentrycount*sizeof(entry[0]));
    unknown_type=unk_leave;
    for(i=0;i<trcnt;i++) {
    suffix_translate(sindbuf[trlist[i]]);
    translate(sindbuf[trlist[i]]);
    }
    taken[0]=0; takenlen=tweight=0;
    ovlstrcpy(buf,sindbuf[s_title]); towords(buf);
    for(p1=find_word_start(buf);*p1;
    p1=find_word_start(p2)) {
    p2=find_word_end(p1); if(*p2) *p2++=0;
    sappenditem(p1,lind,serial,4);
    }
    snprintf(buf,sizeof(buf),"%s %s %s %s",
         sindbuf[s_description],sindbuf[s_keywords],
         sindbuf[s_domain],sindbuf[s_information]);
    towords(buf);
    for(p1=find_word_start(buf);*p1;
    p1=find_word_start(p2)) {
    p2=find_word_end(p1); if(*p2) *p2++=0;
    sappenditem(p1,lind,serial,2);
    }
    entrycount=gentrycount; dicbuf=gdicbuf;
    memmove(entry,gentry,gentrycount*sizeof(entry[0]));
    unknown_type=unk_delete;
    ovlstrcpy(buf,sindbuf[s_title]); translate(buf);
    for(p1=find_word_start(buf); *p1;
    p1=find_word_start(p2)) {
    p2=strchr(p1,',');
    if(p2!=NULL) *p2++=0; else p2=p1+strlen(p1);
    if(strlen(p1)<=0) continue;
    sappenditem(p1,lind,serial,4);
    }
    snprintf(buf,sizeof(buf),"%s, %s, %s, %s",
         sindbuf[s_description],sindbuf[s_keywords],
         sindbuf[s_domain],sindbuf[s_information]);
    translate(buf);
    for(p1=find_word_start(buf); *p1;
    p1=find_word_start(p2)) {
    p2=strchr(p1,',');
    if(p2!=NULL) *p2++=0; else p2=p1+strlen(p1);
    if(strlen(p1)<=0) continue;
    sappenditem(p1,lind,serial,2);
    }
    fprintf(weightf,"%d:%d\n",serial,tweight);
}

void sheets(void)
{
    int i,j;
    char mdic[MAX_LINELEN+1], sdic[MAX_LINELEN+1], gdic[MAX_LINELEN+1], ddic[MAX_LINELEN+1];
    char buf[MAX_LINELEN+1];

    for(j=0;j<langcnt;j++) {
      snprintf(buf,sizeof(buf),"%s/title.%s",sheetoutdir,lang[j]);
      titf=fopen(buf,"w");
      snprintf(buf,sizeof(buf),"%s/description.%s",sheetoutdir,lang[j]);
      descf=fopen(buf,"w");
      snprintf(buf,sizeof(buf),"%s/%s",sheetoutdir,lang[j]);
      indf=fopen(buf,"w");
      snprintf(buf,sizeof(buf),"%s/list.%s",sheetoutdir,lang[j]);
      listf=fopen(buf,"w");
      snprintf(buf,sizeof(buf),"%s/weight.%s",sheetoutdir,lang[j]);
      weightf=fopen(buf,"w");
      snprintf(buf,sizeof(buf),"%s/addr.%s",sheetoutdir,lang[j]);
      addrf=fopen(buf,"w");
      snprintf(buf,sizeof(buf),"%s/information.%s",sheetoutdir,lang[j]);
      remf=fopen(buf,"w");
      snprintf(buf,sizeof(buf),"%s/serial.%s",sheetoutdir,lang[j]);
      serialf=fopen(buf,"w");
      snprintf(buf,sizeof(buf),"%s/tit.%s",sheetoutdir,lang[j]);
      titlef=fopen(buf,"w");
      if(!titlef || !serialf || !remf || !addrf || !weightf || !listf
        || !indf || !descf || !titf ) {
      fprintf(stderr,"modind: error creating output files for sheet %s.\n",sheetoutdir); exit(1);
    }
    snprintf(mdic,sizeof(mdic),"%s/%s.%s",dicdir,maindic,lang[j]);
    snprintf(sdic,sizeof(sdic),"%s/%s.%s",dicdir,suffixdic,lang[j]);
    snprintf(gdic,sizeof(gdic),"%s/%s.%s",dicdir,groupdic,lang[j]);
    snprintf(ddic,sizeof(ddic),"%s/%s.%s",dicdir,domaindic,lang[j]);
    suffix_dic(sdic); prepare_dic(gdic);
    gdicbuf=dicbuf; gentrycount=entrycount;
    memmove(gentry,entry,gentrycount*sizeof(entry[0]));
    prepare_dic(mdic);
    mdicbuf=dicbuf; mentrycount=entrycount;
    memmove(mentry,entry,mentrycount*sizeof(entry[0]));
    prepare_dic(ddic);
    ddicbuf=dicbuf; dentrycount=entrycount;
    memmove(dentry,entry,dentrycount*sizeof(entry[0]));
    unknown_type=unk_leave; translate(ignore[j]);
    for(i=0;i<modcnt;i++) {
        if(mod[i].langs[0]!=j) continue;
        fprintf(addrf,"%d:%s\n",i,mod[i].name+3);
        fprintf(serialf,"%s:%d\n",mod[i].name+3,i);
        onesheet(i,j);
    }
    if(mentrycount>0) free(mdicbuf);
    if(gentrycount>0) free(gdicbuf);
    if(suffixcnt>0) free(sufbuf);
    if(dentrycount>0) free(ddicbuf);
    fclose(titf); fclose(descf); fclose(indf); fclose(listf);
    fclose(weightf); fclose(addrf); fclose(serialf);
    }
}

int main()
{
    gentry=xmalloc(entry_size);
    dentry=xmalloc(entry_size);
    mentry=xmalloc(entry_size);
    prep();
    if(modcnt>0) modules();
    clean();
    sprep();
    if(modcnt>0) sheets();
    return 0;
}

