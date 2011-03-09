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

	/* Daily housekeeping jobs. */
void housekeep(void)
{
    char fname[1024];
    FILE *keeplog;
    
    if(strncmp(keepdate,nowstr,8)==0) return;
    snprintf(fname,sizeof(fname),"%s/keepdate",tmpd);
    keeplog=fopen(fname,"r");
    if(keeplog==NULL) goto dokeep;
    (void)fread(keepdate,8,1,keeplog); keepdate[8]=0; fclose(keeplog);
    if(strncmp(keepdate,nowstr,8)==0) return;
    dokeep:
    keeplog=fopen(fname,"w");
    if(keeplog!=NULL) {
	fwrite(nowstr,8,1,keeplog);fclose(keeplog);
    }
    call_ssh(0,"bin/housekeep.daily &>%s/housekeep.log",tmpd);
}

	/* module update */
void modupdate(void)
{
    char fname[1024];
    FILE *muplog;
    
    if(strncmp(mupdate,nowstr,8)==0) return;
    snprintf(fname,sizeof(fname),"%s/mupdate",tmpd);
    muplog=fopen(fname,"r");
    if(muplog==NULL) goto domup;
    (void)fread(mupdate,8,1,muplog); mupdate[8]=0; fclose(muplog);
    if(strncmp(mupdate,nowstr,8)==0) return;
    domup:
    muplog=fopen(fname,"w");
    if(muplog!=NULL) {
	fwrite(nowstr,8,1,muplog);fclose(muplog);
    }
    call_ssh(0,"bin/modupdate.auto &>%s/modupdate.log",tmpd);
}

	/* Daily backup. */
void backup(void)
{
    FILE *backlog;
    
    if(strncmp(backdate,nowstr,8)==0) return;
    backlog=fopen("backup/backdate","r");
    if(backlog==NULL) goto dobackup;
    (void)fread(backdate,8,1,backlog); backdate[8]=0; fclose(backlog);
    if(strncmp(backdate,nowstr,8)==0) return;
    dobackup:
    call_ssh(0,"bin/backup &>%s/backup.log",tmpd);
}

