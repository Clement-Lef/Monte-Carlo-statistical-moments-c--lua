//
// Created by Clément Lefebvre on 12.12.16.
//

#include "RandomExponential.h"

RandomExponential::RandomExponential(const double &lambda, const double &seed) {
    generator = std::default_random_engine(seed);
    distribution = std::exponential_distribution<double>(lambda);
}

double RandomExponential::getRandomNumber() {
    return distribution(generator);
}