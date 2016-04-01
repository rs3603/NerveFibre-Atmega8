#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include<util/delay.h>
#include"lcd.h"
#include"lcd.c"
#include"adc.h"



char buffer[5],buffer1[5],buffer3[5];


int ReadADC(uint8_t ch)
{
   //Select ADC Channel ch must be 0-7
   ch=ch&0b00000111;
   ADMUX = (ADMUX & 0xF8) | ch;

   //Start Single conversion
   ADCSRA |= (1<<ADSC);

   //Wait for conversion to complete
   while(!(ADCSRA&(1<<ADIF)));

   //Clear ADIF by writing one to it
   //Note you may be wondering why we have write one to clear it
   //This is standard way of clearing bits in io as said in datasheets.
   //The code writes '1' but it result in setting bit to '0' !!!

   ADCSRA|=(1<<ADIF);

   return(ADC);
}

void initADC()
{
ADMUX=(1<<REFS0);  // For Aref=AVcc;
ADCSRA=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1); //Prescalar div factor =64
}




void main()
{
                    // turn on interrupts

lcd_init(LCD_DISP_ON);
lcd_clrscr();
initADC();

int x,y;
DDRB = 0xFF;
lcd_gotoxy(0,0);
lcd_puts("RED:");
lcd_gotoxy(8,0);
lcd_puts("BLU:");
lcd_gotoxy(0,1);
lcd_puts("WHI:");
lcd_gotoxy(8,1);
lcd_puts("YEL:");

while(1)
{
lcd_gotoxy(3,0);
x=ReadADC(0);
y=(300 - x)/3.0;
sprintf(buffer,"%4d",y);
lcd_puts(buffer);

lcd_gotoxy(11,0);
x=ReadADC(1);
y=(300 - x)/3.0;
sprintf(buffer,"%4d",y);
lcd_puts(buffer);

lcd_gotoxy(3,1);
x=ReadADC(2);
y=(300 - x)/3.0;
sprintf(buffer,"%4d",y);
lcd_puts(buffer);

lcd_gotoxy(11,1);
x=ReadADC(3);
y=(300 - x)/3.0;
sprintf(buffer,"%4d",y);
lcd_puts(buffer);

if(x>=0&&x<60)
PORTB=0b00000001;
if(x>=60&&x<70)
PORTB=0b00000011;
if(x>=70&&x<80)
PORTB=0b00000111;
if(x>=80&&x<90)
PORTB=0b00001111;
if(x>=90&&x<100)
PORTB=0b00011111;
if(x>=100)
PORTB=0b00000000;

	


//wait(.1);

}
 
}



