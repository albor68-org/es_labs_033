#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>

constexpr uint16_t BLINK_PERIOD_MS{1000};
constexpr uint16_t CK_CNT_Hz{1000};

int main () {

    //Настройка таймера
    rcc_periph_clock_enable(RCC_TIM6);

    timer_set_prescaler(TIM6, rcc_get_timer_clk_freq(TIM6)/CK_CNT_Hz - 1);
    timer_set_period(TIM6, BLINK_PERIOD_MS - 1);
    timer_enable_counter(TIM6);


    rcc_periph_clock_enable(RCC_GPIOE);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO9);

    while (true) {
        if (timer_get_flag(TIM6, TIM_SR_UIF) !=0) {
            gpio_toggle(GPIOE, GPIO9);
            timer_clear_flag(TIM6, TIM_SR_UIF);
        }
    }
}
