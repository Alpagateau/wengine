#include "luapi.hpp"

extern std::mutex mtx;
extern Settings_t settings; 
extern Event_t event;
//extern int CanRead, Waiting; 
extern bool LuaRun, Terminate;
//extern std::string Message;
//extern std::vector<std::string> opts;
//extern int choice;
//extern std::string imgpath;

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
  temps.shader = lua["Shader"].get<bool>();
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
  while(lua["State"]["fin"] != true && !Terminate)
  {
    if(Terminate)
    {
      lua["State"]["fin"] = true;
    }
    else{
      lua["NextState"]();
    }
  }
  return 0;
}

bool ask(const sol::table& pos)
{
  //std::cout << "Tried asking" << std::endl;
  if(Terminate)
  {
    return false;
  }
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
        event.type = ASK;
        event.msg = s;
        event.data = 9;
        mtx.unlock();
        while(event.type == ASK){}
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
  event.type = ASK;
  event.msg = "";
  event.data = 0;
  mtx.unlock();
  mtx.lock();
  LuaRun = false;
  event.type = WAIT;
  mtx.unlock();
  while(!LuaRun && !Terminate && event.type != RESPONSE)
  {}
  std::cout << "Validated by [LUA]" << std::endl; 
  int temp_data = event.data;
  mtx.lock();
  event.data = 0; 
  event.msg = "";
  event.type = NOTHING;
  mtx.unlock();
  if(!Terminate)
    fs[temp_data](); 
  //std::cout << "[C++] End of SAY" << std::endl;
  return true;
}

void say(std::string msg, float s)
{
  if(!Terminate){
    while(event.type != NOTHING && !Terminate){}
    mtx.lock();
    event.type = SAY;
    LuaRun = false;
    event.msg = msg;
    mtx.unlock();
    while(event.type != NOTHING){}
    mtx.lock();
    event.msg = "";
    event.data = (int)(s*10);
    event.type = WAIT;
    mtx.unlock();
    while(!LuaRun && !Terminate){}
  }
}

void clr()
{
  mtx.lock();
  event.type = CLR;
  event.data = 0;
  event.msg = "";
  mtx.unlock();
}

void loadImg(std::string path)
{
  if(Terminate){return;}
  mtx.lock();
  event.msg = path;
  event.type = IMG;
  event.data = 0;
  mtx.unlock();
}
