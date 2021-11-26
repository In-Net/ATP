APP = atp
CC  = g++

# all source are stored in SRCS-s/r
SRCS-s := sender.cc 
SRCS-r := receiver.cc

ifneq ($(shell uname),Linux)
$(error This application can only operate in a linux environment)
endif

all: sender
.PHONY: sender receiver
sender:   build/$(APP)_sender
receiver: build/$(APP)_receiver

CFLAGS  += -O3
CFLAGS  += -std=c++11
LDFLAGS += -lrt
LDFLAGS += -lnuma
LDFLAGS += -latp

build/$(APP)_sender: $(SRCS-s) | build
	$(CC) $(CFLAGS) $(SRCS-s) -o $@ $(LDFLAGS)

build/$(APP)_receiver: $(SRCS-r) | build
	$(CC) $(CFLAGS) $(SRCS-r) -o $@ $(LDFLAGS)

build:
	@mkdir -p $@

.PHONY: clean
clean:
	rm -f build/$(APP)_sender
	rm -f build/$(APP)_receiver
	test -d build && rmdir -p build || true

