GCC := $(CROSS_COMPILE)gcc
LIBS=`pkg-config gstreamer-1.0 --libs`
CFLAGS=`pkg-config gstreamer-1.0 --cflags`

.PHONY: all install clean
all: gstlooper
gstlooper: gstlooper.o
	$(GCC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
%.o: %.c
	$(GCC) -c $< -o $@ $(CFLAGS)
install:
	install -m 755 gstlooper $(DESTDIR)/usr/bin
clean:
	rm -f gstlooper gstlooper.o
