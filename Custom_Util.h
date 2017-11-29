//
// Created by Vincent on 13/12/2016.
//

#ifndef PCSC_MONTECARLO_CUSTOM_UTIL_H
#define PCSC_MONTECARLO_CUSTOM_UTIL_H

#include <iostream>
#include <sstream>


///This class provides useful methods used in the program (eg robust conversion from string to double method)

class Custom_Util {
private:

    /**
     * Helper function to read a double value stored in a string.
     * It uses std::strtod but raises Exceptions when the conversion fails
     * @param str   : string to convert to double
     * @return       str interpreted as a double
     */
    static double stringToDouble(std::string const &str);

    /**
 * Helper function to read an unsigned int value stored in a string.
 * It uses std::strtoI but raises Exceptions when the conversion fails
 * @param str   : string supposeddly containing a double value
 * @return       str interpreted as an unsigned int
 */
    static unsigned int stringToUnsignedInt(std::string const &str);


public:
    /**
     * Provides the result of stringtoDouble (private), but throws an exception with inputName in its
     * Problem field, and location in its location field (to help inform user)
     * @param str           : String to convert
     * @param inputName     : Name of the parameter actually converted from string representation to double
     * @return               On success the value contained in str, as a double.
     */
    static unsigned int stringToUnsignedInt(std::string const &str, std::string const &inputName, std::string const &location);

    /**
     * Provides the result of stringtoUnsignedInt (private), but throws an exception with inputName in its
     * Problem field, and location in its location field (to help inform user)
     * @param str           : String to convert
     * @param inputName     : Name of the parameter actually converted from string representation to double
     * @return               On success the value contained in str, as a double.
     */
    static double stringToDouble(std::string const &str, std::string const &inputName, std::string const &location);

    /**
     * Return the argument (used with numbers in this project) interpreted as a string.
     * The << operator for ostringstream must be overwritten for the argument.
     * @tparam T        : type of the argument to read as a string
     * @param number    : value of the argument
     * @return           Argument written in a std::string.
     */
    template<typename T> static std::string toString(T const &number) {
        std::ostringstream toString;
        toString << number;
        return toString.str();
    };

};


#endif //PCSC_MONTECARLO_CUSTOM_UTIL_H
