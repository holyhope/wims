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

	/* Nothing but check configure output, to see
	 * whether there are some missing functions in the system. */

  /* Common: WIMS cannot be installed on your system. Please report. */

#include "config.h"

	/* Check system service functions */

#ifndef HAVE_ALARM
 #error Function alarm() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_FLOOR
 #error Function floor() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_GETCWD
 #error Function getcwd() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_GETTIMEOFDAY
 #error Function gettimeofday() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_MALLOC
 #error Function malloc() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_MEMMOVE
 #error Function memmove() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_MEMSET
 #error Function memset() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_MKDIR
 #error Function mkdir() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_POW
 #error Function pow() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_REALLOC
 #error Function realloc() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_RINT
 #error Function rint() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_RMDIR
 #error Function rmdir() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_SELECT
 #error Function select() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_SQRT
 #error Function sqrt() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_STRNCASECMP
 #error Function strncasecmp() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_STRRCHR
 #error Function strrchr() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_STRPBRK
 #error Function strpbrk() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_STRSTR
 #error Function strstr() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_UTIME_NULL
 #error Function utime() unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_WORKING_FORK
 #error Function fork() unavailable or not working. WIMS cannot be installed on your system. Please report.
#endif

	/* Now libraries */

#ifndef HAVE_LIBM
 #error Math library libm unavailable. WIMS cannot be installed on your system. Please report.
#endif

	/* Now header files */

#ifndef STDC_HEADERS
 #error ANSI C header files unavailable. WIMS cannot be installed on your system. Please report.
#endif

#ifndef HAVE_UNISTD_H
 #error Header file unistd.h unavailable. WIMS cannot be installed on your system. Please report.
#endif
