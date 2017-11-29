//
// Created by Clément Lefebvre on 21.11.16.
//

#ifndef PCSC_MONTECARLO_READFUNCTION_H
#define PCSC_MONTECARLO_READFUNCTION_H

#include "Function.h"
#include <fstream>

/// Abstract class used to read a given function (Discrete or continuous) given by the user

class ReadFunction {
    public:
    ///Pure virtual method used to read a file and return a pointer on a function
    virtual Function* read(const std::string &filename) const = 0;

    virtual ~ReadFunction() {};
};


#endif //PCSC_MONTECARLO_READFUNCTION_H
