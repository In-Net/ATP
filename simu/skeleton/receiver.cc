#include <getopt.h>
#include <iostream>

#include "../lib/atp_pktio.h"
#include "../lib/atp_log.h"

static inline void
show_usage(char* app) {
    LOG_INFO(CO_YELLOW "Usage:" CO_RESET " %s [Options]\n", app);
    LOG_INFO("Available Options:\n");
    LOG_INFO("  --pktio            Test packet send/recv\n");
    LOG_INFO("  --stream           Reliable transmission\n");
    LOG_INFO("  --msg              Test message send/recv\n");
    exit(0);
}

static void
main_pktio(void) {
    // TODO
}

static void
main_stream(void) {
    // TODO
}

static void
main_msg(void) {
    // TODO
}

static inline void
opt_parser(int argc, char** argv) {
    if (argc <= 1) {
        show_usage(argv[0]);
    }

    static int lopt = 0;
    static struct option opts[] = {
        {"pktio",  no_argument, &lopt, 1},
        {"stream", no_argument, &lopt, 2},
        {"msg",    no_argument, &lopt, 3},
        {0, 0, 0, 0}
    };

    int c, opt_index = 0;
    while ((c = getopt_long(argc, argv, "", opts, &opt_index)) != -1) {
        switch(c) {
        case 0:
            switch(lopt) {
                case 1:
                    main_pktio();
                    break;
                case 2:
                    main_stream();
                    break;
                case 3:
                    main_msg();
                    break;
            }
            break;
        default:
            show_usage(argv[0]);
        }
    }
}

int main(int argc, char** argv) {
    opt_parser(argc, argv);
    return 0;
}
