#include <avr/io.h>
#include <timer.h>
#include <uart.h>
#include <gpio.h>
#include <avr/interrupt.h>


int main(void)
{

uart_init(UART_BAUD_SELECT(115200, F_CPU));



TIM2_OVF_16MS
TIM2_OVF_ENABLE

sei();

GPIO_mode_input_pullup(&DDRD,3); // Levá
GPIO_mode_input_pullup(&DDRD,4); // Pravá
GPIO_mode_input_pullup(&DDRD,5); // Nahoru
GPIO_mode_input_pullup(&DDRD,6); // Dolů  



    while (1)
{
        
}




}  

ISR(TIMER2_OVF_vect)
{

  if (GPIO_read(&PIND,3) == 0)
            uart_puts("L");
        else if (GPIO_read(&PIND,4) == 0)
            uart_puts("P");
        else if (GPIO_read(&PIND,5) == 0)
            uart_puts("N");
        else if (GPIO_read(&PIND,6) == 0)
            uart_puts("D");
        else 
            uart_puts("."); 

}
