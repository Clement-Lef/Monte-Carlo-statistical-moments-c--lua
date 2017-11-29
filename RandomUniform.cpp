//
// Created by Clément Lefebvre on 28.11.16.
//

#include "RandomUniform.h"

RandomUniform::RandomUniform(const double &newMin, const double &newMax, const double &seed) {
    generator = std::default_random_engine(seed);
    distribution = std::uniform_real_distribution<double>(newMin,newMax);
}

double RandomUniform::getRandomNumber() {
    return distribution(generator);
}


