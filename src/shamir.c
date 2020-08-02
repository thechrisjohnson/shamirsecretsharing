#ifdef __linux__
    #include <bsd/stdlib.h>
#endif

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shamir.h"

int main(int argc, char** argv)
{
    // Create space for the keys we'll be returning
    struct Key *keys = malloc(sizeof(struct Key) * 5);
    
    int result = shamirEncrypt(5, 2, 1234, keys);

    printf("Test: %d\n", (int)pow(1234, 0));

    printf("Keys: \n");
    for (int i = 0; i < 5; i++)
    {
        printf("\t[%u, %llu]\n", keys[i].x, keys[i].y);
    }

    printf ("Decrypting...\n");
    int output = shamirDecrypt(2, keys);
    printf ("Decrypted value: %d\n", output);
    
    return result;
}

int shamirEncrypt(int numKeys, int requiredDecryptors, int secret, struct Key *output)
{
    if (numKeys < requiredDecryptors)
    {
        fprintf(stderr, "The number of keys requested must be higher than the number of required decryptors\n");
    }

    // An array to contain our function, each [n] represents the cooefficient of x^n
    int function[requiredDecryptors];

    // Set the x^0 coefficient as the secret
    function[0] = secret;

    printf("Secret exponents: %d, ", function[0]);
    // Set the other coefficients with random numbers
    for (int i = 1; i < requiredDecryptors; i++)
    {
        function[i] = arc4random_uniform(FINITE_FIELD_SIZE / 2);
        
        printf("%d", function[i]);
        if (i != requiredDecryptors - 1)
        {
            printf(", ");
        }
        else
        {
            printf("\n");
        }
        
    }

    // Now generate the keys
    for (int i = 0; i < numKeys; i++)
    {
        output[i].exponentMax = requiredDecryptors - 1;
        output[i].x = arc4random_uniform(FINITE_FIELD_SIZE / 2);
        for (int j = 0; j < requiredDecryptors; j++)
        {
            output[i].y += function[j] * (int)pow(output[i].x, j);
        }
    }

    return 0;
}

int shamirDecrypt(int numKeys, struct Key *output)
{
    if (numKeys < output[0].exponentMax + 1)
    {
        fprintf(stderr, "There are not enough keys to decrypt the secret\n");
        return -1;
    }

    double sum = 0;
    for (int j = 0; j < numKeys; j++)
    {
        long double prod = 1;
        long double xj = (long double)output[j].x;
        
        for (int m = 0; m < numKeys; m++)
        {
            if (m != j)
            {
                long double xm = (long double)output[m].x;
                prod *= xm / (xm - xj);
            }
        }

        prod *= (long double)output[j].y;
        printf("Iteration %d: %Lf\n", j, prod);
        sum += prod;
    }

    return (int)round(sum);
}

// TODO: When we figure out what we want the parameters to be
void printHelp() {
    printf("usage: shamir ");
}
