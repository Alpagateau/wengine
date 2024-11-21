#include <iostream>
#include <raylib.h>
#include "game.hpp"
#include "tiles.hpp"

extern std::mutex mtx;
extern bool CanRead, CanContinue;
extern std::string Message;

int GameProcess()
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
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second 
  loadTilesetCR("RDE_vector_48x48.png", ts, 16, 16);
  tiles::write(tm, "Hello from :DD2222:[C++]", 0, 0, WHITE);
  double curTime = GetTime();
  while (!WindowShouldClose()) // TO CHANGE
  {
    mtx.lock();
    if(CanRead){
      if(Message != "")
      {
        tiles::write(tm, 
            Message, 
            0, 
            tm.maxLine+1, 
            WHITE);
        Message = "";
      }
      CanRead = false;
    }
    mtx.unlock();
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
      mtx.lock();
      CanContinue = true;
      mtx.unlock();
    }
  }

  CloseWindow();

  return 0;
}
