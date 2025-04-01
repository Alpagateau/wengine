#ifndef STRUCTS_HPP 
#define STRUCTS_HPP 
#include <iostream>
#include <vector>
#include <queue>
#include <string>

#define NOTHING  0
#define SAY      1
#define ASK      2
#define CLR      3
#define IMG      4
#define WAIT     5
#define RESPONSE 6

struct Settings_t 
{
  bool loaded = false;
  std::string font;
  float fontSize = -1;
  bool shader = false;
};

struct Event_t
{
  int type = 0;
  //any usefull numerical value. Timer, index...
  int data = 0;
  std::string msg = "";
};

#endif
