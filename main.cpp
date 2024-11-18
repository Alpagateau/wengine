#include <iostream>
#include <vector>

#include "raylib.h"
#include "tiles.hpp"
#include "luapi.hpp"

int main(void)
{
  const int screenWidth = 800;
  const int screenHeight = 450; 
  
  tileset ts;
  tilemap tm;
  registerTilemap(tm);
  tm.scale = 20.0f;
  
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  registerAll(L); 
  Settings_t settings = loadSettings(L, "settings.lua");
  if(settings.fontSize < 0)
  {
    std::cout << "coulnd't load the settings at all" << std::endl;
  }
  tm.scale = settings.fontSize;
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "Console - Wiremole.exe");
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  loadTilesetCR(settings.font, ts, 16, 16);
  //loadTilesetCR("Alloy_curses_12x12.png" ,ts, 16, 16);
  //loadTilesetCR("RDE_vector_48x48.png", ts, 16, 16);
  /* 
  print(tm, "Hello World!", 0, 0, WHITE);
  print(tm, "Hello from raylib ! <smiley>", 0, 1, WHITE);
  print(tm, "Hey, this is \na multiline:FF0000: string", 0, 2, WHITE);
  print(tm, 
        "<ndsn><ndnd><ndnd><ndnd><nnsd>\n<snsn><25><50><75><snsn>\n<sdnn><ndnd><ndnd><ndnd><snnd>",
        5, 5, WHITE);
  */
  //---------------------------------------------------
  // Main game loop
  while (!WindowShouldClose()) // TO CHANGE
  {
    BeginDrawing();
      ClearBackground(BLACK);
      draw(tm, ts, 800, 450);
    EndDrawing();
  }

  CloseWindow();
  lua_close(L);

  return 0;
}
