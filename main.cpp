#include <iostream>
#include <vector>

#include "raylib.h"
#include "tiles.hpp"
#include "luapi.hpp"
#include "structs.hpp"

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
    return 1;
  }
  tm.scale = settings.fontSize;
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "Console - Wiremole.exe");
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  
  bool r = CheckLua(L, luaL_dofile(L, "./index.lua" ));
  if(!r)
    return 1;
  loadTilesetCR(settings.font, ts, 16, 16);

  CState ConsoleState = PRINTER;
  while (!WindowShouldClose()) // TO CHANGE
  {
    switch(ConsoleState)
    {
      case PRINTER:
        {
          if(tm.toSay.size() > 0)
          {
            print(tm, tm.toSay.front(), 0, tm.maxLine + 1, WHITE);
            tm.toSay.pop();
          }
        }
        break;
      default:
        std::cout << "Should not be reached" << std::endl;
        break;
    }
    BeginDrawing();
      ClearBackground(BLACK);
      draw(tm, ts, 800, 450);
    EndDrawing();
  }

  CloseWindow();
  lua_close(L);

  return 0;
}
