//
// Created by Clément Lefebvre on 21.11.16.
//

#include "RandomGenerator.h"



void RandomGenerator::setSeed(double const &seed) {
    if (seed == 0) {
        generator = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
    }
    else {
        generator = std::default_random_engine(seed);
    }
}

RandomGenerator::~RandomGenerator() {
}

