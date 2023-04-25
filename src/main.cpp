#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

int main () {

    //Светодиод
    rcc_periph_clock_enable(RCC_GPIOE);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);

    //УАПП
    rcc_periph_clock_enable(RCC_USART3);
    usart_set_baudrate(USART3, 115200);
    usart_set_databits(USART3, 8);
    usart_set_parity(USART3, USART_PARITY_NONE);
    usart_set_stopbits(USART3, USART_STOPBITS_1);

    usart_set_flow_control (USART3, USART_FLOWCONTROL_NONE);
    usart_set_mode(USART3, USART_MODE_TX_RX);

    rcc_periph_clock_enable(RCC_GPIOB);
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO10 | GPIO11);
    gpio_set_af(GPIOB, GPIO_AF7, GPIO10 | GPIO11);

    usart_enable(USART3);

    usart_send_blocking(USART3, '>');
    usart_send_blocking(USART3, '\r');
    usart_send_blocking(USART3, '\n');

    while (true)
    {
        //Алгоритм приёма и распознавания символов
        uint16_t data = usart_recv_blocking(USART3);
        switch(data)
        {
            case 'N':
                usart_send_blocking(USART3, data);
                gpio_clear(GPIOE, GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
                gpio_set(GPIOE, GPIO9);
            break;
            case 'E':
                usart_send_blocking(USART3, data);
                gpio_clear(GPIOE, GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
                gpio_set(GPIOE, GPIO11);
            break;
            case 'S':
                usart_send_blocking(USART3, data);
                gpio_clear(GPIOE, GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
                gpio_set(GPIOE, GPIO13);
            break;
            case 'W':
                usart_send_blocking(USART3, data);
                gpio_clear(GPIOE, GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
                gpio_set(GPIOE, GPIO15);
            break;
        }

        //usart_send_blocking(USART3, data);
//        for (volatile uint32_t i=0; i<250'000; ++i);

    }
}
