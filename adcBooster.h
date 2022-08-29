/************************************************
  *        ADC BOOSTER                          *
  ***********************************************
  * Author(s):  Tobias Skovgaard                *
  * Filename:   adcBooster.h                    *
  * Date:       06.06.2022                      *
  * Version:    1.0                             *
  ***********************************************
  * This library is used to set up the ADC to 
  * sample at 10kHz frequency.
  */


/* GENERIC CLOCK SETUP FOR ADC INTERRUPT */
void genClkSetup() {
  /***********************************************
     GENERIC CLOCK SETUP FOR ADC FREQUENCY
   ***********************************************
     Generic clock generator 3 is set up to
     act as clock for the ADC. The generic clock
     has been prescaled with a factor of 0x19 to
     output a frequency of 1.920.000Hz.
  */
  
  REG_GCLK_CLKCTRL  = GCLK_CLKCTRL_CLKEN;       // Enable clock
  REG_GCLK_CLKCTRL |= GCLK_CLKCTRL_GEN_GCLK3;   // Generic clock generator (3)
  REG_GCLK_CLKCTRL |= GCLK_CLKCTRL_ID_ADC;      // Generic Clock Selection ID (GCLK_ADC)

  REG_GCLK_GENCTRL  = GCLK_GENCTRL_GENEN;       // Enable Generic clock generator
  REG_GCLK_GENCTRL |= GCLK_GENCTRL_SRC_DFLL48M; // Source select 48 MHz clock // DFLL48M
  REG_GCLK_GENCTRL |= GCLK_GENCTRL_ID(0x3);     // Generic Clock Generator Selection (generator 3 selected)

  REG_GCLK_GENDIV  = GCLK_GENDIV_ID(0x3);       // Generic clock generator selection (generator 3 selected)
  REG_GCLK_GENDIV |= GCLK_GENDIV_DIV(0x19);     // Division factor (generator clock divided by 25)

  while (REG_GCLK_STATUS != 0);                 // Wait for register synchronization

}


/* ADC SETUP FOR FREQUENCY SAMPLING */
void adcSetup() {
  /***********************************************
     ADC SETUP
   ***********************************************
     The ADC is set up with a resolution of 10 bit
     which takes 6 clock cycles to complete a 
     sample conversion. The ADC prescaler is set
     to 32 and then the interrupt frequency or
     sample rate can be calculated as:
     SampleRate = 1.92MHz / (6 * 32) = 10kHz
     
  */
  
  REG_ADC_REFCTRL = ADC_REFCTRL_REFSEL_INTVCC1;     // Vref set to 1/2 VDDANA

  REG_ADC_INPUTCTRL  = ADC_INPUTCTRL_GAIN_DIV2;     // Gain Factor Selection (1/2x)
  REG_ADC_INPUTCTRL |= ADC_INPUTCTRL_MUXNEG_GND;    // Negative Mux Input Selection (GND)
  REG_ADC_INPUTCTRL |= ADC_INPUTCTRL_MUXPOS_PIN10;  // Positive Mux Input Selection (AIN[10])

  REG_ADC_CTRLB  = ADC_CTRLB_RESSEL_10BIT;          // Conversion Result Resolution (10 bit)
  REG_ADC_CTRLB |= ADC_CTRLB_PRESCALER_DIV32;       // Prescaler Configuration (32)
  REG_ADC_CTRLB |= ADC_CTRLB_FREERUN;               // Free Running Mode (Enabled)

  REG_ADC_EVCTRL = ADC_EVCTRL_STARTEI;              // Start Conversion Event In (Enabled)

  REG_ADC_SAMPCTRL = ADC_SAMPCTRL_SAMPLEN(0);       // Sampling Time Length (0)

  REG_ADC_INTENSET = ADC_INTENSET_RESRDY;           // Result Ready Interrupt Enable

  REG_ADC_CTRLA = ADC_CTRLA_ENABLE;                 // Enable ADC (Enabled)

  while (REG_ADC_STATUS != 0);                      // Wait for register synchronization

  NVIC_EnableIRQ(ADC_IRQn);                         // Enable ADC interrupts
  NVIC_SetPriority(ADC_IRQn, 0);                    // Set priority of the interrupt (priority 0)
}


void verifySetup() {

  /***********************************************
   * REGISTER SETUP VERIFICATION
   ***********************************************
   * This function prints the register values to
   * the terminal on MKR1000 power up for
   * verification of settings change.
   */

  Serial.print("\n---------------------------\n");
  Serial.print("      TIMER SETTINGS \n");
  Serial.print("---------------------------\n");

  Serial.print("GENDIV = ");
  Serial.println(GCLK->GENDIV.reg);

  Serial.print("GENCTRL = ");
  Serial.println(GCLK->GENCTRL.reg);

  Serial.print("CLKCTRL = ");
  Serial.println(GCLK->CLKCTRL.reg);


  Serial.print("\n---------------------------\n");
  Serial.print("       ADC SETTINGS \n");
  Serial.print("---------------------------\n");

  Serial.print("CTRLA = ");
  Serial.println(ADC->CTRLA.reg);

  Serial.print("REFCTRL = ");
  Serial.println(ADC->REFCTRL.reg);

  Serial.print("AVGCTRL = ");
  Serial.println(ADC->AVGCTRL.reg);

  Serial.print("SAMPCTRL = ");
  Serial.println(ADC->SAMPCTRL.reg);

  Serial.print("CTRLB = ");
  Serial.println(ADC->CTRLB.reg);

  Serial.print("WINCTRL = ");
  Serial.println(ADC->WINCTRL.reg);

  Serial.print("SWTRIG = ");
  Serial.println(ADC->SWTRIG.reg);

  Serial.print("INPUTCTRL = ");
  Serial.println(ADC->INPUTCTRL.reg);

  Serial.print("EVCTRL = ");
  Serial.println(ADC->EVCTRL.reg);

  Serial.print("INTENCLR = ");
  Serial.println(ADC->INTENCLR.reg);

  Serial.print("INTENSET = ");
  Serial.println(ADC->INTENSET.reg);

  Serial.print("INTFLAG = ");
  Serial.println(ADC->INTFLAG.reg);

  Serial.print("STATUS = ");
  Serial.println(ADC->STATUS.reg);

  Serial.print("RESULT = ");
  Serial.println(ADC->RESULT.reg);

  Serial.print("WINLT = ");
  Serial.println(ADC->WINLT.reg);

  Serial.print("WINUT = ");
  Serial.println(ADC->WINUT.reg);

  Serial.print("GAINCORR = ");
  Serial.println(ADC->GAINCORR.reg);

  Serial.print("OFFSETCORR = ");
  Serial.println(ADC->OFFSETCORR.reg);

  Serial.print("CALIB = ");
  Serial.println(ADC->CALIB.reg);

  Serial.print("DBGCTRL = ");
  Serial.println(ADC->DBGCTRL.reg);

}
