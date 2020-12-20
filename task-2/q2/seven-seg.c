#include <mega16.h>
const int TIM0 = 0; 
const int TIM1 = 0x7A11; 
static int active_port = 0;
static unsigned int timer = 0;
unsigned char timer_arr[4] = {0};
char bcd_encode(int port){
    switch (port){
     case 0:    return 0b0111111;
     case 1:    return 0b0000110;
     case 2:    return 0b1011011;
     case 3:    return 0b1001111;
     case 4:    return 0b1100110;
     case 5:    return 0b1101101;
     case 6:    return 0b1111101;
     case 7:    return 0b0000111;
     case 8:    return 0b1111111;
     case 9:    return 0b1101111;
    }
}
void timer0_tick_procedure(){
    if (active_port>=4)
        active_port = 0;             
    PORTC = 0x0F & ~(1<<active_port);
    PORTD = bcd_encode(timer_arr[active_port]);
    active_port++;
}
void timer1_tick_procedure(){
    int i,digit=timer;
    timer++;  
    if (timer>9999)
        timer =0;
    for (i=0;i<4;i++){
        timer_arr[i] = digit%10;
        digit /= 10;
    }
}
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
    TCNT0= 0xFF - TIM0;
    timer0_tick_procedure();
}
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
    TCNT1 = 0xFFFF - TIM1;
    timer1_tick_procedure();  
}
void main(void)
{
    DDRC= 0x0F; 
    DDRD= 0xFF; 
    PORTC=0xFE;
    TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
    TCNT0=0xFF - TIM0;
    TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
    TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (1<<CS12) | (0<<CS11) | (0<<CS10);
    TCNT1 = 0xFFFF - TIMER1_VALUE;
    TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);
    #asm("sei")
    timer = 1;
    while (1);
}
