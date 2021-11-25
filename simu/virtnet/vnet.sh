#!/bin/bash

source ../../bin/include/YCFile.sh
source ../../bin/include/YCLog.sh
source ../../bin/include/YCTool.sh
source ../../bin/include/YCOS.sh

####################################################
username=""
num_node=5
####################################################

show_usage() {
    appname=$0
    echo_info "Usage: ${appname} [command], e.g., ${appname} create ns"
    echo_info "  -- create  [ns|mininet|docker|kvm]"
    echo_info "  -- destroy [ns|mininet|docker|kvm]"
    echo_info "  -- help                          show help message"
}

ns_create() {
    local cmd="brctl"
    local addbr="addbr"
    local addif="addif"
    local netPrefix="10.10.10"
    local gw="ns-br0"
    local gw_suffix=200

    local _ret=`check_cmd ${cmd}`
    if [ ${_ret} == -1 ]; then
        echo_back "sudo apt-get install bridge-utils"
    fi 

    # gateway of the virtual network
    echo_back "sudo ${cmd} ${addbr} ${gw}"
    echo_back "sudo ifconfig ${gw} ${netPrefix}.${gw_suffix}/24 up"
    local _start=1
    local _end=${num_node}
    for idx in `seq ${_start} ${_end}`
    do
        namespace="net${idx}"
        intf0="veth-${idx}"
        intf1="br-eth${idx}"
        echo_line 60 "-" "Creating namespace ${namespace}"
        echo_back "sudo ip netns add ${namespace}"
        echo_back "sudo ip link add ${intf0} type veth peer name ${intf1}"
        echo_back "sudo sysctl net.ipv6.conf.${intf0}.disable_ipv6=1"
        echo_back "sudo sysctl net.ipv6.conf.${intf1}.disable_ipv6=1"
        echo_back "sudo ip link set ${intf0} netns ${namespace}"
        echo_back "sudo ip netns exec ${namespace} ifconfig lo 127.0.0.1 up"
        echo_back "sudo ip netns exec ${namespace} ifconfig ${intf0} ${netPrefix}.${idx}/24 up"
        echo_back "sudo ip link set ${intf1} up"
        echo_back "sudo ip netns exec ${namespace} route add default gw ${netPrefix}.${gw_suffix}"
        echo_back "sudo ${cmd} ${addif} ${gw} ${intf1}"
    done

    echo_back "sudo iptables -t nat -A POSTROUTING -s ${netPrefix}.0/24 ! -d ${netPrefix}.0/24 -j MASQUERADE"

    echo_back "sudo sysctl -w net.ipv4.ip_forward=1"
    echo_back "sudo ip link set ${gw} up"
}
ns_destroy() {
    local cmd="brctl"
    local delbr="delbr"
    local delif="delif"
    local netPrefix="10.10.10"
    local gw="ns-br0"

    local _ret=`check_cmd ${cmd}`
    if [ ${_ret} == -1 ]; then
        echo_back "sudo apt-get install bridge-utils"
    fi 

    echo_back "sudo ifconfig ${gw} down"
    echo_back "sudo ${cmd} ${delbr} ${gw}"
  
    local _start=1
    local _end=${num_node}
    for idx in `seq ${_start} ${_end}`
    do
        namespace="net${idx}"
        echo_back "sudo ip netns delete ${namespace}"
    done

    echo_back "sudo iptables -t nat -D POSTROUTING -s ${netPrefix}.0/24 ! -d ${netPrefix}.0/24 -j MASQUERADE"
}

mininet_create() {
    # TODO
    echo_warn "TODO"
}
mininet_destroy() {
    # TODO
    echo_warn "TODO"
}

docker_create() {
    # TODO
    echo_warn "TODO"
}
docker_destroy() {
    # TODO
    echo_warn "TODO"
}

kvm_create() {
    # TODO
    echo_warn "TODO"
}
kvm_destroy() {
    # TODO
    echo_warn "TODO"
}

create() {
    local nettype=${1} 
    case ${nettype} in
        "ns")
            ns_create
            ;;
        "mininet")
            mininet_create
            ;;
        "docker")
            docker_create
            ;;
        "kvm")
            kvm_create
            ;;
        *)
            show_usage
            ;;
    esac
}

destroy() {
    local nettype=${1} 
    case ${nettype} in
        "ns")
            ns_destroy
            ;;
        "mininet")
            mininet_destroy
            ;;
        "docker")
            docker_destroy
            ;;
        "kvm")
            kvm_destroy
            ;;
        *)
            show_usage
            ;;
    esac
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
    "create")
        create ${2}
        ;;
    "destroy")
        destroy ${2}
        ;;
    "help")
        show_usage 
        ;;
    *)
        echo_erro "Unrecognized argument!"
        show_usage
        ;;
esac
