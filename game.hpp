#ifndef GAME_HPP
#define GAME_HPP 
#include <unistd.h>
#include <thread>
#include <mutex>
#include "tiles.hpp"
#include "structs.hpp"
int loadTSI(std::string path, tilemap&);
int GameProcess();
#endif
