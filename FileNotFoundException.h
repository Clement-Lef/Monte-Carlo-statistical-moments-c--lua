//
// Created by Vincent on 05/12/2016.
//

#ifndef PCSC_MONTECARLO_FILENOTFOUNDEXCEPTION_H
#define PCSC_MONTECARLO_FILENOTFOUNDEXCEPTION_H


#include "Exception.h"


///This type of Exception is thrown when the program could not find a file indicated by the user.
/**
 * It uses the inherited members of Exception to bring up to the user the information about the file.
 */
class FileNotFoundException : public Exception {
public:
    /// Constructor : default parameter for Tag is FileNotFound, but it should be used with a more precise Tag if possible
    FileNotFoundException(std::string const &Problem, std::string const &Tag = "FileNotFound");
};


#endif //PCSC_MONTECARLO_FILENOTFOUNDEXCEPTION_H
