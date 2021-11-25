#!/bin/bash

################################################################
##                 _
##    ___ ___   __| | ___  ___ _   _ _ __   ___
##   / __/ _ \ / _` |/ _ \/ __| | | | '_ \ / __|
##  | (_| (_) | (_| |  __/\__ \ |_| | | | | (__
##   \___\___/ \__,_|\___||___/\__, |_| |_|\___|
##                             |___/
################################################################
# auther: Yongchao He
# email: yongchao-he@outlook.com 
################################################################

# RE_DIR="/home/yongchao/code"
################################################################
myuser="yongchao"
BE_DIR="$(cd .. "`dirname ${BASH_SOURCE[0]}`"; pwd)"
RE_DIR="/home/${myuser}/code" 
SSH_LIST=(
    # first_hop [second_hop] remote_dir
    # hop_format: username@ip port 
    # "${myuser}@101.6.96.190 2332 ${RE_DIR}"
    "${myuser}@101.6.96.190 2332 ${myuser}@10.0.0.1 22 ${RE_DIR}"
)
################################################################

color_black="\033[1;30m"
color_red="\033[1;31m"
color_green="\033[1;32m"
color_yellow="\033[1;33m"
color_blue="\033[1;34m"
color_purple="\033[1;35m"
color_skyblue="\033[1;36m"
color_white="\033[1;37m"
color_reset="\033[0m"
echo_back() {
    cmdLog=${1}
    printf "[${color_green}EXEC${color_reset}] ${cmdLog}\n"
    eval ${cmdLog}
}
echo_info() {
    cmdLog=${1}
    printf "[${color_green}INFO${color_reset}] ${cmdLog}\n"
}
echo_warn() {
    cmdLog=${1}
    printf "[${color_yellow}WARN${color_reset}] ${cmdLog}\n"
}
echo_erro() {
    cmdLog=${1}
    printf "[${color_red}ERRO${color_reset}] ${cmdLog}\n"
}

show_usage() {
    appname=$0
    echo_info "Usage: ${appname} [Options]"
    echo_info "  -- -s       start synchronizing files to remote servers" 
    echo_info "  -- -c       stop and clean rsync processes"
}

sync_stop() {
    echo_info "Terminate rsync..."
    for pid in `pgrep fswatch`
    do
        echo_back "sudo kill -9 $pid"
    done
}

# Example
# rsync --delete -avzhcPe 'ssh -T -p xx user@ip -t ssh -p yy -i ~/.ssh/id_rsa' local_dir user@ip:remote_dir
sync_one_hop() {
    local bedir=$1
    local redir=$4
    local info1=$2
    local port1=$3 # ignored
    if [ ! ${redir} ]; then
        echo_warn "Please specify the remote directory"
        exit 0
    fi
    echo_info "Synchronizing ${bedir} to ${info1}:${port1}:${redir}"
    fswatch -o $bedir | while read f; do rsync --delete -avzhcPe ssh ${bedir} ${info1}:${redir}; done &
    echo_info "Done! (PID: $!)"
}

sync_two_hop() {
    local bedir=$1
    local redir=$6
    local info1=$2
    local port1=$3
    local info2=$4
    local port2=$5
    if [ ! ${redir} ]; then
        echo_warn "Please specify the remote directory"
        exit 0
    fi
    echo_info "Synchronizing ${bedir} to ${info2}:${port2}:${redir} over ${info1}:${port1}"
    fswatch -o $bedir | while read f; do rsync --delete -avzhcPe "ssh -p ${port1} ${info1} -t ssh -p ${port2} -i ~/.ssh/id_rsa " $bedir ${info2}:${redir}; done &
    echo_info "Done! (PID: $!)"
}

sync_start() {
    if [ ! ${BE_DIR} ]; then
        echo_warn "Please specify the local directory"
        exit 0
    fi
    if [ ! -d ${BE_DIR} ]; then
        echo_erro "${BE_DIR} does not exist"
        exit 0
    fi
    for ssh_item in "${SSH_LIST[@]}"; do
        local ssh_para=(${ssh_item})
        if (( ${#ssh_para[*]} == 3 )); then
            sync_one_hop ${BE_DIR} ${ssh_para[0]} ${ssh_para[1]} ${ssh_para[2]}
        elif (( ${#ssh_para[*]} == 5 )); then
            sync_two_hop ${BE_DIR} ${ssh_para[0]} ${ssh_para[1]} ${ssh_para[2]} ${ssh_para[3]} ${ssh_para[4]}
        else
            echo_erro "unsupported format: ${ssh_para}"
        fi
    done
}

para_checker() {
    if [ ! ${myuser} ]; then
        echo_erro "Please provide a valid username" 
        exit 0
    fi
    if [ ! ${BE_DIR} ]; then
        echo_erro "Please provide a valid directory for BE_DIR" 
        exit 0
    fi
    if [ ! ${RE_DIR} ]; then
        echo_erro "Please provide a valid directory for RE_DIR" 
        exit 0
    fi
}

################################################################
####################    * Main Process *    ####################
################################################################
if (( $# == 0 )); then
    show_usage
    exit 0
fi

if (( $UID == 0 )); then
    echo_erro "Don't run this script as root"
    exit 0
fi

para_checker

while getopts "cmsldh" opt;
do
    case $opt in
        c)
            sync_stop
            ;;
        s)
            sync_start
            ;;
        h)
            show_usage
            ;;
        \?)
            show_usage
            ;;
    esac
done
