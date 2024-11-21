#include "luapi.hpp"

extern std::mutex mtx;
extern bool CanRead, CanContinue;
extern std::string Message;

int LuaServer()
{
  sol::state lua;
  lua.open_libraries(
    sol::lib::base,
    sol::lib::io,
    sol::lib::math
  );
  lua["say"] = say;
  lua.script_file("sayings.lua");
  return 0;
}

void say(std::string msg)
{
  mtx.lock();
  //std::cout << "[LUA] " << msg << " sent" << std::endl;
  CanRead = true;
  CanContinue = false;
  Message = msg;
  mtx.unlock();
  while(!CanContinue)
  {
  }
}
