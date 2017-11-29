//
// Created by Clément Lefebvre on 28.11.16.
//

#ifndef PCSC_MONTECARLO_RANDOMUNIFORM_H
#define PCSC_MONTECARLO_RANDOMUNIFORM_H

#include "RandomGenerator.h"
#include <random>

///  This class is used to generate random numbers following a uniform distribution



class RandomUniform : public RandomGenerator {
private:
    /// Declare a uniform distribution of real numbers
    std::uniform_real_distribution<double> distribution;

public:
    /**
     * This is the constructor
     * @param newMin : Minimum of the random generator
     * @param newMax : Maximum of the random generator
     * @param seed : Seed of the random generator, it is default to the clock time of the CPU
     */
    RandomUniform(const double &newMin, const double &newMax, const double &seed = std::chrono::system_clock::now().time_since_epoch().count());


    /**
     * Compute and return a random number following the uniform distribution
     * @return a random number
     */
    double getRandomNumber();


};


#endif //PCSC_MONTECARLO_RANDOMUNIFORM_H
