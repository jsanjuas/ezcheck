CFLAGS=-Wall
SRCS=fact.c unittesting.c
LDLIBS=-lcheck

all: main test

main: main.c $(SRCS)
	gcc $(CFLAGS) main.c $(SRCS) -o main $(LDLIBS)

test: main.c $(SRCS)
	gcc -DCOMPILE_TESTS $(CFLAGS) main.c $(SRCS) -o test $(LDLIBS)

clean:
	rm -f main test

