#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
int main () {
    rcc_periph_clock_enable(RCC_GPIOE);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO9 | GPIO11 | GPIO13 | GPIO15);
    rcc_periph_clock_enable(RCC_USART2);
    usart_set_baudrate(USART2,115200);
    usart_set_databits(USART2, USART_PARITY_NONE);
    usart_set_stopbits(USART2, USART_STOPBITS_1);

    usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
    usart_set_mode(USART2, USART_MODE_TX_RX);

    rcc_periph_clock_enable(RCC_GPIOB);
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO3);
    gpio_set_af(GPIOB, GPIO_AF7, GPIO3 | GPIO4);

    usart_enable(USART2);

    usart_send_blocking(USART2, '>');
    usart_send_blocking(USART2, '\r');
    usart_send_blocking(USART2, '\n');
while (true) {
  gpio_toggle(GPIOE, GPIO9 | GPIO11 /*| GPIO13 | GPIO15*/);
  usart_send_blocking(USART2, 'H');
  usart_send_blocking(USART2, 'e');
  usart_send_blocking(USART2, 'l');
  usart_send_blocking(USART2, 'l');
  usart_send_blocking(USART2, '0');
  usart_send_blocking(USART2, '!');
  usart_send_blocking(USART2, '\r');
  usart_send_blocking(USART2, '\n');
  for(volatile uint32_t i=0; i<5'000'00; ++i);
  }
}
