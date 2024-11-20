#include <iostream>
#include <raylib.h>
#include "game.hpp"
#include "tiles.hpp"

int GameProcess(int p1[2], int p2[2])
{
  int screenWidth = 800;
  int screenHeight = 450; 
  
  tileset ts;tilemap tm;
  tm.scale = 20.0f;
  //tm.scale = settings.fontSize;
  SetConfigFlags(
    FLAG_WINDOW_RESIZABLE | 
    FLAG_MSAA_4X_HINT
  );
  InitWindow(
    screenWidth, 
    screenHeight, 
    "Console - Wiremole.exe");
  SetTargetFPS(30); // Set our game to run at 60 frames-per-second 
  loadTilesetCR("RDE_vector_48x48.png", ts, 16, 16);
  tiles::write(tm, "Hello from :DD2222:[C++]", 0, 0, WHITE);
  double curTime = GetTime();
  while (!WindowShouldClose()) // TO CHANGE
  {
    char ch;
    std::string msg;
    //try to read from the lua server eheh
    while(read(p2[0], &ch, 1) > 0)
    {
      if(ch != 0)
        msg += ch;
    }
    if(msg != "")
    {
      tiles::write(tm, 
            msg, 
            0, 
            tm.maxLine+1, 
            WHITE);
    }
    //Draw on the screen hehe
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight(); 
    BeginDrawing();
      ClearBackground(BLACK);
      tiles::draw(tm, ts, screenWidth, screenHeight);
    EndDrawing();


    if(GetTime()-curTime > 2)
    {
      curTime = GetTime();
      int x = 1;
      write(p1[1], &x, sizeof(int));
    }
  }

  CloseWindow();

  return 0;
}
