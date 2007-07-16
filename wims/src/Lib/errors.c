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

	/* type=1: user. type=2: module. type=3: internal. */
void _error(char *msg, int type)
{
    fprintf(stderr,"%s\n",msg);
    exit(type);    
}

void _error1(char *msg) {_error(msg,1);}
void _error2(char *msg) {_error(msg,1);}
void _error3(char *msg) {_error(msg,1);}

void (*error1) (char *msg)=_error1;
void (*error2) (char *msg)=_error2;
void (*error3) (char *msg)=_error3;

