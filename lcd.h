/************************************************
  *        LCD DISPLAY                          *
  ***********************************************
  * Author(s):  Tobias Skovgaard                *
  * Filename:   lcd.h                           *
  * Date:       13.06.2022                      *
  * Version:    1.0                             *
  ***********************************************
  * This library is used to write 
  */

#include <LiquidCrystal.h>    // LCD library

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);


void updateLCD() {

  lcd.setCursor(0, 0); // Lcd first row is 0
  lcd.print("Freq:");
  lcd.setCursor(6, 0);
  lcd.print(frequency,3);
  lcd.setCursor(13, 0);
  lcd.print("Hz");

  lcd.setCursor(0, 1); // Lcd first row is 0
  lcd.print("Vrms:");
  lcd.setCursor(7, 1);
  lcd.print(Vrms,3);
  lcd.setCursor(13, 1);
  lcd.print("V");

}
