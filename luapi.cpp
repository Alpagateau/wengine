#include "luapi.hpp"

extern std::mutex mtx;
extern Settings_t settings; 
extern int CanRead, Waiting; 
extern bool CanContinue, Terminate;
extern std::string Message;
extern std::vector<std::string> opts;
extern int choice;
extern std::string imgpath;

int LuaServer()
{
  sol::state lua;
  lua.open_libraries(
    sol::lib::base,
    sol::lib::io,
    sol::lib::os,
    sol::lib::math,
    sol::lib::package
  );
  
  std::cout << "[LUA] ==Loading Settings==" << std::endl;
  lua.script_file("settings.lua");
  Settings_t temps;
  temps.font = lua["Font"].get<std::string>();
  temps.fontSize = lua["FontSize"].get<float>();
  mtx.lock();
  settings = temps;
  settings.loaded = true;
  mtx.unlock();
  std::cout << "[LUA] ==Starting Scripts=="<<std::endl;
  lua["say"] = say;
  lua["ask"] = ask;
  lua["clr"] = clr;
  lua["loadImg"] = loadImg;
  lua.script_file("./index.lua");
  while(lua["State"]["fin"] != true)
  {
    if(Terminate)
    {
      lua["State"]["fin"] = true;
    }
    lua["NextState"]();
  }
  return 0;
}

void ask(const sol::table& pos)
{
  if(Terminate)
    return;
  mtx.lock();opts.clear();mtx.unlock();
  std::vector<sol::function> fs;
  for(const auto& pair: pos)
  {
    if(pair.second.is<sol::table>())
    {
      sol::table subt = pair.second.as<sol::table>();
      if(subt[1].is<std::string>())
      {
        //work with the string here
        std::string s = subt[1].get<std::string>();
        mtx.lock();
        opts.push_back(s);
        mtx.unlock();
      }
      if(subt[2].is<sol::function>())
      {
        //work with the associated function
        sol::function f = subt[2].get<sol::function>();
        fs.push_back(f);
      } 
    }
  }
  mtx.lock();
  CanContinue = false;
  CanRead = ASK;
  mtx.unlock();
  while(!CanContinue){}
  fs[choice]();
}

void say(std::string msg, float s)
{
  if(!Terminate){
    while(CanRead != NOTHING && CanRead > 2){}
    mtx.lock();
    CanRead = SAY;
    CanContinue = false;
    Message = msg;
    Waiting = (int)(s*10);
    mtx.unlock();
    while(!CanContinue && !Terminate){}
  }
}

void clr()
{
  mtx.lock();
  CanRead = CLR;
  mtx.unlock();
}

void loadImg(std::string path)
{
  if(Terminate){return;}
  mtx.lock();
  imgpath = path;
  mtx.unlock();
}
