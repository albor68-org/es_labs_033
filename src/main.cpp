#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/rcc.h>



void gpio_setup();
int main () {
    gpio_setup ();

    while (true) {

        uint16_t date = usart_recv_blocking(USART3);
        gpio_clear(GPIOE, GPIO9|GPIO11|GPIO13|GPIO15);
        switch((date == 'N')?1:(date =='S')?2:(date == 'E')?3:(date == 'W')?4 : 5){

        case 1:
            usart_send_blocking(USART3,date);
            gpio_clear(GPIOE, GPIO11|GPIO13|GPIO15);
            gpio_set(GPIOE, GPIO9);
            break;
        case 2:
            usart_send_blocking(USART3,date);
            gpio_clear(GPIOE, GPIO9|GPIO13|GPIO15);
            gpio_set(GPIOE, GPIO11);
            break;
        case 3:
            usart_send_blocking(USART3,date);
            gpio_clear(GPIOE, GPIO9|GPIO11|GPIO15);
            gpio_set(GPIOE, GPIO13);
            break;
        case 4:
            usart_send_blocking(USART3,date);
            gpio_clear(GPIOE, GPIO9|GPIO11|GPIO13);
            gpio_set(GPIOE, GPIO15);
            break;
        case 5:
            gpio_clear(GPIOE, GPIO9|GPIO11|GPIO13|GPIO15);
            break;

        }
    }
}

void gpio_setup(){

    //Светодиод
    rcc_periph_clock_enable(RCC_GPIOE);
    gpio_mode_setup(GPIOE,GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO9|GPIO11|GPIO13|GPIO15);

    //УАПП
    rcc_periph_clock_enable(RCC_USART3);

    usart_set_baudrate(USART3,115200); //скорость передачи
    usart_set_databits (USART3,8);
    usart_set_parity(USART3,USART_PARITY_NONE);
    usart_set_stopbits(USART3,USART_STOPBITS_1); //Стоп-БИТ

    usart_set_flow_control(USART3, USART_FLOWCONTROL_NONE);
    usart_set_mode(USART3,USART_MODE_TX_RX);

    //Контакты для УАПП
    rcc_periph_clock_enable(RCC_GPIOB);
    gpio_mode_setup(GPIOB,GPIO_MODE_AF,GPIO_PUPD_NONE, GPIO10|GPIO11);
    gpio_set_af(GPIOB,GPIO_AF7,GPIO10|GPIO11);

    usart_enable(USART3);
    usart_send_blocking(USART3,'>');
    usart_send_blocking(USART3,'\r');
    usart_send_blocking(USART3,'\n');
}

