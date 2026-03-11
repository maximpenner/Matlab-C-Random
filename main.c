#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "random_generator.h"

int main() {
    // time dependent seed
    srand(time(NULL));
    const uint32_t seed = rand() % UINT32_MAX;

    FILE* const file = fopen("c_reference.txt", "w");
    if (file == NULL) {
        return EXIT_FAILURE;
    }

    // first line contains the seed
    fprintf(file, "%.d\n", seed);

    random_generator_t rng;
    random_generator_init(&rng, &seed);

    // generator random numbers
    for (size_t i = 0; i < 1000; i++) {
        // write with full precision
        fprintf(file, "%.20g\n", random_generator_rand(&rng));
    }

    fclose(file);

    return EXIT_SUCCESS;
}
