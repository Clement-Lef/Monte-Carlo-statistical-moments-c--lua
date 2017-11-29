//
// Created by Vincent on 09/12/2016.
//

#ifndef PCSC_MONTECARLO_FUNCTIONEXCEPTION_H
#define PCSC_MONTECARLO_FUNCTIONEXCEPTION_H


#include "Exception.h"

/// The type of Exception is raised when a function could not be evaluated properly.
/**
 * For instance, if a discrete function evaluation is asked in a point outside of its interval of definition, an instance
 * of this call will be thrown
 * It uses the standard members of the mother class Exception to bring to the user the cause of the error.
 */
class FunctionException : public Exception {
public:
    FunctionException(const std::string &Problem, const std::string &Tag = "FunctionEvaluationFailed");
};


#endif //PCSC_MONTECARLO_FUNCTIONEXCEPTION_H
