#include <stdint.h>

typedef struct {
        uint32_t seed;
        uint32_t x;
        uint32_t y;
        uint32_t z;
        uint32_t w;
} random_generator_t;

void random_generator_init(random_generator_t* const rng, const uint32_t* const seed);

void random_generator_reset(random_generator_t* const rng);

uint32_t random_generator_get_seed(const random_generator_t* const rng);

void random_generator_set_seed(random_generator_t* const rng, const uint32_t seed);

double random_generator_rand(random_generator_t* const rng);

double random_generator_randi(random_generator_t* const rng,
                              const double min_val,
                              const double max_val);
