#ifndef _PUL_DATA_H
#define _PUL_DATA_H

#ifdef  __cplusplus
extern "C" {
#endif

//#define JUMP_FL 1
#define S_PUL_LENGTH 6
#define UP_THRESHOLD_VALUE 1000
#define UPE_THRESHOLD_VALUE -1000
#define	DOWN_THRESHOLD_VALUE -1000
#define DOWNE_THRESHOLD_VALUE 1000
#define BEGIN_WINDOW 1
#define END_WINDOW 8

#define LTOOL_STR_PULS_UP "##PULSE-UP#### "
#define LTOOL_STR_PULS_DOWN "##PULSE-DOWN## "
#define LTOOL_STR_STAGE_UP "##STAGE-UP#### "
#define LTOOL_STR_STAGE_DOWN "##STAGE-DOWN## "
#define LTOOL_STR_STILL "##STAGE-STAY## "
#define LTOOL_STR_LOSS "##DATA-LOSS### "
#define LTOOL_STR_ERROR "##MISS##"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cha_ext.h"



extern int pul_detect(long int *data);
extern int pul_judg(int pul_num);
extern int pul_out_m(int pulse,char* addr, long int s[8],FILE *fpo);
extern int pul_out_d(int a,int pulse,int d_pulse,char* addr, char* num2,long int s[8], FILE *fpo);

#endif
