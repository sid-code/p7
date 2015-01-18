CC=cc
CCFLAGS=-Wall -Wextra -O3 -c

all: p7.c p7test.c
	$(CC) $(CCFLAGS) p7.c
	$(CC) $(CCFLAGS) p7test.c
	$(CC) p7.o p7test.o -o p7test
