.PHONY: test pgmopts connect

CFLAGS := -O3 -std=c11 -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=500
CFLAGS += -Wall -Wmissing-prototypes -Wstrict-prototypes -Werror=implicit-function-declaration -Werror=format -Wshadow -Wswitch -pthread
CFLAGS += `pkg-config --cflags gattlib`

LDFLAGS += `pkg-config --libs gattlib`

OBJS := \
	btlehrservice.o \
	containment.o \
	argparse.o \
	pgmopts.o \
	llist.o

BINARIES := btlehrservice

all: btlehrservice 

btlehrservice: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJS)
	rm -f $(BINARIES)

pgmopts:
	../Python/pypgmopts/pypgmopts parser.py

test: all
	./btlehrservice 20:C3:8F:FF:0A:7E heartrate_socket

connect:
	socat - UNIX:heartrate_socket

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<
