CC = gcc
CFLAGS = -std=c99 -Wall -fpic -fstack-protector -D_FORTIFY_SOURCE=2 -O2 -I/usr/local/include -I. -lwiringPi
DEPS = 
#OBJ = dht22.o locking.o
OBJ = dht22.o

build: install example

install: libdht22.so
	cp dht22.h /usr/local/include/
	mv libdht22.so /usr/lib/
	ldconfig

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

libdht22.so: dht22.o
	gcc -shared -o $@ $< $(CFLAGS)

example: libdht22.so
	gcc -o $@ example.c $(CFLAGS) -ldht22

clean:
	rm -f ./*.o
	rm -f ./*.so
	rm -f example
	rm -f Seeed_DHT22
