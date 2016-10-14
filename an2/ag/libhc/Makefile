OBJs = hill_climbing.o
CC = g++
INCLUDES =
LIBS =
CPPFLAGS = -fPIC

all: strip install
.PHONY: all

hill_climbing.o: hill_climbing.cpp hill_climbing.h
	$(CC) -c hill_climbing.cpp $(CPPFLAGS) $(LIBS)

libhc.so: hill_climbing.o hill_climbing.h
	$(CC) -shared -o libhc.so hill_climbing.o hill_climbing.h $(CPPFLAGS) $(LIBS)

strip: libhc.so
	strip -s libhc.so
.PHONY: strip

install:
	sudo cp ./libhc.so /usr/lib/libhc.so
	sudo cp ./hill_climbing.h /usr/include/hill_climbing.h
	sudo cp ./libhc.conf /etc/ld.so.conf.d/libhc.conf
	sudo /sbin/ldconfig
.PHONY: install

clean: libhc.so libhc.so
	rm -f libhc.so
	rm -f libhc.o
.PHONY: clean
