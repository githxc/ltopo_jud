#ifndef _CHA_EXT_H
#define _CHA_EXT_H

#ifdef  __cplusplus
extern "C" {
#endif


extern float cha_dval(long int *s,long int*f);
extern float cha_uord(long int *s,long int*f);
extern float cha_jumt(long int *s,long int*f);
extern void cha_rel(long int *s,long int*f,FILE *fp);
extern float cha_lost(long int *s,long int*f,FILE *fp);
extern float bubble_sort(int a[8]); 
extern void output(long int * s,long int * f,FILE * fp);

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "math.h"


#endif