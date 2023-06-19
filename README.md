# msp430-lm35-RGBled
 RGB Led Thermometer with lm35 temperature sensor.

 The MSP430G2553 microcontroller was used in the project. The LM35 temperature sensor produces an output voltage of 10mV per degree.
 Using the necessary mathematical calculations under a 3.3V reference voltage with the MSP430, a 10-bit ADC measurement is performed.
 The measurement result is then converted to degrees using mathematical operations for temperature measurement. 
 Subsequently, with the ISR (Interrupt Service Routine), the RGB LED's color adjustments are made based on this temperature value. 
 In order to ensure clear visibility of changes in the RGB LED, the color transitions have been made sharp. 
 Please note that you cannot debug the color transition without disabling the GIE (General Interrupt Enable) flag.
 PWM is used for the color table. RGB LED adjustments are made by maintaining a variable for each leg of the RGB LED.
