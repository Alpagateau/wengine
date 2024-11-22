#ifndef STRUCTS_HPP 
#define STRUCTS_HPP 
#include <iostream>
#include <vector>
#include <queue>
#include <string>

#define NOTHING  0
#define SAY      1
#define ASK      2

struct Settings_t 
{
  bool loaded = false;
  std::string font;
  float fontSize = -1;
};

#endif
