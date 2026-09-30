#define STM32N657xx
#define PPP_SUPPORT 0

#include "stm32n6xx.h"      // CMSIS register map for STM32N6 family
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/dhcp.h"
#include "lwip/timeouts.h"

// Millisecond tick counter driven by SysTick
static volatile uint32_t msTicks = 0;

/* Define the global SystemCoreClock variable declared in system_stm32n6xx.h */
uint32_t SystemCoreClock = 64000000; // Default boot clock frequency in Hz

void SysTick_Handler (void)
{
    msTicks++;
}

uint32_t GetTick (void)
{
    return msTicks;
}

int main (void)
{
    // 1. Configure SysTick for 1ms interrupts using CMSIS
    SysTick_Config (SystemCoreClock / 1000);

    // 2. Initialize LwIP core stack (NO_SYS = 1 bare metal)
    lwip_init ();

    while (1)
    {
        // Main event loop - we will add LwIP packet & timer processing here
    }
}
