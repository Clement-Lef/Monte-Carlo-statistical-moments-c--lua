//
// Created by Clément Lefebvre on 03.12.16.
//

#include "MomentComputerManager.h"
#include "RandomUniform.h"
#include <iostream>
#include <sstream>
#include <cfloat>
#include "ReadDiscrete.h"
#include "ReadLua.h"
#include "RandomNormal.h"
#include "FunctionalityNotAvailableException.h"
#include "RandomExponential.h"
#include "FileFormatException.h"
#include "Custom_Util.h"


MomentComputerManager::~MomentComputerManager() {
    delete reader;
    delete randomGenerator;
    delete function;
}

// Set the Random Generator
void MomentComputerManager::setRandomGenerator() {
    if (config.distribution == "Uniform") {
        randomGenerator = new RandomUniform(config.domainLeftSide, config.domainRightSide);
    } else if (config.distribution == "Normal") {
        randomGenerator = new RandomNormal(config.mean, config.stddev);
    } else if (config.distribution == "Exponential") {
        randomGenerator = new RandomExponential(config.lambda);
    } else { // An error is thrown if the argument does not exist
        throw FunctionalityNotAvailableException("Random distribution \"" + config.distribution + "\" is not available",
                                                 "InvalidDistribution");
    }
}

// Set the seed of the random generator
void MomentComputerManager::setSeed() {
    randomGenerator->setSeed(config.randomSeed);
}

// Set the reader depending of the given function
void MomentComputerManager::setReader() {
    if (config.typeOfFunction == "Discrete") {
        reader = new ReadDiscrete;
    } else if (config.typeOfFunction == "Continuous") {
        reader = new ReadLua;
    } else {
        throw FunctionalityNotAvailableException("Function definition \"" + config.typeOfFunction + "\" is not available",
                                                 "InvalidFunctionType");
    }
}

// Set the function to evaluate
void MomentComputerManager::setFunction() {
    function = reader->read(config.functionFileName);
}

// Set the Monte Carlo simulator
void MomentComputerManager::setSimulator() {
    simulator = MCSimulator(config.numberOfEvaluationPoints, config.dimension,  randomGenerator, function);
    if (config.distribution == "Uniform") {
        simulator.setVolume(pow((config.domainRightSide-config.domainLeftSide),config.dimension));
    }
}

// Function to read the config file
void MomentComputerManager::readConfigFile(std::string const &filename) {

    std::ifstream configFile(filename.c_str());
    if (!configFile.is_open()) {
        throw (FileNotFoundException("The configuration file " + filename + " could not be open.", "configuration file"));
    }
    std::string tmp;
    std::string key; //String used to discard the first part of the line, before the argument


    //Type of function
    std::getline(configFile, key, '"');
    std::getline(configFile, config.typeOfFunction, '"');

    //Number of dimension
    std::getline(configFile, key, '"');
    std::getline(configFile, tmp, '"');
    config.dimension = Custom_Util::stringToUnsignedInt(tmp.c_str(), "Number of dimension", "configuration file");

    // For discrete Function, only dimension 1 is supported
    if (config.dimension > 1 && config.typeOfFunction == "Discrete") {
        throw FunctionalityNotAvailableException("Dimension \"" + Custom_Util::toString(config.dimension) + "\" is "
                                                 "not available for discrete function computations.", "TooHighDimension");
    }

    //Interpolation method
    std::getline(configFile, key, '"');
    std::getline(configFile, config.interpolation, '"');

    //Name of function file
    std::getline(configFile, key, '"');
    std::getline(configFile, config.functionFileName, '"');

    //Distribution
    std::getline(configFile, key, '"');
    std::getline(configFile, config.distribution, '"');

    //Inferior boundary of the domain of definition
    std::getline(configFile, key, '"');
    std::getline(configFile, tmp, '"');
    config.domainLeftSide = Custom_Util::stringToDouble(tmp.c_str(), "Domain inferior boundary", "configuration file");

    //Superior boundary of the domain of definition
    std::getline(configFile, key, '"');
    std::getline(configFile, tmp, '"');
    config.domainRightSide = Custom_Util::stringToDouble(tmp.c_str(), "Domain superior boundary", "configuration file");

    // Check if the integration domain is at least 10 * minimal available double precision
    // Otherwise throw exception to inform user
    if (config.domainRightSide - config.domainLeftSide < 10 * (DBL_MIN)) {
        std::ostringstream toString;
        toString << config.domainLeftSide;
        std::string l_side_string = toString.str();      toString.str("");
        toString << config.domainRightSide;
        std::string r_side_string = toString.str();      toString.str("");
        throw  FileFormatException("Invalid domain \"[" + l_side_string + ", " + r_side_string + "]\" for computation"
                                   , "TooSmallDomainInConfigFile","configuration file");
    }

    //Mean of Normal distribution
    std::getline(configFile, key, '"');
    std::getline(configFile, tmp, '"');
    config.mean = Custom_Util::stringToDouble(tmp.c_str(), "Mean of normal distribution", "configuration file");

    //Standard Deviation of normal distribution
    std::getline(configFile, key, '"');
    std::getline(configFile, tmp, '"');
    config.stddev = Custom_Util::stringToDouble(tmp.c_str(), "Standard deviation of normal distribution", "configuration file");

    //Lambda parameter of exponential distribution
    std::getline(configFile, key, '"');
    std::getline(configFile, tmp, '"');
    config.lambda = Custom_Util::stringToDouble(tmp.c_str(), "Lambda parameter of exponential distribution", "configuration file");

    //Seed of the random number generator
    std::getline(configFile, key, '"');
    getline(configFile, tmp, '"');
    config.randomSeed = Custom_Util::stringToDouble(tmp.c_str(), "Seed of random number generator", "configuration file");

    //Number of evaluation points
    std::getline(configFile, key, '"');
    std::getline(configFile, tmp, '"');
    config.numberOfEvaluationPoints = Custom_Util::stringToUnsignedInt(tmp.c_str(), "Number of evaluation points", "configuration file");

    //Number of simulations
    std::getline(configFile, key, '"');
    std::getline(configFile, tmp, '"');
    config.numberOfSimulations = Custom_Util::stringToUnsignedInt(tmp.c_str(), "Number of simulation", "configuration file");

    configFile.close();
}


