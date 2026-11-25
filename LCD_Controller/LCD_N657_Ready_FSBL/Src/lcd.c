#include "stm32n6xx.h"
#include "lcd.h"

/* N657 Arduino pins: RS=D2, E=D3, LCD D4..D7=D4..D7. */
static GPIO_TypeDef *const ports[6] = {
    GPIOD, GPIOE, GPIOE, GPIOE, GPIOD, GPIOE
};
static const uint8_t pins[6] = {0, 9, 0, 10, 5, 11};

static void delay_us(uint32_t us)
{
    uint32_t ticks = ((SystemCoreClock + 999999U) / 1000000U) * us;
    SysTick->CTRL = 0;
    SysTick->LOAD = ticks - 1U;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
    for (; (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0U; ) { }
    SysTick->CTRL = 0;
}

void lcd_delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < ms; i++)
        delay_us(1000U);
}

static void write_pin(uint32_t index, uint32_t high)
{
    ports[index]->BSRR = 1UL << (pins[index] + (high ? 0U : 16U));
}

static void write_nibble(uint8_t value)
{
    for (uint32_t i = 0; i < 4; i++)
        write_pin(i + 2U, (value >> i) & 1U);
    delay_us(2U);
    write_pin(1U, 1U);
    delay_us(2U);
    write_pin(1U, 0U);
    delay_us(50U);
}

static void write_byte(uint8_t value, uint32_t data)
{
    write_pin(0U, data);
    write_nibble(value >> 4);
    write_nibble(value & 0x0FU);
    if ((data == 0U) && ((value == 0x01U) || (value == 0x02U)))
        lcd_delay_ms(3U);
}

void lcd_init(void)
{
    SystemCoreClockUpdate();
    RCC->AHB4ENSR = RCC_AHB4ENSR_GPIODENS | RCC_AHB4ENSR_GPIOEENS;
    (void)RCC->AHB4ENR;
    for (uint32_t i = 0; i < 6; i++)
    {
        GPIO_TypeDef *port = ports[i];
        uint32_t pin = pins[i];
        port->BSRR = 1UL << (pin + 16U);
        port->OTYPER &= ~(1UL << pin);
        port->PUPDR &= ~(3UL << (2U * pin));
        port->OSPEEDR &= ~(3UL << (2U * pin));
        port->MODER = (port->MODER & ~(3UL << (2U * pin)))
                    | (1UL << (2U * pin));
    }
    /* Recover the LCD even if only the MCU was reset. RW stays grounded. */
    lcd_delay_ms(50U);
    write_nibble(0x03U);
    lcd_delay_ms(5U);
    write_nibble(0x03U);
    lcd_delay_ms(1U);
    write_nibble(0x03U);
    lcd_delay_ms(1U);
    write_nibble(0x02U);
    write_byte(0x28U, 0U);  /* 4-bit bus, two lines. */
    write_byte(0x08U, 0U);
    write_byte(0x01U, 0U);
    write_byte(0x06U, 0U);
    write_byte(0x0CU, 0U);  /* Display on, cursor off. */
}

void lcd_set_cursor(uint32_t row, uint32_t column)
{
    if ((row < 2U) && (column < 16U))
        write_byte((uint8_t)(0x80U | (row ? 0x40U : 0U) | column), 0U);
}

void lcd_print(const char *text)
{
    for (uint32_t i = 0; (i < 16U) && (text[i] != '\0'); i++)
        write_byte((uint8_t)text[i], 1U);
}
