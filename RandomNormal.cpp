//
// Created by Clément Lefebvre on 10.12.16.
//

#include "RandomNormal.h"

RandomNormal::RandomNormal(const double &newMean, const double &stddev, const double &seed) {
    generator = std::default_random_engine(seed);
    distribution = std::normal_distribution<double>(newMean,stddev);
}

double RandomNormal::getRandomNumber() {
    return distribution(generator);
}