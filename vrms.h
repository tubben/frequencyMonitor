/************************************************
  *        VRMS CALCULATOR                      *
  ***********************************************
  * Author(s):  Tobias Skovgaard                *
  * Filename:   vrms.h                          *
  * Date:       10.06.2022                      *
  * Version:    1.0                             *
  ***********************************************
  * This library is used calculate the root mean
  * square voltage of the input signal.
  * 
  */
  
float Vholder = 0.00;
float Vrms = 0.00;
float hold;

int adcResArr[200];
int j = 0;
float offset = 1.65;
float vpp = 3.30;


void calcVRMS(){
  
  Vholder = 0.00;  
  int n = 0;
  
  adcResArr[j] = adcResult;
  j++;
  
  
  for (int i = 0; i < 200; i++){
   hold = adcResArr[i];
   Vholder = Vholder + sq(((hold/1023)*vpp)-offset);
   n = i;
   //Serial.print("hold = ");
   //Serial.println(Vholder);
  }
 
  Vrms = sqrt(Vholder/n);  
  
  //Serial.print("Vrms = ");
  //Serial.println(Vrms); 
 
 if(j > 200){
   j = 0;
 }
  
}
