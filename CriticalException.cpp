//
// Created by Vincent on 10/12/2016.
//

#include "CriticalException.h"

CriticalException::CriticalException(std::ostream &ErrorStream, const std::string &Problem, const std::string &Tag)
: Exception(Problem,Tag)
{
    // Display the cause for the error to user
    ErrorStream.flush();
    ErrorStream << "Critical error occurred --- Simulation aborted \n";
    ErrorStream << Tag << " : " << Problem << "\n";
    ErrorStream.flush();
}
