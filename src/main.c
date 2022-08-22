#include "stm32f1xx.h"
#include <stdint.h>

#define LEDPORT (GPIOB)
#define LED1 (2)
#define ENABLE_GPIO_CLOCK (RCC->APB2ENR |= RCC_APB2ENR_IOPBEN)
#define _MODER    CRL
#define GPIOMODER (GPIO_CRL_MODE2_0)

void ms_delay(int ms)
{
   while (ms-- > 0) {
      volatile int x=500;
      while (x-- > 0)
         __asm("nop");
   }
}

//Alternates blue and green LEDs quickly
int main(void)
{
    ENABLE_GPIO_CLOCK;              // enable the clock to GPIO
    // LEDPORT->_MODER |= GPIOMODER;   // set pins to be general purpose output
    LEDPORT->CRL |= GPIO_CRL_MODE2_1;
    LEDPORT->CRL &= ~(GPIO_CRL_MODE2_0);
    LEDPORT->CRL &= ~(GPIO_CRL_CNF2_1 | GPIO_CRL_CNF2_0);

    for (;;) {
    ms_delay(500);
    LEDPORT->ODR ^= (1<<LED1);  // toggle diodes
    }

    return 0;
}
