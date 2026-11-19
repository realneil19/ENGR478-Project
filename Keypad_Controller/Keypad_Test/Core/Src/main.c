#include "stm32l4xx.h"
#include "keypad.h"

/* Buttons 1-4: A2, A1, A4, A3 */
static GPIO_TypeDef * const button_ports[4] = {
    GPIOA, GPIOA, GPIOC, GPIOB
};
static const uint8_t button_pins[4] = {4, 1, 1, 0};

/* Debugger variables. */
volatile uint32_t control_button = 0;
volatile uint32_t last_control_button = 0;
volatile uint32_t control_press_count = 0;

/* LED represents the timed unlock output. */
volatile uint32_t lock_active = 0;
volatile uint32_t unlock_remaining_ms = 0;

static void control_buttons_init(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN
                 | RCC_AHB2ENR_GPIOBEN
                 | RCC_AHB2ENR_GPIOCEN;
    (void)RCC->AHB2ENR;

    /* Common connector pin 1: A0 / PA0, driven LOW. */
    GPIOA->BSRR = (1U << 16);
    GPIOA->OTYPER |= (1U << 0);
    GPIOA->PUPDR &= ~(3U << 0);
    GPIOA->MODER &= ~(3U << 0);
    GPIOA->MODER |=  (1U << 0);

    /* Button inputs with pull-ups. */
    for (unsigned int i = 0; i < 4; i++)
    {
        GPIO_TypeDef *port = button_ports[i];
        unsigned int pin = button_pins[i];

        port->MODER &= ~(3U << (2U * pin));
        port->PUPDR &= ~(3U << (2U * pin));
        port->PUPDR |=  (1U << (2U * pin));
    }
}

/* Return button 1-4, or 0 when none is pressed. */
static uint32_t control_buttons_scan(void)
{
    for (unsigned int i = 0; i < 4; i++)
    {
        if ((button_ports[i]->IDR &
             (1U << button_pins[i])) == 0U)
        {
            return i + 1U;
        }
    }

    return 0;
}

static void control_buttons_update(void)
{
    static uint32_t candidate = 0;
    static uint32_t stable_button = 0;
    static unsigned int stable_count = 0;
    static unsigned int armed = 1;

    uint32_t reading = control_buttons_scan();

    /* Require 20 matching readings. */
    if (reading != candidate)
    {
        candidate = reading;
        stable_count = 1;
    }
    else if (stable_count < 20U)
    {
        stable_count++;
    }

    if ((stable_count == 20U) &&
        (candidate != stable_button))
    {
        stable_button = candidate;
        control_button = stable_button;

        /* Accept one press, then require release. */
        if (stable_button == 0U)
        {
            armed = 1;
        }
        else if (armed != 0U)
        {
            last_control_button = stable_button;
            control_press_count++;
            armed = 0;
        }
    }
}

/* D10 / PB6: external LED output. */
static void lock_led_init(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    (void)RCC->AHB2ENR;

    GPIOB->BSRR = (1U << 22);       /* Start OFF */
    GPIOB->MODER &= ~(3U << 12);
    GPIOB->MODER |=  (1U << 12);    /* Output */
    GPIOB->OTYPER &= ~(1U << 6);    /* Push-pull */
    GPIOB->PUPDR &= ~(3U << 12);
    GPIOB->OSPEEDR &= ~(3U << 12);
}

int main(void)
{
    uint32_t previous_press_count = 0;

    keypad_init();
    control_buttons_init();
    lock_led_init();

    /* SysTick: nominal 1 ms polling. */
    SystemCoreClockUpdate();
    SysTick->CTRL = 0;
    SysTick->LOAD = (SystemCoreClock / 1000U) - 1U;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk
                  | SysTick_CTRL_ENABLE_Msk;

    for (;;)
    {
        if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0U)
        {
            keypad_update();
            control_buttons_update();

            /* End the unlock period after the countdown. */
            if (unlock_remaining_ms > 0U)
            {
                unlock_remaining_ms--;

                if (unlock_remaining_ms == 0U)
                {
                    lock_active = 0;
                }
            }

            /* Handle each newly accepted control-button press. */
            if (control_press_count != previous_press_count)
            {
                previous_press_count = control_press_count;

                /* Button 4 starts an unlock when inactive. */
                if ((last_control_button == 4U) &&
                    (lock_active == 0U))
                {
                    lock_active = 1;
                    unlock_remaining_ms = 3000U;
                }
            }

            /* External LED follows the unlock flag. */
            if (lock_active != 0U)
            {
                GPIOB->BSRR = (1U << 6);
            }
            else
            {
                GPIOB->BSRR = (1U << 22);
            }
        }
    }
}
