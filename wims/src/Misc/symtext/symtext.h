/*    Copyright (C) 2002-2003 XIAO, Gang of Universite de Nice - Sophia Antipolis
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

#ifndef SYMTEXT_H
#define SYMTEXT_H 1

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

#include "lines.h"

	/* Maximum of string length. */
#define MAX_LINELEN (40*1024-1)
	/* Maximum of blocks. Limited to sizeof(short). */
#define MAX_BLOCKS	8192
	/* Maximum of pools. Limited to sizeof(short). */
#define MAX_POOLS	10240
	/* Maximum of variable names. */
#define MAX_NAMELEN	63
	/* Maximum of (complete) file names. */
#define MAX_FNAME	199
	/* Maximum of dictionaries, including reserved ones. */
#define MAX_DICS	15
	/* Maximum of lists in permdata. Very limited. */
#define MAX_PERMLIST	4
	/* Size of list buffer */
#define MAX_LISTS	65536
	/* Limit of the length of builtin command names */
#define MAX_BINAME	10
	/* Limit to nesting levels */
#define MAX_LEVELS	16384
	/* How many picks at most */
#define MAX_PICKS	64
	/* limit of entries in a dictionary */
#define MAX_DICENTRIES 512*1024
	/* limit of any single dictionary size */
#define MAX_DICSIZE	10240*1024

	/* int or short */
#define listtype	short int
	/* default dictionary directory */
#define defaultdir	"scripts"

#define char_punct	".,;:?!\""
#define char_math	"+-*/=|%<>()_"
#define char_parenth	"()[]{}"
#define char_cs		"_&$#`\\@~"
#define char_quote	"`'\""

typedef struct block {
    char *string;		/* string for compare */
    int (*fn) (struct block *blk, char *start, int level);
    listtype nextblock, sublock;	/* subblocks are always consecutive */
    listtype len, lcnt, lind1, lind2, lstart, pool, mpool, mend;
    listtype *listlen;
    listtype *lists[MAX_PERMLIST];	/* permutation lists */
} block;

typedef struct poolstruct {
    listtype block, lastpool, ind1, ind2, dirty, len;
    char *string;
    listtype *tag;		/* level tags for recursion */
} poolstruct;

#endif

