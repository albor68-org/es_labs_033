#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#include <libopencm3/cm3/nvic.h>


constexpr uint16_t BLINK_PERIOD_MS{1000};
constexpr uint16_t CK_CNT_Hz{1000};
//constexpr float DUTY_CYCLE{0.4f};

int main () {

    //Настройка таймера
    rcc_periph_clock_enable(RCC_TIM6);
    timer_set_prescaler(TIM6, rcc_get_timer_clk_freq(TIM6)/CK_CNT_Hz-1);
    timer_set_period(TIM6, BLINK_PERIOD_MS-1);
    timer_enable_counter(TIM6);


    //timer_enable_irq(TIM6, TIM_DIER_UIE);
    //nvic_enable_irq(NVIC_TIM6_DAC_IRQ);


    //Настройка порта
    rcc_periph_clock_enable(RCC_GPIOE);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);

    while (true)
    {
        if (timer_get_flag(TIM6, TIM_SR_UIF)!=0)
        {
            gpio_toggle(GPIOE, GPIO12);
            timer_clear_flag(TIM6, TIM_SR_UIF);
        }
    }



//    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
//
//    //УАПП
//    rcc_periph_clock_enable(RCC_USART3);
//    usart_set_baudrate(USART3, 115200);
//    usart_set_databits(USART3, 8);
//    usart_set_parity(USART3, USART_PARITY_NONE);
//    usart_set_stopbits(USART3, USART_STOPBITS_1);
//
//    usart_set_flow_control (USART3, USART_FLOWCONTROL_NONE);
//    usart_set_mode(USART3, USART_MODE_TX_RX);
//
//    rcc_periph_clock_enable(RCC_GPIOB);
//    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO10 | GPIO11);
//    gpio_set_af(GPIOB, GPIO_AF7, GPIO10 | GPIO11);
//
//    usart_enable(USART3);
//
//    usart_send_blocking(USART3, '>');
//    usart_send_blocking(USART3, '\r');
//    usart_send_blocking(USART3, '\n');
//
//    while (true)
//    {
//        //Алгоритм приёма и распознавания символов
//        uint16_t data = usart_recv_blocking(USART3);
//        switch(data)
//        {
//            case 'N':
//                usart_send_blocking(USART3, data);
//                gpio_clear(GPIOE, GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
//                gpio_set(GPIOE, GPIO9);
//            break;
//            case 'E':
//                usart_send_blocking(USART3, data);
//                gpio_clear(GPIOE, GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
//                gpio_set(GPIOE, GPIO11);
//            break;
//            case 'S':
//                usart_send_blocking(USART3, data);
//                gpio_clear(GPIOE, GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
//                gpio_set(GPIOE, GPIO13);
//            break;
//            case 'W':
//                usart_send_blocking(USART3, data);
//                gpio_clear(GPIOE, GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
//                gpio_set(GPIOE, GPIO15);
//           break;
//        }
//
//        //usart_send_blocking(USART3, data);
//        for (volatile uint32_t i=0; i<250'000; ++i);
//
//    }
}
