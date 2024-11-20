#ifndef LUAPI_HPP
#define LUAPI_HPP 
#include <unistd.h>
#include <iostream>
#include <string>
#include <sol/sol.hpp>
#define SOL_ALL_SAFTIES_ON 1

int LuaServer(int[2], int[2]);
void say(std::string);
#endif
