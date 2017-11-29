//
// Created by Vincent on 09/12/2016.
//

#ifndef PCSC_MONTECARLO_FUNCTIONALITYNOTAVAILABLEEXCEPTION_H
#define PCSC_MONTECARLO_FUNCTIONALITYNOTAVAILABLEEXCEPTION_H


#include "Exception.h"

/// This type of Exception is raised when the user has entered a parameter which doesn't correspond to a feature of the program
/**
 * It is used to inform the user about the parameter that causes the error
 */
class FunctionalityNotAvailableException : public Exception {
public:
    /// Constructor. Generic Tag should be used only when the functionality could not be interpreted
    FunctionalityNotAvailableException(const std::string &Problem, const std::string &Tag = "Functionality not available");
};


#endif //PCSC_MONTECARLO_FUNCTIONALITYNOTAVAILABLEEXCEPTION_H
