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

/* WWW interactive multipurpose server, header definitions */

#ifndef wimsdef_h

	/* maximal (multi-)line length. */
#define MAX_LINELEN 32000
	/* limit of items in a list; will never exceed MAX_LINELEN/2. */
#define MAX_LIST 8192
 	/* maximal name length */
#define MAX_NAMELEN 63
	/* maximal file name length, complete path. */
#define MAX_FNAME 199
	/* maximal module name length. */
#define MAX_MODULELEN 100
	/* maximal number of resident executions */
#define MAX_MULTIEXEC 4
	/* maximal file length for webget */
#define MAX_WEBGETFLEN (32*1024*1024)
	/* max length of class name */
#define MAX_CLASSLEN 31
	/* max length of session name */
#define MAX_SESSIONLEN 23
	/* max number of exercises in a class (sheets and exams) */
#define MAX_CLASSEXOS 2048
	/* max number of exercises in a sheet; not modifiable */
#define MAX_EXOS 64
	/* max number of sheets; not modifiable */
#define MAX_SHEETS 64
	/* max length of data files: records, activities, definitions. */
#define MAX_FILELEN (2048*1024-1)
	/* max number of filewrite calls in one request */
#define MAX_FWRITE 20
	/* max total size of filewrite in one request */
#define MAX_FWRITE_SIZE (64*1024)

	/* max number of lines in a work file */
	/* Limit for datafield cache */
#define LINE_LIMIT 16384
	/* size of cached datafields */
#define DATAFIELD_LIMIT 16384

	/* Define current version of the server here */
#define wims_version PACKAGE_VERSION
#ifdef VERSION_DATE
  #define wims_version_date VERSION_DATE
#else
  #define wims_version_date ""
#endif

#define SHORTSWNAME "WIMS"
#define LONGSWNAME "WWW Interactive Multipurpose Server"

typedef struct scoreresult {
    unsigned short int num, pad;
    float require, weight, score, mean;
} scoreresult;

#define wimsdef_h
#endif
