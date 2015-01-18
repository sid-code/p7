#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "p7.h"

struct mc_task {
  double seed;
  int throws;
  volatile int *finished;
};

void *monte_carlo_large(void *void_task_ptr) {
  struct mc_task *task = (struct mc_task *) void_task_ptr;
  PSprng prng = psprng_create(task->seed);
  printf("s=%.8f, %.8f\n", task->seed, monte_carlo(&prng, task->throws));
  *task->finished++;
  free(task);

  return NULL;

}

int main() {

#define THROWS 1000000000

#define START 1.01
#define END   1.10
#define STEP  0.01

  int num_threads = (END - START) / STEP;
  volatile int finished = 0;

  double seed;

  for (seed = START; seed < END; seed += STEP) {
    struct mc_task *task = malloc(sizeof(struct mc_task));
    task->seed = seed;
    task->throws = THROWS;
    task->finished = &finished;

    pthread_t mc_thread;
    pthread_create(&mc_thread, NULL, monte_carlo_large, task);
  }

  while (finished < num_threads);

  printf("Finished %d threads.\n", num_threads);

  return 0;
}
