//
// Created by Clément Lefebvre on 21.11.16.
//

#include "ReadLua.h"
#include "FunctionLua.h"


Function* ReadLua::read(const std::string &filename) const {


    /* the Lua interpreter */
    lua_State *L = luaL_newstate();

    /* load Lua base libraries */
    luaL_openlibs(L);

    int error;
    /* load the script and return the error "1" if the file is not found */
    error = luaL_dofile(L, filename.c_str());


    if (error == 1) {
        throw FileNotFoundException("The file \"" + filename + "\" could not be interpreted as a lua function.\n"
                                    "Possibility : missing file or syntax error in file", "LuaFileReadingFailed");
    }

    Function* f = new  FunctionLua(L);
    return f;
}



