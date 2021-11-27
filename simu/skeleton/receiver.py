#! /usr/bin/python3
# -*- coding: UTF-8 -*-

import ctypes
import time

if __name__ == '__main__':
    # Path to the shared library
    dll_path = "/usr/local/lib/x86_64-linux-gnu/libatp.so"
    atp = ctypes.CDLL(dll_path, ctypes.RTLD_GLOBAL)
    
    conn_id = 1

    atp.recv_msg.argtypes = [ctypes.c_int]
    atp.recv_msg.restype = ctypes.c_int
    while True:
        ret = atp.recv_msg(conn_id)
        print(ret)
        
