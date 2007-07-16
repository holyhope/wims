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

 /* This file is a temporary patch to tex eps files with extra borders.
  * It cuts the borders in the resulting gif file, so that the font
  * fits tightly in the cadre. libgd is required. */

#include "flydraw.h"
#include "../Lib/libwims.h"

char imagefilename[1024];
int sizex, sizey, saved;
gdImagePtr image=NULL, brushimg=NULL, tileimg=NULL, wimg=NULL;
int brushed=0,tiled=0,styled=0,width=1, savew=1, wcolor=-1;
int color_white,color_black,color_bounder;
int linecnt=-100000;
int tranged=0;
double xscale=1,yscale=1,xstart=0,ystart=0;
double tstart=0,tend=1,tstep=100,plotjump=200;
double animstep=0;
double matrix[]={1,0,0,1};	/* transformation matrix */
int transform=0;		/* transformation indicator */
double transx=0,transy=0;	/* translation vector */
int lstep=4;
ev_variable vartab[MAX_VARS];
char varnamebuf[MAX_VARNAMEBUF], *varnameptr=varnamebuf;
int varcnt;
/***** Les modifs a JC Fev 06 *****/
/** les matrices suivantes sont initialisees par la commande setmatrix nummatrix,a11,a12,a21,a22 */
/** elles sont remises a l'unite par resetmatrix nummatrix */
double matrix01[] = {1,0,0,1};
double matrix02[] = {1,0,0,1};
double matrix03[] = {1,0,0,1};
double matrix04[] = {1,0,0,1};
double matrix05[] = {1,0,0,1};
double matrix06[] = {1,0,0,1};
double matrix07[] = {1,0,0,1};
double matrix08[] = {1,0,0,1};
double matrix09[] = {1,0,0,1};
double matrix10[] = {1,0,0,1};
double matrix11[] = {1,0,0,1};
double matrix12[] = {1,0,0,1};
double matrix13[] = {1,0,0,1};
double matrix14[] = {1,0,0,1};
double matrix15[] = {1,0,0,1};
double matrix16[] = {1,0,0,1};
double matrix17[] = {1,0,0,1};
double matrix18[] = {1,0,0,1};
double matrix19[] = {1,0,0,1};
#define JC_NB_MATRICES 19
/* la matrice fixant le systeme de coordonnees "mathematiques" dans l'image */
double *matrices_pavage[] ={ matrix, 
				matrix01,matrix02,matrix03,matrix04,matrix05,matrix06,matrix07,matrix08,matrix09,
				matrix10,matrix11,matrix12,matrix13,matrix14,matrix15,matrix16,matrix17,matrix18,matrix19

}; 
/** les vecteurs suivants sont initialises par la commande setvector numvector,u_1,u_2 */
/** ils sont remis a zero par resetvector numvector */
double vector[] = {0,0};
double vector01[] = {0,0};
double vector02[] = {0,0};
double vector03[] = {0,0};
double vector04[] = {0,0};
double vector05[] = {0,0};
double vector06[] = {0,0};
double vector07[] = {0,0};
double vector08[] = {0,0};
double vector09[] = {0,0};
double vector10[] = {0,0};
double vector11[] = {0,0};
double vector12[] = {0,0};
double vector13[] = {0,0};
double vector14[] = {0,0};
double vector15[] = {0,0};
double vector16[] = {0,0};
double vector17[] = {0,0};
double vector18[] = {0,0};
double vector19[] = {0,0};

double *vecteurs_pavage[] ={ vector, 
				vector01,vector02,vector03,vector04,vector05,vector06,vector07,vector08,vector09,
				vector10,vector11,vector12,vector13,vector14,vector15,vector16,vector17,vector18,vector19
}; 

/** les coordonnees du parallelograme de pavage = coordonnees "mathematiques" du parallelogramme contenant l'image a recopier **/
/** on place ces coorodonnes avec setparallelogram xs,ys,xu,yu,xv,yu **/
/* xs,ys=coordonnees math du point 0,0, 
 * xu,yu coordonnees math de l'horizontale
 * xv,yv coordonnees math de la verticale
 * ces coordonnees sont remises a leur valeur par defaut par resetparallelogram
 */
/** TODO serait-ce un moyen de definir la brush ?? **/
double parallogram_fonda[]={0,0,100,0,0,100};

/**** Fin modifs JC Fev 06 ******/

	/* Write the image */
void output(void)
{
    FILE *out;

    if(!image) return;
    if(imagefilename[0]) {
	out=fopen(imagefilename,"wb");
	if(out!=NULL) {gdImageGif(image,out); fclose(out); }
    }
    else gdImageGif(image,stdout);
    saved=1;
}

#include "lines.c"
#include "nametab.c"
#include "evalue.c"
#include "objects.c"

void process(void)
{
    char buf[MAX_LINELEN+1];
    int c;
    do {
	c=ggetline(buf); obj_main(buf);
    }
    while(c!=EOF);
}

int verify_tables(void) {
    return evaltab_verify();
}

int main(int argc, char *argv[])
{
    error1=error; error2=error; error3=error;
    substitute=substit;
    ev_varcnt=&varcnt; ev_var=vartab;
    if(argc==2 && strcasecmp(argv[1],"table")==0) {
	if(verify_tables()) {
	    printf("Table disorder.\n"); return 1;
	}
	printf("Table orders OK.\n"); return 0;
    }
    vartab[0].name="animstep"; vartab[0].value=0;
    varcnt=1;
    if(argc>1) snprintf(imagefilename,sizeof(imagefilename),"%s",argv[1]);
    else imagefilename[0]=0;
    process();
    if(!saved || imagefilename[0]!=0) output();
    if(image) gdImageDestroy(image);
    return 0;
}

