#include "lwip/tcp.h"
#include <string.h>

#define SERVER_PORT 5000

static struct tcp_pcb *client_pcb = NULL;

// Callback when server replies with data
static err_t client_recv_cb (void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    if (p == NULL) 
    {
        tcp_close (tpcb);
        client_pcb = NULL;
        return ERR_OK;
    }

    tcp_recved (tpcb, p->tot_len);
    pbuf_free (p);
    return ERR_OK;
}

// Callback when TCP handshake successfully completes
static err_t client_connected_cb (void *arg, struct tcp_pcb *tpcb, err_t err)
{
    if (err == ERR_OK) 
    {
        tcp_recv (tpcb, client_recv_cb);

        char payload [] = "Hello from Bare-Metal Client!";
        tcp_write (tpcb, payload, strlen(payload), TCP_WRITE_FLAG_COPY);
        tcp_output (tpcb);
    }
    return ERR_OK;
}

// Trigger a connection to the server IP
void send_client_message (ip_addr_t *server_ip)
{
    client_pcb = tcp_new ();
    if (client_pcb != NULL) 
    {
        tcp_connect (client_pcb, server_ip, SERVER_PORT, client_connected_cb);
    }
}
