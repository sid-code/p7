#include <stdlib.h>
#include "p7.h"

int main(int argc, char **argv) {
  double seed;
  if (argc < 2) {
    seed = 1.08;
  } else {
    seed = atof(argv[1]);
  }

  PSprng prng = psprng_create(seed);
  double result = monte_carlo(&prng, 10000000000);
  printf("%0.8f\n", result);

  return 0;
}
