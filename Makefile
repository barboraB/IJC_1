CC=gcc
LC_ALL=cs_CZ.utf8
CFLAGS=-O2 -g -std=c99 -Wall -pedantic -Wextra
LDFLAGS=-lm

default: steg-decode primes-i primes

eratosthenes.o: eratosthenes.c bit_array.h

eratosthenes-i.o: eratosthenes.c bit_array.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c -o eratosthenes-i.o eratosthenes.c $(LDFLAGS)

error.o: error.c error.h

primes-i.o: primes.c error.h bit_array.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c -o primes-i.o primes.c $(LDFLAGS)

primes.o: primes.c error.h bit_array.h

primes: eratosthenes.o error.o primes.o

primes-i: eratosthenes-i.o error.o primes-i.o

steg-decode.o: steg-decode.c error.h ppm.h bit_array.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c -o steg-decode.o steg-decode.c $(LDFLAGS)

ppm.o: ppm.c error.h

steg-decode: steg-decode.o ppm.o error.o

run:
	time ./primes
	time ./primes-i

clean:
	rm -f *.o primes steg-decode primes-i
