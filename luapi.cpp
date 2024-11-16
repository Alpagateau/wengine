#include "luapi.hpp"

bool CheckLua(lua_State *L, int r)
{
  if(r != LUA_OK)
  {
    std::string errmsg = lua_tostring(L, -1);
    std::cout << errmsg << std::endl;
    return false;
  }
  return true;
}

Settings_t loadSettings(lua_State* L,std::string path)
{
  Settings_t s;
  //font size
  bool r = CheckLua(L, luaL_dofile(L, path.c_str()));
  if(r)
  {
    lua_getglobal(L, "Font");
    if(lua_isstring(L, -1))
    {
      std::string fontname = lua_tostring(L, -1);
      std::cout << "Font : " << fontname << std::endl;
      s.font = fontname;
      //check if font exists
    }
    lua_getglobal(L, "FontSize");
    if(lua_isnumber(L, -1))
    {
      float fontsize = (float)lua_tonumber(L, -1);
      std::cout << "FontSize : " << fontsize << std::endl;
      s.fontSize = fontsize;
      //check if font exists
    }
  }
  return s;
}
