#ifndef SHAMIR_H
#define SHAMIR_H

#include <math.h>

#define FINITE_FIELD_SIZE pow(10, 10)

struct Key{
    int x;
    int y;
    int exponentMax;
};

int shamirEncrypt(int numKeys, int requiredDescryptors, int secret, struct Key *output);

#endif