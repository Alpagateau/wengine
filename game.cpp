#include <iostream>
#include <sstream>
#include <raylib.h>
#include <fstream>
#include <cmath>
#include "game.hpp"
#include "tiles.hpp"

extern std::mutex mtx;
extern Settings_t settings;
extern int CanRead;
extern bool CanContinue, Terminate;
extern std::string Message;
extern std::vector<std::string> opts;
extern int choice;
extern std::string imgpath;

int GameProcess()
{
  int screenWidth = 800;
  int screenHeight = 450; 
  
  std::string currentImg = "";

  tileset ts;
  tilemap txtview;
  tilemap qview;
  tilemap imview;
  txtview.scale = 20.0f; 
  bool l = false;
  while(!settings.loaded)
  {
    if(!l){
    std::cout << "Waiting for settings" << std::endl;
      l=true;
    }
  }

  SetConfigFlags(
    //FLAG_WINDOW_RESIZABLE | 
    FLAG_MSAA_4X_HINT
  );
  
  InitWindow(
    screenWidth, 
    screenHeight, 
    "Console - Wiremole.exe");
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second 
  //loadTilesetCR("RDE_vector_48x48.png", ts, 16, 16);
  loadTilesetCR(settings.font, ts, 16, 16);
  txtview.scale = settings.fontSize;
  txtview.margin = 1;
  qview.scale = settings.fontSize;
  imview.scale = settings.fontSize;
  //tiles::write(txtview, "Hello from :DD2222:[C++]", 0, 0, WHITE);
  //tiles::write(qview, "Test of qview", 0, 0, WHITE); 
  imview.posx = 25;
  imview.posy = 0;
  double curTime = GetTime();
  while (!WindowShouldClose()) // TO CHANGE
  {
    mtx.lock();
    switch(CanRead){
      case SAY:
      if(Message != "")
      {
        tiles::print(txtview, 
            Message, 0, 
            txtview.maxLine+1, 
            WHITE);
        Message = "";
      }
      CanRead = NOTHING;
      break;

      case ASK: 
        if(opts.size() > 0)
        {
          if(choice < 0)
            choice = opts.size()-1;
          if(choice > opts.size()-1)
            choice = 0;
          qview.tiles.clear();
          qview.maxLine = -1;
          for(int i = 0; i < opts.size(); i ++)
          {
            tiles::write(
              qview, 
              (i==choice?"<rightarrow>":" ")+opts[i], 
              0, i, 
              (i==choice)?BLUE:WHITE);
          }
        }
      break;
    }
    mtx.unlock();
    
    if(imgpath != currentImg)
    {
      currentImg = imgpath;
      loadTSI(imgpath, imview);
    }
    //Draw on the screen hehe
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight(); 
    //place textview at the bottom of the screen 
    int npy = (int)std::floor((float)screenHeight/txtview.scale)-(txtview.maxLine+1);
    if(CanRead == ASK)
    {
      npy -= opts.size();
    }
    int nop = (int)std::floor((float)screenHeight/qview.scale)-(qview.maxLine+1);
    txtview.posy = npy;
    qview.posy = nop;
    BeginDrawing();
      ClearBackground(BLACK);
      tiles::draw(txtview, ts, screenWidth, screenHeight);
      if(CanRead == ASK){tiles::draw(qview, ts, screenWidth, screenHeight);}
      if(currentImg != ""){tiles::draw(imview, ts, screenWidth, screenHeight);}
    EndDrawing();

    //-------
    //INPUTS 
    //-------
    
    if(IsKeyPressed(KEY_UP))
      choice++;
    if(IsKeyPressed(KEY_DOWN))
      choice--;
    
    if(!CanContinue && CanRead == ASK)
    {
      if(IsKeyDown(KEY_ENTER))
      {
        mtx.lock();
        CanContinue = true;
        CanRead = NOTHING;
        mtx.unlock();
        curTime = GetTime();
      }
    }

    if(GetTime()-curTime > 2 && CanRead != ASK)
    {
      curTime = GetTime();
      mtx.lock();
      CanContinue = true;
      mtx.unlock();
    }
  }

  CloseWindow();
  mtx.lock();
  Terminate = true;
  mtx.unlock();

  return 0;
}


int loadTSI(std::string path, tilemap& tm)
{
  std::string myText;
  std::ifstream readim(path);
  while(getline(readim, myText))
  {
    tile t;
    std::stringstream ss;
    ss << myText;
    std::string temp;
    getline(ss,temp,' ');
    t.posx = std::stoi(temp);
    getline(ss,temp,' ');
    t.posy = std::stoi(temp);
    getline(ss,temp,' ');
    t.val = std::stoi(temp);
    
    getline(ss,temp,' ');
    t.c.r = (char)std::stoi(temp);
    getline(ss,temp,' ');
    t.c.g = (char)std::stoi(temp);
    getline(ss,temp,' ');
    t.c.b = (char)std::stoi(temp);
    tm.tiles.push_back(t);
  }
  return 1;
}
