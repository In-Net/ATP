#ifndef _ATP_MSG_H_
#define _ATP_MSG_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize a sending connection. For example, setup socket, allocate shared memory, etc.
 *
 * @para conn_id
 *   Connection ID 
 * @return
 *   0: Success
 *   -1: Otherwise
 */
int init_send_conn(uint32_t conn_id);
/**
 * Generate and enqueue a send task.
 * 
 * @para conn_id
 *   Connection ID 
 * @para dst_ip
 *   IP address of the receiver
 * @para msg_key
 *   An unique key to identify a message
 * @para addr
 *   The address of the message
 * @para msg_len
 *   Length of the message 
 * @return
 *   0: Success
 *   -1: Otherwise
 */
int send_msg(uint32_t conn_id, char* dst_ip, int64_t msg_key, char* addr, size_t msg_len);
/**
 * Check if any message has been sent on the specified connection
 * 
 * @para conn_id
 *   Connection ID 
 * @return 
 *   msg_key, if the corresponding message has been sent
 *   -1, Otherwise 
 */
int64_t done_msg(uint32_t conn_id);
/**
 * Close a sending connection and free the resources
 *
 * @para conn_id
 *   Connection ID 
 */
void exit_send_conn(uint32_t conn_id); 

/**
 * Initialize a receiving connection. For example, setup socket, allocate shared memory, etc.
 * 
 * @para conn_id
 *   Connection ID 
 * @return
 *   0: Success
 *   -1: Otherwise
 */
int init_recv_conn(uint32_t conn_id);
/**
 * Listen to the message queue and return the key of the completed task
 * 
 * @para conn_id
 *   Connection ID 
 * @return
 *   Message key
 */
int64_t recv_msg(uint32_t conn_id);
/**
 * Close a receiving connection and free the resources
 *
 * @para conn_id
 *   Connection ID 
 */
void exit_recv_conn(uint32_t conn_id); 

#ifdef __cplusplus
}
#endif

#endif
