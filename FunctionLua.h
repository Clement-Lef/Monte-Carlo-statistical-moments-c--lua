//
// Created by Clément Lefebvre on 21.11.16.
//

#ifndef PCSC_MONTECARLO_FUNCTIONLUA_H
#define PCSC_MONTECARLO_FUNCTIONLUA_H

#include <lua.hpp>
#include "Function.h"


/// Class children of Function, used to represent a Continuous function with a Lua function
class FunctionLua : public Function {
private:
    lua_State *L;

public:
    /// Virtual destructor used to close the Lua state
    virtual ~FunctionLua();

public:
    /// Constructor which takes a Lua state from the ReaderContinuous class
    FunctionLua(lua_State* newL);
    /**
     * Function used to evaluate the lua function
     * @param x is the coordinates of the evalutions points in dimension N.
     * @param interpolationMethod is empty
     * @return evaluated number
     */
    double eval(std::vector<double> const& x, const std::string &interpolationMethod) const;
};


#endif //PCSC_MONTECARLO_FUNCTIONLUA_H
