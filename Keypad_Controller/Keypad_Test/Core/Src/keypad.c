#include "keypad.h"
#include "stm32l4xx.h"

/* Rows D2-D5: PA10, PB3, PB5, PB4 */
static GPIO_TypeDef * const row_ports[4] = {
    GPIOA, GPIOB, GPIOB, GPIOB
};
static const uint8_t row_pins[4] = {10, 3, 5, 4};

/* Columns D6-D8: PB10, PA8, PA9 */
static GPIO_TypeDef * const col_ports[3] = {
    GPIOB, GPIOA, GPIOA
};
static const uint8_t col_pins[3] = {10, 8, 9};

static const char keys[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

/* Variables for debugging and number entry. */
volatile char current_key = 0;
volatile char last_key = 0;
volatile uint32_t key_count = 0;
volatile char dialed_number[MAX_DIGITS + 1U] = {0};
volatile uint32_t digit_count = 0;
volatile uint32_t call_ready = 0;

/* Configure GPIO clocks, LED, rows, and columns. */
void keypad_init(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN
                 | RCC_AHB2ENR_GPIOBEN;
    (void)RCC->AHB2ENR;

    /* PA5: onboard green LED. */
    GPIOA->BSRR = (1U << 21);
    GPIOA->MODER &= ~(3U << 10);
    GPIOA->MODER |=  (1U << 10);
    GPIOA->OTYPER &= ~(1U << 5);
    GPIOA->PUPDR &= ~(3U << 10);

    /* Open-drain rows: LOW selects; HIGH releases. */
    for (unsigned int r = 0; r < 4; r++)
    {
        GPIO_TypeDef *port = row_ports[r];
        unsigned int pin = row_pins[r];

        port->BSRR = (1U << pin);
        port->OTYPER |= (1U << pin);
        port->PUPDR &= ~(3U << (2U * pin));
        port->OSPEEDR &= ~(3U << (2U * pin));
        port->MODER &= ~(3U << (2U * pin));
        port->MODER |=  (1U << (2U * pin));
    }

    /* Column inputs with pull-ups. */
    for (unsigned int c = 0; c < 3; c++)
    {
        GPIO_TypeDef *port = col_ports[c];
        unsigned int pin = col_pins[c];

        port->MODER &= ~(3U << (2U * pin));
        port->PUPDR &= ~(3U << (2U * pin));
        port->PUPDR |=  (1U << (2U * pin));
    }
}

/* Return the detected character, or 0 for no press. */
static char keypad_scan(void)
{
    for (unsigned int r = 0; r < 4; r++)
    {
        row_ports[r]->BSRR =
            (1U << (row_pins[r] + 16U));

        /* Brief signal-settling delay. */
        for (volatile unsigned int i = 0; i < 100; i++)
        {
            __NOP();
        }

        for (unsigned int c = 0; c < 3; c++)
        {
            if ((col_ports[c]->IDR &
                 (1U << col_pins[c])) == 0U)
            {
                row_ports[r]->BSRR = (1U << row_pins[r]);
                return keys[r][c];
            }
        }

        row_ports[r]->BSRR = (1U << row_pins[r]);
    }

    return 0;
}

/* Handle digits, clear (*), and confirm (#). */
static void process_key(char key)
{
    if (key == '*')
    {
        for (unsigned int i = 0; i <= MAX_DIGITS; i++)
        {
            dialed_number[i] = '\0';
        }

        digit_count = 0;
        call_ready = 0;
    }
    else if (key == '#')
    {
        if (digit_count > 0U)
        {
            call_ready = 1;
        }
    }
    else if ((key >= '0') && (key <= '9'))
    {
        if ((call_ready == 0U) && (digit_count < MAX_DIGITS))
        {
            dialed_number[digit_count] = key;
            digit_count++;
            dialed_number[digit_count] = '\0';
        }
    }
}

/* Call once per nominal 1 ms timer event. */
void keypad_update(void)
{
    static char candidate = 0;
    static char stable_key = 0;
    static unsigned int stable_count = 0;
    static unsigned int armed = 1;

    current_key = keypad_scan();

    /* Debounce using 20 matching samples. */
    if (current_key != candidate)
    {
        candidate = current_key;
        stable_count = 1;
    }
    else if (stable_count < 20U)
    {
        stable_count++;
    }

    if ((stable_count == 20U) && (candidate != stable_key))
    {
        stable_key = candidate;

        /* Accept one press, then require release. */
        if (stable_key == 0)
        {
            armed = 1;
        }
        else if (armed != 0U)
        {
            last_key = stable_key;
            key_count++;
            armed = 0;
            process_key(stable_key);
        }
    }

    /* LED follows the debounced button state. */
    if (stable_key != 0)
    {
        GPIOA->BSRR = (1U << 5);
    }
    else
    {
        GPIOA->BSRR = (1U << 21);
    }
}
