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
int CanRead = NOTHING, Waiting = 0;
bool CanContinue = false;
bool Terminate = false;
Settings_t settings;
std::string Message = "";
std::vector<std::string> opts;
int choice;
std::string imgpath;

int main(void)
{ 
  std::cout << "====Starting LuaThread====" << std::endl; 
  std::thread lua_thread(LuaServer); 
  std::cout << "====Starting GameThread===" << std::endl;
  GameProcess();
  mtx.lock();
  Terminate = true;
  CanContinue = true;
  mtx.unlock();
  lua_thread.join();
  std::cout << "C'est la fin les amis" << std::endl;
  return 0;
}
