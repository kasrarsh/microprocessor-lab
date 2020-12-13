#include <mega16.h>
#include <delay.h>

unsigned int count = 8;
unsigned int num = 0;
unsigned int i = 0;

void main (void){
    DDRB=0xff;
    DDRA=0x00;

    while(1){
        if(PINA.0==0){
             delay_ms(100);
             for(i = 0; i < count * 2; i = i + 1){
                 num = i % (count);
                 if(i < 8) PORTB = 1 << num;
                 if(i >= 8) PORTB = 1 << count - (num + 2);
                 delay_ms(1000);
             }
        }
    }
