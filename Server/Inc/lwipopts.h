/*
 * lwipopts.h
 *
 *  Created on: Sep 28, 2026
 *      Author: mfuhrman
 */

#ifndef LWIP_HDR_LWIPOPTS_H
#define LWIP_HDR_LWIPOPTS_H

/* Bare-metal mode (No RTOS / No OS threads) */
#define NO_SYS                          1
#define SYS_LIGHTWEIGHT_PROT            0

/* Memory layout and alignment for 32-bit Cortex-M */
#define MEM_ALIGNMENT                   4
#define MEM_SIZE                        (16 * 1024)

/* Disable OS-dependent Sockets & Netconn APIs */
#define LWIP_SOCKET                     0
#define LWIP_NETCONN                    0

/* Enable Raw TCP API */
#define LWIP_TCP                        1
#define TCP_MSS                         1460

/* Disable DHCP for now (we can assign a static IP first) */
#define LWIP_DHCP                       0

#endif /* LWIP_HDR_LWIPOPTS_H */
