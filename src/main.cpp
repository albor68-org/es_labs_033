#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>


constexpr uint16_t BLINK_PERIOD_MS{10};
constexpr uint16_t CK_CNT_Hz{1000};


uint32_t ticks{0}; //Счетчик тиков сиситемного таймера (время в мс)



int main () {

    //Настройка  и запуск системного таймера
    systick_set_frequency(CK_CNT_Hz, rcc_ahb_frequency);
    systick_interrupt_enable();
    systick_counter_enable();

    rcc_periph_clock_enable(RCC_TIM1);

    timer_set_prescaler(TIM1, rcc_get_timer_clk_freq(TIM1)/CK_CNT_Hz - 1);
    timer_set_period(TIM1, BLINK_PERIOD_MS - 1);

    timer_set_oc_value(TIM1, TIM_OC4, BLINK_PERIOD_MS/8);
    timer_set_oc_mode(TIM1, TIM_OC4, TIM_OCM_PWM1);
    timer_enable_oc_output(TIM1, TIM_OC4);
    timer_enable_break_main_output(TIM1);

    timer_enable_counter(TIM1);

    rcc_periph_clock_enable(RCC_GPIOE);
    gpio_mode_setup(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO14);
    gpio_set_af(GPIOE, GPIO_AF2, GPIO14);
    while (true) {
        uint32_t ptime = ticks % 40'000;

        if (ptime < 10'000) timer_set_oc_value(TIM1, TIM_OC4, BLINK_PERIOD_MS/8-1);
        else if (ptime < 20'000) timer_set_oc_value(TIM1, TIM_OC4, BLINK_PERIOD_MS/8*4);
        else if (ptime < 30'000) timer_set_oc_value(TIM1, TIM_OC4, BLINK_PERIOD_MS/8*7);
        else timer_set_oc_value(TIM1, TIM_OC4, BLINK_PERIOD_MS);
    }
}

//Обработчик прерывания системного таймера
void sys_tick_handler (void){
    ticks++;
}
