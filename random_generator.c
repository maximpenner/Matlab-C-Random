#include "random_generator.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>

static void xor128(random_generator_t* const rng) {
    const uint32_t t = rng->x ^ (rng->x << 11);
    rng->x = rng->y;
    rng->y = rng->z;
    rng->z = rng->w;
    const uint32_t a = rng->w >> 19;
    const uint32_t b = t >> 8;
    const uint32_t c = t ^ b;
    rng->w = (rng->w ^ a) ^ c;
}

void random_generator_init(random_generator_t* const rng, const uint32_t* const seed) {
    if (seed == NULL) {
        random_generator_reset(rng);
    } else {
        random_generator_set_seed(rng, *seed);
    }
}

void random_generator_reset(random_generator_t* const rng) {
    // arbitrary default seed
    random_generator_set_seed(rng, 123456789);
}

uint32_t random_generator_get_seed(const random_generator_t* const rng) { return rng->seed; }

void random_generator_set_seed(random_generator_t* const rng, const uint32_t seed) {
    assert(seed <= UINT32_MAX);

    rng->seed = seed;
    rng->x = seed;

    // arbitrary default state
    rng->y = 1111111111U;
    rng->z = 2222222222U;
    rng->w = 3333333333U;
}

double random_generator_rand(random_generator_t* const rng) {
    xor128(rng);
    return (double)rng->w / (double)UINT32_MAX;
}

double random_generator_randi(random_generator_t* const rng,
                              const double min_val,
                              const double max_val) {
    assert(min_val <= max_val);
    assert(min_val == round(min_val));
    assert(max_val == round(max_val));

    const double r = random_generator_rand(rng);

    return floor(r * (max_val - min_val + 1.0)) + min_val;
}
