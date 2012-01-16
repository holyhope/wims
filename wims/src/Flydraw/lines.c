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

void error(char *p)
{
    fprintf(stderr,"%s %d\n",p,linecnt);
}

	/* Get a line in a stored working file. 
	 * Buffer length is always MAX_LINELEN. */

/* 1/2012 
J.M. Evers
Added ';' as additional command seperator 
*/ 
int ggetline(char buf[])
{
    int c;
    int i;
    for(i=0,c=getchar();i<MAX_LINELEN;i++,c=getchar()) {
	if(c=='\n' || c==EOF || c==';') break;
	buf[i]=c;
    }
    buf[i]=0; 
    if(linecnt!=-100000) linecnt++;
    return c;
}

double getvar(char *p)
{
    int i;
    for(i=0;i<varcnt && strcmp(p,vartab[i].name)!=0;i++);
    if(i<varcnt) return vartab[i].value;
    else return 0;
}

void setvar(char *p, double v)
{
    int i;
    if((strlen(p)>2 && strcmp(p,"animstep")!=0) || !isalpha(*p)) return;
    for(i=0;i<varcnt && strcmp(p,vartab[i].name)!=0;i++);
    if(i<varcnt) {vartab[i].value=v; return;}
    else {
	if(varcnt>=MAX_VARS || varnameptr>=varnamebuf+sizeof(varnamebuf)-1) return;
	ovlstrcpy(varnameptr,p);
	vartab[varcnt].name=varnameptr; vartab[varcnt].value=v;
	varnameptr+=strlen(varnameptr)+1; (varcnt)++;
    }
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
    else ovlstrcpy(p,pp+1);
}

int getcolor(int r, int g, int b)
{
    int col;
    if(r>255) r=255; if(r<0) r=0;
    if(g>255) g=255; if(g<0) g=0;
    if(b>255) b=255; if(b<0) b=0;
    col=gdImageColorExact(image, r, g, b);
    if(col==-1) col=gdImageColorAllocate(image,r,g,b);
    return col;
}

int widthcolor(int w, int color)
{
    int bg,fg,sh,e;
	    /* already allocated */
    if(wimg!=NULL && savew==w && wcolor==color) goto end;
    if(wimg!=NULL) gdImageDestroy(wimg);
    wimg=gdImageCreate(w,w);
    if(wimg==NULL) {
	error("width_creation_failure"); return color;
    }
    bg=gdImageColorAllocate(wimg,255,255,255);
    gdImageColorTransparent(wimg,bg);
    fg=gdImageColorAllocate(wimg,gdImageRed(image,color),
			    gdImageGreen(image,color),
			    gdImageBlue(image,color));
    e=w-1;sh=e/3;
    switch(w) {
	case 2: {
	    gdImageFill(wimg,0,0,fg); break;
	}
	case 3: {
	    gdImageFill(wimg,0,0,fg); 
	    gdImageSetPixel(wimg,2,0,bg);gdImageSetPixel(wimg,2,2,bg);
	    break;
	}
	case 4:
	case 5:
	case 6:
	case 7: 
	case 8:
	case 9:
	case 10:
	case 11:
	case 12: {
	    int pl[]={0,sh, sh,0, e-sh,0, e,sh,
		  e,e-sh, e-sh,e, sh,e, 0,e-sh};
	    gdImageFilledPolygon(wimg,(gdPointPtr) pl,8,fg);
	    break;
	}
	default: {
	    gdImageArc(wimg,w/2,w/2,w,w,0,360,fg);
	    gdImageFillToBorder(wimg,w/2,w/2,fg,fg);
	    break;
	}
    }
    savew=w; wcolor=color;
    end: gdImageSetBrush(image,wimg); return gdBrushed;
}

	/* scale coordinates, x then y */
void scale(double dbuf[], int ibuf[], int cnt)
{
    int i; double x,y;
    for(i=0;i<cnt*2 && i<MAX_PARMS;i+=2) {
	if(transform) {
	    x=dbuf[i]*matrix[0]+dbuf[i+1]*matrix[1];
	    y=dbuf[i]*matrix[2]+dbuf[i+1]*matrix[3];
	}
	else {x=dbuf[i]; y=dbuf[i+1];}
	scale_buf[i]=x+transx; scale_buf[i+1]=y+transy;
	ibuf[i]=rint((x-xstart+transx)*xscale);
	ibuf[i+1]=rint((y-ystart+transy)*yscale);
	if(ibuf[i]<-BOUND) ibuf[i]=-BOUND;if(ibuf[i]>BOUND) ibuf[i]=BOUND;
	if(ibuf[i+1]<-BOUND) ibuf[i+1]=-BOUND;if(ibuf[i+1]>BOUND) ibuf[i+1]=BOUND;
    }
}

	/* scale without displacement */
void scale2(double xin, double yin, double *xout, double *yout)
{
    if(transform) {
	*xout=xin*matrix[0]+yin*matrix[1];
	*yout=xin*matrix[2]+yin*matrix[3];
    }
    else {
	*xout=xin; *yout=yin;
    }
    *xout*=xscale; *yout*=yscale;
}

