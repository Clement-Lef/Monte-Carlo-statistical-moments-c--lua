//
// Created by Clément Lefebvre on 21.11.16.
//

#ifndef PCSC_MONTECARLO_MCSIMULATOR_H
#define PCSC_MONTECARLO_MCSIMULATOR_H

#include "RandomGenerator.h"
#include "Function.h"
#include <vector>

/// This class handles the computation of the moments of a function

/**
 * The integration points are randomly obtained through the RandomGenerator member of the class
 * The RandomGenerator can provide different points distribution through polymorphism
 */

class MCSimulator {
private:
	/// Number of randomly chosen points over the integration interval
	unsigned int numberOfEvaluationPoints;

    /// Dimesion of the function to evaluate
    unsigned int dimension;

	/// Volume of the integration domain
	double volume;

	/// Table of points used for the integration (obtained randomly)
	std::vector<std::vector <double > > evaluationPoints;

	/// Generator of random points for integration
	RandomGenerator* random;

	/// Function whose moments are to be computed
	Function* function;


	/// Uses the RandomGenerator to compute the integration points
	void generateEvaluationPoints();



public:

    MCSimulator();
	/** Constructor arguments :
	 *  the integration interval end points and the number of integration points
	 *  The RandomGenerator to generate the integration points
	 *  The function which moments are to be computed
	 */
	MCSimulator(unsigned int numberOfEvaluationPoints, unsigned int dimension, RandomGenerator* random, Function* function);
	~MCSimulator();



    /** Computes the moment of order "momentOrder" of the class member function
    *  The integration interval is given by the class member leftSide and rightSide
    *  The integration points are stored in the class member evaluationPoints
    */
    double computeMoment(int momentOrder, std::string const &evaluationMethod = "");


	void setVolume(double volume);


};

#endif //PCSC_MONTECARLO_MCSIMULATOR_H
