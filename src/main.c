#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <stdint.h>

#define RCCLEDPORT (RCC_GPIOB)
#define LEDPORT (GPIOB)
#define LEDPIN (GPIO2)
#define GPIO_MODE_OUTPUT GPIO_MODE_OUTPUT_2_MHZ
#define GPIO_PUPD_NONE GPIO_CNF_OUTPUT_PUSHPULL

static void gpio_setup(void) {
  /* Enable GPIO clock. */
  /* Using API functions: */
  rcc_periph_clock_enable(RCCLEDPORT);
  /* Set pin to 'output push-pull'. */
  /* Using API functions: */
  gpio_set_mode(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
}

int main(void) {
  int i;
  gpio_setup();
  /* Blink the LED on the board. */
  while (1) {
    /* Using API function gpio_toggle(): */
    gpio_toggle(LEDPORT, LEDPIN);   /* LED on/off */
    for (i = 0; i < 1000000; i++) { /* Wait a bit. */
      __asm__("nop");
    }
  }

  return 0;
}