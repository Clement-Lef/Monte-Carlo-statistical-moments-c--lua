//
// Created by Clément Lefebvre on 03.12.16.
//

#ifndef PCSC_MONTECARLO_MOMENTCOMPUTERMANAGER_H
#define PCSC_MONTECARLO_MOMENTCOMPUTERMANAGER_H


#include "ReadFunction.h"
#include "MCSimulator.h"


/// This class is used to manage the Monte Carlo Simulation of statistical moments
/**
 * All parameters of the simulation are stored inside, and the output is also controlled by this class
 */
class MomentComputerManager {

private:
    /// Reader to create function according to user specifications
    ReadFunction* reader;
    /// Monte Carlo simulator
    MCSimulator simulator;
    /// Random Generator to create random integration points
    RandomGenerator* randomGenerator;
    /// Function to evaluate
    Function* function;


    ///Struct to save the config file informations
    struct {
        std::string typeOfFunction;
        unsigned int dimension;
        std::string interpolation;
        std::string functionFileName;
        std::string distribution;
        double domainLeftSide;
        double domainRightSide;
        double mean;
        double stddev;
        double lambda;
        double randomSeed;
        unsigned int numberOfEvaluationPoints;
        unsigned int numberOfSimulations;
    } config;


    /// Private method used by the constructor to create the random generator
    void setRandomGenerator();
    /// Private method used by the constructor to create the reader
    void setReader();
    /// Private method used by the constructor to create the function to evaluate
    void setFunction();
    /// Private method used by the constructor to initialize the Monte Carlo Simulator
    void setSimulator();
    /// Private method used by the constructor to read a configuration file given by the user
    void readConfigFile(std::string const &filename);


public:
    /// Method used to define the seed of the random number generator
    void setSeed();

    /// Computes "numberOfSimulations" times the "momentOrder" moment of the class member function
    std::vector<double> computeMoments(unsigned int momentOrder);

    /**
     * Method used to output the computed moments into a text file
     * @param moments : computed moments
     * @param outputFileName : name of the output file
     */
    void printMoments(std::vector<double> const &moments, std::string const &outputFileName) const;



    /// Method used to print the config file
    void printConfig(std::ostream& writer) const;

    ///Constructor
    MomentComputerManager(std::string const &configFile);

    ///Destructor
    virtual ~MomentComputerManager();

};


#endif //PCSC_MONTECARLO_MOMENTCOMPUTERMANAGER_H
