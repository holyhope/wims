#ifndef basicstr
#define basicstr
     
/* copy of possibly overlapping strings, to replace strcpy which is not guanranteed in this case
   and indeed produces errors particularly on 64 bits computers */

void ovlstrcpy(char *dest, char *src)
{
  memmove(dest, src, strlen(src)+1);
}

     
#endif /* basicstr */

