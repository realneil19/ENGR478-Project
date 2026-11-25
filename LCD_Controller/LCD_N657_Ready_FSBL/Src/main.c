#include "stm32n6xx.h"
#include "lcd.h"

#define FRAME_SIZE 13U

volatile uint32_t lcd_test_stage = 0;
volatile uint32_t link_rx_bytes = 0;
volatile uint32_t link_valid_frames = 0;
volatile uint32_t link_bad_frames = 0;
volatile uint32_t link_uart_errors = 0;
volatile uint32_t link_hsi_hz = 0;

static inline char hex_digit(uint8_t n)
{
    return "0123456789ABCDEF"[n & 15U];
}

static inline uint8_t frame_checksum(const char *frame)
{
    uint8_t sum = 0;

    for (uint32_t i = 1; i < 10U; i++)
    {
        sum ^= (uint8_t)frame[i];
    }

    return sum;
}

static inline int frame_valid(const char *frame)
{
    uint32_t padding = 0;

    if ((frame[0] != '@') || (frame[12] != '\n'))
    {
        return 0;
    }

    if ((frame[1] != 'E') &&
        (frame[1] != 'C') &&
        (frame[1] != 'U'))
    {
        return 0;
    }

    for (uint32_t i = 2; i < 10U; i++)
    {
        if (frame[i] == ' ')
        {
            padding = 1;
        }
        else if ((padding != 0U) ||
                 (frame[i] < '0') ||
                 (frame[i] > '9'))
        {
            return 0;
        }
    }

    uint8_t sum = frame_checksum(frame);

    return (frame[10] == hex_digit(sum >> 4)) &&
           (frame[11] == hex_digit(sum));
}

/* D0 / PD9: USART3 RX, 9600 baud. */
static int link_init(void)
{
    RCC->CSR = RCC_CSR_HSIONS;

    uint32_t timeout = 1000000U;

    for (; ((RCC->SR & RCC_SR_HSIRDY) == 0U) &&
           (timeout != 0U); timeout--)
    {
    }

    if (timeout == 0U)
    {
        return 0;
    }

    RCC->AHB4ENSR = RCC_AHB4ENSR_GPIODENS;
    RCC->APB1ENSR1 = RCC_APB1ENSR1_USART3ENS;
    (void)RCC->APB1ENR1;

    RCC->APB1RSTSR1 = RCC_APB1RSTSR1_USART3RSTS;
    RCC->APB1RSTCR1 = RCC_APB1RSTCR1_USART3RSTC;

    /* USART3 uses HSI with its current divider. */
    RCC->CCIPR13 =
        (RCC->CCIPR13 & ~RCC_CCIPR13_USART3SEL)
        | RCC_CCIPR13_USART3SEL_2
        | RCC_CCIPR13_USART3SEL_1;

    link_hsi_hz =
        64000000U >> ((RCC->HSICFGR & RCC_HSICFGR_HSIDIV)
                      >> RCC_HSICFGR_HSIDIV_Pos);

    GPIOD->PUPDR =
        (GPIOD->PUPDR & ~(3UL << 18)) | (1UL << 18);

    GPIOD->AFR[1] =
        (GPIOD->AFR[1] & ~(15UL << 4)) | (7UL << 4);

    GPIOD->MODER =
        (GPIOD->MODER & ~(3UL << 18)) | (2UL << 18);

    USART3->CR1 = 0;
    USART3->CR2 = 0;
    USART3->CR3 = 0;
    USART3->PRESC = 0;
    USART3->BRR = (link_hsi_hz + 4800U) / 9600U;

    USART3->ICR = USART_ICR_ORECF
                | USART_ICR_FECF
                | USART_ICR_NECF
                | USART_ICR_PECF;

    USART3->CR1 = USART_CR1_FIFOEN
                | USART_CR1_RE
                | USART_CR1_UE;

    return 1;
}

static void show_frame(const char *frame)
{
    static char previous[FRAME_SIZE] = {0};
    uint32_t changed = 0;

    for (uint32_t i = 1; i < 10U; i++)
    {
        if (previous[i] != frame[i])
        {
            changed = 1;
        }
    }

    if (changed == 0U)
    {
        return;
    }

    for (uint32_t i = 0; i < FRAME_SIZE; i++)
    {
        previous[i] = frame[i];
    }

    char number[17] = "                ";

    for (uint32_t i = 0; i < 8U; i++)
    {
        number[i] = frame[i + 2U];
    }

    lcd_set_cursor(0U, 0U);

    if (frame[1] == 'U')
    {
        lcd_print("Unlock active   ");
    }
    else if (frame[1] == 'C')
    {
        lcd_print("Number confirmed");
    }
    else
    {
        lcd_print("Enter number    ");
    }

    lcd_set_cursor(1U, 0U);

    if ((frame[2] == ' ') && (frame[1] == 'E'))
    {
        lcd_print("* clear  # enter");
    }
    else
    {
        lcd_print(number);
    }
}

int main(void)
{
    char frame[FRAME_SIZE];
    uint32_t index = 0;

    lcd_test_stage = 1;
    lcd_init();

    lcd_set_cursor(0U, 0U);
    lcd_print("PROJECT 478     ");

    lcd_set_cursor(1U, 0U);
    lcd_print("Waiting keypad  ");

    lcd_test_stage = 2;

    if (link_init() == 0)
    {
        lcd_set_cursor(1U, 0U);
        lcd_print("UART clock error");

        for (;;)
        {
        }
    }

    lcd_test_stage = 3;

    for (;;)
    {
        uint32_t status = USART3->ISR;

        uint32_t errors = status &
            (USART_ISR_ORE | USART_ISR_FE |
             USART_ISR_NE | USART_ISR_PE);

        if (errors != 0U)
        {
            USART3->ICR = USART_ICR_ORECF
                        | USART_ICR_FECF
                        | USART_ICR_NECF
                        | USART_ICR_PECF;

            if ((status & USART_ISR_RXNE_RXFNE) != 0U)
            {
                (void)USART3->RDR;
            }

            index = 0;
            link_uart_errors++;
        }
        else if ((status & USART_ISR_RXNE_RXFNE) != 0U)
        {
            char value = (char)(USART3->RDR & 255U);
            link_rx_bytes++;

            if (value == '@')
            {
                index = 0;
                frame[index++] = value;
            }
            else if (index != 0U)
            {
                frame[index++] = value;

                if (index == FRAME_SIZE)
                {
                    index = 0;

                    if (frame_valid(frame))
                    {
                        link_valid_frames++;
                        show_frame(frame);
                    }
                    else
                    {
                        link_bad_frames++;
                    }
                }
            }
        }
    }
}
