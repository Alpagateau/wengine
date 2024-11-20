#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include "game.hpp"
#include "luapi.hpp"

int main(void)
{ 
  int p1[2]; // Game sends : lua receives
  int p2[2]; // Lua sends : Game receives 
  if(pipe(p1) == -1) {return 1;}
  if(pipe(p2) == -1) {return 1;}
  
  if(fcntl(p2[0], F_SETFL, O_NONBLOCK) < 0)
    {return 3;}

  int pid = fork();
  if(pid == -1) {return 2;}
  if(pid == 0)
  {
    close(p2[0]);
    close(p1[1]);
    LuaServer(p1, p2);
    close(p2[1]);
    close(p1[0]);
  }
  else 
  {
    close(p1[0]);
    close(p2[1]);
    GameProcess(p1, p2);
    close(p1[1]);
    close(p2[0]);
  }
  return 0;
}
