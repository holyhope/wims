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

		/* student score management, definitions */

#include "../Lib/libwims.h"
#include "../wims.h"
#include <utime.h>
#include <sys/socket.h>
#include <sys/un.h>

	/* how many seconds in a minute? */
#define MINLENGTH 47
	/* maximal running minutes, in order to avoid leaking */
#define MAX_MIN 300
	/* queue of socket requests */
#define SOCKET_QUEUE 32
	/* socket buffer length */
#define BUFFERLEN (MAX_LINELEN+sizeof(scoreresult)*MAX_CLASSEXOS)
	/* number of log lines */
#define MAX_LOGLINES (102400)
	/* cuttime buffer, for all exams in a class */
#define CTBUFLEN 4096
	/* text buffer length in a sheet cache */
#define SHEETBUFLEN 8192
	/* number of cached classes */
	/* Storage requirement: about MAX_CLASSCACHE*(MAX_CLASSEXOS*10+CTBUFLEN) bytes. */
#define MAX_CLASSCACHE 20
	/* number of cached sheets */
	/* Storage requirement: about MAX_SHEETCACHE*SHEETBUFLEN bytes. */
#define MAX_SHEETCACHE 32
	/* Refreshment rate for class caches, in seconds */
#define CLASSCACHE_DELAY 100
	/* Refreshment rate for sheet caches, in seconds */
#define SHEETCACHE_DELAY 50
	/* Maximal debug file length. Debug will be activated once the debug file exists. */
#define MAX_DEBUGLENGTH 1000000
	/* delay before ins files are erased. In seconds */
#define INS_DELAY 500

#define evalue strevalue
#define tmpd "tmp/log"
#define classd "log/classes"
#define sesd "sessions"
#define modd "public_html/modules"
#define logd "log"
#define pidfile "tmp/log/wimslogd.pid"
#define sockfile "tmp/log/.wimslogd"
#define debugfile "tmp/log/wimslogd.debug"

