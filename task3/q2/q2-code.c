

#include <mega16.h>
#include <alcd.h>

int chars;
int i;
int overFlow;
int j;


interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
      ++ overFlow;

      if(overFlow ==1000){

          lcd_putchar(chars);
          chars +=1;
          i=i+1;

            if(i==20){
            i=0;
            j=1;
             }

            lcd_gotoxy(i,j);
            overFlow=0;

            if(chars == 0x5b){
              TCCR0=0x00;
              TIMSK=0x00;
            }

       }

      TCNT0=0x00;

}


void main(void)
{

    DDRA=0x00;
    PORTA=0x00;
    i=0;
    j=0;
    overFlow=0;
    chars=0x41;
    TCCR0=0x01;
    TCNT0=0x00;
    OCR0=0x00;
    TIMSK=0x01;
    lcd_init(20);
    #asm("sei")

while (1)
      {


      }


}
