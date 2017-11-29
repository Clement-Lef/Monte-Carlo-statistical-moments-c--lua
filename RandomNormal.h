//
// Created by Clément Lefebvre on 10.12.16.
//

#ifndef PCSC_MONTECARLO_RANDOMNORMAL_H
#define PCSC_MONTECARLO_RANDOMNORMAL_H


#include "RandomGenerator.h"



/// This class is used to generate random numbers following a normal (gaussian) distribution

class RandomNormal : public RandomGenerator {
    std::normal_distribution<double> distribution;

public:
    /** \brief Constructor
    * This is the constructor
    * @param newMean : Mean of the normal distribution
    * @param stddev : Standard deviation of the normal distribution
    * @param seed : Seed of the random generator, it is default to the clock time of the CPU
    */
    RandomNormal(const double &newMean, const double &stddev, const double &seed = std::chrono::system_clock::now().time_since_epoch().count());

    /** \brief Compute a random number
    * Compute and return a random number following the uniform distribution
    * @return a random number
    */
    double getRandomNumber();

};


#endif //PCSC_MONTECARLO_RANDOMNORMAL_H
