#ifndef LUAPI_HPP
#define LUAPI_HPP 
#include <iostream>
#include <string>
#include <thread>
#include <mutex>

//Somehow, i only got it to build on windows like this....
#ifdef __linux__ 
  #include <unistd.h>
  #include <sol/sol.hpp>
#elif _WIN32
  #include <sol.hpp>
#endif

#define SOL_ALL_SAFTIES_ON 1

#include "structs.hpp"

int LuaServer();
void say(std::string);
void ask(const sol::table& pos);
void loadImg(std::string path);
#endif
