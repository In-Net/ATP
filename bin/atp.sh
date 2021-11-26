#!/bin/bash

source ../include/YCFile.sh
source ../include/YCLog.sh
source ../include/YCTool.sh
source ../include/YCOS.sh

####################################################
username=""
####################################################

show_usage() {
    appname=$0
    echo_info "Usage: ${appname} [command] [options]"
    echo_info "  -- rcmd [hostname] [intruction]           execute a command on the remote server"
    echo_info "  -- vnet [create|destroy|confignet|ping]   virtual network operations"
    echo_info "  -- ..." 
    echo_info "  -- help                                   show help message"
}

################################################################
####################    * Main Process *    ####################
################################################################
export LC_ALL=C

if (( $# == 0 )); then
    echo_warn "Argument cannot be NULL!"
    show_usage
    exit 0
fi

if (( $UID == 0 )); then
    echo_erro "Don't run this script as root!"
    exit 0
fi

username=`who am i | awk '{print $1}'`

global_choice=${1}
case ${global_choice} in
    "rcmd")
        # This should be implemented as a function
        # TODO 
        ;;
    "vnet")
        # TODO
        ;;
    "help")
        show_usage 
        ;;
    *)
        echo_erro "Unrecognized argument!"
        show_usage
        ;;
esac
