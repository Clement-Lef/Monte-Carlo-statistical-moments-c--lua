//
// Created by Clément Lefebvre on 21.11.16.
//

#include "MCSimulator.h"
#include "FunctionalityNotAvailableException.h"

MCSimulator::MCSimulator() {}

MCSimulator::MCSimulator(unsigned int numberOfEvaluationPoints, unsigned int dimension, RandomGenerator* random, Function* function) {
	MCSimulator::numberOfEvaluationPoints = numberOfEvaluationPoints;
    MCSimulator::dimension = dimension;
	MCSimulator::random = random;
	MCSimulator::function = function;
    MCSimulator::volume = 1;
	MCSimulator::generateEvaluationPoints();
}

MCSimulator::~MCSimulator() {
}


void MCSimulator::generateEvaluationPoints() {
    evaluationPoints.clear();
	for (unsigned int i = 0; i < numberOfEvaluationPoints; ++i) { //Loop over all evaluations points
        std::vector<double> row;
        for (unsigned int j = 0; j < dimension; ++j) { //Loop over each dimension
            row.push_back(random->getRandomNumber()); //Fill a vector containing the coordinates of 1 point
        }
        evaluationPoints.push_back(row); //Add 1 point to the list of evaluations points
	}
}

double MCSimulator::computeMoment(int momentOrder, std::string const &evaluationMethod) {
    generateEvaluationPoints(); //Generate the evaluation points
    double moment = 0;
    for (int i = 0; i < numberOfEvaluationPoints; ++i) {

        moment += pow(function->eval(evaluationPoints[i],evaluationMethod),momentOrder); //Compute the monte carlo integral for the moment
    }
    return volume*moment/numberOfEvaluationPoints;
}


void MCSimulator::setVolume(double mVolume) {
    volume = mVolume;
}