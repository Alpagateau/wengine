#ifndef GAME_HPP
#define GAME_HPP 
#include <unistd.h>
#include <thread>
#include <mutex>
#include "tiles.hpp"
#include "structs.hpp"

int loadTSI(std::string path, tilemap&);
int GameProcess();
int GameRender(
  tilemap& txtview,
  tilemap& qview,
  tilemap& imview,
  tileset& ts, 
  int screenWidth, 
  int screenHeight,
  std::string currentImg);
#endif
