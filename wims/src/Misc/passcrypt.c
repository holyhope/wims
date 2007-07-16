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

	/* Crypt password as in /etc/shadow */

#define MAX_LINELEN 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include "../config.h"
#ifdef HAVE_SYS_TIME_H
 #include <sys/time.h>
#endif
#ifdef HAVE_CRYPT
 #include <crypt.h>
#endif

int salt;
char schar[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";

void pcrypt(char *p)
{
#ifdef HAVE_CRYPT
    char saltstr[4];
    char *pp, buf[MAX_LINELEN+1];
    saltstr[0]=schar[salt%64];
    saltstr[1]=schar[(salt/64)%64];
    saltstr[2]=0;
    while(isspace(*p)) p++;
    for(pp=p+strlen(p); pp>p && isspace(*(pp-1)); pp--); *pp=0;
    snprintf(buf,sizeof(buf),"%s",crypt(p,saltstr));
    strcpy(p,buf);
#endif
}

int main(int argc,char *argv[])
{
    int salt1;
    char p[MAX_LINELEN+1];

#ifdef HAVE_GETTIMEOFDAY
    struct timeval tv;
    gettimeofday(&tv,NULL); salt1=tv.tv_sec+tv.tv_usec;
#else
    salt1=3219;
#endif
    if(argc<1) return 1;
    srandom(salt1+getpid());
    salt=random()/101;
    snprintf(p,sizeof(p),"%s",argv[1]);
    pcrypt(p); printf("%s\n",p);
    
    return 0;
}

