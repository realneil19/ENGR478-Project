#include "lwip/api.h"
#include "lwip/dhcp.h"
#include "lwip/netif.h"
#include "cmsis_os.h"
#include <string.h>

#define SERVER_PORT 5000
extern struct netif gnetif;

void tcp_client_task (void *argument)
{
    struct netconn *conn;
    err_t err;
    ip_addr_t server_ip;
    uint32_t msg_counter = 0;

    // 1. Target Server IP Configuration
    // (Set this to the IP assigned to your server by the router)
    IP4_ADDR (&server_ip, 192, 168, 1, 150); 

    // 2. Wait for DHCP IP Assignment on Client
    while (!netif_is_dhcp_supplied (&gnetif)) 
    { osDelay(100);  }

    for (;;) 
    {
        // 3. Create a new TCP socket
        conn = netconn_new (NETCONN_TCP);
        if (conn == NULL) 
        {
            osDelay(1000);
            continue;
        }

        // 4. Connect to server
        err = netconn_connect (conn, &server_ip, SERVER_PORT);

        if (err == ERR_OK) 
        {
            // 5. Send data payload
            char payload [64];
            int len = snprintf (payload, sizeof (payload), 
				"Hello from STM32 Client #%lu", msg_counter++);
            
            err = netconn_write (conn, payload, len, NETCONN_COPY);

            if (err == ERR_OK) 
            {
                // Read response from server
                struct netbuf *buf;
                if (netconn_recv (conn, &buf) == ERR_OK) 
                {
                    netbuf_delete (buf);
                }
            }

            // Close socket cleanly
            netconn_close (conn);
        }

        netconn_delete (conn);

        // Wait 1 second before sending next transmission
        osDelay (1000);
    }
}
