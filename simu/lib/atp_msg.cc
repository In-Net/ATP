#include <iostream>

#include "atp_log.h"
#include "atp_msg.h"

int init_send_conn(uint32_t conn_id) {
    int ret = 0;

    // TODO
    // Allocate shared memory and create message queues

    return ret;
}

int send_msg(uint32_t conn_id, char* dst_ip, int64_t msg_key, char* addr, size_t len) {
    int ret = 0;

    // TODO
    // Notify the C++ sender using message queue

    return ret;
}

int64_t done_msg(uint32_t conn_id) {
    int64_t msg_key = -1;

    // TODO 
    // Check message queue 

    return msg_key;
}

void exit_send_conn(uint32_t conn_id) {
    // TODO
}

int init_recv_conn(uint32_t conn_id) {
    // TODO
    return 0;
}

int64_t recv_msg(uint32_t conn_id) {
    // TODO
    return 0;
}

void exit_recv_conn(uint32_t conn_id) {
    // TODO
}
