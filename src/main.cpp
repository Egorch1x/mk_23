#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>

constexpr uint16_t PRESCALER(20);
constexpr uint16_t PERIOD_US(32000); // Для приставки "микро" используется
                                     // греческая буква, отсутствующая в
                                     // английском алфавите. На замену - u.

void timer_setup () 
{
    rcc_periph_clock_enable(RCC_TIM6);

    timer_set_prescaler(TIM6, PRESCALER - 1);
    timer_set_period(TIM6, PERIOD_US - 1);

    timer_enable_irq(TIM6, TIM_DIER_UIE);
    nvic_enable_irq(NVIC_TIM6_DAC_IRQ);

    timer_enable_counter(TIM6);
}


void gpio_setup () 
{
    rcc_periph_clock_enable(RCC_GPIOE);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO9 | GPIO11);
}


int main () 
{
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);
    timer_setup (); 
    gpio_setup ();
     
    while (true) 
    {
    ;
    }
}

void tim6_dac_isr ()
{
    timer_clear_flag(TIM6, TIM_SR_UIF);
    gpio_toggle(GPIOE, GPIO9);
}