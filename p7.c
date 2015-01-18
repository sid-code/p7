#include <stdio.h>
#include "p7.h"

PSprng psprng_create(double seed) {
  return (PSprng) { seed, seed };
}

double psprng_emit_raw(PSprng *prng) {
  return prng->cur = prng->seed - 1 / prng->cur;
}

#define MULT 100000
double psprng_emit(PSprng *prng) {
  double num = psprng_emit_raw(prng) * MULT;
  return num - (int) num;
}

int psprng_getbit(PSprng *prng) {
  return psprng_emit(prng) > 0.5;
}

int psprng_getbyte(PSprng *prng) {
  int x, r = 0;
  for (x = 0; x < 8; x++) {
    r = (r << 1) | psprng_getbit(prng);
  }

  return r;
}

#define REPORT_INTERVAL 10000000
double monte_carlo(PSprng *prng, int throws) {
  int hits = 0, i;
  for (i = 0; i < throws; i++) {
    double x = psprng_emit(prng);
    double y = psprng_emit(prng);

    if (x * x + y * y < 1) hits++;
#ifdef REPORT_INTERVAL
    if (i % REPORT_INTERVAL == 1) {
      printf("round %d, approx=%0.8f\n", i, ((double) hits) / i * 4);
    }
#endif
  }

  return ((double) hits) / throws * 4;
}

void psprng_write_to_file(PSprng *prng, FILE *fp) {
  int num, x;
  for (x = 0; x < 20000000; x++) {
    num = psprng_getbyte(prng);
    fwrite(&num, 1, 1, fp);
  }
}

// int main() {
// 
// //   int throws = 100000000;
// // #define START 1.08
// // #define END   1.09
// // #define STEP  0.001
// // 
// //   double seed;
// //   for (seed = START; seed < END; seed += STEP) {
// //     PSprng prng = psprng_create(seed);
// //     printf("(s=%.8f) Monte Carlo value of pi with %d throws:\n", seed, throws);
// //     printf("   %.8f\n", monte_carlo(&prng, throws));
// //   }
// 
//   PSprng prng = psprng_create(1.08);
//   printf("%.8f\n", monte_carlo(&prng, 1000000000));
// 
//   return 0;
// }
