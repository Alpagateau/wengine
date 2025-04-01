#ifndef GAME_HPP
#define GAME_HPP 
#include <unistd.h>
#include <thread>
#include <mutex>
#include "tiles.hpp"
#include "structs.hpp"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

int loadTSI(std::string path, tilemap&);
int GameProcess(bool);
int GameRender();
#endif
