#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shamir.h"

int main(int argc, char** argv)
{
    // Create space for the keys we'll be returning
    struct Key *keys = malloc(sizeof(struct Key) * 5);
    
    int result = shamirEncrypt(5, 3, 1234, keys);

    printf("Keys: \n");
    for (int i = 0; i < 5; i++)
    {
        printf("\t[%d, %d]\n", keys[i].x, keys[i].y);
    }
    
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
        function[i] = arc4random_uniform(FINITE_FIELD_SIZE);
        
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
        output[i].x = arc4random_uniform(FINITE_FIELD_SIZE);
        for (int j = 0; j < requiredDecryptors; j++)
        {
            output[i].y = function[j] * pow(output[i].x, j);
        }
    }

    return 0;
}

// TODO: When we figure out what we want the parameters to be
void printHelp() {
    printf("usage: shamir ");
}