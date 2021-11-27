#include <getopt.h>
#include <signal.h>
#include <iostream>

#include "../lib/atp_pktio.h"
#include "../lib/atp_log.h"

volatile bool force_quit = false;

static inline void
show_usage(char* app) {
    LOG_INFO(CO_YELLOW "Usage:" CO_RESET " %s [Options]\n", app);
    LOG_INFO("Available Options:\n");
    LOG_INFO("  --pktio            Test packet send/recv\n");
    LOG_INFO("  --bytestream       Reliable transmission\n");
    LOG_INFO("  --msg              Test message send/recv\n");
    exit(0);
}

static void
signal_handler(int signum) {
    if (signum == SIGINT || signum == SIGTERM) {
        printf("\n");
        LOG_WARN("Signal %d received, preparing to exit ...\n", signum);
        force_quit = true;
    } else {
        printf("\n");
        LOG_WARN("Unrecognized signal %d\n", signum);
    }
}

static void 
send_pktio(void) {
    // TODO 
}

static void 
send_stream(void) {
    // TODO 
}

static void 
send_service(void) {
    // TODO 

    LOG_INFO("Press Ctl+C to exit...\n");
    while (force_quit == false) {
        // TODO
    }
}

static inline void
opt_parser(int argc, char** argv) {
    if (argc <= 1) {
        show_usage(argv[0]);
    }

    static int lopt = 0;
    static struct option opts[] = {
        {"pktio",      no_argument, &lopt, 1},
        {"bytestream", no_argument, &lopt, 2},
        {"msg",        no_argument, &lopt, 3},
        {0, 0, 0, 0}
    };

    int c, opt_index = 0;
    while ((c = getopt_long(argc, argv, "", opts, &opt_index)) != -1) {
        switch(c) {
        case 0:
            switch(lopt) {
                case 1:
                    send_pktio();
                    break;
                case 2:
                    send_stream();
                    break;
                case 3:
                    send_service();
                    break;
            }
            break;
        default:
            show_usage(argv[0]);
        }
    }
}

int main(int argc, char** argv) {
    /* Register signal handler to process signal, such as CTL+C */ 
    signal(SIGINT,  signal_handler);
    signal(SIGTERM, signal_handler);
 
    opt_parser(argc, argv);
    return 0;
}
