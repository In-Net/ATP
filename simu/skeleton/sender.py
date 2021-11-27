#! /usr/bin/python3
# -*- coding: UTF-8 -*-

import ctypes
import time

def gen_msgs():
    messages = []

    # TODO
    messages.append(b"Hello, ATP!")

    return messages

if __name__ == '__main__':
    # Path to the shared library
    dll_path = "/usr/local/lib/x86_64-linux-gnu/libatp.so"
    atp = ctypes.CDLL(dll_path, ctypes.RTLD_GLOBAL)
    
    # TODO
    dst_host = b"" # e.g., 192.168.0.2 
    conn_id = 1
    messages = gen_msgs()
    msg_key  = 0 

    # Initialize sending connection 
    atp.init_send_conn.argtypes = [ctypes.c_int]
    atp.init_send_conn.restype = ctypes.c_int
    ret = atp.init_send_conn(conn_id)
    if ret != 0:
        exit(-1) 
   
    for msg in messages:
        # enqueue a sending task
        atp.send_msg.argtypes = [ctypes.c_int, ctypes.c_char_p, ctypes.c_longlong, ctypes.c_char_p, ctypes.c_size_t]
        atp.send_msg.restype = ctypes.c_int
        ret = atp.send_msg(conn_id, dst_host, msg_key, msg, len(msg))
        if ret != 0:
            break
        msg_key = msg_key + 1

    done = 0
    while True:
        if done == len(messages):
            break
        # Check if any message has been sent
        atp.done_msg.argtypes = [ctypes.c_int]
        atp.done_msg.restype = ctypes.c_int
        msg_key = atp.done_msg(conn_id)
        if msg_key == -1:
            time.sleep(0.01)
        else:
            done = done + 1 
            print("Done [%d/%d]" % (done, len(messages)))

    # Exit and free resources
    atp.exit_send_conn.argtypes = [ctypes.c_int]
    atp.exit_send_conn(conn_id)
