#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>


constexpr uint16_t BLINK_PERIOD_MS{10};
constexpr uint16_t CK_CNT_Hz{1000};

uint32_t ticks{0}; //Счётчик тиков системного таймера(время в мс)

//constexpr float DOTY_CYCLE{0.4f};


int main () {
    //Настройка и запуск системного таймера
    systick_set_frequency(CK_CNT_Hz, rcc_ahb_frequency);
    systick_interrupt_enable();
    systick_counter_enable();


    //Настройка таймера
    rcc_periph_clock_enable(RCC_TIM1);

    timer_set_prescaler(TIM1, rcc_get_timer_clk_freq(TIM1)/CK_CNT_Hz-1);
    timer_set_period(TIM1, BLINK_PERIOD_MS-1);

    timer_set_oc_value(TIM1, TIM_OC4, BLINK_PERIOD_MS/8);
    timer_set_oc_mode(TIM1, TIM_OC4, TIM_OCM_PWM1);
    timer_enable_oc_output(TIM1, TIM_OC4);
    timer_enable_break_main_output(TIM1);

    timer_enable_counter(TIM1);

    timer_enable_irq(TIM1, TIM_DIER_UIE);
    nvic_enable_irq(NVIC_TIM6_DAC_IRQ);


    rcc_periph_clock_enable(RCC_GPIOE);
    gpio_mode_setup(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO14);
    gpio_set_af(GPIOE, GPIO_AF2, GPIO14);

    while(true){
        uint32_t ptime = ticks % 40000;

        if  (ptime < 10000)timer_set_oc_value(TIM1, TIM_OC4, BLINK_PERIOD_MS/8);
        else if  (ptime < 20000)timer_set_oc_value(TIM1, TIM_OC4, BLINK_PERIOD_MS/2);
        else if  (ptime < 30000)timer_set_oc_value(TIM1, TIM_OC4, BLINK_PERIOD_MS/8*7);
        else timer_set_oc_value(TIM1, TIM_OC4, BLINK_PERIOD_MS);
    }
}

//Обработка прирывания системного таймера
void sys_tick_handler (void){
    ticks++;
}



//    //Светодиод
//    rcc_periph_clock_enable(RCC_GPIOE);
//    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8|GPIO9|GPIO10|GPIO11|GPIO12|GPIO13|GPIO14|GPIO15);

//    // УАПП
//    rcc_periph_clock_enable(RCC_USART3);

//    usart_set_baudrate(USART3, 115200);
//    usart_set_databits(USART3, 8);
//    usart_set_parity(USART3, USART_PARITY_NONE);
//    usart_set_stopbits(USART3, USART_STOPBITS_1);

//    usart_set_flow_control(USART3, USART_FLOWCONTROL_NONE);
//    usart_set_mode(USART3, USART_MODE_TX_RX);

//    // Контакты для УАПП
//    rcc_periph_clock_enable(RCC_GPIOB);
//    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO10|GPIO11);
//    gpio_set_af(GPIOB, GPIO_AF7, GPIO10|GPIO11);
//    usart_enable(USART3);

//    usart_send_blocking(USART3, '>');
//    usart_send_blocking(USART3, '\r');
//    usart_send_blocking(USART3, '\n');

//    while (true) {
//        uint16_t data = usart_recv_blocking(USART3);
//        switch(data) {
//            case 'N':
//                gpio_clear(GPIOE, GPIO8|GPIO9|GPIO10|GPIO11|GPIO12|GPIO13|GPIO14|GPIO15);
//                gpio_set(GPIOE, GPIO9|GPIO10);
//            break;
//            case 'E':
//                gpio_clear(GPIOE, GPIO8|GPIO9|GPIO10|GPIO11|GPIO12|GPIO13|GPIO14|GPIO15);
//                gpio_set(GPIOE, GPIO11|GPIO12);
//            break;
//            case 'S':
//                gpio_clear(GPIOE, GPIO8|GPIO9|GPIO10|GPIO11|GPIO12|GPIO13|GPIO14|GPIO15);
//                gpio_set(GPIOE, GPIO13|GPIO14);
//            break;
//            case 'W':
//                gpio_clear(GPIOE, GPIO8|GPIO9|GPIO10|GPIO11|GPIO12|GPIO13|GPIO14|GPIO15);
//                gpio_set(GPIOE, GPIO8|GPIO15);
//            break;
//        }
//    usart_send_blocking(USART3, data);


//        //for(volatile uint32_t i = 0; i < 15'000; ++i);
//    }


