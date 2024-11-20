#ifndef TILES_HPP 
#define TILES_HPP 

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "raylib.h"

struct tile
{
  int posx = 0;
  int posy = 0;
  int val = 0;
  Color c = WHITE;
};

struct tileset 
{
  Texture2D sheet;
  float twidth;
  float theight;
  int width;
  int height;
  Color asAlpha = MAGENTA;
};

struct tilemap 
{
  int posx = 0;
  int posy = 0;
  float scale = 1;
  bool transparent;
  std::vector<Color> mapping = {BLACK, RED, GREEN, BLUE, RAYWHITE};
  std::vector<tile> tiles;
  int maxLine = -1;
};

int loadTilesetCR(std::string,tileset&,int,int);
//TODO
//Somewhy, jenky texture scaling, to be improved
namespace tiles{
  int draw(tilemap&,tileset&,int,int);
  int place(tilemap&,int,int,int,Color);
  int write(tilemap&,std::string,int,int,Color);
  int print(tilemap&,std::string,int,int,Color);
}
#endif 
