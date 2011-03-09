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

		/* student score management */

double oldfactor=0.85;  /* quality factor, should remain stable. */

	/* User score information of an exercise. Size: 16 bytes. */
typedef struct scoredata {
    unsigned short int num, new, try, hint;
    float user, user2;
} scoredata;

struct scoreheader {
    char raf[8][20];
    int sheet, exo;
    char session[32];
} scoreheader;
struct scoredata uscore[MAX_CLASSEXOS];

struct scoreresult tscore[MAX_CLASSEXOS];

#define oldraf scoreheader.raf
#define oldsheet scoreheader.sheet
#define oldexo scoreheader.exo
#define oldsession scoreheader.session

	/* one line of score. */
void scoreline(struct classdata *cd, char *l)
{
    int i,sheet,exo,num;
    char *pm[16];
    struct scoredata *thiscore;
    float score;

    i=cutwords(l,pm,8); if(i<6) return;
    if(strcmp(pm[i-1],"noscore")==0 || strcmp(pm[i-1],"erased")==0) {
	if(strcmp(pm[1],oldsession)!=0) 
	  mystrncpy(oldsession,pm[1],sizeof(oldsession));
	return;
    }
    sheet=atoi(pm[2]); exo=atoi(pm[3]);
    if(sheet<=0 || sheet>MAX_SHEETS || exo<=0 || exo>MAX_EXOS) return;
    num=search_data(cd->exos,cd->exocnt,sizeof(exodata),((sheet-1)<<8)+(exo-1));
    if(num<0) return;
    thiscore=uscore+num;
    if(strcmp(pm[4],"score")==0) {
	score=atof(pm[5]); if(!finite(score)) score=0;
	if(score>10) score=10; if(score<-10) score=-10;
	
	if(strcmp(pm[1],oldsession)==0 &&   /* measure to prohibit simultaneous scoring. */
	   sheet==oldsheet && exo==oldexo &&
	   strncmp(pm[0],oldraf[6],13)!=0   /* prohit scores immediately after rafale */
	   ) {
	    thiscore->user+=score;
	    thiscore->user2*=oldfactor;
	    thiscore->user2+=score;
	    if(thiscore->try<60000) thiscore->try++;
	    oldsheet=oldexo=0;
	}
    }
    else {
	if(strcmp(pm[4],"rafale")==0) { /* rafale punishment */
	    if(strncmp(pm[0],oldraf[3],13)==0 && thiscore->new<60000) thiscore->new++;
	    memmove(oldraf[1],oldraf[0],sizeof(oldraf[0])*7);
	    mystrncpy(oldraf[0],pm[0],sizeof(oldraf[0]));
	}
	if(strcmp(pm[4],"resume")!=0 && strcmp(pm[4],"rafale")!=0) {
	    if(strcmp(pm[4],"hint")==0) thiscore->hint++;
	    else if(thiscore->new<60000) thiscore->new++;
	}
	mystrncpy(oldsession,pm[1],sizeof(oldsession));
	oldsheet=sheet; oldexo=exo;
    }
}

unsigned int _cuttime(char ends[], char starts[], unsigned int startn)
{
    int h1,h2,m1,m2,s2, t;
    if(ends[0]==0) return 0;
    if(strncmp(ends,starts,14)<0) return 10;
    if(strncmp(ends,starts,8)>0) return 0;
    h1=atoi(ends+9);   m1=atoi(ends+12);
    h2=atoi(starts+9); m2=atoi(starts+12); s2=atoi(starts+15);
    t=((h1-h2)*60+(m1-m2))*60-s2;
    return startn+t;
}

	/* Gather exam score. */
