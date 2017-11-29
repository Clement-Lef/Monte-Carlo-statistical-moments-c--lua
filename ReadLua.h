//
// Created by Clément Lefebvre on 21.11.16.
//

#ifndef PCSC_MONTECARLO_READLUA_H
#define PCSC_MONTECARLO_READLUA_H

#include "ReadFunction.h"
#include "FileNotFoundException.h"


/// Class used to read a Lua file to get a continuous function


class ReadLua : public ReadFunction {
public:
    /**
     * Function used to read a Lua file
     * @param filename : lua file name
     * @return a pointer on a function.
     */
    Function* read(const std::string &filename) const;

};


#endif //PCSC_MONTECARLO_READLUA_H
