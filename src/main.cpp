#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

void gpio_setup();
#include <libopencm3/stm32/rcc.h>
void gpio_use();

int main () {
    gpio_setup ();

    while (true) {
        gpio_use();

        usart_send_blocking(USART2,'H');
        usart_send_blocking(USART2,'e');
        usart_send_blocking(USART2,'l');
        usart_send_blocking(USART2,'l');
        usart_send_blocking(USART2,'o');
        usart_send_blocking(USART2,'\r');
        usart_send_blocking(USART2,'\n');

        for(volatile uint32_t i = 0; i < 5'000'00;i++);
    }
}

void gpio_setup(){

    //Светодиод
    rcc_periph_clock_enable(RCC_GPIOE);
    gpio_mode_setup(GPIOE,GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO10|GPIO14);

    //УАПП
    rcc_periph_clock_enable(RCC_USART2);

    usart_set_baudrate(USART2,115200); //скорость передачи
    usart_set_databits (USART2,8);
    usart_set_parity(USART2,USART_PARITY_NONE);
    usart_set_stopbits(USART2,USART_STOPBITS_1); //Стоп-БИТ

    usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
    usart_set_mode(USART2,USART_MODE_TX_RX);

    rcc_periph_clock_enable(RCC_GPIOB);
    gpio_mode_setup(GPIOB,GPIO_MODE_AF,GPIO_PUPD_NONE, GPIO3|GPIO4);
    gpio_set_af(GPIOB,GPIO_AF7,GPIO3|GPIO4);

    usart_enable(USART2);
    usart_send_blocking(USART2,'>');
    usart_send_blocking(USART2,'\r');
    usart_send_blocking(USART2,'\n');
}
void gpio_use (){
    gpio_toggle(GPIOE,GPIO10|GPIO14);
}


