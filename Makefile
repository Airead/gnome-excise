#DESTDIR = /usr/bin

CC	= gcc

CFLAGS	= -Wall -g
#CFLAGS += $(shell pkg-config --cflags glib-2.0 )
CFLAGS += $(shell pkg-config --cflags gtk+-2.0)

LDFLAGS	= 
#LDFLAGS += $(shell pkg-config --libs glib-2.0)
LDFLAGS += $(shell pkg-config --libs gtk+-2.0)

Hello: hello.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: clean install uninstall

clean:
	rm -f *~ a.out *.o Hello core.*

install:
	cp Hello $(DESTDIR)/usr/bin 
	mkdir -p $(DESTDIR)/usr/share/hello
	cp logo.png $(DESTDIR)/usr/share/hello

uninstall:
	rm -f $(DESTDIR)/usr/bin/Hello
	rm -rf $(DESTDIR)/usr/share/hello




