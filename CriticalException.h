//
// Created by Vincent on 10/12/2016.
//

#ifndef PCSC_MONTECARLO_CRITICALEXCEPTION_H
#define PCSC_MONTECARLO_CRITICALEXCEPTION_H


#include "Exception.h"

/// CriticalException is thrown when the program needs to abort.
/**
 * This type of Exception is thrown when the program can not deal with an error.
 * It uses the Problem and Tag field of class Exception to inform user of the error
 * Tag field is here used to print the cause of the problem to the user, so it is more descriptive than in other
 * Exceptions classes where the tag field is used for internal recognition of the errors.
 */
class CriticalException : public Exception {
public:
    /**
     * CriticalException is thrown when the program needs to abort.
     * The constructors thus displays the cause of the error to the user on the argument stream
     * Default parameters correspond to a Exceptions which cause could not be determined
     * @param ErrorStream   : is used to print Problem and Tag to user
     * @param Problem       : Description of the Problem causing the abortion
     * @param Tag           : Cause of the problem
     */
    CriticalException(std::ostream& ErrorStream, std::string const &Problem = "Unexpected error occurred",
                      std::string const &Tag = "Unknown error");
};


#endif //PCSC_MONTECARLO_CRITICALEXCEPTION_H
