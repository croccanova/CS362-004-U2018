CFLAGS = -Wall -pedantic -lm

all: testme
	./testme

testme: testme.c
	gcc $(CFLAGS) -std=c99 -o testme testme.c

clean:
	rm -rf testme
