#ifndef TILES_HPP 
#define TILES_HPP 

#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"

struct tile
{
  int posx = 0;
  int posy = 0;
  int val = 0;
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
};

int loadTilesetCR(std::string,tileset&,int,int);
//TODO
//Somewhy, jenky texture scaling, to be improved
int draw(tilemap&,tileset&,int,int);
int place(tilemap&,int,int,int);
int write(tilemap&,std::string,int,int);
int print(tilemap&,std::string,int,int);

#endif 
