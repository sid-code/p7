#include <stdio.h>
#ifndef P7_H
#define P7_H

typedef struct prng_state PSprng;
struct prng_state {
  double seed;
  double cur;
};

PSprng psprng_create(double seed);
double psprng_emit_raw(PSprng *prng);
double psprng_emit(PSprng *prng);
int psprng_getbit(PSprng *prng);
int psprng_getbyte(PSprng *prng);
double monte_carlo(PSprng *prng, int throws);
void psprng_write_to_file(PSprng *prng, FILE *fp);
#endif
