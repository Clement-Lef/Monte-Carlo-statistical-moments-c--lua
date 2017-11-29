//
// Created by Clément Lefebvre on 12.12.16.
//

#ifndef PCSC_MONTECARLO_RANDOMEXPONENTIAL_H
#define PCSC_MONTECARLO_RANDOMEXPONENTIAL_H


#include "RandomGenerator.h"

/// This class is used to generate random numbers following an exponential distribution

class RandomExponential : public RandomGenerator {
    std::exponential_distribution<double> distribution;

public:
    /**
    * This is the constructor
    * @param lambda : Parameter of the exponential distribution
    * @param seed : Seed of the random generator, it is default to the clock time of the CPU
    */
    RandomExponential(const double &lambda, const double &seed = std::chrono::system_clock::now().time_since_epoch().count());

    /**
     * Compute and return a random number following the uniform distribution
     * @return a random number
     */
    double getRandomNumber();

};


#endif //PCSC_MONTECARLO_RANDOMEXPONENTIAL_H
