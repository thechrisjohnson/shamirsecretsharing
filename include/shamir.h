#ifndef SHAMIR_H
#define SHAMIR_H

#include <math.h>
#include <stdint.h>

#define FINITE_FIELD_SIZE pow(10, 5)

struct Key{
    uint x;
    ulong y;
    int exponentMax;
};

int shamirEncrypt(int numKeys, int requiredDescryptors, int secret, struct Key *output);

#endif
