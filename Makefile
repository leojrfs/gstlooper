GCC := $(CROSS_COMPILE)gcc
LIBS=`pkg-config gstreamer-1.0 --libs`
CFLAGS=`pkg-config gstreamer-1.0 --cflags`

GST_CFLAGS := $(shell pkg-config --cflags gstreamer-1.0 gstreamer-base-1.0)
GST_LIBS := $(shell pkg-config --libs gstreamer-1.0 gstreamer-base-1.0)

.PHONY: all install clean
all: gstlooper
gstlooper: gstlooper.o
	$(GCC) $(CFLAGS) $(GST_CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS) $(GST_LIBS)
%.o: %.c
	$(GCC) -c $< -o $@ $(CFLAGS) $(GST_CFLAGS)
install:
	install -m 755 gstlooper $(DESTDIR)/usr/bin
clean:
	rm -f gstlooper gstlooper.o
