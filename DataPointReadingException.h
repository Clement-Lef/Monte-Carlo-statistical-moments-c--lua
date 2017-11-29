//
// Created by Vincent on 05/12/2016.
//

#ifndef PCSC_MONTECARLO_DATAPOINTREADINGEXCEPTION_H
#define PCSC_MONTECARLO_DATAPOINTREADINGEXCEPTION_H


#include <cstddef>
#include "Exception.h"

/// This exception is thrown when an error happens while reading the data points defining a discrete function.
/**
 * Apart of the members inherited from Exception, it contains a size_t which will be initialised with the index of the
 * problematic data point in the data points vector.
 */
class DataPointReadingException : public Exception {
private:
    /// Index of the problematic data point in the data point vector in readDiscrete.
    size_t indexOfProblematicDataPoint;
public:
    /// Constructor : initialise all parameters. Default error is to have multiple times the same value of x ( in data points (x,f(x)))
    DataPointReadingException(std::string const &Problem, size_t indexOfProblematicDataPoint, std::string const &Tag = "Twice same data point");

    /// getter for the index : used to inform the user or handle the issue.
    size_t getIndexOfProblematicDataPoint() const;
};


#endif //PCSC_MONTECARLO_DATAPOINTREADINGEXCEPTION_H
