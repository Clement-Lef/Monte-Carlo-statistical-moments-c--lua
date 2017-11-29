//
// Created by Clément Lefebvre on 21.11.16.
//

#ifndef PCSC_MONTECARLO_RANDOMGENERATOR_H
#define PCSC_MONTECARLO_RANDOMGENERATOR_H

#include <random>
#include <chrono>


/// This is an abstract class used to get a random number following a certain distribution defined in the children


class RandomGenerator {
protected:
    std::default_random_engine generator;
public:
    /// Get a random number
    virtual double getRandomNumber() = 0;
    /// Method the manually set the seed of the random number generator
    void setSeed(double const &seed);

    virtual ~RandomGenerator();

};


#endif //PCSC_MONTECARLO_RANDOMGENERATOR_H
