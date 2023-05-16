#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>


constexpr uint16_t BLINK_PERIOD_MS{1000};
constexpr uint16_t CK_CNT_Hz{1000};

int main () {

    //Настройка таймера
    rcc_periph_clock_enable(RCC_TIM1);

    timer_set_prescaler(TIM1,rcc_get_timer_clk_freq(TIM1) / CK_CNT_Hz - 1);

    timer_set_period(TIM1, BLINK_PERIOD_MS - 1);

    timer_set_oc_value(TIM1,TIM_OC4, BLINK_PERIOD_MS/2);
    timer_set_oc_mode (TIM1, TIM_OC4, TIM_OCM_TOGGLE);
    timer_enable_oc_output(TIM1,TIM_OC4);
    timer_enable_break_main_output(TIM1);


    timer_enable_counter(TIM1);

    rcc_periph_clock_enable(RCC_GPIOE);

    gpio_mode_setup(GPIOE,GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO14);
    gpio_set_af(GPIOE,GPIO_AF2,GPIO14);

    while (true) {

//        if(timer_get_flag(TIM6,TIM_SR_UIF != 0)) {

//            gpio_toggle(GPIOE, GPIO9);

//            timer_clear_flag(TIM6,TIM_SR_UIF);
//        }

}
    }


