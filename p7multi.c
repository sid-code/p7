#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "p7.h"

struct mc_task {
  double seed;
  int throws;
};

void *monte_carlo_large(void *void_task_ptr) {
  struct mc_task *task = (struct mc_task *) void_task_ptr;
  PSprng prng = psprng_create(task->seed);
  printf("s=%.8f, %.8f\n", task->seed, monte_carlo(&prng, task->throws));
  free(task);

  return NULL;

}

volatile int finished;

int main() {

#define THROWS 1000000000

#define START 1.01
#define END   1.10
#define STEP  0.01

  int num_threads = (END - START) / STEP;
  pthread_t mc_threads[num_threads];
  int index = 0;

  double seed;


  for (seed = START; seed < END; seed += STEP, index++) {
    struct mc_task *task = malloc(sizeof(struct mc_task));
    task->seed = seed;
    task->throws = THROWS;

    pthread_t mc_thread;
    pthread_create(&mc_thread, NULL, monte_carlo_large, task);
    mc_threads[index] = mc_thread;
  }

  for (index = 0; index < num_threads; index++) {
    pthread_join(mc_threads[index], NULL);
  }


  printf("Finished %d threads.\n", num_threads);

  return 0;
}
