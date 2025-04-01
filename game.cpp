#include <iostream>
#include <sstream>
#include <raylib.h>
#include <fstream>
#include <cmath>
#include "game.hpp"
#include "tiles.hpp"

extern std::mutex mtx;
extern Settings_t settings;
extern Event_t event;
extern bool LuaRun, Terminate; 
//LuaRun : Is lua able to run ? false if waiting for something on cpp side 
//Terminate : safe switch. Should prevent all activity and quit every function if true

tilemap txtview;
tilemap qview;
tilemap imview; 
tileset ts;
const int screenWidth = 1000;
const int screenHeight = 450;
std::string currentImg = "";
RenderTexture target;
Shader shader;
int choice = -1; //Selected answer (-1 if nothing to ask)
int Waiting = 0; //Time before next msg


int GameProcess(bool verbose)
{ 
  bool printed_setting_message = false;

  while(!settings.loaded)
  {
    if(!printed_setting_message){
      std::cout << "[C++] Waiting for settings" << std::endl;
      printed_setting_message=true;
    }
  }

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  //SetTraceLogLevel(LOG_INFO | LOG_WARNING); 
  
  InitWindow(
    screenWidth, 
    screenHeight, 
    "Console - 91 Rue Des Vignoles.exe"
  );

  InitAudioDevice();
  SetTargetFPS(60);
  
  //Load sounds
  Sound blipt = LoadSound("./res/blipt.wav"); //text sound
  Sound blipa = LoadSound("./res/blipa.wav"); //question sound

  target = LoadRenderTexture(screenWidth, screenHeight); //Used for shaders
  shader = LoadShader(0, TextFormat("./res/shader.frag", GLSL_VERSION)); //Said shader

  //Loading font settings
  loadTilesetCR("./res/"+settings.font, ts, 16, 16);
  txtview.scale = settings.fontSize;
  txtview.margin = 1;
  txtview.squish = 2;
  qview.scale = settings.fontSize;
  imview.scale = settings.fontSize;
 
  std::string imgpath;
  imview.posx = 35;
  imview.posy = 0;
  
  std::vector<std::string> opts;
  double curTime = GetTime();
  while (!WindowShouldClose()) // TO CHANGER 
  {
    mtx.lock();
    switch(event.type){
      case SAY:
      {
        //std::cout << "SAY : " << event.msg << std::endl;
        if(event.msg != "")
        { 
          tiles::print(txtview, wrap(event.msg, 36), 0, txtview.maxLine+1, WHITE);
          PlaySound(blipt);
        }
        event.type = NOTHING;
        break;
      }
      case ASK:
      {
        std::cout << "[C++] ASK : " << event.msg  << " : " << event.data << std::endl; 
        //Read the options
        if(event.data == 0){ event.type = NOTHING;}
        else
        {
          event.type = WAIT;
          Waiting = -event.data; //Negative waiting times = serial com
          opts.push_back(event.msg);
        }
        break;
      }
      case WAIT:
        //std::cout << "WAIT : " << event.data << "\r"; 
        Waiting = event.data;
        break;
      case CLR:
        txtview.tiles.clear();
        txtview.maxLine = -1;
        event.type = NOTHING;
        break;
      case IMG:
        imgpath = event.msg;
        loadTSI(imgpath, imview);
        std::cout << "[C++] Loading image : " << imgpath << std::endl; 
        event.type = NOTHING;
        break;
      default:
        break;
    }
    mtx.unlock();

    //To rework 
    //place textview at the bottom of the screen 
    int txt_pos = std::floor((float)screenHeight/txtview.scale)-(txtview.maxLine+1);
    txt_pos -= opts.size();
    int q_pos = std::floor((float)screenHeight/qview.scale)-(qview.maxLine+1);

    txtview.posy = txt_pos;
    qview.posy = q_pos;
    
    GameRender();
    
    if(event.type == WAIT && opts.size() > 0){ 
      qview.tiles.clear(); //Rewrite whole question screen
      qview.maxLine = 0;
      for(int i = 0; i < opts.size(); i++)
      {
        std::string o = opts[i];
        if(i == choice){o = "<rightarrow>:0000FF:" + o;}
        else{o=" "+o;}
        tiles::print(qview,o, 0, qview.maxLine+1,WHITE);
      }
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
      if(choice < 0)
      {
        choice = opts.size()-1;
      }
      else if(choice >= opts.size())
      {
        choice = 0;
      }
      if(IsKeyDown(KEY_ENTER) && !LuaRun)
      {
        mtx.lock(); 
        std::cout << "[C++] Validated : " << choice << std::endl;
        event.type = RESPONSE;
        event.data = choice;
        LuaRun = true;
        mtx.unlock();
        qview.tiles.clear();
        opts.clear();
        curTime = GetTime();
      }
    }
    
    if(GetTime()-curTime > 0.1 && Waiting > 0)
    {
      curTime = GetTime();
      mtx.lock();
      Waiting--;
      event.data--;
      if(Waiting == 0)
      {
        LuaRun = true;
        event.type = NOTHING;
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

int GameRender()
{
  std::string debug = "Event Type :" + std::to_string(event.type) 
                    + "\nEvent Data :" + std::to_string(event.data)
                    + "\nEvent Msg  :\"" + event.msg + "\"";   

  BeginTextureMode(target);
    ClearBackground(BLACK); 
    tiles::draw(txtview, ts, screenWidth, screenHeight);
    tiles::draw(qview, ts, screenWidth, screenHeight);
    tiles::draw(imview, ts, screenWidth, screenHeight);
    DrawText(debug.c_str(), 4, 4, 20, GREEN);
  EndTextureMode();

  BeginDrawing();
  if(settings.shader){BeginShaderMode(shader);}
    DrawTextureRec(
      target.texture, 
      (Rectangle){0, 0, 
        (float)target.texture.width, 
        (float)-target.texture.height 
      },
      (Vector2){ 0, 0 }, 
      WHITE);
  if(settings.shader){EndShaderMode();}
  EndDrawing();
  return 0;
}


int loadTSI(std::string path, tilemap& tm)
{
  std::string myText;
  std::ifstream readim("./res/"+path);
  if(readim.fail())
    std::cout << "[C++] Couldn't open " << path << std::endl;
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
