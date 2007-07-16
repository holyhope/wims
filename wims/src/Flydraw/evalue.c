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

	/* It is this routine which uses print_precision. */
void float2str(double d, char *p)
{
    char buf[64], *pp;
    int i;
    if(d==0) {
	strcpy(p,"0"); return;
    }
    i=10; /* simple precision cookup */
    snprintf(buf,sizeof(buf),"%%.%dg",i);
    snprintf(p,MAX_LINELEN,buf,(double) d);
    pp=p;while(isspace(*pp)) pp++;
    if(pp>p) strcpy(p,pp);
}

	/* substitute variable names by their environment strings
	 * The buffer pointed to by p must have enough space
	 * (defined by MAX_LINELEN). */
char *substit(char *p)
{
    char *pp, *pe;
    char namebuf[MAX_NAMELEN+1];
    int i, l;

    pe=strchr(p,'"'); if(pe!=NULL) l=pe-p; else l=MAX_LINELEN;
    for(pp=find_name_start(p); *pp!=0 && pp-p<l;
	pp=find_name_start(pe)) {
	pe=find_name_end(pp);
	if((pp>p && !isspace(*(pp-1)) && *(pp-1)!=',') ||
	   (*pe!=0 && !isspace(*pe) && *pe!=',')) continue;
	memmove(namebuf,pp,pe-pp); namebuf[pe-pp]=0;
	i=search_list(nametab,nametab_no,sizeof(nametab[0]),namebuf);
	if(i<0) continue;
	if(nametab[i].type==t_prep && preptab[nametab[i].serial].typ==p_font) 
	  break;
	if(nametab[i].type==t_color) 
	  string_modify(p,pp,pe,colortab[nametab[i].serial].def);
    }
    return p;
}

double evalue(char *p)
{
    return strevalue(p);
}
    
