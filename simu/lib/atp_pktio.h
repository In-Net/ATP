#ifndef _ATP_PKTIO_
#define _ATP_PKTIO_

#include <stdint.h>
#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif

#define LEN_MAC_ADDR 6

struct atp_conf {
    /* Network Adaptor, e.g., eth0 */
    char* device; 
    /* Network Adaptor, e.g., Index */
    uint16_t kindex;
    /* ID */
    uint32_t ID;
    /* Total Worker */
    uint32_t num_worker;
    /* Source MAC */
    uint8_t src_mac[LEN_MAC_ADDR];
    /* Source IP */
    uint32_t src_ip;
    /* More */
    // TODO 
};

/**
 * An example header definition:
 * ATP Header Definition. Refer to https://www.usenix.org/conference/nsdi21/presentation/lao
 *
struct __attribute__((__packed__)) atp_hdr {
    uint32_t bitmap0;
    uint32_t bitmap1;
    uint16_t type;
    uint16_t aggregator_index;
    uint32_t jobid_seq;
};
*/
/**
 * Simplified Header Definition 
 */
struct __attribute__((__packed__)) atp_hdr {
    /* Connection ID */
    uint8_t conn_id:4;
    /* ACK */
    uint8_t ack:1;
    /* ECN echo flag bit */
    uint8_t ece:1;
    uint8_t reserved:2;
    /* Sequence Number */
    uint32_t seq;
};

/**
 * ATP Packet Content
 */
struct atp_pkt {
   /* Base address of the packet */
   char* addr;
   /* Header + Payload */
   size_t len; 
};

/**
 * Send a burst of output packets on an Ethernet device.
 * 
 * @para conf
 *   Global configuration.
 * @para pkts
 *   The address of an array of *num* pointers to *atp_pkt* structures 
 *   which contain the output packets.
 * @para num
 *   The maximum number of packets to transmit.
 * @return
 *   The number of output packets actually stored in transmit descriptors of
 *   the transmit ring. The return value can be less than the value of the
 *   *pkts* parameter when the transmit ring is full or has been filled up.
 */
uint8_t snd_pkts(struct atp_conf* conf, struct atp_pkt** pkts, uint8_t num);

/**
 * Receive a burst of input packets from an Ethernet device.
 *
 * @para conf
 *   Global configuration.
 * @para pkts
 *   The address of an array of pointers to *atp_pkt* structures that
 *   must be large enough to store *num* pointers in it.
 * @para num
 *   The maximum number of packets to retrieve.
 * @return
 *   The number of packets actually retrieved, which is the number
 *   of pointers to *atp_pkt* structures effectively supplied to the
 *   *pkts* array.
 */
uint8_t rcv_pkts(struct atp_conf* conf, struct atp_pkt** pkts, uint8_t num);

#ifdef __cplusplus
}
#endif

#endif
