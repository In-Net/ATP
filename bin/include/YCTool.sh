#!/bin/bash

##
# Show Progress Bar; Note this will block the process
# 
# @para : ${1}
#     time in seconds
##
progress_bar() {
    if [ ! ${1} ]; then
        echo_erro "usage: ${FUNCNAME} time"
	exit 0
    fi
    if [ ${1} -le 0 ]; then
        echo_erro "usage: ${FUNCNAME} time"
	exit 0
    fi
    bTool=''
    curTool=0
    intervalTool=1
    maxlenTool=50
    temptimeTool=$((${1}-1))
    intervalTool=`expr ${temptimeTool} / ${maxlenTool}`
    intervalTool=$((${intervalTool}+1))
    barlenTool=$((${1}/${intervalTool}))
    while [ ${curTool} -le ${1} ]
    do
        printf "[${color_yellow}WAIT${color_reset}] [${color_green}%-${barlenTool}s${color_reset}] [%2d/%d] \r" "$bTool" "${curTool}" "${1}";
        bTool+="#"
        ((curTool=curTool+${intervalTool}))
        sleep ${intervalTool}
    done
    echo ""
}

get_terminal_width() {
    local _width_=`stty size|awk '{print $2}'`
    echo ${_width_}
}