//Constructor
MomentComputerManager::MomentComputerManager(std::string const &configFile) {
    readConfigFile(configFile);
    setRandomGenerator();
    setReader();
    setFunction();
    setSeed();
    setSimulator();
}

//Function used to compute the moments
std::vector<double> MomentComputerManager::computeMoments(unsigned int momentOrder) {
    std::vector<double> Moments(config.numberOfSimulations);
    for (unsigned int i = 0; i < config.numberOfSimulations; ++i) {
        Moments[i] = simulator.computeMoment(momentOrder, config.interpolation);
    }
    return Moments;
}

void MomentComputerManager::printMoments(std::vector<double> const &moments, std::string const &outputFileName) const {
    std::ofstream output(outputFileName.c_str());
    if (!output.is_open()) {
        throw FileNotFoundException("Impossible to write moments to file \"" + outputFileName + "\"", "WritingFile");
    }
    for (int i = 0; i < config.numberOfSimulations; ++i) {
        output << moments[i] << std::endl;
    }
    output.close();
}

//Print the configuration file in the terminal
void MomentComputerManager::printConfig(std::ostream &writer) const {
    writer << "Type of function : " << config.typeOfFunction << std::endl;
    if (config.typeOfFunction == "Discrete") {
        writer << "Interpolation method : " << config.interpolation << std::endl;
    }
    writer << "Dimension : " << config.dimension << std::endl;
    writer << "Function file name : " << config.functionFileName << std::endl;
    writer << "Random distribution : " << config.distribution << std::endl;
    if (config.distribution == "Uniform") {
        writer << "Domain left side : " << config.domainLeftSide << std::endl;
        writer << "Domain right side : " << config.domainRightSide << std::endl;
    }
    if (config.distribution == "Normal") {
        writer << "Mean : " << config.mean << std::endl;
        writer << "Standard deviation : " << config.stddev << std::endl;
    }
    if (config.distribution == "Exponential") {
        writer << "Lambda : " << config.lambda << std::endl;
    }
    writer << "Random seed : ";
    if ((int) config.randomSeed == 0) {
        writer << "none" << std::endl;
    } else {
        writer << config.randomSeed << std::endl;
    }
    writer << "Number of evaluation points : " << config.numberOfEvaluationPoints << std::endl;
    writer << "Number of simulations : " << config.numberOfSimulations << std::endl;
}

