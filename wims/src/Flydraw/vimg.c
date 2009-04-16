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


void vimg_init (void)
{
    double x1,x2,y1,y2,t;
    if(vimgfilename[0]==0) vimgf=stdout;
    else vimgf=fopen(vimgfilename,"w");
    if(vimgf==NULL) {vimg_enable=0; return;}
    x1=xstart; y1=ystart;
    x2=sizex/xscale+xstart;
    y2=sizey/yscale+ystart;
    if(x2<x1) {t=x1;x1=x2;x2=t;}
    if(y2<y1) {t=y1;y1=y2;y2=t;}
    fprintf(vimgf,"  0\nSECTION\n  2\nHEADER\n\
  9\n$EXTMIN\n  10\n%f\n  20\n%f\n\
  9\n$EXTMAX\n  10\n%f\n  20\n%f\n\
  9\n$LIMMIN\n  10\n%f\n  20\n%f\n\
  9\n$LIMMAX\n  10\n%f\n  20\n%f\n\
  9\n$MEASUREMENT\n  70\n1\n  0\nENDSEC\n  0\nSECTION\n  2\nENTITIES\n",
	    x1,y1,x2,y2, x1,y1,x2,y2);
    vimg_ready=1;
}

void vimg_close (void)
{
    if(vimgf==NULL || vimg_ready==0) return;
    fprintf(vimgf,"  0\nENDSEC  \n  0\nEOF\n");
    fclose(vimgf); vimg_ready=vimg_enable=0; vimgf=NULL;
}

void vimg_arc (double x0,double y0, double rx, double ry,double a1, double a2)
{
    double mx,my,ratio;
    if(rx==ry) {
	fprintf(vimgf,"  0\nARC\n  10\n%f\n  20\n%f\n  40\n%f\n\
  50\n%f\n51\n%f\n",x0,y0,rx,a1,a2);
	return;
    }
    if(rx>ry) {mx=rx;my=0;ratio=ry/rx;}
    else {mx=0;my=ry;ratio=rx/ry;}
    fprintf(vimgf,"  0\nELLIPSE\n  10\n%f\n  20\n%f\n\
  11\n%f\n  21\n%f\n  40\n%f\n  41\n%f\n  42\n%f\n",
	    x0,y0,mx,my,ratio,
	    a1*3.14159265/180,a2*3.14159265/180);
    
}

void vimg_ellipse (double x0, double y0, double rx, double ry)
{
    if(rx==ry) {
	fprintf(vimgf,"  0\nCIRCLE\n  10\n%f\n  20\n%f\n\
  40\n%f\n",x0,y0,rx);
	return;
    }
    else vimg_arc (x0,y0,rx,ry,0,360);
}

void vimg_line (double x1,double y1,double x2,double y2)
{
    fprintf(vimgf,"  0\nLINE\n  10\n%f\n  20\n%f\n  11\n%f\n  21\n%f\n",
	   x1,y1,x2,y2);
}

void vimg_polyline (double xy[], int cnt, int closed)
{
    int i;
    fprintf(vimgf,"  0\nPOLYLINE\n  70\n%d\n",closed);
    for(i=0;i<2*cnt;i++,i++) {
	fprintf(vimgf,"  0\nVERTEX\n  10\n%f\n  20\n%f\n",
		xy[i],xy[i+1]);
    }
    fprintf(vimgf,"  0\nSEQEND\n");
}

void vimg_rect (double x1, double y1, double x2, double y2)
{
    double d[8];
    d[0]=x1; d[1]=y1; d[2]=x1; d[3]=y2;
    d[4]=x2; d[5]=y2; d[6]=x2; d[7]=y1;
    vimg_polyline (d,4,1);
}

void vimg_plotstart (void)
{
    fprintf(vimgf,"  0\nPOLYLINE\n  70\n0\n");
}

void vimg_plot1 (double x, double y)
{
    fprintf(vimgf,"  0\nVERTEX\n  10\n%f\n  20\n%f\n", x,y);
}

void vimg_plotend (void)
{
    fprintf(vimgf,"  0\nSEQEND\n");
}

