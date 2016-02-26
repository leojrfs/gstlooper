GCC := $(CROSS_COMPILE)gcc
CFLAGS := -Wall -Os -g

.PHONY: all install clean
all: dummy
dummy: dummy.o
        $(GCC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
%.o: %.c
        $(GCC) -c $< -o $@ $(CFLAGS)
install:
        install -m 755 dummy $(DESTDIR)/usr/bin
clean:
        rm -f dummy dummy.o
