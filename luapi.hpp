#ifndef LUAPI_HPP
#define LUAPI_HPP 

#include <iostream>
#include <string>

extern "C"
{
#include "lua54/lua.h"
#include "lua54/lauxlib.h"
#include "lua54/lualib.h"
}

#include "structs.hpp"

bool CheckLua(lua_State*L, int r);
Settings_t loadSettings(lua_State*,std::string);

#endif