void examscorecalc(struct classdata *cd, char *uname)
{
    struct scoredata *thiscore;
    char nbuf[MAX_FNAME+1];
    char cuttimes[MAX_EXOS][16];
    char rbuf[MAX_FILELEN+1];
    char *wlist[8];
    char *p1, *p2;
    int i, k, ecnt, num;
    double ss, sc[MAX_EXOS], sc2[MAX_EXOS];
    int ind[MAX_EXOS];
    unsigned int tr[MAX_EXOS], all[MAX_EXOS], ver[MAX_EXOS], start[MAX_EXOS], dure[MAX_EXOS];
    char *ip[MAX_EXOS], *ses[MAX_EXOS];
    unsigned int start1, endtime[MAX_EXOS];
    signed int dure1;

    ecnt=cd->examcnt; if(ecnt<=0) return; if(ecnt>MAX_EXOS) ecnt=MAX_EXOS;
    memset(all,0,sizeof(all)), memset(ver,0,sizeof(ver));
    for(i=0;i<MAX_EXOS;i++) ind[i]=-1;
    for(i=0;i<ecnt;i++) {
	k=((cd->exos[i+cd->examstart].num)&255);
	all[k]=cd->exos[i+cd->examstart].require;
	ind[k]=i+cd->examstart;
    }
    memset(sc,0,sizeof(sc)); memset(sc2,0,sizeof(sc2));
    memset(tr,0,sizeof(tr)); memset(cuttimes,0,sizeof(cuttimes));
    memset(dure,0,sizeof(dure)); memset(start,0,sizeof(start));
    memset(endtime,0,sizeof(endtime));
    memset(ip,0,sizeof(ip)); memset(ses,0,sizeof(ses));
    snprintf(nbuf,sizeof(nbuf),"score/%s.exam",uname);
    readfile(nbuf,rbuf,sizeof(rbuf));
    if(rbuf[0]==0) goto end;
    for(p1=rbuf; p1!=NULL && *p1; p1=p2) {
	p2=strchr(p1,'\n'); if(p2!=NULL) *p2++=0;
	i=cutwords(find_word_start(p1),wlist,7);
	if(i<6) continue;
	i=atoi(wlist[0])-1; if(i<0 || i>=ecnt) continue;
	dure1=atoi(wlist[2]); start1=atoi(wlist[3]);
	if(strcmp(wlist[1],"--")==0) {	/* session closure */
	    start[i]=dure[i]=0; ip[i]=ses[i]="";
	    continue;
	}
	if(strcmp(wlist[1],"00")==0) {
	    if(sc2[i]<sc[i]) sc2[i]=sc[i];
	    ver[i]=1; tr[i]++; start[i]=start1; dure[i]=dure1; sc[i]=0;
	    ip[i]=wlist[4]; ses[i]=wlist[5];
	    if(tr[i]==1 && wlist[6]!=NULL) {
		char *pp1, *pp2, lbuf[CTBUFLEN];
		if(cd->ctptr[ind[i]]>=0)
		  mystrncpy(lbuf,cd->ctbuf+cd->ctptr[ind[i]],sizeof(lbuf));
		else lbuf[0]=0;
		if(lbuf[0]) {
		    for(pp1=find_word_start(lbuf); *pp1; pp1=find_word_start(pp2)) {
			pp2=find_word_end(pp1); if(pp2-pp1!=14) continue;
			if(*pp2) *pp2++=0;
			pp1[8]='.'; pp1[11]=':';
			if(strcmp(pp1,wlist[6])<0) continue;
			memmove(cuttimes[i],pp1,15); break;
		    }
		}
	    }
	    endtime[i]=_cuttime(cuttimes[i],wlist[6],start1);
	}
	else if(ver[i]==0) tr[i]++;
	if(tr[i]>all[i]) continue;
	ss=atof(wlist[1]); if(ss<=0) continue; if(ss>10) ss=10;
	if(ss!=sc[i] && (dure1>=0 ||	/* checking conditions */
			(start1-start[i]<dure[i]*60 &&
			 dure[i]>0 && dure[i]<4096 &&
			 *ses[i]!=0 && *ip[i]!=0 &&
			 start[i]!=0 && start1>start[i] &&
			 (endtime[i]==0 || endtime[i]>=start1) &&
			 strcmp(ip[i],wlist[4])==0 &&
			 strcmp(ses[i],wlist[5])==0)))
	  sc[i]=ss;
    }
    end:
    for(i=0; i<ecnt; i++) {
	if(sc2[i]<sc[i]) sc2[i]=sc[i];
	num=search_data(cd->exos,cd->exocnt,sizeof(exodata),0xFF00+i);
	if(num<0) continue;
	thiscore=uscore+num;
	thiscore->user=sc2[i];
	thiscore->try=tr[i];
	if(cuttimes[i][0] && strncmp(cuttimes[i],nowstr,14)<0) k=0; else k=1;
	thiscore->hint=k;
    }
}

	/* calculate score from raw data, core routine. */
void rawscorecalc(struct classdata *cd, char *uname)
{
    int i;
    char fbuf[MAX_FILELEN+1];
    char *p1, *p2;
    char namebuf[MAX_FNAME+1];

    memset(uscore,0,sizeof(uscore[0])*cd->exocnt);
    memset(&scoreheader,0,sizeof(scoreheader));
    for(i=0;i<cd->exocnt;i++) uscore[i].num=cd->exos[i].num;
    snprintf(namebuf,sizeof(namebuf),"score/%s",uname);
    readfile(namebuf,fbuf,sizeof(fbuf));
    if(fbuf[0]!=0) {
	oldsession[0]=oldsheet=oldexo=0;
	for(p1=fbuf; *p1; p1=p2) {
	    p2=strchr(p1,'\n'); if(p2) *p2++=0; else p2=p1+strlen(p1);
	    if(myisdigit(*p1)) scoreline(cd,p1);
	}
    }
    examscorecalc(cd,uname);
}

