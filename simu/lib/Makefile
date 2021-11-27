LIB = atp
CC  = g++

# all source are stored in SRCS-y
SRCS-y := atp_pktio.cc atp_reliable.cc atp_msg.cc

ifneq ($(shell uname),Linux)
$(error This application can only operate in a linux environment)
endif

all: lib_shared
.PHONY: lib_shared
lib_shared: build/lib$(LIB).so

CFLAGS  += -O3
CFLAGS  += -std=c++11
LDFLAGS += -lrt
LDFLAGS += -lnuma
LDFLAGS += -fPIC
LDFLAGS += -shared
LDFLAGS += -D_REENTRANT

build/lib$(LIB).so: $(SRCS-y) | build
	$(CC) $(CFLAGS) $(SRCS-y) -o $@ $(LDFLAGS) -Wl,--no-undefined

build:
	@mkdir -p $@

.PHONY: install
install: $(APP)
	cp build/lib$(LIB).so /usr/local/lib/x86_64-linux-gnu

.PHONY: clean
clean:
	rm -f build/lib$(LIB).so
	test -d build && rmdir -p build || true

