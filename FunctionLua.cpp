//
// Created by Clément Lefebvre on 21.11.16.
//

#include <iostream>
#include "FunctionLua.h"


FunctionLua::FunctionLua(lua_State* newL) {
    L = newL;
}



double FunctionLua::eval(std::vector<double> const& x, const std::string &interpolationMethod) const{

    //Get the function in the lua file
    lua_getglobal(L, "func");

    //Push the evaluation point on top of the stack
    lua_createtable(L,x.size(),0); //Create a table at the top of the stack
    int indexTable = lua_gettop(L); //Get the index of the table in the stack
    int index = 0;

    while (index < x.size()) {
        lua_pushnumber(L,x[index]);
        lua_rawseti(L, indexTable, index+1); //Fill the table with the coordinate to evaluate
        ++index;
    }

    /* call the function with 1 arguments (table), return 1 result (double)*/
    lua_call(L, 1, 1);

    double value = 0;
    /* get the result */
    value = lua_tonumber(L, -1);
    lua_pop(L, 1); //Delete the result from the stack

    return value;

}

FunctionLua::~FunctionLua() {
    lua_close(L);
}


