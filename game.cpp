#include <iostream>
#include <sstream>
#include <raylib.h>
#include <fstream>
#include <cmath>
#include "game.hpp"
#include "tiles.hpp"

extern std::mutex mtx;
extern Settings_t settings;
extern int CanRead, Waiting;
extern bool CanContinue, Terminate;
extern std::string Message;
extern std::vector<std::string> opts;
extern int choice;
extern std::string imgpath;

int GameProcess()
{
  int screenWidth = 1000;
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
  //SetTraceLogLevel(LOG_INFO | LOG_WARNING); 
  InitWindow(
    screenWidth, 
    screenHeight, 
    "Console - Wiremole.exe");
  InitAudioDevice();
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second 
  
  //Load sounds
  Sound blipt = LoadSound("./res/blipt.wav");
  Sound blipa = LoadSound("./res/blipa.wav");

  RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
  Shader shader = LoadShader(0, TextFormat("./res/shader.frag", GLSL_VERSION));

  loadTilesetCR("./res/"+settings.font, ts, 16, 16);
  txtview.scale = settings.fontSize;
  txtview.margin = 1;
  txtview.squish = 2;
  qview.scale = settings.fontSize;
  imview.scale = settings.fontSize;
  
  imview.posx = 35;
  imview.posy = 0;
  double curTime = GetTime();
  while (!WindowShouldClose()) // TO CHANGER 
  {
    mtx.lock();
    switch(CanRead){
      case SAY:
      if(Message != "")
      {
        tiles::print(
            txtview,
            wrap(Message, 36), 0, 
            txtview.maxLine+1, 
            WHITE);
        Message = "";
        PlaySound(blipt);
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
      case CLR:
        txtview.tiles.clear();
        txtview.maxLine = -1;
        CanRead = 0;
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
    
     GameRender(
      txtview, qview, imview, ts, 
      screenWidth, screenHeight,
      currentImg, target, shader);
    //-------
    //INPUTS 
    //-------
    if(CanRead == ASK){ 
      if(IsKeyPressed(KEY_UP))
      {
        choice++;
        PlaySound(blipa);
      }
      if(IsKeyPressed(KEY_DOWN))
      {
        choice--;
        PlaySound(blipa);
      }
    }
    
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

    if(GetTime()-curTime > 0.1 && CanRead != ASK && Waiting > 0)
    {
      curTime = GetTime();
      mtx.lock();
      Waiting--;
      if(Waiting == 0)
      {
        CanContinue = true;
      }
      mtx.unlock();
    }
  }
  
  CloseAudioDevice();
  CloseWindow();
  mtx.lock();
  Terminate = true;
  mtx.unlock();

  return 0;
}

int GameRender(
  tilemap& txtview, 
  tilemap& qview, 
  tilemap& imview, 
  tileset& ts, 
  int screenWidth, 
  int screenHeight,
  std::string currentImg,
  RenderTexture& target,
  Shader& shader)
{
  BeginTextureMode(target);
    ClearBackground(BLACK);
    tiles::draw(txtview, ts, screenWidth, screenHeight);
    if(CanRead == ASK){tiles::draw(qview, ts, screenWidth, screenHeight);}
    if(currentImg != ""){tiles::draw(imview, ts, screenWidth, screenHeight);}
  EndTextureMode();

  BeginDrawing();
    if(settings.shader){ 
      BeginShaderMode(shader);
        DrawTextureRec(
          target.texture, 
          (Rectangle){0, 0, 
            (float)target.texture.width, 
            (float)-target.texture.height 
            },
          (Vector2){ 0, 0 }, 
          WHITE);
      EndShaderMode();
    }else{
      DrawTextureRec(
          target.texture, 
          (Rectangle){0, 0, 
            (float)target.texture.width, 
            (float)-target.texture.height 
            },
          (Vector2){ 0, 0 }, 
          WHITE);

    }
  EndDrawing();
  return 0;
}


int loadTSI(std::string path, tilemap& tm)
{
  std::string myText;
  std::ifstream readim("./res/"+path);
  tm.tiles.clear();
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
