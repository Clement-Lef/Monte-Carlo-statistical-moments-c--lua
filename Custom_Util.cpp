//
// Created by Vincent on 13/12/2016.
//

#include "Custom_Util.h"
#include "FileFormatException.h"

#include <limits.h>
#include <cstdlib>
#include <cmath>


double Custom_Util::stringToDouble(std::string const &str) {
    // Pointer which will be set by std::strtod to the first char after the double in the string.
    // It is used to check if the conversion was successful.
    char *end_ptr;
    // If the conversion is successful, number is the number contained in str.
    double number = std::strtod(str.c_str(), &end_ptr);
    if (*end_ptr != *str.end()) {
        // Number doesn't correspond to the conversion of the entire string.
        // Throw Exception to inform user.
        throw FileFormatException("\"" + str + "\" could not be interpreted as a double value.", "TypeMissMatch", "");
    } else if ((number == HUGE_VAL) || (std::isnan(number)) || (!std::isfinite(number)))  {
        // Condition 1 : number is out of range of double
        // Condition 2 : number is NAN
        // Condition 3 : number is INF
        // In each case : throw exception to inform user.
        throw FileFormatException("\"" + str + "\" is not in range for type double used in the simulation.", "OutOFRange", "");
        // Note that is number is rounded in case of underflow.
    }
    return number;
}

double Custom_Util::stringToDouble(std::string const &str, std::string const &inputName, std::string const &location) {
    try {
        return Custom_Util::stringToDouble(str);
    } catch (FileFormatException &e) {
        // Add the name of parameter causing the exception to the exception problem.
        e.setProblem(inputName + " " + e.getProblem());
        // Add the location of the error
        e.setLocation(location);
        // Re-throw the error
        throw ;
    }
}


unsigned int Custom_Util::stringToUnsignedInt(std::string const &str) {
    // Pointer which will be set by std::strtoI to the first char after the long integer in the string.
    // It is used to check if the conversion was successful.
    char *end_ptr;
    // If the conversion is successful, number is the number contained in str.
    // strtouI returns a long unsigned int
    long int number = std::strtol(str.c_str(), &end_ptr,10);
    if ((number == HUGE_VAL) || (number > UINT_MAX)) {
        // Condition 1 : number is out of rang of type unsigned long int
        // Condition 2 : check for overflow before converting from unsigned long int to unsigned int
        // Throw Exception to inform user in case of overflow.
        throw FileFormatException("\"" + str + "\" is out of range for type unsigned long int used in simulation.", "OutOFRange","");
    }
    if ((*end_ptr != *str.end()) || number < 0) {
        // Number doesn't correspond to the conversion of the entire string.
        // Throw Exception to inform user
        throw FileFormatException("\"" + str + "\" could not be interpreted as a positive integer value.", "TypeMissMatch","");
    }
    return (unsigned int) number;
}

unsigned int Custom_Util::stringToUnsignedInt(std::string const &str, std::string const &inputName, std::string const &location) {
    try {
        return Custom_Util::stringToUnsignedInt(str);
    } catch (FileFormatException &e) {
        // Add the name of parameter causing the exception to the exception problem
        e.setProblem(inputName + " " + e.getProblem());
        // Add the location of the error
        e.setLocation(location);
        // Re-throw the error
        throw ;
    }
}
