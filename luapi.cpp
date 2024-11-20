#include "luapi.hpp"

int* l2g; 
int* g2l;

int LuaServer(int p1[2], int p2[2])
{
  l2g = p2;
  g2l = p1;
  sol::state lua;
  lua.open_libraries(
    sol::lib::base,
    sol::lib::math
  );
  lua["say"] = say;
  lua.script_file("sayings.lua");
  return 0;
}

void say(std::string msg)
{
  std::cout 
    << "[LUA] " << msg << " sent" << std::endl;
  write(l2g[1], msg.c_str(), msg.size()+1);
  int r;
  while(read(g2l[0], &r, sizeof(int)) < 0)
  {
  }
}
