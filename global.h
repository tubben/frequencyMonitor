/************************************************
  *        GLOBAL VARIABLES                     *
  ***********************************************
  * Author(s):  Jørgen D. Greve                 *
  * Filename:   global.h                        *
  * Date:       06.06.2022                      *
  * Version:    1.0                             *
  ***********************************************
  * Library for global variables.
  */

#ifndef GLOBAL_VARIABLES_HEADER
#define GLOBAL_VARIABLES_HEADER

// Variables for zeroDetect.h
extern volatile int adcResult;
extern int lastAdcResult;
extern int lastFrequency;
extern volatile unsigned long microsLast;
extern int adcIntrrFlag;
extern int switchZeroCross;
extern float frequency;
extern int cnt;

#endif