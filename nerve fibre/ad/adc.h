
/***********************************************************************

Headerfile for make ADC convertion

*COPYRIGHT(c): Technophilia embedded systems.
*AUTHOR: Technophilia
*Target system: AVR devlopment board s/n-118010
*Manufacturer: Technophilia 
*Microcontroller: ATmega-8
*Clock: 12MHz
*COMPILER: WinAVR
*last modified 04/10/2011

************************************************************************/

#ifndef _ADC_H_
#define _ADC_H_						//This is the header for AVR Microcontroller.

unsigned int adcdata,adcdata1;

 void adc_init()
 {
  ADCSRA=0X86;						//ADC enable, ADC interrupt enable, set prescaller to 64
  		
 }
 unsigned char getdata(unsigned char chno)	
  {
    ADMUX=0X60;						//right align the ADC result
    ADMUX|=chno;					//select the ADC channel
    ADCSRA|=0X40;					//start ADC convertion
   	while((ADCSRA&0x40)==0x40);    //give some time delay to complit the aDC convertion
	return ADCH;
  }


#endif 