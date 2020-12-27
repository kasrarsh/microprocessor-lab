#include <mega16.h>
#include <alcd.h>
#include <stdio.h>
#include <delay.h>

#define ICR1 256 * ICR1H + ICR1L;

char mainFreq[16];
long freq;
unsigned int periodTime;
unsigned int firstStart;
unsigned int secondStart;
unsigned int end;

void main(void)
{
    lcd_init(20);
    DDRA =0xFF;
    PORTA = 0x00;

    while(1)
    {
        TCCR1A = 0;
        TCNT1=0;
        TIFR = (1<<ICF1);

        TCCR1B = 0x41;
        while ((TIFR&(1<<ICF1)) == 0);
        firstStart = ICR1;
        TIFR = (1<<ICF1);

        TCCR1B = 0x01;
        while ((TIFR&(1<<ICF1)) == 0);
        secondStart = ICR1;
        TIFR = (1<<ICF1);

        TCCR1B = 0x41;
        while ((TIFR&(1<<ICF1)) == 0);
        end = ICR1;
        TIFR = (1<<ICF1);

        TCCR1B = 0;

		if(firstStart < end)
		{
			periodTime = end - firstStart;

			freq= 8000000UL/periodTime;
            sprintf(mainFreq,"Freq: %d Hz", (int)freq);

            lcd_clear();
			lcd_puts(mainFreq);
		}else lcd_puts("Waiting...");

        delay_ms(100);
	}
}
