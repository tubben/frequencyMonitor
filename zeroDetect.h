/************************************************
  *   ZERO DETECTOR / FREQUENCY CALCULATOR      *
  ***********************************************
  * Author(s):  Tobias Skovgaard                *
  *             Jørgen D. Greve                 *
  * Filename:   zeroDetect.h                    *
  * Date:       07.06.2022                      *
  * Version:    1.0                             *
  ***********************************************
  * This library is used to find whenever a 
  * signal crosses zero and from that calculate
  * the signal frequency.
  */

#include "global.h"

void meanRes();   // meanRes() prototyping

void freqDetect() {
  /***********************************************
     FREQUENCY DETECTION
   ***********************************************
     This function is run every time an interrupt
     happens. Every time the input signal which
     is measured by the ADC is rising and crossing
     "zero" in this case; 1023/2 = 512 it calculates
     the frequency from how long it has taken since
     the last time it crossed zero.
  */
  
  if (adcResult >= 490 && adcResult <= 530 && adcResult > lastAdcResult) {  // Detect if signal is crossing 0 (offset = 1023/2 = 512)

    if (switchZeroCross == 1) {
      //digitalWrite(8, HIGH);            // For frequency measuring via an oscilloscope
      unsigned long microsNow;            // Holds the current microsecond count
      unsigned long period;               // Holds the calculated signal period

      microsNow = micros();               
      period = microsNow - microsLast ;   // Period in micro seconds
      frequency = 1000000.0 / period;     // Frequency calculation
      microsLast = microsNow;

      // Correct frequency if not within specified parameters
      if (frequency > 0 && frequency < 70) {
        lastFrequency = frequency;
      }
      else {
        frequency = lastFrequency;
      }

      switchZeroCross = 0;                // Reset switch

      meanRes();                          // Calculate the mean of the frequency readings

    }

  }

  lastAdcResult = adcResult;              // For detecting if the inputsignal is rising or faling
  
  // Reset switch
  if (adcResult < 490 || adcResult > 530) {
    switchZeroCross = 1;
    //digitalWrite(8, LOW);
  }
}

/* Variables for meanRes() */
float freqSumArr[50];
float freqSum = 0;
int freqSumDone = 0;
int i = 0;

void meanRes() {
  /***********************************************
     MEAN RESULT
   ***********************************************
     This function calculates the mean frequency
     to get a more steady frequency
  */

  freqSumArr[i] = frequency;            // Save current frequency in an array

  for (int j = 0; j < 50; j++) {
    freqSum = freqSum + freqSumArr[j];  // Calculate the sum of the frequency readings
    freqSumDone = 1;
  }

  if (freqSumDone == 1) {
    frequency = freqSum / 50;           // Calculate the mean value
    freqSum = 0;
    freqSumDone = 0;
  }

  i++;
  if (i == 50) {
    i = 0;
  }

}
