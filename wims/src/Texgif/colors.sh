#! /bin/sh

cat <<@ >colors.c

	/* This file is automatically generated! Do not edit it. */
#include "texgif.h"
struct colors colors[]={

@

sort -k 1,1 <colors | awk 'NF==2 {print "	{\""$1"\",     	"$2"},"}' >>colors.c

cat <<@ >>colors.c
};

int colorno=(sizeof(colors)/sizeof(colors[0]));

@

