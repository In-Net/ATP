#ifndef _ATP_LOG_
#define _ATP_LOG_

#include <stdio.h>

#define CO_RED                "\033[1;31m"
#define CO_BLACK              "\033[1;30m"
#define CO_RED                "\033[1;31m"
#define CO_GREEN              "\033[1;32m"
#define CO_YELLOW             "\033[1;33m"
#define CO_BLUE               "\033[1;34m"
#define CO_PURPLE             "\033[1;35m"
#define CO_SKYBLUE            "\033[1;36m"
#define CO_WHITE              "\033[1;37m"
#define CO_RESET              "\033[0m"
#define BG_BLACK              "\033[40m"
#define BG_RED                "\033[41m"
#define BG_GREEN              "\033[42m"
#define BG_YELLOW             "\033[43m"
#define BG_BLUE               "\033[44m"
#define BG_PURPLE             "\033[45m"
#define BG_SKYBLUE            "\033[46m"
#define BG_WHITE              "\033[47m"
#define BG_RESET              "\033[0m"

#define LOG_INFO(format, ...)  printf("[%sINFO%s] " format, CO_GREEN,  CO_RESET, ##__VA_ARGS__)
#define LOG_WARN(format, ...)  printf("[%sWARN%s] " format, CO_YELLOW, CO_RESET, ##__VA_ARGS__)
#define LOG_ERRO(format, ...)  printf("[%sERRO%s] " format, CO_RED,    CO_RESET, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...) printf("[%sDEBUG%s] " format, CO_PURPLE, CO_RESET, ##__VA_ARGS__)

#endif