void savescorebin(struct classdata *cd, char *uname)
{
    int fd, cnt;
    char fname[MAX_FNAME+1];
    snprintf(fname,sizeof(fname),"score/%s.bin",uname);
    cnt=cd->exocnt;
    fd=creat(fname,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if(fd==-1) return;
    (void)write(fd,&scoreheader,sizeof(scoreheader));
    (void)write(fd,uscore,sizeof(uscore[0])*cnt);
    close(fd);
}

void readscorebin(char *fname,int cnt)
{
    int fd;
    fd=open(fname,O_RDONLY);
    if(fd==-1) return;
    (void)read(fd,&scoreheader,sizeof(scoreheader));
    (void)read(fd,uscore,sizeof(uscore[0])*cnt);
    close(fd);
}

void getscore(struct classdata *cd, char *user)
{
    struct stat st[3];
    int i, cnt, non[3];
    char buf[3][MAX_FNAME+1];
    
    snprintf(buf[0],sizeof(buf[0]),"score/%s",user);
    snprintf(buf[1],sizeof(buf[1]),"score/%s.exam",user);
    snprintf(buf[2],sizeof(buf[2]),"score/%s.bin",user);
    cnt=cd->exocnt; if(cnt<=0) return;
    for(i=0;i<3;i++) non[i]=stat(buf[i],st+i);
    if(non[0] && non[1]) {
	memset(uscore,0,sizeof(uscore[0])*cnt);
	memset(&scoreheader,0,sizeof(scoreheader));
	return;
    }
    if(!non[2] &&
       st[2].st_size==sizeof(scoreheader)+sizeof(uscore[0])*cnt &&
       (non[0] || st[2].st_mtime>=st[0].st_mtime) &&
       st[2].st_mtime>=cd->modif) {
	readscorebin(buf[2],cnt);
	if(!non[1] && st[2].st_mtime<st[1].st_mtime) {
	    examscorecalc(cd,user);
	    savescorebin(cd,user);
	}
	return;
    }
    rawscorecalc(cd,user);
    savescorebin(cd,user);
}

void cmd_getscore(char *p)
{
    struct classdata *cd;
    char *cut[4];
    int i, sheet, exo, snew, stry, lastsheet, thissheet, thisexo;
    double score, score2, quality, tt, ts, thisscore;
    if(cwdtype!=dir_class) {
	sockerror(2,"getscore_no_class"); return;
    }
    if(*opt_user==0) {
	sockerror(2,"getscore_no_user"); return;
    }
    cd=getclasscache(opt_class);
    if(cd==NULL) {
	sockerror(2,"getscore_bad_class"); return;
    }
    if(cutwords(p,cut,3)==3) {
	thissheet=atoi(cut[0]); thisexo=atoi(cut[1]); thisscore=atof(cut[2]);
	if(!finite(thisscore)) thisscore=0;
	if(thisscore<-10) thisscore=-10;
	if(thisscore>10) thisscore=10;
    }
    else {thissheet=thisexo=thisscore=0;}
    getscore(cd,opt_user);
    lastsheet=0;
    for(i=0;i<cd->exocnt;i++) {
	tscore[i].num=cd->exos[i].num;
	tscore[i].require=cd->exos[i].require;
	tscore[i].weight=cd->exos[i].weight;
	sheet=(cd->exos[i].num>>8)+1;
	exo=((cd->exos[i].num)&255)+1;
	score=uscore[i].user; stry=uscore[i].try; score2=uscore[i].user2;
	if(sheet==thissheet && exo==thisexo) {
	    score+=thisscore; stry++;
	    score2*=oldfactor; score2+=thisscore;
	}
	if(sheet==256) {
	    tscore[i].score=score;
	    tscore[i].mean=stry*2+uscore[i].hint;
	    continue;
	}
	if(score>cd->exos[i].require) score=cd->exos[i].require;
	if(score>0 && stry>0) {
	    snew=uscore[i].new; if(uscore[i].hint>0) snew++;
	    	/* here we give up to 1 time unsuccessful tries.
		 * Together with a premium of 5 uncounted tries. */
	    if(snew<stry*2+5) tt=1;
	    else tt=(double) (snew-4)/(2*stry); /* tt>=1 */
	    ts=(1-pow(oldfactor,stry))/(1-oldfactor);
	    quality=score2/(ts*tt);
	}
	else score=quality=0;
	tscore[i].score=score; tscore[i].mean=quality;
    }
    answerlen=cd->exocnt*sizeof(tscore[0]);
    memmove(textbuf+3,tscore,answerlen);
    answerlen+=3;
}

void cmd_scorelog(char *p)
{
    struct classdata *cd;
    char buf[MAX_LINELEN+1];
    
    if(cwdtype!=dir_class) {
	sockerror(2,"scorelog_no_class"); return;
    }
    if(*opt_user==0) {
	sockerror(2,"scorelog_no_user"); return;
    }
    cd=getclasscache(opt_class);
    if(cd==NULL) {
	sockerror(2,"scorelog_bad_class"); return;
    }
    getscore(cd,opt_user);
    p=find_word_start(p); strip_trailing_spaces(p);
    snprintf(buf,sizeof(buf),"%s\n",p);
    accessfile(buf,"a","score/%s",opt_user);
    if(myisdigit(*p)) scoreline(cd,p);
    savescorebin(cd,opt_user);
}

