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

	/* Mathematical expression manipulations for WIMS, header declarations */

/* #include "../../Lib/libwims.h" */
#include "../../wims.h"
#include <regex.h>

	/* maximal number of object lines */
#define MAX_OBJLINES	2048
	/* maximal number of cuts */
#define MAX_COMMAS	1024
	/* maximal number of regex strings */
#define MAX_REGEX	16


