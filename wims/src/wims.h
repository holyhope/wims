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

/* WWW multipurpose server, header definitions */

#include "config.h"
#include "includes.h"
#include "wimsdef.h"
/* #include "wimsshm.h" */

        /* limit of query_string. */
#define QUERY_STRING_LIMIT 204799
	/* maximal length of deposited file */
#define MAX_DEPOSITLEN (8*1024*1024)
	/* maximal number of registered variables */
#define MAX_VAR_NUM 512
	/* length limit for public_html/bin executable names */
#define MAX_EXEC_NAME 31
	/* max level of nested fors */
#define MAX_FOR_LEVEL 12
	/* max nested read; to avoid infinite loop */
#define MAX_READNEST 20
	/* number of cached working files */
#define MAX_MCACHE 32
	/* max languages on a site, hard limit */
#define MAX_LANGUAGES 32
	/* max sort items. */
#define MAX_SORT_ITEM 5000
	/* max randperm() items. Should be compatible to MAX_LINELEN. */
#define MAX_RANDPERM 2000
	/* Number of session random numbers */
#define MAX_SESRANDOM 64
  /* Limit of output length. This can be configured. */
#define OUTPUT_LENGTH_LIMIT 600000
  /* limit of items in value lists */
#define MAX_VALUE_LIST 2048
	/* file to hold last output */
#define lastout	"last.html"
	/* temporary log file */
#define TEMP_LOG_FILE "../log/temp.log"
	/* Access policy configuration file */
#define ACCESS_CONF "../log/wims.conf.access"
	/* Should not be changed */
#define SESSION_BASE "sessions"
#define S2_BASE "s2"

	/* Prefix char for exec functions */
#define exec_prefix_char '!'
	/* Prefix char for calc functions */
#define calc_prefix_char '!'
	/* Prefix char for goto labels */
#define label_prefix_char ':'
	/* Prefix for tags in data files */
#define tag_prefix_char ':'
	/* Tag string for randfile */
#define tag_string "\n:"
	/* Prefix char for comment lines */
#define comment_prefix_char '#'
  /* prefix to user variable names */
#define var_prefix	"w_"
  /* (user) prefix for mathematical fonts */
#define mathfont_prefix	"m_"
  /* prefix for internal variables */
#define wims_prefix "wims_"
#define wpflen strlen(wims_prefix)
  /* name of variable definition file */
#define default_var_def "var.def"
	/* Not configured */
#define error_data_string "wims_error_data"
  /* Name of files containing error messages. */
#define user_error_msg_file "msg/user_error.phtml"
#define module_error_msg_file "msg/module_error.msg"
  /* directory containing log files */
#define log_dir "../log"
#define class_base "../log/classes"
  /* What should indicate that a file name given by the user 
   * would allow him to go upstairs in the directory tree?
   * We shouldn't use "../", otherwise the user may just specify
   * ".." as name and go upstairs one step. */
#define parent_dir_string ".."
  /* This one is stronger. */
#define PARENT_DIR_STRING "/../"
  /* kernel daemon socket file. Should match that of wimslogd. */
#define ksockfile "../tmp/log/.wimslogd"
  /* this directory should not exist. Do not change the definition! */
#define sysmask_trigger_dir "sysmask/stat/trigger"

typedef struct {
    int lineno; /* line number */
/*    long fpt;	*/ /* position in the file */
    char varname[MAX_NAMELEN+1];
    double varval;
    double varend;
    char *list_pt, *bufpt;
    double step;
    int from;	/* from ... to ... if 0, list if 1 */
} FOR_STACK;

typedef struct {
    char *address;
    short int execcode, varcode;
    int isstart; /* bit 0: start line; bit 1: exec; bit 2: label. bit 3: hard comment. bit 4: soft comment */
    unsigned int llen;
} LINE_STRUCT;

typedef struct {
    char name[MAX_FNAME+1];
    int  l;
    int linepointer;
	/* nocache bits: 0. !nocache; 1. hard nocache; 2. isfromcache; 3. isbase; */
    short int for_idx, nocache;
    int linecnt;
    char *textbuf;
    LINE_STRUCT *lines;
    FOR_STACK *for_stack;
} WORKING_FILE;

struct {
    char *name;
    char *font;
} charname[]={
    {"en","iso-8859-1"},
      {"fr","iso-8859-1"},
      {"es","iso-8859-1"},
      {"cn","gb2312"},
      {"de","iso-8859-1"},
      {"it","iso-8859-1"},
      {"nl","iso-8859-1"},
      {"si","iso-8859-2"},
      {"tw","big5"}
};

#define charname_no (sizeof(charname)/sizeof(charname[0]))

	/* var.c */
char *getvar(char *name);
int setvar(char *vname, char *vval);
void debug_output(void);
void exportall(void);

	/* config.c */
void setsesdir(char *p);

	/* variables.c */
void var_proc(char *fname,int cache);
void phtml_put(char *fname,int cache);
void phtml_put_base(char *fname,int cache);

	/* evalue.c */
double evalue(char *p);
char *substit(char *p);

	/* calc.c */
void calc_tolower(char *p);
void calc_toupper(char *p);

	/* log.c */
void user_log(char *p);
void write_logs(void);
void mail_log(char *p);
void flushlog(void);

	/* insmmath.c */
void insmath(char *p);

	/* mathfonts.c */
void fix_tex_size(void);

	/* exam.c */
void calc_examdep(char *p);

	/* test.c */
void exec_test(char *p);

	/* var.c */
int force_setvar(char *vname,char *vvalue);

	/* variables.c */
int var_def_check(char *name);

#if !HAVE_SETENV
int setenv(const char *name, const char *value, int overwrite);
void unsetenv(const char *name);
#endif
