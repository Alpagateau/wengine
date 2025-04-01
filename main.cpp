#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#ifdef __linux__
  #include <unistd.h>
#elif _WIN32 
  #include <windows.h>
#endif
#include "game.hpp"
#include "luapi.hpp"

std::mutex mtx;
//int State = NOTHING, Waiting = 0;
bool LuaRun = false;
bool Terminate = false;
Settings_t settings;
Event_t event;
//std::string Message = "";
//std::vector<std::string> opts;
//int choice;
//std::string imgpath;

int main(int argc, char* argv[])
{ 
  std::cout << "====Starting LuaThread====" << std::endl; 
  std::thread lua_thread(LuaServer); 
  std::cout << "====Starting GameThread===" << std::endl;
  GameProcess(argc > 1);
  mtx.lock();
  Terminate = true;
  LuaRun = true;
  mtx.unlock();
  lua_thread.join();
  std::cout << "C'est la fin les amis" << std::endl;
  return 0;
}
