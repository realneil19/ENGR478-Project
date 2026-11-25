#include "stm32l4xx.h"
#include "keypad.h"

#define FRAME_SIZE 13U

/* Small keypad buttons 1–4: A2, A1, A4, A3. */
static GPIO_TypeDef *const button_ports[4] = {
    GPIOA, GPIOA, GPIOC, GPIOB
};

static const uint8_t button_pins[4] = {4, 1, 1, 0};

volatile uint32_t control_button = 0;
volatile uint32_t last_control_button = 0;
volatile uint32_t control_press_count = 0;

volatile uint32_t lock_active = 0;
volatile uint32_t unlock_remaining_ms = 0;
volatile uint32_t link_frames_sent = 0;

static char tx_frame[FRAME_SIZE];
static uint32_t tx_index = FRAME_SIZE;

static char hex_digit(uint8_t n)
{
    return "0123456789ABCDEF"[n & 15U];
}

static uint8_t frame_checksum(const char *frame)
{
    uint8_t sum = 0;

    for (uint32_t i = 1; i < 10U; i++)
    {
        sum ^= (uint8_t)frame[i];
    }

    return sum;
}

static void control_buttons_init(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN
                 | RCC_AHB2ENR_GPIOBEN
                 | RCC_AHB2ENR_GPIOCEN;
    (void)RCC->AHB2ENR;

    /* A0 / PA0: keypad common held LOW. */
    GPIOA->BSRR = (1U << 16);
    GPIOA->OTYPER |= (1U << 0);
    GPIOA->PUPDR &= ~(3U << 0);
    GPIOA->MODER &= ~(3U << 0);
    GPIOA->MODER |= (1U << 0);

    for (uint32_t i = 0; i < 4U; i++)
    {
        GPIO_TypeDef *port = button_ports[i];
        uint32_t pin = button_pins[i];

        port->MODER &= ~(3U << (2U * pin));
        port->PUPDR &= ~(3U << (2U * pin));
        port->PUPDR |= (1U << (2U * pin));
    }
}

static uint32_t control_buttons_scan(void)
{
    for (uint32_t i = 0; i < 4U; i++)
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
    static uint32_t stable_count = 0;
    static uint32_t armed = 1;

    uint32_t reading = control_buttons_scan();

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

/* D10 / PB6: MOSFET control output. */
static void lock_led_init(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    (void)RCC->AHB2ENR;

    GPIOB->BSRR = (1U << 22);
    GPIOB->MODER &= ~(3U << 12);
    GPIOB->MODER |= (1U << 12);
    GPIOB->OTYPER &= ~(1U << 6);
    GPIOB->PUPDR &= ~(3U << 12);
    GPIOB->OSPEEDR &= ~(3U << 12);
}

/* PC10 / CN7 pin 1: USART3 TX, 9600 baud. */
static void link_init(void)
{
    SystemCoreClockUpdate();

    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    RCC->APB1ENR1 |= RCC_APB1ENR1_USART3EN;
    (void)RCC->APB1ENR1;

    RCC->APB1RSTR1 |= RCC_APB1RSTR1_USART3RST;
    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_USART3RST;

    /* USART3 uses SYSCLK. */
    RCC->CCIPR = (RCC->CCIPR & ~RCC_CCIPR_USART3SEL)
                | RCC_CCIPR_USART3SEL_0;

    GPIOC->BSRR = (1U << 10);
    GPIOC->OTYPER &= ~(1U << 10);

    GPIOC->PUPDR = (GPIOC->PUPDR & ~(3U << 20))
                  | (1U << 20);

    GPIOC->OSPEEDR &= ~(3U << 20);

    GPIOC->AFR[1] = (GPIOC->AFR[1] & ~(15U << 8))
                   | (7U << 8);

    GPIOC->MODER = (GPIOC->MODER & ~(3U << 20))
                  | (2U << 20);

    USART3->CR1 = 0;
    USART3->CR2 = 0;
    USART3->CR3 = 0;
    USART3->BRR = (SystemCoreClock + 4800U) / 9600U;
    USART3->CR1 = USART_CR1_TE | USART_CR1_UE;
}

/* Prepare the number and status for the N657. */
static void link_snapshot(void)
{
    if (tx_index != FRAME_SIZE)
    {
        return;
    }

    tx_frame[0] = '@';

    if (lock_active != 0U)
    {
        tx_frame[1] = 'U';
    }
    else if (call_ready != 0U)
    {
        tx_frame[1] = 'C';
    }
    else
    {
        tx_frame[1] = 'E';
    }

    for (uint32_t i = 0; i < MAX_DIGITS; i++)
    {
        tx_frame[i + 2U] =
            (i < digit_count) ? dialed_number[i] : ' ';
    }

    uint8_t sum = frame_checksum(tx_frame);

    tx_frame[10] = hex_digit(sum >> 4);
    tx_frame[11] = hex_digit(sum);
    tx_frame[12] = '\n';

    tx_index = 0;
}

/* Transmit without blocking the keypad or timer. */
static void link_poll(void)
{
    if ((tx_index < FRAME_SIZE) &&
        ((USART3->ISR & USART_ISR_TXE) != 0U))
    {
        USART3->TDR = (uint8_t)tx_frame[tx_index++];

        if (tx_index == FRAME_SIZE)
        {
            link_frames_sent++;
        }
    }
}

int main(void)
{
    uint32_t previous_press_count = 0;
    uint32_t link_ms = 0;

    keypad_init();
    control_buttons_init();
    lock_led_init();
    link_init();
    link_snapshot();

    /* SysTick: nominal 1 ms polling. */
    SystemCoreClockUpdate();

    SysTick->CTRL = 0;
    SysTick->LOAD = (SystemCoreClock / 1000U) - 1U;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk
                  | SysTick_CTRL_ENABLE_Msk;

    for (;;)
    {
        link_poll();

        if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0U)
        {
            keypad_update();
            control_buttons_update();

            if (unlock_remaining_ms > 0U)
            {
                unlock_remaining_ms--;

                if (unlock_remaining_ms == 0U)
                {
                    lock_active = 0;
                }
            }

            if (control_press_count != previous_press_count)
            {
                previous_press_count = control_press_count;

                /* Button 4 starts a three-second unlock. */
                if ((last_control_button == 4U) &&
                    (lock_active == 0U))
                {
                    lock_active = 1;
                    unlock_remaining_ms = 3000U;
                }
            }

            if (++link_ms >= 100U)
            {
                link_ms = 0;
                link_snapshot();
            }

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
