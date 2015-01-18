CC=cc
CCFLAGS=-Wall -Wextra -O3 -c
ifeq ($(INTERVAL),)
  REPORT_INTERVAL=
else
  REPORT_INTERVAL=-DREPORT_INTERVAL=$(INTERVAL)
endif

ifeq ($(PARALLEL),)
  PARALLEL_=
else
  PARALLEL_=-DPARALLEL
endif

all: p7.c p7test.c p7multi.c
	$(CC) $(CCFLAGS) $(REPORT_INTERVAL) p7.c
	$(CC) $(CCFLAGS) p7test.c
	$(CC) $(CCFLAGS) $(PARALLEL_) -lpthread p7multi.c
	$(CC) p7.o p7test.o -o p7test
	$(CC) p7.o p7multi.o -o p7multi -lpthread
