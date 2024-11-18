#include "tiles.hpp"
#include <iostream>
#include "aliases.hpp"

int draw(tilemap &tm, tileset &ts, int maxX, int maxY)
{
  for(int i = 0; i < tm.tiles.size(); i++)
  {
    tile t = tm.tiles[i];
    float nposx = (t.posx + tm.posx)*tm.scale;
    float nposy = (t.posy + tm.posy)*tm.scale;
    float s = tm.scale;
    if(nposx >= maxX || nposy >= maxY)
      continue; 
    if((nposx+s) <= 0 || (nposy+s) <= 0)
      continue;
    int rat = (int)(ts.width/ts.twidth);
    int tposx = (int)t.val % rat;
    int tposy = (int)(t.val - tposx) / rat;
    if(!tm.transparent)
      DrawRectangle(nposx, nposy, s, s, BLACK);
    
    Rectangle frec = {
      tposx*ts.twidth,
      tposy*ts.theight,
      ts.twidth, 
      ts.theight};
    Rectangle fsize = {(float)nposx,(float)nposy,s,s};
    DrawTexturePro(
      ts.sheet,
      frec, 
      fsize,
      (Vector2){0, 0}, 
      0.0f,
      t.c
      );
  }
  return 0;
}

bool EqCol(Color a, Color b)
{
  return (a.r == b.r) && (a.g == b.g) && (a.b == b.b) && (a.a == b.a);
}

int loadTilesetCR(std::string path, tileset& out, int c, int r)
{
  if(EqCol(out.asAlpha,BLANK)){
    out.sheet = LoadTexture(path.c_str());
  }else{
    Image img = LoadImage(path.c_str()); 
    ImageColorReplace(&img, out.asAlpha, BLANK);
    out.sheet = LoadTextureFromImage(img); 
    UnloadImage(img);
  }
  GenTextureMipmaps(&out.sheet);
  out.width = out.sheet.width;
  out.height = out.sheet.height;
  out.twidth = (float)out.sheet.width/c;
  out.theight = (float)out.sheet.height/r;
  return 0;
}

int place(tilemap &tm, int posx, int posy, int v, Color col)
{
  tm.tiles.push_back(
    (tile){posx, posy, v, col}
  );
  return 0;
}

unsigned char nameToChar(std::string name)
{
  unsigned char c = '\0';
  int l = sizeof(ctable)/sizeof(ctable[0]);
  for(int i = 0; i < l; i++)
  {
    if(ctable[i].alias == name)
    {
      //std::cout << name << " | " << ctable[i].c << std::endl;
      c =(unsigned char)ctable[i].c;
      break;
    }
  }
  return c;
}

struct CChar 
{
  unsigned char c;
  Color col;
};

std::vector<CChar> conv(std::string msg, Color oldC)
{
  Color curc = oldC;
  std::vector<CChar> out;
  int idx = 0;
  while(idx < msg.size()){
    if(msg[idx]=='<'){
      bool tooBig = false;
      std::string buf = "";
      for(int i = 0; i < 14; i++) //arbitrary upper bound
      {
        if(idx+i<msg.size()){
          buf+=msg[i+idx];
          if(msg[i+idx] == '>')
            break;
        } else 
          tooBig = true;
      }
      if(tooBig)
        out.push_back({(unsigned char)msg[idx], curc});
      else {
        unsigned char c = nameToChar(buf);
        out.push_back({c, curc});
        idx+=buf.size()-1;
      }
    }
    else if(msg[idx]==':')
    {
      std::string buf = "";
      if(idx+7 < msg.size())
      {
        if(msg[idx+7]==':')
        {
          std::string hexcode = msg.substr(idx+1, 6);
          //std::cout << "Color code : "  << hexcode << std::endl; 
          Color newcol = {
            (unsigned char)std::stoi(hexcode.substr(0, 2), 0, 16),
            (unsigned char)std::stoi(hexcode.substr(2, 2), 0, 16),
            (unsigned char)std::stoi(hexcode.substr(4, 2), 0, 16),
            255,
          };
          //std::cout << "Color > " << (int)newcol.r << " : "
          //                        << (int)newcol.g << " : "
          //                        << (int)newcol.b << " : " << std::endl;
          curc = newcol;
          idx+=8;
          continue;
        }
      }
      out.push_back( {(unsigned char)msg[idx], curc});
    }
    else 
    {
      out.push_back( {(unsigned char)msg[idx], curc});
    }
    idx++;
  }
  return out;
}

int write(tilemap &tm,std::string msg,int px,int py, Color col)
{
  std::vector<CChar> cvd = conv(msg, col);
  int doff = 0;
  for(int i = 0; i<cvd.size(); i++)
  {
    place(tm, px+i-doff, py, cvd[i].c, cvd[i].col);
  }
  return 0;
}

std::vector<std::string> split(std::string s, char c)
{
  std::vector<std::string> out;
  std::string buf = "";
  for(int i = 0; i<s.size();i++)
  {
    if(s[i] == c){
      out.push_back(buf);
      buf = "";
    }
    else
    {
      buf+=s[i];
    }
  }
  out.push_back(buf);
  return out;
}

int print(tilemap &tm,std::string msg, int px, int py, Color col)
{
  std::vector<std::string> lines = split(msg, '\n');
  for(int i = 0; i<lines.size(); i++)
  {
    write(tm, lines[i], px, py+i, col);
  }
  return 0;
}
