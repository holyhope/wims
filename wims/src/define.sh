#! /bin/sh
grep "#define MAX_SHEETS" wimsdef.h | awk -F'#define MAX_SHEETS' ' {print "MAX_SHEETS="$2 ; exit}'
grep "#define MAX_EXOS" wimsdef.h | awk -F'#define MAX_EXOS' ' {print "MAX_EXOS="$2 ; exit}'
grep "#define MAX_REQUIRE" wimsdef.h | awk -F'#define MAX_REQUIRE' ' {print "MAX_REQUIRE="$2 ; exit}'
grep "#define MAX_EXAMS" wimsdef.h | awk -F'#define MAX_EXAMS' ' {print "MAX_EXAMS="$2 ; exit}'
