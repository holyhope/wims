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

/* WWW multipurpose server, dynamic library definitions */

	/* errors.c */
void (*error1) (char *msg);
void (*error2) (char *msg);
void (*error3) (char *msg);

	/* lines.c */
char *int2str(int i);
void *xmalloc(size_t n);
int msleep(int ms);	/* millisecond sleeper */
void _tolinux(char *p);		/* dos/mac to unix/linux translation */
void mystrncpy(char *dest, char *src, int lim);	/* optimized and secured strncpy */
        /* find matching parenthesis.
	 * The entrance point should be after the opening parenthesis.
	 * Returns NULL if unmatched. */
char *find_matching(char *p, char c);
char *find_word_start(char *p);	/* Strips leading spaces */
char *find_word_end(char *p);	/* Points to the end of the word */
char *strparchr(char *p, char c);	/* search for char, skipping parentheses */
char *strparstr(char *p, char *fnd);	/* search for string, skipping parentheses */
char *find_item_end(char *p);	/* Points to the end of an item */
char *find_line_end(char *p);	/* Points to the end of a line */
char *charchr(char *p,char *w);
char *wordchr(char *p, char *w);	/* Find first occurrence of word */
char *itemchr(char *p, char *w);	/* Find first occurrence of item */
char *linechr(char *p, char *w);	/* Find first occurrence of line */
char *varchr(char *p, char *v);		/* Find first occurrence of math variable */
int cutitems(char *p, char *list[], int max); 	/* Cut items of a string */
int cutwords(char *p, char *list[], int max); 	/* Cut words of a string */
int cutlines(char *p, char *list[], int max); 	/* Cut lines of a string */
int cutchars(char *p, char *list[], int max); 	/* Cut chars of a string */
char *strip_trailing_spaces(char *p);	/* strip trailing spaces; return string end. */
        /* Verify whether a list is well-ordered. For debugging uses.
	 * Returns 0 if order is OK, -1 otherwise. */
int verify_order(void *list, int items, size_t item_size);
        /* searches a list. Returns index if found, -1 if nomatch. 
	 * Uses binary search, list must be sorted. */
int search_list(void *list, int items, size_t item_size, const char *str);
unsigned int linenum(char *p);		/* Returns number of lines in string p */
unsigned int itemnum(char *p);		/* Returns number of items in the list p, comma separated */
unsigned int wordnum(char *p);		/* Returns number of words in string p */
unsigned int charnum(char *p);		/* This is just to suppress an annoying compiler warning message. */
char *fnd_line(char *p, int n, char bf[]); /* find n-th line in string p */
char *fnd_item(char *p, int n, char bf[]); /* find n-th item in list p, comma separated */
char *fnd_word(char *p, int n, char bf[]); /* find n-th word in string p */
char *fnd_char(char *p, int n, char bf[]); /* find n-th char in string p */
char *fnd_row(char *p, int n, char bf[]); /* find n-th row in a matrix p */
        /* Separate items in the string p, end each item with 0,
	 * and store item pointers in parm[]. Does not parse past max.
	 * Returns the number of fields. */
int separate_item(char *p, char *parm[], int max);
int separate_line(char *p, char *parm[], int max);
int separate_word(char *p, char *parm[], int max);
int _separator(char *p,char *parm[], int max, char fs);
int rows2lines(char *p);		/* Returns 1 if semicolons changed to new lines */
void lines2rows(char *p);
unsigned int rownum(char *p);
void words2items(char *p);	/* change words to items */
void words2lines(char *p);	/* change words to lines */
void lines2items(char *p);	/* change lines to items */
void lines2words(char *p);	/* change lines to words */
void items2words(char *p);	/* change items to words */
void items2lines(char *p);	/* change items to lines */
void strip_enclosing_par(char *p);	/* Strip enclosing pairs of parentheses */
        /* strstr but may have embedde deros. 
	 * Returns memory end if not found.
	 * Supposes memory ends with 0. */
char *memstr(char *s1, char *s2, int len);
        /* Check whether parentheses are balanced in a given string.
	 * Returns 0 if OK. */
        /* style=0: simple check. style<>0: strong check. */
int check_parentheses(char *p, int style);
void nospace(char *p);		/* collapses all space characters in string. */
void singlespace(char *p);	/* change all spaces into ' ', and collapse multiple occurences */
void deaccent(char *p);		/* fold accented letters to unaccented */
void reaccent(char *p);		/* compose accented letters using symbols */
	/* modify a string. Bufferlen must be ast least MAX_LINELEN */
void string_modify(char *start, char *bad_beg, char *bad_end, char *good,...);
long int filelength(char *fn,...);
int catfile(FILE *outf, char *fn,...);
char *fnd_position;
char *fnd_nextpos;

/* My accelerated definitions. */
#define myisdigit(x) (x>='0' && x<='9')
#define myisalpha(x) ((x&~32)>='A' && (x&~32)<='Z')
#define myisalnum(x) (myisalpha(x) || myisdigit(x))
#define myisupper(x) (x>='A' && x<='Z')
#define myislower(x) (x>='a' && x<='z')
#define myislspace(x) (x==' ' || x=='\t')
#define myisspace(x) (x==' ' || x=='\t' || x=='\n' || x=='\r')
