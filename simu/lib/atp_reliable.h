#ifndef _ATP_RELIABLE_H_
#define _ATP_RELIABLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/uio.h>
#include "atp_pktio.h"

#define MAX_WND  512
#define MAX_TASK 1024

/**
 * A structure to record each packet's state.
 */
struct pkt_state {
    /* The timestamp of the packet is sent */
    uint64_t ts;
    /* The packet's sequence number */
    uint32_t seq;
    /* Offset in the buffer */
    uint64_t off;
    /* This packet's length */
    uint16_t len;
};

/**
 * A structure to record each connection's state 
 */
struct conn_state {
    /* Connection ID */
    uint32_t id;
    /* Destination MAC */
    uint8_t dst_mac[LEN_MAC_ADDR];
    /* Destination IP */
    uint32_t dst_ip;
    /* Manage each packet's state in a sliding window */
    struct pkt_state states[MAX_WND];
    /* Left boundary of the sliding window */
    uint32_t last_acked;
    /* Seq of the last sent packet */
    uint32_t last_sent;
    /* Total bytes sent/received */
    uint64_t total_bytes;
    /* Total packets sent/received */
    uint64_t total_pkts; 

    /* Send/Recv task queue */
    struct iovec tasks[MAX_TASK];
    /* Queue head */
    uint64_t head;
    /* Queue tail */
    uint64_t tail;
};

/**
 * Initilize and allocate resources
 *
 * @para conf
 *   Global configuration
 * @para conn
 *   Sender connection state
 * @return 
 *   0: Success
 *   1: Otherwise 
 */
int init_send(struct atp_conf* conf, struct conn_state* conn);
/**
 * Exit and free resources
 *
 * @para conf
 *   Global configuration
 * @return 
 *   0: Success
 *   1: Otherwise 
 */
int exit_send(struct atp_conf*);
/**
 * Send data to the destination node. 
 * 
 * @para conf
 *   Global configuration
 * @para conn
 *   Sender connection state
 */
void atp_send(struct atp_conf* conf, struct conn_state* conn);
/**
 * Initilize and allocate resources
 *
 * @para conf
 *   Global configuration
 * @para conn
 *   Receiver connection state
 * @return 
 *   0: Success
 *   1: Otherwise 
 */
int init_recv(struct atp_conf* conf, struct conn_state* conn);
/**
 * Exit and free resources
 *
 * @para conf
 *   Global configuration
 * @return 
 *   0: Success
 *   1: Otherwise 
 */
int exit_recv(struct atp_conf*);
/**
 * Receive data from the source node
 *
 * @para conf
 *   Global configuration
 * @para conn
 *   Receiver connection state
 */
void atp_recv(struct atp_conf* conf, struct conn_state* conn);

#ifdef __cplusplus
}
#endif

#endif
