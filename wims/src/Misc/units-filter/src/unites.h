#ifndef UNITES_H
#define UNITES_H

#include <gmp.h>
#include <gmpxx.h>

typedef enum {
  TUh, TUmin,
  TUm, TUg, TUs, TUA, TUK, TUmol, TUcd, TUHz, TUN, TUPa, TUJ, TUW, 
  TUC, TUV, TUohm, TUS, TUF, TUT, TUWb, TUH, TUlm, TUlx, TUBq, 
  TUGy, TUSv, TUrad, TUsr, TUnull, TUda, TUma, TUsa, TUangs, TUbarn, 
  TUare, TUl, TUt, TUbar, TUeV, TUuam,
  TU_LAST /* doit rester en dernier */
} uniteSI;

typedef enum {
 BUM,BUK,BUS,BUA,BUKel,BUmol,BUcd,
 BU_LAST /* doit rester en dernier */
} baseSI;

typedef struct{
  char sym[8];
  char nom[12]; 
  double multiplicateur;
  int base[BU_LAST];
} unite_data;

extern mpq_class val_real;

void atodecimal(char* s, mpq_class & r);

#endif
