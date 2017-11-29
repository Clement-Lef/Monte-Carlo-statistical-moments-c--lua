//
// Created by Vincent on 05/12/2016.
//

#ifndef PCSC_MONTECARLO_FILEFORMATEXCEPTION_H
#define PCSC_MONTECARLO_FILEFORMATEXCEPTION_H


#include "Exception.h"
/// This Exception are thrown when the program could not interpret the content of a file.
/**
 * Apart from inherited members, it contains an additionnal string "location" which is used to bring up to the user
 * the file which causes the error
 */
class FileFormatException : public Exception {
private:
    /// location should be initialised with the location of the error (eg Configuration file, function file...)
    std::string location;
public:
    /// Constructor : all members should be initialised for correct operation
    FileFormatException(std::string const &Problem, std::string const &Tag, const std::string &location);

    /// Setter for the location
    void setLocation(const std::string &location);
    /// Getter for the location
    const std::string &getLocation() const;
};


#endif //PCSC_MONTECARLO_FILEFORMATEXCEPTION_H
