#include "io430.h"
#include "in430.h"

#define BLED BIT5
#define GLED BIT4
#define RLED BIT3

unsigned int ADC_Result;

unsigned int Temperature;
unsigned char tR=0,tG=0,tB=0;



void adc_init(void)
{
   ADC10CTL0 &= ~ENC;
   ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE ;
   ADC10CTL1 = INCH_0 + ADC10SSEL_3 + ADC10DIV_3;
  
}

void RGB_LED(unsigned char tR,unsigned char tG, unsigned char tB){
unsigned char a;
unsigned int i;
 
for(a=0;a<25;a++){
for(i=1;i<=255;i++){  // 255 adimda 3 ayri PWM isaret uret
	if(i>tR)P2OUT|=RLED;
	if(i<=tR)P2OUT&= ~RLED;
 
	if(i>tG)P2OUT|=GLED;
	if(i<=tG)P2OUT&= ~GLED;
 
	if(i>tB)P2OUT|=BLED;
	if(i<=tB)P2OUT&= ~BLED; 
 
	__delay_cycles(1);
}}}

void colour_table(void){
if(Temperature<20){tR=0; tG=0;   tB=255;}                      // Blue
if(Temperature>=20 && Temperature<25){tR=0;   tG=255;   tB=0;} // Green
if(Temperature>=25 && Temperature<30){tR=255;   tG=0; tB=0;}   // Red
if(Temperature>30){tR=255; tG=255;   tB=255;}                  // All 3 colours
} 


int main( void )
{


 WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer
 
   DCOCTL=CALDCO_1MHZ;
   BCSCTL1=CALBC1_1MHZ;
 
   P1SEL = 0x00;
   P1OUT = 0x00;
   P1DIR = 0x00;
   P2DIR = BIT3|BIT4|BIT5;
   P2OUT = 0x00;
 
 
   adc_init();
   ADC10CTL0 |= ADC10SC + ENC;
  
  
  
   _BIS_SR(GIE);
   
   
   for(;;);
   
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC_ISR(void)
{
  
   ADC_Result = ADC10MEM;
  Temperature = (ADC_Result * 0.33); // MSP430 referans gerilimi 3.3 olarak ayarlandi bu yüzden (3.3/1024)/0.01mV islemini yaptigimizda olusan sonuç budur.

   ADC10CTL0_bit.ADC10IFG = 0;
   ADC10CTL0 |= ADC10SC + ENC;
    _BIC_SR(GIE); // GIE bayragi kapatiliyor

   colour_table();
   RGB_LED( tR, tG, tB);
  
   }