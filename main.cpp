#include <iostream>
#include <thread>
#include <mutex>
#ifdef __linux__
  #include <unistd.h>
#elif _WIN32 
  #include <windows.h>
#endif
#include "game.hpp"
#include "luapi.hpp"

std::mutex mtx;
bool CanRead = false;
bool CanContinue = false;
std::string Message = "";

int main(void)
{ 
  std::cout << "====Starting LuaThread====" << std::endl; 
  std::thread lua_thread(LuaServer); 
  std::cout << "====Starting GameThread===" << std::endl;
  GameProcess();
  lua_thread.join();
  return 0;
}
