/************************************************
  *        GLOBAL VARIABLES                     *
  ***********************************************
  * Author(s):  Jørgen D. Greve                 *
  * Filename:   global.c                        *
  * Date:       06.06.2022                      *
  * Version:    1.0                             *
  ***********************************************
  * Library for global variables.
  */

#include "global.h"

// Variable initialization
volatile int adcResult = 0;
int lastAdcResult = 0;
int lastFrequency = 0;
volatile unsigned long microsLast;
int adcIntrrFlag = 0;
int switchZeroCross = 0;
float frequency = 0.000;
int cnt = 0;